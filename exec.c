/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:13:23 by demane            #+#    #+#             */
/*   Updated: 2025/12/21 16:36:26 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_exec_cmd(char *path, t_cmd *cmd)
{
	char	*path_with_cmd;

	path_with_cmd = ft_strjoin_sep(path, cmd->cmd, '/');
	if (!path_with_cmd)
		return (-1);
	if (execv(path_with_cmd, cmd->arg) == -1)
		return (ft_free((void **)&path_with_cmd), -1);
	return (0);
}
