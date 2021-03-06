/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:09:01 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 12:49:42 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				mat_trans(t_vec v, t_mat **m)
{
	t_mat			*i;
	t_mat			*tmp;

	i = mat_identity();
	mat_set_col(i, 4, 3, v.x, v.y, v.z);
	tmp = mat_mult((*m), i);
	(*m) = tmp;
}

float				*mat_to_float(t_mat *m)
{
	int				i;
	int				x;
	int				y;
	float			*f;

	f = malloc(sizeof(float) * m->width * m->height);
	if (!f)
		return (NULL);
	x = 1;
	i = 0;
	while (x <= m->width)
	{
		y = 1;
		while (y <= m->height)
		{
			f[i++] = m->array[(y - 1) * m->width + x - 1];
			y++;
		}
		x++;
	}
	return (f);
}

void				mat_set(t_mat *m, int x, int y, float val)
{
	if (m == NULL || x > m->width || y > m->height)
		return ;
	m->array[m->width * (y - 1) + (x - 1)] = val;
}

void				mat_set_col(t_mat *m, int y, int ac, ...)
{
	int				i;
	int				x;
	float			tmp;
	va_list			ap;

	if (m == NULL || ac == 0 || ac > m->height)
		return ;
	i = 0;
	va_start(ap, ac);
	while (i < ac)
	{
		tmp = va_arg(ap, double);
		x = i + 1 % m->height;
		m->array[m->width * (x - 1) + (y - 1)] = tmp;
		i++;
	}
	va_end(ap);
}

void				mat_set_row(t_mat *m, int x, int ac, ...)
{
	int				i;
	int				y;
	float			tmp;
	va_list			ap;

	if (m == NULL || ac == 0 || ac > m->width)
		return ;
	i = 0;
	va_start(ap, ac);
	while (i < ac)
	{
		tmp = va_arg(ap, double);
		y = i + 1 % m->height;
		m->array[m->width * (x - 1) + (y - 1)] = tmp;
		i++;
	}
	va_end(ap);
}
