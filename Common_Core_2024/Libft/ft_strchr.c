#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	int i;
	unsigned char t;

	i = 0;
	t = (unsigned char)c;

	while(s[i] != '\0')
	{
		if(s[i] == t)
		{
			return((char *)&s[i]);
		}
		i++;
	}
	if(s[i] == t)
		return((char *)&s[i]);
	return(NULL);
}
/*
int main()
{
	char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
 	char *d1 = strchr(src, '\0');
 	char *d2 = ft_strchr(src, '\0');
 
	printf("ORIGINALE: %s\n", d1);
	printf("MIO: %s\n", d2);

 	if (d1 == d2)
 		printf("TEST_SUCCESS");
 	printf("TEST_FAILED");

}*/
