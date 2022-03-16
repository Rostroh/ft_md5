#include "ft_ssl.h"

int				error_usage(char *prog_name)
{
	ft_printf("Usage: ./%s command [flags] [file/string]\n", prog_name);
	return (0);
}

static void		display(void)
{
	const char	flags_tab[NB_FLG] = {'p', 'q', 'r', 's'};
	const char	*command_tab[NB_CMD] = {"md5"};

	ft_putstr("\nCommands:\n");
	for (int i = 0; i < NB_CMD; i++)
		ft_printf("%s\n", command_tab[i]);
	ft_putstr("\nFlags:\n");
	for (int i = 0; i < NB_FLG; i++)
		ft_printf("-%c ", flags_tab[i]);
	ft_putstr("\n");
}

int				error_command(char *prog_name, char *wrong_cmd)
{	
	ft_printf("%s: Error: '%s' is an invalid command.\n", prog_name, wrong_cmd);
	display();
	return (0);
}

int				error_flag(char *prog_name, char wrong_flg)
{
	ft_printf("%s: illegal option -- %c\n", prog_name, wrong_flg);
	display();
	return (0);
}

int				error_string(char *algo)
{
	const char	flags_tab[NB_FLG] = {'p', 'q', 'r', 's'};
	
	ft_printf("%s: option requires an argument -- s\n", algo);
	ft_printf("usage: %s [-", algo);
	for (int i = 0; i < NB_FLG - 1; i++)
		ft_putchar(flags_tab[i]);
	ft_putstr("] [-s string] [files ...]\n");
	return (-1);
}

int				error_open(char *algo, char *name, int err)
{
	if (err == -1)
		printf("%s: %s: No such or directory\n", algo, name);
	else
		printf("err = %d\n", err);
	return (-1);
}
