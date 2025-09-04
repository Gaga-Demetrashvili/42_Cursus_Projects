/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:50:53 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/02 20:04:25 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>

int	ft_isalnum(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return ((1));
	return (0);
}

// int	main(void)
// {
// 	ft_printf("Result of isalnum original - %d\n", isalnum('$'));
// 	ft_printf("Result of isalnum mine - %d\n", ft_isalnum('%'));

// 	return (0);
// }