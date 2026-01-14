/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:41:24 by demane            #+#    #+#             */
/*   Updated: 2026/01/14 17:26:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_redirec_to_outfile(t_pipex *pip, char **envp, int index)
{
	char	*path;

	pip->outfile = open(pip->outfile_name, pip->open_mode, 0644);
	if (pip->outfile == -1)
	{
		perror(pip->outfile_name);
		close(pip->prev_fd);
		ft_free_all_pipex(&(*pip));
		exit(1);
	}
	dup2(pip->outfile, STDOUT_FILENO);
	close(pip->outfile);
	close(pip->prev_fd);
	path = ft_get_path(envp, pip->cmds[index], *pip);
	if (path)
		ft_exec_cmd(path, &pip->cmds[index], envp, *pip);
}

void	ft_process_child(t_pipex *pip, char **envp, int fd[2], int index)
{
	char	*path;

	dup2(pip->prev_fd, STDIN_FILENO);
	if (index < pip->cmd_count - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(pip->prev_fd);
		path = ft_get_path(envp, pip->cmds[index], *pip);
		if (path)
			ft_exec_cmd(path, &pip->cmds[index], envp, *pip);
	}
	else
		ft_redirec_to_outfile(pip, envp, index);
}

int	ft_process_cmd_not_end(int *i, t_pipex *pip, int fd[2], char **envp)
{
	while (++(*i) < pip->cmd_count - 1)
	{
		if (pipe(fd) == -1)
		{
			if (*i == 0)
				close(pip->prev_fd);
			return (-1);
		}
		pip->pid.pid[*i] = fork();
		if (pip->pid.pid[*i] == -1)
		{
			close(fd[1]);
			return (close(pip->prev_fd), close(fd[0]), -1);
		}
		if (pip->pid.pid[*i] == 0)
			ft_process_child(&(*pip), envp, fd, *i);
		close(pip->prev_fd);
		close(fd[1]);
		pip->prev_fd = fd[0];
	}
	return (0);
}

void	ft_process_parent(t_pipex *pip, char **envp)
{
	int		i;
	int		fd[2];

	pip->prev_fd = pip->infile;
	fd[0] = -1;
	fd[1] = -1;
	i = -1 + pip->infile_err;
	if (ft_process_cmd_not_end(&i, pip, fd, envp) == -1)
		return ((void)0);
	pip->pid.pid[pip->cmd_count -1] = fork();
	if (pip->pid.pid[pip->cmd_count -1] == -1)
		return (close(pip->prev_fd), close(fd[0]), (void)0);
	if (pip->pid.pid[pip->cmd_count - 1] == 0)
		ft_process_child(&(*pip), envp, fd, i);
	close(pip->prev_fd);
	pip->prev_fd = -1;
}

void	ft_wait_all_child(t_pipex *pip)
{
	t_pid	*pids;
	int		res_pid;
	int		stats;
	int		index[2];

	index[0] = 0;
	pids = &pip->pid;
	while (index[0] < pip->cmd_count + pip->here_doc)
	{
		res_pid = wait(&stats);
		if (pip->here_doc && res_pid == pip->pid_here_doc)
		{
			index[0] += 1;
			continue ;
		}
		index[1] = 0;
		while (index[1] < pip->cmd_count)
		{
			if (res_pid == pids->pid[index[1]])
				pids->status[index[1]] = stats;
			index[1] += 1;
		}
		index[0] += 1;
	}
}
