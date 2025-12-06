#include <string>
#include <iostream>
#include <cctype>

#include "Contact.hpp"
#include "PhoneBook.hpp"

bool isEmptyOrWhitespace(std::string str)
{
    if (str.empty())
        return true;

    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isspace(str[i]))
            return false;
    }
    
    return true;
}

void getInputFromUser(std::string& contactInfo, const std::string& label)
{
    do
    {
        std::cout << label;
        std::getline(std::cin, contactInfo);

        if(isEmptyOrWhitespace(contactInfo))
            std::cout << "Input can not be empty" << std::endl;
    } while (isEmptyOrWhitespace(contactInfo));

}

void initContact(Contact& contact) {
    const std::string labelForName = "first name: ";
    const std::string labelForSurname = "last name: ";
    const std::string labelForNick = "nickname: ";
    const std::string labelForPhone = "phone number: ";
    const std::string labelForSecret = "darkest secret: ";

    std::string contactInfo;
    std::cin.ignore();

    std::cout << "Enter contact information:" << std::endl;

    getInputFromUser(contactInfo, labelForName);
    contact.SetName(contactInfo);

    getInputFromUser(contactInfo, labelForSurname);
    contact.SetSurname(contactInfo);
    
    getInputFromUser(contactInfo, labelForNick);
    contact.SetNick(contactInfo);

    getInputFromUser(contactInfo, labelForPhone);
    contact.SetPhone(contactInfo);

    getInputFromUser(contactInfo, labelForSecret);
    contact.SetSecret(contactInfo);

    // std::cout << contact.GetName() << std::endl;
    // std::cout << contact.GetSurname() << std::endl;
    // std::cout << contact.GetNickname() << std::endl;
}

int main() {
    const std::string addCmd = "ADD";
    const std::string searchCmd = "SEARCH";
    const std::string exitCmd = "EXIT";

    Contact contact;
    PhoneBook phonebook;

    std::string cmd;
    while (true) {
        std::cout << "Enter command: ";
        std::cin >> cmd;

        if (cmd == addCmd){
            initContact(contact);
            phonebook.AddContact(contact);
        }
        else if (cmd == searchCmd){
            phonebook.FillContactsWithDummyData();
            phonebook.DisplayContacts();
        }
        else if (cmd == exitCmd){
            break;
        }
        else {
            std::cout << "Invalid command!" << std::endl;
            std::cout << "Use following commands: ADD, SEARCH, EXIT" << std::endl;
        }
    }

    return 0;
}