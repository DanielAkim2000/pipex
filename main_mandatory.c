/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:15 by demane            #+#    #+#             */
/*   Updated: 2025/12/25 00:28:55 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_invalid_ac_av_envp(int ac, char **envp)
{
	if (ac != 5)
	{
		ft_putstr_fd("error: invalid number of arguments\n", 2);
		exit (1);
	}
	if (!envp)
	{
		ft_putstr_fd("envp: Not envp setted\n", STDERR_FILENO);
		exit(1);
	}
}

void	ft_verif_infile(t_pipex *pip, char **av)
{
	if ((pip->infile == -1))
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
	int		status;

	ft_invalid_ac_av_envp(ac, envp);
	ft_init_pipex_mandatory(ac, av, &pip);
	ft_verif_infile(&pip, av);
	ft_verif_here_doc(&pip, av);
	ft_alloc_pip(&pip);
	ft_parse_all_cmd(&pip, av);
	ft_process_parent(&pip, envp);
	ft_wait_all_child(pip, &status);
	ft_free_all_pipex(&pip);
	return (ft_exit_pg(pip, av, ac, status));
}
