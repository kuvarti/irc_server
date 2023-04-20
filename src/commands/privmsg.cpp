/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:13:00 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/20 14:50:57 by kuvarti          ###   ########.fr       */
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
		//std::vector<Clients>::iterator it2 = srv.getclient().begin();
		//while (it2 != srv.getclient().end())
		//{
		//    if ((*it2).getchannel() == token[1])
		//        srv.sendmessage((*it2).getsock(), util::msgSender(util::msgCreator("PRIVMSG", token[1], token[2].substr(1))));
		//    it2++;
		//}
	}
	else
	{
		std::vector<Clients>::iterator it2 = util::findnick(srv.getclient(), token[1]);
		if (it2 == srv.getclient().end())
		{
			Messages::error(sock, srv, util::msgCreator("ERROR", "401", "No Such Nickname"));
			return 1;
		}
		//fix there later
		srv.sendmessage(*(*it2).getclient(), util::msgSender(util::msgCreator("PRIVMSG", token[1], token[2].substr(1))));
	}
	return 0;
}