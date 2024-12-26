/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:40:04 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 13:24:33 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	del(void *content)
{
	free(content);
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

/*void	ft_free(t_list **lst)
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
}*/

/*int main (void)
{
	t_list *lista = ft_lstnew(strdup("i"));
	t_list *node1 = ft_lstnew(strdup("10"));
	t_list *node2 = ft_lstnew(strdup("25"));
	t_list *node3 = ft_lstnew(strdup("40"));
	t_list *node4 = ft_lstnew(strdup("75"));

   	 //creamos lista
	lista->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	t_list *tmp2 = lista->next;
	int i = 0;
	while (tmp2 !=  NULL)
	{
		printf("lista antes de clear[%d]: %s\n",i, tmp2->content);
		tmp2 = tmp2->next;
		i++;

	}
	//printf("head antes de clear: %s\n", lista->content);
	//eliminar  nodo....
	ft_lstclear(&node3, del);


	t_list	*tmp = lista;
	i = 0;
    while (tmp)
	{
		printf("0 %p\n", tmp);
		printf("init %d\n", i);
		printf("- nodo[%d]: %s\n", i, (*tmp).content);
		printf("1 %d\n", i);
		tmp = tmp->next;
		printf("tmp %p")
		printf("2 %d\n", i);
		i++;
    }
	//ft_free(&lista);
    return (0);
}*/