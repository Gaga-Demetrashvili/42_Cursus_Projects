#include "Contact.hpp"

Contact::Contact()
{
}

Contact::~Contact()
{
}

std::string Contact::GetName() const
{
    return firstName;
}

std::string Contact::GetSurname() const
{
    return lastName;
}

std::string Contact::GetNickname() const
{
    return nickName;
}

std::string Contact::GetPhone() const
{
    return phoneNumber;
}

std::string Contact::GetSecret() const
{
    return darkestSecret;
}

void Contact::SetName(const std::string &name)
{
    firstName = name;
}

void Contact::SetSurname(const std::string &surname)
{
    lastName = surname;
}

void Contact::SetNick(const std::string &nick)
{
    nickName = nick;
}

void Contact::SetPhone(const std::string &phone)
{
    phoneNumber = phone;
}

void Contact::SetSecret(const std::string &secret)
{
    darkestSecret = secret;
}

void Contact::InitContact(const std::string &name, const std::string &surname, const std::string &nick,
                          const std::string &phone, const std::string &secret)
{
    firstName = name;
    lastName = surname;
    nickName = nick;
    phoneNumber = phone;
    darkestSecret = secret;
}
