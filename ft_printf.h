/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:27:52 by biremong          #+#    #+#             */
/*   Updated: 2017/02/14 11:55:43 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H


# include <stdarg.h>
# include <stdio.h>////
# include <unistd.h>
# include <stdlib.h>


typedef struct	s_spec
{
	int plus;
	int	minus;
	int	space;
	int	zero;
	int	octo;
	int	min_width;
	int precision;
	char *mod;
	char c;
	char *str;
}				t_spec;


//ft_printf.c
int		ft_printf(const char *format, ...);
void	ft_get_arg_str(t_spec *spec, va_list ap);
void    ft_parse_spec(t_spec *spec, char **format, va_list ap);
void    ft_handle_type(t_spec *spec, char **format);
int     ft_is_modifier(char *c);
int     ft_is_conversion(char c);
void    ft_handle_precision(t_spec *spec, char **format);
void    ft_handle_min_width(t_spec *spec, char **format);
void    ft_handle_flags(t_spec *spec, char **format);
void	ft_handle_overrides(t_spec *spec);

//print_specifier.c
int		ft_print_spec(t_spec *spec);
void	ft_print_prefix(t_spec *spec, int *is_neg);
void	ft_get_lens(t_spec *spec, int *pad_len, int *prec_len, int *total);

//to_multibyte.c
char	*ft_to_multibyte(wchar_t *wc_str);
void	ft_encode_wc(wchar_t wc, char *mb_str, int *j);
int		ft_get_mb_len(wchar_t wc);

//libft_functions
int		ft_isdigit(int c);
int		ft_isupper(char c);
char	*ft_itoa(intmax_t n);
char	*ft_itoa_base(uintmax_t n, int base, int upper_flag);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *str);
int		ft_strequ(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strndup(char *str, size_t len);
char	*ft_strnew(size_t size);
int		ft_tolower(int c);
void	*ft_memalloc(size_t size);
void	ft_crash(void);
void	ft_error(void);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);

#endif
