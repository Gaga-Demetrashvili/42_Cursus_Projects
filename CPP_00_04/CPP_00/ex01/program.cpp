#include "phonebook.h"

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
            if(-1 == index)
                continue;
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