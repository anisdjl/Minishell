#include "../../minishell.h"

void  history(char *line)
{
	int fd;

	if (access(".minishell_history", F_OK) == -1)
	{
		fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0700);
		if (fd == -1)
            return ;
	}
	else
		fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND);
	write(fd, line, ft_strlen(line)); // on doit mettre notre ft_strlen
	write(fd, "\n", 1);
}