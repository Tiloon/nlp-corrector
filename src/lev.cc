#include <string>
#include <algorithm>
#include <iostream>

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


static int lev(const std::string& str1, const std::string& str2)
{
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
      if (str1[i - 1] == str2[j - 1])
        c = 0;
      else
        c = 1;
      d[(len2 * k) + j] = min(d[(len2 * !k) + j] + 1,
          d[(len2 * k) + j - 1] + 1,
          d[(len2 * !k) + j - 1] + c);
      // if (i > 1 && j > 1 && str[1
    }
    d[len2 * k] = i;
  }
  return d[k * len2 + len2];
}

int main(int argc, char** argv) {
  if (argc != 3)
    return 1;
  std::cout << lev(argv[1], argv[2]) << "\n";
}
