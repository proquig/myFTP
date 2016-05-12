/*
** functions.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue May 10 12:46:42 2016 Guillaume PROQUIN
** Last update Thu May 12 13:41:46 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

int	fn_pwd(const char **cmds, t_client *client)
{
  char	path[1024];

  (void)cmds;
  if (getcwd(path, sizeof(path)))
    dprintf(client->fd, "257 \"%s\"\r\n", path);
  return (1);
}

int	fn_cwd(const char **cmds, t_client *client)
{
  (void)client;
  //if (!strcmp("CDUP", cmds[0]))
  if(chdir(strcmp("CWD", cmds[0]) ? ".." : cmds[1]))
    dprintf(client->fd, "550 Failed to change directory.\r\n");
  else
    dprintf(client->fd, "250 Directory successfully changed.\r\n");
  return (1);
  //return (!chdir(cmds[1]));
}

int	fn_noop(const char **cmds, t_client *client)
{
  (void)cmds;
  dprintf(client->fd, "200 NOOP ok.\r\n");
  return (1);
}

/*
int	fn_cdup(const char **cmds, t_client *client)
{
  (void)cmds;
  (void)client;
  return (!chdir(".."));
  //return (fn_cwd("..", client));
}
*/

/*
int	fn_ls()
{
  //return 
}
*/
