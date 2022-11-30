/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:14:25 by cfontain          #+#    #+#             */
/*   Updated: 2022/10/19 19:18:48 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*gethome(t_minishell *ms)
{
	char	**p;
	int		i;

	p = ms->env_array;
	i = 0;
	if (p != NULL)
	{
		while (p[i] != NULL)
		{
			if (!ft_strncmp(p[i], "HOME=", 5))
				return (p[i] + 5);
			++i;
		}
	}
	return (NULL);
}

static char	**update_opwd(t_minishell *ms)
{
	char	**ptr;
	char	*p;
	char	wd[PATH_MAX];

	p = genv(ms, "OLDPWD");
	if (p)
	{
		ptr = (char **)ft_calloc(sizeof(char *), 3);
		if (!ptr)
			error_clean_up(ms);
		ptr[0] = NULL;
		if (!getcwd(wd, PATH_MAX))
			return (free(ptr), perror("cd: update opwd"), NULL);
		ptr[1] = ft_strjoin("OLDPWD=", wd);
		if (ptr[1] == NULL)
		{
			free(ptr);
			error_clean_up(ms);
		}
		return (ptr);
	}
	return (NULL);
}

static void	update_pwd(t_minishell *ms)
{
	char	**ptr;
	char	*p;
	char	wd[PATH_MAX];

	p = genv(ms, "PWD");
	if (p)
	{
		ptr = (char **)ft_calloc(sizeof(char *), 3);
		if (!ptr)
			error_clean_up(ms);
		ptr[0] = NULL;
		if (!getcwd(wd, PATH_MAX))
			return (free(ptr), perror("cd: update pwd"), (void)0);
		ptr[1] = ft_strjoin("PWD=", wd);
		if (ptr[1] == NULL)
		{
			free(ptr);
			error_clean_up(ms);
		}	
		ft_export(ms, 2, ptr);
		free(ptr[1]);
		free(ptr);
	}
}

static int	normadjust3(t_minishell *ms, char **ptr)
{
	char	*p;

	p = gethome(ms);
	if (p == NULL)
	{
		if (ptr)
			freer(ptr);
		return (ft_putendl_fd("HOME unset", 2), 1);
	}
	if (chdir(p) == -1)
	{
		if (ptr)
			freer(ptr);
		return (perror("cd gethome"), errno);
	}
	if (ptr)
	{
		ft_export(ms, 2, ptr);
		freer(ptr);
		update_pwd(ms);
	}
	return (0);
}

int	ft_cd(t_minishell *ms, int argc, char **argv)
{
	char	**ptr;
	int		i;

	i = 0;
	if (argc > 2)
		return (ft_putendl_fd("cd:wrong arguments", 2), 1);
	ptr = update_opwd(ms);
	if (argc == 1)
		i = normadjust3(ms, ptr);
	else if (chdir(argv[1]) == -1)
	{
		if (ptr)
			freer(ptr);
		return (perror(argv[1]), errno);
	}
	else
	{
		if (ptr)
		{
			ft_export(ms, 2, ptr);
			freer(ptr);
		}
	}
	update_pwd(ms);
	return (i);
}
