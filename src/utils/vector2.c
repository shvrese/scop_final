/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 12:51:36 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 12:51:50 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec				*vec_offset(t_vec *v1, t_vec *v2)
{
	t_vec			*v;

	v = vec_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (v);
}