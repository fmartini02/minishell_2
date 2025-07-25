/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:00:08 by francema          #+#    #+#             */
/*   Updated: 2025/07/15 14:01:18 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_there_letters(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_isalpha(s[i]))
		i++;
	if (s[i] && ft_isalpha(s[i]))
		return (true);
	return (false);
}

/* Verifica gli argomenti del comando exit
- Nessun argomento: exit 0
- Uno: se numerico lo usa come codice di uscita
- Due o piu': stampa errore 'too many arguments' e non esce
- Se il secondo argomento non e' numerico segnala eroore*/
static int	ft_exit_args_check(char **args)
{
	int	i;
	int	arg_count;

	i = 0;
	arg_count = ft_matlen((void **)args);
	if (arg_count > 2)
	{
		if (is_there_letters(args[1]))
			return (2);
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
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
static int	ft_atol_check(const char *str, long *out)
{
	int		sign;
	long	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i])
			|| (sign > 0 && res > (LONG_MAX - (str[i] - '0')) / 10)
			|| (sign < 0 && - res < (LONG_MIN + (str[i] - '0')) / 10))
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	*out = res * sign;
	return (1);
}

/* Gestisce uscita con argomento non numerico*/
static void	ft_non_digit_exit(char *arg, t_mini *shell, t_pipinfo *info)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_info(info);
	cleanup_shell(shell, 2);
}

/* Funzione pricipale che implementa il comando exit
- Nessun argomento: exit 0
- Uno: esce con quel valore (convertito in int tra 0-255)
- Più di uno: errore e non esce
- Argomento non numerico: exit 255*/
void	ft_exit(t_mini *shell, char **args, t_pipinfo *info)
{
	int		ret_err;
	long	exit_val;
	int		valid;

	ret_err = ft_exit_args_check(args);
	if (ret_err == 1)
		return (free_info(info), cleanup_shell(shell, -1));
	else if (ret_err == 2)
		ft_non_digit_exit(args[1], shell, info);
	if (ft_matlen((void **)args) == 2)
	{
		valid = ft_atol_check(args[1], &exit_val);
		if (!valid)
			ft_non_digit_exit(args[1], shell, info);
		exit_val %= 256;
		if (exit_val < 0)
			exit_val += 256;
	}
	else
		exit_val = 0;
	ft_putstr_fd("exit\n", 1);
	free_info(info);
	cleanup_shell(shell, (int)exit_val);
}
