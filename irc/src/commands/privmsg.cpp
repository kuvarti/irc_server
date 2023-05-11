/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:13:00 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/24 01:56:07 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int Messages::privmsg(struct pollfd sock,  Server &srv, std::vector<std::string> token)
{
	std::vector<Clients>::iterator it = util::findclient(srv.getclient(), sock);
	if (it == srv.getclient().end())
		return 1;
	if (token.size() < 3)
	{
		Messages::error(sock, srv, util::msgCreator("ERROR", "411", "No Recipient Given"));
		return 1;
	}
	if (token[2][0] != ':')
	{
		Messages::error(sock, srv, util::msgCreator("ERROR", "412", "No Text To Send"));
		return 1;
	}
	if (token[1][0] == '#')
	{
		std::map<std::string, Channel>::iterator	it3 = srv.findchannel(token[1]);
		if (srv.ischannelexists(it3))
			(*it3).second.broadcast(srv, &*(util::findclient(srv.getclient(), sock)), RPL_PRIVMSG((*it).getnickname(), token[1], util::msgSender(token, 2)));
	}
	else
	{
		std::vector<Clients>::iterator it2 = util::findnick(srv.getclient(), token[1]);
		if (it2 == srv.getclient().end())
		{
			Messages::error(sock, srv, util::msgCreator("ERROR", "401", "No Such Nickname"));
			return 1;
		}
		else if ((*it2).getnickname() == (*it).getnickname())
		{
			Messages::error(sock, srv, util::msgCreator("ERROR", "404", "Cannot Send To Self"));
			return 1;
		}
		srv.sendmessage(*(*it2).getclient(), RPL_PRIVMSG((*it).getnickname(), (*it2).getnickname(), util::msgSender(token, 2)));
	}
	return 0;
} 