/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:42:15 by waxxy             #+#    #+#             */
/*   Updated: 2022/10/11 18:10:42 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exportlist(t_list *list)
{
	if (list)
	{
		while (list != NULL)
		{
			if (list->content != NULL)
			{
				ft_printf("declare -x ");
				ft_printf("%s\n", list->content);
			}
			list = list->next;
		}
	}
}

int	str_is_alnum(char *p)
{
	char	*ptr;

	ptr = p;
	if (!ft_isalpha(*ptr))
	{
		if (*ptr != '_')
			return (1);
	}
	ptr++;
	while (*ptr && *ptr != '=')
	{
		if (ft_isalnum(*ptr) || *ptr == '_')
			ptr++;
		else
			return (1);
	}
	return (0);
}

int	formatok(char *str)
{
	char	*p;

	p = ft_strchr(str, '=');
	if (p == NULL && !str_is_alnum(str))
		return (0);
	if (str_is_alnum(str) || *p == *str)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": no export done, not a valid identifier\n", 2);
		return (1);
	}
	else
		return (0);
}

int	is_in_env(t_list *lst, char *str)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_cmpchr(str, tmp->content, '='))
		{
			free(tmp->content);
			tmp->content = ft_strdup(str);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_minishell *minishell, int argc, char **argv)
{
	int	i;

	if (argc == 1)
		exportlist(minishell->env);
	else
	{
		i = 1;
		while (i < argc)
		{
			if (!formatok(argv[i]) && !is_in_env(minishell->env, argv[i]))
			{
				ft_lstadd_back(&minishell->env,
					ft_lstnew(ft_strdup(argv[i]), NULL));
				if (!ft_lstlast(minishell->env)
					|| !ft_lstlast(minishell->env)->content)
					return (perror("ft_export"), errno);
			}
			++i;
		}
		bubblesortlist(minishell->env);
		list_to_export(minishell);
	}
	return (SUCCESS);
}
