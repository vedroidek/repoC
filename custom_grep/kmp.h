#ifndef KMP_H
#define KMP_H

int kmp_search(char* text, char* pattern, char* res_arr[], int arrlen);
int* build_lps(const char* pattern, int pattern_len);

#endif