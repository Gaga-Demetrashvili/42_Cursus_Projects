#include "Contact.hpp"
#include "PhoneBook.hpp"
#include "program.hpp"

bool inputValidation(std::string &input, const FieldType field)
{
    InputType inputType = getInputType(field);
    const size_t phoneNumberLen = 9;

    if (ALPHA == inputType && !inputIsAlpha(input))
    {
        std::cout << "Input should contain only letters" << std::endl;
        return false;
    }
    else if (NUMERIC == inputType && (!inputIsNumeric(input) || input.length() < phoneNumberLen))
    {
        if (!inputIsNumeric(input))
            std::cout << "Input should contain only numbers" << std::endl;
        else
            std::cout << "Phone number should have at least 9 digits" << std::endl;
        return false;
    }

    return true;
}

void getInputFromUser(std::string &input, const FieldType field)
{
    bool inputValidationRes = false;

    do
    {
        std::cout << getLabel(field);
        std::getline(std::cin, input);

        if (std::cin.eof())
        {
            std::cout << std::endl
                      << "EOF" << std::endl;
            exit(0);
        }
        if (std::cin.fail())
        {
            std::cout << "Input error" << std::endl;
            exit(0);
        }

        if (isEmptyOrWhitespace(input))
            std::cout << "Input can not be empty" << std::endl;

        inputValidationRes = inputValidation(input, field);

    } while (isEmptyOrWhitespace(input) || !inputValidationRes);
}

void initContact(Contact &contact)
{
    std::string input;
    std::cin.ignore();

    getInputFromUser(input, FIRST_NAME);
    contact.SetName(input);

    getInputFromUser(input, LAST_NAME);
    contact.SetSurname(input);

    getInputFromUser(input, NICKNAME);
    contact.SetNick(input);

    getInputFromUser(input, PHONE_NUMBER);
    contact.SetPhone(input);

    getInputFromUser(input, DARKEST_SECRET);
    contact.SetSecret(input);
}

int getContactIndex(PhoneBook &phoneBook)
{
    std::cout << std::endl;

    std::string input;
    std::cin.ignore();
    int index;

    do
    {
        getInputFromUser(input, INDEX);
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
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::cin >> cmd;

        if (std::cin.eof())
        {
            std::cout << std::endl
                      << "EOF" << std::endl;
            break;
        }
        if (std::cin.fail())
        {
            std::cout << "Input error" << std::endl;
            break;
        }

        if (cmd == addCmd)
        {
            initContact(contact);
            phonebook.AddContact(contact);
        }
        else if (cmd == searchCmd)
        {
            phonebook.DisplayContacts();
            int index = getContactIndex(phonebook);
            if (-1 == index)
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

        std::cout << std::endl;
    }

    return 0;
}