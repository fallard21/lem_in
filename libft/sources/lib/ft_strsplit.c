/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:38:28 by edoll             #+#    #+#             */
/*   Updated: 2020/09/11 15:20:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Function to handle splited arrays
*/

int			ft_len_splited(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void		ft_free_splited(char **split)
{
	int		i;

	i = 0;
	if (!split || !*split)
		return;
	while (split[i])
		free (split[i++]);
	free(split);
	return;	
}

/*
**	Strsplit functions
*/

static char		*get_word(const char *s, char c)
{
	size_t	ln;
	char	*word;
	int		i;

	i = 0;
	ln = 0;
	while (s[ln] && s[ln] != c)
		ln++;
	if (!(word = (char*)malloc(sizeof(char) * (ln + 1))))
		return (NULL);
	while (*s && *s != c)
		word[i++] = *s++;
	word[i] = '\0';
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	w_ct;
	size_t	i;

	i = 0;
	if (s)
	{
		w_ct = ft_word_count(s, c);
		if (!(tab = (char**)malloc(sizeof(char*) * (w_ct + 1))))
			return (NULL);
		while (*s)
		{
			if (*s == c)
				s++;
			else
			{
				tab[i++] = get_word(s, c);
				while (*s && *s != c)
					s++;
			}
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
