#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/export.h"
#include "../include/rent.h"

/*
 * Default export location.
 *
 * Users can change this path to any custom directory.
 *
 * Example for Google Drive auto-sync using rclone:
 *
 * #define EXPORT_PATH "/home/your-linux-username/gdrive/RENT & ELECTRIC BILL/RentDB/rent.csv"
 *
 * This allows exported CSV files to automatically sync
 * with Google Drive and become accessible from anywhere.
 */

#define EXPORT_PATH "exports/rent_report.csv"

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
