#ifndef CONTACT_HPP 
# define CONTACT_HPP

#include <string>

class Contact {
    private:
        std::string firstName;
        std::string lastName;
        std::string nickName;
        std::string phoneNumber;
        std::string darkestSecret;

    public:
        Contact();
        ~Contact();

        std::string GetName() const;
        std::string GetSurname() const;
        std::string GetNickname() const;

        void SetName(const std::string& name);
        void SetSurname(const std::string& surname);
        void SetNick(const std::string& nick);
        void SetPhone(const std::string& phone);
        void SetSecret(const std::string& secret);   
        void InitContact(const std::string& name, const std::string& surname, const std::string& nick, 
            const std::string& phone, const std::string& secret);    
};

#endif