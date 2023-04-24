/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:19:07 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/24 02:48:09 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	Messages::who(struct pollfd sock,  Server &srv, std::vector<std::string> token)
{
	std::vector<Clients>::iterator	it = util::findclient(srv.getclient(), sock);
	if (token[1][0] == '#')
	{
		std::map<std::string, Channel>::iterator chnl = srv.findchannel(token[1]);
		if (srv.ischannelexists(chnl))
		{
			(*chnl).second.loadlist(srv, &*(util::findclient(srv.getclient(), sock)));
		}
	}
	return 0;
}