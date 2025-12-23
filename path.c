/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:40:32 by demane            #+#    #+#             */
/*   Updated: 2025/12/23 15:31:38 by demane           ###   ########.fr       */
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

int	ft_access(char *path)
{
	int	acs_val;

	acs_val = access(path, X_OK);
	if (acs_val == 0)
		return (1);
	return (0);
}

char	*ft_get_path(char **envp, t_cmd cmd)
{
	char	*path;
	int		index;
	char	**split_val;
	int		i;

	index = ft_get_index_path(envp);
	if (index == -1)
		return (NULL);
	path = envp[index] + 5;
	split_val = ft_split(path, ':');
	if (!split_val)
		return (NULL);
	i = -1;
	while (split_val[++i])
	{
		path = ft_strjoin_sep(split_val[i], cmd.cmd, '/');
		if (ft_access(path))
			return (ft_free((void **)&split_val[i]), ft_free((void **)&split_val), path);
		ft_free((void **)&split_val[i]);
		ft_free((void **)&path);
	}
	return (ft_free((void **)&split_val), NULL);
}
