#include "ft_ssl.h"

static uint32_t		function_f(t_hash var)
{
	return ((var.vector[B] & var.vector[C]) | (~var.vector[B] & var.vector[D]));
}

void				round1(t_hash *var, int i)
{
	var->f = function_f(*var);
	var->g = i;
}

static uint32_t		function_g(t_hash var)
{
	return ((var.vector[B] & var.vector[D]) | (var.vector[C] & ~var.vector[D]));
}

void				round2(t_hash *var, int i)
{
	var->f = function_g(*var);
	var->g = (i * 5 + 1) % 16;
}

static uint32_t		function_h(t_hash var)
{
	return (var.vector[B] ^ var.vector[C] ^ var.vector[D]);
}

void				round3(t_hash *var, int i)
{
	var->f = function_h(*var);
	var->g = (i * 3 + 5) % 16;
}

static uint32_t		function_i(t_hash var)
{
	return (var.vector[C] ^ (var.vector[B] | ~var.vector[D]));
}

void				round4(t_hash *var, int i)
{
	var->f = function_i(*var);
	var->g = (i * 7) % 16;
}
