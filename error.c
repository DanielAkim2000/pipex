/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 16:53:43 by demane            #+#    #+#             */
/*   Updated: 2026/01/13 03:21:22 by demane           ###   ########.fr       */
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

	if (err_p == NULL)
		err_p = "";
	mess = ft_strjoin(err_p, ": command not found\n");
	ft_putstr_fd(mess, STDERR_FILENO);
	ft_free((void **)&mess);
	ft_free_all_pipex(&p);
	ft_free(split_val);
	exit(127);
}

int	ft_write_infile_err(t_pipex *pip)
{
	char	*msg;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!pip->infile_err)
		return (0);
	len = ft_strlen(pip->av[1]) + 2 + ft_strlen(pip->msg_inf) + 2;
	msg = malloc(sizeof(char) * len);
	if (!msg)
		return (-1);
	i = -1;
	while (++i < ft_strlen(pip->av[1]))
		msg[i] = pip->av[1][i];
	msg[i++] = ':';
	msg[i++] = ' ';
	j = 0;
	while (j < ft_strlen(pip->msg_inf))
		msg[i++] = pip->msg_inf[j++];
	return (msg[i++] = '\n', msg[i] = '\0', ft_putstr_fd(msg, STDERR_FILENO),
		ft_free((void **)&msg), 0);
}
