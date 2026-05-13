#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 256

void usage(const char *progname) {
    fprintf(stderr, "Usage: %s <filename> <key>\n", progname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
    }

    const char *filename = argv[1];
    int key = atoi(argv[2]);

    char enc_filename[MAX_FILENAME_LEN];
    snprintf(enc_filename, MAX_FILENAME_LEN, "%s.enc", filename);

    FILE *input_file = fopen(filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *enc_file = fopen(enc_filename, "wb");
    if (!enc_file) {
        perror("Failed to open output file");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            buffer[i] ^= key;
        }
        fwrite(buffer, 1, bytes_read, enc_file);
    }

    fclose(input_file);
    fclose(enc_file);

    char dec_filename[MAX_FILENAME_LEN];
    snprintf(dec_filename, MAX_FILENAME_LEN, "%s.dec", filename);

    FILE *dec_file = fopen(enc_filename, "rb");
    if (!dec_file) {
        perror("Failed to open encrypted file for decryption");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(dec_filename, "wb");
    if (!output_file) {
        perror("Failed to open output file for decryption");
        fclose(dec_file);
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), dec_file)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            buffer[i] ^= key;
        }
        fwrite(buffer, 1, bytes_read, output_file);
    }

    fclose(dec_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
