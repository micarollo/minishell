#include "../../include/minishell.h"

void    print_export_error(char *str)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(str, 2);
    ft_putendl_fd("': not a valid identifier", 2);
}

void    add_to_env(char *content, char *title, char *value, t_env *env)
{
    t_env   *new;

    new = new_env(content, title, value);
    add_back(env, new);
}

void    update_var(t_env *env, char *str, t_master *master)
{
    char    *end;
    size_t  n;

    end = ft_strchr(str, '=');
    if (!end)
        n = ft_strlen(str);
    else
        n = end - str;
    while (env != NULL)
    {
        if (ft_strncmp(env->title, str, n) == 0)
        {
            env->value = get_value(str, master);
            break ;
        }
        env = env->next;
    }
}

int var_exist(t_env *env, char *str)
{
    char    *end;
    size_t  n;

    end = ft_strchr(str, '=');
    if (!end)
        n = ft_strlen(str);
    else
        n = end - str;
    while (env != NULL)
    {
        if (ft_strncmp(env->title, str, n) == 0)
            return (1);
        env = env->next;
    }
    return (0);
}

int equal_check(char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    while (i < len)
    {
        if (str[i] == '=')
            i++;
        else
            return (0);
    }
    return (1);
}

int var_title_check(char *str)
{
    int i;
    int len;
    char    *aux;

    aux = ft_strchr(str, '=');
	if (!aux)
		len = ft_strlen(str);
	else
		len = aux - str;
    if (len == 0)
        return (0);
    if (equal_check(str))
        return (0);
    i = 0;
    while (i < len)
    {
        if (!ft_isalpha(str[i]) && str[i] != '_')
        {
            if ((i == (len - 1)) && str[i] == '+') //soluciona un error pero el nombre de la var no esta ok!
                return (1);
            return (0);
        }
        i++;
    }
    return (1);
}

int ft_export(t_env *env, char **args, t_master *master)
{
    int i;
    int ret;

    ret = 0;
    if (!args[1])
    {
        print_sort_env(env);
        return (0);
    }
    else
    {
        i = 1;
        while (args && args[i])
        {
            if(var_title_check(args[i]))
            {
                if (var_exist(env, args[i]))
                    update_var(env, args[i], master);
                else
                    add_to_env(args[i], get_title(args[i], master), get_value(args[i], master), env);
            }
            else
            {
                print_export_error(args[i]);
                ret = 1;
            }
            i++;
        }
    }
    return (ret);
}