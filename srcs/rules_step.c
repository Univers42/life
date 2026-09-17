/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:35:02 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:35:02 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	count_neighbors(t_grid *grid, int x, int y)
{
	int	count;
	int	dx;
	int	dy;

	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if ((dx != 0 || dy != 0) && grid_get(grid, x + dx, y + dy))
				count++;
			dx++;
		}
		dy++;
	}
	return (count);
}

int	next_state(t_rule *rule, int alive, int neighbors)
{
	if (alive)
		return (rule->survive[neighbors]);
	return (rule->born[neighbors]);
}

static void	compute_cell(t_worker *w, int x, int y)
{
	t_grid	*grid;
	int		idx;
	int		alive;
	int		next;

	grid = &w->game->grid;
	idx = y * grid->width + x;
	alive = grid_get(grid, x, y);
	next = next_state(&w->game->rule, alive, count_neighbors(grid, x, y));
	if (next && !alive)
		w->births++;
	else if (!next && alive)
		w->deaths++;
	grid->next[idx] = next;
	grid->age_next[idx] = next_age(grid, idx, alive, next);
}

static void	compute_row(t_worker *w, int y)
{
	int	x;

	x = 0;
	while (x < w->game->grid.width)
	{
		compute_cell(w, x, y);
		x++;
	}
}

void	compute_rows(t_worker *w)
{
	int	y;

	w->births = 0;
	w->deaths = 0;
	y = w->y_start;
	while (y < w->y_end)
	{
		compute_row(w, y);
		y++;
	}
}
