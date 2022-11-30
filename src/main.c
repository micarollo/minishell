/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/11/29 10:08:27 by arebelo          ###   ########.fr       */
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
		while (!master->status)
		{
			master->line = readline(YELLOW"minishell: "RESET);
			master->status = add_hist_exit_check(master);
			if (master->status)
				break ;
			minishell(master->line, master);
		}
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
	add_history(master->line);
	if (master->line && ft_strcmp(master->line, "exit") == 0)
	{
		free_line(master);
		return (1);
	}
	if (isatty(STDIN_FILENO) == 0 && !master->line)
		return (1);
	return (0);
}

void	minishell(char *line, t_master *master)
{
	t_command	*cmd;

	init_redirs(master);
	if (parsing(line, master))
	{
		// if (master->numCommands == 1)
		// 	minishell_one(master);
		// else
		// {
			cmd = master->commands_list;
			while (cmd)
			{
				handle_pipe(master, cmd);
				master->pid = fork();
				if (master->pid < 0)
					break ; //Correct + close fd[write]
				if (master->pid == 0)
					if (handle_redirs(cmd, master))
						exec(master, cmd);
				close(master->fd[WRITE]);
				waitpid(master->pid, NULL, 0);
				cmd = cmd->next;
			}
		//}
		prep_next_line(master);
	}
}

void	minishell_one(t_master *master)
{
	t_command	*cmd;

	cmd = master->commands_list;
	close(master->fd[READ]);
	handle_outputs(cmd);
	if (cmd->inv_file)
	{
		close(master->fd[WRITE]);
		printf("minishell: %s: No such file or directory\n", last_token(cmd->inputs)->str);
		return ;
	}
	exec(master, cmd);
	return ;
}

void	exec_one(t_master *master, t_command *cmd)
{
	char	**path;
	char	*command;
	char	**env;
	int		pid;

	pid = fork();
	//protect
	if (pid == 0)
	{
		redir_inputs(cmd);
		redir_outputs(cmd, master);
		path = find_path(master);
		command = get_command(path, cmd->args_char[0]);
		env = env_to_array(master->env);
		execve(command, cmd->args_char, env);
		exit(1);// Adjust
	}
	waitpid(pid, NULL, 0);
}
