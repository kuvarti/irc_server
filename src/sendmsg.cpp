/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:32:02 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/21 12:40:40 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>

/*
void	Server::sendmessage(struct pollfd &sock, std::string str)
{
	str += "\r\n";

	int error_code;
	socklen_t error_code_size = sizeof(error_code);
	getsockopt(sock.fd, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
	if (error_code == 0)
		send(sock.fd, str.c_str(), str.size(), 0);
	else{
		std::cout << "A connection is down" << std::endl;
		removesock(sock);
	}
}
*/