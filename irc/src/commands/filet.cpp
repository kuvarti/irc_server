/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filet.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:02:18 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/22 21:01:12 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

static int	flset(struct pollfd sock, Server &srv, std::vector<std::string> token)
{
	if (token.size() != 4)
	{
		srv.sendmessage(sock, "FileTransfer : Too Much parameter.");
		return 1;
	}
	filet	*tmp = new filet(&(*(util::findclient(srv.getclient(), sock))), &(*(util::findnick(srv.getclient(), token[2]))) , token[3]);
	if (tmp->setfile(new std::fstream(token[3], std::fstream::in)))
		return 1;
	srv.insertfile(tmp);
	srv.sendmessage(*(util::findnick(srv.getclient(), token[2])->getclient()), 
		RPL_FILET(util::findclient(srv.getclient(), sock)->getnickname(), 
		" /filet get " + util::findclient(srv.getclient(), sock)->getnickname() + " " + tmp->getFilename() + " destPath"));
	srv.sendmessage(sock, "FileTransfer : Transfer request set.");
	return 0;
}

static int	flget(struct pollfd sock, Server &srv, std::vector<std::string> token)
{
	if (token.size() != 5)
	{
		srv.sendmessage(sock, "FileTransfer : Too much or not enough parameter");
		return 1;
	}
	std::vector<filet *>::iterator it = filet::filetfinder(srv.getfilet(), &(*(util::findnick(srv.getclient(), token[2]))), token[3]);
	if (it == srv.getfilet().end())
	{
		srv.sendmessage(sock, "FileTransfer Failed. File not found!");
		return 1;
	}
	std::fstream ofs(token[4] + "/" + (*it)->getFilename(), std::fstream::out);
	std::fstream *ifs = (*it)->getfile();
	if (ofs.is_open())
		ofs << ifs->rdbuf();
	srv.sendmessage(sock, "FileTransfer success. Transfer request deleted.");
	srv.sendmessage(*(util::findnick(srv.getclient(), token[2]))->getclient(), "FileTransfer success. Transfer request deleted.");
	srv.removefile(it);
	return 0;
}

int	Messages::filet(struct pollfd sock, Server &srv, std::vector<std::string> token)
{
	if (token.size() < 4)
	{
		srv.sendmessage(sock, ERR_NEEDMOREPARAMS(util::findclient(srv.getclient(), sock)->getnickname(), token[0]));
		return (1);
	}
	if (token[1] == "set")
		return flset(sock, srv, token);
	else if (token[1] == "get")
		return flget(sock, srv, token);
	else
	{
		srv.sendmessage(sock, ERR_UNKNOWNCOMMAND(util::findclient(srv.getclient(), sock)->getnickname(), token[0] + token [1]));
		return (1);
	}
}