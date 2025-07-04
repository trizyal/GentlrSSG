#ifndef SITEBUILDER_HPP
#define SITEBUILDER_HPP

#include "config.hpp"

class SiteBuilder
{
public:
    static void buildSite(const Config& config);

    static int checkPaths(const Config& config);
};

#endif //SITEBUILDER_HPP
