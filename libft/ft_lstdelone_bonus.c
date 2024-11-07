/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:01:40 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 13:20:09 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	del(void *content)
{
	free(content);
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
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

/*t_list *ft_lstnew (void *content)
{
	t_list	*new_nodo = (t_list*)malloc (sizeof(t_list));
	if (!new_nodo)
		return(NULL);

	new_nodo-> content = content;
	new_nodo->next = NULL;
	return (new_nodo);

}
int main (void)
{
	t_list	*lista = ft_lstnew(strdup(""));
	t_list	*node1 = ft_lstnew(strdup("10"));
	t_list	*node2 = ft_lstnew(strdup("25"));
	t_list	*node3 = ft_lstnew(strdup("40"));
	t_list	*node4 = ft_lstnew(strdup("75"));

	lista->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;

	node1->next = node3;

	printf("%s\n", node2->content);

	ft_lstdelone(node2, del);
	t_list	*tmp = lista;
	int i;
	i = 0;
    while (tmp != NULL)
	{
		printf("nodo[%d]: %s\n", i, tmp->content);
		tmp = tmp->next;
		i++;
    }
	ft_free(&lista);
    return (0);
}*/
