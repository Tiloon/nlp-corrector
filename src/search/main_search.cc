#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "output.hh"
#include "lev.hh"
#include "bin_node.hh"
#include "bare_trie_helper.hh"

//FIXME: Doc
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


/**
 * \brief Search the word in the trie recursively in the case of the maximum distance is not 0
 * \param currWord The word built by appending his fathers
 * \param curr The current node in the mmap'ed zone with the trie
 * \param myNode
 */
void resolveRec(MyString currWord, const char *curr, BinNode &myNode) {
    while (true) {
        size_t len = (size_t) (unsigned char) *curr;
        curr = curr + 1;
        currWord.append(curr, len);
        MyString new_word = MyString(currWord.index + len, currWord.computed_index);
        if (new_word.index <= myNode.wanted_word.length() + myNode.approx) {
            if (new_word.index >= myNode.wanted_word.length() - myNode.approx || new_word.index == myNode.approx + 1) { // call lev earlier and kill tree if too bad
                long freq = get_freq(curr, len);
                if (freq != 0) {
                    int dist = lev_max(new_word, new_word.get_string(), new_word.index, myNode.wanted_word,
                                       myNode.approx);
                    if (dist == -1)
                        goto after_son; // current branch is bad, skip the sons
                    if (dist <= myNode.approx) {
                        myNode.out.insert(OutputElement(new_word.get_string(), freq, dist));
                    }
                }
            }
            const char *first_son = myNode.g_son(curr, len);
            if (*first_son != '\0')
                resolveRec(new_word, first_son, myNode);
        }
        after_son:
        long next_pos = *(long *) (curr + len + 1 + sizeof(long));
        if (next_pos == 0l)
            return;
        curr = myNode.go_to(next_pos);
    }
}

/**
 * \brief Search the word in the trie recursively in the case of the maximum distance is 0
 * \param currWord The word built by appending his fathers
 * \param curr The current node in the mmap'ed zone with the trie
 * \param myNode
 */
void resolveRecZero(MyString currWord, const char *curr, BinNode &myNode) {
    while (true) {
        size_t len = (size_t) (unsigned char) *curr; // (int) (unsigned char) (curr) = 133
        curr = curr + 1;
        currWord.append(curr, len);
        MyString new_word = MyString(currWord.index + len, currWord.computed_index);
        long freq = get_freq(curr, len);
        int dist = lev_zero(new_word, new_word.get_string(), new_word.index, myNode.wanted_word);
        if (freq != 0 && dist == 1) { //we found it
            myNode.out.insert(OutputElement(new_word.get_string(), freq, 0));
            return;
        }

        if (dist != -1) { // dont match, go to brother
            const char *first_son = myNode.g_son(curr, len);
            if (*first_son != '\0')
                resolveRecZero(new_word, first_son, myNode);
        }
        long next_pos = *(long *) (curr + len + 1 + sizeof(long));
        if (next_pos == 0l)
            return;
        curr = myNode.go_to(next_pos);
    }
}

/**
 * \brief Search the word in the trie and print the results
 * \param ptr The mmap'ed zone with the trie
 * \param word The searched word
 * \param dist The maximum edition distance allowed
 */
void resolve(char *ptr, std::string word, int approx) {
    int max = (int) (word.size() + approx);
    auto myOutput = Output();
    BinNode myNode = BinNode(ptr, max, approx, word, myOutput);
    MyString currWord = MyString();
    if (approx == 0)
        resolveRecZero(currWord, ptr + 1, myNode);
    else
        resolveRec(currWord, ptr + 1, myNode); // ptr + 1 because of first empty char
    myOutput.print_json();
}


/**
 * \brief Search the word in the trie and print the results
 * \param ptr The mmap'ed zone with the trie
 * \param word The searched word
 * \param dist The maximum edition distance allowed
 */
void search(char* ptr, std::string word, int dist) {
    std::cerr << "Search: |" << word << "| Dist=" << dist << std::endl;
    resolve(ptr, word, dist);
}


int main(int argc, char** argv) {
    std::cerr << "Load Trie" << std::endl;
    char* ptr = (char*) map_file(argv[1]);
    init_dist();

#if 1
    for (std::string line; std::getline(std::cin, line);) {
        std::string approx;
        std::string precision;
        std::string word;
        std::istringstream iss(line);

        std::getline(iss, approx, ' ');
        std::getline(iss, precision, ' ');
        std::getline(iss, word, ' ');
        std::cerr << approx << " " << precision << " " << word << std::endl;

        search(ptr, word, stoi(precision));
    }
#else
    std::string precision = argv[2];
    std::string word = argv[3];

    search(ptr, word, stoi(precision));
#endif

    return 0;

}