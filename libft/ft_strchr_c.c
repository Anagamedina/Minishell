
#include "libft.h"


int	ft_strchr_c(const char *s, char c)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (-1);
}