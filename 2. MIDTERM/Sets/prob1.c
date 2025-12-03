#include <stdio.h>
#include <stdlib.h> // Required for malloc() and free()

// --- Function Prototypes ---
// Declaring the functions before main() is good practice.

/**
 * @brief Converts an array of 4 short integers into a 64-element bit vector.
 * @param word The array of 4 short integers (16 bits each).
 * @return A pointer to a dynamically allocated 64-element integer array (bit vector).
 * The caller is responsible for freeing this memory.
 */
int* bitmaskToArray(short int word[]);

/**
 * @brief Decodes a 64-element bit vector into an 8-character string.
 * @param arr The 64-element bit vector (array of 0s and 1s).
 * @return A pointer to a dynamically allocated 9-byte char array (8 letters + '\0').
 * The caller is responsible for freeing this memory.
 */
char* decodeString(int arr[]);

/**
 * @brief Displays the 64-bit pattern with spaces every 16 bits.
 * @param arr The 64-element bit vector.
 */
void displayBitPattern(int arr[]);


// --- Main Program ---
// This function runs the menu and ties all the other functions together.
int main() {
    printf("=== Sabado Cipher ===\n\n");
    printf("Given the following integers, decode the numbers to form the 8 letter word\n");
    
    // The 4 integer values from the problem
    short int encodedMessage[4] = {17729, 21074, 18766, 18259};
    printf("%d %d %d %d\n\n", encodedMessage[0], encodedMessage[1], encodedMessage[2], encodedMessage[3]);

    // Pointers to hold the dynamically allocated data
    int* bitVector = NULL;
    char* decodedStr = NULL;
    int choice = 0;

    // We use a do-while loop to keep showing the menu until the user exits
    do {
        printf("Enter test case choice:\n");
        printf("1. Convert the decimal integers into a bit vector Array\n");
        printf("2. Decode the String using the converted bit vector Array\n");
        printf("3. Convert and Decode while displaying both\n");
        printf("0. Exit\n"); // Added an exit option
        printf("\nChoice: ");
        
        // Check if input is a valid integer
        if (scanf("%d", &choice) != 1) {
            // Clear the invalid input buffer
            while(getchar() != '\n');
            choice = -1; // Set to an invalid choice
        }

        printf("\n"); // Add a newline for clean formatting

        switch (choice) {
            case 1:
                // Free previous memory if it exists, before re-allocating
                if (bitVector) free(bitVector); 
                
                bitVector = bitmaskToArray(encodedMessage);
                if (bitVector == NULL) {
                    printf("Error: Memory allocation failed.\n");
                    return 1; // Exit with an error
                }
                displayBitPattern(bitVector);
                break;

            case 2:
                if (bitVector == NULL) {
                    // This check ensures Option 1 or 3 has been run first
                    printf("Error: Please run option 1 first to create the bit vector.\n");
                } else {
                    if (decodedStr) free(decodedStr); // Free previous string
                    
                    decodedStr = decodeString(bitVector);
                    if (decodedStr == NULL) {
                        printf("Error: Memory allocation failed.\n");
                        return 1;
                    }
                    printf("Decoded String: %s\n", decodedStr);
                }
                break;

            case 3:
                // Clean up any old data before running the full process
                if (bitVector) free(bitVector);
                if (decodedStr) free(decodedStr);

                // Step 1: Convert
                bitVector = bitmaskToArray(encodedMessage);
                if (bitVector == NULL) {
                    printf("Error: Memory allocation failed.\n");
                    return 1;
                }
                
                // Step 2: Display Bit Pattern
                displayBitPattern(bitVector);

                // Step 3: Decode
                decodedStr = decodeString(bitVector);
                if (decodedStr == NULL) {
                    printf("Error: Memory allocation failed.\n");
                    free(bitVector); // Clean up the vector before exiting
                    return 1;
                }
                
                // Step 4: Display String
                printf("Decoded String: %s\n", decodedStr);
                break;

            case 0:
                printf("Exiting. Janie's boyfriend thanks you!\n");
                break;

            default:
                printf("Invalid choice. Please enter 0, 1, 2, or 3.\n");
                break;
        }
        printf("\n"); // Add a newline for spacing
    } while (choice != 0);


    // --- Final Cleanup ---
    // Free all dynamically allocated memory before the program ends
    if (bitVector) {
        free(bitVector);
    }
    if (decodedStr) {
        free(decodedStr);
    }

    return 0; // Indicates successful execution
}


// --- Function Implementations ---

/**
 * 1. int* bitmaskToArray(short int word[])
 * This function takes the 4 short ints. Each short int is 16 bits.
 * It unpacks them into a single 64-element array of 0s and 1s.
 */
int* bitmaskToArray(short int word[]) {
    // 4 short ints * 16 bits/short = 64 bits total
    int* bitVector = (int*)malloc(64 * sizeof(int));
    if (bitVector == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    int vectorIndex = 0; // Current position in the bitVector array

    // Loop through each of the 4 short integers
    for (int i = 0; i < 4; i++) {
        short int currentWord = word[i];

        // Loop through each of the 16 bits for this short int
        // We go from 15 (most significant bit) down to 0 (least significant bit)
        // This ensures the bit order is correct (e.g., 0101... not ...1010)
        for (int j = 15; j >= 0; j--) {
            // (currentWord >> j) shifts the j-th bit to the 0-th position
            // & 1 isolates that bit (result is 1 if the bit was 1, 0 otherwise)
            int bit = (currentWord >> j) & 1;
            
            bitVector[vectorIndex] = bit;
            vectorIndex++; // Move to the next spot in the bit vector
        }
    }
    return bitVector;
}

/**
 * 2. char* decodeString(int arr[])
 * This function takes the 64-element bit vector.
 * It reads the vector in 8-bit chunks, converts each chunk to a character,
 * and assembles them into an 8-letter string.
 */
char* decodeString(int arr[]) {
    // We need 8 bytes for the letters + 1 byte for the null terminator '\0'
    char* decodedString = (char*)malloc(9 * sizeof(char));
    if (decodedString == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    int vectorIndex = 0; // Current position in the 64-bit vector

    // Loop 8 times to create 8 characters
    for (int i = 0; i < 8; i++) {
        char currentChar = 0; // Start with an 8-bit value of 00000000

        // Loop 8 times to read 8 bits from the vector
        for (int j = 0; j < 8; j++) {
            // 1. (currentChar << 1): 
            //    Shifts all bits left, e.g., 0101 -> 1010.
            //    This makes room for the new bit on the right.
            // 2. | arr[vectorIndex]: 
            //    Uses bitwise OR to add the new bit (0 or 1)
            //    from the vector into the new empty spot.
            currentChar = (currentChar << 1) | arr[vectorIndex];
            
            vectorIndex++; // Move to the next bit in the vector
        }
        
        // After 8 bits, we have a complete character. Add it to the string.
        decodedString[i] = currentChar;
    }

    // Add the null terminator at the end to make it a valid C string
    decodedString[8] = '\0';

    return decodedString;
}

/**
 * 3. void displayBitPattern(int arr[])
 * This function simply prints all 64 elements of the bit vector.
 * It adds a space every 16 bits to match the formatting in the image.
 */
void displayBitPattern(int arr[]) {
    printf("Bit Pattern: \n");
    // Loop through all 64 bits
    for (int i = 0; i < 64; i++) {
        printf("%d", arr[i]);

        // (i + 1) % 16 == 0 checks if we are at the 16th, 32nd, 48th, or 64th bit
        // i < 63 ensures we don't print a space after the very last bit
        if ((i + 1) % 16 == 0 && i < 63) {
            printf(" "); // Add a space to separate the 16-bit groups
        }
    }
    printf("\n"); // Print a final newline
}

