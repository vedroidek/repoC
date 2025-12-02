#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int* build_lps(const char *pattern, int pattern_len) {
    int* lps = (int*)malloc(pattern_len * sizeof(int));
    if (lps == NULL) return NULL;
    
    lps[0] = 0;
    int len = 0;
    int i = 1;
    
    while (i < pattern_len) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int kmp_search(char *text, char *pattern, char *res_arr[], int arrlen) {
    if (!text || !pattern || !pattern[0]) return 0;
    
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    if (pattern_len > text_len) return 0;
    
    int *lps = build_lps(pattern, pattern_len);
    if (lps == NULL) return 0;
    
    int i = 0;
    int j = 0;
    int counter = 0;
    
    while (i < text_len) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        
        if (j == pattern_len) {
            if (counter < arrlen) {
                res_arr[counter++] = text + (i - j);
            } else {
                free(lps);
                return counter;
            }
            j = lps[j - 1];
        } else if (i < text_len && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    free(lps);
    return counter;
}