/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:50:53 by mrollo            #+#    #+#             */
/*   Updated: 2022/10/15 14:20:31 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <../libft/libft.h>

typedef struct s_env
{
	char *content;
	char *title;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct  s_token
{
    char            *str;
    int             type; 
    _Bool			env_update;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

typedef struct s_master
{
    t_env *env;
    t_token *token_list;
}   t_master;

//ENVIROMENT
int		init_env(t_master *master, char **enviroment);
t_env	*new_env(char *content, char *title, char *value);
char    *get_title(char *str);
char    *get_value(char *str);
void	add_back(t_env *env, t_env *new);
t_env	*last_env(t_env *env);
void	print_env(t_env *env);
void    free_env(t_env *item);
void    free_env_lst(t_env *list);
char    **env_to_array(t_env *env);
int 	env_len(t_env *env);
void    free_array(char **array);
void	sort(char **sort_array, int len);
char    **sort_env_array(char **sort_array, t_env *env, int len);
void    print_sort_env(t_env *env);


//Parsing
void	parsing(char * line, t_master *master);
int		tokenize(char *line, t_master *master);
t_token *new_token(char *line, int size, t_master *master);
void	env_update(t_token *new, t_master *master);
char	*find_var(char *str, t_master *master, int pos, char *full_line);
_Bool	check_quotes(char *line);
char	*quotes_clean(t_token *new);
void	quotes_update(t_token *new);
void    add_list(t_master *list, t_token *item);
t_token *last_token(t_token *token);
t_token *first_token(t_token *token);
void    free_token(t_token *item);
void    free_list(t_token *list);
void	clean_tokens(t_master *master);
void    delete_token(t_token *token, t_master *master);


//Aux to delete before submitting
void    print_list_tokens(t_token *list);
size_t	ft_strlcat1(char *dst, const char *src, size_t dstsize);


//Utils
char			*join_free(char *s1, char *s2);
unsigned int	find_max_len(char *s1, char *s2);
#endif
