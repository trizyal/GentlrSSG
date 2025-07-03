#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include <string>

#include "link.hpp"


/// @brief Represents an author with name, email, and links to social profiles.
class Author {
public:
    std::string name;
    std::string email;
    Link github;
    Link linkedin;

    int setName(const std::string& aName) {
        if (aName.empty()) {
            return -1; // Error: Name cannot be empty
        }
        name = aName;
        return 0; // Success
    }

    int setEmail(const std::string& anEmail) {
        if (anEmail.empty()) {
            return -1; // Error: Email cannot be empty
        }
        email = anEmail;
        return 0; // Success
    }

    void setGithub(const Link& aGithub)
    {
        github = aGithub;
    }

    void setLinkedin(const Link& aLinkedin)
    {
        linkedin = aLinkedin;
    }

    [[nodiscard]] std::string getName() const {
        return name;
    }

    [[nodiscard]] std::string getEmail() const {
        return email;
    }

    [[nodiscard]] Link getGithub() const {
        return github;
    }

    [[nodiscard]] Link getLinkedin() const {
        return linkedin;
    }

};



#endif //AUTHOR_HPP
