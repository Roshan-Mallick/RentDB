#ifndef RENT_H
#define RENT_H

typedef struct {

    char paymentDate[20];
    char rentPeriod[50];
    float amount;
    char status[30];
    char transactionId[200];

} RentRecord;

void addRentRecord();
void viewRentRecords();

#endif
