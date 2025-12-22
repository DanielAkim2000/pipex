/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:07:46 by demane            #+#    #+#             */
/*   Updated: 2025/12/21 14:59:04 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

t_cmd	ft_parse_cmd(char *cmd_line)
{
	t_cmd	cmd;
	int		i;

	cmd.arg = ft_split(cmd_line, 32);
	if (!cmd.arg)
		return (cmd.cmd = NULL, cmd);
	cmd.cmd = cmd.arg[0];
	return (cmd);
}