/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 20:54:23 by biremong          #+#    #+#             */
/*   Updated: 2017/02/14 14:33:39 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_spec(t_spec *spec)//mayeb do separaet for unicode// make sure god wth "-hi" string with precision and everything
{
	int		pad_len;
	int 	prec_len;
	int 	total;
	char	pad;
	int		is_neg;

	ft_get_lens(spec, &pad_len, &prec_len, &total);

//printf("pad_len: %d, prec_len: %d total: %d str: %s\n", pad_len, prec_len, total, spec->str);

	pad = (spec->zero ? '0' : ' ');
	if (spec->zero)
		ft_print_prefix(spec, &is_neg);
	while (!spec->minus && pad_len--)
		write(1, &pad, 1);
	if (!spec->zero)
		ft_print_prefix(spec, &is_neg);
	while (prec_len--)
		write(1, "0", 1);
	ft_putstr(spec->str + is_neg);
	while (pad_len-- > 0)
		write(1, " ", 1);
	return (total);
}











void	ft_print_prefix(t_spec *spec, int *is_neg)
{
	if (*spec->str == '-')
	{
		write(1, "-", 1);
		*is_neg = 1;
		return ;
	}
	*is_neg = 0;
	if (spec->plus)
		write(1, "+", 1);
	else if (spec->space)
		write(1, " ", 1);
	if (spec->octo && ft_tolower(spec->c) == 'o')
		write(1, "0", 1);
	else if (spec->octo && spec->c == 'b')
		write(1, "0b", 2);
	else if (spec->octo && spec->c == 'X')
		write(1, "0X", 2);
	else if (spec->octo)
		write(1, "0x", 2);

}
	






















void	ft_get_lens(t_spec *spec, int *pad_len, int *prec_len, int *total)
{
	int len;

	len = ft_tolower(spec->c) == 'c' ? 1 : ft_strlen(spec->str);
	
	
	if (*spec->str == '-')
		*prec_len = (spec->precision - len + 1 > 0 ? spec->precision - len + 1 : 0);
	else
		*prec_len = (spec->precision - len > 0 ? spec->precision - len : 0);
	len += *prec_len;
	if (ft_tolower(spec->c) == 'o' && spec->octo)
		len++;
	else if (spec->octo)
		len += 2;
	if ((spec->space || spec->plus) && ft_isdigit(*spec->str))
		len++;
	*pad_len = (spec->min_width > len ? spec->min_width - len : 0);
	*total = (spec->min_width > len ? spec->min_width : len);
}






	



