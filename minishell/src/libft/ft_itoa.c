/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:43:24 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 15:58:10 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell_types.h"

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			buf[4];
	int				i;

	nb = (unsigned char)n;
	i = 3;
	buf[i] = '\0';
	i--;
	if (nb == 0)
	{
		buf[i] = '0';
		return (strdup(&buf[i]));
	}
	while (nb)
	{
		buf[i] = (char)('0' + (nb % 10));
		nb /= 10;
		i--;
	}
	return (strdup(&buf[i + 1]));
}
