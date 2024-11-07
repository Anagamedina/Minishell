/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:43:06 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 13:21:10 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc (sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*int main(void)
{
    t_list *lista = NULL; // Inicializar lista como NULL
    t_list *node1;
    char *content = "helloWorld";

    node1 = ft_lstnew(content);

    // Asignar node1 a lista si lista está vacía
    if (lista == NULL)
        lista = node1;
    int i = 0;
    while (lista != NULL)
    {
        // Imprimir contenido según su tipo
        printf("nodo[%d]: %s\n",i, (char*)lista->content);
        lista = lista->next;
        i++;
    }

    return (0);
}*/
