/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:31:18 by ashih             #+#    #+#             */
/*   Updated: 2017/12/25 03:55:44 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define GNL_BUFF_SIZE 4096

/*
** Function: int chop_next_line(char **src, char **dst);
**
** Pre-condition: *src must contain a '\n'.
**
** Set *dst to a new string containing the first half of *src up to '\n',
** without the '\n'.
**
** Set *src to a new string containing its remaining half after the '\n',
** without the '\n'.
**
** Return 1 if success;
** Return -1 if an error has occurred.
*/

static int			chop_next_line(char **src, char **dst)
{
	int				new_src_len;
	int				dst_len;
	char			*temp;

	dst_len = ft_strchr(*src, '\n') - *src;
	if ((*dst = malloc(sizeof(char) * (dst_len + 1))) == 0)
		return (-1);
	ft_strncpy(*dst, *src, dst_len);
	(*dst)[dst_len] = '\0';
	new_src_len = ft_strlen(*src) - dst_len - 1;
	temp = *src;
	if ((*src = malloc(sizeof(char) * (new_src_len + 1))) == 0)
		return (-1);
	ft_strncpy(*src, ft_strchr(temp, '\n') + 1, new_src_len);
	(*src)[new_src_len] = '\0';
	ft_strdel(&temp);
	return (1);
}

/*
** Function: int do_one_read(int fd, t_gnl *gnl);
**
** Do read() once into buffer, and set gnl->str to the result of
** joining gnl->str and buffer.
**
** Return 1 if success;
** Return -1 if an error has occurred.
*/

static int			do_one_read(int fd, t_gnl *gnl)
{
	int				ret;
	char			buffer[GNL_BUFF_SIZE + 1];
	char			*temp;

	ret = read(fd, buffer, GNL_BUFF_SIZE);
	if (ret == -1)
		return (-1);
	if (ret == 0)
		return (0);
	buffer[ret] = '\0';
	temp = gnl->str;
	if ((gnl->str = ft_strjoin(temp, buffer)) == 0)
		return (-1);
	ft_strdel(&temp);
	return (1);
}

/*
** Function: t_gnl *add_new_gnl_to_list(t_list **list, int fd);
**
** Create a new t_gnl object for the given fd, add it to list,
** and return a pointer to the new t_gnl object.
**
** Return NULL if an error has occurred.
*/

static t_gnl		*add_new_gnl_to_list(t_list **list, int fd)
{
	t_list			*temp;
	t_gnl			*new;

	if (list == 0 || (new = malloc(sizeof(t_gnl))) == 0)
		return (0);
	new->fd = fd;
	if ((new->str = malloc(sizeof(char) * 1)) == 0)
	{
		free(new);
		return (0);
	}
	new->str[0] = '\0';
	if ((temp = ft_lstnew(new, sizeof(t_gnl))) == 0)
	{
		ft_strdel(&(new->str));
		free(new);
		return (0);
	}
	ft_lstadd(list, temp);
	free(new);
	return ((*list)->content);
}

/*
** Function: t_gnl *find_gnl(t_list **list, int fd);
**
** Search the linked list and return a pointer to the t_gnl object
** that matches the giiven fd.
**
** If it does not exist, create a new t_gnl object, add it to list,
** and return a pointer to the new t_gnl object.
**
** Return NULL if an error has occurred.
*/

static t_gnl		*find_gnl(t_list **list, int fd)
{
	t_list			*temp;

	temp = *list;
	while (temp != 0)
	{
		if (((t_gnl *)(temp->content))->fd == fd)
			return (temp->content);
		temp = temp->next;
	}
	return (add_new_gnl_to_list(list, fd));
}

/*
** Function: int get_next_line(const int fd, char **line);
**
** Set *line to a new string that was read up to a '\n', without the '\n'.
**
** Remember to resume where it stopped after the previous get_next_line() call.
**
** Return 1 if a line has been read succesfully;
** Return 0 if there are no more chars to read;
** Return -1 if an error has occurred.
*/

int					get_next_line(const int fd, char **line)
{
	static t_list	*list = 0;
	t_gnl			*gnl;
	int				flag;

	if (fd < 0 || line == 0 || (gnl = find_gnl(&list, fd)) == 0)
		return (-1);
	while (1)
	{
		if (gnl->str == 0)
			return (0);
		if (ft_strchr(gnl->str, '\n') != 0)
			return (chop_next_line(&(gnl->str), line) == -1) ? (-1) : (1);
		if ((flag = do_one_read(fd, gnl)) == -1)
			return (-1);
		if (flag == 0)
		{
			if (ft_strlen(gnl->str) == 0)
				return (0);
			if ((*line = ft_strdup(gnl->str)) == 0)
				return (-1);
			ft_strdel(&(gnl->str));
			return (1);
		}
	}
}
