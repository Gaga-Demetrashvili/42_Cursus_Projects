#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>

enum FieldType
{
    FIRST_NAME,
    LAST_NAME,
    NICKNAME,
    PHONE_NUMBER,
    DARKEST_SECRET,
    INDEX
};

enum InputType
{
    ALPHA,
    NUMERIC,
    ALPHANUMERIC
};

std::string getLabel(FieldType field);
InputType getInputType(FieldType field);
bool isEmptyOrWhitespace(const std::string str);
bool inline indexIsOutOfRange(const char index);
bool inputIsNumeric(const std::string &input);
bool inputIsAlpha(const std::string &input);
bool isValidIndex(const std::string index);

#endif