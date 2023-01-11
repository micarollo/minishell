/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2023/01/11 15:33:57 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **enviroment)
{
	t_master	*master;

	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));
		if (!master)
			return (1);
		init_env(master, enviroment);
		init_redirs(master);
		while (!master->status)
		{
			//	printf("ERROR CODE: %d\n", g_error);
			master->line = readline(YELLOW"minishell: "RESET);
			master->status = add_hist_exit_check(master);
			if (master->status)
				break ;
			if (master->line == 0)
			{
				free_master(master);
				//write(1, "\n", 1);
				exit (1);
			}
			if (*master->line != '\0')
			{
				add_history(master->line); //asi parece que se soluciona
				minishell(master->line, master);
			}
		}
		close_init_redirs(master);
		free_master(master);
	}
	return (0);
}

/**
 * Adds line to the history
 * If line is "exit" changes master->status to 1 to end minishell loop and finish parent process
 * If line is empty and original STDIN is not a terminal (e.g. is a file) changes master->status to 1 to end minishell loop and finish parent process
*/
_Bool	add_hist_exit_check(t_master *master)
{
	if (master->line && ft_strcmp(master->line, "exit") == 0)
		return (1);
	if (isatty(STDIN_FILENO) == 0 && !master->line)
		return (1);
	return (0);
}

/**
 * Waits for all child processes
 * if there is only one command, the waitpid is done in the function exec_bin_one
*/
void	wait_childs(t_master *master)
{
	int	i;
	int	pid;
	int	j;

	i = master->numCommands;
	if(i == 1)
		return ;
	while(i--)
	{
		pid = waitpid(-1, &j, 0);
		if (pid == -1)
			clean_free_pipe_read(master, 1);
		if (pid == master->pid)
		{
			if (WIFEXITED(j))
				g_error = WEXITSTATUS(j);
		}
	}
	return ;
}

void	minishell(char *line, t_master *master)
{
	t_command	*cmd;

	init_pipe(master);
	if (parsing(line, master))
	{
		if (master->numCommands == 1)
			minishell_one(master);
		else
		{
			cmd = master->commands_list;
			while (cmd)
			{
				handle_outputs(cmd, master);
				handle_pipe(master, cmd);
				master->pid = fork();
				if (master->pid < 0)
				{
					close(master->fd[WRITE]);
					close(master->fd[READ]);
					clean_free(master, 1);
				}
				if (master->pid == 0)
				{
					handle_redirs(cmd, master);
					exec(master, cmd);
				}
				if(close(master->fd[WRITE]) == -1)
					clean_free_pipe_read(master, 1);
				cmd = cmd->next;
			}
		}
	}
	wait_childs(master);
	prep_next_line(master);
}
	