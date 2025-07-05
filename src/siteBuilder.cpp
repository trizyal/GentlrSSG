#include "siteBuilder.hpp"

#include <filesystem>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define PATH_MAX_2 4096



void SiteBuilder::buildSite(const Config& config)
{
    char result[PATH_MAX_2];

#ifdef _WIN32
    DWORD count = GetModuleFileNameA(NULL, result, PATH_MAX_2);
#else
    const ssize_t count = readlink("/proc/self/exe", result, PATH_MAX_2);
#endif

    const std::filesystem::path exe_path = std::string(result, (count > 0) ? count : 0);

    rootPath = exe_path.parent_path().parent_path().string();

#ifdef _WIN32
    rootPath.append("\\");
#else
    rootPath.append("/");
#endif

    checkPaths(config);
    readPages(config);

    std::cout << "Pages: " << pages.size() << std::endl;
    for (const auto& [filename, page] : pages)
    {
        std::cout << "Page: " << filename << ", Title: " << page.title << std::endl;
    }
}


void SiteBuilder::readPages(const Config& config)
{
    // Iterate through all files in the pages directory
    for (const auto& entry : std::filesystem::directory_iterator(rootPath + config.pagesPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".md")
        {
            Page page;
            page.readPage(entry.path().string());
            pages[page.filename] = page;
        }
    }

    // Check if any pages were found
    if (pages.empty())
    {
        throw std::runtime_error("No pages found in the specified directory: " + config.pagesPath);
    }
}



void SiteBuilder::checkPaths(const Config& config) const
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
        throw std::filesystem::filesystem_error(
        "Directory not found",
        rootPath + config.templatesPath,
        std::make_error_code(std::errc::no_such_file_or_directory)
        );
    }

    // Check if the site path exists, create it if it doesn't
    if (!std::filesystem::exists(rootPath + config.sitePath))
    {
        std::filesystem::create_directories(rootPath + config.sitePath);
        std::cout << "Created site path: " << rootPath + config.sitePath << std::endl;
    }
}