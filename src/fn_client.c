/*
** fn_client.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/include
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Thu May 12 11:09:36 2016 Guillaume PROQUIN
** Last update Sat May 14 22:51:55 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

void	fn_login(const char **cmds, t_client *client)
{
  if (!cmds[1])
    dprintf(client->fd, "530 Permission denied.\r\n");
  else
    {
      client->user = strdup(cmds[1]);
      dprintf(client->fd, "331 Please specify the password.\r\n");
    }
}

void	fn_pass(const char **cmds, t_client *client)
{
  (void)cmds;
  if (!client->user)
    dprintf(client->fd, "503 Login with USER first.\r\n");
  else if (!strcmp("Anonymous", client->user))
    {
      client->is_logged = 1;
      dprintf(client->fd, "230 User logged in, proceed.\r\n");
    }
  else
    dprintf(client->fd, "530 Login incorrect.\r\n");
}

void	fn_quit(const char **cmds, t_client *client)
{
  (void)cmds;
  dprintf(client->fd, "221 Goodbye.\r\n");
  printf("%d\n", close(client->fd));
  if (client->user)
    free(client->user);
  exit(0);
}
