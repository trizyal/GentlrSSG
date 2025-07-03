#include <iostream>

#include "page.hpp"
#include "config.hpp"

int main()
{
    std::cout << "Gentlr Static Site Generator" << std::endl;

    try
    {
        Config config;
        config.loadConfig("../config.toml");

        Page page;
        page.readPageMarkdown("../pages/gentlr.md");
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error reading page: " << e.what() << std::endl;
        return 1;
    }

    // 1. Read files from /pages
    // 2. Load templates from /templates
    // 3. Generate files to /site

    return 0;
}