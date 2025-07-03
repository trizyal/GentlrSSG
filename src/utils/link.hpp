#ifndef LINK_HPP
#define LINK_HPP

#include <string>


/// Represents a hyperlink with a URL, label, and optional icon.
class Link
{
    std::string url;
    std::string label;
    std::string icon; // Optional icon

    public:
    Link( )
        : url(""), label(""), icon("") {}

    Link( const Link& other )
        : url(other.url), label(other.label), icon(other.icon) {}

    int setURL(const std::string& aUrl)
    {
        if (aUrl.empty())
        {
            return -1; // Error: URL cannot be empty
        }
        url = aUrl;
        return 0; // Success
    }

    int setLabel(const std::string& aLabel)
    {
        if (aLabel.empty())
        {
            return -1; // Error: Label cannot be empty
        }
        label = aLabel;
        return 0; // Success
    }

    int setIcon(const std::string& aIcon)
    {
        if (aIcon.empty())
        {
            return -1; // Error: Icon cannot be empty
        }
        icon = aIcon;
        return 0; // Success
    }

    [[nodiscard]] std::string getURL() const
    {
        return url;
    }

    [[nodiscard]] std::string getLabel() const
    {
        return label;
    }

    [[nodiscard]] std::string getIcon() const
    {
        return icon;
    }

};

#endif //LINK_HPP
