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
        contacts[oldestContactIndex] = contact;
        if (oldestContactIndex == contactMaxCount - 1)
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

void PhoneBook::DisplayContact(const int index) const
{
    Contact contact = contacts[index];

    std::cout << std::setw(10) << "first name: " << contact.GetName() << std::endl;
    std::cout << std::setw(10) << "last name: " << contact.GetSurname() << std::endl;
    std::cout << std::setw(10) << "nickname: " << contact.GetNickname() << std::endl;
    std::cout << std::setw(10) << "phone number: " << contact.GetPhone() << std::endl;
    std::cout << std::setw(10) << "darkest secret: " << contact.GetSecret() << std::endl;
} 

int PhoneBook::GetContactCount() const
{
    return contactCount;
}

void PhoneBook::FillContactsWithDummyData()
{
    Contact contact1;
    contact1.InitContact("John", "Smith", "JSmith", "555-0101", "Afraid of butterflies");
    AddContact(contact1);

    Contact contact2;
    contact2.InitContact("Alice", "Johnson", "AJ", "555-0102", "Loves pizza");
    AddContact(contact2);

    Contact contact3;
    contact3.InitContact("Bob", "Williams", "Bobby", "555-0103", "Collects stamps");
    AddContact(contact3);

    Contact contact4;
    contact4.InitContact("Emma", "Brown", "EmBrown", "555-0104", "Speaks 5 languages");
    AddContact(contact4);

    Contact contact5;
    contact5.InitContact("Michael", "Davis", "MikeyD", "555-0105", "Afraid of heights");
    AddContact(contact5);

    Contact contact6;
    contact6.InitContact("Sophia", "Martinez", "SophieM", "555-0106", "Professional dancer");
    AddContact(contact6);

    Contact contact7;
    contact7.InitContact("Christopher", "Anderson", "Chris", "555-0107", "Works at NASA");
    AddContact(contact7);
}