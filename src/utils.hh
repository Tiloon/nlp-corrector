#pragma once
#include <string>

int lev(const std::string &s1, const std::string &s2);
int lev_max(char* s1, size_t len1, const std::string &s2, int maxDist, int prevLen);
void init_dist();
