/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/14 21:14:43 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_spec(t_spec *spec, char **format, va_list ap)
{
	*spec = (t_spec) {0, 0, 0, 0, 0, 0, -1, 0, 0, 0};
	(*format)++;
	ft_handle_flags(spec, format);
	ft_handle_min_width(spec, format);
	ft_handle_precision(spec, format);
	ft_handle_type(spec, format);
	ft_get_arg_str(spec, ap);
	ft_handle_overrides(spec, spec->c);
}

void	ft_handle_type(t_spec *spec, char **format)
{
	int i;

	i = 0;
	while (ft_is_modifier(**format))
	{
		i++;
		(*format)++;
	}
	spec->mod = ft_strndup(*format - i, i);
	spec->c = *(*format)++;
	//else
	//{
	//	free(spec->mod);
	//	*spec = (t_spec) {0, 0, 0, 0, 0, 0, -1, 0, ' ', 0};
	//}
}

void	ft_handle_precision(t_spec *spec, char **format)
{
	if (**format != '.')
		return ;
	(*format)++;
	spec->precision = 0;
	while (ft_isdigit(**format))
	{
		spec->precision *= 10;
		spec->precision += **format - '0';
		(*format)++;
	}
}

void	ft_handle_min_width(t_spec *spec, char **format)
{
	while (ft_isdigit(**format))
	{
		spec->min_width *= 10;
		spec->min_width += **format - '0';
		(*format)++;
	}
}

void	ft_handle_flags(t_spec *spec, char **format)
{
	while (1)
	{
		if (**format == '+')
			spec->plus = 1;
		else if (**format == '-')
			spec->minus = 1;
		else if (**format == '#')
			spec->octo = 1;
		else if (**format == ' ')
			spec->space = 1;
		else if (**format == '0')
			spec->zero = 1;
		else
			return ;
		(*format)++;
	}
}
