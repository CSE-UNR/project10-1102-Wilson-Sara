//Sara Wilson
//Date: 5-5-25
//Purpose: Project 10

#include <stdio.h>

#define MAX_GUESSES 6
#define WORD_LENGTH 6 //null character

//function declarations
void getInputWord(char input[]);
void getUserGuess(char guess[]);
void checkGuess(char guess[], char input[], char feedback[]);
void printBoard(char guesses[MAX_GUESSES][WORD_LENGTH], char feedback[MAX_GUESSES][WORD_LENGTH], int attempt);
int isCorrect(char guess[], char input[]);
int getLength(char word[]);

int main() {
    char input[WORD_LENGTH];
    char guesses[MAX_GUESSES][WORD_LENGTH];
    char feedback[MAX_GUESSES][WORD_LENGTH];
    int attempt;

    getInputWord(input);
    if (input[0] == '\0') return 1;

    for (attempt = 0; attempt < MAX_GUESSES; attempt++) {
        if (attempt == MAX_GUESSES - 1) {
            printf("FINAL GUESS : ");
        } else {
            printf("GUESS %d! Enter your guess: ", attempt + 1);
        }

        while (1) {
            getUserGuess(guesses[attempt]);
            if (getLength(guesses[attempt]) != 5) {
                printf("Your guess must be 5 letters long.\nPlease try again: ");
            } else {
                break;
            }
        }

        checkGuess(guesses[attempt], input, feedback[attempt]);
        printf("=========================================\n");
        printBoard(guesses, feedback, attempt);

        if (isCorrect(guesses[attempt], input)) {
            printf("You guessed the word!\n");
            return 0;
        }
    }

    printf("You lost, better luck next time!\n");
    return 0;
}

void getInputWord(char input[]) {
    FILE *file = fopen("word.txt", "r");
    if (file == NULL) {
        printf("Could not open word file.\n");
        input[0] = '\0';
        return;
    }
    fscanf(file, "%s", input);
    fclose(file);
}

void getUserGuess(char guess[]) {
    scanf("%s", guess);
}

void checkGuess(char guess[], char input[], char feedback[]) {
    int matched[WORD_LENGTH - 1] = {0};

    
    for (int i = 0; i < WORD_LENGTH - 1; i++) {
        if (guess[i] == input[i]) {
            feedback[i] = guess[i] - 32; //uppercase
            matched[i] = 1;
        } else {
            feedback[i] = ' ';
        }
    }


    for (int i = 0; i < WORD_LENGTH - 1; i++) {
        if (feedback[i] == ' ') {
            for (int j = 0; j < WORD_LENGTH - 1; j++) {
                if (!matched[j] && guess[i] == input[j]) {
                    feedback[i] = '^';
                    matched[j] = 1;
                    break;
                }
            }
        }
    }

    feedback[WORD_LENGTH - 1] = '\0';
}

void printBoard(char guesses[MAX_GUESSES][WORD_LENGTH], char feedback[MAX_GUESSES][WORD_LENGTH], int attempt) {
    printf("%s\n", guesses[attempt]);
    printf("%s\n\n", feedback[attempt]);
}

int isCorrect(char guess[], char input[]) {
    for (int i = 0; i < WORD_LENGTH - 1; i++) {
        char g = guess[i];
        if (g >= 'A' && g <= 'Z') g += 32;
        if (g != input[i]) return 0;
    }
    return 1;
}

int getLength(char word[]) {
    int length = 0;
    while (word[length] != '\0') {
        length++;
    }
    return length;
}










	
	 

