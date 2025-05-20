#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char write_buf[100];

    printf("Enter a string: ");
    fgets(write_buf, sizeof(write_buf), stdin);
    if (strlen(write_buf) == 0) {
        printf("No input provided.\n");
        return EXIT_FAILURE;
    }
    write_buf[strcspn(write_buf, "\n")] = 0; // Remove newline character

    // Write to file
    FILE *fp = fopen("output.txt", "w");
    if (!fp) {
        printf("Failed to open file when write!\n");
        return EXIT_FAILURE;
    }
    fprintf(fp, "%s", write_buf);
    fclose(fp);

    // Read from file
    char read_buf[100];
    fp = fopen("output.txt", "r");
    if (!fp) {
        printf("Failed to open file when read!\n");
        return EXIT_FAILURE;
    }
    fgets(read_buf, sizeof(read_buf), fp);
    fclose(fp);

    printf("Read from file: %s\n", read_buf);

    return EXIT_SUCCESS;
}
