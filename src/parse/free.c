/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:55:49 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/29 15:53:21 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_free_pipe_read(t_master *master)
{
	close(master->fd[WRITE]);
	close_init_redirs(master);
	free_master(master);
	exit(1);
}

void    prep_next_line(t_master *master)
{
	close(master->fd[READ]);
	dup2(master->std_in, STDIN_FILENO);
    free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
	free_line(master);
}

void    free_master(t_master *master)
{
	free_line(master);
	free_env_lst(master->env);  //Suggestion: change arg to only master to avoid next line
	master->env = NULL;
	free_token_list(master->token_list);
	master->token_list = NULL;
	free_commands(master);
	if(master)
		free(master);
}

void	free_line(t_master *master)
{
	if(master->line)
		free(master->line);
	master->line = NULL;
}


/**
 * Frees the list of commands stored in t_master
*/
void	free_commands(t_master *master)
{
	t_command	*list;
	t_command	*temp;

	list = master->commands_list;
	while (list)
	{
		temp = list->next;
		free_command(list);
		free(list);
		list = temp;
	}
	master->commands_list = NULL;
}

/**
 * Frees each command
*/
void	free_command(t_command *command)
{
	free_token_list(command->args);
	free_token_list(command->inputs);
	free_token_list(command->outputs);
	free_double_array(command->args_char);
	command->args = NULL;
	command->inputs = NULL;
	command->outputs = NULL;
	command->args_char = NULL;
}