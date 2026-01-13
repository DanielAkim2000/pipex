/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:41:28 by demane            #+#    #+#             */
/*   Updated: 2026/01/13 03:31:13 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_write_in_child(int fd[2], char *limiter, t_line *l)
{
	char	*str;

	write(1, ">", 1);
	str = get_next_line(STDIN_FILENO, l);
	if (!str)
		return (1);
	if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
		&& str[ft_strlen(limiter)] == '\n')
	{
		ft_free((void **)&str);
		return (1);
	}
	write(fd[1], str, ft_strlen(str));
	free(str);
	return (0);
}

int	ft_here_doc(t_pipex *pip, char *limiter)
{
	int		fd[2];
	pid_t	pid;
	int		check;
	t_line	l;

	l.fd = STDIN_FILENO;
	l.line = NULL;
	l.next = NULL;
	check = 0;
	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(fd[0]);
		while (check == 0)
			check = ft_write_in_child(fd, limiter, &l);
		close(fd[1]);
		ft_free((void **)&(l.line));
		exit(0);
	}
	return (wait(NULL), close(fd[1]), pip->infile = fd[0], 0);
}

void	ft_verif_here_doc(t_pipex *pip, char **av)
{
	int	test;

	test = 0;
	if (pip->here_doc)
	{
		test = ft_here_doc(pip, av[2]);
		if (test == -1)
		{
			exit (1);
		}
	}
}
