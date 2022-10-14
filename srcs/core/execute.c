/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:29:21 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/06 17:49:31 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_parser(char *env_var, t_minishell *ms)
{
	char	*p;
	char	*env_ptr;

	p = NULL;
	env_ptr = genv(ms, env_var);
	if (!env_ptr)
		return (NULL);
	p = ft_substr(env_ptr, 0, ft_strlen(env_ptr));
	if (!p)
		return (write(1, "malloc issue env_parser\n", 24), NULL);
	return (p);
}

static char	**paths_maker(t_minishell *ms)
{
	char	*path;
	char	**bin_path;
	char	*tmp;
	char	**tmp2;
	int		i;

	path = env_parser("PATH", ms);
	if (!path)
		bin_path = NULL;
	else
		bin_path = ft_split(path, ':');
	free(path);
	if (!bin_path)
		return (NULL);
	i = -1;
	while (bin_path[++i])
	{
		tmp = bin_path[i];
		tmp2 = bin_path;
		bin_path[i] = ft_strjoin(bin_path[i], "/");
		if (!bin_path[i])
			return (ft_free_split(tmp2), NULL);
		free(tmp);
	}
	return (bin_path);
}

char	*cmd_check(char **bin_path, char *cmd)
{
	char	*tmp;
	int		i;

	if (!bin_path || !*bin_path)
		return (NULL);
	i = -1;
	while (bin_path[++i])
	{
		tmp = ft_strjoin(bin_path[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)
			return (ft_free_split(bin_path), tmp);
		else
			free(tmp);
	}
	return (ft_free_split(bin_path), NULL);
}

int	is_built_in(t_minishell *ms, int argc, char **argv)
{
	int			i;
	t_builtin	built[7];

	i = 0;
	init_builtin(built);
	while (i < NBR_BI)
	{
		if (!ft_strncmp(argv[0], built[i].name, 10))
		{
			ms->exec_ret = built[i].func(ms, argc, argv);
			return (1);
		}
		i++;
	}
	return (0);
}

int	exec(t_minishell *ms, char **cmds, char **envp)
{
	char	*cmd_path;
	int		i;

	i = nb_cmd(cmds);
	if (i)
	{
		if (is_built_in(ms, i, cmds))
			return (ms->exec_ret);
		if (ft_memchr(cmds[0], '/', ft_strlen(cmds[0])) || !genv(ms, "PATH"))
		{
			if (access(cmds[0], F_OK | X_OK) == 0)
				cmd_path = cmds[0];
			else if (errno == 13)
				return (perror("access"), 126);
			else
				return (perror("access"), errno);
		}
		else
			cmd_path = cmd_check(paths_maker(ms), cmds[0]);
		if (!cmd_path || cmds[0][0] == '\0')
			return (ft_putstr_fd(cmds[0], 2), ft_putendl_fd(NOTFOUND, 2), 127);
		if (execve(cmd_path, cmds, envp) == -1)
			return (free(cmd_path), perror("exec"), errno);
	}
	return (0);
}
