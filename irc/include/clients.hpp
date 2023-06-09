/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 00:04:18 by root              #+#    #+#             */
/*   Updated: 2023/04/21 18:38:42 by kuvarti          ###   ########.fr       */
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
	
	// added by Bilal (for join part)
	//void Clients::addChannelToClient(Channel* chan) {
    	//this->channels.push_back(chan);
	//}

	void	setnickname(std::string nick) { _nickname = nick; }

	int			getclientsock() const { return _client.fd; };
	struct pollfd	*getclient() { return &_client; };
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

	bool	isop() const { return serverop; };
	void	setop(bool b) { serverop = b; };

private:
	//std::vector<Channel*> channels; // added by Bilal
	bool				confirmed;
	bool				registered;
	bool				serverop;
	struct pollfd		_client;
	struct sockaddr_in	clientaddr;
	std::string			_nickname;
	userinf				_userinf;
};
