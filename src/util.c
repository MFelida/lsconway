

#include "util.h"

#include <stdio.h>

int	read_line(FILE *fp, char *read_buffer)
{
	int		bytes_read;
	char	c;

	bytes_read = 0;
	c = fgetc(fp);
	while (c != '\n' && c != EOF)
	{
		read_buffer[bytes_read] = c;
		c = fgetc(fp);
		bytes_read++;
	}
	read_buffer[bytes_read] = '\0';
	return bytes_read;
}