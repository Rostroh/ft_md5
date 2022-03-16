#include "ft_ssl.h"

static int		get_command_id(char *string)
{
	const int	command_len[NB_CMD] = {3, 6};
	const char	*command_tab[NB_CMD] = {"md5", "sha256"};

	for (int i = 0; i < NB_CMD; i++)
	{
		if (ft_strncmp(string, command_tab[i], command_len[i]) == 0)
			return (i);
	}
	return (-1);
}

void			print_data(t_data info)
{
	printf("STRUCT DATA:\ncmd_id: %d\n", info.cmd_id);
	//printf("flgs:\n\tstd: %d\n\tquiet: %d\n\trev: %d\n\tstr: %d\n", info.flgs.std, info.flgs.quiet, info.flgs.rev, info.flgs.str);
	printf("offset: %d\nString: %s\n", info.offset, info.str);
	printf("file = %s, str = %s\n", info.file, info.str);
}

int				main(int argc, char **argv)
{
	t_data		info;
	static int		(*command[NB_CMD])(t_data *info) = {&ft_md5, &ft_sha256};

	ft_bzero(&info, sizeof(info));
	info.fd = 0;
	info.offset = 2;
	info.len = 0;
	info.str = NULL;
	info.nb_param = argc;
	info.param = argv;
	info.flgs = 0;
	if (argc == 1)
		return (error_usage(argv[0]));
	if ((info.cmd_id = get_command_id(argv[1])) < 0)
		return (error_command(argv[0], argv[1]));
	//if (get_flags(&info, 2) == FLG_ERR)
	//	return (error_flag(argv[0], info.flgs.err));
	if (VERBOSE)
		print_data(info);
//	printf("En vie %d\n", info.flgs);
	dispencer(info, command[info.cmd_id]);
	//command[info.cmd_id](info);
	return (0);
}
