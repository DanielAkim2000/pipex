/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:30:38 by demane            #+#    #+#             */
/*   Updated: 2025/12/21 17:38:30 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_init_pipex(int ac, char **av, char **envp, t_pipex *pip)
{
	pip->here_doc = (ft_strncmp(av[1], "here_doc", 8) == 0);

	if (pip->here_doc)
	{
		pip->infile = -1;
		pip->outfile = open(av[ac - 1],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		pip->cmd_count = ac - 4;
	}
	else
	{
		pip->infile = open(av[1], O_RDONLY);
		pip->outfile = open(av[ac - 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		pip->cmd_count = ac - 3;
	}
	// if (pip->infile < 0 && !pip->here_doc)
	// 	perror(av[1]);
	// if (pip->outfile < 0)
	// 	perror(av[ac - 1]);
	pip->cmd_index = 0;
	pip->prev_fd = -1;
	pip->envp = envp;
	pip->cmds = NULL;
}
