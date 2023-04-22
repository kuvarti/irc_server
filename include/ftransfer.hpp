/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftransfer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:27:55 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/22 15:54:33 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
class Clients;

class CTCP{
public:
	CTCP(Clients *source, Clients *target, std::string filename);
	~CTCP();

	Clients *	getSource() const	{ return source;	}
	Clients *	getTarget() const	{ return target;	}
	std::string	getFilename() const	{ return filename;	}
	std::string	getFilepath() const	{ return filepath;	}
private:
	Clients *	source;
	Clients *	target;
	std::string	filepath;
	std::string	filename;
	//🤔 🤔 🤔 🤔 🤔
};