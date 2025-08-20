#include <stdio.h>
#include <string.h>

#define MAX_MOVIES 100

struct Movie {
    char title[100];
    char director[100];
    int releaseYear;
    float rating;
};

void addMovie(struct Movie movies[], int *count);
void displayMovies(struct Movie movies[], int count);
void searchMovie(struct Movie movies[], int count);
void updateMovie(struct Movie movies[], int count);
void saveToFile(struct Movie movies[], int count);
void loadFromFile(struct Movie movies[], int *count);

int main() {
    struct Movie movies[MAX_MOVIES];
    int count = 0;
    int choice;

    loadFromFile(movies, &count);

    do {
        printf("\n==== Movie Rating Database ====\n");
        printf("1. Add Movie\n");
        printf("2. Display Movies\n");
        printf("3. Search Movie\n");
        printf("4. Update Movie\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addMovie(movies, &count); break;
            case 2: displayMovies(movies, count); break;
            case 3: searchMovie(movies, count); break;
            case 4: updateMovie(movies, count); break;
            case 5: saveToFile(movies, count); break;
            case 6: loadFromFile(movies, &count); break;
            case 7: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 7);

    return 0;
}

// Tahmid's part
void addMovie(struct Movie movies[], int *count) {
    if (*count >= MAX_MOVIES) {
        printf("Database is full!\n");
        return;
    }

    printf("Enter movie title: ");
    fgets(movies[*count].title, 100, stdin);
    movies[*count].title[strcspn(movies[*count].title, "\n")] = 0;

    printf("Enter director: ");
    fgets(movies[*count].director, 100, stdin);
    movies[*count].director[strcspn(movies[*count].director, "\n")] = 0;

    printf("Enter release year: ");
    scanf("%d", &movies[*count].releaseYear);

    printf("Enter rating (0.0 - 10.0): ");
    scanf("%f", &movies[*count].rating);
    getchar();

    (*count)++;
    printf("Movie added successfully!\n");
}

// Saeeda's part
void displayMovies(struct Movie movies[], int count) {
    if (count == 0) {
        printf("No movies to display!\n");
        return;
    }

    printf("\n--- Movie List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s | Director: %s | Year: %d | Rating: %.1f\n",
               i+1, movies[i].title, movies[i].director,
               movies[i].releaseYear, movies[i].rating);
    }
}

// Mahadi's part
void searchMovie(struct Movie movies[], int count) {
    if (count == 0) {
        printf("No movies available!\n");
        return;
    }

    char query[100];
    printf("Enter title or director to search: ");
    fgets(query, 100, stdin);
    query[strcspn(query, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(movies[i].title, query) == 0 || strcasecmp(movies[i].director, query) == 0) {
            printf("Found: %s | Director: %s | Year: %d | Rating: %.1f\n",
                   movies[i].title, movies[i].director,
                   movies[i].releaseYear, movies[i].rating);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching movie found.\n");
    }
}

// Zulfiqar's part
void updateMovie(struct Movie movies[], int count) {
    if (count == 0) {
        printf("No movies available!\n");
        return;
    }

    char title[100];
    printf("Enter movie title to update: ");
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcasecmp(movies[i].title, title) == 0) {
            printf("Updating %s...\n", movies[i].title);

            printf("Enter new title: ");
            fgets(movies[i].title, 100, stdin);
            movies[i].title[strcspn(movies[i].title, "\n")] = 0;

            printf("Enter new director: ");
            fgets(movies[i].director, 100, stdin);
            movies[i].director[strcspn(movies[i].director, "\n")] = 0;

            printf("Enter new release year: ");
            scanf("%d", &movies[i].releaseYear);

            printf("Enter new rating: ");
            scanf("%f", &movies[i].rating);
            getchar();

            printf("Movie updated successfully!\n");
            return;
        }
    }

    printf("Movie not found!\n");
}

// Tasfia's part (1)
void saveToFile(struct Movie movies[], int count) {
    FILE *fp = fopen("movies.txt", "w");
    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s;%s;%d;%.1f\n",
                movies[i].title, movies[i].director,
                movies[i].releaseYear, movies[i].rating);
    }

    fclose(fp);
    printf("Movies saved to file!\n");
}

// Tasfia's part (2)
void loadFromFile(struct Movie movies[], int *count) {
    FILE *fp = fopen("movies.txt", "r");
    if (fp == NULL) {
        printf("No saved file found.\n");
        return;
    }

    *count = 0;
    while (fscanf(fp, "%99[^;];%99[^;];%d;%f\n",
                  movies[*count].title,
                  movies[*count].director,
                  &movies[*count].releaseYear,
                  &movies[*count].rating) == 4) {
        (*count)++;
        if (*count >= MAX_MOVIES) break;
    }

    fclose(fp);
    printf("Movies loaded from file!\n");
}
