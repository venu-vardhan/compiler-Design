#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to count characters
void countCharacters(char *str) {
    int digits = 0;
    int vowels = 0;
    int consonants = 0;
    int symbols = 0;
    int spaces = 0;
    int uppercase = 0;
    int lowercase = 0;
    int length = strlen(str);
    
    printf("\n========== CHARACTER COUNT ANALYSIS ==========\n");
    printf("Input String: %s\n", str);
    printf("Total Length: %d\n", length);
    printf("=============================================\n\n");
    
    for (int i = 0; i < length; i++) {
        char ch = str[i];
        
        // Count digits
        if (isdigit(ch)) {
            digits++;
        }
        // Count vowels (case-insensitive)
        else if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                 ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            vowels++;
        }
        // Count consonants
        else if (isalpha(ch)) {
            consonants++;
        }
        // Count spaces
        else if (ch == ' ') {
            spaces++;
        }
        // Count symbols (special characters)
        else if (!isalnum(ch) && ch != ' ') {
            symbols++;
        }
        
        // Count uppercase and lowercase
        if (isupper(ch)) {
            uppercase++;
        } else if (islower(ch)) {
            lowercase++;
        }
    }
    
    // Display results
    printf("CHARACTER COUNTS:\n");
    printf("  Digits:       %d\n", digits);
    printf("  Vowels:       %d\n", vowels);
    printf("  Consonants:   %d\n", consonants);
    printf("  Symbols:      %d\n", symbols);
    printf("  Spaces:       %d\n", spaces);
    printf("  Uppercase:    %d\n", uppercase);
    printf("  Lowercase:    %d\n", lowercase);
    printf("  Alphabets:    %d (Vowels + Consonants)\n", vowels + consonants);
    printf("=============================================\n\n");
}

// Function to count from file
void countFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return;
    }
    
    int digits = 0;
    int vowels = 0;
    int consonants = 0;
    int symbols = 0;
    int spaces = 0;
    int newlines = 0;
    int uppercase = 0;
    int lowercase = 0;
    int total_chars = 0;
    int ch;
    
    printf("\n========== FILE CHARACTER COUNT ANALYSIS ==========\n");
    printf("File: %s\n", filename);
    printf("====================================================\n\n");
    
    while ((ch = fgetc(file)) != EOF) {
        total_chars++;
        char c = (char)ch;
        
        if (isdigit(c)) {
            digits++;
        } else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                   c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowels++;
        } else if (isalpha(c)) {
            consonants++;
        } else if (c == ' ') {
            spaces++;
        } else if (c == '\n') {
            newlines++;
        } else if (!isalnum(c) && c != ' ' && c != '\n') {
            symbols++;
        }
        
        if (isupper(c)) {
            uppercase++;
        } else if (islower(c)) {
            lowercase++;
        }
    }
    
    fclose(file);
    
    printf("CHARACTER COUNTS:\n");
    printf("  Total Characters: %d\n", total_chars);
    printf("  Digits:           %d\n", digits);
    printf("  Vowels:           %d\n", vowels);
    printf("  Consonants:       %d\n", consonants);
    printf("  Symbols:          %d\n", symbols);
    printf("  Spaces:           %d\n", spaces);
    printf("  Newlines:         %d\n", newlines);
    printf("  Uppercase:        %d\n", uppercase);
    printf("  Lowercase:        %d\n", lowercase);
    printf("  Alphabets:        %d\n", vowels + consonants);
    printf("====================================================\n\n");
}

// Function to display menu
void displayMenu() {
    printf("\n========== CHARACTER COUNTER ==========\n");
    printf("1. Count characters in a string\n");
    printf("2. Count characters in a file\n");
    printf("3. Run demo with sample strings\n");
    printf("4. Exit\n");
    printf("======================================\n");
    printf("Enter your choice (1-4): ");
}

// Main function
int main() {
    int choice;
    char input[500];
    char filename[256];
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer
        
        switch (choice) {
            case 1:
                printf("\nEnter a string: ");
                fgets(input, sizeof(input), stdin);
                // Remove newline if present
                if (input[strlen(input) - 1] == '\n') {
                    input[strlen(input) - 1] = '\0';
                }
                countCharacters(input);
                break;
                
            case 2:
                printf("\nEnter filename: ");
                fgets(filename, sizeof(filename), stdin);
                // Remove newline if present
                if (filename[strlen(filename) - 1] == '\n') {
                    filename[strlen(filename) - 1] = '\0';
                }
                countFromFile(filename);
                break;
                
            case 3:
                printf("\n========== DEMO: Running with sample strings ==========\n");
                
                // Sample 1
                countCharacters("Hello World123!");
                
                // Sample 2
                countCharacters("Programming@2024#");
                
                // Sample 3
                countCharacters("aeiou AEIOU bcdfg BCDFG 12345 !@#$%");
                
                break;
                
            case 4:
                printf("\nThank you for using Character Counter. Goodbye!\n");
                break;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
    } while (choice != 4);
    
    return 0;
}
