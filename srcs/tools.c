#include "../twenty.h"

int     if_only(char *s, char c)
{
        
    while (s && *s == c)
        ++s;
    if (!(*s))
        return (1);
    return (0);
}
void	ecriture_info(t_env *lst)
{
	if (!(lst))
		return ;
	while (lst->next != NULL)
	{
		ft_putstr(lst->name);
		ft_putendl(lst->ctn);
		lst = lst->next;
	}
	ft_putstr(lst->name);
	ft_putendl(lst->ctn);
}