#include <string>
#include <algorithm>
#include <iostream>
#include "utils.hh"
#include "output_element.hh"
#include "trie_node.hh"

inline static int min(int a, int b, int c) {
    return std::min(a, std::min(b, c));
}

static int **dist;
//static int dist[WORD_MAX_SIZE][WORD_MAX_SIZE];

void init_dist() {
    dist = (int **) malloc(WORD_MAX_SIZE * sizeof (int*));
    for (int i = 0; i < WORD_MAX_SIZE; i++) {
        dist[i] = (int *) malloc(WORD_MAX_SIZE * sizeof (int));
        dist[i][0] = i; // TODO: memset ?
        dist[0][i] = i;
    }
}

int lev_max(MyString& new_word, const char* s1, size_t len1, const std::string& s2, int maxDist) {
    size_t len2 = s2.length();
    for (int i = new_word.computed_index; i <= len1; i++) {
        int swapCost = s1[i - 1] == s2[0] ? 0 : 1;
        dist[i][1] = min(dist[i - 1][1] + 1, dist[i][0] + 1, dist[i - 1][0] + swapCost);
        for (int j = 2; j <= len2; j++) {
            int swapCost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            dist[i][j] = min(dist[i - 1][j] + 1, dist[i][j - 1] + 1, dist[i - 1][j - 1] + swapCost);
            if (i > 1) // optimized by compiler
                if (s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                    dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + swapCost);
                }
        }
        int j; // stop compute if dist is too big
        for (j = 1; j <= len2; j++)
            if (dist[i][j] <= maxDist)
                break;
        if (j == len2 + 1) {
            new_word.computed_index = i;
            return -1;
        }
    }
    new_word.computed_index = (int) len1;
    return dist[len1][len2];
}


int lev_zero(MyString& new_word, const char* s1, size_t len1, const std::string& s2) {
    size_t len2 = s2.length();
    if (len1 > len2)
        return -1;
    int i;
    for (i = new_word.computed_index - 1; i < len1; i++) {
        if (s1[i] != s2[i])
            return -1;
    }
    new_word.computed_index = i;
    return len1 == len2 ? 1 : 0;
}

/*int lev_max(MyString& new_word, const char* s1, size_t len1, const std::string& s2, int maxDist) {
    size_t len2 = s2.length();
    if (new_word.computed_index == 1 && len1 > 0) { // unrolling of first element
        int swapCost = s1[0] == s2[0] ? 0 : 1;
        dist[1][1] = min(dist[0][1] + 1, dist[1][0] + 1, dist[0][0] + swapCost);
        for (int j = 2; j <= len2; j++) {
            int swapCost = s1[0] == s2[j - 1] ? 0 : 1;
            dist[1][j] = min(dist[0][j] + 1, dist[1][j - 1] + 1, dist[0][j - 1] + swapCost);
//            if (s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
//                dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + swapCost);
//            }
        }
        int j; // stop compute if dist is too big
        for (j = 1; j <= len2; j++)
            if (dist[1][j] <= maxDist)
                break;
        if (j == len2 + 1) {
            new_word.computed_index = 1;
            return -1;
        }
        new_word.computed_index = 2;
    }
    for (int i = new_word.computed_index; i <= len1; i++) {
        int swapCost = s1[i - 1] == s2[0] ? 0 : 1;
        dist[i][1] = min(dist[i - 1][1] + 1, dist[i][0] + 1, dist[i - 1][0] + swapCost);
        for (int j = 2; j <= len2; j++) {
            int swapCost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            dist[i][j] = min(dist[i - 1][j] + 1, dist[i][j - 1] + 1, dist[i - 1][j - 1] + swapCost);
            if (s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + swapCost);
            }
        }
        int j; // stop compute if dist is too big
        for (j = 1; j <= len2; j++)
            if (dist[i][j] <= maxDist)
                break;
        if (j == len2 + 1) {
            new_word.computed_index = i;
            return -1;
        }
    }
    new_word.computed_index = (int) len1;
    return dist[len1][len2];
}*/