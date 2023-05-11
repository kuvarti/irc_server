/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:53:18 by root              #+#    #+#             */
/*   Updated: 2023/04/26 23:06:23 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "utils.hpp"
#include "clients.hpp"

std::vector<struct pollfd>::iterator	util::findsocket(std::vector<struct pollfd> &vec,const struct pollfd &str)
{
	std::vector<struct pollfd>::iterator	ret = vec.begin();
	for (; ret < vec.end(); ret++)
	{
		if (ret->fd == str.fd)
			break ;
	}
	return (ret);
}

std::map <std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> Messages::fillcommands(){
	std::map <std::string, int(*)(struct pollfd,  Server &, std::vector<std::string>)> ret;
	ret["who"] = &Messages::who;
	ret["WHO"] = &Messages::who;
	ret["JOIN"] = &Messages::join;
	ret["KICK"] = &Messages::kick;
	ret["NICK"] = &Messages::nick;
	ret["ERROR"] = &Messages::error;
	ret["PASS"] = &Messages::pass;
	ret["CAP"] = &Messages::cap;
	ret["MODE"] = &Messages::cap;
	ret["QUIT"] = &Messages::quit;
	ret["USER"] = &Messages::user;
	ret["PRIVMSG"] = &Messages::privmsg;
	ret["whois"] = &Messages::whois;
	ret["PING"] = &Messages::ping;
	ret["PONG"] = &Messages::pong;
	ret["RPASS"] = &Messages::rpass;
	ret["filet"] = &Messages::filet;
	return ret;
}

std::string	util::msgSender(std::vector<std::string> vc)
{
	std::string	ret;

	for (std::vector<std::string>::iterator it = vc.begin(); it != vc.end(); it++)
		ret += (*it) + " ";
	return ret;
}

std::string	util::msgSender(std::vector<std::string> vs, int start)
{
	std::string	ret;

	for (std::vector<std::string>::iterator it = vs.begin() + start; it != vs.end(); it++)
		ret += (*it) + " ";
	return ret;
}

std::vector<std::string>	util::msgCreator(std::string prefix, std::string msg)
{
	std::vector<std::string>	ret;
	ret.push_back(prefix);
	msg = ":" + msg;
	ret.push_back(msg);
	return ret;
}

std::vector<std::string>	util::msgCreator(std::string prefix, std::string errcode, std::string msg)
{
	std::vector<std::string>	ret;
	ret.push_back(":ft_irc " + errcode);
	ret.push_back(prefix);
	msg = ":" + msg;
	ret.push_back(msg);
	return ret;
}

std::vector<std::string>	util::split(std::vector<std::string> str, int start)
{
	std::vector<std::string> ret;
	for (std::vector<std::string>::iterator it = str.begin() + start; it != str.end(); it++)
		ret.push_back(*it);
	return ret;
}