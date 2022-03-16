#include "ft_ssl.h"

void		output(t_data info)
{
	char	*alg_name[2] = {"MD5", "SHA256"};

	if ((info.flgs & MASK_Q) == 0 && (info.flgs & MASK_R) == 0)
	{
		printf("%s ", alg_name[info.cmd_id]);
		if ((info.flgs & MASK_S) != 0)
			printf("(\"%s\") = ", info.str);
		else
			printf("(%s) = ", info.file);
	}
	fingerprint_output(info.fingprint);
	if ((info.flgs & MASK_Q) == 0 && (info.flgs & MASK_R) != 0)
	{
		if ((info.flgs & MASK_S) != 0)
			printf(" \"%s\"", info.str);
		else
			printf(" %s", info.file);
	}
	printf("\n");
}
