/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 16:53:43 by demane            #+#    #+#             */
/*   Updated: 2026/01/12 15:03:34 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_throw_error_cmd(char *err_p, t_pipex p)
{
	perror(err_p);
	ft_free_all_pipex(&p);
	if (errno == EACCES || errno == ENOEXEC)
		exit (126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}

void	ft_throw_err_cmd_not_found(char *err_p, void **split_val, t_pipex p)
{
	char	*mess;

	mess = ft_strjoin(err_p, ": command not found\n");
	ft_putstr_fd(mess, STDERR_FILENO);
	ft_free((void **)&mess);
	ft_free_all_pipex(&p);
	ft_free(split_val);
	exit(127);
}
