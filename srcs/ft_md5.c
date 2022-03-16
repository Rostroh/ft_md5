#include "ft_ssl.h"
/*
static int		get_next_arg(t_data *info, int index)
{
	if (index + 1  >= info->nb_param && (info->flgs & MASK_S) != 0)
			return (error_string("md5"));
	if ((info->flgs & MASK_S) != 0)
		info->str = info->param[index + 1];
	else
		info->file = info->param[index];
	return (1);
}
*/
static void		print_byte(unsigned char c)
{
	int		and = 128;
	int 	shift = 7;

	for (int i = 0; i < 8; i++)
	{
		printf("%d", (c & and) >> shift);
		and = and >> 1;
		shift--;
	}
	printf(" ");
}

static void		putsize(unsigned char *buf, int size)
{
	uint64_t	mask;
	int			shift;

	mask = 0xff;
	shift = 0;
	//for (int i = 1; i <= 8; i++)
	for (int i = 8; i > 0; i--)
	{
		//printf("%d\n", BUF_SIZE - i);
		buf[BUF_SIZE - i] = (size & mask) >> shift;
		//buf[BUF_SIZE - i] = (size & mask) >> shift;
		//printf("size = %d mask %llx shift %x %d\n", size, mask, shift, size & mask, (size & mask) >> shift);
		shift += 8;
		mask = mask << 8;
	}
}

uint32_t		calc_k(uint32_t i)
{/*
	uint32_t	val;

	for (int i = 0; i < 64; i++)
	{
		val = fabs(sin(i + 1)) * pow(2, 32);
		printf("%d : 0x%X\n", i, val);
	}*/
	return (fabs(sin(i + 1)) * pow(2, 32));
}

void		setup_m(t_md5 *var, unsigned char *buf)
{
	int			shift;

	for (int i = 0; i < 16; i++)
	{
		shift = 0;
		var->m[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			var->m[i] = var->m[i] + (buf[i * 4 + j] << shift);
			shift += 8;
			//var->m[i] = (var->m[i] << 8) + buf[i * 4 + j];
			//printf("buf[%d] = %d\n", i * 4 + j, buf[i * 4 + j]);
		}
	}
}

static void		print_block(unsigned char *buf)
{
	printf("BLOCK BYTES :\n");
	for (int i = 0; i < BUF_SIZE; i++)
	{
		print_byte(buf[i]);
	}
	printf("\n");
}

int				setup_message(t_data *info, unsigned char *buf, int len)
{
//	unsigned char		*padding;

	info->padding = NULL;
	//printf("FINAL BLOCK ! %d -- %d\n", len * 8, block_id);
	buf[len % BUF_SIZE] = 0x80;
		//if (len % BUF_SIZE != 0 && 448 - 1 - (len- block_id * BUF_SIZE) * 8 <= 0)
	if (len > 55)
	{
	//	printf("total len = %d\n", info.len);
		info->padding = (unsigned char *)malloc(sizeof(unsigned char) * BUF_SIZE);
		bzero(info->padding, BUF_SIZE);
		putsize(info->padding, info->len * 8);
	}
	else
		putsize(buf, info->len * 8);
/*	print_block(buf);
	if (padding)
	{
	//	printf("PADDED\n");
		print_block(padding);
	}*/
	return (0);
}

uint32_t		not(uint32_t byte)
{
	//return (byte ^ 0xffffffff);
	return (~byte);
}

uint32_t		mod_add(uint32_t x, uint32_t y)
{
	return ((x + y) % MOD_Z);
}

uint32_t		left_rot(uint32_t byte, int n)
{
	//printf("shift for 0x%x %d\n", byte, n);
	//printf("0x%x et 0x%x\n", byte << n, byte >> (BYTE_SIZE - n));
	return ((byte << n) | (byte >> (BYTE_SIZE - n)));
}

void			switch_vec(t_md5 *var, uint32_t byte)
{
	var->vector[A] = var->vector[D];
	var->vector[D] = var->vector[C];
	var->vector[C] = var->vector[B];
	var->vector[B] = byte;
	if (VERBOSE)
		printf("\nh0: 0x%x\nh1: 0x%x\nh2: 0x%x\nh3: 0x%x\n", var->vector[A], var->vector[B], var->vector[C], var->vector[D]);
}

void			print_u32_little_endian(uint32_t byte)
{
	int			mask;
	int			shift;

	mask = 0xff;
	shift = 0;
	for (int i = 0; i < 4; i++)
	{
		printf("%02x", (byte & mask) >> shift);
		mask = mask << 8;
		shift += 8;
	}
	//printf(" ");
}

void			fingerprint_output(uint32_t *fingprint)
{
//	printf("BEFORE\n");
//	printf("%x %x %x %x\n", var.fingprint[A], var.fingprint[B], var.fingprint[C], var.fingprint[D]);
	print_u32_little_endian(fingprint[A]);
	print_u32_little_endian(fingprint[B]);
	print_u32_little_endian(fingprint[C]);
	print_u32_little_endian(fingprint[D]);
	//ft_putchar('\n');
}

void			init_vec(t_md5 *vars)
{
	vars->vector[A] = vars->fingprint[A];
	vars->vector[B] = vars->fingprint[B];
	vars->vector[C] = vars->fingprint[C];
	vars->vector[D] = vars->fingprint[D];
}

void			md5(unsigned char *buf, t_data info, t_md5 *var)
{
	uint32_t		byte;
	static void		(*round[4])(t_md5 *var, int i) = {&round1, &round2, &round3, &round4};
	static int		shift[4][4] = {{7, 12, 17, 22}, {5, 9, 14, 20}, {4, 11, 16, 23}, {6, 10, 15, 21}};

	init_vec(var);
	for (int i = 0; i < 64; i++)
	{
		round[i / 16](var, i);
		byte = left_rot(var->vector[A] + var->f + calc_k(i) + var->m[var->g], shift[i / 16][i % 4]) + var->vector[B];
		switch_vec(var, byte);
	}
	var->fingprint[A] += var->vector[A];
	var->fingprint[B] += var->vector[B];
	var->fingprint[C] += var->vector[C];
	var->fingprint[D] += var->vector[D];
}

static void		init_vars(t_md5 *vars)
{
	vars->fingprint[A] = VEC_A;
	vars->fingprint[B] = VEC_B;
	vars->fingprint[C] = VEC_C;
	vars->fingprint[D] = VEC_D;
}
/*
int				ft_md5(t_data *info)
{
	int		len;
	unsigned char	*buf;
	int		block_id;
	t_md5	vars;

	init_vars(&vars);
	buf = (unsigned char *)malloc(sizeof(unsigned char) * BUF_SIZE);
	block_id = 0;
	ft_bzero(buf, BUF_SIZE);
	while ((len = reader(*info, buf, block_id * BUF_SIZE)) == BUF_SIZE)//stop == 0)
	{
		if ((info->flgs & MASK_P) != 0)
			printf("%s", buf);
		info->len += len;
		setup_m(&vars, buf);
		md5(buf, *info, &vars);
		ft_bzero(buf, BUF_SIZE);
		block_id++;
	}
	if ((info->flgs & MASK_P) != 0)
		printf("%s", buf);
	info->len += len;
	setup_message(info, buf, len);
	setup_m(&vars, buf);
	md5(buf, *info, &vars);
	if (info->padding)
	{
		setup_m(&vars, info->padding);
		md5(info->padding, *info, &vars);
	}
	ft_memcpy(info->fingprint, &vars.fingprint, sizeof(uint32_t) * 4);
	output(*info);
	return (0);
}*/
