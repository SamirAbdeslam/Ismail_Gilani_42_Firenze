/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:35:01 by igilani           #+#    #+#             */
/*   Updated: 2025/07/26 19:26:51 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include <sstream>

class Contact
{
	private:
		std::string first_name;
		std::string last_name;
		std::string nickname;
		std::string phone_number;
		std::string darkest_secret;
	public:
		void setData();
		void displayBrief();
		void displayFull();
};

class Phonebook
{
	private:
		Contact contacts[8];
		int current_index;
		int total_contact;
	public:
		Phonebook();
		void addContact();
		void displayContacts();
		void displayContactDetails(std::string input);
};

#endif