#include "ft_ssl.h"

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
		info->flg_err = c;
		return (-1);
	}
	//printf("%c %d\n", c, info->flgs);
	info->flgs |= (MASK_P << offset);
	//addr = (int *)(&info->flgs);
	//*(addr + offset) = 1;
	return (0);
}

int				get_flags(t_data *info, int pam_idx)
{
	int			i;
	int			flg_idx;
	int			flg;

	flg = 0;
	if (ft_strlen(info->param[pam_idx]) == 2 && ft_strncmp(info->param[pam_idx], "--", 2) == 0)
		return (FLG_STOP);
	if ((info->flgs & MASK_S) != 0)
		info->flgs ^= MASK_S;
	if (info->param[pam_idx][0] == '-')
	{
		i = 1;
		while (info->param[pam_idx][i])
		{	
			if ((flg_idx = pars_flags(info, info->param[pam_idx][i])) == -1)
				return (FLG_ERR);
			i++;
			if ((info->flgs & MASK_S) != 0 && i < ft_strlen(info->param[pam_idx]))	//if string flag
			{
				info->str = info->param[pam_idx] + i;
				return (FLG_STR);
			}
		}
		pam_idx++;
		return (FLG_ONGO);
	}
	//return (FLG_NONE);
	return (info->flgs == 0 ? FLG_NONE : FLG_DONE);
	//return (flg ? FLG_DONE : FLG_DONE);
}
