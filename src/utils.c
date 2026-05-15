#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/utils.h"

void stripNewline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

void printDivider()
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    for (int i = 0; i < w.ws_col; i++)
    {
        printf("═");
    }

    printf("\n");
}

void printTableHeader()
{
    printDivider();

    printf(
        "%-5s %-18s %-20s %-12s %-15s %-50s\n",
        "SL",
        "PAYMENT DATE",
        "RENT PERIOD",
        "AMOUNT",
        "STATUS",
        "TRANSACTION ID"
    );

    printDivider();
}
