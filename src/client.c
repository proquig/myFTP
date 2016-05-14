/*
** client.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/include
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Thu May 12 10:23:50 2016 Guillaume PROQUIN
** Last update Sat May 14 19:47:16 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

void		init_client(struct sockaddr_in *sock,int fd)
{
  t_client	client;

  client.is_logged = 0;
  client.user = NULL;
  client.ip = NULL;
  client.port = -1;
  client.fd = fd;
  client.m_fd = -1;
  client.sock = sock;
  client.mode = NONE;

  dprintf(client.fd, "220 Welcome.\r\n");
  read_cmd(&client);
}

void		read_cmd(t_client *client)
{
  char			*cmd;

  while ((cmd = get_next_line(client->fd)))
    {
      exec_cmd(cmd, client);
      free(cmd);
    }
  close(client->fd);
  exit(0);
}
