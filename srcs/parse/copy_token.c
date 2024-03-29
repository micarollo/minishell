/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:24:25 by arebelo           #+#    #+#             */
/*   Updated: 2023/02/09 16:11:12 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "free.h"

/**
 * Creates a deep copy of a given token
 * Returns the pointer to the created token
*/
static t_token	*copy_token(t_token *src, t_master *master)
{
	t_token	*res;

	res = ft_calloc(1, sizeof(t_token));
	if (!res)
		clean_free(master, 1);
	res->str = ft_strdup(src->str);
	if (!res->str)
	{
		free(res);
		clean_free(master, 1);
	}
	res->here = src->here;
	res->type = src->type;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

/**
 * Adds the token to the end of **list
*/
void	add_to_command(t_token *member, t_token **list, t_master *master)
{
	t_token	*end;

	end = last_token(*list);
	if (end)
		end->next = copy_token(member, master);
	else
		*list = copy_token(member, master);
}
