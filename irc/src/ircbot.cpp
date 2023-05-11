/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircbot.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:34:41 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/26 23:03:05 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "ircbot.hpp"

ircbot::ircbot(Channel &c) : onwork(c)
{
	name = "ircbot";
	cnlname = onwork.getname();
}

void ircbot::wellcome(Server &srv, Clients *cl)
{
	srv.sendmessage(*cl->getclient(), RPL_PRIVMSG(name, cnlname, "<-<-<-<-<-<-<-<-<-<-->->->->->->->->->->\n"));
	srv.sendmessage(*cl->getclient(), RPL_PRIVMSG(name, cnlname, "<-          Welcome IM ircbot         ->\n"));
	srv.sendmessage(*cl->getclient(), RPL_PRIVMSG(name, cnlname, "<-    This channel Protected by me    ->\n"));
	srv.sendmessage(*cl->getclient(), RPL_PRIVMSG(name, cnlname, "<-               ENJOY !              ->\n"));
	srv.sendmessage(*cl->getclient(), RPL_PRIVMSG(name, cnlname, "<-<-<-<-<-<-<-<-<-<-->->->->->->->->->->\n"));
}

int	ircbot::checkmsg(Server &srv, Clients *cl, std::string str)
{
	if (str.find("aq") != std::string::npos)
		srv.sendmessage(*cl->getclient(), RPL_PRIVMSG(name, cnlname, "Lutfen kufur etmeyin !\n"));
	return 1;
}