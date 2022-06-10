#include "ft_ssl.h"

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
}

void			fingerprint_output(uint32_t *fingprint)
{
	print_u32_little_endian(fingprint[A]);
	print_u32_little_endian(fingprint[B]);
	print_u32_little_endian(fingprint[C]);
	print_u32_little_endian(fingprint[D]);
}

void			vec_output(uint32_t *vec)
{
	for (int i = 0; i < SHA_VECN; i++)
		printf("%x", vec[i]);
}

void			output(t_data info, t_hash var)
{
	char	*alg_name[2] = {"MD5", "SHA256"};

	if ((info.flgs & MASK_Q) == 0 && (info.flgs & MASK_R) == 0)
	{
		printf("%s ", alg_name[info.cmd_id]);
		if ((info.flgs & MASK_S) != 0)
			printf("(\"%s\") = ", info.str);
		else
			printf("(%s) = ", info.file);
	}
	if (info.cmd_id == SHA256)
		vec_output(var.vector);
	else
		fingerprint_output(var.fingprint);
	if ((info.flgs & MASK_Q) == 0 && (info.flgs & MASK_R) != 0)
	{
		if ((info.flgs & MASK_S) != 0)
			printf(" \"%s\"", info.str);
		else
			printf(" %s", info.file);
	}
	printf("\n");
}
