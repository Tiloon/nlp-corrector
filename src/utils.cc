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

int lev_max(const char* s1, size_t len1, const std::string& s2, int maxDist, int prevLen) {
    size_t len2 = s2.length();
    prevLen = prevLen < 1 ? 1 : prevLen;
    prevLen = 1;
    for (int i = prevLen; i <= len1; i++) {
//        stock[i] = 0;
        for (int j = 1; j <= len2; j++) {
            int swapCost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            dist[i][j] = min(dist[i - 1][j] + 1, dist[i][j - 1] + 1, dist[i - 1][j - 1] + swapCost);
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + swapCost);
            }
        }
        int j; // stop compute if dist is too big
        for (j = 1; j <= len2; j++)
            if (dist[i][j] <= maxDist)
                break;
        if (j == len2 + 1) {
            return maxDist + 1;
        }
//            stock[i] = 1;
        }
//    }
//    int i = len1;
//    if (i >= 2 && stock[i] && stock[i - 1] && stock[i - 2])
//        return -1;
    return dist[len1][len2];
}
