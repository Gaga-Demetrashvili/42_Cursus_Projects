#include "phonebook.h"

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
