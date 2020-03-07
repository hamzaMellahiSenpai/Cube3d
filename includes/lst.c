/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 00:30:02 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/05 22:27:45 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	push_back(t_lst **alst, t_lst *new)
{
	t_lst	*ptr;

	if (!*alst)
		return (push_front(alst, new));
	ptr = *alst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void push_front(t_lst** head_ref, t_lst *new) 
{ 
    new->next = *head_ref;
    *head_ref = new;
}

t_lst	*new_lst(void *content)
{
	t_lst	*newlist;

	newlist = sf_malloc(sizeof(t_lst));
	newlist->content = content;
	newlist->next = NULL;
	printf("[%s]\n", (char*)((t_pair*)content)->b);
	return (newlist);
}

void deleteList(t_lst** head_ref)
{  
	t_lst* current;
	t_lst* next;

	current = *head_ref;
	while (current != NULL)
	{  
		next = current->next;
		free(current);
		current = next;
	}  
	*head_ref = NULL;
}

t_pair	*make_pair(void *a, void *b)
{
	t_pair *pair;

	pair = sf_malloc(sizeof(t_pair));
	pair->a = a; //Leakos
	pair->b = b;
	//printf("%d || %s\n", (*(int*)pair->a), (t_string)pair->b);
	return (pair);
}

void	lstiter(t_lst *lst, void  *(*f)(void *))
{
	t_lst	*ptr;

	ptr = lst;
	while (ptr)
	{
		f(ptr->content);
		ptr = ptr->next;
	}
}