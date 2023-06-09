/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:44:04 by root              #+#    #+#             */
/*   Updated: 2023/04/22 12:10:25 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <poll.h>
#include <vector>
#include <string>
#include <map>

class Clients;

class util{
public:
	static	std::vector<struct pollfd>::iterator	findsocket(std::vector<struct pollfd> &,const struct pollfd &);
//todo bu template bitecek!
	template<typename T>
	static	std::vector<Clients>::iterator	findnclient(std::vector<Clients> &, T(Clients::*)(void), T);
	static	std::vector<Clients>::iterator	findclient(std::vector<Clients> &map, const int &poll);
	static	std::vector<Clients>::iterator	findclient(std::vector<Clients> &, const struct pollfd &);
	static	std::vector<Clients>::iterator	findnick(std::vector<Clients> &, std::string);

	static	std::vector<std::string>	msgCreator(std::string, std::string, std::string);
	static	std::vector<std::string>	msgCreator(std::string, std::string);
	static	std::string	msgSender(std::vector<std::string>);
	static	std::string	msgSender(std::vector<std::string>, int start);

	static	std::vector<std::string>	split(std::vector<std::string>, int start);
};

int	operator<<(std::vector<struct pollfd> &, const struct pollfd &);