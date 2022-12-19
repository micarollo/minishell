/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebelo <arebelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:18:50 by mrollo            #+#    #+#             */
/*   Updated: 2022/11/30 17:47:46 by arebelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Toma la variable $PATH y la separa (con split)

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
			if(!path)	//@arebelo confirmar con mica
				clean_free(master);
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


//Prueba en cada direccion de path si encuentra el comando necesario
//y lo devuelve en formato "/bin/ls"

char    *get_command(char **path, char *cmd, t_master *master)
{
    int 	i;
    char    *aux;
    char    *path_cmd;

    i = 0;
    while (path[i])
    {
        aux = ft_strjoin(path[i], "/");
		if(!aux)
			clean_free(master);
        path_cmd = join_free(aux, cmd);
		if(!path_cmd)
		{
			free(aux);
			clean_free(master);
		}
        if (access(path_cmd, 0) == 0)
            return (path_cmd);
        i++;
    }
    return (NULL);
}

//ejecuta los comandos en un child process

void exec_bin(t_master *master, t_command *cmd)
{
    char    **path;
    char    *command;
    char    **env;

	path = find_path(master);
	command = get_command(path, cmd->args_char[0], master);
	env = env_to_array(master->env);

	execve(command, cmd->args_char, env);	
	exit(1);// Adjust
}

void    exec_builtin(char *command, t_command *cmd, t_env *env)
{
    if (strcmp(command, "echo") == 0)
        ft_echo(cmd->args_char);
    else if (ft_strcmp(command, "cd") == 0)
		ft_cd(env, cmd->args_char);
    else if (ft_strcmp(command, "pwd") == 0)
		ft_pwd(env);
    else if (ft_strcmp(command, "export") == 0)
		return ;
	else if (ft_strcmp(command, "unset") == 0)
		return ;
    else if (ft_strcmp(command, "env") == 0)
        return ;
    else if (ft_strcmp(command, "exit") == 0)
        return ;
}

int is_builtin(char *command)
{
    if (strcmp(command, "echo") == 0)
        return (1);
    if (ft_strcmp(command, "pwd") == 0)
		return (1);
    if (ft_strcmp(command, "cd") == 0)
		return (1);
	if(1)
		return (0);
    if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
    if (ft_strcmp(command, "env") == 0)
        return (1);
    if (ft_strcmp(command, "exit") == 0)
        return (1);
    else
        return (0);
}

int exec(t_master *master, t_command *cmd)
{
    if (master->numCommands == 1)
        exec_one(master, cmd);
	else if (is_builtin(cmd->args_char[0]))
        exec_builtin(cmd->args_char[0], cmd, master->env);
    else
        exec_bin(master, cmd);
    return (0);
}