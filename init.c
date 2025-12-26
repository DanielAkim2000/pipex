/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:30:38 by demane            #+#    #+#             */
/*   Updated: 2025/12/26 00:05:13 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_init_pipex_bonus(int ac, char **av, t_pipex *pip)
{
	pip->here_doc = (ft_strncmp(av[1], "here_doc", 8) == 0);

	if (pip->here_doc)
	{
		pip->infile = -1;
		pip->outfile_name = av[ac -1];
		pip->open_mode = O_CREAT | O_WRONLY | O_APPEND;
		// pip->outfile = open(av[ac - 1],
		// 		O_CREAT | O_WRONLY | O_APPEND, 0644);
		pip->cmd_count = ac - 4;
	}
	else
	{
		pip->infile = open(av[1], O_RDONLY);
		pip->outfile_name = av[ac -1];
		pip->open_mode = O_CREAT | O_WRONLY | O_TRUNC;
		// pip->outfile = open(av[ac - 1],
		// 		O_CREAT | O_WRONLY | O_TRUNC, 0644);
		pip->cmd_count = ac - 3;
	}
	pip->outfile = -1;
	pip->prev_fd = -1;
	pip->cmds = NULL;
	(&(pip->pid))->pid = NULL;
	(&(pip->pid))->status = NULL;
}

void	ft_init_pipex_mandatory(int ac, char **av, t_pipex *pip)
{
	pip->here_doc = 0;
	pip->infile = open(av[1], O_RDONLY);
	pip->outfile_name = av[ac -1];
	pip->open_mode = O_CREAT | O_WRONLY | O_TRUNC;
	pip->cmd_count = ac - 3;
	pip->prev_fd = -1;
	pip->cmds = NULL;
	(&(pip->pid))->pid = NULL;
	(&(pip->pid))->status = NULL;
}
