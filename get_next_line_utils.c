/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpeavey <rpeavey@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:56:06 by rpeavey           #+#    #+#             */
/*   Updated: 2024/06/15 22:56:50 by rpeavey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memchr(const void *ptr, int ch, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)ptr++ == (unsigned char)ch)
			return ((void *)(unsigned char *)ptr - 1);
	}
	return (NULL);
}

void	gnl_memset(void *dest, int ch, size_t n)
{
	while (n--)
	{
		*(unsigned char *)dest++ = (unsigned char)ch;
	}
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	void	*dest_ptr;

	dest_ptr = dest;
	if (!dest && !src)
		return (dest);
	while (n--)
		*(char *)dest++ = *(char *)src++;
	return (dest_ptr);
}

void	remove_n_bytes(char *buf, size_t n)
{
	char	tmp[BUFFER_SIZE];

	gnl_memset(tmp, 0, BUFFER_SIZE);
	gnl_memcpy(tmp, buf + n, BUFFER_SIZE - n);
	gnl_memset(buf, 0, BUFFER_SIZE);
	gnl_memcpy(buf, tmp, BUFFER_SIZE);
}
