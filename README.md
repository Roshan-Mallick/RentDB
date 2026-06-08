# RentDB

RentDB is a modular CLI-based rent management system written in C.

It is designed to manage tenant rent records, payment tracking, CSV exports, and automatic GitHub backups using a structured and scalable project architecture.

This project focuses on learning:

* Modular C programming
* File handling in C
* Data management using structures
* CLI application design
* Build automation using Makefiles
* CSV export systems
* Git and GitHub automation

---

# Features

* Add rent records
* View rent records
* Edit rent records
* Persistent binary database storage
* CSV export support
* Automatic GitHub backup
* Modular source and header separation
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

# Build Instructions

Compile the project:

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

# GitHub Backup Setup (One-Time)

## Step 1 — Create a Private Repository

Create a private GitHub repository.

Example:

```text
rent_database
```

Do not initialize it with:

* README
* .gitignore
* License

---

## Step 2 — Clone the Backup Repository

Example:

```bash
git clone git@github.com:YOUR_GITHUB_USERNAME/rent_database.git ~/rent_database
```

This creates:

```text
/home/YOUR_USERNAME/rent_database
```

---

## Step 3 — Configure SSH Authentication

Generate an SSH key:

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

Start the SSH agent:

```bash
eval "$(ssh-agent -s)"
```

Add the key:

```bash
ssh-add ~/.ssh/id_ed25519
```

Display your public key:

```bash
cat ~/.ssh/id_ed25519.pub
```

Copy the output.

---

## Step 4 — Add SSH Key to GitHub

Open:

```text
GitHub
→ Settings
→ SSH and GPG Keys
→ New SSH Key
```

Paste your public key and save.

---

## Step 5 — Verify SSH Access

```bash
ssh -T git@github.com
```

Expected output:

```text
Hi YOUR_GITHUB_USERNAME! You've successfully authenticated,
but GitHub does not provide shell access.
```

---

## Step 6 — Create Export Directory

```bash
cd ~/rent_database
mkdir -p exports
touch exports/.gitkeep
```

Initial commit:

```bash
git add .
git commit -m "Initial repository structure"
git push -u origin main
```

---

## Step 7 — Configure Export Path

Open:

```bash
src/export.c
```

Update:

```c
#define BACKUP_REPO "/home/YOUR_USERNAME/rent_database"
#define EXPORT_PATH BACKUP_REPO "/exports/rent.csv"
```

Check your Linux username:

```bash
whoami
```

Example:

```text
john
```

---

## Step 8 — Rebuild

```bash
make clean
make
```

---

# CSV Export System

Exported CSV format:

```csv
PAYMENT DATE,RENT_PERIOD,AMOUNT,STATUS,TRANSACTION_ID
```

Example:

```csv
"15 JUN 2026","15 JUN TO 15 JUL 2026",9000.00,"PAID ON 15 JUN 2026","NIL"
```

---

# Export and Backup Workflow

Inside the application:

```text
4. Export CSV
```

The workflow is:

```text
RentDB
   ↓
Read data/rent.dat
   ↓
Generate rent.csv
   ↓
Save to ~/rent_database/exports/rent.csv
   ↓
git add
   ↓
git commit
   ↓
git push
   ↓
Private GitHub repository updated
```

No manual Git commands are required after the one-time setup.

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

and ensure the public key has been added to GitHub.

---

## Git Push Fails

Verify remote:

```bash
git remote -v
```

Example:

```text
origin git@github.com:YOUR_GITHUB_USERNAME/rent_database.git
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

# Important Notes

* SSH authentication must be configured before automatic pushes can work.
* The backup repository must contain at least one commit before the first export.
* If `git push` fails, the CSV is still saved locally.
* If no CSV changes are detected, the backup system reports "No changes since last backup".

---

# Future Improvements

* SQLite database integration
* PDF export system
* Search and filter support
* Tenant management
* Monthly analytics
* Timestamped export archives
* Authentication system
* Web dashboard version
* REST API version

---

# Learning Goals

This project was built to practice:

* Modular C programming
* Structures and file handling
* Persistent data systems
* CSV report generation
* Git automation
* GitHub integration
* Linux development workflows
* Software project organization

---

# License

This project is open-source and intended for learning and educational purposes.

