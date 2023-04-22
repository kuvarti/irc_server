/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftransfer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:30:00 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/22 18:14:24 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

filet::filet(Clients *source, Clients *target, std::string filename)
{
	this->source = source;
	this->target = target;
	this->filename = std::string(filename.begin() + filename.find_last_of("/") + 1, filename.end());
	this->filepath = std::string(filename.begin(), filename.begin() + filename.find_last_of("/") + 1);
}

filet::~filet()
{
	delete _file;
}

int	filet::setfile(std::fstream *s)
{
	_file = s;
	if (_file->fail())
		return 1;
	else
		return 0;
}