/*
** my_ftp.h for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/include
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Sat May  7 17:31:28 2016 Guillaume PROQUIN
** Last update Sat May 14 19:48:36 2016 Guillaume PROQUIN
*/

#ifndef			__MY_FTP_H__
# define		__MY_FTP_H__

# include		<stdlib.h>
# include		<stdio.h>
# include		<unistd.h>
# include		<string.h>
# include		<signal.h>
# include		<dirent.h>
# include		<netdb.h>
# include		<fcntl.h>
# include		<sys/stat.h>
# include		<sys/types.h>
# include		<sys/socket.h>
# include		<netinet/in.h>
# include		<arpa/inet.h>
# include		"get_next_line.h"

# define		BUFFER_SIZE	1024

typedef enum
{
  NONE,
  ACTV,
  PASV
}	TSFR_MODE;

typedef struct		s_client
{
  char			is_logged;
  char			*user;
  char			*ip;
  int			port;
  int			fd;
  int			m_fd;
  struct sockaddr_in	*sock;
  TSFR_MODE		mode;
}			t_client;

void			init_client(struct sockaddr_in *sock, int fd);
void			read_cmd(t_client *client);

void			exec_cmd(char *cmd, t_client *client);

int			is_number(const char *str);
void			put_error(const char *msg);

void			close_fd(int fd, const char *msg);
void			sig_handler(int sig);
int			init_ftp(int port);
void			my_ftp(int port, const char *path);

int			is_delimiter(char c, const char *dels);
int			count_cmds(const char *line, const char *dels);
char			**get_cmds(const char *str, const char *dels);

void			*get_fn(const char *cmd, t_client *client);

void			fn_pwd(const char **cmds, t_client *client);
void			fn_cwd(const char **cmds, t_client *client);
void			fn_cdup(const char **cmds, t_client *client);
void			fn_list(const char **cmds, t_client *client);
void			fn_dele(const char **cmds, t_client *client);

void			fn_noop(const char **cmds, t_client *client);
void			fn_help(const char **cmds, t_client *client);

void			fn_login(const char **cmds, t_client *client);
void			fn_pass(const char **cmds, t_client *client);
void			fn_quit(const char **cmds, t_client *client);

int			fn_listen(t_client *client);
void			fn_close(t_client *client, int fd);
void			fn_pasv(char **cmds, t_client *client);

void			fn_tsfr(char **cmds, t_client *client);
void			fn_retr(char **cmds, t_client *client);

#endif
