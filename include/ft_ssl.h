#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

# define VERBOSE 0

# define MD5 0
# define SHA256 1

# define NB_FLG 4
# define NB_CMD 2

# define MASK_P 0b1
# define MASK_Q 0b10
# define MASK_R 0b100
# define MASK_S 0b1000

# define FLG_ERR -1
# define FLG_NONE 0
# define FLG_STOP 1
# define FLG_STR 2
# define FLG_ONGO 3
# define FLG_END 4
# define FLG_DONE 5
# define FLG_INIT -256

# define BUF_SIZE 64
# define BYTE_SIZE 32

# define A 0
# define B 1
# define C 2
# define D 3

# define E 4
# define F 5
# define G 6
# define H 7

//MD5 VECTORS
# define VEC_A 0x67452301
# define VEC_B 0xefcdab89
# define VEC_C 0x98badcfe
# define VEC_D 0x10325476


//SHA256 VECTORS
# define SHA_H0 0x6a09e667
# define SHA_H1 0xbb67ae85
# define SHA_H2 0x3c6ef372
# define SHA_H3 0xa54ff53a
# define SHA_H4 0x510e527f
# define SHA_H5 0x9b05688c
# define SHA_H6 0x1f83d9ab
# define SHA_H7 0x5be0cd19

# define MOD_Z 0x100000000

typedef struct	s_md5
{
	uint32_t	vector[4];
	uint32_t	m[16];
	uint32_t	f;
	uint32_t	g;
	uint32_t	fingprint[4];//x
}				t_md5;

typedef struct	s_sha256
{
	uint32_t	vector[8];
	uint32_t	m[64];
}				t_sha256;

# define MD5_MLEN 16
# define SHA_MLEN 64

# define MD5_VECN 4
# define SHA_VECN 8

typedef struct	s_hash
{
	//usage for MD5 only
	uint32_t	f;
	uint32_t	g;
	uint32_t	fingprint[4];
	//------------------
	uint32_t	m[SHA_MLEN];
	uint32_t	vector[SHA_VECN];
}				t_hash;

typedef struct	s_flg
{
	int			std;
	int			quiet;
	int			rev;
	int			str;
	char		err;			//error flag, do not try to use it
}				t_flg;

//NEED TO SPLIT THIS STRUCT IN 2 (1 data and one pars)
//data output var are marked with an x
typedef struct		s_data
{
	int				fd;
	int				cmd_id;
	//t_flg			flgs;
	uint8_t			flgs;
	char			flg_err;
	int				offset;
	int				len;
	char			*str;
	char			*file;
	unsigned char	*padding;
	int				nb_param;
	char			**param;
	uint32_t		fingprint[4];
}					t_data;

/*
 *	block_parser.c
*/
int			block_parser(t_data info);
void		print_byte(unsigned char c);

/*
 *	errors_input.c
*/
int			error_usage(char *prog_name);
int			error_command(char *prog_name, char *wrong_cmd);
int			error_flag(char *prog_name, char wrong_flg);
int			error_string(char *algo);
int			error_open(char *algo, char *name, int err);

/*
 *	flags.c
*/
int			get_flags(t_data *info, int pam_idx);

/*
 *	ft_md5.c
*/
void		md5(unsigned char *buf, t_data info, t_hash *var);
//int			setup_message(t_data *info, unsigned char *buf, int len);
//void		fingerprint_output(uint32_t *fingprint);
//int			ft_md5(t_data info);

/*
 *	ft_sha256.c
*/
void		sha256(unsigned char *buf, t_data info, t_hash *var);
//int			ft_sha256(t_data info);

/*
 *	dispencer.c
*/
int			dispencer(t_data info);

/*
 *	main.c
*/
void		print_data(t_data info);

/*
 *	md5_func.c
*/
void			round1(t_hash *var, int i);
void			round2(t_hash *var, int i);
void			round3(t_hash *var, int i);
void			round4(t_hash *var, int i);
/*
 *	output.c
*/
void		output(t_data info, t_hash var);

/*
 *	reader.c
*/
int			reader(t_data info, unsigned char *buffer, int file_offset);

/*
 *	utilities.c
*/
uint32_t	left_rot(uint32_t byte, int n);
uint32_t	right_rot(uint32_t byte, int n);
#endif
