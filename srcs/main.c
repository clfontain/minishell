/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:33:49 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/12 16:43:03 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_tab(char **str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			i++;
		}
	}
	return (i);
}

void	ft_printab(char **str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			ft_printf("%s\n", str[i]);
			i++;
		}
	}
}

int	space_only(char *p)
{
	char	*char_ptr;

	char_ptr = p;
	if (char_ptr != NULL)
	{
		while (*char_ptr)
		{
			if (ft_isspace(*char_ptr))
				char_ptr++;
			else
				return (0);
		}
		return (1);
	}
	else
		return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*p;
	t_minishell	minishell;

	init_minishell(&minishell, argc, envp);
	build_env(&minishell, envp);
	signal_handling();
	if (argc > 1)
		cmd_argv(argv + 1, &minishell);
	while (mini_init(&minishell), 42)
	{
		p = prompt_line(&minishell);
		if (space_only(p))
		{
			minishell.sigint = FALSE;
			continue ;
		}
		if (lexer_and_expend(p, &minishell) == 1)
			return (perror("main: lexer:"), error_clean_up(&minishell), 1);
		minishell.parse_status = parse(&minishell);
		if (minishell.parse_status != 1)
			minishell.exec_ret = pipex(&minishell);
		clean_iteration(&minishell);
	}
	return (0);
}
