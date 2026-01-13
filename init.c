/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:30:38 by demane            #+#    #+#             */
/*   Updated: 2026/01/13 00:57:41 by demane           ###   ########.fr       */
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
		pip->cmd_count = ac - 4;
	}
	else
	{
		pip->infile = open(av[1], O_RDONLY);
		pip->outfile_name = av[ac -1];
		pip->open_mode = O_CREAT | O_WRONLY | O_TRUNC;
		pip->cmd_count = ac - 3;
	}
	pip->outfile = -1;
	pip->prev_fd = -1;
	pip->cmds = NULL;
	(&(pip->pid))->pid = NULL;
	(&(pip->pid))->status = NULL;
	pip->infile_err = 0;
	pip->infile_msg_aff = 0;
	pip->av = av;
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
	pip->infile_err = 0;
	pip->infile_msg_aff = 0;
	pip->av = av;
}
