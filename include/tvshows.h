#ifndef TVSHOW_H
#define TVSHOW_H

#include "content.h"
#include <iostream>
#include <sstream>

class TVShow : public Content {
private:
    int seasons;
    int episodes_per_season;
    float rent_cost_per_season;
    float purchase_cost_per_season;

public:
    TVShow(string t, string g, float r, int s, int eps, float rent, float purchase)
        : Content(t, g, r), seasons(s), episodes_per_season(eps),
          rent_cost_per_season(rent), purchase_cost_per_season(purchase) {}

    void display() const override {
        cout << "TV Show: " << title << " | Genre: " << genre << " | Rating: " << rating
             << " | Seasons: " << seasons << " | Episodes/Season: " << episodes_per_season
             << " | Rent/Season: $" << rent_cost_per_season
             << " | Purchase/Season: $" << purchase_cost_per_season << endl;
    }

    float getRentCost() const override { return seasons * rent_cost_per_season; }
    float getPurchaseCost() const override { return seasons * purchase_cost_per_season; }

    string serialize() const override {
        stringstream ss;
        ss << "TVShow|" << title << "|" << genre << "|" << rating << "|" << seasons
           << "|" << episodes_per_season << "|" << rent_cost_per_season
           << "|" << purchase_cost_per_season;
        return ss.str();
    }

    static TVShow* deserialize(const string& line)
    {
        stringstream ss(line);

        string type, t, g;
        float r;
        int s, eps;
        float rent, purchase;

        getline(ss, type, '|');
        getline(ss, t, '|');
        getline(ss, g, '|');

        ss >> r;
        ss.ignore();

        ss >> s;
        ss.ignore();

        ss >> eps;
        ss.ignore();

        ss >> rent;
        ss.ignore();

        ss >> purchase;

        return new TVShow(
            t,
            g,
            r,
            s,
            eps,
            rent,
            purchase
        );
    }
};

#endif
