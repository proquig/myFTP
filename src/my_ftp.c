/*
** my_ftp.c for my_ftp in /home/proqui_g/rendu/PSU_2015_myftp/src
** 
** Made by Guillaume PROQUIN
** Login   <proqui_g@epitech.net>
** 
** Started on  Sat May  7 17:40:23 2016 Guillaume PROQUIN
** Last update Thu May 12 11:21:59 2016 Guillaume PROQUIN
*/

#include "my_ftp.h"

int			fd_ftp = 0;

int			is_number(const char *str)
{
  int	i;

  i = -1;
  while (str[++i] && str[i] >= '0' && str[i] <= '9');
  return (!str[i]);
}

void			put_error(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

/*
int			send_msg(int client_fd, const char *msg)
{
  return (write(client_fd, msg, strlen(msg)) == -1);
}
*/

void			close_fd(int fd, const char *msg)
{
  close(fd);
  if (msg)
    put_error(msg);
}

/*
void			loop_ftp()
{

}
*/

void			sig_handler(int sig)
{
  if (sig == SIGINT)
    close_fd(fd_ftp, NULL);
}

void			init_ftp(int port)
{
  struct protoent	*pe;
  struct sockaddr_in	sock;
  //int			fd;

  signal(SIGINT, sig_handler);
  if (!(pe = getprotobyname("TCP")))
    put_error("getprotomyname failed");
  if ((fd_ftp = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    put_error("socket failed");
  sock.sin_family = AF_INET;
  sock.sin_port = htons(port);
  sock.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd_ftp, (const struct sockaddr *)&sock, sizeof(sock)) == -1)
    close_fd(fd_ftp, "bind failed");
  if (listen(fd_ftp, 5) == -1)
    close_fd(fd_ftp, "listen failed");
  //return (fd);
}

void			my_ftp(int port, const char *path)
{
  //int			fd_ftp;
  int			fd_cl;
  struct sockaddr_in	sock;
  socklen_t		sock_size;
  //char			cmd[1024];

  //if (!fn_cwd(path, 0))
  if (chdir(path))
    put_error("Incorrect path");
  init_ftp(port);
  sock_size = sizeof(sock);
  while (42)
    {
      if ((fd_cl = accept(fd_ftp, (struct sockaddr*)&sock, &sock_size)) == -1)
	close_fd(fd_ftp, "accept failed");
      if (!fork())
	{
	  init_client(&sock, fd_cl);
	  /*
	    while (42)
	    {
	      cmd[read(fd_cl, cmd, 1024) + 1] = 0;
	      exec_cmd(cmd, fd_cl);
	    }
	  */
	}
	//if (send_msg(fd_cl, "Hello Bitch !\n"))
	//put_error("failed to send_msg");
	//close(fd_cl);
    }
  close(fd_ftp);
  /*
  //(void)path;		//DEBUG
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  struct sockaddr_in	s_in_client;
  socklen_t		s_in_size;
  int			client_fd;
  char			*client_ip;
  //char			*ip;
  //int			port;
  int			fd;

  if (!(pe = getprotobyname("TCP")))
    put_error("getprotomyname failed");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    put_error("socket failed");
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  //s_in.sin_addr = inet_addr(ip);
  //(void)ip;
  //printf("%d\n", INADDR_ANY);
  //if (close(fd) == -1)
  //put_error("close failed");
  //if (bind(fd, (const struct sockaddr *)
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    close_fd(fd, "bind failed");
  if (listen(fd, port) == -1)
    close_fd(fd, "listen failed");
  s_in_size = sizeof(s_in_client);
  if ((client_fd = accept(fd, (struct sockaddr *)&s_in_client, &s_in_size)) == -1)
    close_fd(fd, "accept failed");
  //client_ip = inet_ntoa(s_in_client.sin_addr);
  //(void)client_ip;
  if (send_msg(client_fd, "Hello"))
    put_error("failed to send_msg");
  close(fd);
  */
}

int		main(int ac, const char **av)
{
  //printf("%d\n", is_number(av[1]));
  if (ac == 3 && atoi(av[1]) >= 0)
    my_ftp(atoi(av[1]), av[2]);
  else
    fprintf(stderr, "Usage : %s port path\n", av[0]);
  return 0;
}
