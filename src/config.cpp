#include "config.hpp"

#include <iostream>
#include <cpptoml/cpptoml.h>



int Config::loadConfig(const std::string& configPath)
{
    auto config = cpptoml::parse_file(configPath);

    return 0;
}