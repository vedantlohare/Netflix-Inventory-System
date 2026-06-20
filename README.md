# Netflix Inventory Management System

A Command Line Interface (CLI) based Netflix Inventory Management System developed in C++.

## Overview

This project simulates a Netflix-style content inventory management platform where administrators can manage movies, TV shows, and user information through a terminal-based interface.

The system provides functionality for content management, user management, authentication, and inventory tracking using file handling and object-oriented programming concepts.

## Features

### Authentication
- User Login
- Admin Login
- Password Security and Validation

### Content Management
- Add New Content
- View Available Content
- Search Content
- Manage Movies
- Manage TV Shows

### User Management
- Create Users
- View User Details
- User Data Storage

### Inventory Management
- Track Available Content
- Maintain Content Records
- File-Based Data Persistence

## Project Structure

```
Netflix-Inventory-System/
│
├── src/
├── include/
│   ├── content.h
│   ├── movie.h
│   ├── tvshows.h
│   ├── user.h
│   ├── inventory.h
│   ├── SecurityUtils.h
│   └── UserUtils.h
│
├── users/
├── data/
├── main.cpp
├── SecurityUtils.cpp
├── Dockerfile
└── README.md
```

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- STL (Standard Template Library)
- Command Line Interface (CLI)

## Concepts Implemented

- Classes and Objects
- Inheritance
- Encapsulation
- File I/O
- Data Persistence
- Authentication System
- Modular Programming

## How to Run

### Compile

```bash
g++ main.cpp SecurityUtils.cpp -o netflix
```

### Execute

```bash
./netflix
```

For Windows:

```bash
netflix.exe
```

## Future Improvements

- Database Integration
- GUI Interface
- Content Recommendation System
- Advanced Search Filters
- User Watch History

## Author

Vedant

## License

This project was developed for academic and learning purposes.