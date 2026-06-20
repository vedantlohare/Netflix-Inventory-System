#ifndef USER_UTILS_H
#define USER_UTILS_H

#include "user.h"
#include <filesystem>

namespace fs = std::filesystem;

inline bool userExists(const string& username) {
    return fs::exists("users/" + username + ".txt");
}

inline User* loadUser(const string& username) {
    ifstream file("users/" + username + ".txt");
    string line;
    getline(file, line);
    file.close();
    return User::deserialize(line);
}

inline void saveUser(User* user) {
    ofstream file("users/" + user->getUsername() + ".txt");
    file << user->serialize();
    file.close();
}

#endif
