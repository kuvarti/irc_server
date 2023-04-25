/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:49:18 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/24 20:25:09 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
//	KICK #xd kuvarti

int	Messages::kick(struct pollfd fd,  Server &srv, std::vector<std::string> token)
{
	std::vector<Clients>::iterator it = util::findclient(srv.getclient(), fd);
	std::map<std::string, Channel>::iterator cnl = srv.findchannel(token[1]);
	if (srv.ischannelexists(cnl) && it != srv.getclient().end())
	{
		if (cnl->second.isthisop(&*it))
			cnl->second.kickmember(srv, &(*it), &*(util::findnick(srv.getclient(), token[2])));
		else
			srv.sendmessage(fd, RPL_PRIVMSG(it->getnickname(), token[1], "You are not OP in that Channel."));
		return 0;
	}
	return 1;
}