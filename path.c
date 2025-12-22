/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:40:32 by demane            #+#    #+#             */
/*   Updated: 2025/12/21 17:37:57 by demane           ###   ########.fr       */
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

char	*ft_get_path(char **envp)
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
	path = "";
	i = -1;
	while (split_val[++i])
	{
		path = ft_strjoin_sep(path, split_val[i], '/');
		if (!path)
			// return (ft_free_all(split_val, i), NULL);
			return (NULL);
		if (ft_access(path))
			return (path);
	}
	return (NULL);
}
