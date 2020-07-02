/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:38:47 by yaye              #+#    #+#             */
/*   Updated: 2019/05/10 11:38:48 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long		ft_power(unsigned long x, int power)
{
	if (power > 0)
	{
		if (x >= 9223372036854775807 / ft_power(x, power - 1))
			return (0);
		return (x * ft_power(x, power - 1));
	}
	if (power < 0)
		return (0);
	return (1);
}
