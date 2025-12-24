/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:13:23 by demane            #+#    #+#             */
/*   Updated: 2025/12/25 00:25:46 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_exec_cmd(char *path, t_cmd *cmd, char **envp, t_pipex p)
{
	if (execve(path, cmd->arg, envp) == -1)
	{
		ft_free((void **)&path);
		ft_throw_error_cmd(cmd->cmd, p);
	}
	return (0);
}
