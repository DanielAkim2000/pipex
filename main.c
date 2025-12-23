/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:15 by demane            #+#    #+#             */
/*   Updated: 2025/12/23 15:28:57 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pip;
	int		i;
	char	*path;

	if (ac < 5)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		return (1);
	}
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6)
	{
		ft_putstr_fd("Error: invalid number of arguments for here_doc\n", 2);
		return (1);
	}
	ft_init_pipex(ac, av, envp, &pip);
	pip.cmds = (t_cmd *)malloc(sizeof(t_cmd) * pip.cmd_count);
	// if (!pip.cmds)
	// 	return (ft_perror("malloc"));
	i = -1;
	while (++i < pip.cmd_count)
	{
		pip.cmds[i] = ft_parse_cmd(av[i + 2 + pip.here_doc]);
		// if (!pip.cmds[i].cmd)
		// 	return (ft_perror("malloc"), ft_free_pip(pip, i));
	}
	// path = ft_get_path(pip.envp);
	// // if (!path)
	// // 	return (perror());
	if (pip.here_doc)
	{
		if (ft_here_doc(&pip, av[2]) == -1)
			return (0);
	}
	pip.prev_fd = pip.infile;
	i = 0;
	// printf("ETAT\n");
	// printf("nb_cmd: %d, pip.prev_fd : %d\n", pip.cmd_count, pip.prev_fd);
	while (i < pip.cmd_count)
	{
		if (i < pip.cmd_count -1)
			pipe(pip.pipe_fd);
		if (fork() == 0)
		{
			dup2(pip.prev_fd, STDIN_FILENO);
			if (i < pip.cmd_count - 1)
				dup2(pip.pipe_fd[1], STDOUT_FILENO);
			else
				dup2(pip.outfile, STDOUT_FILENO);
			if (i < pip.cmd_count - 1)
			{
				close(pip.pipe_fd[0]);
				close(pip.pipe_fd[1]);
			}
			else
				close(pip.outfile);
			close(pip.prev_fd);
			path = ft_get_path(envp, pip.cmds[i]);
			ft_exec_cmd(path, &pip.cmds[i], envp);
		}
		close(pip.prev_fd);
		if (i < pip.cmd_count - 1)
			close(pip.pipe_fd[1]);
		else
			close(pip.outfile);
		if (i < pip.cmd_count - 1)
			pip.prev_fd = pip.pipe_fd[0];
		else
			pip.prev_fd = -1;
		i++;
	}
	int	j;
	j = 0;
	while (j < pip.cmd_count)
	{
		wait(NULL);
		j++;
	}
	// return (perror());
}
