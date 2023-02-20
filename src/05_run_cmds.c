/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isojo-go <isojo-go@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:32:55 by isojo-go          #+#    #+#             */
/*   Updated: 2023/02/20 09:58:23 by isojo-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_path(char *cmd, t_data *data)
{
	int		i;
	char	**path_tab;
	char	*path;
	char	*aux;

	i = 0;
	path_tab = ft_split(ft_get_var(data, "PATH"), ':');
	i = 0;
	while (*(path_tab + i))
	{
		aux = ft_strjoin(*(path_tab + i), "/");
		path = ft_strjoin(aux, cmd);
		free (aux);
		free (*(path_tab + i++));
		if (access(path, F_OK) == 0)
			break ;
	}
	while (*(path_tab + i))
		free (*(path_tab + i++));
	free (path_tab);
	return (path);
}

char	**ft_get_args(char *arg)
{
	char	**cmd;
	int		i;
	int		j;
	char	*mod;

	mod = (char *)malloc(ft_strlen(arg) + 1);
	if (mod == NULL)
		return NULL;
	i = 0;
	j = 0;
	while (*(arg + i))
	{
		if (ft_ischarset(*(arg + i), "\"\'") && !ft_inquotes(arg, i))
			i++;
		if (*(arg + i) == ' ' && !ft_inquotes(arg, i))
			*(mod + j) = '+';
		else
			*(mod + j) = *(arg + i);
		i++;
		j++;
	}
	*(mod + j) = '\0';
	cmd = ft_split(mod, '+');
	free(mod);
	return (cmd);
}

static void	ft_run_command(char *arg, t_data *data, char **envp)
{
	char	**cmd;
	char	*cmd_path;
	int		i;
	int		error_flag;

	error_flag = 0;
	cmd = ft_get_args(arg);
	if (*(*(cmd + 0)) == '/' || *(*(cmd + 0)) == '.')
		cmd_path = *(cmd + 0);
	else
		cmd_path = ft_get_path(*(cmd + 0), data);
	if (DEBUG == 1)
		ft_check_cmd(cmd_path, cmd);
	if (execve(cmd_path, cmd, envp) == -1)
		error_flag = 1;
	i = 0;
	while (*(cmd + i))
		free (*(cmd + i++));
	free (cmd);
	free (cmd_path);
	if (error_flag == 1)
		ft_exit_w_error("Command not found\n");
}

char	*ft_lst_to_str(t_vars *tmp)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(ft_strlen(tmp->name) + ft_strlen(tmp->val) + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (*(tmp->name + j))
		*(str + i++) = *(tmp->name + j++);
	*(str + i++) = '=';
	j = 0;
	while (*(tmp->val + j))
		*(str + i++) = *(tmp->val + j++);
	*(str + i++) = '\0';
	return (str);
}

char	**ft_gen_envp(t_data *data)
{
	t_vars	*tmp;
	int		i;
	int		len;
	char	**custom_envp;

	len = ft_vars_size(data);
	custom_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (custom_envp == NULL)
		return (NULL);
	i = 0;
	tmp = data->vars;
	while (tmp)
	{
		if (tmp->is_exp == 1)
			*(custom_envp + i) = ft_lst_to_str(tmp);
		i++;
		tmp = tmp ->next;
	}
	*(custom_envp + i) = NULL;
	return (custom_envp);
}

int	ft_launch_piped_process(char *str, t_data *data, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	(void)envp;
	if (pipe(fd) == -1)
		ft_exit_w_error("errno");
	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		close(*(fd + 1));
		dup2(*(fd + 0), STDIN_FILENO);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		close(*(fd + 0));
		dup2(*(fd + 1), STDOUT_FILENO);
		if (data->custom_envp != NULL)
			ft_free_custom_envp(data);
		data->custom_envp = ft_gen_envp(data);
		ft_run_command(str, data, data->custom_envp);
		return (EXIT_FAILURE);
	}
}

int	ft_launch_process(char *str, int outfd, t_data *data, char **envp)
{
	pid_t	pid;
	int		status;

	(void)envp;
	pid = fork();
	if (pid == -1)
		ft_exit_w_error("errno");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (outfd != STDOUT_FILENO)
			close(outfd);
		return (WEXITSTATUS(status));
	}
	else
	{
		if (outfd != STDOUT_FILENO)
			dup2(outfd, STDOUT_FILENO);
		if (data->custom_envp != NULL)
			ft_free_custom_envp(data);
		data->custom_envp = ft_gen_envp(data);


		// //DEBUG
		// 	int	i;
		// 	i = 0;
		// 	printf("SYSTEM ENVP:\n");
		// 	while (*(envp + i))
		// 		printf("    %s\n", *(envp + i++));
		// 	printf("\n    -------------\n\n");
		// 	i = 0;
		// 	printf("CUSTOM ENVP:\n");
		// 	while (*(data->custom_envp + i))
		// 		printf("    %s\n", *(data->custom_envp + i++));
		// //____


		ft_run_command(str, data, data->custom_envp);
		return (EXIT_FAILURE);
	}
}
