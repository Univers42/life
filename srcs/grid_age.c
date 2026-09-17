/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_age.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:27:50 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/17 15:27:52 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	age_reset(t_grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->width * grid->height)
	{
		if (grid->cells[i])
			grid->age[i] = 1;
		else
			grid->age[i] = 0;
		i++;
	}
}

int	next_age(t_grid *grid, int idx, int alive, int next)
{
	int	age;

	if (!next)
		return (0);
	if (alive)
		age = grid->age[idx] + 1;
	else
		age = 1;
	if (age > MAX_AGE)
		age = MAX_AGE;
	return (age);
}
