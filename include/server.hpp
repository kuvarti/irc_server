/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:45:53 by root              #+#    #+#             */
/*   Updated: 2023/04/20 14:12:08 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>

#include <algorithm>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <utility>
#include <map>

#include "utils.hpp"
#include "clients.hpp"

#define BSIZE 512
class Channel;
class Server;

class Messages{
public:
	static std::map<std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> fillcommands();

	//static void	join(struct pollfd,  Server &, std::vector<std::string>);
	static int	user(struct pollfd,  Server &, std::vector<std::string>);
	static int	nick(struct pollfd,  Server &, std::vector<std::string>);
	static int	error(struct pollfd,  Server &, std::vector<std::string>);
	static int	pass(struct pollfd,  Server &, std::vector<std::string>);
	static int	cap(struct pollfd,  Server &, std::vector<std::string>);
	static int	quit(struct pollfd,  Server &, std::vector<std::string>);
	static int	privmsg(struct pollfd,  Server &, std::vector<std::string>);
};

class Server{
public:
	Server(int, std::string);
	~Server();

	void	loop();
	void	recvmessage(struct pollfd &);
	void	sendmessage(struct pollfd &, std::string);
	int		messageexecuter(struct pollfd &, std::vector<std::string>);
	std::vector<std::string>	parsemessage(struct pollfd &, char *);

	std::vector<Clients> &getclient() { return _cli; }

	std::string	getpass() const { return _password; }
	void	removesock(struct pollfd &);
private:
	std::string		_password;
	int				_sock;
	std::vector<pollfd>		_socks;
	std::vector<Clients>	_cli;
	std::map<std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> commands;
};