/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:34:55 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/18 19:43:41 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome_msg(char **envp)
{
	char	*user;

	if (isatty(STDIN_FILENO))
	{
		ft_fprintf(2, YELLOW"\n🅼 🅸 🅽 🅸 🆂 🅷 🅴 🅻 ->"BLINK_YELLOW"🅻\n"WHITE);
		if (envp == NULL)
			ft_fprintf(2, "\nWelcome,"RED" no env detected at launch"END);
		else
		{
			user = getenv("USER");
			if (!user)
				ft_fprintf (2, "\nWelcome friend");
			else
				ft_fprintf (2, "\nWelcome %s", user);
		}
		ft_fprintf(2, "\n"END);
	}
}
