/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 21:19:30 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	if (!s)
		return (NULL);
	ch = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)(s + i));
		i++;
	}
	if (ch == '\0')
		return ((char *)(s + i));
	return (NULL);
}
