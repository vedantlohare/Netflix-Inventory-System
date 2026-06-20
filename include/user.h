#ifndef USER_H
#define USER_H

#include "content.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


class User {
private:
    string username;
    vector<string> rented_titles;
    vector<string> purchased_titles;
    float charges_due;
    string passwordHash;
    bool isAdmin;

public:
    // Constructor
    User(const string& uname, const string& passHash, bool admin = false) : username(uname), passwordHash(passHash), isAdmin(admin), charges_due(0.0f) {}

    // Getters
    string getUsername() const { return username; }
    float getChargesDue() const { return charges_due; }
    string getPasswordHash() const { return passwordHash;}
    bool getIsAdmin() const { return isAdmin;}

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

        getline(ss, uname, '|');
        getline(ss, passHash, '|');
        getline(ss, adminStr, '|');
        getline(ss, charge_str, '|');
        getline(ss, rented_str, '|');
        getline(ss, purchased_str, '|');

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

        return u;
    }
};

#endif
