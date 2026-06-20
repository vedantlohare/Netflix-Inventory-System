#include <iostream>
#include <string>
#include <filesystem>
#include "../include/inventory.h"
#include "../include/user.h"
#include "../include/UserUtils.h"
#include "../include/SecurityUtils.h"

using namespace std;
namespace fs = std::filesystem;


void userMenu(User* user, Inventory& inventory) {
    int choice;
    while (true) {
        cout << "\nUSER MENU - " << user->getUsername() << "\n";
        cout << "1. Browse all content\n";
        cout << "2. Search by title\n";
        cout << "3. Search by genre\n";
        cout << "4. Rent\n";
        cout << "5. Purchase\n";
        cout << "6. Return\n";
        cout << "7. Add to watchlist\n";
        cout << "8. View watchlist\n";
        cout << "9. View watch history\n";
        cout << "10. Recommendations\n";
        cout << "11. Add Rating\n";
        cout << "12. Top rated content\n";
        cout << "13. View rented\n";
        cout << "14. View purchased\n";
        cout << "15. Charges due\n";
        cout << "16. Logout\n";
        cout << "Choice: ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000,'\n');

            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore();

        if (choice == 1) {
            inventory.displayAll();
        } else if (choice == 2) {
            string title;
            cout << "Enter title: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) c->display();
            else cout << "Not found.\n";
        } else if(choice == 3)
            {
                string genre;

                cout << "Enter genre: ";

                getline(cin, genre);

                inventory.searchByGenre(genre);
            }else if (choice == 4) {
            string title;
            cout << "Enter title to rent: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) user->rent(c);
            else cout << "Not found.\n";
        } else if (choice == 5) {
            string title;
            cout << "Enter title to purchase: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) user->purchase(c);
            else cout << "Not found.\n";
        } else if (choice == 6) {
            string title;
            cout << "Enter title to return: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) user->returnItem(c);
            else cout << "Not found.\n";
        } else if(choice == 7)
        {
            string title;

            cout << "Enter title: ";

            getline(cin, title);

            Content* c =
                inventory.searchByTitle(title);

            if(c)
                user->addToWatchlist(c);
            else
                cout << "Not found.\n";
        }else if(choice == 8)
        {
            user->viewWatchlist();
        }else if(choice == 9)
        {
            user->viewWatchHistory();
        }else if(choice == 10)
        {
            inventory.recommendByGenre(
                user->getFavouriteGenre()
            );
        }else if(choice == 11)
        {
            string title;

            cout << "Enter title: ";

            getline(cin, title);

            Content* c =
                inventory.searchByTitle(title);

            if(!c)
            {
                cout << "Not found.\n";
                continue;
            }

            int rating;

            cout << "Enter rating (1-5): ";

            cin >> rating;

            cin.ignore();

            c->addRating(rating);

            cout << "Rating submitted.\n";
        }else if(choice == 12)
        {
            inventory.displayTopRated();
        }else if (choice == 13) {
            user->viewRented();
        } else if (choice == 14) {
            user->viewPurchased();
        } else if (choice == 15) {
            user->viewCharges();
        } else if (choice == 16) {
            saveUser(user);
            cout << "Logged out.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void adminMenu(Inventory& inventory) {
    int choice;
    while (true) {
        cout << "\nADMIN MENU\n";
        cout << "1. Add Movie\n2. Add TV Show\n3. Remove Content\n4. View All Content\n5. Logout\nChoice: ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000,'\n');

            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore();

        if (choice == 1) {
            string title, genre;
            float rating, rent, purchase;
            int duration;
            cout << "Enter title, genre, rating, duration, rent cost, purchase cost:\n";
            getline(cin, title); getline(cin, genre);
            cin >> rating >> duration >> rent >> purchase; cin.ignore();
            inventory.addContent(new Movie(title, genre, rating, duration, rent, purchase));
            cout << "Movie added.\n";
        } else if (choice == 2) {
            string title, genre;
            float rating, rent, purchase;
            int seasons, eps;
            cout << "Enter title, genre, rating, seasons, eps/season, rent/season, purchase/season:\n";
            getline(cin, title); getline(cin, genre);
            cin >> rating >> seasons >> eps >> rent >> purchase; cin.ignore();
            inventory.addContent(new TVShow(title, genre, rating, seasons, eps, rent, purchase));
            cout << "TV Show added.\n";
        } else if (choice == 3) {
            string title;
            cout << "Enter title to remove: ";
            getline(cin, title);
            // Simplified: just mark as not available, or skip (you can implement actual removal later)
            cout << "Feature not implemented.\n";
        } else if (choice == 4) {
            inventory.displayAll();
        } else if (choice == 5) {
            cout << "Admin logged out.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    fs::create_directory("users");
    cout << "Current path: "
     << fs::current_path()
     << endl;
    if(!userExists("admin"))
    {
        User* admin =
        new User(
            "admin",
            hashPassword("admin123"),
            true
        );

        saveUser(admin);
        delete admin;
    }

    Inventory inventory;
    inventory.loadFromFile("inventory.txt");

    while (true) {
        int option;
        cout << "\n--- NETFLIX CLI SYSTEM ---\n";
        cout << "1. User Sign Up\n2. Login\n3. Exit\nChoice: ";
        if(!(cin >> option))
        {
            cin.clear();
            cin.ignore(10000,'\n');

            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore();

        if (option == 1) {
            string uname;
            cout << "Enter new username: ";
            getline(cin, uname);
            string password;
            cout << "Enter password: ";
            getline(cin, password);
            if (userExists(uname)) {
                cout << "Username already exists.\n";
            } else {
                User* u = new User(uname,hashPassword(password));
                saveUser(u);
                cout << "Sign-up successful. You can now log in.\n";
                delete u;
            }
            
        } else if (option == 2) {
            string uname;

            cout << "Enter username: ";
            getline(cin, uname);

            if (!userExists(uname))
            {
                cout << "User not found.\n";
                continue;
            }

            string password;

            cout << "Enter password: ";
            getline(cin, password);

            User* user = loadUser(uname);

            if (user->getPasswordHash() != hashPassword(password))
            {
                cout << "Wrong password.\n";
                delete user;
                continue;
            }

            cout << "Welcome "
                << user->getUsername()
                << "!\n";

            if(user->getIsAdmin())
            {
                adminMenu(inventory);
            }
            else
            {
                userMenu(user, inventory);
            }

            delete user;
        
        } else if (option == 3) {
            inventory.saveToFile("inventory.txt");
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid input.\n";
        }
    }

    return 0;
}
