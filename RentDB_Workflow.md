# RentDB Export & GitHub Backup Workflow Notes

## Overview

RentDB uses **two separate directories**:

```text
/home/user/RentDB
```

Main application source code.

```text
/home/user/rent_database
```

Private GitHub backup repository.

---

# Why Two Repositories?

## RentDB

Contains:

```text
RentDB/
├── src/
├── include/
├── data/
├── Makefile
└── README.md
```

Purpose:

* Store source code
* Store application database
* Development repository

---

## rent_database

Contains:

```text
rent_database/
└── exports/
    └── rent.csv
```

Purpose:

* Store exported CSV files
* Automatically push backups to GitHub
* Separate application code from backup data

---

# Complete Workflow

## Step 1

User runs:

```bash
./rentdb
```

Program starts.

---

## Step 2

User selects:

```text
4. Export CSV
```

Menu flow:

```text
User
 ↓
RentDB Menu
 ↓
Export CSV
```

---

## Step 3

Program opens database file:

```c
FILE *datFile = fopen("data/rent.dat", "rb");
```

File:

```text
RentDB/data/rent.dat
```

This contains all rent records.

---

## Step 4

Program creates CSV file:

```c
FILE *csvFile = fopen(EXPORT_PATH, "w");
```

Where:

```c
#define EXPORT_PATH "/home/user/rent_database/exports/rent.csv"
```

Result:

```text
rent_database/
└── exports/
    └── rent.csv
```

---

## Step 5

Program reads records:

```c
while (fread(...))
```

Example:

```text
Payment Date
Rent Period
Amount
Status
Transaction ID
```

---

## Step 6

Program writes CSV:

Example:

```csv
PAYMENT DATE,RENT PERIOD,AMOUNT,STATUS,TRANSACTION ID
"15 JUN 2026","15 JUN TO 15 JUL 2026",9000.00,"PAID","NIL"
```

---

## Step 7

CSV export completes:

```text
====================================
 CSV Export Successful
====================================
```

At this point:

```text
rent.csv
```

already exists locally.

Even if GitHub fails later, CSV is still saved.

---

# GitHub Backup Stage

After export:

```c
backupToGitHub();
```

is called.

---

## Step 8

Store current location:

```c
getcwd(...)
```

Example:

```text
/home/user/RentDB
```

Saved temporarily.

---

## Step 9

Program enters backup repository:

```c
chdir(BACKUP_REPO);
```

Result:

```text
/home/user/rent_database
```

---

## Step 10

Stage CSV:

```c
git add exports/rent.csv
```

Flow:

```text
rent.csv
 ↓
Git Staging Area
```

---

## Step 11

Create commit:

```c
git commit -m "RentDB export update"
```

Example:

```text
Commit #1
Commit #2
Commit #3
```

Every export creates Git history.

---

## Step 12

Push to GitHub:

```c
git push origin main
```

Flow:

```text
Local Repository
       ↓
GitHub Repository
```

---

## Step 13

Success:

```text
[✓] GitHub backup completed successfully
```

---

# Full Flow Diagram

```text
RentDB
   ↓
Open rent.dat
   ↓
Read records
   ↓
Generate rent.csv
   ↓
Save CSV locally
   ↓
Enter backup repository
   ↓
git add
   ↓
git commit
   ↓
git push
   ↓
GitHub updated
```

---

# Important Files

## Database

```text
RentDB/data/rent.dat
```

Purpose:

```text
Stores actual rent records
```

---

## Export File

```text
rent_database/exports/rent.csv
```

Purpose:

```text
Human-readable export
```

---

## Git Repository

```text
rent_database/.git
```

Purpose:

```text
Tracks export history
```

---

# What Happens If GitHub Is Down?

Example:

```text
git push failed
```

Result:

```text
CSV still saved locally
```

Location:

```text
rent_database/exports/rent.csv
```

No data loss.

---

# What Happens If rent_database Is Deleted?

Program tries:

```c
fopen("/home/user/rent_database/exports/rent.csv")
```

Result:

```text
Failed to create CSV export file
```

Export fails.

Therefore:

```text
DO NOT DELETE:
~/rent_database
```

---

# What Can Be Deleted?

Safe:

```text
~/gdrive
rclone
Google Drive configuration
```

Not Safe:

```text
~/rent_database
```

because it is now part of the export system.

---

# Mental Model

Think of it like this:

```text
RentDB
│
├── Stores data
│
└── Creates reports
        │
        ▼
rent_database
│
├── Stores CSV backups
│
└── Pushes them to GitHub
```

The application repository and backup repository have different jobs:

```text
RentDB        = Application
rent_database = Backup Storage
```

