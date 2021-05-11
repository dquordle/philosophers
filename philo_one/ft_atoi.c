/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:17:22 by dquordle          #+#    #+#             */
/*   Updated: 2021/03/30 13:12:54 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	z;
	int	a;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	z = 0;
	if (str[i] == '-' || str[i] == '+')
		z = '+' - str[i++];
	a = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		a *= 10;
		a += str[i++] - 48;
	}
	if (a == -2147483648)
		return (a);
	if (z)
		return (a * (-1));
	return (a);
}
