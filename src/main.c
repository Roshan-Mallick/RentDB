#include <stdio.h>

#include "../include/rent.h"
#include "../include/export.h"
#include "../include/database.h"

int main()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("====================================\n");
        printf("       RENT DATABASE SYSTEM\n");
        printf("====================================\n");

        printf("1. Add Rent Record\n");
        printf("2. View Rent Records\n");
        printf("3. Edit Rent Record\n");
        printf("4. Export CSV\n");
        printf("0. Exit\n");

        printf("\nEnter Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[!] Invalid Input.\n");

            while (getchar() != '\n');

            continue;
        }

        getchar();

        switch (choice)
        {
            case 1:

                addRentRecord();
                break;

            case 2:

                viewRentRecords();
                break;

            case 3:

                editRentRecord();
                break;

            case 4:

                exportRentCSV();
                break;

            case 0:

                printf("\n[✓] Exiting Program...\n");
                return 0;

            default:

                printf("\n[!] Invalid Choice.\n");
        }
    }

    return 0;
}
