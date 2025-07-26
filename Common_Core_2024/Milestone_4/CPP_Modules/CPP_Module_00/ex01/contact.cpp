/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:55:20 by igilani           #+#    #+#             */
/*   Updated: 2025/07/26 19:47:41 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

static std::string getValidInput(const std::string& prompt)
{
	std::string input;
	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (input.empty())
			std::cout << "❌ Field cannot be empty! Please try again." << std::endl;
	} while (input.empty());
	return input;
}

void Contact::setData()
{
	std::cout << "\n📝 ADDING NEW CONTACT" << std::endl;
	std::cout << "─────────────────────" << std::endl;
	
	first_name = getValidInput("First Name: ");
	last_name = getValidInput("Last Name: ");
	nickname = getValidInput("Nickname: ");
	phone_number = getValidInput("Phone Number: ");
	darkest_secret = getValidInput("Darkest Secret: ");
	
	std::cout << "✅ Contact added successfully!" << std::endl;
}

static std::string truncateString(const std::string& str)
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void Contact::displayBrief()
{
	std::cout << std::setw(10) << truncateString(first_name) << "|"
		<< std::setw(10) << truncateString(last_name) << "|"
		<< std::setw(10) << truncateString(nickname) << "|" << std::endl;
}

void Contact::displayFull()
{
	std::cout << "\n📋 CONTACT DETAILS:" << std::endl;
	std::cout << "First Name: " << first_name << std::endl;
	std::cout << "Last Name: " << last_name << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;
	std::cout << "Phone Number: " << phone_number << std::endl;
	std::cout << "Darkest Secret: " << darkest_secret << std::endl;
}