/*
** fn_mode.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Fri May 13 17:11:20 2016 Guillaume PROQUIN
** Last update Sun May 15 17:27:07 2016 Guillaume PROQUIN
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

int			fn_connect(t_client *client, char *ip, int port)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sock;

  if (!(pe = getprotobyname("TCP")))
    return (0);
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (0);
  sock.sin_family = AF_INET;
  sock.sin_port = htons(port);
  sock.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (struct sockaddr*)&sock, sizeof(sock)) == -1)
  client->ip = inet_ntoa(sock.sin_addr);
  client->port = ntohs(sock.sin_port);
  client->m_fd = fd;
  client->m_sock = &sock;
  return (1);
}

void			fn_close(t_client *client, int fd)
{
  close(client->m_fd);
  close(fd);
  client->m_fd = -1;
  client->port = -1;
  client->mode = NONE;
}

void			fn_pasv(const char **cmds, t_client *client)
{
  char			ip[16];
  int			i;

  (void)cmds;
  if (fn_listen(client))
    {
      strcpy(ip, client->ip);
      i = -1;
      while (ip[++i])
	ip[i] = (ip[i] == '.') ? ',' : ip[i];
      client->mode = PASV;
      printf("%d\n", client->port);
      dprintf(client->fd, "227 Entering Passive Mode (%s,%d,%d).\r\n",	\
	      ip, (client->port / 256), (client->port % 256));
    }
}

void			fn_port(const char **cmds, t_client *client)
{
  int			i;
  char			**ip;

  ip = cmds[1] ? get_cmds(cmds[1], ",") : NULL;
  i = -1;
  while (ip && ip[++i] && is_number(ip[i]) && strlen(ip[i]) < 4);
  if (i != 6)
    dprintf(client->fd, "500 Illegal PORT command.\r\n");
  else
    {
      if (!(client->ip = malloc(16)))
	return ;
      sprintf(client->ip, "%s.%s.%s.%s", ip[0], ip[1], ip[2], ip[3]);
      client->port = atoi(ip[4]) * 256 + atoi(ip[5]);
      client->mode = ACTV;
      i = -1;
      while (ip[++i])
	free(ip[i]);
      free(ip);
      dprintf(client->fd, "200 PORT command successful. Consider using PASV.\r\n");
    }
}
