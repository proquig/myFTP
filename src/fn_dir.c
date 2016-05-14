/*
** functions.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue May 10 12:46:42 2016 Guillaume PROQUIN
** Last update Sat May 14 22:50:47 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

void	fn_pwd(const char **cmds, t_client *client)
{
  char	path[1024];

  (void)cmds;
  if (getcwd(path, sizeof(path)))
    dprintf(client->fd, "257 \"%s\"\r\n", path);
}

void	fn_cwd(const char **cmds, t_client *client)
{
  if (chdir(strcmp("CWD", cmds[0]) ? ".." : cmds[1]))
    dprintf(client->fd, "501 Failed to change directory.\r\n");
  else
    if (!strcmp("CWD", cmds[0]))
      dprintf(client->fd, "250 Directory successfully changed.\r\n");
    else
      dprintf(client->fd, "200 Directory successfully changed.\r\n");
}

void	fn_dele(const char **cmds, t_client *client)
{
  if (cmds[1] && !remove(cmds[1]))
    dprintf(client->fd, "250 Delete operation successful.\r\n");
  else
    dprintf(client->fd, "550 Delete operation failed.\r\n");
}

void	fn_noop(const char **cmds, t_client *client)
{
  (void)cmds;
  dprintf(client->fd, "200 NOOP ok.\r\n");
}

void	fn_help(const char **cmds, t_client *client)
{
  (void)cmds;
  dprintf(client->fd, "214-The following commands are recognized.\r\n");
  dprintf(client->fd, "214 Help OK.\r\n");
}
