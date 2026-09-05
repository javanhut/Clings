// project1.c - word frequency counter
//
// THE PROJECT
// Read text from stdin, count how often each word occurs (case-
// insensitive, letters and digits only; everything else separates
// words), and print the N most frequent words with their counts, most
// frequent first, ties broken alphabetically. N comes from argv[1]
// (default 5). This is the shape of many real tools: read, tokenize,
// aggregate, sort, report.
//
// WHAT IT COMBINES
// fgets and ctype (15_io, 07_strings), a growable array of structs
// that own their strings (11_memory, 08_structs), linear or hashed
// lookup (13_data_structures), qsort with a two-key comparator
// (12_function_pointers), argv parsing with a default (15_io), and
// freeing everything at the end so LeakSanitizer stays quiet.
//
// SUGGESTED STRUCTURE
//   struct entry { char *word; int count; };
//   struct table { struct entry *items; size_t len, cap; };
//   table_bump(table, word)   find the word (strcmp) and increment, or
//                             append a copy with count 1
//   next_word(cursor, buf)    scan from *cursor: skip non-alnum, copy
//                             alnum chars lower-cased into buf, advance
//   by_count_then_word        comparator for qsort
//   main: read lines, tokenize each, bump; sort; print top N; free
//
// A linear search per word is fine at this size; if you want the
// challenge, use the hash map from hashmap1 instead.
//
// EXPECTED OUTPUT
//     the: 4
//     dog: 2
//     fox: 2
//     brown: 1
//     does: 1
//     (11 distinct words)

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 64

struct entry {
    char *word;
    int count;
};

struct table {
    struct entry *items;
    size_t len;
    size_t cap;
};

// TODO: implement the project.

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    return 0;
}
