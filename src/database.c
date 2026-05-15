#include <stdio.h>
#include <string.h>

#include "../include/database.h"
#include "../include/utils.h"

void saveRentRecord(RentRecord record)
{
    FILE *fp = fopen("data/rent.dat", "ab");

    if (fp == NULL)
    {
        printf("\n[!] Failed to open database file.\n");
        return;
    }

    fwrite(&record, sizeof(RentRecord), 1, fp);

    fclose(fp);
}

void loadRentRecords()
{
    FILE *fp = fopen("data/rent.dat", "rb");

    RentRecord record;

    if (fp == NULL)
    {
        printf("\n[!] No rent records found.\n");
        return;
    }

    int slno = 1;

    printf("\n");

    printDivider();

    printf(
        "| %-5s | %-18s | %-22s | %-10s | %-20s | %-50s |\n",
        "SL",
        "PAYMENT DATE",
        "RENT PERIOD",
        "AMOUNT",
        "STATUS",
        "TRANSACTION ID"
    );

    printDivider();

    while (fread(&record, sizeof(RentRecord), 1, fp))
    {
        printf(
            "| %-5d | %-18s | %-22s | %-10.2f | %-20s | %-50s |\n",
            slno,
            record.paymentDate,
            record.rentPeriod,
            record.amount,
            record.status,
            record.transactionId
        );

        slno++;
    }

    printDivider();

    fclose(fp);
}

void editRentRecord()
{
    FILE *fp = fopen("data/rent.dat", "rb");

    if (fp == NULL)
    {
        printf("\n[!] No records found.\n");
        return;
    }

    RentRecord records[100];

    int count = 0;

    while (fread(&records[count],
                  sizeof(RentRecord),
                  1,
                  fp))
    {
        count++;
    }

    fclose(fp);

    loadRentRecords();

    int slno;

    printf("\nEnter SL NO to edit: ");

    if (scanf("%d", &slno) != 1)
    {
        printf("\n[!] Invalid input.\n");

        while (getchar() != '\n');

        return;
    }

    getchar();

    if (slno < 1 || slno > count)
    {
        printf("\n[!] Invalid SL NO.\n");
        return;
    }

    int index = slno - 1;

    int choice;

    while (1)
    {
        printDivider();

        printf("EDIT RENT RECORD MENU\n");

        printDivider();

        printf("1. Edit Payment Date\n");
        printf("2. Edit Rent Period\n");
        printf("3. Edit Amount\n");
        printf("4. Edit Status\n");
        printf("5. Edit Transaction ID\n");
        printf("0. Save & Exit\n");

        printDivider();

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[!] Invalid input.\n");

            while (getchar() != '\n');

            continue;
        }

        getchar();

        switch(choice)
        {
            case 1:

                printf("Enter New Payment Date: ");

                fgets(records[index].paymentDate,
                      sizeof(records[index].paymentDate),
                      stdin);

                stripNewline(records[index].paymentDate);

                break;

            case 2:

                printf("Enter New Rent Period: ");

                fgets(records[index].rentPeriod,
                      sizeof(records[index].rentPeriod),
                      stdin);

                stripNewline(records[index].rentPeriod);

                break;

            case 3:

                printf("Enter New Amount: ");

                if (scanf("%f",
                          &records[index].amount) != 1)
                {
                    printf("\n[!] Invalid amount.\n");

                    while (getchar() != '\n');

                    continue;
                }

                getchar();

                break;

            case 4:

                printf("Enter New Status: ");

                fgets(records[index].status,
                      sizeof(records[index].status),
                      stdin);

                stripNewline(records[index].status);

                break;

            case 5:

                printf("Enter New Transaction ID: ");

                fgets(records[index].transactionId,
                      sizeof(records[index].transactionId),
                      stdin);

                stripNewline(records[index].transactionId);

                break;

            case 0:

                fp = fopen("data/rent.dat", "wb");

                if (fp == NULL)
                {
                    printf("\n[!] Failed to update database.\n");
                    return;
                }

                fwrite(records,
                       sizeof(RentRecord),
                       count,
                       fp);

                fclose(fp);

                printf("\n[✓] Record updated successfully.\n");

                return;

            default:

                printf("\n[!] Invalid choice.\n");
        }
    }
}
