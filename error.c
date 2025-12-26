/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 16:53:43 by demane            #+#    #+#             */
/*   Updated: 2025/12/26 01:14:11 by demane           ###   ########.fr       */
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

void	ft_throw_err_cmd_not_found(t_cmd cmd, void **split_val, t_pipex p)
{
	perror(cmd.cmd);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd.cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_free_all_pipex(&p);
	ft_free(split_val);
	exit(127);
}
