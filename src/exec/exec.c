/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:18:50 by mrollo            #+#    #+#             */
/*   Updated: 2022/11/08 12:18:58 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// int exec(char *command, t_master *master)
// {
//     if (ft_strcmp(command, "echo") == 0)
//         printf("echo\n");
//     if (ft_strcmp(command, "cd") == 0)
//         printf("cd\n");
//     if (ft_strcmp(command, "pwd") == 0)
//         printf("pwd\n");
//     if (ft_strcmp(command, "export") == 0)
//         printf("export\n");
//     if (ft_strcmp(command, "unset") == 0)
//         printf("unset\n");
//     if (ft_strcmp(command, "env") == 0)
//         printf("env\n");
//     if (ft_strcmp(command, "exit") == 0)
//         printf("exit\n");
//     else
//         exec_bin(command, master);
//     return (0);
// }

// int exec_bin(char *command, t_master *master)
// {
//     char    *path;
//     int len;
//     t_env *tmp;

//     tmp = master->env;
//     while (tmp != NULL)
//     {
//         if (ft_strcmp(tmp->title, "PATH") == 0)
//         {
//             path = ft_strdup(tmp->value);
//             printf("path: %s\n", path);
//             break;
//         }
//         tmp = tmp->next;
//     }
//     return (0);
// }

char    **find_path(t_master *master)
{
    char **path;
    t_env *tmp;
    //int i;

    path = NULL;
    tmp = master->env;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->title, "PATH") == 0)
        {
            path = ft_split(tmp->value, ':');
            break;
        }
        tmp = tmp->next;
    }
    //imprimir path
    // i = 0;
    // while (path[i])
    // {
    //     printf("path[%d]: %s\n", i, path[i]);
    //     i++;
    // }
    return (path);
}

char    *get_command(char **path, char *cmd)
{
    int i;
    char    *aux;
    char    *path_cmd;

    i = 0;
    while (path[i])
    {
        aux = ft_strjoin(path[i], "/");
        path_cmd = join_free(aux, cmd);
        //printf("probando: %s\n", path_cmd);
        if (access(path_cmd, 0) == 0)
            return (path_cmd);
        i++;
    }
    return (NULL);
}

char    **token_to_array(t_token *token)
{
    char    **token_array;
    t_token *aux;
    int len;
    int i;

    aux = token;
    len = 0;
    while (aux != NULL)
    {
        len++;
        aux = aux->next;
    }
    //len = env_len(env);
    token_array = (char **)ft_calloc((len + 1), sizeof(char *));
    if (!token_array)
        return (NULL);
    i = 0;
    while (i < len)
    {
        token_array[i] = ft_strdup(token->str);
        token = token->next;
        i++;
    }
    //print_array(array_env, len);
    return (token_array);
}