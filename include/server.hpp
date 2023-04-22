/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:45:53 by root              #+#    #+#             */
/*   Updated: 2023/04/22 18:30:23 by kuvarti          ###   ########.fr       */
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
#include "ftransfer.hpp"

#define BSIZE 512
#define DEBUGMOD 1
class Channel;
class Server;

std::vector<std::string> getops();

class Messages{
public:
	static std::map<std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> fillcommands();

	//static int	join(struct pollfd,  Server &, std::vector<std::string>);
	static int	user(struct pollfd,  Server &, std::vector<std::string>);
	static int	nick(struct pollfd,  Server &, std::vector<std::string>);
	static int	error(struct pollfd,  Server &, std::vector<std::string>);
	static int	pass(struct pollfd,  Server &, std::vector<std::string>);
	static int	cap(struct pollfd,  Server &, std::vector<std::string>);
	static int	quit(struct pollfd,  Server &, std::vector<std::string>);
	static int	privmsg(struct pollfd,  Server &, std::vector<std::string>);
	static int	whois(struct pollfd,  Server &, std::vector<std::string>);
	static int	ping(struct pollfd,  Server &, std::vector<std::string>);
	static int	pong(struct pollfd,  Server &, std::vector<std::string>);
	static int	rpass(struct pollfd,  Server &, std::vector<std::string>);
	static int	filet(struct pollfd,  Server &, std::vector<std::string>);
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
	std::map<std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> &getcommands() { return commands; }

	std::string	getpass() const { return _password; }
	void	setpass(std::string pass) { _password = pass; }

	void	insertfile(filet f) { _files.push_back(f); }
	int		removefile();

	void	removesock(struct pollfd &);

	bool	isop(std::string);
private:
	std::string		_password;
	int				_sock;
	std::vector<filet>			_files;
	std::vector<std::string>	ops;
	std::vector<pollfd>			_socks;
	std::vector<Clients>		_cli;
	std::map<std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> commands;
};

//	RPL
#define RPL_WELCOME(source)						"001 " + source + " :Welcome " + source + " to the ft_irc network"
#define RPL_PRIVMSG(source, target, message)	":" + source + " PRIVMSG " + target + " : " + message
#define RPL_WHOIS(target, message)				"whois " + target + ":" + message

#define RPL_FILET(source, message)				"620 FileTransfer : " + source + " want to sen you a file :" + message

//	Errors
#define ERR_UNKNOWNCOMMAND(source, command)		"421 " + source + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(source, command)		"461 " + source + " " + command + " :Not enough parameters"
#define ERR_PASSWDMISMATCH(source)				"464 " + source + " :Password incorrect"
#define ERR_NICKNAMEINUSE(source)				"433 " + source + " " + source  + " :Nickname is already in use"
#define ERR_NOTREGISTERED(source)				"451 " + source + " :You have not registered"
