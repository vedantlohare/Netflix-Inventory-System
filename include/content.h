
#ifndef CONTENT_H
#define CONTENT_H

#include <string>
using namespace std;

class Content {
protected:
    string title;
    string genre;
    float rating;


public:
    Content(string t, string g, float r) : title(t), genre(g), rating(r) {}

    virtual void display() const = 0;
    virtual float getRentCost() const = 0;
    virtual float getPurchaseCost() const = 0;

    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    float getRating() const { return rating; }


    virtual string serialize() const = 0;
    virtual ~Content() {}
};

#endif
