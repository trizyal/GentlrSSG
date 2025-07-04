#include <filesystem>
#include <iostream>

#include "config.hpp"
#include "siteBuilder.hpp"

int main()
{
    try
    {
        // Load the configuration file
        Config config;
        config.loadConfig("../config.toml");
        config.printConfig();

        // Read pages
        SiteBuilder::buildSite(config);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // 1. Read files from /pages
    // 2. Load templates from /templates
    // 3. Generate files to /site

    return 0;
}