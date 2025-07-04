#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "utils.hpp"


/// @brief Represents the configuration for a site, including metadata and theme settings.
class Config
{
    public:

    Site site;
    Author author;
    std::string theme;

    // paths
    std::string pagesPath;
    std::string templatesPath;
    std::string sitePath;

    // navigation
    std::vector<Navigation> navigation;


    int loadConfig(const std::string& configPath);
    void printConfig() const;
};

#endif //CONFIG_HPP
