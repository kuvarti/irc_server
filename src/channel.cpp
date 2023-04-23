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
	boardcast(srv, RPL_JOIN(newcli->getnickname(), _name));
}

void	Channel::boardcast(Server &srv, std::string msg)
{
	std::vector<Clients *>::iterator	it;

	it = _ops.begin();
	for (; it != _ops.end(); it++)
		srv.sendmessage(*(*it)->getclient(), msg);
	it = _members.begin();
	for (; it != _members.end(); it++)
		srv.sendmessage(*(*it)->getclient(), msg);
}

void	Channel::boardcast(Server &srv, Clients *own, std::string msg)
{
	std::vector<Clients *>::iterator	it;

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


int		Server::newchannel(Clients *cli, std::string name)
{
	Channel cnl(name, cli);
	_channels.insert(std::pair<std::string, Channel>(name, cnl));
	sendmessage(*cli->getclient(), RPL_JOIN(cli->getnickname(), name));
	return 1;
}