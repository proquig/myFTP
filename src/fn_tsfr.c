/*
** fn_tsfr.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Sat May 14 18:56:21 2016 Guillaume PROQUIN
** Last update Sat May 14 22:53:14 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

void			fn_tsfr(char **cmds, t_client *client)
{
  int			i;
  void			(*f)(char**, t_client*);
  void			*fn[][2] = {
    {"LIST", &fn_list},
    {"RETR", &fn_retr},
    {"STOR", &fn_stor},
    {NULL, NULL}
  };

  i = -1;
  while (fn[++i][0] && strcmp(fn[i][0], cmds[0]));
  if (client->mode && (f = fn[i][1]))
    (*f)(cmds, client);
  else
    dprintf(client->fd, "425 Use PORT or PASV first.\r\n");
}

void			fn_list(const char **cmds, t_client *client)
{
  struct sockaddr_in	s;
  socklen_t		ss;
  char			path[1024];
  int			old_fd;
  int			fd;

  ss = sizeof(s);
  dprintf(client->fd, "150 Here comes the directory listing.\r\n");
  if ((fd = accept(client->m_fd, (struct sockaddr*)&s, &ss)) == -1)
    return ;
  if (opendir(cmds[1] ? cmds[1] : getcwd(path, sizeof(path))))
    {
      old_fd = dup(1);
      dup2(fd, 1);
      if (!fork())
	execlp("/bin/ls", "/bin/ls", "-l", cmds[1], NULL);
      dup2(old_fd, 1);
      fn_close(client, fd);
    }
  dprintf(client->fd, "226 Directory send OK.\r\n");
}

void			fn_retr(char **cmds, t_client *client)
{
  struct sockaddr_in	s;
  socklen_t		ss;
  char			buffer[BUFFER_SIZE];
  int			fd;
  int			file_fd;
  int			size;

  ss = sizeof(s);
  if (cmds[1] && (file_fd = open(cmds[1], O_RDONLY)) != -1)
    {
      if ((fd = accept(client->m_fd, (struct sockaddr*)&s, &ss)) == -1)
	return ;
      dprintf(client->fd, "150 Opening file %s.\r\n", cmds[1]);
      while ((size = read(file_fd, buffer, BUFFER_SIZE)))
	write(fd, buffer, size);
      close(file_fd);
      dprintf(client->fd, "226 Transfer complete.\r\n");
      fn_close(client, fd);
    }
  else
    dprintf(client->fd, "227 Failed to open file.\r\n");
}

void			fn_stor(char **cmds, t_client *client)
{
  struct sockaddr_in	s;
  socklen_t		ss;
  char			buffer[BUFFER_SIZE];
  int			fd;
  int			file_fd;
  int			size;

  ss = sizeof(s);
  if (cmds[1] \
      &&(file_fd = open(cmds[1], O_CREAT | O_TRUNC | O_WRONLY, 0600)) != -1)
    {
      if ((fd = accept(client->m_fd, (struct sockaddr*)&s, &ss)) == -1)
	return ;
      dprintf(client->fd, "150 Ok to send data.\r\n");
      while ((size = read(fd, buffer, BUFFER_SIZE)))
	write(file_fd, buffer, size);
      close(file_fd);
      dprintf(client->fd, "226 Transfer complete.\r\n");
      fn_close(client, fd);
    }
  else
    dprintf(client->fd, "227 Could not create file.\r\n");
}
