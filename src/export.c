#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../include/export.h"
#include "../include/rent.h"

#define BACKUP_REPO "/home/eth0x1/rent_database"
#define EXPORT_PATH BACKUP_REPO "/exports/rent.csv"

static int runCommand(const char *command)
{
    int status = system(command);

    if (status == -1)
    {
        perror("Failed to run command");
        return -1;
    }

    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }

    return -1;
}

static void backupToGitHub(void)
{
    char originalDir[4096];

    if (getcwd(originalDir, sizeof(originalDir)) == NULL)
    {
        perror("Failed to get current directory");
        return;
    }

    printf("\nBacking up to GitHub...\n");

    if (chdir(BACKUP_REPO) != 0)
    {
        perror("Failed to enter backup repository");
        printf("CSV saved locally at: %s\n", EXPORT_PATH);
        return;
    }

    int status = runCommand("git add exports/rent.csv");

    if (status != 0)
    {
        printf("[!] git add failed (exit code %d)\n", status);
        chdir(originalDir);
        return;
    }

    status = runCommand("git commit -m \"RentDB export update\"");

    if (status == 0)
    {
        printf("[✓] Changes committed\n");
    }
    else if (status == 1)
    {
        printf("[✓] No changes since last backup\n");
        chdir(originalDir);
        return;
    }
    else
    {
        printf("[!] git commit failed (exit code %d)\n", status);
        chdir(originalDir);
        return;
    }

    status = runCommand("git push origin main");

    if (status != 0)
    {
        printf("[!] git push failed (exit code %d)\n", status);
        printf("CSV saved locally at: %s\n", EXPORT_PATH);
        chdir(originalDir);
        return;
    }

    printf("[✓] GitHub backup completed successfully\n");

    chdir(originalDir);
}

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

    backupToGitHub();
}
