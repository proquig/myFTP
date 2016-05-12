/*
** client.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/include
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Thu May 12 10:23:50 2016 Guillaume PROQUIN
** Last update Thu May 12 14:48:34 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

void		init_client(struct sockaddr_in *sock,int fd)
{
  t_client	client;

  client.is_logged = 0;
  client.user = NULL;
  client.ip = inet_ntoa(sock->sin_addr);
  client.port = 0;
  client.fd = fd;
  client.sock = sock;

  dprintf(client.fd, "220 (vsFTPd 3.0.0)\r\n");
  read_cmd(&client);
}

void		read_cmd(t_client *client)
{
  //char		cmd[1024];

  (void)client;
  while (42)
    {
      //usleep(10000);
      //cmd[read(client->fd, cmd, 1024) + 1] = 0;
      //exec_cmd(cmd, client);
      exec_cmd(get_next_line(client->fd), client);
    }
}
