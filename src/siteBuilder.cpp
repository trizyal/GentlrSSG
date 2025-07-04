#include "siteBuilder.hpp"

#include <filesystem>
#include <iostream>
#include <unistd.h>

#define PATH_MAX 4096

std::string SiteBuilder::rootPath = "";

void SiteBuilder::buildSite(const Config& config)
{
    char result[PATH_MAX];
    const ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    const std::filesystem::path exe_path = std::string(result, (count > 0) ? count : 0);

    rootPath = exe_path.parent_path().parent_path();
    rootPath.append("/");

    checkPaths(config);
}



int SiteBuilder::checkPaths(const Config& config)
{
    // Check if the pages path exists
    if (!std::filesystem::exists(rootPath + config.pagesPath))
    {
        throw std::filesystem::filesystem_error(
        "Directory not found",
        rootPath + config.pagesPath,
        std::make_error_code(std::errc::no_such_file_or_directory)
        );
    }

    // Check if the templates path exists
    if (!std::filesystem::exists(rootPath + config.templatesPath))
    {
        std::cerr << "Templates path does not exist: " << config.templatesPath << std::endl;
        return 1;
    }

    // Check if the site path exists, create it if it doesn't
    if (!std::filesystem::exists(rootPath + config.sitePath))
    {
        std::filesystem::create_directories(rootPath + config.sitePath);
        std::cout << "Created site path: " << rootPath + config.sitePath << std::endl;
    }

    return 0;
}