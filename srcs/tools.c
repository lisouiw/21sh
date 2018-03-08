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

char	*strjoin_free(char *nw, char *sub, int i)
{
	char	*tmp;

	if (nw && sub == NULL)
		sub = nw;
	else if (nw && sub)
	{
		tmp = ft_strjoin(sub, nw);
		if (i == 1 || i == 3)
			free(nw);
		if (i == 2 || i == 3)
			free(sub);
		return (tmp);
	}
	return (sub);
}