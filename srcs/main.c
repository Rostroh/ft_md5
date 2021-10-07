#include "ft_ssl.h"

static int		get_command_id(char *string)
{
	const int	command_len[NB_CMD] = {3};
	const char	*command_tab[NB_CMD] = {"md5"};

	for (int i = 0; i < NB_CMD; i++)
	{
		if (ft_strncmp(string, command_tab[i], command_len[i]) == 0)
			return (i);
	}
	return (-1);
}

static int		get_flags(t_data *info)
{
	const char	flags_tab[NB_FLG] = {'-', 'p', 'q', 'r', 's'};

	for (int i = 2; i < info->nb_param; i++)
	{
		printf("%s\n", info->param[i]);
		if (info->param[i][0] == '-')
			continue ;	//CHECK NEXT CHARS FOR FLAGS
		else
		{
			printf("LOL\n");
			info->offset = i;
			return (0);
		}
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_data		info;

	info.offset = 2;
	info.nb_param = argc;
	info.param = argv;
	if (argc == 1)
		return (error_usage(argv[0]));
	if ((info.cmd_id = get_command_id(argv[1])) < 0)
		return (error_command(argv[0], argv[1]));
	ft_printf("Hello world %d\n", info.cmd_id);
	if (get_flags(&info) == -1)
		return (error_flag(argv[0], info.flgs.err));
	ft_printf("%d\n", info.offset);
	return (0);
}
