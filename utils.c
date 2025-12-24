/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 22:06:59 by demane            #+#    #+#             */
/*   Updated: 2025/12/24 22:08:13 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_alloc_pip(t_pipex *pip)
{
	pip->cmds = (t_cmd *)malloc(sizeof(t_cmd) * (pip->cmd_count + 1));
	if (pip->cmds == NULL)
	{
		exit(1);
	}
	pip->pid = (int *)malloc(sizeof(int) * pip->cmd_count);
	if (!pip->pid)
	{
		ft_free((void **)&pip->cmds);
		exit (1);
	}
	pip->cmds[pip->cmd_count].arg = NULL;
}

int	ft_exit_pg(t_pipex pip, char **av, int ac, int status)
{
	if (pip.outfile == -1)
	{
		perror(av[ac -1]);
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}