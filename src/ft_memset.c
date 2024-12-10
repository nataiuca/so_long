/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:15:12 by natferna          #+#    #+#             */
/*   Updated: 2024/12/10 16:57:14 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	size_t	count;

	ptr = s;
	count = 0;
	while (count < n)
	{
		ptr[count] = c;
		count++;
	}
	return (s);
}
