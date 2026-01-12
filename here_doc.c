/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:41:28 by demane            #+#    #+#             */
/*   Updated: 2026/01/12 14:30:28 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_here_doc(t_pipex *pip, char *limiter)
{
	char	*str;
	int		fd[2];
	t_line	l;

	if (pipe(fd) != 0)
		return (-1);
	l.fd = STDIN_FILENO;
	l.line = NULL;
	l.next = NULL;
	while (1)
	{
		ft_putstr_fd("pipe heredoc>", 1);
		str = get_next_line(STDIN_FILENO, &l);
		if (!str)
			break ;
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter)] == '\n')
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd[1]);
		free(str);
	}
	return (close(fd[1]), ft_free((void **)&l.line), pip->infile = fd[0], 0);
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
