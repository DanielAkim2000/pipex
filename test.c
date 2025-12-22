/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:33:20 by demane            #+#    #+#             */
/*   Updated: 2025/12/21 17:35:48 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>

// void	ft_free(void **p)
// {
// 	if (p && *p)
// 		free(*p);
// 	if (p && *p)
// 		*p = NULL;
// }

// /*
// int	main(int ac, char **av, char **envp)
// {
// 	char	**test;

// 	test = (char **)malloc(sizeof(char *) * 1);
// 	if (!test)
// 		return (1);
// 	printf("%p\n", test);
// 	ft_free((void **)&test);
// 	printf("%p\n", test);
// 	return (0);
// }
// */


// #include <stdio.h>
// #include <unistd.h>
// #include <sys/types.h>

// int main(void)
// {
//     pid_t pid;

//     printf("Avant fork\n");

//     pid = fork();
//     if (pid == -1)
//         return (1);

//     if (pid == 0)
//         printf("Je suis l'ENFANT (pid = %d)\n", getpid());
//     else
//         printf("Je suis le PARENT (pid = %d, enfant = %d)\n",
//                getpid(), pid);

//     printf("Fin du programme (pid = %d)\n", getpid());
//     return (0);
// }

// #include <stdio.h>
// #include <unistd.h>

// int main(void)
// {
//     printf("Avant exec\n");

//     execv("/bin/ls", (char *[]){"ls", NULL});

//     printf("Après exec (JAMAIS affiché si succès)\n");
//     return (0);
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main(void)
// {
//     pid_t pid;

//     pid = fork();
//     if (pid == 0)
//     {
//         printf("Enfant avant exec\n");
//         execv("/bin/ls", (char *[]){"ls", NULL});
//         perror("execv");
//     }
//     else
//     {
//         wait(NULL);
//         printf("Parent après wait\n");
//     }
//     return (0);
// }

// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>

// int main(void)
// {
//     int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

//     dup2(fd, STDOUT_FILENO);
//     close(fd);

//     printf("Ce texte va dans out.txt\n");
//     return (0);
// }

// #include <stdio.h>
// #include <unistd.h>

// int main(void)
// {
//     int fd[2];
//     char buf[100];

//     pipe(fd);

//     write(fd[1], "Hello pipe\n", 11);
//     read(fd[0], buf, 100);

//     printf("Lu depuis le pipe: %s", buf);

//     close(fd[0]);
//     close(fd[1]);
//     return (0);
// }

// #include <unistd.h>
// #include <sys/wait.h>

// int main(void)
// {
//     int fd[2];
//     pipe(fd);

//     if (fork() == 0)
//     {
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execv("/bin/echo", (char *[]){"echo", "Hello pipex", NULL});
//     }

//     if (fork() == 0)
//     {
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[1]);
//         close(fd[0]);
//         execv("/usr/bin/wc", (char *[]){"wc", "-c", NULL});
//     }

//     close(fd[0]);
//     close(fd[1]);
//     wait(NULL);
//     wait(NULL);
//     return (0);
// }

