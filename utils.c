/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 22:06:59 by demane            #+#    #+#             */
/*   Updated: 2025/12/26 00:32:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_initialise(t_pid *tab, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		tab->status[i] = -1;
		tab->pid[i] = -1;
	}
}

void	ft_alloc_pip(t_pipex *pip)
{
	t_pid	*pid;

	pip->cmds = (t_cmd *)malloc(sizeof(t_cmd) * (pip->cmd_count + 1));
	if (pip->cmds == NULL)
	{
		exit(1);
	}
	pid = &(pip->pid);
	pid->pid = (int *)malloc((sizeof(int) * pip->cmd_count));
	if (!pid->pid)
	{
		ft_free_all_pipex(pip);
		exit(1);
	}
	pid->status = (int *)malloc((sizeof(int) * pip->cmd_count));
	if (!pid->status)
	{
		ft_free_all_pipex(pip);
		exit(1);
	}
	ft_initialise(&pip->pid, pip->cmd_count);
	pip->cmds[pip->cmd_count].arg = NULL;
}

int	ft_get_last_status(t_pid *p, int n)
{
	int	status;
	int	i;

	i = 0;
	status = -1;
	while (i < n)
	{
		if (p->pid[i] != -1)
		{
			status = p->status[i];
		}
		i++;
	}
	return (status);
}

int	ft_exit_pg(t_pipex *p)
{
	int	status;

	status = ft_get_last_status(&p->pid, p->cmd_count);
	ft_free_all_pipex(p);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
