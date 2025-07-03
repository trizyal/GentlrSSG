#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "utils/site.hpp"


/// @brief Represents the configuration for a site, including metadata and theme settings.
class Config
{
    public:

    Site site;



    std::string theme;

    int loadConfig(std::string configPath);
};

#endif //CONFIG_HPP
