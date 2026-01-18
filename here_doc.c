/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:41:28 by demane            #+#    #+#             */
/*   Updated: 2026/01/19 00:22:38 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_write_here_doc(int fd, char *limiter, t_line *l)
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
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		ft_free((void **)&str);
		ft_free((void **)&l->line);
		return (-1);
	}
	ft_free((void **)&str);
	return (0);
}

int	ft_here_doc(t_pipex *pip, char *limiter)
{
	int		fd;
	int		check;

	check = 0;
	pip->l.fd = STDIN_FILENO;
	fd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), -1);
	while (check == 0)
	{
		check = ft_write_here_doc(fd, limiter, &pip->l);
		if (check == -1)
			return (close(fd), -1);
	}
	close(fd);
	ft_free((void **)&pip->l.line);
	pip->infile = open(".here_doc_tmp", O_RDONLY);
	if (pip->infile < 0)
		return (perror("open"), -1);
	return (0);
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
