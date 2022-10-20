/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/19 16:41:39 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int main(int argc, char **argv, char **enviroment)
{
    t_master *master;
	char **array;

	if (argc >= 1 && argv)
	{
		master = ft_calloc(1, sizeof(t_master));
		init_env(master, enviroment);
		print_env(master->env);
		array = env_to_array(master->env);
		free_array(array);
		free_env_lst(master->env);
		free (master);
	}
}
