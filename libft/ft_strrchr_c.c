#include "libft.h"

int	ft_strrchr_c(char *s, char c)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
		index ++;

	while (s[index] >= 0)
	{
		if (s[index] == c)
			return (index);
		index --;
	}
	return (-1);
}
