#include "../include/SecurityUtils.h"
#include <functional>

std::string hashPassword(
    const std::string& password
)
{
    return std::to_string(
        std::hash<std::string>{}(password)
    );
}