#include <string>
#include <algorithm>
#include <iostream>
#include "utils.hh"
#include "output_element.hh"

static int min(int a, int b, int c)
{
  if (a < b)
  {
    if (a < c)
      return a;
    else
      return c;
  }
  if (b < c)
    return b;
  return c;
}

int lev(const std::string& str1, const std::string& str2)
{
  std::cerr << str1 << std::endl;
  int len1 = str1.size();
  int len2 = str2.size();
  int d[len2 * 2 + 1];
  int c = 0;
  int k = 0;
  for (int i = 0; i <= 1; ++i)
    d[i * len2 + 0] = i;
  for (int i = 0; i <= len2; ++i)
    d[i] = i;
  for (int i = 1; i <= len1; ++i)
  {
    k = i % 2;
    for (int j = 1; j <= len2; ++j)
    {
      if (str1[i] == str2[j])
        c = 0;
      else
        c = 1;
      int tmp = min(d[(len2 * !k) + j] + 1,
          d[(len2 * k) + j - 1] + 1,
          d[(len2 * !k) + j - 1] + c);
      if (i > 1 && j > 1 && str1[i] == str2[j - 1] && str1[i - 1] == str2[j])
        tmp = std::min(tmp, d[(len2 * k) + j]);
      d[(len2 * k) + j] = tmp;
    }
    d[len2 * k] = i;
  }
  return d[k * len2 + len2];
}
