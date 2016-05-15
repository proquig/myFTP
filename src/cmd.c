/*
** cmd.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Tue May 10 14:28:54 2016 Guillaume PROQUIN
** Last update Sun May 15 18:01:38 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

void	*get_fn(const char *cmd, t_client *client)
{
  int	i;
  void	*fn[][3] = {
    {"PWD", &fn_pwd, (void*)-1},
    {"CWD", &fn_cwd, (void*)-1},
    {"CDUP", &fn_cwd, (void*)-1},
    {"DELE", &fn_dele, (void*)-1},
    {"HELP", &fn_help, (void*)-1},
    {"NOOP", &fn_noop, (void*)-1},
    {"PORT", &fn_port, (void*)-1},
    {"PASV", &fn_pasv, (void*)-1},
    {"LIST", &fn_tsfr, (void*)-1},
    {"RETR", &fn_tsfr, (void*)-1},
    {"STOR", &fn_tsfr, (void*)-1},
    {"QUIT", &fn_quit, NULL},
    {"USER", &fn_login, NULL},
    {"PASS", &fn_pass, NULL},
    {NULL, NULL, NULL}
  };

  i = -1;
  while (cmd && fn[++i][0])
    if (!strcmp(fn[i][0], cmd)	\
	&& (client->is_logged || (!client->is_logged && !fn[i][2])))
      return (fn[i][1]);
  return (client->is_logged ? NULL : (void*)-1);
}

void	exec_cmd(const char *cmd, t_client *client)
{
  char	**cmds;
  int	i;
  void	(*f)(char**, t_client*);

  cmds = get_cmds(cmd, " \r\n");
  if ((f = get_fn(cmds[0], client)) == (void*)-1)
    dprintf(client->fd, "530 Please login with USER and PASS.\r\n");
  else if (f)
    (*f)(cmds, client);
  else
    dprintf(client->fd, "500 Unknown command.\r\n");
  i = -1;
  while (cmds[++i])
    free(cmds[i]);
}
