/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:05:19 by rtorres           #+#    #+#             */
/*   Updated: 2024/08/29 11:44:46 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (av[i][0] == '-')
			return (1);
		else if (av[i][0] == '+')
			j++;
		if (!ft_isdigit(av[i][j + 1]))
			return (1);
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
		}
	}
	return (0);
}

static int	check_num(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "21478368", 10) >= 0)
		return (1);
	return (0);
}

static int	valid_args(int ac, char **av)
{
	int	i;

	if (check_args(ac, av))
		return (1);
	i = 0;
	while (++i < ac)
	{
		if (check_num(av[i]))
			return (1);
	}
	return (0);
}

static void	init(t_simulation *sim)
{
	int	i;

	sim->dead = 0;
	sim->full = 0;
	sim->ph = (t_philosopher *)malloc(sim->n_philo * sizeof(t_philosopher));
	i = -1;
	while (++i < sim->n_philo)
	{
		sim->ph[i].id = i + 1;
		sim->ph[i].sim = sim;
		sim->ph[i].m_eaten = 0;
		if (i + 1 == sim->n_philo)
			sim->ph[i].next = &sim->ph[0];
		else
			sim->ph[i].next = &sim->ph[i + 1];
		if (i == 0)
			sim->ph[i].prev = &sim->ph[sim->n_philo - 1];
		else
			sim->ph[i].prev = &sim->ph[i - 1];
		pthread_mutex_init(&sim->ph[i].fork, NULL);
	}
	pthread_mutex_init(&sim->print_mutex, NULL);
	pthread_mutex_init(&sim->check, NULL);
}

int	parse_args(int ac, char **av, t_simulation *sim)
{
	if (valid_args(ac, av))
		return (1);
	sim->n_philo = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->n_meal = -1;
	if (ac == 6)
		sim->n_meal = ft_atoi(av[5]);
	init(sim);
	return (0);
}
