/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftransfer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:27:55 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/22 18:13:26 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <fstream>
class Clients;

#define FILET_STATUS_WAITING	0
#define FILET_STATUS_ACCEPTED	1
#define FILET_STATUS_REJECTED	2

class filet{
public:
	filet(Clients *source, Clients *target, std::string filename);
	~filet();

	int	setfile(std::fstream *);

	std::fstream	*getfile() const	{ return _file;		}
	Clients *		getSource() const	{ return source;	}
	Clients *		getTarget() const	{ return target;	}
	std::string		getFilename() const	{ return filename;	}
	std::string		getFilepath() const	{ return filepath;	}
private:
	int	status;
	std::fstream	*_file;

	Clients *	source;
	Clients *	target;
	std::string	filepath;
	std::string	filename;
	//🤔 🤔 🤔 🤔 🤔
};