/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:14:31 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/20 14:07:37 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>

int	Messages::pass(struct pollfd sock, Server &srv, std::vector<std::string> token)
{
	std::vector<Clients>::iterator it = util::findclient(srv.getclient(), sock);
	if (it == srv.getclient().end())
		return 1;
	if (token[1] != srv.getpass())
	{
		Messages::error(sock, srv, util::msgCreator(" ERROR", "464","incorrect Password."));
		Messages::quit(sock, srv, util::msgCreator(" QUIT", "Disconnecting()"));
		return 1;
	}
	(*it).setconfirmed(true);
	srv.sendmessage(sock, util::msgSender(util::msgCreator("PASS", "001", "Password Accepted")));
	return 0;
}