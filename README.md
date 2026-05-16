# RentDB

RentDB is a modular CLI-based rent management system written in C.

It is designed to manage tenant rent records, payment tracking, and export operations using a structured and scalable project architecture.

This project focuses on learning:

* Modular C programming
* File handling in C
* Data management using structures
* CLI application design
* Build automation using Makefile
* Export system integration (CSV/PDF planned)
* Linux cloud synchronization using rclone

---

# Features

* Add and store rent records
* Persistent file-based database system
* Modular source and header separation
* Export module structure
* Utility helper functions
* Organized project structure
* Makefile-based build system
* CSV export support
* Google Drive sync support using rclone (Linux)

---

# Project Structure

```bash
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
```

---

# Build Instructions

Compile the project:

```bash
make
```

Run the application:

```bash
make run
```

Clean build files:

```bash
make clean
```

---

# CSV Export System

The project supports CSV export for rent records.

Exported CSV format:

```csv
PAYMENT DATE,RENT PERIOD,AMOUNT,STATUS,TRANSACTION ID
```

The export system automatically generates:

```bash
rent.csv
```

---

# Google Drive Sync Setup (Linux)

RentDB supports Google Drive synchronization using `rclone`.

This allows exported CSV files to automatically sync to Google Drive.

---

# Step 1 — Install rclone

Ubuntu / Debian:

```bash
sudo apt install rclone
```

Fedora:

```bash
sudo dnf install rclone
```

Verify installation:

```bash
rclone version
```

---

# Step 2 — Configure Google Drive

Run:

```bash
rclone config
```

Follow these steps:

## Create New Remote

Type:

```text
n
```

Enter remote name:

```text
gdrive
```

Select storage type:

```text
18
```

(Google Drive)

---

## Client ID / Secret

Press ENTER for both.

---

## Scope

Choose:

```text
1
```

(Full access)

---

## Service Account

Press ENTER.

---

## Advanced Config

Type:

```text
n
```

---

## Auto Config

Type:

```text
y
```

Browser login will open.

Login to Google account and allow access.

---

## Shared Drive

Choose:

```text
n
```

(for personal Google Drive)

---

## Save Configuration

Type:

```text
y
```

Quit:

```text
q
```

---

# Step 3 — Test Connection

Run:

```bash
rclone ls gdrive:
```

If setup is successful, your Google Drive files will appear.

---

# Step 4 — Create Mount Directory

Create local mount folder:

```bash
mkdir -p ~/gdrive
```

---

# Step 5 — Mount Google Drive

Run:

```bash
rclone mount gdrive: ~/gdrive --daemon
```

This mounts Google Drive locally at:

```bash
/home/USERNAME/gdrive
```

---

# Step 6 — Verify Mount

Run:

```bash
ls ~/gdrive
```

You should see your Google Drive folders.

---

# Step 7 — Create RentDB Export Folder

Navigate:

```bash
cd ~/gdrive/"RENT & ELECTRIC BILL"
```

Create project folder:

```bash
mkdir RentDB
```

---

# Step 8 — Configure Export Path

Update export path inside:

```bash
src/export.c
```

Example:

```c
#define EXPORT_PATH "/home/your-linux-username/gdrive/RENT & ELECTRIC BILL/RentDB/rent.csv"
```

Replace:

```text
your-linux-username
```

with your actual Linux username.

Example:

```c
#define EXPORT_PATH "/home/eth0x1/gdrive/RENT & ELECTRIC BILL/RentDB/rent.csv"
```

You can check your Linux username using:

```bash
whoami
```

---

# Step 9 — Build Project

Compile:

```bash
make
```

Run:

```bash
make run
```

---

# Step 10 — Export CSV

Inside application:

```text
4. Export CSV
```

Selecting option `4` will:

```text
RentDB
   ↓
Generate rent.csv
   ↓
Save inside Google Drive
   ↓
Auto-sync using rclone
```

Final output location:

```text
Google Drive/
└── RENT & ELECTRIC BILL/
    └── RentDB/
        └── rent.csv
```

---

# Example Export Function

```c
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/export.h"
#include "../include/rent.h"

#define EXPORT_PATH "/home/your-linux-username/gdrive/RENT & ELECTRIC BILL/RentDB/rent.csv"

void exportRentCSV()
{
    FILE *datFile = fopen("data/rent.dat", "rb");

    if (datFile == NULL)
    {
        perror("Failed to open rent database");
        return;
    }

    FILE *csvFile = fopen(EXPORT_PATH, "w");

    if (csvFile == NULL)
    {
        perror("Failed to create CSV export file");
        fclose(datFile);
        return;
    }

    fprintf(
        csvFile,
        "PAYMENT DATE,RENT PERIOD,AMOUNT,STATUS,TRANSACTION ID\n"
    );

    RentRecord record;

    while (fread(&record, sizeof(RentRecord), 1, datFile) == 1)
    {
        fprintf(
            csvFile,
            "\"%s\",\"%s\",%.2f,\"%s\",\"%s\"\n",
            record.paymentDate,
            record.rentPeriod,
            record.amount,
            record.status,
            record.transactionId
        );
    }

    fflush(csvFile);

    fclose(datFile);
    fclose(csvFile);

    printf("\n====================================\n");
    printf(" CSV Export Successful\n");
    printf("====================================\n");

    printf("Exported File:\n%s\n", EXPORT_PATH);
}
```

---

# Important Notes

* Google Drive must be mounted before exporting.
* Run mount command after reboot:

```bash
rclone mount gdrive: ~/gdrive --daemon
```

* Folder names are case-sensitive.
* Paths containing spaces must be quoted in terminal commands.

---

# Future Improvements

* SQLite database integration
* PDF export system
* Search and filter support
* Authentication system
* Tenant management
* Monthly analytics
* Web dashboard version
* Automatic startup mount using systemd

---

# Learning Goals

This project is built to improve understanding of:

* Real-world C project architecture
* Persistent data systems
* Linux filesystem handling
* Cloud synchronization workflows
* Modular software engineering
* Build systems and automation

---

# License

This project is open-source and intended for learning and educational purposes.
