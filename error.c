/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 16:53:43 by demane            #+#    #+#             */
/*   Updated: 2025/12/25 00:24:35 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_throw_error_cmd(char *err_p, t_pipex p)
{
	if (errno == EACCES)
	{
		perror(err_p);
		ft_free_all_pipex(&p);
		exit (127);
	}
	if (errno == ENOENT)
	{
		ft_putstr_fd(err_p, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_free_all_pipex(&p);
		exit(127);
	}
	// if (errno == E)
}
