#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>



struct Site
{
    std::string name;
    std::string description;
    std::string logoPath;
};

struct Link
{
    std::string url;
    std::string label;
    std::string icon; // Optional icon
};

struct Author {
    std::string name;
    std::string email;
    std::vector<Link> socials;
};

struct Navigation
{
    std::string label;
    std::string url;
};



#endif //UTILS_HPP
