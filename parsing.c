/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:02:07 by francema          #+#    #+#             */
/*   Updated: 2025/05/08 15:05:42 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quotes_case(t_mini *shell, size_t *i)
{
	(void)shell;
	(void)i;
	printf("Single quotes case \n");
}

void	duble_quotes_case(t_mini *shell, size_t *i)
{
	(void)shell;
	(void)i;
	printf("Double quotes case \n");
}

void	redi_case(t_mini *shell, size_t *i)
{
	(void)shell;
	(void)i;
	printf("Redi case \n");
}

void	pipe_char_case(t_mini *shell, size_t *i)
{
	(void)shell;
	(void)i;
	printf("Pipe char case \n");
}

void	ampersand_case(t_mini *shell, size_t *i)
{
	(void)shell;
	(void)i;
	printf("Ampersand case \n");
}

void	parentesis_case(t_mini *shell, size_t *i)
{
	(void)shell;
	(void)i;
	printf("Parentesis case \n");
}

void	wildcard_case(t_mini *shell, size_t *i)
{
	(void)shell;
	(void)i;
	printf("Wildcard case \n");
}
