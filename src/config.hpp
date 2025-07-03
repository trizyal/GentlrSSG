#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "author.hpp"
#include "site.hpp"


/// @brief Represents the configuration for a site, including metadata and theme settings.
class Config
{
    public:

    Site site;
    Author author;
    std::string theme;

    int loadConfig(const std::string& configPath);
};

#endif //CONFIG_HPP
