/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:00:54 by athonda           #+#    #+#             */
/*   Updated: 2025/01/08 11:29:59 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @fn dlist.c
 * @brief manupilate double linked list
 */

#include "miniRT.h"

t_dlist	*dlst_new(void *content)
{
	t_dlist	*newlst;

	newlst = (t_dlist *)malloc(sizeof (t_dlist) * 1);
	if (newlst == NULL)
		return (NULL);
	newlst->content = content;
	newlst->next = NULL;
	newlst->prev = NULL;
	return (newlst);
}

t_dlist	*dlst_add_right(t_dlist **lst, t_dlist *new)
{
	if (lst == NULL || new == NULL)
		return (NULL);
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = new;
		(*lst)->prev = new;
	}
	else
	{
		new->next = (*lst)->next;
		new->prev = (*lst)->prev;
		(*lst)->next->prev = new;
		(*lst)->next = new;
	}
	*lst = new;
	return (*lst);
}