
#ifndef CONTENT_H
#define CONTENT_H

#include <string>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Content {
protected:
    string title;
    string genre;
    float rating;
    vector<int> ratings;


public:
    Content(string t, string g, float r) : title(t), genre(g), rating(r) {}

    virtual void display() const = 0;
    virtual float getRentCost() const = 0;
    virtual float getPurchaseCost() const = 0;

    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    float getRating() const { return rating; }
    void addRating(int r)
    {
        if(r >= 1 && r <= 5)
        {
            ratings.push_back(r);
        }
    }

    float getAverageRating() const
    {
        if(ratings.empty())
            return 0;

        float sum = 0;

        for(int r : ratings)
            sum += r;

        return sum / ratings.size();
    }


    virtual string serialize() const = 0;
    virtual ~Content() {}
};

#endif
