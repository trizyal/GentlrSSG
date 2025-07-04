#include "config.hpp"

#include <iostream>
#include <vector>
#include <cpptoml/cpptoml.h>
#include "utils.hpp"



void Config::printConfig() const
{
    // Site
    std::cout << "Site Name: " << this->site.name << std::endl;
    std::cout << "Description: " << this->site.description << std::endl;
    std::cout << "Logo Path: " << this->site.logoPath << std::endl;

    // Author
    std::cout << "Author Name: " << this->author.name << std::endl;
    std::cout << "Author Email: " << this->author.email << std::endl;
    std::cout << "Author Socials: "<< this->author.socials.size() << std::endl;
    for (const auto& [url, label, icon] : this->author.socials)
    {
        std::cout << "  - " << label << ": " << url << " (Icon: " << icon << ")" << std::endl;
    }

    // Paths
    std::cout << "Pages Path: " << this->pagesPath << std::endl;
    std::cout << "Templates Path: " << this->templatesPath << std::endl;
    std::cout << "Site Path: " << this->sitePath << std::endl;

    // Theme
    std::cout << "Theme: " << this->theme << std::endl;

    // Navigation
    std::cout << "Navigation Links: " << this->navigation.size() <<std::endl;
    for (const auto& [label, url] : this->navigation)
    {
        std::cout << "  - " << label << ": " << url << std::endl;
    }
}



int Config::loadConfig(const std::string& configPath)
{
    const auto config = cpptoml::parse_file(configPath);

    // site data
    this->site.name = *config->get_as<std::string>("title");
    this->site.description = *config->get_as<std::string>("description");
    this->site.logoPath = *config->get_as<std::string>("logo");

    // author data
    if (const auto author = config->get_table("author"))
    {
        this->author.name = *author->get_as<std::string>("name");
        this->author.email = *author->get_as<std::string>("email");

        // Get array of tables (socials)
        if (const auto socials = author->get_table_array("socials")) {
            for (const auto& entry : *socials) {
                Link socialLink;
                socialLink.label = *entry->get_as<std::string>("label");
                socialLink.url = *entry->get_as<std::string>("url");
                socialLink.icon = *entry->get_as<std::string>("icon");
                this->author.socials.push_back(socialLink);
            }
        }
    }

    // paths
    if (const auto paths_tbl = config->get_table("paths")) {
        // add ../ before the paths to make them relative to the config file
        this->pagesPath = *paths_tbl->get_as<std::string>("pages");
        // if (!this->pagesPath.starts_with("../")) {
        //     this->pagesPath = "../" + this->pagesPath;
        // }
        this->templatesPath = *paths_tbl->get_as<std::string>("templates");
        // if (!this->templatesPath.starts_with("../")) {
        //     this->templatesPath = "../" + this->templatesPath;
        // }
        this->sitePath = *paths_tbl->get_as<std::string>("output");
        // if (!this->sitePath.starts_with("../")) {
        //     this->sitePath = "../" + this->sitePath;
        // }
    }

    // template / theme
    if (const auto template_tbl = config->get_table("template")) {
        this->theme = *template_tbl->get_as<std::string>("theme");
    }

    // navigation links
    if (const auto nav_tbl = config->get_table("nav")) {
        if (const auto nav_links = nav_tbl->get_table_array("links")) {
            for (const auto& link : *nav_links) {
                Navigation navLink;
                navLink.label = *link->get_as<std::string>("label");
                navLink.url = *link->get_as<std::string>("url");
                this->navigation.push_back(navLink);
            }
        }
    }

    return 0;
}