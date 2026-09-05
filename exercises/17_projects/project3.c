// project3.c - an RPN calculator
//
// THE PROJECT
// Reverse Polish Notation puts the operator after its operands:
// "3 4 +" is 7, "5 1 2 + 4 * + 3 -" is 14. Evaluating it needs only a
// stack: push numbers; on an operator pop two, apply, push the result.
// At the end exactly one value must remain.
//
// Read one expression per line from stdin and print its value, or an
// error. Errors, printed to stdout as "error: <message>", are:
//   - "stack underflow"      an operator with fewer than two operands
//   - "division by zero"
//   - "unknown token: <tok>"  anything that is not a number or + - * /
//   - "too many values"      more than one value left at the end
//   - "empty"                a line with no tokens
// Exit with code 1 if any line had an error, 0 otherwise.
//
// WHAT IT COMBINES
// fgets + strtok tokenizing (07_strings, 15_io), strtod for numbers
// (like strtol but for doubles; check *end == '\0'), a stack of
// doubles (13_data_structures), a switch on the operator character
// (03_control_flow), a dispatch table if you like
// (12_function_pointers), and exit codes (15_io).
//
// SUGGESTED STRUCTURE
//   struct stack { double *items; size_t len, cap; } with push/pop
//   bool eval_line(char *line, double *result, const char **error)
//   main: loop over lines, print "%g" of the result or the error
//
// EXPECTED OUTPUT
//     7
//     14
//     2.5
//     error: stack underflow
//     error: division by zero
//     error: unknown token: x
//     error: too many values
//     error: empty
//     -3

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: implement the project.

int main(void)
{
    return 0;
}
