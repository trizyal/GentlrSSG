#include "siteBuilder.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

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
    std::string templatePath = config.templatesPath;
#ifdef _WIN32
    rootPath.append("\\");
    templatePath.append("\\");
#else
    rootPath.append("/");
    templatePath.append("/");
#endif

    checkPaths(config);
    readTemplates(templatePath + config.theme);
    readPages(config.pagesPath);
    // Process each page with the templates


    std::cout << "Pages: " << pages.size() << std::endl;
    for (const auto& [filename, page] : pages)
    {
        // Check if the layout exists in the templates
        auto it = htmlTemplates.find(page.layout);
        if (it != htmlTemplates.end())
        {
            std::string htmlContent = it->second; // Get the template content
            // Replace placeholders in the template with page content
            htmlContent = std::regex_replace(htmlContent, std::regex(R"(\{\{ title \}\})"), page.title);
            htmlContent = std::regex_replace(htmlContent, std::regex(R"(\{\{ tagline \}\})"), page.description);
            htmlContent = std::regex_replace(htmlContent, std::regex(R"(\{\{ content \}\})"), page.htmlContent);

            // Write the processed HTML to a file in the site directory
            std::ofstream outFile(rootPath + "/" + config.sitePath + "/" + filename + ".html");
            if (outFile.is_open())
            {
                outFile << htmlContent;
                outFile.close();
                std::cout << "Generated: " << filename << ".html" << std::endl;
            }
            else
            {
                throw std::runtime_error("Failed to write HTML file: " + filename + ".html");
            }
        }
        else
        {
            throw std::runtime_error("Layout not found for page: " + filename);
        }
    }

    copyTemplateAssets(config);
}



void SiteBuilder::copyTemplateAssets(const Config& config)
{
    std::string templatePath = rootPath + config.templatesPath + "/" + config.theme;
    std::string destinationPath = rootPath + config.sitePath;

    // copy the css and js directories
    std::filesystem::path cssSource = templatePath + "/css";
    std::filesystem::path jsSource = templatePath + "/js";
    std::filesystem::path cssDestination = destinationPath + "/css";
    std::filesystem::path jsDestination = destinationPath + "/js";
    try
    {
        // Create destination directories if they don't exist
        std::filesystem::create_directories(cssDestination);
        std::filesystem::create_directories(jsDestination);

        // Copy CSS files
        for (const auto& entry : std::filesystem::directory_iterator(cssSource))
        {
            if (entry.is_regular_file())
            {
                std::filesystem::copy(entry.path(),
                    cssDestination / entry.path().filename(),
                    std::filesystem::copy_options::overwrite_existing);
            }
        }

        // Copy JS files
        for (const auto& entry : std::filesystem::directory_iterator(jsSource))
        {
            if (entry.is_regular_file())
            {
                std::filesystem::copy(entry.path(),
                    jsDestination / entry.path().filename(),
                    std::filesystem::copy_options::overwrite_existing
);
            }
        }

        std::cout << "Assets copied successfully." << std::endl;
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Failed to copy template assets: " + std::string(e.what()));
    }
}




void SiteBuilder::readTemplates(const std::string& path)
{
    // Iterate through all files in the templates directory
    for (const auto& entry : std::filesystem::directory_iterator(rootPath + path))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".html")
        {
            std::string layoutName = entry.path().filename().replace_extension("").string();
            std::string htmlTemplate = getTemplateFromFile(entry.path().string());
            htmlTemplates[layoutName] = htmlTemplate;
        }
    }

    std::cout << "Templates: " << htmlTemplates.size() << std::endl;

    // Check if any templates were found
    if (htmlTemplates.empty())
    {
        throw std::runtime_error("No templates found in the specified directory: " + path);
    }
}




std::string SiteBuilder::getTemplateFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open template file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the entire file into buffer
    return buffer.str();     // Return as a string
}


void SiteBuilder::readPages(const std::string& path)
{
    // Iterate through all files in the pages directory
    for (const auto& entry : std::filesystem::directory_iterator(rootPath + path))
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
        throw std::runtime_error("No pages found in the specified directory: " + path);
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