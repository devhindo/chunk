#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to process the video
void process_video(const char* path, int percentage, const char* output_path) {
    // TODO: Implement this function
    printf("Processing video at %s with similarity percentage %d, output path: %s\n", path, percentage, output_path);
}

int is_supported_format(const char* path) {
    const char* dot = strrchr(path, '.');
    if(!dot || dot == path) return 0;
    if(strcmp(dot, ".mp4") == 0 || strcmp(dot, ".avi") == 0 || strcmp(dot, ".mkv") == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    const char* path = NULL;
    int percentage = 90;
    char output_path[256] = {0};

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--percentage") == 0) {
            if (i + 1 < argc) {
                percentage = atoi(argv[++i]);
                if (percentage < 0 || percentage > 100) {
                    fprintf(stderr, "Error: Invalid percentage. Must be between 0 and 100.\n");
                    return 1;
                }
            } else {
                fprintf(stderr, "Error: No percentage provided after -p/--percentage.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                strncpy(output_path, argv[++i], sizeof(output_path) - 1);
            } else {
                fprintf(stderr, "Error: No output path provided after -o/--output.\n");
                return 1;
            }
        }            else {
            if (path == NULL) {
                path = argv[i];
                if (access(path, F_OK) != 0) {
                    fprintf(stderr, "Error: File does not exist at provided path.\n");
                    return 1;
                }
                if (!is_supported_format(path)) {
                    fprintf(stderr, "Error: Unsupported video format. Only .mp4, .avi, and .mkv are supported.\n");
                    return 1;
                }
            } else {
                fprintf(stderr, "Error: Multiple paths provided. Only one path is allowed.\n");
                return 1;
            }
        }
    }

    if (path == NULL) {
        fprintf(stderr, "Error: No path provided.\n");
        return 1;
    }

    if (output_path[0] == '\0') {
        snprintf(output_path, sizeof(output_path), "%s-chunked.mp4", path);
    }

    process_video(path, percentage, output_path);

    return 0;
}