#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

# define NB_FLG 4
# define NB_CMD 1

typedef struct	s_flg
{
	int			std;
	int			quiet;
	int			rev;
	int			str;
	char		err;			//error flag, do not try to use it
}				t_flg;

typedef struct	s_data
{
	int			cmd_id;
	t_flg		flgs;
	int			offset;
	char		*str;
	int			nb_param;
	char		**param;
}				t_data;

/*
 * errors_input.c
*/
int		error_usage(char *prog_name);
int		error_command(char *prog_name, char *wrong_cmd);
int		error_flag(char *prog_name, char wrong_flg);
#endif
