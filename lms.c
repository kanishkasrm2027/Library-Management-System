#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_HISTORY 100

// Book structure
typedef struct {
    int id;
    char title[50];
    int available;
} Book;

// Member structure
typedef struct Member {
    char registrationNumber[20];
    struct Member* next;
} Member;

typedef struct {
    char registrationNumber[20];
    char borrowedBook[50];
    int penaltyFee;
    char borrowDate[15];
    char returnDate[15];
    int isPenaltyPaid;  // 0 for unpaid, 1 for paid
} History;

Book books[MAX_BOOKS];
int bookCount = 0;
History transactionHistory[MAX_HISTORY];
int historyCount = 0;
Member* memberList = NULL;

// Function prototypes
void addBook(int id, const char* title);
void addMember(const char* regNumber, const char* date);
void displayBooks();
void borrowBook(const char* regNumber, int bookId);
void returnBook(const char* regNumber, int bookId, const char* returnDate);
void displayHistory(const char* regNumber);
void updatePenaltyStatus(const char* regNumber);
Member* findMember(const char* regNumber);
int calculateDaysDifference(const char* startDate, const char* endDate);

void addBook(int id, const char* title) {
    books[bookCount].id = id;
    strcpy(books[bookCount].title, title);
    books[bookCount].available = 1;
    bookCount++;
}

void addMember(const char* regNumber, const char* date) {
    Member* newMember = (Member*)malloc(sizeof(Member));
    strcpy(newMember->registrationNumber, regNumber);
    newMember->next = memberList;
    memberList = newMember;
    printf("New member added with Registration No: %s on %s\n", regNumber, date);
}

void displayBooks() {
    printf("Available books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Available: %s\n",
               books[i].id,
               books[i].title,
               books[i].available ? "Yes" : "No");
    }
}

void borrowBook(const char* regNumber, int bookId) {
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookId && books[i].available == 1) {
            books[i].available = 0;
            strcpy(transactionHistory[historyCount].registrationNumber, regNumber);
            strcpy(transactionHistory[historyCount].borrowedBook, books[i].title);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            sprintf(transactionHistory[historyCount].borrowDate, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
            transactionHistory[historyCount].penaltyFee = 0;
            transactionHistory[historyCount].isPenaltyPaid = 0;
            historyCount++;
            printf("Book '%s' has been borrowed by member %s.\n", books[i].title, regNumber);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d is not available.\n", bookId);
    }
}

void returnBook(const char* regNumber, int bookId, const char* returnDate) {
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookId && books[i].available == 0) {
            books[i].available = 1;
            for (int j = 0; j < historyCount; j++) {
                if (strcmp(transactionHistory[j].registrationNumber, regNumber) == 0 &&
                    strcmp(transactionHistory[j].borrowedBook, books[i].title) == 0) {
                    strcpy(transactionHistory[j].returnDate, returnDate);

                    // Calculate penalty based on date difference
                    int daysLate = calculateDaysDifference(transactionHistory[j].borrowDate, returnDate) - 14;
                    if (daysLate > 0) {
                        transactionHistory[j].penaltyFee = daysLate;
                        printf("Book '%s' returned by member %s. Penalty: Rs. %d\n", books[i].title, regNumber, transactionHistory[j].penaltyFee);
                    } else {
                        printf("Book '%s' returned by member %s. No penalty.\n", books[i].title, regNumber);
                    }
                    found = 1;
                    break;
                }
            }
        }
    }
    if (!found) {
        printf("Book with ID %d was not borrowed.\n", bookId);
    }
}

void displayHistory(const char* regNumber) {
    int foundHistory = 0;
    printf("Transaction history for registration number %s:\n", regNumber);

    for (int i = 0; i < historyCount; i++) {
        if (strcmp(transactionHistory[i].registrationNumber, regNumber) == 0) {
            printf("Book Borrowed: %s\n", transactionHistory[i].borrowedBook);
            printf("Borrow Date: %s\n", transactionHistory[i].borrowDate);
            printf("Return Date: %s\n", transactionHistory[i].returnDate[0] ? transactionHistory[i].returnDate : "Not yet returned");
            printf("Penalty Fee: Rs. %d\n", transactionHistory[i].penaltyFee);
            printf("Penalty Status: %s\n", transactionHistory[i].isPenaltyPaid ? "Paid" : "Unpaid");
            printf("----------------------------\n");
            foundHistory = 1;
        }
    }

    if (!foundHistory) {
        printf("No borrowing history or penalty found.\n");
    }
}

void updatePenaltyStatus(const char* regNumber) {
    for (int i = 0; i < historyCount; i++) {
        if (strcmp(transactionHistory[i].registrationNumber, regNumber) == 0 && transactionHistory[i].penaltyFee > 0) {
            printf("Penalty for Book '%s': Rs. %d\n", transactionHistory[i].borrowedBook, transactionHistory[i].penaltyFee);
            printf("Mark as Paid? (1 for Yes, 0 for No): ");
            int choice;
            scanf("%d", &choice);
            if (choice == 1) {
                transactionHistory[i].isPenaltyPaid = 1;
                printf("Penalty marked as Paid.\n");
            } else {
                printf("Penalty remains Unpaid.\n");
            }
        }
    }
}

Member* findMember(const char* regNumber) {
    Member* temp = memberList;
    while (temp != NULL) {
        if (strcmp(temp->registrationNumber, regNumber) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int calculateDaysDifference(const char* startDate, const char* endDate) {
    struct tm start = {0}, end = {0};
    sscanf(startDate, "%d-%d-%d", &start.tm_year, &start.tm_mon, &start.tm_mday);
    sscanf(endDate, "%d-%d-%d", &end.tm_year, &end.tm_mon, &end.tm_mday);

    start.tm_year -= 1900;
    start.tm_mon -= 1;
    end.tm_year -= 1900;
    end.tm_mon -= 1;

    time_t startSec = mktime(&start);
    time_t endSec = mktime(&end);
    return (int)difftime(endSec, startSec) / (60 * 60 * 24);
}

int main() {
    int choice;
    char regNumber[20];
    char date[15];
    int bookId;

    addBook(1, "C Programming Language");
    addBook(2, "Data Structures and Algorithms");
    addBook(3, "Introduction to Algorithms");

    while (1) {
        printf("\nLibrary Management System:\n");
        printf("1. Display Books\n");
        printf("2. Add Member\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Display Member History\n");
        printf("6. Update Penalty Status\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBooks();
                break;
            case 2:
                printf("Enter user registration number: ");
                scanf("%s", regNumber);
                printf("Enter current date (yyyy-mm-dd): ");
                scanf("%s", date);
                addMember(regNumber, date);
                break;
            case 3:
                printf("Enter user registration number: ");
                scanf("%s", regNumber);
                printf("Enter book ID to borrow: ");
                scanf("%d", &bookId);
                borrowBook(regNumber, bookId);
                break;
            case 4:
                printf("Enter user registration number: ");
                scanf("%s", regNumber);
                printf("Enter book ID to return: ");
                scanf("%d", &bookId);
                printf("Enter today's date (yyyy-mm-dd): ");
                scanf("%s", date);
                returnBook(regNumber, bookId, date);
                break;
            case 5:
                printf("Enter user registration number: ");
                scanf("%s", regNumber);
                displayHistory(regNumber);
                break;
            case 6:
                printf("Enter user registration number to update penalty status: ");
                scanf("%s", regNumber);
                updatePenaltyStatus(regNumber);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
