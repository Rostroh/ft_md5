#include "ft_ssl.h"
/*
 *	read from provided string
*/
static int		fetch_byte_string(char *str, unsigned char *buffer, int file_offset)
{
	int		size;
	int		off;

	//printf("Fetch string\n");
	off = ft_strlen(str) - file_offset;
	size = off - BUF_SIZE >= 0 ? BUF_SIZE : off;
	for (int i = 0; i < size; i++)
	{
		buffer[i] = str[file_offset + i];
	}
	//printf("%s\n", buffer);
	return (off <= 0 ? 0 : size);
/*	printf("size = %d\n", size);
	if (off <= 0 || size % BUF_SIZE != 0)
	{
		*stop = 1;
//		printf("Stop = 1\n");
	}*/
	return (size);
}

/*
 *	read from provided file
*/
static int		fetch_byte_file(int fd, char *buf)//, int *stop)
{
	int		nb_read;

	nb_read = read(fd, buf, BUF_SIZE);
	if (nb_read == 0 || nb_read % BUF_SIZE != 0)
		;//*stop = 1;
	return (nb_read);
}

/*
**	read 64 bytes from plain text
*/
int				reader(t_data info, unsigned char *buffer, int file_offset)
{
	//printf("flg = %d\n", info.flgs);
	if ((info.flgs & MASK_S) != 0)
		return (fetch_byte_string(info.str, buffer, file_offset));
	else
		//return (fetch_byte_file(info.fd, buffer));
		return (read(info.fd, buffer, BUF_SIZE));
	return (0);
}
