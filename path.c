/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:40:32 by demane            #+#    #+#             */
/*   Updated: 2025/12/26 01:03:55 by demane           ###   ########.fr       */
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

char	*ft_get_path(char **envp, t_cmd cmd, t_pipex p)
{
	char	*path;
	int		index;
	char	**split_val;
	int		i;
	int		j;

	if (!cmd.cmd || ft_strlen(cmd.cmd) == 0 || ft_str_is_space(cmd.cmd))
		ft_throw_err_cmd_not_found(cmd, (void **)NULL, p);
	if (ft_access(cmd.cmd, p))
	{
		path = ft_strdup(cmd.cmd);
		if (!path)
		{
			ft_free_all_pipex(&p);
			exit(1);
		}
		return (path);
	}
	index = ft_get_index_path(envp);
	if (index == -1)
	{
		ft_throw_err_cmd_not_found(cmd, (void **)NULL, p);
		return (NULL);
	}
	split_val = NULL;
	path = envp[index] + 5;
	split_val = ft_split(path, ':');
	if (!split_val)
		return (NULL);
	i = -1;
	while (split_val[++i])
	{
		path = ft_strjoin_sep(split_val[i], cmd.cmd, '/');
		if (!path)
		{
			j = -1;
			while (split_val[++j])
				ft_free((void **)&split_val[j]);
			ft_free((void **)&split_val);
			ft_free_all_pipex(&p);
			exit(1);
		}
		if (ft_access(path, p))
			return (ft_free((void **)&split_val[i]),\
				ft_free((void **)&split_val), path);
		ft_free((void **)&split_val[i]);
		ft_free((void **)&path);
	}
	ft_throw_err_cmd_not_found(cmd, (void **)&split_val, p);
	return (NULL);
}
