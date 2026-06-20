# Netflix CLI Content Management System

A command-line application built in C++ that simulates a Netflix-style content platform. The system allows users to browse content, manage watchlists, rent or purchase movies and TV shows, and receive simple genre-based recommendations. User and content data are stored using file-based persistence.

## Features

### User Authentication

* User registration and login
* Admin and user roles
* Password hashing and authentication

### Content Management

* Add and manage movies
* Add and manage TV shows
* Browse all available content
* Search content by title
* Search content by genre

### User Features

* Rent content
* Purchase content
* Return rented content
* View rented and purchased content
* Watchlist management
* Watch history tracking

### Recommendation System

* Tracks user viewing preferences
* Provides genre-based content recommendations

### Rating System

* Users can rate content
* Average ratings are calculated
* View top-rated content

### Data Persistence

* User data stored in text files
* Inventory stored in files
* Data remains available across sessions

---

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* File Handling
* STL (Vectors, Maps, Algorithms)
* Git & GitHub
* Docker

---

## OOP Concepts Applied

* Encapsulation
* Inheritance
* Abstraction
* Polymorphism
* Modular Design

---

## Project Structure

```text
Netflix-Inventory-System/
│
├── include/
│   ├── content.h
│   ├── movie.h
│   ├── tvshows.h
│   ├── inventory.h
│   ├── user.h
│   ├── SecurityUtils.h
│   └── UserUtils.h
│
├── src/
│   ├── main.cpp
│   └── SecurityUtils.cpp
│
├── users/
├── inventory.txt
├── Dockerfile
└── README.md
```

---

## How to Run

### Compile

```bash
g++ src/main.cpp src/SecurityUtils.cpp -I include -o netflix
```

### Run

#### Windows

```bash
.\netflix.exe
```

#### Linux / macOS

```bash
./netflix
```

---

## Example Workflow

1. Sign up or log in.
2. Browse available content.
3. Search by title or genre.
4. Rent or purchase movies and TV shows.
5. Add content to your watchlist.
6. View watch history.
7. Receive recommendations based on viewing preferences.
8. Rate content and explore top-rated titles.

---

## Future Improvements

* Database integration (MySQL/PostgreSQL)
* Better recommendation algorithms
* Content reviews and comments
* Admin analytics dashboard
* Graphical user interface (GUI)
* REST API support

---

## What I Learned

This project helped me gain hands-on experience with:

* Designing object-oriented systems in C++
* Managing data using file handling
* Building authentication workflows
* Working with modular project structures
* Using Git and GitHub for version control

---

## Author

Vedant Lohare

GitHub: https://github.com/vedantlohare

---

## License

This project was developed for learning and educational purposes.
