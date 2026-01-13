/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:07:46 by demane            #+#    #+#             */
/*   Updated: 2026/01/13 03:20:38 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

t_cmd	ft_parse_cmd(char *cmd_line)
{
	t_cmd	cmd;

	cmd.arg = ft_split(cmd_line, 32);
	if (!cmd.arg)
		return (cmd.cmd = NULL, cmd);
	cmd.cmd = cmd.arg[0];
	return (cmd);
}

void	ft_parse_all_cmd(t_pipex *pip, char **av)
{
	int	i;

	i = -1;
	while (++i < pip->cmd_count)
	{
		pip->cmds[i] = ft_parse_cmd(av[i + 2 + pip->here_doc]);
		if (pip->cmds[i].arg == NULL)
		{
			ft_free_all_pipex(pip);
			exit(1);
		}
	}
}
