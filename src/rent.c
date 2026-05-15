#include <stdio.h>
#include <string.h>

#include "../include/rent.h"
#include "../include/database.h"

void addRentRecord()
{
    RentRecord record;

    printf("\nEnter Payment Date: ");
    fgets(record.paymentDate, sizeof(record.paymentDate), stdin);
    strtok(record.paymentDate, "\n");

    printf("Enter Rent Period: ");
    fgets(record.rentPeriod, sizeof(record.rentPeriod), stdin);
    strtok(record.rentPeriod, "\n");

    printf("Enter Amount: ");
    scanf("%f", &record.amount);
    getchar();

    printf("Enter Status: ");
    fgets(record.status, sizeof(record.status), stdin);
    strtok(record.status, "\n");

    printf("Enter Transaction ID: ");
    fgets(record.transactionId, sizeof(record.transactionId), stdin);
    strtok(record.transactionId, "\n");

    saveRentRecord(record);

    printf("\nRecord saved successfully.\n");
}

void viewRentRecords()
{
    loadRentRecords();
}
