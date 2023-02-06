/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/02 10:25:22 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environment)
{
	t_master	*master;

	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));
		if (!master)
			return (1);
		begin_env(environment, master);
		init_redirs(master);
		while (!master->status)
			readline_loop(master);
		close_init_redirs(master);
		free_master(master);
	}
	return (g_error);
}

void	readline_loop(t_master *master)
{
	init_signal(1);
	master->line = readline(YELLOW"minishell: "RESET);
	master->status = isatty_check(master);
	if (master->status)
		return ;
	if (master->line == 0)
	{
		printf("exit\n");
		free_master(master);
		exit (0);
	}
	if (*master->line != '\0')
	{
		add_history(master->line);
		minishell(master);
	}
	else
		free_line(master);
}

/**
 * If line is empty and original STDIN is not a terminal (e.g. is a file) 
 * changes master->status to 1 to end minishell loop and finish parent process
*/
_Bool	isatty_check(t_master *master)
{
	if (isatty(STDIN_FILENO) == 0 && !master->line)
		return (1);
	return (0);
}
