/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:51:00 by root              #+#    #+#             */
/*   Updated: 2023/04/19 12:36:22 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Wrong use plase run with : ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	Server	srv(stoi(argv[1]), argv[2]);
	srv.loop();
}