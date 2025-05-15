/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:00:08 by francema          #+#    #+#             */
/*   Updated: 2025/05/07 17:07:49 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Verifica gli argomenti del comando exit
- Nessun argomento: exit 0
- Uno: se numerico lo usa come codice di uscita
- Due o piu': stampa errore 'too many arguments' e non esce
- Se il secondo argomento non e' numerico segnala eroore*/
int	ft_exit_args_check(char **args)
{
	int	i = 0;
	int	arg_count = ft_matlen((void **)args);

	if (arg_count > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (arg_count == 2)
	{
		if (args[1][0] == '-' || args[1][0] == '+')
			i++;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				return (2);
			i++;
		}
	}
	return (0);
}

/* Converte una stringa in long controllando l'overflow/underflow*/
int	ft_atol_check(const char *str, long *out)
{
	int		sign = 1;
	long	res = 0;
	int		i = 0;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
			
		int digit = str[i] - '0';
		if (res > (LONG_MAX - digit) / 10)
			return (0);
		res = res * 10 + digit;
		i++;
	}
	*out = res * sign;
	return (1);
}

/* Gestisce uscita con argomento non numerico*/
void	ft_non_digit_exit(char *arg)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

/* Funzione pricipale che implementa il comando exit
- Nessun argomento: exit 0
- Uno: esce con quel valore (convertito in int tra 0-255)
- Più di uno: errore e non esce
- Argomento non numerico: exit 255*/
void	ft_exit(t_mini *shell, char **args)
{
	int		ret_err;
	long	exit_val;
	int		valid;

	(void)shell;
	ret_err = ft_exit_args_check(args);
	if (ret_err == 1)
		return ;
	else if (ret_err == 2)
		ft_non_digit_exit(args[1]);

	if (ft_matlen((void **)args) == 2)
	{
		valid = ft_atol_check(args[1], &exit_val);
		if (!valid)
			ft_non_digit_exit(args[1]);

		exit_val %= 256;
		if (exit_val < 0)
			exit_val += 256;
	}
	else
		exit_val = 0;
	exit((int)exit_val);
}
