#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <stddef.h>

#include "Contact.hpp"
#include "PhoneBook.hpp"

// Validations
bool isEmptyOrWhitespace(const std::string str);

static inline bool indexIsOutOfRange(const char index)
{
    return (index < '0' || index > '7');
}

inline bool isValidIndex(const std::string index)
{
    return (index.length() == 1 && isdigit(index[0]) && !indexIsOutOfRange(index[0]));
}

// Inputs
void getInputFromUser(std::string &input, const std::string &label);
int getContactIndex(PhoneBook &phoneBook);
void initContact(Contact &contact);

#endif