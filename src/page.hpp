#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>

class Page
{
    public:

    std::string title;
    std::string content;
    std::string filename;

    int readPage(const std::string& filename);
    int writePage(const std::string& filename);
};

#endif //PAGE_HPP
