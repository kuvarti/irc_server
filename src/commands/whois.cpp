/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:43:41 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/21 14:06:58 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	Messages::whois(struct pollfd sock, Server &srv, std::vector<std::string> token)
{
	std::vector<Clients>::iterator it = util::findnick(srv.getclient(), token[1]);
	if (it == srv.getclient().end())
		return 1;
	userinf tmp = (*it).getuserinf();
	std::string	msg;
	msg = " " + tmp.username + " " + tmp.hostname + " " + tmp.realname;
	srv.sendmessage(sock, RPL_WHOIS((*it).getnickname(), msg));
	return 0;
}