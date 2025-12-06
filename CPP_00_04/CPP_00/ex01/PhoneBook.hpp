#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"
#include <stddef.h>

class PhoneBook {
    private:
        Contact contacts[8];
        size_t contactCount;
        size_t oldestContactIndex;
        size_t contactMaxCount;

        std::string truncateString(const std::string& str) const;
        
    public:
        PhoneBook();
        ~PhoneBook();

    void AddContact(Contact& contact);
    void DisplayContacts() const;
    void FillContactsWithDummyData();
};

#endif