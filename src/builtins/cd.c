/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:59:56 by mrollo            #+#    #+#             */
/*   Updated: 2023/02/01 15:11:25 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	change_dir(char *arg, char *oldpwd, t_env *env, t_master *master)
{
	if (chdir(arg) == 0)
	{
		update_env(oldpwd, env, master);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		if (access(arg, F_OK) == -1)
			ft_putendl_fd("No such file or directory", 2);
		else if (access(arg, R_OK) == -1)
			ft_putendl_fd("Permission denied", 2);
		else
			ft_putendl_fd("Not a directory", 2);
		return (1);
	}
}

void	update_env_var(t_env *env, char *title, char *value, t_master *master)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->title, title) == 0)
		{
			free (env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				clean_free(master, 1);
			return ;
		}
		env = env->next;
	}
}

void	update_oldpwd(char *oldpwd, t_env *env, t_master *master)
{
	t_env	*aux;
	char	*value;

	aux = env;
	if (find_in_env(aux, "PWD"))
	{
		value = get_env_value("PWD", env);
		if (find_in_env(aux, "OLDPWD"))
			update_env_var(env, "OLDPWD", value, master);
		else
			add_to_env(ft_strdup("OLDPWD"), ft_strdup(value), master);
	}
	else
		add_to_env(ft_strdup("OLDPWD"), ft_strdup(oldpwd), master);
	// while (env != NULL)
	// {
	// 	if (ft_strcmp("OLDPWD", env->title) == 0)
	// 	{
	// 		free (env->value);
	// 		if (find_in_env(aux, "PWD"))
	// 			env->value = ft_strdup(get_env_value("PWD", aux));
	// 		else
	// 			env->value = ft_strdup(oldpwd);
	// 		return ;
	// 	}
	// 	env = env->next;
	// }
	// add_to_env(ft_strdup("OLDPWD"), ft_strdup(oldpwd), aux);
	// aux = env;
	// while (env != NULL)
	// {
	// 	if (ft_strcmp("OLDPWD", env->title) == 0)
	// 	{
	// 		free (env->value);
	// 		env->value = ft_strdup(oldpwd);
	// 		return ;
	// 	}
	// 	else
	// 		env = env->next;
	// }
	// add_to_env(ft_strdup("OLDPWD"), ft_strdup(oldpwd), aux);
}

int	update_pwd(t_env *env, t_master *master)
{
	char	*pwd;

	pwd = malloc(4097 * sizeof(char));
	if (!pwd)
		clean_free(master, 1);
	if (getcwd(pwd, 4097) == NULL)
	{
		free (pwd);
		clean_free(master, 1);
	}
	while (env != NULL)
	{
		if (ft_strcmp("PWD", env->title) == 0)
		{
			free (env->value);
			env->value = ft_strdup(pwd);
			if (!env->value)
			{
				free (pwd);
				clean_free(master, 1);
			}
			break ;
		}
		else
			env = env->next;
	}
	free (pwd);
	return (0);
}

void	update_env(char *oldpwd, t_env *env, t_master *master)
{
	update_oldpwd(oldpwd, env, master);
	update_pwd(env, master);
}

char	*get_env_value(char *title, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(title, env->title) == 0)
			return (env->value);
		else
			env = env->next;
	}
	return (NULL);
}

int	ft_cd(t_env *env, char **args, t_master *master)
{
	char	*home_path;
	char	*pwd;
	int		i;

	home_path = get_env_value("HOME", env);
	pwd = malloc(4097 * sizeof(char));
	if (!pwd)
	{
		clean_free(master, 1);
		return (1);
	}
	if (getcwd(pwd, 4097) == NULL)
		return (1);
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0
		|| ft_strcmp(args[1], "--") == 0)
		i = change_dir(home_path, pwd, env, master);
	else if (strcmp(args[1], "-") == 0)
	{
		if (!change_dir(home_path, pwd, env, master))
		{
			ft_putendl_fd(home_path, 1);
			i = 0;
		}
		else
			i = 1;
	}
	else
		i = change_dir(args[1], pwd, env, master);
	free (pwd);
	return (i);
}
