/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/14 12:07:27 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//need to store a pointer to the % every time i handel specifier, so if there is a mistake it just translates it into regualr string and writes it, like %hhhd

#include "ft_printf.h"




int	ft_printf(const char *format, ...)
{
	va_list ap;
	t_spec spec;
	int char_count;

	va_start(ap, format);
	char_count = 0;
	while (*format)//rework this logic
	{
		while (*format && *format != '%')// print until % or NUL
		{
			write(1, format++, 1);
			char_count++;
		}
		if (!*format)
			break;
		ft_parse_spec(&spec, (char **)&format, ap);//gets all info on specifier, validates?
		char_count += ft_print_spec(&spec);
	}




	va_end(ap);

	return (char_count);
}







void	ft_get_arg_str(t_spec *spec, va_list ap)
{
	char c;
	c = spec->c;

	uintmax_t int_arg;


	if (ft_tolower(c) == 'd' || c == 'i')
	{		
		if (ft_strequ(spec->mod, "l") || c == 'D')
			spec->str = ft_itoa(va_arg(ap, long));
		else if (ft_strequ(spec->mod, "ll"))
			spec->str = ft_itoa(va_arg(ap, long long));
		else if (ft_strequ(spec->mod, "hh"))
			spec->str = ft_itoa((char)va_arg(ap, int));
		else if (ft_strequ(spec->mod, "h"))
			spec->str = ft_itoa((short)va_arg(ap, int));
		else if (ft_strequ(spec->mod, "j"))
			spec->str = ft_itoa(va_arg(ap, intmax_t));
		else if (ft_strequ(spec->mod, "z"))
			spec->str = ft_itoa(va_arg(ap, size_t)); ////////
		else 
			spec->str = ft_itoa(va_arg(ap, int));
	}


	else if (ft_tolower(c) == 'u' || ft_tolower(c) == 'o' || ft_tolower(c) == 'x')
	{
		if (ft_strequ(spec->mod, "l") || c == 'O' || c == 'U')
			int_arg = va_arg(ap, unsigned long);
		else if (ft_strequ(spec->mod, "ll"))
			int_arg = va_arg(ap, unsigned long long);
		else if (ft_strequ(spec->mod, "hh"))
			int_arg = (unsigned char)va_arg(ap, int);
		else if (ft_strequ(spec->mod, "h"))
			int_arg = (unsigned short)va_arg(ap, int);
		else if (ft_strequ(spec->mod, "j"))
			int_arg = va_arg(ap, uintmax_t);
		else if (ft_strequ(spec->mod, "z"))
			int_arg = va_arg(ap, size_t);
		else 
			int_arg = va_arg(ap, unsigned int);

		if (ft_tolower(c) == 'u')
			spec->str = ft_itoa_base(int_arg, 10, 0);
		else if (ft_tolower(c) == 'o')
			spec->str = ft_itoa_base(int_arg, 8, 0);//add flag to indicate upper or lower case a-f
		else if (c == 'x')
			spec->str = ft_itoa_base(int_arg, 16, 0);
		else 
			spec->str = ft_itoa_base(int_arg, 16, 1);
	}


	else if (ft_tolower(c) == 'c')
	{
		if (ft_strequ(spec->mod, "l") || c == 'C')
		{
			if (!(spec->str = (char *)malloc(sizeof(wchar_t))))/////
				ft_crash();
			*(wchar_t*)spec->str = va_arg(ap, wchar_t); ////huh unicode what ?????????
		}
		else
			spec->str = ft_memset(ft_strnew(1), (unsigned char)va_arg(ap, int), 1);
	}









	else if (ft_tolower(c) == 's')
	{
		if (ft_strequ(spec->mod, "l") || c == 'S')
			spec->str = ft_to_multibyte(va_arg(ap, wchar_t*));
		else
			spec->str = ft_strdup(va_arg(ap, char*));
		if (!spec->str)
		   spec->str = ft_strdup("(null)");
	}




	else if (c == 'p')
		spec->str = ft_itoa_base((uintmax_t)va_arg(ap, void*), 16, 0);

	else if (c == '%')
		spec->str = ft_strdup("%");


}


































void	ft_parse_spec(t_spec *spec, char **format, va_list ap)//need to add validation, deal with %%
{
	*spec = (t_spec) {0, 0, 0, 0, 0, 0, -1, 0, 0, 0};
	(*format)++;
	ft_handle_flags(spec, format);
	ft_handle_min_width(spec, format);
	ft_handle_precision(spec, format);
	ft_handle_type(spec, format);
	ft_get_arg_str(spec, ap);
//printf("str: %s\n", spec->str);
	ft_handle_overrides(spec);
}







void	ft_handle_overrides(t_spec *spec)//some orders mattr some don't with s at bottom it does, nee dto handle %%
{
	char c;

	c = spec->c;
	if (spec->precision >= 0 &&
			(ft_tolower(c) == 'd' || c == 'i' || ft_tolower(c) == 'o' ||
			 ft_tolower(c) == 'u' || ft_tolower(c) == 'x'))
		spec->zero = 0;
	if (spec->minus)
		spec->zero = 0;
	if (ft_tolower(c) != 'd' && c != 'i')
	{
		spec->space = 0;
		spec->plus = 0;
	}
	if (spec->plus)
		spec->space = 0;
	if (c == 'p')
		spec->octo = 1;
	if (ft_tolower(c) != 'o' && ft_tolower(c) != 'x' && c != 'p')
		spec->octo = 0;
	if ((ft_tolower(c) == 'x' ft_lower(c) == 'o') && ft_strequ(spec->str, "0"))
		spec->octo = 0;
	if (ft_tolower(c) == 's' && spec->precision >= 0 && (int)ft_strlen(spec->str) > spec->precision)
		spec->str[spec->precision] = 0;
	if (ft_tolower(c) == 'c' || ft_tolower(c) == 's' ||  c == 'p' || c == '%')
		spec->precision = -1;
	if (spec->precision == 0 && ft_strequ(spec->str, "0"))
		spec->str[0] = 0;

}

















void	ft_handle_type(t_spec *spec, char **format)
{
	int i;

	i = 0;
	while (!ft_is_conversion(**format) && **format)
	{
		i++;
		(*format)++;
	}
	spec->mod = ft_strndup(*format - i, i); //free after each use
	if (**format && ft_is_modifier(spec->mod))
		spec->c = *(*format)++;
	else
		ft_error();//need to return value to tell it to just normal print //will all other issues get caught here? %..5c, or things in the worng order, %.7+hhi
}



int		ft_is_modifier(char *str)
{
	if (!*str ||
			ft_strequ(str, "h") ||
			ft_strequ(str, "hh") ||
			ft_strequ(str, "l") ||
			ft_strequ(str, "ll") ||
			ft_strequ(str, "j") ||
			ft_strequ(str, "z"))
		return (1);
	return (0);
}


int		ft_is_conversion(char c)
{
	if (\
			c == '%' ||
			c == 'p' ||
			c == 'i' ||
			ft_tolower(c) == 'd' ||
			ft_tolower(c) == 'o' ||
			ft_tolower(c) == 'u' ||
			ft_tolower(c) == 'x' ||
			ft_tolower(c) == 's' ||
			ft_tolower(c) == 'c')
		return (1);
	return (0);
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



void	ft_handle_flags(t_spec *spec, char **format) ///what is format is like "hello %++++++++++++++"?
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

