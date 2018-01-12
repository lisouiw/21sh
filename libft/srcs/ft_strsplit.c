/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:01:02 by ltran             #+#    #+#             */
/*   Updated: 2017/09/06 12:28:28 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		ft_nb_word(const char *s, char c)
{
	int			i;
	int			word;

	i = -1;
	word = 0;
	while (s[++i] != '\0')
	{
		while (s[i] != c)
		{
			i++;
			if (s[i] == c)
				word++;
			if (s[i] == '\0')
				return (++word);
		}
	}
	return (word);
}

static int		ft_size_w(char const *s, char c, int i)
{
	int			nb;

	nb = 0;
	while (s[i] != '\0' && s[i++] != c)
		nb++;
	return (nb);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**spl;
	int			w;
	int			t;
	size_t		i;

	if (!s)
		return (NULL);
	w = ft_nb_word(s, c);
	t = 0;
	i = -1;
	if (!(spl = (char**)malloc(sizeof(char *) * (w + 1))))
		return (NULL);
	while (++i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			spl[t++] = ft_strsub(s, i, ft_size_w(s, c, i));
			i += ft_size_w(s, c, i);
		}
	}
	spl[t] = NULL;
	return (spl);
}
