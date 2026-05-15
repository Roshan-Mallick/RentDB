# RentDB

RentDB is a modular CLI-based rent management system written in C.  
It is designed to manage tenant rent records, payment tracking, and export operations using a structured and scalable project architecture.

This project focuses on learning:

- Modular C programming
- File handling in C
- Data management using structures
- CLI application design
- Build automation using Makefile
- Export system integration (CSV/PDF planned)

---

# Features

- Add and store rent records
- Persistent file-based database system
- Modular source and header separation
- Export module structure
- Utility helper functions
- Organized project structure
- Makefile-based build system

---

# Project Structure

```text
RentDB/
├── data/               # Stores database files
├── exports/            # Stores exported reports
├── include/            # Header files
│   ├── database.h
│   ├── export.h
│   ├── rent.h
│   └── utils.h
│
├── src/                # Source files
│   ├── database.c
│   ├── export.c
│   ├── main.c
│   ├── rent.c
│   └── utils.c
│
├── Makefile
├── README.md
└── .gitignore
