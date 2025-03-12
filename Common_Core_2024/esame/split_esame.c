#include <stdlib.h>
#include <stdio.h>
char    **count(char *s)
{
    int i;
    int count;
    i = 0;
    count = 0;
    while (s[i])
    {
        while (s[i] && (s[i] == ' ' || s[i] == '\t'  || s[i] == '\n'))
            i++;
        if (s[i])
            count++;
        while (s[i] && s[i] != ' ' && s[i] != '\t'  && s[i] != '\n')
            i++;
    }
    return ((char **)malloc((count + 1) * sizeof(char *)));
}
char    *ft_substr(char *s, int len)
{
    char    *sub;
    int     i;
    sub = (char *)malloc((len + 1) * sizeof(char));
    if (!sub)
        return (NULL);
    i = 0;
    while (s[i] && i < len)
    {
        sub[i] = s[i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}
char    **ft_split(char *str)
{
    char    **arr;
    int     i;
    int     j;
    int     a;
    if (!str)
        return (NULL);
    arr = count(str);
    if (!arr)
        return (NULL);
    i = 0;
    a = 0;
    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t'  || str[i] == '\n'))
            i++;
        if (!str[i])
            break ;
        j = i;
        while (str[i] && str[i] != ' ' && str[i] != '\t'  && str[i] != '\n')
            i++;
        arr[a] = ft_substr(&str[j], i - j);
        if (!arr[a])
            return (NULL);
        a++;
    }
    arr[a] = NULL;
    return (arr);
}

// int main()
// {
//  char *str = "ciao come va";
//  char **arr = ft_split(str);
//  while (*arr)
//  {
//      printf("%s\n", *arr);
//      arr++;
//  }
//  return 0;
// }
