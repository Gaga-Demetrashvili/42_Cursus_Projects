#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>

#include "Contact.hpp"
#include "PhoneBook.hpp"

bool isEmptyOrWhitespace(const std::string str)
{
    if (str.empty())
        return true;

    for (size_t i = 0; i < str.length(); i++)
    {
        if (!std::isspace(str[i]))
            return false;
    }

    return true;
}

bool inline indexIsOutOfRange(const char index)
{
    return (index < '0' || index > '7');
}

void getInputFromUser(std::string &input, const std::string &label)
{
    do
    {
        std::cout << label;
        std::getline(std::cin, input);

        if (isEmptyOrWhitespace(input))
            std::cout << "Input can not be empty" << std::endl;
    } while (isEmptyOrWhitespace(input));
}

void initContact(Contact &contact)
{
    const std::string labelForName = "first name: ";
    const std::string labelForSurname = "last name: ";
    const std::string labelForNick = "nickname: ";
    const std::string labelForPhone = "phone number: ";
    const std::string labelForSecret = "darkest secret: ";

    std::string input;
    std::cin.ignore();

    std::cout << "Enter contact information:" << std::endl;

    getInputFromUser(input, labelForName);
    contact.SetName(input);

    getInputFromUser(input, labelForSurname);
    contact.SetSurname(input);

    getInputFromUser(input, labelForNick);
    contact.SetNick(input);

    getInputFromUser(input, labelForPhone);
    contact.SetPhone(input);

    getInputFromUser(input, labelForSecret);
    contact.SetSecret(input);
}

bool isValidIndex(const std::string index)
{
    return (index.length() == 1 && isdigit(index[0]) && !indexIsOutOfRange(index[0]));
}

int getContactIndex(PhoneBook &phoneBook)
{
    const std::string labelForIndex = "index: ";
    std::string input;
    std::cin.ignore();
    int index;

    do
    {
        getInputFromUser(input, labelForIndex);
        if (!isValidIndex(input))
        {
            std::cout << "Please enter valid index (0-7)" << std::endl;
            continue;
        }
        index = atoi(input.c_str());
        if (index > (phoneBook.GetContactCount() - 1))
            std::cout << "There is no data on that index yet" << std::endl;
    } while (!isValidIndex(input) || (index > (phoneBook.GetContactCount() - 1)));

    return index;
}

int main()
{
    const std::string addCmd = "ADD";
    const std::string searchCmd = "SEARCH";
    const std::string exitCmd = "EXIT";
    const std::string dummyData = "DUMMYDATA";

    Contact contact;
    PhoneBook phonebook;

    std::string cmd;
    while (true)
    {
        std::cout << "Enter command: ";
        std::cin >> cmd;

        if (cmd == addCmd)
        {
            initContact(contact);
            phonebook.AddContact(contact);
        }
        else if (cmd == searchCmd)
        {
            phonebook.DisplayContacts();
            int index = getContactIndex(phonebook);
            phonebook.DisplayContact(index);
        }
        else if (cmd == exitCmd)
        {
            break;
        }
        else if (cmd == dummyData)
        {
            phonebook.FillContactsWithDummyData();
        }
        else
        {
            std::cout << "Invalid command!" << std::endl;
            std::cout << "Use following commands: ADD, SEARCH, EXIT" << std::endl;
        }
    }

    return 0;
}