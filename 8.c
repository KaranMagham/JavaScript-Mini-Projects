#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 100
int main()
{
    int frames[MAX_FRAMES];
    int page_sequence[MAX_PAGES];
    int front = 0, rear = 0;
    int page_faults = 0;
    int num_frames, num_pages;
    // Initialize frames
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;
    }
    // Input number of frames
    printf("Enter number of frames (max %d): ", MAX_FRAMES);
    scanf("%d", &num_frames);
    // Input number of pages
    printf("Enter number of pages in the reference string (max %d): ",
           MAX_PAGES);
    scanf("%d", &num_pages);
    // Input page reference string
    printf("Enter the page reference string:\n");
    for (int i = 0; i < num_pages; i++)
    {
        scanf("%d", &page_sequence[i]);
    }
    printf("\nPage replacement process using FIFO:\n");
    for (int i = 0; i < num_pages; i++)
    {
        int current_page = page_sequence[i];
        int found = 0;
        // Check if page is already in frames
        for (int j = 0; j < num_frames; j++)
        {
            if (frames[j] == current_page)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            // Page fault occurs
            frames[rear] = current_page;
            rear = (rear + 1) % num_frames;
            if (page_faults >= num_frames)
            {
                front = (front + 1) % num_frames;
            }
            page_faults++;
            // Print current frame status
            printf("Page %d -> [", current_page);
            for (int k = 0; k < num_frames; k++)
            {
                if (frames[k] != -1)
                    printf("%d", frames[k]);
                else
                    printf("-");
                if (k != num_frames - 1)
                    printf(" ");
            }
            printf("] Page Fault\n");
        }
        else
        {
            // Page hit
            printf("Page %d -> [", current_page);
            for (int k = 0; k < num_frames; k++)
            {
                if (frames[k] != -1)
                    printf("%d", frames[k]);
                else
                    printf("-");
                if (k != num_frames - 1)
                    printf(" ");
            }
            printf("] Hit\n");
        }
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
    return 0;
}