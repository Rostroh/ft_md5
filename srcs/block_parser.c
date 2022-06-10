#include "ft_ssl.h"

void			print_byte(unsigned char c)
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
		print_byte(buf[i]);
	}
	printf("\n");
}

static void		init_md5(t_hash *vars)
{
	vars->fingprint[A] = VEC_A;
	vars->fingprint[B] = VEC_B;
	vars->fingprint[C] = VEC_C;
	vars->fingprint[D] = VEC_D;
}

static void		init_sha256(t_hash *vars)
{
	vars->vector[0] = SHA_H0;
	vars->vector[1] = SHA_H1;
	vars->vector[2] = SHA_H2;
	vars->vector[3] = SHA_H3;
	vars->vector[4] = SHA_H4;
	vars->vector[5] = SHA_H5;
	vars->vector[6] = SHA_H6;
	vars->vector[7] = SHA_H7;
}

static void		init_vars(t_hash *vars, int algo)
{
	static void		(*init[NB_CMD])(t_hash *vars) = {&init_md5, &init_sha256};

	ft_bzero(vars, sizeof(t_hash));
	init[algo](vars);
}

static void		putsize(unsigned char *buf, int size, int is_sha)
{
	uint64_t	mask;
	int			shift;
	uint64_t	*ssize;

	mask = 0xff;
	shift = 0;
	if (is_sha)
	{
		for (int i = 1; i < 8; i++)
		{
			buf[BUF_SIZE - i] = (size & mask) >> shift;
			//printf("%x - %x - %x\n", size, (size & mask), (size & mask) >> shift);
			shift += 8;
			mask = mask << 8;
		}
		return ;
	}
	for (int i = 8; i > 0; i--)
	{
		buf[BUF_SIZE - i] = (size & mask) >> shift;
		shift += 8;
		mask = mask << 8;
	}
}

static int				setup_message(t_data *info, unsigned char *buf, int len)
{

	info->padding = NULL;
	buf[len % BUF_SIZE] = 0x80;
	if (len > 55)
	{
		info->padding = (unsigned char *)malloc(sizeof(unsigned char) * BUF_SIZE);
		bzero(info->padding, BUF_SIZE);
		putsize(info->padding, info->len * 8, info->cmd_id);
	}
	else
		putsize(buf, info->len * 8, info->cmd_id);
	return (0);
}

void		setup_m(t_hash *var, unsigned char *buf, int is_sha)
{
	int			shift;

	for (int i = 0; i < 16; i++)
	{
		shift = 0;
		var->m[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			//printf("[%d] = %x\n", i * 4 + j, buf[i * 4 + j]);
			if (is_sha)
				var->m[i] = (var->m[i] << 8) + buf[i * 4 + j];
			else
				var->m[i] = var->m[i] + (buf[i * 4 + j] << shift);
			//printf("---> %x\n", var->m[i]);
			shift += 8;
		}
	}
}

int				block_parser(t_data info)
{
	int				len;
	int				block_id;
	t_hash			vars;
	unsigned char	buf[BUF_SIZE];
	static void		(*command[NB_CMD])(unsigned char *buf, t_data info, t_hash *vars) = {&md5, &sha256};

	
	init_vars(&vars, info.cmd_id);
	block_id = 0;
	do
	{
		ft_bzero(buf, BUF_SIZE);
		len = reader(info, buf, block_id * BUF_SIZE);
		if ((info.flgs & MASK_P) != 0)
			printf("%s", buf);
		info.len += len;
		if (len != BUF_SIZE)
			setup_message(&info, buf, len);
		setup_m(&vars, buf, info.cmd_id);
		command[info.cmd_id](buf, info, &vars);
		block_id++;
	} while (len == BUF_SIZE);
	if (info.padding)
	{
		setup_m(&vars, info.padding, info.cmd_id);
		command[info.cmd_id](info.padding, info, &vars);
	}
	ft_memcpy(info.fingprint, &vars.fingprint, sizeof(uint32_t) * 4);
	output(info, vars);
	return (0);
}
