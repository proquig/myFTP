/*
** utils.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Sat May 14 22:48:11 2016 Guillaume PROQUIN
** Last update Sat May 14 22:54:29 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

int			is_number(const char *str)
{
  int			i;

  i = -1;
  while (str[++i] && str[i] >= '0' && str[i] <= '9');
  return (!str[i]);
}

void			put_error(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

void			close_fd(int fd, const char *msg)
{
  close(fd);
  if (msg)
    put_error(msg);
}
