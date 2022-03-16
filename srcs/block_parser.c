#include "ft_ssl.h"

static void		print_byte(unsigned char c)
{
	int		and = 128;
	int		shift = 7;

	for (int i = 0; i < 8; i++)
	{
		printf("%d", (c & and) >> shift);
		and = and >> 1;
		shift--;
	}
	printf(" ");
}

static void		print_block(unsigned char *buf)
{
	printf("BLOCK BYTES:\n");
	for (int i = 0; i < BUF_SIZE; i++)
	{
		//printf("%03d ", buf[i]);
		print_byte(buf[i]);
	}
	printf("\n");
}

int				block_parser(t_data *info, int command(t_data *info))
{
	int				len;
	int				block_id;
	unsigned char	buf[BUF_SIZE];

	block_id = 0;
	do
	{
		ft_bzero(buf, BUF_SIZE);
		len = reader(*info, buf, block_id * BUF_SIZE);
		info->len += len;
		if (len != BUF_SIZE)
			setup_message(info, buf, len);
		print_block(buf);
		block_id++;
	} while (len == BUF_SIZE);
	if (info->padding)
	{
		printf("sha prout\n");
		print_block(info->padding);
	}
	return (0);
}
