/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:11:20 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/30 11:11:25 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_putchar_count(char c, int fd);
int	ft_putstr_count(char *s, int fd, int *count);
int	ft_putnbr_count(int n, int fd, int *count);
int	ft_printf(const char *p, ...);
int	memory(void	*str, int *count);
int	convert(unsigned long num, int base, int *count, char *cases);
int	ft_unsigned_nbr(unsigned int n, int fd, int *count);

#endif
