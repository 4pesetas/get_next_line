/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iumorave <iumorave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:33:50 by iumorave          #+#    #+#             */
/*   Updated: 2024/12/09 12:01:08 by iumorave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




typedef struct s_list
{
   char         *content;
   struct s_list *next;
}               t_list;

/*Looks for a newline char in the given linked list*/

int found_newline(t_list *stash)
{
    int     i;
    t_list  *current;

    if (stash == NULL)
        return (0);
    current = ft_lst_get_last(stash);
    i = 0;
    while (current->content[i])
    {
        if (current->content[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

t_list  *ft_lst_get_last(t_list *stash)
{
    t_list *current;

    current = stash;
    while (current && current->next)
        current = current->next;
    return (current);
}