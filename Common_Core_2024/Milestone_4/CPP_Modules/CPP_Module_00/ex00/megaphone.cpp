/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:21:56 by igilani           #+#    #+#             */
/*   Updated: 2025/07/26 17:31:31 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			for(int j = 0; argv[i][j]; ++j)
			{
				std::cout << (char)std::toupper(argv[i][j]);
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	return (0);
}