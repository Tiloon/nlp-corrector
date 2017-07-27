#include <string>
#include <algorithm>
#include <iostream>
#include "utils.hh"
#include "output_element.hh"
#include "trie_node.hh"

inline static int min(int a, int b, int c) {
    return std::min(a, std::min(b, c));
}

static int dist[WORD_MAX_SIZE][WORD_MAX_SIZE];
//static int stock[WORD_MAX_SIZE];

void init_dist() {
    for (int i = 0; i < WORD_MAX_SIZE; i++) {
        dist[i][0] = i; // TODO: memset ?
        dist[0][i] = i;
//        stock[i] = 0;
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
            if (i > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
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
