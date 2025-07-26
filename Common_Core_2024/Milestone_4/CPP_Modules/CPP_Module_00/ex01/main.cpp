/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:36:57 by igilani           #+#    #+#             */
/*   Updated: 2025/07/26 19:47:41 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

int main()
{
	std::string input;
	Phonebook ph;
	
	std::cout << "┌─────────────────────────────────────────┐" << std::endl;
	std::cout << "│            📞 PHONEBOOK 📞              │" << std::endl;
	std::cout << "├─────────────────────────────────────────┤" << std::endl;
	std::cout << "│  Commands:                              │" << std::endl;
	std::cout << "│  • ADD    - Add new contact             │" << std::endl;
	std::cout << "│  • SEARCH - Search contacts             │" << std::endl;
	std::cout << "│  • EXIT   - Exit program                │" << std::endl;
	std::cout << "└─────────────────────────────────────────┘" << std::endl;
	
	while (true)
	{
		std::cout << "\n💬 Enter command: ";
		std::getline(std::cin, input);
		if (input == "ADD")
		{
			ph.addContact();
		}
		else if (input == "SEARCH")
		{
			ph.displayContacts();
			ph.displayContactDetails(input);
		}
		else if (input == "EXIT")
		{
			std::cout << "\n👋 Goodbye! Thanks for using Phonebook!" << std::endl;
			break;
		}
		else
			std::cout << "❌ Invalid command! Please use ADD, SEARCH or EXIT" << std::endl;
	}
}
