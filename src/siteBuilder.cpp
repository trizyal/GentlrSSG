#include "siteBuilder.hpp"

#include <filesystem>
#include <iostream>


void SiteBuilder::buildSite(const Config& config)
{
    checkPaths(config);
}



int SiteBuilder::checkPaths(const Config& config)
{
    // Check if the pages path exists
    if (!std::filesystem::exists(config.pagesPath))
    {
        throw std::filesystem::filesystem_error(
        "Directory not found",
        config.pagesPath,
        std::make_error_code(std::errc::no_such_file_or_directory)
        );
    }

    // Check if the templates path exists
    if (!std::filesystem::exists(config.templatesPath))
    {
        std::cerr << "Templates path does not exist: " << config.templatesPath << std::endl;
        return 1;
    }

    // Check if the site path exists, create it if it doesn't
    if (!std::filesystem::exists(config.sitePath))
    {
        std::filesystem::create_directories(config.sitePath);
        std::cout << "Created site path: " << config.sitePath << std::endl;
    }

    return 0;
}