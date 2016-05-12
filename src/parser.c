/*
** parser.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue May 10 14:27:03 2016 Guillaume PROQUIN
** Last update Thu May 12 13:51:40 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

int		is_delimiter(char c, const char *dels)
{
  int		i;

  i = -1;
  while (dels[++i] && dels[i] != c);
  return (dels[i] ? 1 : 0);
}

int		count_cmds(const char *line, const char *dels)
{
  int		i;
  int		count;

  count = 0;
  i = -1;
  while (line[++i])
    if (!is_delimiter(line[i], dels) \
        && (is_delimiter(line[i + 1], dels) || !line[i + 1]))
      count++;
  return (count);
}

char		**get_cmds(const char *str, const char *dels)
{
  int		i;
  int		j;
  int		k;
  int		word_size;
  char		**tab;

  tab = malloc(sizeof(char*) * (count_cmds(str, dels) + 1));
  i = -1;
  while (is_delimiter(str[++i], dels));
  j = 0;
  while (str[i])
    {
      word_size = i - 1;
      while (str[++word_size] && !is_delimiter(str[word_size], dels));
      if (!tab || (tab[j] = malloc(sizeof(char) * (word_size - i + 1))) == NULL)
	return (NULL);
      k = 0;
      while (str[i] && !is_delimiter(str[i], dels))
        tab[j][k++] = str[i++];
      tab[j++][k] = '\0';
      while (str[i] && is_delimiter(str[i], dels))
        i++;
    }
  tab[j] = NULL;
  return (tab);
}
