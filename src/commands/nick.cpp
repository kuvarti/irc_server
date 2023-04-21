/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:18:22 by root              #+#    #+#             */
/*   Updated: 2023/04/21 18:39:11 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	Messages::nick(struct pollfd fd,  Server &srv, std::vector<std::string> msg)
{
	std::vector<Clients>::iterator	cli = util::findclient(srv.getclient(), fd);
	if (util::findnick(srv.getclient(), msg[1]) != srv.getclient().end())
	{
		Messages::error(fd, srv, util::msgCreator("ERROR", "443", "This Nickname Already Taken"));
		return 1;
	}
	if (srv.isop((*cli).getnickname()))
		(*cli).setop(1);
	else
		(*cli).setop(0);
	(*cli).setnickname(msg[1]);
	return 0;
}