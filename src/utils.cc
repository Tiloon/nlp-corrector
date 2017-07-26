#include <string>
#include <algorithm>
#include <iostream>
#include "utils.hh"
#include "output_element.hh"

static int min(int a, int b, int c) {
    if (a < b) {
        if (a < c)
            return a;
        else
            return c;
    }
    if (b < c)
        return b;
    return c;
}

int lev(const std::string &s1, const std::string &s2) {
    int len1 = s1.length();
    int len2 = s2.length();
    int dist[len1 + 1][len2 + 1];


    for (int i = 0; i <= len1; i++) {
        dist[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        dist[0][j] = j;
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int swapCost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            dist[i][j] = min(dist[i - 1][j] + 1, dist[i][j - 1] + 1, dist[i - 1][j - 1] + swapCost);

            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + swapCost);
            }
        }
    }
    return dist[len1][len2];
}

int lev_max(const std::string &s1, const std::string &s2, int maxDist) {
    int len1 = s1.length();
    int len2 = s2.length();
    int dist[len1 + 1][len2 + 1];


    for (int i = 0; i <= len1; i++) {
        dist[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        dist[0][j] = j;
    }

    for (int i = 1; i <= len1; i++) {
        int needToContinue = 0;
        for (int j = 1; j <= len2; j++) {
            int swapCost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            dist[i][j] = min(dist[i - 1][j] + 1, dist[i][j - 1] + 1, dist[i - 1][j - 1] + swapCost);
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + swapCost);
//                std::cerr << dist[i][j] << "/" << maxDist  << "/" << (dist[i][j] <= maxDist) << std::endl;
            }
            needToContinue = needToContinue || (dist[i][j] <= maxDist);
        }
        if (!needToContinue)
            return maxDist + 1;
    }
    return dist[len1][len2];
}
