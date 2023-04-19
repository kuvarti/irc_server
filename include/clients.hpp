/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:04:18 by root              #+#    #+#             */
/*   Updated: 2023/04/19 22:23:57 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <poll.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <vector>

#define	UNCONFIRMED "unconfirmed"	//password
#define	UNREGISTERED "unregistered"	//nickname

struct userinf{
	std::string username;
	std::string hostname;
	std::string servername;
	std::string realname;
};

class Clients{
public:
	Clients(int);
	~Clients();

	void	setnickname(std::string nick) { _nickname = nick; }

	int			getclientsock() const { return _client.fd; };
	std::string	getnickname() { return _nickname; };

	bool	isconfirmed() const { return confirmed; };
	bool	isregistered() const { return registered; };

	void	setconfirmed(bool b) { confirmed = b; };
	void	setregistered(bool b) { registered = b; };

	void	setuserinf(std::string, std::string, std::string, std::string);
	void	setuserinf(userinf u) { _userinf = u; };
	struct	userinf	getuserinf() const { return _userinf; };

	template<typename T>
	static	std::vector<Clients>::iterator	findnclient(std::vector<Clients> &, T(Clients::*)(void), T);

private:
	bool				confirmed;
	bool				registered;
	bool				serverop;
	std::string			_nickname;
	struct pollfd		_client;
	struct sockaddr_in	clientaddr;
	userinf				_userinf;
};