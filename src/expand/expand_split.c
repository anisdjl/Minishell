#include "../../minishell.h"

char	*ft_strjoin_spe(char *s1, char *s2)
{
	char	*ns;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ns = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!ns)
		return (NULL);
	while (s1[i])
	{
		ns[i] = s1[i];
		i++;
	}
	while (s2[j])
		ns[i++] = s2[j++];
	//ns[i] = ' ';
	ns[i + 1] = '\0';
	return (ns);
}

char	*expand_split(char *expand_value)
{
	int		i;
	char	*clean_vers;
	char	**split_vers;

	i = 0;
	clean_vers = ft_strdup("");
	split_vers = ft_split(expand_value, ' ');
	while (split_vers[i] != NULL)
	{
		clean_vers = ft_strjoin_spe(clean_vers, split_vers[i]);
		i++;
	}
	return (clean_vers);
}

/*
	Split -> strjoin
*/