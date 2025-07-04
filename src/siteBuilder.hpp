#ifndef SITEBUILDER_HPP
#define SITEBUILDER_HPP

#include <unordered_map>

#include "config.hpp"
#include "htmlTemplate.hpp"
#include "page.hpp"

class SiteBuilder
{
public:
    std::string rootPath;

    std::unordered_map<std::string, Page> pages;
    std::unordered_map<std::string, htmlTemplate> htmlTemplates;

    void buildSite(const Config& config);

    void checkPaths(const Config& config) const;
    void readPages(const Config& config);

};

#endif //SITEBUILDER_HPP
