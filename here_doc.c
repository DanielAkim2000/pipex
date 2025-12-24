/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:41:28 by demane            #+#    #+#             */
/*   Updated: 2025/12/24 22:16:56 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_here_doc(t_pipex *pip, char *limiter)
{
	char	*str;
	int		fd[2];

	if (pipe(fd) != 0)
		return (-1);
	while (1)
	{
		ft_putstr_fd("pipe heredoc>", 1);
		str = get_next_line(STDIN_FILENO);
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
	return (close(fd[1]), pip->infile = fd[0], 0);
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