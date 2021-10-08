#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

# define NB_FLG 4
# define NB_CMD 1

# define FLG_ERR -1
# define FLG_NONE 0
# define FLG_STOP 1
# define FLG_STR 2
# define FLG_DONE 3
# define FLG_INIT -256

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
 *	errors_input.c
*/
int		error_usage(char *prog_name);
int		error_command(char *prog_name, char *wrong_cmd);
int		error_flag(char *prog_name, char wrong_flg);

/*
 *	flags.c
*/
int		get_flags(t_data *info, int pam_idx);
/*
 *	ft_md5.c
*/
int		ft_md5(t_data info);

/*
 *	dispencer.c
*/
void	dispencer(t_data info);

#endif
