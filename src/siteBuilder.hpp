#ifndef SITEBUILDER_HPP
#define SITEBUILDER_HPP

#include <unordered_map>

#include "config.hpp"
#include "page.hpp"

class SiteBuilder
{
public:
    std::string rootPath;

    std::unordered_map<std::string, Page> pages;

    // htmlTemplates["layout"] = htmlTemplateString
    std::unordered_map<std::string, std::string> htmlTemplates;

    void buildSite(const Config& config);

    void checkPaths(const Config& config) const;

    void readTemplates(const std::string& path);
    static std::string getTemplateFromFile(const std::string& string);


    void readPages(const std::string& path);

    void copyTemplateAssets(const Config& config);

};

#endif //SITEBUILDER_HPP
