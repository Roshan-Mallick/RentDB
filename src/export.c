#include <stdio.h>
#include <errno.h>

#include "../include/export.h"
#include "../include/rent.h"

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

    while (fread(&record, sizeof(RentRecord), 1, datFile))
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

    fclose(datFile);
    fclose(csvFile);

    printf("\n====================================\n");
    printf(" CSV Export Successful\n");
    printf("====================================\n");

    printf("Exported File:\n%s\n", EXPORT_PATH);
}
