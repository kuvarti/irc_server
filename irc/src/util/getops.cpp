/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getops.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuvarti <kuvarti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:22:30 by kuvarti           #+#    #+#             */
/*   Updated: 2023/04/21 18:27:20 by kuvarti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>

std::vector<std::string> getops()
{
	std::vector<std::string> ret;
	std::cout << "Do you want to enter op? (y/n) :";
	std::string op;
	std::cin >> op;
	if (!(op == "y"))
		return ret;
	while (op == "y") {
		std::cout << "Enter op(nickname): ";
		std::cin >> op;
		ret.push_back(op);
		std::cout << "Do you want to enter another op? (y/n) :";
		std::cin >> op;
	}
	return ret;
}
