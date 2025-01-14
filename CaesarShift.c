#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* encrypt(char *text, int shift) {
  char *result = strdup(text);
  for (int k = 0; result[k] != '\0'; k++) {
    if (result[k] >= 'A' && result[k] <= 'Z') {
      result[k] = (result[k] - 'A' + shift) % 26 + 'A';
    } else if (result[k] >= 'a' && result[k] <= 'z') {
      result[k] = (result[k] - 'a' + shift) % 26 + 'a';
    }
  }
  return result;
}

char* decrypt(char *text, int shift) {
  char* result = strdup(text);
  for (int k = 0; result[k] != '\0'; k++) {
    if (result[k] >= 'A' && result[k] <= 'Z') {
      result[k] = ((result[k] - 'A' - shift + 26) % 26) + 'A';
    } else if (result[k] >= 'a' && result[k] <= 'z') {
      result[k] = ((result[k] - 'a' - shift + 26) % 26) + 'a';
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  char *text = NULL;
  char *command = NULL;
  char *result = NULL;
  int shift = 0;

  if (argc == 4) {
    // Command-line input mode
    text = strdup(argv[1]);
    char *endptr;
    shift = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0') {
      printf("Invalid shift value. Must be a number.\n");
      free(text);
      return 1;
    }
    command = strdup(argv[3]);
  } else if (argc == 1) {
    // Interactive input mode
    char buffer[1000];
    printf("Enter text: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
      buffer[strcspn(buffer, "\n")] = '\0';
      text = strdup(buffer);
    }

    printf("Enter shift: ");
    char shiftInput[10];
    if (fgets(shiftInput, sizeof(shiftInput), stdin)) {
      char *endptr;
      shift = strtol(shiftInput, &endptr, 10);
      if (*endptr != '\0' && *endptr != '\n') {
	printf("Invalid shift value. Must be a number.\n");
	free(text);
	return 1;
      }
    }

    printf("Enter command (encrypt or decrypt): ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
      buffer[strcspn(buffer, "\n")] = '\0';
      command = strdup(buffer);
    }
  } else {
    printf("Usage: %s <text> <shift> <command>\n", argv[0]);
    return 1;
  }

  // Validate command
  if (strcmp(command, "encrypt") == 0) {
    result = encrypt(text, shift);
  } else if (strcmp(command, "decrypt") == 0) {
    result = decrypt(text, shift);
  } else {
    printf("Invalid command. Valid commands are 'encrypt' or 'decrypt'.\n");
    free(text);
    free(command);
    return 1;
  }

  // Print result
  printf("Result: %s\n", result);

  // Free allocated memory
  free(text);
  free(command);
  free(result);

  return 0;
}
