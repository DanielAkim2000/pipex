/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:15 by demane            #+#    #+#             */
/*   Updated: 2025/12/26 14:31:41 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_invalid_ac_av_envp(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("error: invalid number of arguments\n", 2);
		exit (1);
	}
}

void	ft_verif_infile(t_pipex *pip, char **av)
{
	if (pip->infile == -1)
	{
		perror(av[1]);
		pip->infile = open("/dev/null", O_RDONLY);
		if (pip->infile == -1)
		{
			perror("/dev/null");
			exit(1);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pip;

	ft_invalid_ac_av_envp(ac);
	ft_init_pipex_mandatory(ac, av, &pip);
	ft_verif_infile(&pip, av);
	ft_verif_here_doc(&pip, av);
	ft_alloc_pip(&pip);
	ft_parse_all_cmd(&pip, av);
	ft_process_parent(&pip, envp);
	ft_wait_all_child(&pip);
	return (ft_exit_pg(&pip));
}
