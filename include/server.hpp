/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:45:53 by root              #+#    #+#             */
/*   Updated: 2023/04/26 14:32:46 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <iostream>
#include <sstream>
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
#include "channel.hpp"
#include "ftransfer.hpp"

#define BSIZE 512
#define DEBUGMOD 1
class Server;

std::vector<std::string> getops();

class Messages{
public:
	static std::map<std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> fillcommands();

	static int	kick(struct pollfd,  Server &, std::vector<std::string>);
	static int	join(struct pollfd,  Server &, std::vector<std::string>);
	static int	user(struct pollfd,  Server &, std::vector<std::string>);
	static int	nick(struct pollfd,  Server &, std::vector<std::string>);
	static int	error(struct pollfd,  Server &, std::vector<std::string>);
	static int	pass(struct pollfd,  Server &, std::vector<std::string>);
	static int	cap(struct pollfd,  Server &, std::vector<std::string>);
	static int	quit(struct pollfd,  Server &, std::vector<std::string>);
	static int	privmsg(struct pollfd,  Server &, std::vector<std::string>);
	static int	whois(struct pollfd,  Server &, std::vector<std::string>);
	static int	who(struct pollfd,  Server &, std::vector<std::string>);
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

	std::vector<filet *>	&getfilet() { return _files; }
	void	insertfile(filet *f) { _files.push_back(f); }
	int		removefile(std::vector<filet *>::iterator);

	void	removesock(struct pollfd &);
	bool	isop(std::string);

	int		newchannel(Clients *, std::string);
	std::map<std::string, Channel>::iterator findchannel(std::string cnl) { return _channels.find(cnl); }
	bool	ischannelexists(std::map<std::string, Channel>::iterator it) { return it != _channels.end(); }
private:
	std::string		_password;
	int				_sock;
	std::vector<filet *>			_files;
	std::vector<std::string>		_ops;
	std::vector<pollfd>				_socks;
	std::vector<Clients>			_cli;
	std::map<std::string, Channel>	_channels;
	std::map<std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> commands;
};

//	RPL
#define RPL_WELCOME(source)						"001 " + source + " :Welcome " + source + " to the ft_irc network"
#define RPL_PRIVMSG(source, target, message)	":" + source + " PRIVMSG " + target + " : " + message
#define RPL_WHOIS(target, message)				"whois " + target + ":" + message
#define RPL_JOIN(source, channel)				":" + source + " JOIN :" + channel
#define RPL_KICK(source, channel, target)		":" + source + " KICK " + channel + " " + target + " : OP kicked out."
#define RPL_IRCKICK(channel, target, message)	":ircbot KICK " + channel + " " + target + " : " + message

#define RPL_FILET(source, message)				"FileTransfer : " + source + " wants to sen you a file :" + message

//	Errors
#define ERR_UNKNOWNCOMMAND(source, command)		"421 " + source + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(source, command)		"461 " + source + " " + command + " :Not enough parameters"
#define ERR_PASSWDMISMATCH(source)				"464 " + source + " :Password incorrect"
#define ERR_NICKNAMEINUSE(source)				"433 " + source + " " + source  + " :Nickname is already in use"
#define ERR_NOTREGISTERED(source)				"451 " + source + " :You have not registered"
