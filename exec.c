/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:13:23 by demane            #+#    #+#             */
/*   Updated: 2025/12/23 15:33:41 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_exec_cmd(char *path, t_cmd *cmd, char **envp)
{
	if (execve(path, cmd->arg, envp) == -1)
	{
		printf("errorrrrrr\n %s\n", path);
		return (ft_free((void **)&path), -1);
	}
	return (0);
}
