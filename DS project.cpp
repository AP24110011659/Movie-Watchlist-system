#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie {
    int id;
    char title[50];
    char genre[30];
    int watched;
    struct Movie *next;
};

struct Movie *head = NULL;

// Create a new movie
struct Movie* createMovie(int id, char title[], char genre[], int watched) {
    struct Movie *newMovie = (struct Movie*)malloc(sizeof(struct Movie));
    newMovie->id = id;
    strcpy(newMovie->title, title);
    strcpy(newMovie->genre, genre);
    newMovie->watched = watched;
    newMovie->next = NULL;
    return newMovie;
}

// Add Movie
void addMovie() {
    printf("\n========== ADD MOVIE OPERATION ==========\n");

    int id, watched;
    char title[50], genre[30];

    printf("Enter Movie ID: ");
    scanf("%d", &id);
    getchar();

    printf("Enter Movie Title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Enter Movie Genre: ");
    fgets(genre, sizeof(genre), stdin);
    genre[strcspn(genre, "\n")] = '\0';

    printf("Watched? (1 = Yes, 0 = No): ");
    scanf("%d", &watched);

    struct Movie *newMovie = createMovie(id, title, genre, watched);

    if (head == NULL) {
        head = newMovie;
    } else {
        struct Movie *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newMovie;
    }

    printf("Movie Successfully Added to Watchlist!\n");
}

// Display Movies
void displayWatchlist() {
    printf("\n========== DISPLAY WATCHLIST OPERATION ==========\n");

    if (head == NULL) {
        printf("Watchlist is Empty!\n");
        return;
    }

    struct Movie *temp = head;
    while (temp != NULL) {
        printf("ID: %d | Title: %s | Genre: %s | Status: %s\n",
               temp->id, temp->title, temp->genre,
               (temp->watched == 1 ? "Watched" : "Not Watched"));
        temp = temp->next;
    }
}

// Delete based on Title
void deleteMovie() {
    printf("\n========== DELETE MOVIE OPERATION ==========\n");

    if (head == NULL) {
        printf("Watchlist is Empty! Nothing to Delete.\n");
        return;
    }

    char name[50];
    getchar();
    printf("Enter Movie Title to Delete: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    struct Movie *temp = head;
    struct Movie *prev = NULL;

    if (temp != NULL && strcmp(temp->title, name) == 0) {
        head = temp->next;
        free(temp);
        printf("Movie Deleted Successfully.\n");
        return;
    }

    while (temp != NULL && strcmp(temp->title, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Movie Not Found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Movie Deleted Successfully.\n");
}

// Search based on Title
void searchMovie() {
    printf("\n========== SEARCH MOVIE OPERATION ==========\n");

    if (head == NULL) {
        printf("Watchlist is Empty!\n");
        return;
    }

    char name[50];
    getchar();
    printf("Enter Movie Title to Search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    struct Movie *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->title, name) == 0) {
            printf("\nMovie Found!\n");
            printf("ID: %d\nTitle: %s\nGenre: %s\nStatus: %s\n",
                   temp->id, temp->title, temp->genre,
                   (temp->watched ? "Watched" : "Not Watched"));
            return;
        }
        temp = temp->next;
    }

    printf("Movie Not Found.\n");
}

// Mark as Watched based on Title
void markWatched() {
    printf("\n========== MARK MOVIE AS WATCHED OPERATION ==========\n");

    if (head == NULL) {
        printf("Watchlist is Empty!\n");
        return;
    }

    char name[50];
    getchar();
    printf("Enter Movie Title to Mark as Watched: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    struct Movie *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->title, name) == 0) {
            temp->watched = 1;
            printf("Movie Status Updated to Watched!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Movie Not Found.\n");
}

void freeList() {
    struct Movie *temp = head;
    while (temp != NULL) {
        struct Movie *next = temp->next;
        free(temp);
        temp = next;
    }
}

int main() {
    int choice;

    do {
        printf("\n=========== MOVIE WATCHLIST MENU ===========\n");
        printf("1. Add Movie\n");
        printf("2. Delete Movie\n");
        printf("3. Display Watchlist\n");
        printf("4. Search Movie\n");
        printf("5. Mark as Watched\n");
        printf("6. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMovie(); break;
            case 2: deleteMovie(); break;
            case 3: displayWatchlist(); break;
            case 4: searchMovie(); break;
            case 5: markWatched(); break;
            case 6: 
                freeList();
                printf("\nThank You! Exiting Program...\n");
                break;
            default:
                printf("Invalid Choice! Try Again.\n");
        }

    } while (choice != 6);

    return 0;
}

