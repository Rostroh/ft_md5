#include "ft_ssl.h"

void				print_u32(uint32_t byte)
{
	int			shift = 31;
	uint32_t	and = 0x80000000;

	for (int i = 0; i < 32; i++)
	{
		//printf("byte = %x, & = %x et byte& = %x\n", byte, and, byte & and);
		printf("%u", (byte & and) >> shift);
		//printf("\n");
		and = and >> 1;
		shift--;
	}
	printf(" ");
}

static void			print_w(uint32_t *w)
{
	for (int i = 0; i < SHA_MLEN; i++)
	{
		print_u32(w[i]);
		if (i % 2 != 0 && i != 0)
			printf("\n");
	}
	printf("\n");
}

static uint32_t		round_constant(int i)
{
	static uint32_t		tab[64] = 
		{0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 
		0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be,
		0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1,
		0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc,
		0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3,
		0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
		0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1,
		0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585,
		0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 
		0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 
		0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

		return (tab[i]);
}

static void			setup_w(t_hash *var)
{
	uint32_t	s0;
	uint32_t	s1;

	for (int i = 16; i < SHA_MLEN; i++)
	{
		s0 = (right_rot(var->m[i - 15], 7) ^ right_rot(var->m[i - 15], 18)) ^ (var->m[i - 15] >> 3);
		s1 = (right_rot(var->m[i - 2], 17) ^ right_rot(var->m[i - 2], 19)) ^ (var->m[i - 2] >> 10);
		var->m[i] = var->m[i - 16] + s0 + var->m[i - 7] + s1;
	}
}

static void			init_tab(uint32_t *tab, t_hash var)
{
	for (int i = 0; i < 8; i++)
		tab[i] = var.vector[i];
}

static void			switch_var(uint32_t *var_tab, uint32_t temp1, uint32_t temp2)
{
	var_tab[H] = var_tab[G];
	var_tab[G] = var_tab[F];
	var_tab[F] = var_tab[E];
	var_tab[E] = var_tab[D] + temp1;
	var_tab[D] = var_tab[C];
	var_tab[C] = var_tab[B];
	var_tab[B] = var_tab[A];
	var_tab[A] = temp1 + temp2;
}

static void			add_vectors(t_hash *var, uint32_t *var_tab)
{
	for (int i = 0; i < SHA_VECN; i++)
	{
		var->vector[i] += var_tab[i];
	}
}

void				sha256(unsigned char *buf, t_data info, t_hash *var)
{
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	ch;
	uint32_t	maj;
	uint32_t	tmp1;
	uint32_t	tmp2;
	uint32_t	var_tab[8];

	setup_w(var);
	init_tab(var_tab, *var);
	for (int i = 0; i < 64; i++)
	{
		s1 = (right_rot(var_tab[E], 6) ^ right_rot(var_tab[E], 11)) ^ right_rot(var_tab[E], 25);
		ch = (var_tab[E] & var_tab[F]) ^ (~var_tab[E] & var_tab[G]);
		tmp1 = var_tab[H] + s1 + ch + round_constant(i) + var->m[i];
		s0 = (right_rot(var_tab[A], 2) ^ right_rot(var_tab[A], 13)) ^ right_rot(var_tab[A], 22);
		maj = (var_tab[A] & var_tab[B]) ^ (var_tab[A] & var_tab[C]) ^ (var_tab[B]& var_tab[C]);
		tmp2 = s0 + maj;
		switch_var(var_tab, tmp1, tmp2);
	}
	add_vectors(var, var_tab);
}
