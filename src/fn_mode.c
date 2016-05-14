/*
** fn_mode.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Fri May 13 17:11:20 2016 Guillaume PROQUIN
** Last update Sat May 14 18:20:11 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

int			fn_listen(t_client *client)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sock;
  socklen_t		s_sock;

  if (!(pe = getprotobyname("TCP")))
    return (0);
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (0);
  sock.sin_family = AF_INET;
  sock.sin_port = 0;
  sock.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&sock, sizeof(sock)) == -1)
    return (0);
  if (listen(fd, 1) == -1)
    return (0);
  s_sock = sizeof(sock);
  if (getsockname(fd, (struct sockaddr*)&sock, &s_sock) == -1)
    return (0);
  client->ip = inet_ntoa(sock.sin_addr);
  client->port = ntohs(sock.sin_port);
  client->m_fd = fd;
  return (1);
}

void	fn_close(t_client *client, int fd)
{
  close(client->m_fd);
  close(fd);
  client->m_fd = -1;
  client->port = -1;
  client->mode = NONE;
}

void	fn_pasv(char **cmds, t_client *client)
{
  char	ip[16];
  int	i;

  (void)cmds;
  if (fn_listen(client))
    {
      strcpy(ip, client->ip);
      i = -1;
      while (ip[++i])
	ip[i] = (ip[i] == '.') ? ',' : ip[i];
      client->mode = PASV;
      printf("%d\n", client->port);
      dprintf(client->fd, "Entering Passive Mode (%s,%d,%d)\r\n",	\
	      ip, (client->port / 256), (client->port % 256));
    }
}
