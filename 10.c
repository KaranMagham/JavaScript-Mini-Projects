#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DISK_FILE "virtual_disk.bin"
#define DISK_SIZE (1024 * 1024) // 1 MB
#define BLOCK_SIZE 512
#define MAX_FILES 100
#define MAX_FILENAME 32
typedef struct
{
    char filename[MAX_FILENAME];
    int start_block;
    int num_blocks;
    int size;
    int is_used;
} FileEntry;
FileEntry directory[MAX_FILES];
// Initializes virtual disk and directory
void init_file_system()
{
    FILE *disk = fopen(DISK_FILE, "rb");
    if (!disk)
    {
        // Create new virtual disk
        disk = fopen(DISK_FILE, "wb");
        char zero = 0;
        for (int i = 0; i < DISK_SIZE; i++)
            fwrite(&zero, 1, 1, disk);
        fclose(disk);
        printf("Virtual disk created.\n");
    }
    else
    {
        fclose(disk);
    }
    // Initialize file directory
    for (int i = 0; i < MAX_FILES; i++)
    {
        directory[i].is_used = 0;
    }
}
// Find free contiguous blocks on disk
int find_free_blocks(int num_blocks)
{
    int used_blocks[DISK_SIZE / BLOCK_SIZE] = {0};
    // Mark used blocks
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (directory[i].is_used)
        {
            for (int j = 0; j < directory[i].num_blocks; j++)
            {
                used_blocks[directory[i].start_block + j] = 1;
            }
        }
    }
    // Search for contiguous free blocks
    int free_count = 0;
    for (int i = 0; i < (DISK_SIZE / BLOCK_SIZE); i++)
    {
        if (used_blocks[i] == 0)
        {
            free_count++;
            if (free_count == num_blocks)
            {
                return i - num_blocks + 1;
            }
        }
        else
        {
            free_count = 0;
        }
    }
    return -1; // Not enough space
}
// Create a file
void create_file()
{
    char name[MAX_FILENAME];
    char content[1024];
    printf("Enter file name: ");
    scanf("%s", name);
    printf("Enter file content: ");
    getchar(); // consume newline
    fgets(content, sizeof(content), stdin);
    int size = strlen(content);
    int blocks_needed = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int start_block = find_free_blocks(blocks_needed);
    if (start_block == -1)
    {
        printf("Not enough disk space!\n");
        return;
    }
    FILE *disk = fopen(DISK_FILE, "rb+");
    fseek(disk, start_block * BLOCK_SIZE, SEEK_SET);
    fwrite(content, 1, size, disk);
    fclose(disk);
    // Add to directory
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (!directory[i].is_used)
        {
            strcpy(directory[i].filename, name);
            directory[i].start_block = start_block;
            directory[i].num_blocks = blocks_needed;
            directory[i].size = size;
            directory[i].is_used = 1;
            break;
        }
    }
    printf("File '%s' created successfully.\n", name);
}
// List all files
void list_files()
{
    printf("Files in file system:\n");
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (directory[i].is_used)
        {
            printf("Name: %s | Size: %d bytes | Blocks: %d\n",
                   directory[i].filename,
                   directory[i].size,
                   directory[i].num_blocks);
        }
    }
}
// Read a file
void read_file()
{
    char name[MAX_FILENAME];
    printf("Enter file name to read: ");
    scanf("%s", name);
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (directory[i].is_used && strcmp(directory[i].filename, name) == 0)
        {
            char buffer[BLOCK_SIZE * directory[i].num_blocks + 1];
            FILE *disk = fopen(DISK_FILE, "rb");
            fseek(disk, directory[i].start_block * BLOCK_SIZE, SEEK_SET);
            fread(buffer, 1, directory[i].size, disk);
            buffer[directory[i].size] = '\0';
            fclose(disk);
            printf("File Content:\n%s\n", buffer);
            return;
        }
    }
    printf("File not found!\n");
}
// Delete a file
void delete_file()
{
    char name[MAX_FILENAME];
    printf("Enter file name to delete: ");
    scanf("%s", name);
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (directory[i].is_used && strcmp(directory[i].filename, name) == 0)
        {
            directory[i].is_used = 0;
            printf("File '%s' deleted.\n", name);
            return;
        }
    }
    printf("File not found!\n");
}
int main()
{
    init_file_system();
    int choice;
    while (1)
    {
        printf("\nSimple File System Menu:\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Delete File\n");
        printf("4. List Files\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create_file();
            break;
        case 2:
            read_file();
            break;
        case 3:
            delete_file();
            break;
        case 4:
            list_files();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}