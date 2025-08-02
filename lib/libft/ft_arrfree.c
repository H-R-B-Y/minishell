
#include "include/libft.h"

void	ft_arrfree(void **chunks)
{
	void	**ch;

	if (!chunks)
		return ;
	ch = chunks;
	while (*chunks)
	{
		free(*chunks);
		*chunks = 0;
		chunks++;
	}
	free(ch);
}