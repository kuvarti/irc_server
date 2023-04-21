/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpass.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:11:44 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/21 19:15:11 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	Messages::rpass(struct pollfd fd,  Server &srv, std::vector<std::string> msg)
{
	std::vector<Clients>::iterator	cli = util::findclient(srv.getclient(), fd);
	if (msg.size() < 2)
	{
		Messages::error(fd, srv, util::msgCreator("ERROR", "461", "Not enough parameters"));
		return 1;
	}
	if ((*cli).isop())
		srv.setpass(msg[1]);
	else
		Messages::error(fd, srv, util::msgCreator("ERROR", "481", "Permission Denied- You're not an IRC operator"));
	return 0;
}