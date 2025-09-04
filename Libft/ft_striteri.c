/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:38:44 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/17 19:45:10 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	while (*(s + i))
	{
		f(i, s + i);
		i++;
	}
}

void	ft_delegate_iteri(unsigned int i, char *p)
{
	*p += 1 + (0 * i);
}

// int	main(void)
// {
// 	char src[] = "012345678";
// 	ft_striteri(src, ft_delegate_iteri);
// 	printf("%s", src);
// 	return (0);
// }