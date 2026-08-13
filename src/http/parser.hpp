#pragma once

#include "request.hpp"
#include <optional>
#include <string>


std::optional<Method> parseMethod(const std::string& raw);
std::optional<Request> parseRequest(const std::string& raw);
