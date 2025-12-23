/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:47 by demane            #+#    #+#             */
/*   Updated: 2025/12/23 15:28:53 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>

typedef struct cmd
{
	char	*cmd;
	char	**arg;
}	t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		cmd_count;
	int		cmd_index;
	char	**envp;
	t_cmd	*cmds;
	int		prev_fd;
	int		pipe_fd[2];
}	t_pipex;


void	ft_init_pipex(int ac, char **av, char **envp, t_pipex *pip);
t_cmd	ft_parse_cmd(char *cmd_line);
char	*ft_get_path(char **envp, t_cmd cmd);
int		ft_here_doc(t_pipex *pip, char *limiter);
int		ft_exec_cmd(char *path, t_cmd *cmd, char **envp);
char	*get_next_line(int fd);

#endif
