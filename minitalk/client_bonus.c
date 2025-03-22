#include "minitalk_bonus.h"
void	confirm_msg(int a)
{
	if (a == SIGUSR2)
		ft_printf("message done\n");
}
int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

void ascii_to_byte(int pid, char c)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if (c & (1 << bit))
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(400);
        bit++;
    }
}

int main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if(argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			ascii_to_byte(pid, argv[2][i]);
			i++;
		}
        confirm_msg(SIGUSR2);
	}
	else
	{
		ft_printf("%s", "Error\n");
		return (1);
	}
	return (0);
}
