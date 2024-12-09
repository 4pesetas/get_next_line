/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iumorave <iumorave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:38:08 by iumorave          #+#    #+#             */
/*   Updated: 2024/12/09 12:19:23 by iumorave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static	t_list	*stash = NULL;
	char	*line;
	int		readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	readed = 1;
	line = NULL;
	// 1. read from fd and add to linked list
	read_and_stash(int fd, &stash, &readed);
	if (stash == NULL)
		return (NULL);
	//2, extract from stash to line
	//3. clean up stash
	return (line);
} 

void	read_and_stash(t_list **stash, int *readed_ptr)
{
	char	*buf;

	while (!found_newline(*stash) && *readed_ptr != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return;
		*readed_ptr = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && *readed_ptr == 0) || *readed_ptr == -1)
		{
			free(buf);
			return;
		}
		buf[*readed_ptr] = '\0';
		add_to_stash(stash, buf, *readed_ptr);
		free(buf);
	}
}
void	add_to_stash(t_list **stash, char *buf, int readed)
{
	int	i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i]
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}
int main()
{
    int	fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}

