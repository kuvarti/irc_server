/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:50:06 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/23 22:50:06 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"
#include "server.hpp"

#define RMV_FLETTER(str) std::string(str.begin() + 1, str.end())

Channel::Channel(std::string name, Clients *creator)
{
	_creator = creator;
	_ops.push_back(creator);
	_name = name;
	_topic = "Takling about " + name;
}

Channel::~Channel()
{ }

void	Channel::joinmember(Server &srv, Clients *newcli)
{
	_members.push_back(newcli);
	broadcast(srv, RPL_JOIN(newcli->getnickname(), _name));
}

void	Channel::kickmember(Server &srv, Clients *op, Clients *cli)
{
	std::vector<Clients *>::iterator	it = _members.begin();
	for (; it != _members.end(); it++)
	{
		if (*it == cli)
			break;
	}
	if (it != _members.end())
	{
		broadcast(srv, RPL_KICK(op->getnickname(), _name, cli->getnickname()));
		_members.erase(it);
	}
}

void	Channel::broadcast(Server &srv, std::string msg)
{
	std::vector<Clients *>::iterator	it;

	it = _ops.begin();
	for (; it != _ops.end(); it++)
		srv.sendmessage(*(*it)->getclient(), msg);
	it = _members.begin();
	for (; it != _members.end(); it++)
		srv.sendmessage(*(*it)->getclient(), msg);
}

void	Channel::broadcast(Server &srv, Clients *own, std::string msg)
{
	std::vector<Clients *>::iterator	it;

	if ((std::find(_members.begin(), _members.end(), own) != _members.end())
		|| (std::find(_ops.begin(), _ops.end(), own) != _ops.end()))
	{
		//Messages::error(*own->getclient(), srv, util::msgCreator("ERROR ", ": You're not in that channel."));
		//return ;
	}
	it = _ops.begin();
	for (; it != _ops.end(); it++)
	{
		if ((*it) != own)
			srv.sendmessage(*(*it)->getclient(), msg);
	}
	it = _members.begin();
	for (; it != _members.end(); it++)
	{
		if ((*it) != own)
			srv.sendmessage(*(*it)->getclient(), msg);
	}
}

bool	Channel::isthisop(Clients *cli)
{
	std::vector<Clients *>::iterator	it = _ops.begin();

	for (; it != _ops.end(); it++)
	{
		if (*it == cli)
			return 1;
	}
	return 0;
}

int		Server::newchannel(Clients *cli, std::string name)
{
	Channel cnl(name, cli);
	_channels.insert(std::pair<std::string, Channel>(name, cnl));
	sendmessage(*cli->getclient(), RPL_JOIN(cli->getnickname(), name));
	sendmessage(*cli->getclient(), RPL_JOIN(cli->getnickname(), name));
	return 1;
}

static std::string	chnlloadlst(Clients *cli, Clients *it, std::string name)
{
	if (cli == it)
		return "";
	struct userinf usr = (*it).getuserinf();
	std::string msg = ":" + (*cli).getnickname() + " 352 " + (*cli).getnickname() + " " + name;
	msg += " " + usr.username;
	msg += " " + usr.hostname;
	msg += " " + usr.servername;
	msg += " " + (*it).getnickname();
	msg += " H";
	msg += ":0 " + usr.realname;
	return msg;
}

void	Channel::loadlist(Server &srv, Clients *cli)
{
	std::vector<Clients *>::iterator it = _ops.begin();
	for (; it != _ops.end(); it++)
		srv.sendmessage(*(*cli).getclient(), chnlloadlst(cli, *it, _name));
	it = _members.begin();
	for (; it != _members.end(); it++)
		srv.sendmessage(*(*cli).getclient(), chnlloadlst(cli, *it, _name));
}