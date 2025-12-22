/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:41:28 by demane            #+#    #+#             */
/*   Updated: 2025/12/21 17:51:56 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	ft_here_doc(t_pipex *pip, char *limiter)
{
	char	*str;
	int		fd[2];
	int		err;

	if (pipe(fd) != 0)
		return (-1);
	err = 0;
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		str = get_next_line(fd[0]);
		if (!str)
		{
			err = -1;
			break ;
		}
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter)] == '\n')
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd[1]);
		free(str);
	}
	return (close(fd[0]), pip->infile = fd[1], err);
}
