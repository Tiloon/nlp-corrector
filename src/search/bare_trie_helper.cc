#include <cstring>
#include "bare_trie_helper.hh"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <cstdlib>

void *map_file(char *path) {
    int fd;
    struct stat stat;
    void *ptr;

    if ((fd = open(path, O_RDONLY)) < 0)
        err(EXIT_FAILURE, "%s", path);

    if (fstat(fd, &stat) != 0)
        err(EXIT_FAILURE, "%s", path);

    if ((ptr = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        err(EXIT_FAILURE, "%s", path);

    return ptr;
}
