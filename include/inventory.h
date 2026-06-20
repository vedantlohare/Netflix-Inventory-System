#ifndef INVENTORY_H
#define INVENTORY_H

#include "movie.h"
#include "tvshows.h"
#include <vector>
#include <fstream>

class Inventory {
private:
    vector<Content*> contents;

public:
    ~Inventory() {
        for (auto c : contents) delete c;
    }

    void addContent(Content* c) {
        contents.push_back(c);
    }

    void displayAll() const {
        for (const auto& c : contents)
            c->display();
    }

    void displayByGenre(const string& genre) const {
        for (const auto& c : contents)
            if (c->getGenre() == genre)
                c->display();
    }

    Content* searchByTitle(const string& title) {
        for (auto& c : contents)
            if (c->getTitle() == title)
                return c;
        return nullptr;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& c : contents)
            file << c->serialize() << "\n";
        file.close();
    }

    void loadFromFile(const string& filename) {
        for(auto c : contents)
        delete c;

        contents.clear();
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            if (line.find("Movie|") == 0)
                contents.push_back(Movie::deserialize(line));
            else if (line.find("TVShow|") == 0)
                contents.push_back(TVShow::deserialize(line));
        }
        file.close();
    }
};

#endif
