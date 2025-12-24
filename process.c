/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:41:24 by demane            #+#    #+#             */
/*   Updated: 2025/12/24 22:05:34 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_process_child(t_pipex *pip, char **envp, int fd[2], int index)
{
	char	*path;

	dup2(pip->prev_fd, STDIN_FILENO);
	if (index < pip->cmd_count - 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(pip->outfile, STDOUT_FILENO);
	if (index < pip->cmd_count - 1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	else
		close(pip->outfile);
	close(pip->prev_fd);
	path = ft_get_path(envp, pip->cmds[index], *pip);
	if (path)
		ft_exec_cmd(path, &pip->cmds[index], envp, *pip);
}

void	ft_process_parent(t_pipex *pip, char **envp)
{
	int		i;
	int		fd[2];

	pip->prev_fd = pip->infile;
	i = -1;
	while (++i < pip->cmd_count)
	{
		if (i < pip->cmd_count -1)
			pipe(fd);
		pip->pid[i] = fork();
		if (pip->pid[i] == 0)
			ft_process_child(pip, envp, fd, i);
		close(pip->prev_fd);
		if (i < pip->cmd_count - 1)
			close(fd[1]);
		else
			close(pip->outfile);
		if (i < pip->cmd_count - 1)
			pip->prev_fd = fd[0];
		else
			pip->prev_fd = -1;
	}
}

void	ft_wait_all_child(t_pipex pip, int *status)
{
	int	j;

	j = -1;
	while (++j < pip.cmd_count)
	{
		if (j < pip.cmd_count - 1)
			waitpid(pip.pid[j], NULL, 0);
		else
			waitpid(pip.pid[j], status, 0);
	}
}
