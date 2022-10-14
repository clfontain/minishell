/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:34:55 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/11 19:48:51 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome_msg(char **envp)
{
	char	*user;

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
