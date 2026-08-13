#include "parser.hpp"
#include "request.hpp"
#include <vector>
#include <algorithm>
#include <cctype>

std::vector<std::string> split(const std::string& str, const std::string& delimiter){
    std::vector<std::string> splitted;

    size_t startPos = 0;
    size_t endPos = str.find(delimiter);
    while(endPos != std::string::npos){
        splitted.push_back(str.substr(startPos, endPos - startPos));
        startPos = endPos + delimiter.size();
        endPos = str.find(delimiter, startPos);
    }
    splitted.push_back(str.substr(startPos));

    return splitted;
}

void trim(std::string& str) {
    const std::string whitespace = " \t\r\f\v"; 
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        str = "";
        return; 
    }
    size_t end = str.find_last_not_of(whitespace);
    str = str.substr(start, end - start + 1);
}

std::optional<Method> parseMethod(const std::string& raw){
    static const std::map<std::string, Method> methodMap = {{"GET", Method::GET}, {"POST", Method::POST}, {"PUT", Method::PUT}, 
                    {"DELETE", Method::DELETE}, {"PATCH", Method::PATCH}, {"HEAD", Method::HEAD}, {"OPTIONS", Method::OPTIONS}};
    
    auto it = methodMap.find(raw);
    if(it != methodMap.end()) return it->second;
    return std::nullopt;
}

std::optional<Request> parseRequest(const std::string& raw){
    size_t pos = raw.find("\r\n\r\n");
    if(pos == std::string::npos) return std::nullopt;
    std::string headersPart = raw.substr(0, pos);
    std::string body = raw.substr(pos + 4);

    std::vector<std::string> headers = split(headersPart, "\r\n");
    if(headers.empty()) return std::nullopt;

    std::vector<std::string> startStr = split(headers[0], " ");
    if(startStr.size() != 3) return std::nullopt;

    std::optional<Method> method = parseMethod(startStr[0]);
    if(!method.has_value()) return std::nullopt;

    Request request;
    request.method = method.value();
    request.path = startStr[1];
    request.version = startStr[2];
    request.body = body;

    headers.erase(headers.begin());

    for(auto& str: headers){
        size_t parsePos = str.find(":");
        if(parsePos == std::string::npos) return std::nullopt;
        std::string key = str.substr(0, parsePos);
        trim(key);
        std::transform(key.begin(), key.end(), key.begin(),[](unsigned char c) {
            return std::tolower(c);
        });
        std::string value = str.substr(parsePos + 1);
        trim(value);
        request.headers[key] = value;
    }

    return request;
}