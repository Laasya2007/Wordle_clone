#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WORD_COUNT 100
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6

#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"

void updateKeyboardStatus(const char *inputWord, const char *randomWord, char keyboardStatus[]) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        int idx = inputWord[i] - 'a';
        if (inputWord[i] == randomWord[i]) {
            keyboardStatus[idx] = 1; // Green
        } else if (strchr(randomWord, inputWord[i]) && keyboardStatus[idx] != 1) {
            keyboardStatus[idx] = 2; // Yellow
        } else {
            keyboardStatus[idx] = 3; // Red
        }
    }
}

void printKeyboard(char keyboardStatus[]) {
    printf("Keyboard:\n");
    for (char c = 'a'; c <= 'z'; c++) {
        int idx = c - 'a';
        if (keyboardStatus[idx] == 1) {
            printf("%s%c%s ", GREEN, c, RESET);
        } else if (keyboardStatus[idx] == 2) {
            printf("%s%c%s ", YELLOW, c, RESET);
        } else if (keyboardStatus[idx] == 3) {
            printf("%s%c%s ", RED, c, RESET);
        } else {
            printf("%c ", c);
        }
    }
    printf("\n");
}

int main() {
    // Example word list (replace with 100 words if needed)
    const char *words[WORD_COUNT] = {
        "apple", "brain", "chair", "dream", "eagle", "flame", "grape", "house",
        "input", "jolly", "knife", "light", "mango", "night", "ocean", "piano",
        "queen", "river", "snake", "tiger", "union", "vivid", "world", "xenon",
        "yacht", "zebra"
    };

    srand(time(NULL));
    int randomIndex = rand() % 26; // Adjust to number of words you have
    const char *randomWord = words[randomIndex];

    char keyboardStatus[26] = {0}; // 0 = unused, 1 = green, 2 = yellow, 3 = red
    char inputWord[WORD_LENGTH + 1];

    printf("Welcome to Wordle Clone! Guess the %d-letter word.\n", WORD_LENGTH);

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        printf("\nAttempt %d/%d: ", attempt, MAX_ATTEMPTS);
        scanf("%s", inputWord);

        if (strlen(inputWord) != WORD_LENGTH) {
            printf("Invalid input. Please enter a %d-letter word.\n", WORD_LENGTH);
            attempt--;
            continue;
        }

        // Show colored feedback
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (inputWord[i] == randomWord[i]) {
                printf(GREEN "%c" RESET, inputWord[i]);
            } else if (strchr(randomWord, inputWord[i])) {
                printf(YELLOW "%c" RESET, inputWord[i]);
            } else {
                printf(RED "%c" RESET, inputWord[i]);
            }
        }
        printf("\n");

        updateKeyboardStatus(inputWord, randomWord, keyboardStatus);
        printKeyboard(keyboardStatus);

        if (strcmp(inputWord, randomWord) == 0) {
            printf("Congratulations! You guessed the word: %s\n", randomWord);
            return 0;
        }
    }

    printf("\nYou have used all your tries.\n");
    printf("The word was: %s\n", randomWord);
    return 0;
}
