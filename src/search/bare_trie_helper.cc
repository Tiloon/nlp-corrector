//
// Created by hugo on 29/07/17.
//

#include <cstring>
#include "bare_trie_helper.hh"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <cstdlib>

long get_freq(const char *ptr, size_t len) {
    return *(long *) (ptr + len + 1);
}

//void process_file(char *start, char *ptr) {
//    while (true) {
////        struct node *n = (struct node *) ptr;
//        std::string name = ptr;
//        if (name.empty()) {
//            break;
//        }
//        long *freq = (long *) (ptr + name.size() + 1);
//        long *next = (long *) (ptr + name.size() + 1 + sizeof(long));
//        std::cerr << name << std::endl;
//        std::cerr << *freq << std::endl;
//        std::cerr << *next << std::endl;
////        if (*next != 0)
////            process_file(start, start + *next); // iterate on this son
//        ptr = ptr + name.size() + 2 + sizeof(long) * 2;
//    }
//}

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
