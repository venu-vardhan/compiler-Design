#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define USERNAME_MIN_LEN 5
#define USERNAME_MAX_LEN 20
#define PASSWORD_MIN_LEN 8
#define PASSWORD_MAX_LEN 30

// Structure to store validation results
typedef struct {
    int valid;
    char message[256];
} ValidationResult;

// Function to validate username
ValidationResult validateUsername(char *username) {
    ValidationResult result;
    result.valid = 1;
    strcpy(result.message, "");
    
    // Check if username is empty
    if (username == NULL || strlen(username) == 0) {
        result.valid = 0;
        strcpy(result.message, "Username cannot be empty!");
        return result;
    }
    
    // Check length
    if (strlen(username) < USERNAME_MIN_LEN) {
        result.valid = 0;
        sprintf(result.message, "Username must be at least %d characters long!", USERNAME_MIN_LEN);
        return result;
    }
    
    if (strlen(username) > USERNAME_MAX_LEN) {
        result.valid = 0;
        sprintf(result.message, "Username cannot exceed %d characters!", USERNAME_MAX_LEN);
        return result;
    }
    
    // Check first character (must be alphabetic)
    if (!isalpha(username[0])) {
        result.valid = 0;
        strcpy(result.message, "Username must start with a letter!");
        return result;
    }
    
    // Check for valid characters (alphanumeric and underscore only)
    for (int i = 0; i < strlen(username); i++) {
        if (!isalnum(username[i]) && username[i] != '_') {
            result.valid = 0;
            strcpy(result.message, "Username can only contain letters, numbers, and underscores!");
            return result;
        }
    }
    
    // Check if username contains at least one letter
    int hasLetter = 0;
    for (int i = 0; i < strlen(username); i++) {
        if (isalpha(username[i])) {
            hasLetter = 1;
            break;
        }
    }
    
    if (!hasLetter) {
        result.valid = 0;
        strcpy(result.message, "Username must contain at least one letter!");
        return result;
    }
    
    strcpy(result.message, "Username is valid!");
    return result;
}

// Function to validate password
ValidationResult validatePassword(char *password) {
    ValidationResult result;
    result.valid = 1;
    strcpy(result.message, "");
    
    // Check if password is empty
    if (password == NULL || strlen(password) == 0) {
        result.valid = 0;
        strcpy(result.message, "Password cannot be empty!");
        return result;
    }
    
    // Check length
    if (strlen(password) < PASSWORD_MIN_LEN) {
        result.valid = 0;
        sprintf(result.message, "Password must be at least %d characters long!", PASSWORD_MIN_LEN);
        return result;
    }
    
    if (strlen(password) > PASSWORD_MAX_LEN) {
        result.valid = 0;
        sprintf(result.message, "Password cannot exceed %d characters!", PASSWORD_MAX_LEN);
        return result;
    }
    
    // Check for uppercase letter
    int hasUpper = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) {
            hasUpper = 1;
            break;
        }
    }
    
    if (!hasUpper) {
        result.valid = 0;
        strcpy(result.message, "Password must contain at least one uppercase letter!");
        return result;
    }
    
    // Check for lowercase letter
    int hasLower = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (islower(password[i])) {
            hasLower = 1;
            break;
        }
    }
    
    if (!hasLower) {
        result.valid = 0;
        strcpy(result.message, "Password must contain at least one lowercase letter!");
        return result;
    }
    
    // Check for digit
    int hasDigit = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (isdigit(password[i])) {
            hasDigit = 1;
            break;
        }
    }
    
    if (!hasDigit) {
        result.valid = 0;
        strcpy(result.message, "Password must contain at least one digit!");
        return result;
    }
    
    // Check for special character
    int hasSpecial = 0;
    char specialChars[] = "!@#$%^&*()-_=+[]{}|;:',.<>?/\\";
    for (int i = 0; i < strlen(password); i++) {
        for (int j = 0; j < strlen(specialChars); j++) {
            if (password[i] == specialChars[j]) {
                hasSpecial = 1;
                break;
            }
        }
        if (hasSpecial) break;
    }
    
    if (!hasSpecial) {
        result.valid = 0;
        strcpy(result.message, "Password must contain at least one special character (!@#$%^&*-_=+)!");
        return result;
    }
    
    // Check for spaces
    for (int i = 0; i < strlen(password); i++) {
        if (isspace(password[i])) {
            result.valid = 0;
            strcpy(result.message, "Password cannot contain spaces!");
            return result;
        }
    }
    
    strcpy(result.message, "Password is valid!");
    return result;
}

// Function to display password strength
void displayPasswordStrength(char *password) {
    int score = 0;
    
    if (strlen(password) >= PASSWORD_MIN_LEN) score++;
    if (strlen(password) > 12) score++;
    
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (islower(password[i])) hasLower = 1;
        if (isdigit(password[i])) hasDigit = 1;
    }
    
    char specialChars[] = "!@#$%^&*()-_=+[]{}|;:',.<>?/\\";
    for (int i = 0; i < strlen(password); i++) {
        for (int j = 0; j < strlen(specialChars); j++) {
            if (password[i] == specialChars[j]) {
                hasSpecial = 1;
                break;
            }
        }
    }
    
    if (hasUpper) score++;
    if (hasLower) score++;
    if (hasDigit) score++;
    if (hasSpecial) score++;
    
    printf("\nPassword Strength: ");
    switch (score) {
        case 0:
        case 1:
            printf("Weak\n");
            break;
        case 2:
        case 3:
            printf("Fair\n");
            break;
        case 4:
        case 5:
            printf("Good\n");
            break;
        case 6:
            printf("Strong\n");
            break;
        default:
            printf("Very Strong\n");
    }
}

// Function to display validation rules
void displayRules() {
    printf("\n========== VALIDATION RULES ==========\n");
    printf("\nUSERNAME REQUIREMENTS:\n");
    printf("  • Length: %d to %d characters\n", USERNAME_MIN_LEN, USERNAME_MAX_LEN);
    printf("  • Must start with a letter\n");
    printf("  • Can contain letters, numbers, and underscores only\n");
    printf("  • Must contain at least one letter\n");
    
    printf("\nPASSWORD REQUIREMENTS:\n");
    printf("  • Length: %d to %d characters\n", PASSWORD_MIN_LEN, PASSWORD_MAX_LEN);
    printf("  • At least one uppercase letter (A-Z)\n");
    printf("  • At least one lowercase letter (a-z)\n");
    printf("  • At least one digit (0-9)\n");
    printf("  • At least one special character (!@#$%%^&*-_=+)\n");
    printf("  • No spaces allowed\n");
    printf("=======================================\n\n");
}

// Function to display menu
void displayMenu() {
    printf("\n========== USERNAME & PASSWORD VALIDATOR ==========\n");
    printf("1. Register new user\n");
    printf("2. Validate username only\n");
    printf("3. Validate password only\n");
    printf("4. Run demo tests\n");
    printf("5. View validation rules\n");
    printf("6. Exit\n");
    printf("===================================================\n");
    printf("Enter your choice (1-6): ");
}

// Function for demo tests
void runDemoTests() {
    printf("\n========== DEMO: Running validation tests ==========\n\n");
    
    // Test usernames
    printf("--- USERNAME TESTS ---\n");
    char *testUsernames[] = {
        "john_doe",        // Valid
        "user123",         // Valid
        "j",               // Invalid - too short
        "123user",         // Invalid - starts with number
        "user@123",        // Invalid - special character
        "user name",       // Invalid - contains space
        "a_b_c_d_e_f_g",   // Invalid - too long
        "User_Name"        // Valid
    };
    
    int numUserTests = sizeof(testUsernames) / sizeof(testUsernames[0]);
    for (int i = 0; i < numUserTests; i++) {
        ValidationResult result = validateUsername(testUsernames[i]);
        printf("Username: %-15s | %s\n", testUsernames[i], 
               result.valid ? "✓ Valid" : "✗ Invalid");
        printf("  Message: %s\n\n", result.message);
    }
    
    // Test passwords
    printf("\n--- PASSWORD TESTS ---\n");
    char *testPasswords[] = {
        "Pass123!",        // Valid
        "Weak",            // Invalid - too short, no special char
        "password123!",    // Invalid - no uppercase
        "PASSWORD123!",    // Invalid - no lowercase
        "Password!",       // Invalid - no digit
        "Password123",     // Invalid - no special character
        "Pass 123!",       // Invalid - contains space
        "MyPass@2024"      // Valid
    };
    
    int numPassTests = sizeof(testPasswords) / sizeof(testPasswords[0]);
    for (int i = 0; i < numPassTests; i++) {
        ValidationResult result = validatePassword(testPasswords[i]);
        printf("Password: %-15s | %s\n", testPasswords[i], 
               result.valid ? "✓ Valid" : "✗ Invalid");
        printf("  Message: %s\n", result.message);
        if (result.valid) {
            displayPasswordStrength(testPasswords[i]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    int choice;
    char username[256];
    char password[256];
    
    printf("Welcome to Username & Password Validator!\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer
        
        switch (choice) {
            case 1: {
                printf("\n========== REGISTER NEW USER ==========\n");
                
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                if (username[strlen(username) - 1] == '\n') {
                    username[strlen(username) - 1] = '\0';
                }
                
                ValidationResult userResult = validateUsername(username);
                printf("\nUsername Validation: %s\n", userResult.message);
                
                if (!userResult.valid) {
                    printf("Registration failed. Please try again.\n");
                    break;
                }
                
                printf("\nEnter password: ");
                fgets(password, sizeof(password), stdin);
                if (password[strlen(password) - 1] == '\n') {
                    password[strlen(password) - 1] = '\0';
                }
                
                ValidationResult passResult = validatePassword(password);
                printf("\nPassword Validation: %s\n", passResult.message);
                
                if (!passResult.valid) {
                    printf("Registration failed. Please try again.\n");
                    break;
                }
                
                displayPasswordStrength(password);
                printf("\n✓ Registration successful for user: %s\n", username);
                break;
            }
            
            case 2:
                printf("\nEnter username to validate: ");
                fgets(username, sizeof(username), stdin);
                if (username[strlen(username) - 1] == '\n') {
                    username[strlen(username) - 1] = '\0';
                }
                
                ValidationResult userResult = validateUsername(username);
                printf("\nResult: %s\n", userResult.message);
                break;
                
            case 3:
                printf("\nEnter password to validate: ");
                fgets(password, sizeof(password), stdin);
                if (password[strlen(password) - 1] == '\n') {
                    password[strlen(password) - 1] = '\0';
                }
                
                ValidationResult passResult = validatePassword(password);
                printf("\nResult: %s\n", passResult.message);
                if (passResult.valid) {
                    displayPasswordStrength(password);
                }
                break;
                
            case 4:
                runDemoTests();
                break;
                
            case 5:
                displayRules();
                break;
                
            case 6:
                printf("\nThank you for using the validator. Goodbye!\n");
                break;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        
    } while (choice != 6);
    
    return 0;
}
