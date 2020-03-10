/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:16:31 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/06 21:42:51 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// void    *sf_malloc(size_t size)
// {
//     void    *ptr;
//     static  int i;

//     if (!(ptr = malloc(size)))
//         (handle_error(Allocation_Failed, FAIL));
//     g_world.adresses[i] = ptr;
//     g_world.adresses[i + 1] = 0;
//     i++;
//     return (ptr);
// }

// void    free_all(int status)
// {
//     int i;

//     i = -1;
//     while (g_world.adresses[++i] != 0)
//         free(g_world.adresses[i]);
//     exit(status);
// }

void    print_lst(t_lst *lst)
{
    while (lst != NULL)
    {
        printf("%s\n", (char*)lst->content);
        lst = lst->next;
    }
}

void    *sf_malloc(size_t size)
{
    void    *ptr;

    if (!(ptr = malloc(size)))
        (handle_error(Allocation_Failed, FAIL));
    t_lst *lst = new_lst(ptr);
    push_back(&g_world.adresses, lst);
    //print_lst(g_world.adresses);
    printf("[%s]\n", (char*)lst->content);
    return (ptr);
}

void    free_all(int status)
{
    deleteList(&g_world.adresses);
    exit(status);
}