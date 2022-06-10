#include "ft_ssl.h"

uint32_t		calc_k(uint32_t i)
{
	return (fabs(sin(i + 1)) * pow(2, 32));
}

void			switch_vec(t_hash *var, uint32_t byte)
{
	var->vector[A] = var->vector[D];
	var->vector[D] = var->vector[C];
	var->vector[C] = var->vector[B];
	var->vector[B] = byte;
}

void			init_vec(t_hash *vars)
{
	vars->vector[A] = vars->fingprint[A];
	vars->vector[B] = vars->fingprint[B];
	vars->vector[C] = vars->fingprint[C];
	vars->vector[D] = vars->fingprint[D];
}

void			md5(unsigned char *buf, t_data info, t_hash *var)
{
	uint32_t		byte;
	static void		(*round[4])(t_hash *var, int i) = {&round1, &round2, &round3, &round4};
	static int		shift[4][4] = {{7, 12, 17, 22}, {5, 9, 14, 20}, {4, 11, 16, 23}, {6, 10, 15, 21}};

	init_vec(var);
//	setup_m(var, buf);
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
