/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:42:48 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/23 22:42:48 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

#include "clients.hpp"
class Server;

class Channel{
public:
	Channel(std::string, Clients *);
	~Channel();

	void	boardcast(Server &, Clients *, std::string);
	void	joinmember(Server &, Clients *);
private:
	Clients	*_creator;
	std::string	_name;
	std::string	_topic;
	std::vector<Clients *>	_members;
	std::vector<Clients *>	_ops;

	void	boardcast(Server &, std::string);
};
