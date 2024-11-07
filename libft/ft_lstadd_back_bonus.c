/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:51:32 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 13:29:22 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

/*int main (void)
{
	t_list *lista = (t_list *) malloc(sizeof(t_list));
	t_list *node1 = (t_list *) malloc(sizeof(t_list));
	t_list *node2 = (t_list *) malloc(sizeof(t_list));
	t_list *node3 = (t_list *) malloc(sizeof(t_list));
	
	node1->content = "10";
	node1->next = NULL;

	node2->content = "25";
	node2->next = NULL;

	node3->content = "40";
	node3->next = NULL;

	
	lista->next = node1;
	node1->next = node2;
	node2->next = node3;


	t_list *tmp2 = lista;
	int i = 0;
	while (tmp2 != NULL)
	{
		printf("nodos antes de funcion[%d]: %s\n", i , tmp2->content);
		tmp2 = tmp2->next;
		i++;
	}

	t_list *new_nodo = (t_list *) malloc(sizeof(t_list));

	new_nodo->content = "75";
	new_nodo->next = NULL;

	ft_lstadd_back(&lista, new_nodo);
	t_list *temp = lista;
	i = 0;
	while (temp != NULL)
	{
		printf("nodo[%d]: %s\n", i, temp->content);
		temp = temp->next;
		i++;
	}
	return(0);
}*/
