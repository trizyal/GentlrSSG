#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config
{
    public:

    std::string siteUrl;
    std::string siteName;
    std::string siteDescription;
    std::string siteLogo;

    std::string authorName;
    std::string authorEmail;
    std::string authorGitHub;
    std::string authorLinkedIn;

    std::string theme;

    int loadConfig(std::string configPath);
};

#endif //CONFIG_HPP
