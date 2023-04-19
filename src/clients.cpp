/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:19:06 by root              #+#    #+#             */
/*   Updated: 2023/04/19 22:25:57 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clients.hpp"

Clients::Clients(int sock) : _nickname(UNCONFIRMED)
{
	struct sockaddr_in	clientaddr;
	socklen_t	slen = sizeof(clientaddr);
	_client.fd = accept(sock, (struct sockaddr*)&clientaddr, &slen);
	if (_client.fd < 0)
		exit(EXIT_FAILURE);
	confirmed = false;
	registered = false;
	serverop = false;
}

void	Clients::setuserinf(std::string s1, std::string s2, std::string s3, std::string s4)
{
	_userinf.username = s1;
	_userinf.hostname = s2;
	_userinf.servername = s3;
	_userinf.realname = s4;
}

Clients::~Clients()
{
}