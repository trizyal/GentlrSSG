#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>


/// @brief Represents a page with title, content, filename, and layout.
class Page
{
    public:

    std::string title;
    std::string content;
    std::string filename;
    std::string layout;

    int readPageMarkdown(const std::string& filename);
    int writePageHTML(const std::string& filename);
};

#endif //PAGE_HPP
