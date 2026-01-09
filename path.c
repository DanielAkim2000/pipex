/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:40:32 by demane            #+#    #+#             */
/*   Updated: 2026/01/06 13:16:38 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_get_index_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
	}
	return (-1);
}

int	ft_access(char *path, t_pipex p)
{
	int	acs_val;

	if (!path)
		return (0);
	if (ft_strchr(path, '/') == NULL)
		return (0);
	acs_val = access(path, X_OK);
	if (acs_val == 0)
		return (1);
	if (errno == EACCES)
	{
		perror(path);
		ft_free_all_pipex(&p);
		exit(126);
	}
	return (0);
}

void	ft_free_all_split_val(char ***split_val)
{
	char	**free_val;
	int		i;

	free_val = *split_val;
	if (!free_val)
		return ((void)0);
	i = 0;
	while (free_val[i])
	{
		ft_free((void **)&free_val[i]);
		i++;
	}
	ft_free((void **)&free_val);
}

char	*ft_try_paths(char ***split_val, char *cmd_name, t_pipex p)
{
	char	*path;
	int		i;

	i = -1;
	while ((*split_val)[++i])
	{
		path = ft_strjoin_sep((*split_val)[i], cmd_name, '/');
		if (!path)
		{
			ft_free_all_split_val(split_val);
			ft_free_all_pipex(&p);
			exit(1);
		}
		if (ft_access(path, p))
			return (ft_free_all_split_val(split_val), path);
		ft_free((void **)&path);
	}
	return (ft_free_all_split_val(split_val), NULL);
}

char	*ft_get_path(char **envp, t_cmd cmd, t_pipex p)
{
	char	*path;
	char	**split_val;
	int		index;

	if (!cmd.cmd || ft_strlen(cmd.cmd) == 0 || ft_str_is_space(cmd.cmd))
		ft_throw_err_cmd_not_found(cmd, NULL, p);
	if (ft_access(cmd.cmd, p))
		return (ft_strdup(cmd.cmd));
	index = ft_get_index_path(envp);
	if (index == -1)
		return (ft_throw_err_cmd_not_found(cmd, NULL, p), NULL);
	split_val = ft_split(envp[index] + 5, ':');
	if (!split_val)
		return (NULL);
	path = ft_try_paths(&split_val, cmd.cmd, p);
	if (!path)
		ft_throw_err_cmd_not_found(cmd, NULL, p);
	return (path);
}
