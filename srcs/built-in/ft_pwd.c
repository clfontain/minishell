/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:47:10 by tnoulens          #+#    #+#             */
/*   Updated: 2022/09/28 21:36:32 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *minishell, int argc, char **argv)
{
	char	wd[PATH_MAX];

	(void)minishell;
	(void)argc;
	(void)argv;
	if (getcwd(wd, PATH_MAX))
	{
		ft_putendl_fd(wd, STDIN_FILENO);
		return (SUCCESS);
	}
	else
		return (perror("pwd"), errno);
}
