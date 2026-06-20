#ifndef USER_H
#define USER_H

#include "content.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;


class User {
private:
    string username;
    vector<string> rented_titles;
    vector<string> purchased_titles;
    float charges_due;
    string passwordHash;
    bool isAdmin;
    vector<string> watchlist_titles;
    vector<string> watch_history;
    string favouriteGenre;
    map<string,int> genreCount;

public:
    // Constructor
    User(const string& uname, const string& passHash, bool admin = false) : username(uname), passwordHash(passHash), isAdmin(admin), charges_due(0.0f) {}

    // Getters
    string getUsername() const { return username; }
    float getChargesDue() const { return charges_due; }
    string getPasswordHash() const { return passwordHash;}
    bool getIsAdmin() const { return isAdmin;}
    string getFavouriteGenre() const {return favouriteGenre;}

    // Rent content
    void rent(Content* item) {

        if(find(
                rented_titles.begin(),
                rented_titles.end(),
                item->getTitle()
            ) != rented_titles.end())
        {
            cout << "You already rented this item.\n";
            return;
        } 
        
        if(find(
                purchased_titles.begin(),
                purchased_titles.end(),
                item->getTitle()
            ) != purchased_titles.end())
        {
            cout << "You already purchased this item.\n";
            return;
        }
        genreCount[item->getGenre()]++;

        if(
            favouriteGenre.empty() ||
            genreCount[item->getGenre()] >
            genreCount[favouriteGenre]
        )
        {
            favouriteGenre = item->getGenre();
        }

        watch_history.push_back(item->getTitle());
        rented_titles.push_back(item->getTitle());
        charges_due += item->getRentCost();
        cout << "Rented successfully. $" << item->getRentCost() << " added to charges.\n";
    }

    // Purchase content
    void purchase(Content* item) {


        if(find(
            purchased_titles.begin(),
            purchased_titles.end(),
            item->getTitle()
        ) != purchased_titles.end())
        {
            cout << "Already purchased.\n";
            return;
        }

        if(find(
                rented_titles.begin(),
                rented_titles.end(),
                item->getTitle()
            ) != rented_titles.end())
        {
            cout << "You already rented this item.\n";
            return;
        }
        genreCount[item->getGenre()]++;

        if(
            favouriteGenre.empty() ||
            genreCount[item->getGenre()] >
            genreCount[favouriteGenre]
        )
        {
            favouriteGenre = item->getGenre();
        }

        watch_history.push_back(item->getTitle());
        purchased_titles.push_back(item->getTitle());
        charges_due += item->getPurchaseCost();
        cout << "Purchased successfully. $" << item->getPurchaseCost() << " added to charges.\n";
    }

    // Return rented content
    void returnItem(Content* item) {
        auto it =
        find(
            rented_titles.begin(),
            rented_titles.end(),
            item->getTitle()
        );

        if(it == rented_titles.end())
        {
            cout << "You have not rented this item.\n";
            return;
        }
        
        rented_titles.erase(it);
        cout << "Returned successfully.\n";
    }

    //View watch history
    void viewWatchHistory() const
    {
        cout << "\nWATCH HISTORY\n";

        if(watch_history.empty())
        {
            cout << "No history.\n";
            return;
        }

        for(const auto& item : watch_history)
            cout << "- " << item << endl;
    }

    // View currently rented titles
    void viewRented() const {
        cout << "Rented Items:\n";
        if (rented_titles.empty()) {
            cout << "None\n";
        } else {
            for (const auto& title : rented_titles)
                cout << "- " << title << endl;
        }
    }

    // View purchased titles
    void viewPurchased() const {
        cout << "Purchased Items:\n";
        if (purchased_titles.empty()) {
            cout << "None\n";
        } else {
            for (const auto& title : purchased_titles)
                cout << "- " << title << endl;
        }
    }
    // Add to watchlist feature
    void addToWatchlist(Content* item)
    {
        if(find(
            watchlist_titles.begin(),
            watchlist_titles.end(),
            item->getTitle()
        ) != watchlist_titles.end())
        {
            cout << "Already in watchlist.\n";
            return;
        }

        watchlist_titles.push_back(item->getTitle());

        cout << "Added to watchlist.\n";
    }
    //View watchlist
    void viewWatchlist() const
    {
        cout << "\nWATCHLIST\n";

        if(watchlist_titles.empty())
        {
            cout << "Empty\n";
            return;
        }

        for(const auto& item : watchlist_titles)
            cout << "- " << item << endl;
    }

    // View due charges
    void viewCharges() const {
        cout << "Total Charges Due: $" << charges_due << endl;
    }

    // Convert to string for file storage
    string serialize() const {
        stringstream ss;
        ss << username << "|" << passwordHash << "|" << isAdmin << "|" << charges_due << "|";

        for (const auto& r : rented_titles)
            ss << r << ",";
        ss << "|";

        for (const auto& p : purchased_titles)
            ss << p << ",";

        ss << "|";

        for(const auto& w : watchlist_titles)
            ss << w << ",";

        ss << "|";

        for(const auto& h : watch_history)
            ss << h << ",";

        ss << "|" << favouriteGenre;

        return ss.str();
    }

    // Restore from file
    static User* deserialize(const string& line)
    {
        stringstream ss(line);

        string uname;
        string passHash;
        string adminStr;
        string charge_str;
        string rented_str;
        string purchased_str;
        string watchlist_str;
        string history_str;
        string favouriteGenreStr;

        getline(ss, uname, '|');
        getline(ss, passHash, '|');
        getline(ss, adminStr, '|');
        getline(ss, charge_str, '|');
        getline(ss, rented_str, '|');
        getline(ss, purchased_str, '|');
        getline(ss, watchlist_str, '|');
        getline(ss, history_str, '|');
        getline(ss, favouriteGenreStr, '|');

        bool admin = (adminStr == "1");

        User* u =
            new User(
                uname,
                passHash,
                admin
            );

        try
        {
            u->charges_due = stof(charge_str);
        }
        catch(...)
        {
            u->charges_due = 0.0f;
        }

        string title;

        stringstream rented_stream(rented_str);

        while(getline(rented_stream, title, ','))
        {
            if(!title.empty())
                u->rented_titles.push_back(title);
        }

        stringstream purchased_stream(purchased_str);

        while(getline(purchased_stream, title, ','))
        {
            if(!title.empty())
                u->purchased_titles.push_back(title);
        }
        stringstream watchlist_stream(watchlist_str);

        while(getline(watchlist_stream, title, ','))
        {
            if(!title.empty())
                u->watchlist_titles.push_back(title);
        }

        stringstream history_stream(history_str);

        while(getline(history_stream, title, ','))
        {
            if(!title.empty())
                u->watch_history.push_back(title);
        }

        u->favouriteGenre = favouriteGenreStr;

        return u;
    }
};

#endif
