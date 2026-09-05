// project4.c - a tiny records database
//
// THE PROJECT
// Read CSV-like records "name,department,salary" from stdin into memory
// (skipping blank lines and reporting malformed ones to stderr), then
// carry out the commands given as arguments, in order:
//
//   sort name | sort dept | sort salary   sort by that field (salary
//                                         descending, others ascending;
//                                         ties by name)
//   filter DEPT                            keep only that department
//   print                                  print a table
//   total                                  print the total salary
//
// Table format: name left-aligned in 8 columns, department left-aligned
// in 12, salary right-aligned in 7, separated by single spaces.
//
// WHAT IT COMBINES
// Everything: a struct with owned strings and a growable array of them
// (08, 11), tokenizing with strtok and validating with strtol (07),
// stdin and argv (15), qsort with comparators picked from a table by
// name (12), swap-remove or compaction for filter (08), printf width
// and alignment (00), and freeing every allocation. This is a small
// version of what awk, sqlite's shell or a report generator does.
//
// SUGGESTED STRUCTURE
//   struct record { char *name; char *dept; long salary; };
//   struct db { struct record *rows; size_t len, cap; };
//   bool db_add_line(db, line)    parse and append; false if malformed
//   void db_filter(db, dept)      compact in place, freeing dropped rows
//   comparators by_name, by_dept, by_salary
//   main: read; for each argv command apply; free
//
// Clings runs the program with: sort salary filter eng print total
//
// EXPECTED OUTPUT
//     grace    eng           120000
//     ada      eng           105000
//     linus    eng            98000
//     total: 323000

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record {
    char *name;
    char *dept;
    long salary;
};

struct db {
    struct record *rows;
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
