#include "minishell.h"

void    free_array(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        free (array[i]);
        i++;
    }
    free(array);
}

void    print_array(char **array, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        printf("%s\n", array[i]);
        i++;
    }
}

int env_len(t_env *env)
{
    t_env   *tmp;
    int i;

    i = 0;
    tmp = env;
    while (tmp != NULL)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

char    **env_to_array(t_env *env)
{
    char    **array_env;
    char    *str;
    int i;
    int len;

    len = env_len(env);
    array_env = (char **)ft_calloc((len + 1), sizeof(char *));
    if (!array_env)
        return (NULL);
    i = 0;
    while (i < len)
    {
        if (env->value)
        {
            str = ft_strdup(env->title);
            str = join_free(str, "=");
            str = join_free(str, env->value);
        }
        else
            str = ft_strdup(env->title);
        array_env[i] = str;
        if (!array_env[i])
        {
            free_double_array(array_env);
			return (NULL);
        }
        i++;
        env = env->next;
    }
    return (array_env);
}