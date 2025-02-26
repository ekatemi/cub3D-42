#include "mlx_linux/mlx.h"

//int check_extention

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (write(1, "(null)", 6));
	
    while (*str)
	{
		if (ft_putchar(*str) == -1)
			return (-1);
		str++;
		counter++;
	}
	return (counter);
}

int main (int argc, char **argv) {


    
    
    
    
    return (0);
}