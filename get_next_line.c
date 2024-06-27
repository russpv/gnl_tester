/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpeavey <rpeavey@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:47:21 by rpeavey           #+#    #+#             */
/*   Updated: 2024/06/15 22:53:26 by rpeavey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define SUCCESS 0
#define FAILURE -1

static void	_check_buf(struct s_vars *v);
static void	*_concat_all(struct s_vars *v);
static int	_file_to_stack(struct s_vars *v);
static char	*_handle_result_and_cleanup(char **cc, struct s_vars *v, int i);

/* CHECKBUF
 * Sets flag to skip read loop if newline in buf
 * Sets byte counter based on buf content
 * Copies buf in to stack
*/
static void	_check_buf(struct s_vars *v)
{
	size_t	buflen;
	char	*nulloc;
	char	*newloc;

	buflen = 0;
	nulloc = gnl_memchr(v->buf, '\0', BUFFER_SIZE);
	newloc = (char *)gnl_memchr(v->buf, '\n', BUFFER_SIZE);
	if (newloc)
		buflen = newloc - v->buf + 1;
	else if (*(v->buf) && nulloc)
		buflen = nulloc - v->buf;
	else if (*(v->buf))
		buflen = BUFFER_SIZE;
	v->bytes_read = buflen;
	if (newloc)
	{
		v->code = EOLPRELOOP;
		return ;
	}
	if (buflen <= PAGESZ)
	{
		gnl_memcpy(v->stackbuf, v->buf, buflen);
		remove_n_bytes(v->buf, buflen);
	}
}

/* CONCATALL -> returns new string
** Copies heap allocs (linked list) and stackbuf if loop ran
**	OR only buf if loop didn't run, into one malloc location
** Called after end of read loop
**
** bytes_read: only the bytes since last STCK>HP flush or pre-loop buf check
*/
static void	*_concat_all(struct s_vars *v)
{
	char			*line;
	unsigned int	offset;
	size_t			stackbytes;

	offset = 0;
	line = malloc(sizeof(char) * (v->bytes_read + \
				(v->bytes_read / v->bytes_read) * 1));
	if (!line)
		return (NULL);
	line[v->bytes_read] = 0;
	stackbytes = (char *)gnl_memchr(v->stackbuf, 0, PAGESZ) - *(v->stackbuf);
	if (v->code != EOLPRELOOP && *(v->stackbuf))
	{
		gnl_memcpy(line, v->stackbuf, stackbytes);
		offset += stackbytes;
	}
	if (v->code == EOLPRELOOP)
	{
		gnl_memcpy(line + offset, v->buf, v->bytes_read - stackbytes);
		v->bytes_read -= stackbytes;
		remove_n_bytes(v->buf, v->bytes_read);
	}
	return (line);
}

/* FILETOSTACK -> returns new string
** Main read() loop. Concats buffer reads on stack until \n or limit reached
** If BUFF_SIZE > PAGESZ, flushes buf to heap instead
*/
static int	_file_to_stack(struct s_vars *v)
{
	ssize_t	n;

	n = 1;
	while (n > 0 && (v->code != EOL && v->code != EOLPRELOOP))
	{
		n = read(v->fd, v->buf, BUFFER_SIZE);
		if (n < 0 || (v->bytes_read == 0 && n == 0))
			return (FAILURE);
		if (n == 0)
			v->code = EOFILE;
		if (gnl_memchr(v->buf, '\n', BUFFER_SIZE))
		{
			n = (char *)gnl_memchr(v->buf, '\n', BUFFER_SIZE) - v->buf + 1;
			v->code = EOL;
		}
		if (v->code != EOFILE && v->bytes_read + n <= PAGESZ)
		{
			gnl_memcpy(*(v->stackbuf) + v->bytes_read, v->buf, n);
			remove_n_bytes(v->buf, n);
		}
		v->bytes_read += n;
	}
	return (SUCCESS);
}

static char	*_handle_result_and_cleanup(char **buf, struct s_vars *v, int res)
{
	char	*result;

	if (v->code == EOFILE || res == FAILURE)
	{
		free(*buf);
		*buf = NULL;
		if (res == FAILURE)
			return (NULL);
	}
	result = (char *)_concat_all(v);
	if (!result)
	{
		if (v->code != EOFILE)
		{
			free(*buf);
			*buf = NULL;
		}
		return (NULL);
	}
	return (result);
}

/* If line bytes exceeds PAGESZ, does not work. */
char	*get_next_line(int fd)
{
	static char			*buf[MAX_BUFFERS];
	char				stackbuf[PAGESZ];
	struct s_vars		vars;	
	int					res;

	if (fd < 0 || fd > MAX_BUFFERS)
		return (NULL);
	if (!buf[fd])
	{	
		buf[fd] = malloc(sizeof(char) * BUFFER_SIZE);
		if (!buf[fd])
			return (NULL);
		gnl_memset(buf[fd], 0, BUFFER_SIZE);
	}
	vars.buf = buf[fd];
	vars.fd = fd;
	vars.stackbuf = &stackbuf;
	gnl_memset(*(vars.stackbuf), 0, PAGESZ);
	vars.code = PRELOOP;
	vars.bytes_read = 0;
	_check_buf(&vars);
	res = FAILURE;
	res = _file_to_stack(&vars);
	return (_handle_result_and_cleanup(&buf[fd], &vars, res));
}
