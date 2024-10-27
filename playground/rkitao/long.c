# include <stdio.h>
# include <limits.h>

int	ft_isdigit(int c)
{
	if (c < -1 || c > 255)
		return (0);
	if ('0' <= (unsigned char)c && (unsigned char)c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
	{
		count++;
	}
	return (count);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

static int ft_help2(char *str, int sign)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	if (ft_strlen(str) > 19)
		return (-1);
	if (ft_strlen(str) == 19)
	{
		if (sign == 1 && ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (-1);
		else if(sign == -1 && ft_strncmp(str, "9223372036854775808", 19) > 0)
			return (-1);
	}
	return (0);
}

static int	ft_exit_help(char *str)
{
	int i;
	int sign;
	int result;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (ft_help2(str, sign) == -1)
		return (-1);
	result = 0;
	i = 0;
	while (str[i])
	{
		result = (unsigned char)(result * 10 + str[i] - '0');
		i++;
	}
	result = (unsigned char)(result * sign);
	return (result);
}

int main(void)
{
	printf("%d\n", ft_exit_help("2147483647"));
	printf("%d\n", ft_exit_help("2147483648"));
	printf("%d\n", ft_exit_help("2147483649"));
	printf("%d\n", ft_exit_help("-2147483646"));
	printf("%d\n", ft_exit_help("-2147483647"));
	printf("%d\n", ft_exit_help("-2147483648"));
	printf("%d\n", ft_exit_help("-2147483649"));
	printf("%d\n", ft_exit_help("4294967295"));
	printf("%d\n", ft_exit_help("4294967296"));
	printf("%d\n", ft_exit_help("4294967297"));
	printf("%d\n", ft_exit_help("4294967298"));
	printf("%d\n", ft_exit_help("-4294967296"));
	printf("%d\n", ft_exit_help("-4294967297"));
	printf("%d\n", ft_exit_help("-4294967298"));
	printf("%d\n", ft_exit_help("-4294967299"));
	printf("%d\n", ft_exit_help("123456789123456789"));
	printf("%d\n", ft_exit_help("987654321987654321"));
	printf("%d\n", ft_exit_help("9223372036854775807"));
	printf("%d\n", ft_exit_help("9223372036854775808"));
	printf("%d\n", ft_exit_help("9223372036854775809"));
	printf("%d\n", ft_exit_help("-9223372036854775807"));
	printf("%d\n", ft_exit_help("-9223372036854775808"));
	printf("%d\n", ft_exit_help("-9223372036854775809"));
	printf("%d\n", ft_exit_help("-9223372036854775810"));
	printf("%d\n", ft_exit_help(""));
	printf("%d\n", ft_exit_help("0"));
	printf("%d\n", ft_exit_help("-0"));
	printf("%d\n", ft_exit_help("+0"));
	printf("%d\n", ft_exit_help("254"));
	printf("%d\n", ft_exit_help("255"));
	printf("%d\n", ft_exit_help("256"));
	printf("%d\n", ft_exit_help("257"));
	printf("%d\n", ft_exit_help("-1"));
	printf("%d\n", ft_exit_help("-10"));
	printf("%d\n", ft_exit_help("+10"));
	printf("%d\n", ft_exit_help("-42"));
	printf("%d\n", ft_exit_help("--10"));
	printf("%d\n", ft_exit_help("--10 1"));
	printf("%d\n", ft_exit_help("++10 1"));
	printf("%d\n", ft_exit_help("++10"));
}
