#include "ft_ssl.h"

int			ft_md5(t_data info)
{
	int		stop;

	stop = FLG_INIT;
	printf("Md5!\n");
	for (int i = info.offset; i < info.nb_param; i++)
	{
		if (stop != FLG_STOP && stop != FLG_NONE)
		{
			if ((stop = get_flags(&info, i)) == -1)
				return (error_flag(info.param[0], info.flgs.err));
			else if (stop == FLG_STR)
				printf("On est sur une string (%s)\n", info.str);
			else if (stop == FLG_DONE && info.flgs.str == 1)
				printf("On est sur une string (the next one)\n");
			else if (stop == FLG_DONE)
				printf("On est sur un flag\n");
			else if (stop == FLG_NONE)
				printf("On est sur un file\n");
		}
	}
	return (0);
}
