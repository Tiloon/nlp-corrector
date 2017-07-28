//
// Created by hugo on 29/07/17.
//

#include "bin_node.hh"

inline const char *get_son(const char *ptr, size_t len) {
    return ptr + len + 1 + sizeof(long) * 2;
}

inline const char *get_brother(const char *start, const char *ptr, size_t len) {
    return start + *(long *) (ptr + len + 1 + sizeof(long));
}

inline const char *BinNode::g_son(const char *ptr, size_t len) {
    return get_son(ptr, len);
}

inline const char *BinNode::g_brother(const char *ptr, size_t len) {
    return get_brother(this->start, ptr, len);
}

inline const char *BinNode::go_to(size_t len) {
    return start + len;
}
