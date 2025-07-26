/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:33:09 by igilani           #+#    #+#             */
/*   Updated: 2025/07/26 19:47:40 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

Phonebook::Phonebook() : current_index(0), total_contact(0) {}

void Phonebook::addContact()
{
	contacts[current_index].setData();
	current_index = (current_index + 1) % 8;
	if (total_contact < 8)
		total_contact++;
}

void Phonebook::displayContacts()
{
	if (total_contact == 0)
	{
		std::cout << "\n📝 No contacts found. Use ADD to create your first contact!" << std::endl;
		return;
	}
	
	std::cout << "\n📋 CONTACTS LIST:" << std::endl;
	std::cout << std::setw(10) << "Index" << "|"
		<< std::setw(10) << "First Name" << "|"
		<< std::setw(10) << "Last Name" << "|"
		<< std::setw(10) << "Nickname" << "|" << std::endl;
	std::cout << "─────────────────────────────────────────────" << std::endl;
	
	for (int i = 0; i < total_contact; i++)
	{
		std::cout << std::setw(10) << i << "|";
		contacts[i].displayBrief();
	}
}

static bool isNumeric(std::string& input)
{
	if (input.empty())
		return (false);
	for (size_t i = 0; i < input.length(); ++i)
	{
		if (!std::isdigit(input[i]))
			return (false);
	}
	return (true);
}

void Phonebook::displayContactDetails(std::string input)
{
	if (total_contact == 0)
		return;
		
	int index = 0;
	
	std::cout << "\n🔍 Enter contact index to view details: ";
	std::getline(std::cin, input);
	
	std::stringstream ss(input);
	ss >> index;
	if (isNumeric(input) && index >= 0 && index < total_contact)
		contacts[index].displayFull();
	else
	{
		std::cout << "\n❌ Error: Invalid index! Please enter a number between 0 and " 
			<< total_contact - 1 << std::endl;
		return;
	}
}