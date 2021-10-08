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

	if ((offset = check_flags(c)) == -1)
	{
		info->flgs.err = c;
		return (-1);
	}
	addr = (int *)(&info->flgs);
	*(addr + offset) = 1;
	return (0);
}

int		get_flags(t_data *info, int pam_idx)
{
	int			i;
	int			flg_idx;

	i = 1;
	if (ft_strlen(info->param[pam_idx]) == 2 && ft_strncmp(info->param[pam_idx], "--", 2) == 0)
		return (FLG_STOP);
	info->flgs.str = 0;
	if (info->param[pam_idx][0] == '-')
	{
		while (info->param[pam_idx][i])
		{	
			if ((flg_idx = pars_flags(info, info->param[pam_idx][i])) == -1)
				return (FLG_ERR);
			i++;
			if (info->flgs.str == 1 && i < ft_strlen(info->param[pam_idx]))	//if string flag
			{
				info->str = info->param[pam_idx] + i;
				return (FLG_STR);
			}
		}
		return (FLG_DONE);
	}
	return (FLG_NONE);
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
	static int		(*command[NB_CMD])(t_data info) = {&ft_md5};

	ft_bzero(&info, sizeof(info));
	info.offset = 2;
	info.str = NULL;
	info.nb_param = argc;
	info.param = argv;
	if (argc == 1)
		return (error_usage(argv[0]));
	if ((info.cmd_id = get_command_id(argv[1])) < 0)
		return (error_command(argv[0], argv[1]));
	command[info.cmd_id](info);
	/*if (get_flags(&info) == -1)
		return (error_flag(argv[0], info.flgs.err));
	print_data(info);*/
	return (0);
}
