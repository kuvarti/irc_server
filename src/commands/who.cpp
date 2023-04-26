/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeryilma <aeryilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:19:07 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/26 16:39:53 by aeryilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	Messages::who(struct pollfd sock,  Server &srv, std::vector<std::string> token)
{
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