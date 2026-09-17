/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:28:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/17 15:28:03 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static int	stop_color(int index)
{
	int	stops[AGE_STOPS];

	stops[0] = AGE_COLOR_0;
	stops[1] = AGE_COLOR_1;
	stops[2] = AGE_COLOR_2;
	stops[3] = AGE_COLOR_3;
	stops[4] = AGE_COLOR_4;
	stops[5] = AGE_COLOR_5;
	return (stops[index]);
}

static int	lerp_channel(int from, int to, int step, int span)
{
	return (from + (to - from) * step / span);
}

static int	lerp_color(int c1, int c2, int step, int span)
{
	int	r;
	int	g;
	int	b;

	r = lerp_channel((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, step, span);
	g = lerp_channel((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, step, span);
	b = lerp_channel(c1 & 0xFF, c2 & 0xFF, step, span);
	return ((r << 16) | (g << 8) | b);
}

int	age_color(int age)
{
	int	span;
	int	seg;
	int	step;

	if (age <= 0)
		return (COLOR_DEAD);
	if (age >= MAX_AGE)
		return (stop_color(AGE_STOPS - 1));
	span = MAX_AGE / (AGE_STOPS - 1);
	seg = (age - 1) / span;
	if (seg > AGE_STOPS - 2)
		seg = AGE_STOPS - 2;
	step = (age - 1) - seg * span;
	return (lerp_color(stop_color(seg), stop_color(seg + 1), step, span));
}
