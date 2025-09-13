/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:40:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/02 14:06:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isspace(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	return (i);
}

static int	ft_checksign(char *str)
{
	unsigned int	i;
	int				sign;

	i = 0;
	sign = 1;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (i > 1)
		return (0);
	else
		return (sign);
}

static int	ov_underflow(int num, char c, int sign)
{
	if (sign > 0)
	{
		if (num > (INT_MAX - (c - 48)) / 10)
			return (0);
	}
	else
	{
		if (num > (INT_MIN + (c - 48)) / -10)
			return (0);
	}
	return (1);
}

/*The  atoi()  function  converts the
	initial  portion  of   the   string
	pointed to by nptr to int.  The be‐
	havior is the same as strtol (takes only one sign and checks
	for isspace)
	this atoi is checking for over and underflows, as well as for tthe
	presence of any nondigit c after the sign
	Returns converte value or 0 on error*/
int	ft_atoi(const char *nptr)
{
	int				num;
	char			*a_num;
	int				sign;

	num = 0;
	a_num = (char *)nptr;
	a_num += ft_isspace(a_num);
	sign = ft_checksign(a_num);
	if (!sign)
		return (0);
	if ((*a_num == '-' || *a_num == '+'))
		a_num++;
	while (*a_num >= '0' && *a_num <= '9')
	{
		if (!ov_underflow(num, *a_num, sign))
			return (0);
		num = (*a_num - 48) + num * 10;
		a_num++;
	}
	if (*a_num)
		return (0);
	return (num * sign);
}

int	ft_atoi_unsafe(const char *nptr)
{
	long	output;
	int		sign;

	output = 0;
	sign = 1;
	if (*nptr == 0)
		return (0);
	while (ft_isspace(nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-' && nptr++)
		sign *= -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		output *= 10;
		output += *nptr - '0';
		nptr++;
	}
	return ((int)(output * sign));
}
