/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:05:45 by arebelo           #+#    #+#             */
/*   Updated: 2022/11/29 14:13:51 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Checks if it is alphanumeric or $
*/
_Bool	ok(char c)
{
	if (!ft_isalnum(c) && c != '$')
		return (0);
	return (1);
}

/**
 * Determines if $VAR is allowed to be substituted (if between simple quotes it shouldn't); 
 * If it is (allow_update == 1) and searches for variables named *str on the environment and returns its value; returns NULL if it does not find a match
 * returns $VAR if the substitution is not allowed
*/
char	*find_var(char *str, t_master *master, int pos, char *full_line)
{
	int		i;
	int		j;
	_Bool	allow_update;

	allow_update = 1;
	i = 0;
	j = -1;
	while (i < pos)
	{
		if (j < 0 && (full_line[i] == '\'' || full_line[i] == '\"' ))
		{
			j = i;
			if (full_line[i] == '\'')
				allow_update = 0;
		}
		else if (j >= 0 && full_line[i] == full_line[j])
		{
			j = -1;
			allow_update = 1;
		}	
		i++;
	}
	if (allow_update)
		return (find_aux(str, master));
	return (find_aux2(str, master));
}

char	*find_aux(char *str, t_master *master)
{
	t_env	*temp;
	char	*a;

	temp = master->env;
	while (temp && str)
	{
		if (ft_strcmp(str, temp->title) == 0)
		{
			free(str);
			a = ft_strdup(temp->value);
			if (!a)
				clean_free_pipe_read(master);
			return (a);
		}
		temp = temp->next;
	}
	free(str);
	return (NULL);
}

char	*find_aux2(char *str, t_master *master)
{
	str = join_free_s2("$", str);
	if (!str)
		clean_free_pipe_read(master);
	return (str);
}