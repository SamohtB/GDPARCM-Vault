#pragma once

#include <string>
#include <vector>
#include <sstream>

class StringUtils
{
public:
	static std::vector<std::string> split(const std::string& s, char delimiter)
	{
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
	}
};
