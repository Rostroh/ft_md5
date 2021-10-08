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

static int		check_flags(char c)
{
	const char	flags_tab[NB_FLG] = {'p', 'q', 'r', 's'};

	for (int i = 0; i < NB_FLG; i++)
	{
		if (c == flags_tab[i])
			return (i);
	}
	return (-1);
}

static int		pars_flags(t_data *info, char c)
{
	int			offset;
	int			*addr;
	const int	flg_offset[NB_FLG] = {0, 4, 8, 12};

	if ((offset = check_flags(c)) == -1)
	{
		info->flgs.err = c;
		return (-1);
	}
	addr = (int *)(&info->flgs);
	*(addr + offset) = 1;
	return (0);
}

static int		get_flags(t_data *info)
{
	int			j;

	for (int i = 2; i < info->nb_param; i++)
	{
		if (ft_strlen(info->param[i]) == 2 && ft_strncmp(info->param[i], "--", 2) == 0)
			break ;
		if (info->param[i][0] == '-')
		{
			j = 1;
			while (info->param[i][j])
			{
				if (pars_flags(info, info->param[i][j]) == -1)
					return (-1);
				j++;
			}
		}
		else
		{
			info->offset = i;
			return (0);
		}
	}
	return (0);
}

static void		print_data(t_data info)
{
	printf("STRUCT DATA:\ncmd_id: %d\n", info.cmd_id);
	printf("flgs:\n\tstd: %d\n\tquiet: %d\n\trev: %d\n\tstr: %d\n", info.flgs.std, info.flgs.quiet, info.flgs.rev, info.flgs.str);
	printf("offset: %d\nString: %s\n", info.offset, info.str);
}

int				main(int argc, char **argv)
{
	t_data		info;

	ft_bzero(&info, sizeof(info));
	info.offset = 2;
	info.str = NULL;
	info.nb_param = argc;
	info.param = argv;
	if (argc == 1)
		return (error_usage(argv[0]));
	if ((info.cmd_id = get_command_id(argv[1])) < 0)
		return (error_command(argv[0], argv[1]));
	if (get_flags(&info) == -1)
		return (error_flag(argv[0], info.flgs.err));
	print_data(info);
	return (0);
}
