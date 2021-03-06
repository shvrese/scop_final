/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 10:16:09 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 17:50:14 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int			parse_triangle_v(char *l, int *v, size_t n, t_obj **o)
{
	static int		c;

	if (sscanf(l, "%d/%d/%d%*c%n", &v[0], &v[1], &v[2], &c) == 3)
	{
		push('i', &v[0], ++(*o)->v_index_size, (void **)&(*o)->v_index);
		push('i', &v[1], ++(*o)->vt_index_size, (void **)&(*o)->vt_index);
		push('i', &v[2], ++(*o)->vn_index_size, (void **)&(*o)->vn_index);
	}
	else if (sscanf(l, "%d/%d%*c%n", &v[0], &v[1], &c) == 2)
	{
		push('i', &v[0], ++(*o)->v_index_size, (void **)&(*o)->v_index);
		push('i', &v[1], ++(*o)->vt_index_size, (void **)&(*o)->vt_index);
	}
	else if (sscanf(l, "%d%*c%n", &v[0], &c) == 1)
		push('i', &v[0], ++(*o)->v_index_size, (void **)&((*o)->v_index));
	else if (sscanf(l, "%d//%d%*c%n", &v[0], &v[1], &c) == 2)
	{
		push('i', &v[0], ++(*o)->v_index_size, (void **)&(*o)->v_index);
		push('i', &v[1], ++(*o)->vn_index_size, (void **)&(*o)->vn_index);
	}
	(*o)->f[(*o)->f_size - 1][n] = v[0];
	(*o)->p_size += 3;
	return (c);
}

static int			parse_face(char *l, t_obj **o)
{
	int				tmp[4];
	int				i;
	int				ret;
	size_t			n;

	l += 2;
	ret = 0;
	i = 0;
	n = 0;
	(*o)->f = realloc((*o)->f, sizeof(int *) * (int)++(*o)->f_size);
	(*o)->f[(*o)->f_size - 1] = malloc(sizeof(int) * 5);
	(*o)->f[(*o)->f_size - 1][3] = -1;
	(*o)->f[(*o)->f_size - 1][4] = -1;
	while (*l)
	{
		if (i == 3)
			(*o)->p_size += 6;
		if (i > 3)
			return (-1);
		else
			ret = parse_triangle_v(l, tmp, n++, o);
		l += ret;
		i++;
	}
	return (1);
}

static int			parse_v(char *l, t_obj **o)
{
	float			tmp[3];
	t_vec			***v;
	t_vec			v_ret;

	if (sscanf(l, "%*s%f %f %f", &tmp[0], &tmp[1], &tmp[2]) == 3)
	{
		if (strncmp(l, "v ", 2) == 0)
			v = &((*o)->v);
		else if (strncmp(l, "vn", 2) == 0)
			return (-1);
		else if (strncmp(l, "vt", 2) == 0)
			return (-1);
		else
			return (-1);
		v_ret.x = tmp[0];
		v_ret.y = tmp[1];
		v_ret.z = tmp[2];
		push_vec(v_ret, ++(*o)->v_size, v);
		return (1);
	}
	return (-1);
}

static int			parse_obj_loop(FILE *f, t_obj **o)
{
	static int		ret = -1;
	char			line[256];

	while (fgets(line, sizeof(line), f))
	{
		if (line[0] == 'o')
			ret = sscanf(line, "%*s %s", (*o)->name);
		else if (line[0] == 'm')
		{
			(*o)->mtllib = malloc(sizeof(char) * 256);
			ret = sscanf(line, "%*s %s", (*o)->mtllib);
		}
		else if (line[0] == 's')
			ret = sscanf(line, "%*s %s", (*o)->lighting);
		else if (line[0] == 'v')
			ret = parse_v(line, o);
		else if (line[0] == 'u' && !(*o)->mtl)
		{
			(*o)->mtl_name = malloc(sizeof(char) * 256);
			ret = sscanf(line, "%*s %s", (*o)->mtl_name);
		}
		else if (line[0] == 'f')
			ret = parse_face(line, o);
	}
	return (ret);
}

int					parse_obj(char *file, t_obj **o)
{
	static int		ret = -1;
	FILE			*f;
	char			*ext;

	ext = strrchr(file, '.');
	if (!ext || strcmp(ext, ".obj") != 0)
		return (ret);
	if ((f = fopen(file, "r")))
	{
		*o = malloc(sizeof(t_obj));
		init_obj_infos(file, o);
		ret = parse_obj_loop(f, o);
	}
	return (ret);
}
