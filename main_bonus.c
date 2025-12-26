/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:15 by demane            #+#    #+#             */
/*   Updated: 2025/12/26 00:35:22 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_invalid_ac_av_envp(int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", STDERR_FILENO);
		exit (1);
	}
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6)
	{
		ft_putstr_fd("Error: invalid number of arguments for here_doc\n",\
						 STDERR_FILENO);
		exit (1);
	}
	// if (!envp)
	// {
	// 	ft_putstr_fd("envp: Not envp setted\n", STDERR_FILENO);
	// 	exit(1);
	// }
}

void	ft_verif_infile(t_pipex *pip, char **av)
{
	if ((pip->infile == -1 && !pip->here_doc))
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

	ft_invalid_ac_av_envp(ac, av);
	ft_init_pipex_bonus(ac, av, &pip);
	ft_verif_infile(&pip, av);
	ft_verif_here_doc(&pip, av);
	ft_alloc_pip(&pip);
	ft_parse_all_cmd(&pip, av);
	ft_process_parent(&pip, envp);
	ft_wait_all_child(&pip);
	return (ft_exit_pg(&pip));
}
