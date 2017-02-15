/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/14 18:55:08 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_spec	spec;
	int		char_count;

	va_start(ap, format);
	char_count = 0;
	while (*format)
	{
		while (*format && *format != '%')
		{
			write(1, format++, 1);
			char_count++;
		}
		if (!*format)
			break ;
		ft_parse_spec(&spec, (char **)&format, ap);
		char_count += ft_print_spec(&spec);
		free(spec.mod);
		free(spec.str);
	}
	va_end(ap);
	return (char_count);
}
