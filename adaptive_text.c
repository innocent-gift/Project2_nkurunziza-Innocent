#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct wordStat { 
    char name[40]; 
    int count;
};

// Analysis function prototypes matching function pointer schema
void count_words(struct wordStat *stats, int size);
void longest_word(struct wordStat *stats, int size);
void most_frequent(struct wordStat *stats, int size);
void vowel_density(struct wordStat *stats, int size); // Custom Analysis

int main() {
    // Dynamic allocation of source text
    char *text = (char *)malloc(1024 * sizeof(char));
    if (!text) return 1;

    //  text analysis paragraph
    strcpy(text, "Equipped with his five senses, man explores the universe around him and calls the adventure Science.");
    
    printf("Source Text Address: %p\n", (void*)text);

    int max_words = 100;
    struct wordStat *stats_array = (struct wordStat *)malloc(max_words * sizeof(struct wordStat));
    printf("Word stats array address: %p\n", (void*)stats_array);

    int unique_count = 0;
    char *ptr = text;
    char word[40];
    int w_idx = 0;

    // Manual pointer traversal for string splitting
    while (*ptr != '\0') {
        if (isalpha((unsigned char)*ptr)) {
            if (w_idx < 39) {
                word[w_idx++] = tolower((unsigned char)*ptr);
            }
        } else if (w_idx > 0) {
            word[w_idx] = '\0';
            
            // Search if word exists using strcmp
            int found = 0;
            struct wordStat *s_ptr = stats_array;
            for (int i = 0; i < unique_count; i++, s_ptr++) {
                if (strcmp(s_ptr->name, word) == 0) {
                    s_ptr->count++;
                    found = 1;
                    break;
                }
            }
            // If new unique word discovered
            if (!found && unique_count < max_words) {
                strcpy((stats_array + unique_count)->name, word);
                (stats_array + unique_count)->count = 1;
                unique_count++;
            }
            w_idx = 0;
        }
        ptr++;
    }
    
    // Handle last trailing word if active
    if (w_idx > 0) {
        word[w_idx] = '\0';
        int found = 0;
        for (int i = 0; i < unique_count; i++) {
            if (strcmp(stats_array[i].name, word) == 0) {
                stats_array[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(stats_array[unique_count].name, word);
            stats_array[unique_count].count = 1;
            unique_count++;
        }
    }

    // Array of function pointers to execute steps
    void (*analyses[])(struct wordStat*, int) = {
        count_words,
        longest_word,
        most_frequent,
        vowel_density
    };

    printf("\n Executing Analysis Engine \n");
    for(int i = 0; i < 4; i++) {
        analyses[i](stats_array, unique_count);
    }

    free(text);
    free(stats_array);
    return 0;
}

void count_words(struct wordStat *stats, int size) {
    int total = 0;
    for (struct wordStat *p = stats; p < stats + size; p++) {
        total += p->count;
    }
    printf("Total Words Parsed: %d (Unique: %d)\n", total, size);
}

void longest_word(struct wordStat *stats, int size) {
    struct wordStat *longest = stats;
    for (struct wordStat *p = stats + 1; p < stats + size; p++) {
        if (strlen(p->name) > strlen(longest->name)) {
            longest = p;
        }
    }
    printf("Longest Word Identified: '%s' (Length: %lu)\n", longest->name, strlen(longest->name));
}

void most_frequent(struct wordStat *stats, int size) {
    struct wordStat *most = stats;
    for (struct wordStat *p = stats + 1; p < stats + size; p++) {
        if (p->count > most->count) {
            most = p;
        }
    }
    printf("Most Frequent Word: '%s' (Occurrences: %d)\n", most->name, most->count);
}

// Custom function checking specific rule criteria
void vowel_density(struct wordStat *stats, int size) {
    printf("Custom Analysis: Words with Vowel Density higher than 50%%:\n");
    for (struct wordStat *p = stats; p < stats + size; p++) {
        int v_count = 0;
        size_t len = strlen(p->name);
        for (size_t i = 0; i < len; i++) {
            char ch = p->name[i];
            if (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') {
                v_count++;
            }
        }
        float density = (float)v_count / len;
        if (density > 0.5f) {
            printf(" -> %-15s (Density: %2.1f%%)\n", p->name, density * 100);
        }
    }
}
