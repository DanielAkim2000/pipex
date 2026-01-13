/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:47 by demane            #+#    #+#             */
/*   Updated: 2026/01/13 03:38:31 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "../get_next_line.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
}	t_cmd;

typedef struct s_pid
{
	int	*pid;
	int	*status;
}	t_pid;

typedef struct s_pipex
{
	int		infile;
	int		infile_err;
	int		infile_msg_aff;
	char	*msg_inf;
	int		outfile;
	int		here_doc;
	int		cmd_count;
	t_cmd	*cmds;
	int		prev_fd;
	t_pid	pid;
	char	*outfile_name;
	int		open_mode;
	char	**av;
}	t_pipex;

void	ft_init_pipex_mandatory(int ac, char **av, t_pipex *pip);
void	ft_init_pipex_bonus(int ac, char **av, t_pipex *pip);
t_cmd	ft_parse_cmd(char *cmd_line);
char	*ft_get_path(char **envp, t_cmd cmd, t_pipex p);
int		ft_here_doc(t_pipex *pip, char *limiter);
int		ft_exec_cmd(char *path, t_cmd *cmd, char **envp, t_pipex p);
void	ft_throw_error_cmd(char *err_p, t_pipex p);
void	ft_free_all_pipex(t_pipex *p);
void	ft_free_all_pipex(t_pipex *p);
void	ft_parse_all_cmd(t_pipex *pip, char **av);
void	ft_process_child(t_pipex *pip, char **envp, int fd[2], int index);
void	ft_process_parent(t_pipex *pip, char **envp);
void	ft_wait_all_child(t_pipex *pip);
void	ft_verif_here_doc(t_pipex *pip, char **av);
void	ft_alloc_pip(t_pipex *pip);
int		ft_exit_pg(t_pipex *pip);
void	ft_throw_err_cmd_not_found(char *err_p, void **split_val, t_pipex p);
int		ft_write_infile_err(t_pipex *pip);
int		ft_get_index_path(char **envp);
void	ft_free_all_split_val(char ***split_val);
int	ft_access(char **path_params, t_pipex p, char ***split_val, int bool);
char	*ft_try_paths(char ***split_val, char *cmd_name, t_pipex p);

#endif
