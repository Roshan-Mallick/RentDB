# RentDB

RentDB is a modular CLI-based rent management system written in C.

It provides a simple and efficient way to manage rent records, store data persistently, export reports, and automatically back up exported data to a GitHub repository.

---

# Features

* Add rent records
* View rent records
* Edit rent records
* Persistent binary database storage
* CSV export support
* Automatic GitHub backup
* Modular C project architecture
* Makefile-based build system
* Linux-friendly workflow

---

# Project Structure

```text
RentDB/
├── data/
│   └── rent.dat
│
├── include/
│   ├── database.h
│   ├── export.h
│   ├── rent.h
│   └── utils.h
│
├── src/
│   ├── database.c
│   ├── export.c
│   ├── main.c
│   ├── rent.c
│   └── utils.c
│
├── exports/
│   └── rent.csv
│
├── Makefile
├── README.md
└── .gitignore
```

---

# Requirements

## Ubuntu / Debian

```bash
sudo apt update
sudo apt install build-essential git
```

## Fedora

```bash
sudo dnf install gcc make git
```

---

# Step 1 — Clone RentDB

Example:

```bash
git clone git@github.com:johnsmith/RentDB.git
cd RentDB
```

Replace:

```text
johnsmith
```

with your GitHub username.

---

# Step 2 — Build Project

Compile:

```bash
make
```

Run:

```bash
make run
```

Clean build files:

```bash
make clean
```

---

# Step 3 — Create a GitHub Backup Repository

Create a new repository.

Example name:

```text
rent_database
```

Recommended:

* Private repository
* No README
* No .gitignore
* No License

---

# Step 4 — Clone Backup Repository

Example:

```bash
git clone git@github.com:johnsmith/rent_database.git
```

This creates:

```text
/home/john/rent_database
```

---

# Step 5 — Configure SSH Authentication

Generate SSH key:

```bash
ssh-keygen -t ed25519 -C "user@example.com"
```

Start SSH agent:

```bash
eval "$(ssh-agent -s)"
```

Add key:

```bash
ssh-add ~/.ssh/id_ed25519
```

Display public key:

```bash
cat ~/.ssh/id_ed25519.pub
```

Example output:

```text
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIExamplePublicKey1234567890 user@example.com
```

Copy the output.

---

# Step 6 — Add SSH Key to GitHub

Open:

```text
GitHub
→ Settings
→ SSH and GPG Keys
→ New SSH Key
```

Paste the public key and save.

---

# Step 7 — Verify SSH

Run:

```bash
ssh -T git@github.com
```

Example output:

```text
Hi johnsmith! You've successfully authenticated,
but GitHub does not provide shell access.
```

---

# Step 8 — Configure Backup Repository

Navigate:

```bash
cd ~/rent_database
```

Create export folder:

```bash
mkdir exports
```

Create placeholder file:

```bash
touch exports/.gitkeep
```

Commit:

```bash
git add .
git commit -m "Initial export structure"
git push -u origin main
```

---

# Step 9 — Configure Export Path

Open:

```bash
src/export.c
```

Update:

```c
#define BACKUP_REPO "/home/john/rent_database"
#define EXPORT_PATH BACKUP_REPO "/exports/rent.csv"
```

Replace:

```text
john
```

with your Linux username.

Check username:

```bash
whoami
```

Example:

```text
john
```

---

# Step 10 — Build Again

```bash
make clean
make
```

---

# Step 11 — Run Application

```bash
./rentdb
```

Menu:

```text
====================================
       RENT DATABASE SYSTEM
====================================
1. Add Rent Record
2. View Rent Records
3. Edit Rent Record
4. Export CSV
0. Exit
```

---

# Step 12 — Export CSV

Select:

```text
4
```

The application automatically:

```text
RentDB
   ↓
Read rent.dat
   ↓
Generate rent.csv
   ↓
Save to backup repository
   ↓
git add
   ↓
git commit
   ↓
git push
   ↓
GitHub Backup Complete
```

---

# CSV Format

```csv
PAYMENT DATE,RENT PERIOD,AMOUNT,STATUS,TRANSACTION ID
```

Example:

```csv
"15 JUN 2026","15 JUN TO 15 JUL 2026",9000.00,"PAID ON 15 JUN 2026","NIL"
```

---

# Automatic GitHub Backup

The export module automatically executes:

```bash
git add exports/rent.csv
git commit -m "RentDB export update"
git push origin main
```

No manual Git commands are required after setup.

---

# Backup Repository Structure

```text
rent_database/
└── exports/
    ├── .gitkeep
    └── rent.csv
```

---

# Example Success Output

```text
====================================
 CSV Export Successful
====================================

Backing up to GitHub...

[✓] Changes committed
[✓] GitHub backup completed successfully
```

---

# Troubleshooting

## SSH Permission Denied

```text
Permission denied (publickey)
```

Verify:

```bash
ssh -T git@github.com
```

If authentication fails:

```bash
ssh-add ~/.ssh/id_ed25519
```

and confirm the public key is added to GitHub.

---

## Git Push Fails

Verify remote:

```bash
git remote -v
```

Example:

```text
origin git@github.com:johnsmith/rent_database.git
```

---

## Export File Not Found

Verify:

```bash
ls ~/rent_database/exports
```

Expected:

```text
rent.csv
```

---

# Future Improvements

* Delete rent records
* Search records
* Filter records
* Monthly statistics
* PDF export
* SQLite database support
* User authentication
* Tenant management
* Dashboard version
* REST API version

---

# Learning Goals

This project was built to practice:

* Modular C programming
* Structures and file handling
* Persistent storage systems
* CSV report generation
* Git automation
* GitHub integration
* Linux development workflows
* Software project organization

---

# License

This project is open-source and intended for learning and educational purposes.
