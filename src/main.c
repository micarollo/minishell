/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:13:55 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/17 12:31:27 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int main(int argc, char **argv, char **enviroment)
{
    t_master *master;

	if (argc >= 1 && argv)
	{
		master = malloc(sizeof(t_master));
		init_env(master, enviroment);
		//print_env(master->env);
		printf("len list: [%d]\n", len_lst(master->env));
		lst_to_array(master);
		//free_lst(master->env);
	}
}
