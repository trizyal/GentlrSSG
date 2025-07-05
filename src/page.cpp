#include "page.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cpptoml/cpptoml.h>
#include <md4c/src/md4c-html.h>
#include <md4c/src/md4c.h>



void Page::readPage(const std::string& filename)
{
    this->filename = std::filesystem::path(filename).filename().replace_extension("").string();

    auto [mdContent, tomlContent] = extractTomlAndMarkdown(filename);
    setMetadata(tomlContent);
    markdownToHtml(mdContent);
}


void Page::markdownToHtml(const std::string& md)
{
    std::string html;

    // Callback to receive HTML output from md_html()
    auto callback = [](const MD_CHAR* text, MD_SIZE size, void* userdata) {
        auto* out = static_cast<std::string*>(userdata);
        out->append(text, size);
    };

    const int result = md_html(
        md.c_str(), md.size(),
        callback, &html,
        // Parser flags (can OR multiple)
        MD_FLAG_TABLES | MD_FLAG_STRIKETHROUGH | MD_FLAG_TASKLISTS,
        // Renderer flags (can OR multiple)
        MD_HTML_FLAG_SKIP_UTF8_BOM
    );

    if (result != 0) {
        throw std::runtime_error("md_html failed to convert markdown to HTML.");
    }

    htmlContent = html;
}




void Page::setMetadata(const std::string &tomlContent)
{
    std::istringstream ss(tomlContent);
    cpptoml::parser p{ss};
    const auto metaData = p.parse();

    this->title = *metaData->get_as<std::string>("title");
    this->description = *metaData->get_as<std::string>("description");
    this->layout = *metaData->get_as<std::string>("layout");
    this->date = *metaData->get_as<std::string>("date");
    this->permalink = *metaData->get_as<std::string>("permalink");
}



std::pair<std::string, std::string> Page::extractTomlAndMarkdown(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::ostringstream toml, md;
    enum {NONE, TOML, MARKDOWN} state = NONE;

    if (!file.is_open())
    {
        throw std::runtime_error("File not found or cannot be opened: " + filename);
    }

    while (std::getline(file, line))
    {
        if (line == "+++")
        {
            if (state == NONE) {state = TOML;}
            else if (state == TOML) {state = MARKDOWN;}
            continue;
        }
        if (state == TOML) {toml << line << "\n";}
        else if (state == MARKDOWN) {md << line << "\n";}
    }

    return std::make_pair(md.str(), toml.str());
}


