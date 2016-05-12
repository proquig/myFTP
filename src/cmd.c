/*
** cmd.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue May 10 14:28:54 2016 Guillaume PROQUIN
** Last update Thu May 12 15:49:07 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

void	*get_fn(const char *cmd, t_client *client)
{
  int	i;
  void	*fn[][3] = {
    {"PWD", &fn_pwd, (void*)-1},
    {"CWD", &fn_cwd, (void*)-1},
    {"CDUP", &fn_cwd, (void*)-1},
    {"QUIT", &fn_quit, NULL},
    {"USER", &fn_login, NULL},
    {"PASS", &fn_pass, NULL},
    {NULL, NULL, NULL}
  };

  i = -1;
  while (fn[++i][0])
    if (!strcmp(fn[i][0], cmd)	\
	&& (client->is_logged || (!client->is_logged && !fn[i][2])))
      return (fn[i][1]);
  return (client->is_logged ? NULL : (void*)-1);
}

void	exec_cmd(char *cmd, t_client *client)
{
  char	**cmds;
  int	i;
  int	(*f)(char**, t_client*);

  //dprintf(client->fd, "%s\n", cmd); //DEBUG
  cmds = get_cmds(cmd, " \r\n");
  if (!cmd[0])
    return ;
  if ((f = get_fn(cmds[0], client)) == (void*)-1)
    dprintf(client->fd, "530 Please login with USER and PASS.\r\n");
  else if (f)
    (*f)(cmds, client);
  else
    dprintf(client->fd, "500 Unknown command.\r\n");
  i = -1;
  while (cmds[++i])
    free(cmds[i]);
  free(cmd);
}
