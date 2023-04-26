/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircbot.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:23:10 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/26 13:57:14 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "channel.hpp"
class Server;
class Clients;
class Channel;

class ircbot{
public:
	ircbot(Channel &);

	void	wellcome(Server &, Clients *);
	int		checkmsg(Server &, Clients *, std::string);
private:
	std::string	name;
	std::string	cnlname;
	Channel &onwork;
};