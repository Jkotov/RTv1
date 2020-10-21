/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 05:08:36 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 16:27:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INI_PARSER_H
# define INI_PARSER_H
# define SUCCESS 0
# define FILE_ERROR -1
# define MALLOC_ERROR -2
# define UNKNOWN_ERROR -3

typedef struct				s_string_pair
{
	char					*key;
	char					*value;
	struct s_string_pair	*next;
}							t_string_pair;

typedef struct				s_block
{
	char					*name;
	t_string_pair			*pairs;
	struct s_block			*next;
}							t_block;

void						parse_error(int code);
int							ini_parser(char	*file_name, t_block **res);
void						cleanup_ini(t_block *ini);
char						*find_value(char *key, t_block *block);
#endif
