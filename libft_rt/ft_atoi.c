/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:42:01 by jwoo              #+#    #+#             */
/*   Updated: 2020/12/30 20:37:44 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	atoi_sign(const char *str)
{
	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		if (*str == '-')
			return (-1);
	return (1);
}

static int	atoi_len(const char *str)
{
	int	len;

	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	len = 0;
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
		{
			len++;
			if (len == 20)
				break ;
		}
		else
			break ;
		str++;
	}
	return (len);
}

static int	last_num(const char *str)
{
	int			len;
	long long	num;
	int			last;

	len = 0;
	num = 0;
	last = -1;
	while (len < 18)
	{
		if ('0' <= *str && *str <= '9')
		{
			num = num * 10 + (*str - '0');
			len++;
		}
		str++;
	}
	last = *str - '0';
	if (num < 922337203685477580)
		return (-1);
	else if (num > 922337203685477580)
		return (10);
	else
		return (last);
}

static int	atoi_flow(const char *str)
{
	int	sign_len;

	sign_len = atoi_sign(str) * atoi_len(str);
	if (sign_len == 20)
		return (-1);
	else if (sign_len == -20)
		return (0);
	else if (sign_len == 19 && last_num(str) > 7)
		return (-1);
	else if (sign_len == -19 && last_num(str) > 8)
		return (0);
	else
		return (1);
}

int			ft_atoi(const char *str)
{
	int	num;
	int	sign;

	sign = atoi_sign(str);
	if (atoi_flow(str) != 1)
		return (atoi_flow(str));
	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	num = 0;
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			break ;
		str++;
	}
	return (sign * num);
}
