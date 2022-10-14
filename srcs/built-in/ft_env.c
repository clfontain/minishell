/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:00:00 by tnoulens          #+#    #+#             */
/*   Updated: 2022/09/28 21:35:59 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *minishell, int argc, char **argv)
{
	int	i;

	(void)argc;
	(void)argv;
	if (!minishell->env_array || !*minishell->env_array)
		return (perror("env: no env array"), errno);
	i = 0;
	while (minishell->env_array[i])
	{
		ft_putendl_fd(minishell->env_array[i], STDOUT_FILENO);
		++i;
	}
	return (0);
}
