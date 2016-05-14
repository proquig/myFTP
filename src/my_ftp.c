/*
** my_ftp.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Sat May  7 17:40:23 2016 Guillaume PROQUIN
** Last update Sat May 14 18:26:11 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

int			is_number(const char *str)
{
  int	i;

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

int			init_ftp(int port)
{
  int			fd_ftp;
  struct protoent	*pe;
  struct sockaddr_in	sock;

  if (!(pe = getprotobyname("TCP")))
    put_error("getprotomyname failed");
  if ((fd_ftp = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    put_error("socket failed");
  sock.sin_family = AF_INET;
  sock.sin_port = htons(port);
  sock.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd_ftp, (const struct sockaddr *)&sock, sizeof(sock)) == -1)
    close_fd(fd_ftp, "bind failed");
  if (listen(fd_ftp, 5) == -1)
    close_fd(fd_ftp, "listen failed");
  return (fd_ftp);
}

void			my_ftp(int port, const char *path)
{
  int			fd_ftp;
  int			fd_cl;
  struct sockaddr_in	sock;
  socklen_t		sock_size;

  if (chdir(path))
    put_error("Incorrect path");
  fd_ftp = init_ftp(port);
  sock_size = sizeof(sock);
  while (42)
    {
      if ((fd_cl = accept(fd_ftp, (struct sockaddr*)&sock, &sock_size)) == -1)
	close_fd(fd_ftp, "accept failed");
      if (!fork())
	init_client(&sock, fd_cl);
      close(fd_cl);
    }
  close(fd_ftp);
}

int		main(int ac, const char **av)
{
  if (ac == 3 && atoi(av[1]) >= 0)
    my_ftp(atoi(av[1]), av[2]);
  else
    fprintf(stderr, "Usage : %s port path\n", av[0]);
  return 0;
}
