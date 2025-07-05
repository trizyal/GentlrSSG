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

    // Markdown Content
    std::string content;


    void readPage(const std::string& filename);

    static std::pair<std::string, std::string> extractTomlAndMarkdown(const std::string& filename);
    void getMetadata(const std::string &tomlContent);

};

#endif //PAGE_HPP
