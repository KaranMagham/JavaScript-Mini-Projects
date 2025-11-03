#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 100
int main()
{
    int frames[MAX_FRAMES], recent[MAX_FRAMES];
    int page_sequence[MAX_PAGES];
    int num_frames, num_pages;
    int page_faults = 0, time = 0;
    // Initialize frames
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
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
    printf("\nPage replacement process using LRU:\n");
    for (int i = 0; i < num_pages; i++)
    {
        int current_page = page_sequence[i];
        int found = 0;
        // Check if page is already in frames (Hit)
        for (int j = 0; j < num_frames; j++)
        {
            if (frames[j] == current_page)
            {
                found = 1;
                recent[j] = time++; // Update usage time
                break;
            }
        }
        if (!found)
        {
            // Page Fault
            int replace_index = -1;
            // Look for an empty frame
            for (int j = 0; j < num_frames; j++)
            {
                if (frames[j] == -1)
                {
                    replace_index = j;
                    break;
                }
            }
            // If no empty frame, find least recently used
            if (replace_index == -1)
            {
                int lru_time = recent[0];
                replace_index = 0;
                for (int j = 1; j < num_frames; j++)
                {
                    if (recent[j] < lru_time)
                    {
                        lru_time = recent[j];
                        replace_index = j;
                    }
                }
            }
            frames[replace_index] = current_page;
            recent[replace_index] = time++;
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
            // Page Hit
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
