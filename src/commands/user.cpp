/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:16:45 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/24 00:28:52 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	Messages::user(struct pollfd sock,  Server &srv, std::vector<std::string> token)
{
	std::vector<Clients>::iterator it = util::findclient(srv.getclient(), sock);
	if (token.size() != 5)
	{
		Messages::error(sock, srv, util::msgCreator("ERROR", "Not Enough Parameters"));
		return 1;
	}
	(*it).setuserinf(token[1], token[2], token[3], token[4]);
	(*it).setregistered(true);
	srv.sendmessage(sock, util::msgSender(util::msgCreator((*it).getnickname(), "001", "User Registered")));
	return 0;
}