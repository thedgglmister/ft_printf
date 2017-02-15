/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/14 21:09:07 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_get_arg_str(t_spec *spec, va_list ap)
{
	char c;
	char *mod;

	c = spec->c;
	mod = spec->mod;
	if (ft_tolower(c) == 'd' || c == 'i')
		ft_get_di_str(spec, ap, c, mod);
	else if (ft_is_diouxb(c))
		ft_get_ouxb_str(spec, ap, c, mod);
	else if (ft_tolower(c) == 'c')
		ft_get_c_str(spec, ap, c, mod);
	else if (ft_tolower(c) == 's')
		ft_get_s_str(spec, ap, c, mod);
	else if (c == 'p')
		spec->str = ft_itoa_base((uintmax_t)va_arg(ap, void*), 16, 0);
	else if (c == '%')
		spec->str = ft_strdup("%");
	else
		spec->str = ft_memset(ft_strnew(1), spec->c, 1);
}

void	ft_get_di_str(t_spec *spec, va_list ap, char c, char *mod)
{
	if (ft_strequ(mod, "l") || c == 'D')
		spec->str = ft_itoa(va_arg(ap, long));
	else if (ft_strequ(mod, "ll"))
		spec->str = ft_itoa(va_arg(ap, long long));
	else if (ft_strequ(mod, "hh"))
		spec->str = ft_itoa((char)va_arg(ap, int));
	else if (ft_strequ(mod, "h"))
		spec->str = ft_itoa((short)va_arg(ap, int));
	else if (ft_strequ(mod, "j"))
		spec->str = ft_itoa(va_arg(ap, intmax_t));
	else if (ft_strequ(mod, "z"))
		spec->str = ft_itoa(ft_get_signed_size_t(ap));
	else
		spec->str = ft_itoa(va_arg(ap, int));
}

void	ft_get_ouxb_str(t_spec *spec, va_list ap, char c, char *mod)
{
	uintmax_t int_arg;

	if (ft_strequ(mod, "l") || c == 'O' || c == 'U')
		int_arg = va_arg(ap, unsigned long);
	else if (ft_strequ(mod, "ll"))
		int_arg = va_arg(ap, unsigned long long);
	else if (ft_strequ(mod, "hh"))
		int_arg = (unsigned char)va_arg(ap, int);
	else if (ft_strequ(mod, "h"))
		int_arg = (unsigned short)va_arg(ap, int);
	else if (ft_strequ(mod, "j"))
		int_arg = va_arg(ap, uintmax_t);
	else if (ft_strequ(mod, "z"))
		int_arg = va_arg(ap, size_t);
	else
		int_arg = va_arg(ap, unsigned int);
	if (ft_tolower(c) == 'u')
		spec->str = ft_itoa_base(int_arg, 10, 0);
	else if (ft_tolower(c) == 'o')
		spec->str = ft_itoa_base(int_arg, 8, 0);
	else if (spec->c == 'b')
		spec->str = ft_itoa_base(int_arg, 2, 0);
	else
		spec->str = ft_itoa_base(int_arg, 16, (c == 'X'));
}

void	ft_get_c_str(t_spec *spec, va_list ap, char c, char *mod)
{
	wchar_t	*temp_wc_str;

	if ((ft_strequ(mod, "l") || c == 'C') && MB_CUR_MAX > 1)
	{
		if (!(temp_wc_str = (wchar_t *)malloc(sizeof(wchar_t) * 2)))
			ft_crash();
		temp_wc_str[0] = va_arg(ap, wchar_t);
		temp_wc_str[1] = 0;
		spec->str = ft_to_multibyte(temp_wc_str);
		free(temp_wc_str);
	}
	else
		spec->str = ft_memset(ft_strnew(1), (unsigned char)va_arg(ap, int), 1);
}

void	ft_get_s_str(t_spec *spec, va_list ap, char c, char *mod)
{
	if (ft_strequ(mod, "l") || c == 'S')
		spec->str = ft_to_multibyte(va_arg(ap, wchar_t*));
	else
		spec->str = ft_strdup(va_arg(ap, char*));
	if (!spec->str)
		spec->str = ft_strdup("(null)");
}
