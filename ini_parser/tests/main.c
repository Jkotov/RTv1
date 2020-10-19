#include <stdio.h>
#include <stdlib.h>
#include "ini_parser.h"
#include "libft.h"

void	print_blocks_name(t_block *block)
{
	t_block	*tmp;

	tmp = block;
	while (tmp != NULL)
	{
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
}

void	print_block_pairs(t_block *block)
{
	t_string_pair 	*tmp;

	tmp = block->pairs;
	while (tmp != NULL)
	{
		ft_putstr(tmp->key);
		ft_putchar('=');
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
}

void	print_block(t_block *block, const char *name)
{
	t_block	*tmp;

	tmp = block;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			ft_putendl(name);
			print_block_pairs(tmp);
		}
		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	t_block	*res;

	ini_parser(argv[argc - 1], &res);
//	print_blocks_name(res);
	while(res->next)
	{
//		ft_putendl(res->name);
		print_block(res, res->name);
		res = res->next;
	}
	print_block(res, res->name);
	res = res->next;
	cleanup_ini(res);
	return 0;
}
