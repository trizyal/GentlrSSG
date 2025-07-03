#include "page.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

int Page::readPageMarkdown(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line, title, content;
    std::ostringstream body;

    if (!file.is_open())
    {
        throw std::runtime_error("File not found or cannot be opened: " + filename);
    }

    bool firstLine = true;
    while (std::getline(file, line))
    {
        if (firstLine)
        {
            title = line;
            firstLine = false;
        }
        else
        {
            body << line << "\n";
        }
    }

    if (title.empty())
    {
        this ->title = "";
    }
    else
    {
        // Remove leading and trailing whitespace from the title
        title.erase(0, title.find_first_not_of(" \t"));
        title.erase(title.find_last_not_of(" \t") + 1);
        this->title = title;
    }

    if (body.str().empty())
    {
        this->content = "";
    }
    else
    {
        // Remove leading and trailing whitespace from the content
        std::string bodyContent = body.str();
        bodyContent.erase(0, bodyContent.find_first_not_of(" \t"));
        bodyContent.erase(bodyContent.find_last_not_of(" \t") + 1);
        this->content = bodyContent;
    }

    // Extract the filename without the extension or path
    this->filename = std::filesystem::path(filename).filename().replace_extension("").string();

    std::cout << "Read page: " << this->filename << std::endl;

    return 0;
}