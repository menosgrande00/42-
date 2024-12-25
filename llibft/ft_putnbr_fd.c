#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + '0', fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}
#include <fcntl.h>

int main()
{
	open("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(3);
	open("text.tx", O_RDWR | O_CREAT | O_TRUNC, 0644);
	open("text.", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(-233423, 4);
	close(5);
}