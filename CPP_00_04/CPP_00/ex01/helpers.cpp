#include "program.hpp"

std::string getLabel(FieldType field)
{
    switch (field)
    {
    case FIRST_NAME:
        return "First name: ";
    case LAST_NAME:
        return "Last name: ";
    case NICKNAME:
        return "Nickname: ";
    case PHONE_NUMBER:
        return "Phone number: ";
    case DARKEST_SECRET:
        return "Darkest secret: ";
    case INDEX:
        return "Enter index to display: ";
    default:
        return "";
    }
}

InputType getInputType(FieldType field)
{
    switch (field)
    {
    case FIRST_NAME:
    case LAST_NAME:
        return ALPHA;
    case PHONE_NUMBER:
        return NUMERIC;
    default:
        return ALPHANUMERIC;
    }
}

bool isValidIndex(const std::string index)
{
    return (index.length() == 1 && isdigit(index[0]) && !indexIsOutOfRange(index[0]));
}

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

bool inline indexIsOutOfRange(const char index)
{
    return (index < '0' || index > '7');
}

bool inputIsNumeric(const std::string &input)
{
    for (size_t i = 0; i < input.length(); i++)
    {
        if (!isdigit(input[i]))
            return false;
    }

    return true;
}

bool inputIsAlpha(const std::string &input)
{
    for (size_t i = 0; i < input.length(); i++)
    {
        if (!isalpha(input[i]))
            return false;
    }

    return true;
}
