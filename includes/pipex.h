/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:51:47 by demane            #+#    #+#             */
/*   Updated: 2025/12/19 15:25:05 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
// # include ""

typedef struct s_pipex
{
	int		infile;//C’est le file descriptor du fichier d’entrée.
	int		outfile;//C’est le file descriptor du fichier de sortie
	int		here_doc;//Un flag (0 ou 1) pour savoir si on est en mode here_doc.
	int		cmd_count;//Nombre total de commandes à exécuter.
	int		cmd_index;//Index de la commande en cours d’exécution.
	char	**envp;//Copie de envp reçue dans main.
	char	***cmds;//Toutes les commandes, déjà découpées.
	int		prev_fd;//Stocke le fd du pipe précédent.
	int		pipe_fd[2];//Le pipe courant.
}	t_pipex;

#endif
