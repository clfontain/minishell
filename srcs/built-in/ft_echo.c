/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:23:14 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/14 00:50:37 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	options_n(char *p)
{
	char	*ptr;

	ptr = p;
	while (*ptr == 'n' && *ptr)
		++ptr;
	if (*ptr == 0)
		return (1);
	else
		return (0);
}

int	ft_echo(t_minishell *minishell, int argc, char **argv)
{
	int		option_n;
	int		i;

	(void)minishell;
	option_n = 0;
	i = 1;
	while (--argc > 0 && argv[i][0] == '-')
	{
		if (options_n(argv[1] + 1))
			option_n = i++;
		else if (argc == 1)
			ft_printf("%s", argv[i++]);
		else
			ft_printf("%s ", argv[i++]);
	}
	while (argv[i] && argc-- > 0)
	{
		if (argc > 0)
			ft_printf("%s ", argv[i++]);
		else
			ft_printf("%s", argv[i++]);
	}
	if (!option_n)
		ft_printf("\n");
	return (SUCCESS);
}
