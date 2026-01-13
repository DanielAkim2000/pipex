/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:43:22 by demane            #+#    #+#             */
/*   Updated: 2026/01/13 01:47:24 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_free_pid(t_pid *pid)
{
	ft_free((void **)&pid->pid);
	ft_free((void **)&pid->status);
}

void	ft_free_all_pipex(t_pipex *p)
{
	int		i;
	int		j;
	char	**arg;

	i = -1;
	if (p->cmds)
	{
		while (p->cmds[++i].arg)
		{
			arg = p->cmds[i].arg;
			j = -1;
			while (arg[++j])
				ft_free((void **)&arg[j]);
			ft_free((void **)&arg);
			p->cmds[i].cmd = NULL;
		}
	}
	ft_free_pid(&p->pid);
	ft_free((void **)&p->cmds);
}
