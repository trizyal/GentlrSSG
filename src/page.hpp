#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>


class Page
{
    public:

    std::string filename;

    // TOML Metadata
    // Possibly could be an unordered_map to allow
    // for more flexible metadata
    std::string title;
    std::string description;
    std::string layout;
    std::string date;
    std::string permalink;

    // Markdown Content in HTML
    std::string htmlContent;


    void readPage(const std::string& filename);

    static std::pair<std::string, std::string> extractTomlAndMarkdown(const std::string& filename);
    void setMetadata(const std::string &tomlContent);
    void markdownToHtml(const std::string& md);

};

#endif //PAGE_HPP
