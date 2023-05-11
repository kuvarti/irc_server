/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:10:52 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/23 23:56:12 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define CNLNAME (token[1][0] != '#' ? "#" + token[1] : token[1])
#include "server.hpp"

int	Messages::join(struct pollfd sock,  Server &srv, std::vector<std::string> token)
{
	std::map<std::string, Channel>::iterator	it;
	it = srv.findchannel(CNLNAME);
	if (srv.ischannelexists(it))
	{
		(*it).second.joinmember(srv, &*(util::findclient(srv.getclient(), sock)));
	}
	else
	{
		srv.newchannel(&*(util::findclient(srv.getclient(), sock)), CNLNAME);
	}
	return 0;
}