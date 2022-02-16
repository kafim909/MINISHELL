/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:47:25 by mtournay          #+#    #+#             */
/*   Updated: 2022/02/16 16:34:00 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_minimize(char ***cmd)
{
	int	i;

	i = 0;
	while ((*cmd)[0][i])
	{
		ft_tolower((int)(*cmd)[0][i]);
		i++;
	}
}

int	get_cmd(char **envp, char ***dir, char **argvec)
{
	int	i;

	i = 0;
	while (envp)
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			break ;
		i++;;
	}
	*dir = ft_split(envp[i] + 5, ':');
	if (!*dir)
		return (0);
	while ((*dir)[i])
	{
		(*dir)[i] = cat_dup((*dir)[i], argvec[0]);
		if (!(*dir)[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_execute(char **cmd, char **envp)
{
	char	**dir;
	int		i;

	i = 0;
	if (!get_cmd(envp, &dir, cmd))
		return (0);
	while ((execve(dir[i], cmd, envp) == -1) && dir[i])
		i++;
	if (!dir[i])
	{
		write(1, cmd[0], ft_strlen(cmd[0]));
		write(1, " : command not found\n", 22);
	}
	return (1);
}

int	ft_bin(char ***env, char **cmd)
{
	ft_minimize(&cmd);
	if (!ncmp(cmd[0], "echo", 4))
		return (ft_echo(cmd, *env));
	if (!ncmp(cmd[0], "cd", 2))
		return (ft_cd(cmd));
	if (!ncmp(cmd[0], "pwd", 3))
		return (ft_pwd(cmd));
	if (!ncmp(cmd[0], "export", 6))
		return (ft_export(env, cmd));
	if (!ncmp(cmd[0], "unset", 5))
		return (ft_unset(env, cmd));
	if (!ncmp(cmd[0], "env", 3))
		return (ft_env(*env, cmd));
	if (!ncmp(cmd[0], "exit", 4))
		return (1);
	return (8);
}	

int bin_cmd(char ***env, char **cmd)
{
	int	ret;
	
	ret = ft_bin(env, cmd);
	if (!ret)
		return (0);
	if (ret == 8)
		return (ft_execute(cmd, *env));
	return (1); 
}