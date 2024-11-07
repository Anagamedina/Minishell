/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:39:48 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 13:18:49 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL )
		return ;
	new->next = *lst;
	*lst = new;
}
/*int main(void)
{ 
	//definir una lista vaacia
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

	//CREAMOS LISTA
	lista->next = node1;
	node1->next = node2;
	node2->next = node3;

	t_list *new_nodo = (t_list *) malloc(sizeof(t_list));
	
	new_nodo->content = "75";
	new_nodo->next = NULL;

	ft_lstadd_front(&lista, new_nodo);
	t_list *temp = lista;
	int i = 0;
	while (temp != NULL)
	{
		printf("nodo[%d]: %s\n", i, temp->content);
		temp = temp->next;
		i++;
	}
	return(0);
}*/
