#include <stddef.h>
#include <iostream>
#include <iomanip>

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : contactCount(0), oldestContactIndex(0), contactMaxCount(8) {
}

PhoneBook::~PhoneBook() {
}

void PhoneBook::AddContact(Contact& contact){
    if (contactCount == contactMaxCount) {
        for (size_t i = oldestContactIndex; i < contactMaxCount - 1; i++)
        {
            contacts[i + 1] = contacts[i];
        }

        contacts[oldestContactIndex] = contact;
        if (oldestContactIndex == contactMaxCount)
            oldestContactIndex = 0;
        else
            oldestContactIndex++;
    }
    else {
        contacts[contactCount] = contact;
        contactCount++;
    }
}

std::string PhoneBook::truncateString(const std::string& str) const
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void PhoneBook::DisplayContacts() const
{
    std::cout << std::setw(10) << "index" << "|";
    std::cout << std::setw(10) << "first name" << "|";
    std::cout << std::setw(10) << "last name" << "|";
    std::cout << std::setw(10) << "nickname" << "|";
    std::cout << std::endl;

    for (size_t i = 0; i < contactCount; i++)
    {
        std::cout << std::setw(10) << i << "|";
        std::cout << std::setw(10) << truncateString(contacts[i].GetName()) << "|";
        std::cout << std::setw(10) << truncateString(contacts[i].GetSurname()) << "|";
        std::cout << std::setw(10) << truncateString(contacts[i].GetNickname()) << "|";
        std::cout << std::endl;
    }
}

void PhoneBook::FillContactsWithDummyData()
{
    Contact contact1;
    contact1.InitContact("John", "Smith", "JSmith", "555-0101", "Afraid of butterflies");
    AddContact(contact1);
}