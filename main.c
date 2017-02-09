#include <inttypes.h>
#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	wchar_t *test = L"米";

	//ft_printf("%s\n", NULL);
	ft_printf("%S", test);
	return (0);
}
