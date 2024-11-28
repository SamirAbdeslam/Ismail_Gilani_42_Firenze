#include <unistd.h>
#include <stdlib.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putnbr(int nb)
{
    if(nb == -2147483648)
    {
        ft_putchar('-');
        ft_putchar('2');
        ft_putnbr(147483648);
    }
    else if(nb < 0)
    {
        ft_putchar('-');
        nb = -nb;
        ft_putnbr(nb);
    }
    else if(nb >= 0 && nb <= 9)
    {
        nb = nb + '0';
        ft_putchar(nb);
    }
    else
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
}
