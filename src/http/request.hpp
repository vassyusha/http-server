#pragma once

#include <string>
#include <map>

enum class Method{
    GET,
    POST,
    PUT,
    DELETE,
    PATCH,
    HEAD,
    OPTIONS
};

struct Request{
    Method method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};