#include "ft_ssl.h"

static int		get_next_arg(t_data *info, int index)
{
	if (index + 1  >= info->nb_param && (info->flgs & MASK_S) != 0)
			return (error_string("md5"));
	if ((info->flgs & MASK_S) != 0)
		info->str = info->param[index + 1];
	else
		info->file = info->param[index];
	return (1);
}
/*
void		iteration(t_data info, int command(t_data info))
{
	int		iter;
	char	*buf;
	int		file_off;

	iter = 0;
	file_off = 0;
	buf = (char *)malloc(sizeof(char) * BUF_SIZE);
	while (iter != 0)
	{
		ft_bzero(buf, BUF_SIZE);
		iter = reader(info, buf, file_off * BUF_SIZE);
		printf("\nat %d: %s\n\n", file_off, buf);
		file_off++;
	}
}*/

int			dispencer(t_data info, int command(t_data *info))
{
	int		stop;
	uint32_t	*finger_print;

	if (info.offset == info.nb_param)
		command(&info);
	for (int i = info.offset; i < info.nb_param; i++)
	{
		stop = FLG_INIT;
	//	printf("i = %d\n", i);
//		printf("iteration [%d] : processing %s\n", i, info.param[i]);
		if (stop != FLG_STOP && stop != FLG_NONE)
		{
			//printf("En vie v2 %d\n", info.flgs);
			switch (stop = get_flags(&info, i))
			{
				case FLG_ERR:
					printf("flg error\n");
					return (error_flag(info.param[0], info.flg_err));
				case FLG_STR:
				//	printf("flg str %s\n", info.str);
					command(&info);
					break ;
				case FLG_ONGO:
		//			printf("flg done\n");
					if ((info.flgs & MASK_P) != 0)
					{
						command(&info);
						info.flgs ^= MASK_P;
					}
					if ((info.flgs & MASK_S) != 0)
					{
				//	printf("CALL MD5\n");
						if ((i += get_next_arg(&info, i)) == -1)
							return (-1);
				//	printf("fl str %s i = %d\n", info.str, i);
						command(&info);
					}
					break ;/*
				case FLG_NONE:
					printf("Vroom\n");
					command(&info);
					break ;*/
				default:
		//			printf("En vie v3 %d\n", info.flgs);
					info.file = info.param[i];
					if ((info.fd = open(info.file, O_RDONLY)) < 0)
						error_open("md5", info.file, info.fd);
					else
					{
						//printf("default %d\n", stop);
						//i += get_next_arg(&info, i);
						command(&info);
					}
					break ; 
			}
		}
		else
		{
			printf("Un cas a gerer\n");
		}
	}/*
	if (!info.file)
	{
		//printf("Duh\n");
		command(&info);
	}*/
	return (0);


}
