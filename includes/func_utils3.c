
#include "../header.h"

int		tablen(void **tab)
{
	int i;

	i = 0;
	while (*tab++)
		i++;
	return (i);
}

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		isnumber(t_string str)
{
	while (*str)
		if (!(ft_isdigit(*str++)))
			return (0);
	return (1);
}


char		*trim(char const *s, char const *set)
{
        int             debut;
        int             fin;
        int             i;
        char    *p;

        debut = -1;
        if (!s)
                return (NULL);
        if (!set)
                return (ft_strdup(s));
        fin = ft_strlen(s);
        while (s[++debut] && ft_strchr(set, s[debut]))
                ;
        while (debut < fin - 1)
                if (!ft_strchr(set, s[fin - 1]))
                        break ;
                else
                        fin--;
        if (!(p = sf_malloc(fin - debut + 1)))
                return (NULL);
        i = -1;
        while (++i < (fin - debut))
                p[i] = s[debut + i];
        p[i] = '\0';
        return (p);
}