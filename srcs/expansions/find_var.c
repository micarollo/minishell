/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarebelo <anarebelo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:05:45 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 22:43:05 by anarebelo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "utils.h"
#include "free.h"

/**
 * Checks if it is alphanumeric or $
*/
_Bool	ok(char c)
{
	if (!ft_isalnum(c) && c != '$' && c != '?' && c != '_')
		return (0);
	return (1);
}

static char	*find_aux2(char *str, t_master *master)
{
	str = join_free_s2("$", str);
	if (!str)
		clean_free(master, 1);
	return (str);
}

static char	*find_aux(char *str, t_master *master)
{
	t_env	*temp;
	char	*test;

	temp = master->env;
	if (ft_strcmp(str, "?") == 0)
	{
		free(str);
		test = ft_itoa(g_glbl.g_error);
		if (!test)
			clean_free(master, 1);
		return (test);
	}
	while (temp && str)
	{
		if (ft_strcmp(str, temp->title) == 0)
			return (create_str(str, temp, master));
		temp = temp->next;
	}
	if (str)
		free(str);
	return (NULL);
}

/**
 * Determines if $VAR is allowed to be substituted
 * (if between simple quotes it shouldn't); 
 * If it is (allow_update == 1) and searches for variables named *str 
 * on the environment and returns its value;
 * returns NULL if it does not find a match
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

/**
 * Creates a malloc char* with value of matched env variable
*/
char	*create_str(char *str, t_env *temp, t_master *master)
{
	char	*a;

	if (str)
		free(str);
	if (!temp->value)
		a = ft_strdup("");
	else
		a = ft_strdup(temp->value);
	if (!a)
		clean_free(master, 1);
	a = do_non_print(a);
	return (a);
}
