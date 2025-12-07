#include "phonebook.h"

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
        {
            std::cout << "There is no data on that index yet" << std::endl;
            return -1;
        }
    } while (!isValidIndex(input) || (index > (phoneBook.GetContactCount() - 1)));

    return index;
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