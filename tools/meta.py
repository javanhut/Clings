HEADER = '''# Exercise catalogue for Clings.
#
# Each [[exercises]] entry describes one file under exercises/<dir>/<name>.c
# with a reference solution at solutions/<dir>/<name>.c.
#
# Per-exercise fields:
#   name             (required) file stem of the .c file
#   dir              topic directory below exercises/ and solutions/
#   description      one-line summary shown by `clings list`; starts with
#                    "Fix:" (repair a broken program), "Write:" (implement
#                    something from a spec) or "Project:" (a larger program)
#   hint             (required) shown by `clings hint`
#   std              c89 | c99 | c11 | c17 (default) | c23
#   expected_stdout  exact stdout the program must print
#   expected_exit    exit code the program must return (default 0)
#   args             command-line arguments the program is started with
#   stdin            text fed to the program on standard input
#   extra_sources    further .c files in the exercise's directory that are
#                    compiled and linked with the exercise (for multi-file
#                    exercises about headers and linkage)
#   required_flags   extra compiler flags for this exercise
#   skip_check_unsolved  `clings dev check` will not verify that the unsolved
#                    exercise fails
#
# This file is generated from the solutions: expected_stdout is whatever the
# reference solution prints. Edit the exercise, the solution and the hint,
# then regenerate.

format_version = 1

# Flags passed to the compiler for every exercise. Warnings fail an exercise.
# The sanitizers make out-of-bounds accesses, use-after-free, leaks and
# undefined behavior (signed overflow, bad shifts, ...) fail at run time
# instead of silently "working". Clings drops the -fsanitize flags
# automatically on compilers that do not support them.
default_flags = [
    "-Wall",
    "-Wextra",
    "-g",
    "-fsanitize=address,undefined",
    "-fno-sanitize-recover=undefined",
]
'''

WELCOME = r'''
       Welcome to...
        ____ _ _
       / ___| (_)_ __   __ _ ___
      | |   | | | '_ \ / _` / __|
      | |___| | | | | | (_| \__ \
       \____|_|_|_| |_|\__, |___/
                       |___/

Clings is a set of exercises that take you from your first compile error to
writing real C: pointers, memory management, data structures, the
preprocessor, I/O and the undefined behavior that bites everyone.

There are three kinds of exercise:
  Fix:     a program with a bug or a gap. Repair it.
  Write:   a specification and a test harness. You write the code.
  Project: a larger program that combines several topics.

Every exercise must compile without warnings and print exactly the expected
output. The compiler runs with AddressSanitizer and UndefinedBehaviorSanitizer,
so memory errors and undefined behavior fail loudly instead of hiding.

Each file starts with a long comment: what the concept is, when real programs
use it, and the task. Read it. Stuck? Press `h` for a hint. Lost a concept
later on? `clings reset 06_pointers` gives you a whole topic back to redo.
'''

FINAL = '''
That was every exercise Clings has for you. Well done!

Where to go from here:
  - Read "The C Programming Language" by Kernighan and Ritchie, then
    "Modern C" by Jens Gustedt for the C11/C17 view.
  - Write a real tool: a line editor, a JSON parser, an HTTP client with
    sockets, a tiny virtual machine. Keep it warning-free under
    -Wall -Wextra -fsanitize=address,undefined.
  - Read other people's C: the Redis, SQLite and Lua sources are small,
    readable and beautifully engineered.
  - Forgot something? `clings reset --all --keep-file` lets you redo the
    whole course while keeping your old answers around to compare.
'''

META = []
def ex(name, dir, description, hint, **kw):
    META.append(dict(name=name, dir=dir, description=description, hint=hint, **kw))

# ---------------------------------------------------------------- 00_intro
ex("intro1", "00_intro", "Fix: your first compile error.", """
Every C statement ends with a semicolon. Look at the line with printf: the
compiler even tells you the line number where it expected a `;`.""")
ex("intro2", "00_intro", "Fix: newlines are your job, not printf's.", """
Inside a string, `\\n` is the newline character. Add one at the end of each
string you print.""")
ex("intro3", "00_intro", "Write: printf format specifiers.", """
One printf per line is easiest: printf("Name: %s\\n", name); and so on.
%.2f prints a double with two decimals. A literal percent sign is written
as %% in a format string.""")

# ---------------------------------------------------------------- 01_variables
ex("variables1", "01_variables", "Fix: declare before use.", """
A declaration names the type and the variable, for example `int x;`. You can
declare and assign in one go: `int x = 42;`.""")
ex("variables2", "01_variables", "Fix: const means constant.", """
`count` needs to change inside the loop, so it must not be `const`. Remove
the `const` from its declaration.""")
ex("variables3", "01_variables", "Fix: pick a type that fits the value.", """
Numbers with a fractional part need a floating-point type: `float` or
`double`. `double` is the usual choice, and it matches `%f` in printf.""")
ex("variables4", "01_variables", "Fix: block scope and shadowing.", """
Move `int largest = 0;` out of the loop, to just before the `for`. Then the
loop updates that one variable, and it is still in scope for the printf.""")
ex("variables5", "01_variables", "Write: choose types and do arithmetic.", """
width, height, area and perimeter are ints; scale and the scaled area are
doubles. `area * scale` is automatically computed in double because one
operand is a double. Tiles fit `area / 16` times and `area % 16` units are
left over. Print the scaled area with %.1f.""")

# ---------------------------------------------------------------- 02_types
ex("types1", "02_types", "Fix: integer division truncates.", """
If at least one operand of `/` is a floating-point value, the division is
done in floating point. Cast *before* dividing: `(double)a / b`.
`(double)(a / b)` is still 3.0 because the integer division already
happened.""")
ex("types2", "02_types", "Fix: characters are small integers.", """
Since 'A' + 1 is 'B', the letter two places after `c` is simply `c + 2`.
The value of a digit character is `digit - '0'`, because the digit codes
are consecutive.""")
ex("types3", "02_types", "Fix: every type has a range.", """
Change `unsigned char` to `int`. INT_MAX comes from <limits.h>; include it
and use the name instead of typing the number.""")
ex("types4", "02_types", "Fix: bool lives in a header before C23.", """
Add `#include <stdbool.h>` at the top of the file.""")
ex("types5", "02_types", "Fix: signed meets unsigned.", """
First bug: make `limit` an `int` (and cast it to unsigned only in the
printf, where %u needs it), or cast `limit` to int in the comparison.
Second bug: `i >= 0` is always true for a size_t. The idiom for counting
down with an unsigned index is `for (size_t i = count; i-- > 0;)`: the
condition decrements *after* the test, so the body sees count-1 ... 0 and
the loop stops when i was 0.""")
ex("types6", "02_types", "Write: fixed-width integers and how to print them.", """
`int64_t sum = (int64_t)a + b;` converts a first, so the addition is done
in 64 bits. Print sizeof with %zu, and 32/64-bit values with
`"%" PRId32` and `"%" PRId64` from <inttypes.h> (they are string pieces
that the compiler glues to the rest of the format).""")
ex("types7", "02_types", "Write: floating point is not exact.", """
nearly_equal: `return fabs(a - b) < epsilon;`. The loop: `for (int i = 0;
i < 10; i++) sum += 0.1;`. That is all; the point of the exercise is to see
the printed value 0.99999999999999989.""")

# ---------------------------------------------------------------- 03_control_flow
ex("if1", "03_control_flow", "Fix: = assigns, == compares.", """
Change `if (x = 5)` to `if (x == 5)`.""")
ex("if2", "03_control_flow", "Write: an if / else if chain.", """
Test the ranges from most specific to least: `n < 0`, then `n == 0`, then
`n >= 10`, then `n % 2 == 0` for even, else odd. Each branch is one printf
with %d for n.""")
ex("loops1", "03_control_flow", "Fix: off by one.", """
`i < 10` stops at 9. Use `i <= 10` to include 10.""")
ex("loops2", "03_control_flow", "Fix: break vs continue.", """
`break` leaves the loop the first time an odd number shows up (that is 1,
right away). You want to *skip* odd numbers: use `continue`.""")
ex("loops3", "03_control_flow", "Write: nested loops and aligned columns.", """
An outer loop over row = 1..4 and an inner loop over col = 1..4. Inside,
`printf("%3d", row * col);`. After the inner loop, print "\\n".""")
ex("loops4", "03_control_flow", "Write: do-while and while.", """
digit_sum: `int sum = 0; do { sum += n % 10; n /= 10; } while (n != 0);`.
collatz_steps: `while (n != 1) { n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
steps++; }`.""")
ex("switch1", "03_control_flow", "Fix: forgotten breaks.", """
Add a `break;` after each printf so execution does not fall through to
the next case.""")
ex("switch2", "03_control_flow", "Write: grouped cases.", """
Stack the labels: `case 1: case 3: case 5: ... return 31;`, then the 30-day
group, then `case 2: return leap ? 29 : 28;` and `default: return -1;`.""")
ex("ternary1", "03_control_flow", "Write: ternary expressions and goto cleanup.", """
max3: `int ab = a > b ? a : b; return ab > c ? ab : c;`.
plural: `return n == 1 ? "" : "s";`.
process: declare `int result = -1;` at the top. Each failure prints its
message and does `goto cleanup;`. After step 3, set `result = 0;`. Then
`cleanup:` followed by the "cleanup done" printf and `return result;`.""")

# ---------------------------------------------------------------- 04_functions
ex("functions1", "04_functions", "Fix: declare a function before calling it.", """
Add a prototype above main: `void greet(void);`. (Moving the whole
definition above main also works, but prototypes are what headers are
made of, so practice that.)""")
ex("functions2", "04_functions", "Fix: a value must be returned.", """
`return n * n;`""")
ex("functions3", "04_functions", "Fix: arguments are copies.", """
Change the return type to int, `return n + 1;`, and in main write
`x = increment(x);`.""")
ex("functions4", "04_functions", "Fix: recursion needs a base case.", """
`if (n == 0) return 1;` at the top of factorial.""")
ex("functions5", "04_functions", "Write: gcd, is_prime, count_primes_below.", """
gcd: `while (b != 0) { int t = a % b; a = b; b = t; } return a;`.
is_prime: return false for n < 2; `for (int d = 2; d * d <= n; d++)`
return false if `n % d == 0`; otherwise return true.
count_primes_below: loop n from 2 to limit-1 and count is_prime(n).""")
ex("functions6", "04_functions", "Write: static locals and file-scope state.", """
Put `static int counter = 0;` above next_id. next_id does `counter++;
return counter;` and reset_ids sets `counter = 0;`.
Careful in main: C does not say in which order the arguments of one
printf call are evaluated, so `printf("%d %d", next_id(), next_id())`
may print "2 1" on some compilers. Call next_id into separate variables
first, then print them.""")
ex("functions7", "04_functions", "Fix: return types and unused parameters.", """
1. print_banner never returns anything: make it `void`.
2. average divides two ints; divide by `2.0` (or cast) so the division
   happens in floating point.
3. `unused_flag` is never used: add `(void)unused_flag;` in the body.""")
ex("functions8", "04_functions", "Write: recursive power, fib and hanoi.", """
power: `if (exp == 0) return 1; return base * power(base, exp - 1);`
fib: `if (n < 2) return n; return fib(n - 1) + fib(n - 2);`
hanoi: `if (disks == 0) return 0; return 2 * hanoi(disks - 1) + 1;`""")

# ---------------------------------------------------------------- 05_arrays
ex("arrays1", "05_arrays", "Fix: reading past the end of an array.", """
The valid indices are 0 to 4. Change `i <= 5` to `i < 5`.""")
ex("arrays2", "05_arrays", "Fix: let sizeof count the elements.", """
`size_t len = sizeof(numbers) / sizeof(numbers[0]);`""")
ex("arrays3", "05_arrays", "Fix: two-dimensional arrays.", """
The outer loop runs over rows (`r < ROWS`), the inner over columns
(`c < COLS`).""")
ex("arrays4", "05_arrays", "Fix: arrays decay to pointers in calls.", """
Change the signature to `int sum(const int values[], size_t len)`, delete
the sizeof line, and call it with
`sum(numbers, sizeof(numbers) / sizeof(numbers[0]))`.""")
ex("arrays5", "05_arrays", "Write: read-only and in-place array functions.", """
index_of_max: start with best = 0, loop i from 1, update best when
values[i] > values[best] (strictly greater keeps the first of ties).
reverse: two indices, `i` from the front and `j` from the back; swap while
`i < j`. With size_t, write the back index as `len - 1 - i` and loop while
`i < len / 2`, which is safe for len 0.
count_if_even: count elements where `values[i] % 2 == 0`.
print_array: print "(empty)" and return when len is 0; otherwise print a
space before every element except the first, then a newline.""")
ex("arrays6", "05_arrays", "Write: passing 2D arrays to functions.", """
transpose: two nested loops over r and c, `out[c][r] = in[r][c];`.
row_sums: for each r, sum m[r][c] over c and print
`printf("row %d: %d\\n", r, sum);`.""")
ex("arrays7", "05_arrays", "Write: binary search and sorted insert.", """
find: `size_t lo = 0, hi = len; while (lo < hi) { size_t mid = lo +
(hi - lo) / 2; if (a[mid] == target) return (int)mid; if (a[mid] < target)
lo = mid + 1; else hi = mid; } return -1;`.
insert_sorted: find the first pos with a[pos] >= value (or pos == *len).
Shift from the end: `for (size_t i = *len; i > pos; i--) a[i] = a[i-1];`.
Then `a[pos] = value; (*len)++;`.""")

# ---------------------------------------------------------------- 06_pointers
ex("pointers1", "06_pointers", "Fix: address-of and dereference.", """
`int *p = &x;` The `&` operator gives the address of x.""")
ex("pointers2", "06_pointers", "Fix: swap through pointers.", """
`void swap(int *a, int *b)` with `int tmp = *a; *a = *b; *b = tmp;`, and
in main call `swap(&a, &b);`.""")
ex("pointers3", "06_pointers", "Fix: pointer arithmetic.", """
`values + 1` is the second element, `values + count - 1` the last, and
`last - first` the element distance (a ptrdiff_t).""")
ex("pointers4", "06_pointers", "Fix: check for NULL.", """
At the top of print_length: `if (s == NULL) { printf("(null)\\n");
return; }`.""")
ex("pointers5", "06_pointers", "Write: output parameters.", """
divmod: `if (b == 0) return false; *quotient = a / b; *remainder = a % b;
return true;`.
min_max: compute lo and hi in locals over the loop, then
`if (min != NULL) *min = lo;` and the same for max.""")
ex("pointers6", "06_pointers", "Write: walking a range with a pointer.", """
`for (const int *p = begin; p != end; p++)` and use `*p`. find_first
returns `p` inside the loop when `*p == target`, and NULL after it.""")
ex("pointers7", "06_pointers", "Fix: const correctness.", """
1. shout must not write into s. Print each character converted with
   toupper instead of modifying the string: putchar(toupper(...)).
2. `size_t length(const char *s)`.
3. `fixed` is a const pointer: it cannot be repointed at b. Drop the
   `fixed = &b;` line and add b through the pointer: `*fixed += b;`.""")
ex("pointers8", "06_pointers", "Write: pointers to pointers.", """
skip_spaces: `while (**cursor == ' ') (*cursor)++;`.
take_word: loop while `**cursor != '\\0' && **cursor != ' '`; copy the
character into out[n++] only if `n + 1 < cap`; always advance
`(*cursor)++`. After the loop `out[n] = '\\0';`.
choose: `*out = (*a > *b) ? a : b;`.""")
ex("pointers9", "06_pointers", "Fix: wild and dangling pointers.", """
Give p something to point at: `int value = 0; int *p = &value;`.
Move `int largest = values[0];` out of the inner block so it is still
alive when `*best` is read after the block.""")

# ---------------------------------------------------------------- 07_strings
ex("strings1", "07_strings", "Fix: strlen vs sizeof.", """
Include <string.h> and use `strlen(greeting)` for the character count;
`sizeof(greeting)` is the byte count of the array (6, with the '\\0').""")
ex("strings2", "07_strings", "Fix: comparing strings.", """
`strcmp(answer, "yes") == 0` tests for equal contents, and
`strcmp("apple", "banana") < 0` tests the sort order.""")
ex("strings3", "07_strings", "Write: reverse a string in place.", """
`size_t len = strlen(s); for (size_t i = 0; i < len / 2; i++)` swap
`s[i]` with `s[len - 1 - i]` through a temporary char. For len 0 the loop
body never runs.""")
ex("strings4", "07_strings", "Fix: || does not distribute.", """
Spell out each comparison: `c == 'a' || c == 'e' || c == 'i' || c == 'o'
|| c == 'u'`.""")
ex("strings5", "07_strings", "Fix: string literals are read-only.", """
Declare `char word[] = "hello";` in main, which makes a writable copy on
the stack. Change print_twice to take `const char *greeting`.""")
ex("strings6", "07_strings", "Write: strlen, strcpy, strcmp, strcat by hand.", """
my_strlen: count until s[n] == '\\0'.
my_strcpy: copy characters until and including the '\\0'; return dst.
my_strcmp: `while (*a != '\\0' && *a == *b) { a++; b++; } return
(unsigned char)*a - (unsigned char)*b;`.
my_strcat: `my_strcpy(dst + my_strlen(dst), src); return dst;`.""")
ex("strings7", "07_strings", "Fix: a buffer overflow, and snprintf.", """
`int n = snprintf(out, cap, "%s/%s", dir, file); return n >= 0 &&
(size_t)n < cap;`. snprintf writes at most cap bytes including the
terminator and returns the untruncated length, so n >= cap means it did
not fit.""")
ex("strings8", "07_strings", "Write: strtol with error checking, strtok.", """
parse_int: `char *end; errno = 0; long v = strtol(text, &end, 10);`
then reject if `end == text` (nothing parsed), `*end != '\\0'` (junk after
the number), `errno == ERANGE`, or v outside INT_MIN..INT_MAX. Otherwise
`*out = (int)v; return true;`.
sum_csv: `for (char *tok = strtok(line, ","); tok != NULL; tok =
strtok(NULL, ","))`, call parse_int on each token, add or print
"bad token: %s".""")
ex("strings9", "07_strings", "Write: ctype and three text algorithms.", """
count_words: keep `bool in_space = true;`. For each char, `bool space =
isspace((unsigned char)c)`; if in_space && !space, a word starts. Then
`in_space = space`.
title_case: same state; at a word start write toupper, elsewhere tolower.
is_palindrome: i from the front, j from the back (as an exclusive bound,
so compare s[j - 1]); skip non-alnum on either side; compare with
tolower; return false on mismatch, true when i >= j.""")

# ---------------------------------------------------------------- 08_structs
ex("structs1", "08_structs", "Fix: define struct members.", """
Inside the struct: `const char *name;` and `int age;`. For q:
`struct person q = {.name = "Grace", .age = 45};`.""")
ex("structs2", "08_structs", "Fix: -> for members through a pointer.", """
`p->x += dx;` and `p->y += dy;`.""")
ex("structs3", "08_structs", "Fix: arrays of structs.", """
`items[i].name`, `items[i].stock`, and `total += items[i].stock;`.""")
ex("structs4", "08_structs", "Fix: structs are copied when passed by value.", """
Change the parameters to `struct account *acc` (and `const struct
account *acc` for print_account), use `acc->balance` inside, and pass
`&acc` at every call in main.""")
ex("structs5", "08_structs", "Write: typedef, by-value structs, compound literals.", required_flags=["-lm"], hint="""
`typedef struct { double x; double y; } vec2;`
vec_add: `return (vec2){a.x + b.x, a.y + b.y};` and vec_scale similarly.
vec_dot: `a.x * b.x + a.y * b.y`. vec_len: `sqrt(vec_dot(v, v))`.""")
ex("structs6", "08_structs", "Write: nested structs and a bounded list.", """
rect_area: `(r.max.x - r.min.x) * (r.max.y - r.min.y)`.
rect_contains: p.x between min.x and max.x inclusive, same for y.
inventory_add: return false if `inv->count >= MAX_ITEMS`; otherwise fill
`inv->items[inv->count]` and increment count.
inventory_remove: loop over items; on `strcmp(name) == 0` do
`inv->items[i] = inv->items[inv->count - 1]; inv->count--; return true;`.""")
ex("structs7", "08_structs", "Write: tagged unions, and struct padding.", """
Both functions are a `switch (v->kind)` with one case per tag, reading
`v->as.i`, `v->as.d` or `v->as.s`. value_as_double returns the int
converted, the double as is, and 0.0 for strings. Add a `return 0.0;`
after the switch so the compiler sees every path returns.""")

# ---------------------------------------------------------------- 09_enums
ex("enums1", "09_enums", "Fix: a missing case.", """
Add `case GREEN: return "green";` to the switch.""")
ex("enums2", "09_enums", "Fix: a count sentinel and enum arithmetic.", """
The sentinel is `DIRECTION_COUNT` (the array already uses that name).
turn_right: `return (d + 1) % DIRECTION_COUNT;`.""")
ex("enums3", "09_enums", "Write: a state machine with enum and switch.", """
state_name: a switch returning "closed", "open", "locked".
next_state: switch on s; in CLOSED, 'o' gives OPEN and 'l' gives LOCKED;
in OPEN, 'c' gives CLOSED; in LOCKED, 'u' gives CLOSED; everything else
returns s.
run: `for (const char *e = events; *e; e++) { enum door_state next =
next_state(s, *e); printf("%c: %s -> %s\\n", *e, state_name(s),
state_name(next)); s = next; }`.""")

# ---------------------------------------------------------------- 10_bits
ex("bits1", "10_bits", "Fix: bitwise vs logical operators.", """
Testing a bit is `flags & PERM_READ` (single &). "Read or write" as a
mask is `PERM_READ | PERM_WRITE` (single |). The three `&&`/`||` in the
tests are the bugs.""")
ex("bits2", "10_bits", "Write: set, clear, toggle and test bit flags.", """
set: `flags | flag`; clear: `flags & ~flag`; toggle: `flags ^ flag`;
has_all: `(flags & mask) == mask`. describe: print "none" for 0,
otherwise test each style bit in order and print its name, with a space
before every name except the first.""")
ex("bits3", "10_bits", "Write: pack, unpack, popcount, power of two.", """
pack: `((uint32_t)r << 16) | ((uint32_t)g << 8) | b`.
get_byte: `(value >> (8 * index)) & 0xFF`.
popcount: `while (value) { value &= value - 1; count++; }`.
is_power_of_two: `value != 0 && (value & (value - 1)) == 0`.""")
ex("bits4", "10_bits", "Fix: undefined shifts and promotions.", """
1. `1 << 31` on int: use `1u << 31` and an unsigned variable.
2. `1 << 40` is shifted as an int: `(uint64_t)1 << 40`.
3. `~byte` promotes to int and gives -16 (0xfffffff0); cast the result
   back: `(uint8_t)~byte`.
4. low_bits(32) shifts by the full width. Handle n >= 32 explicitly by
   returning UINT32_MAX.""")
ex("bits5", "10_bits", "Write: binary printing, bit reversal, trailing zeros.", """
print_binary8: `for (int i = 7; i >= 0; i--) putchar((value >> i) & 1 ?
'1' : '0');`.
reverse_bits8: `result = (result << 1) | (value & 1); value >>= 1;`
eight times (cast the result to uint8_t).
trailing_zeros: return 32 for 0; otherwise count while `(value & 1) == 0`
shifting right.""")

# ---------------------------------------------------------------- 11_memory
ex("memory1", "11_memory", "Fix: malloc takes bytes, free gives them back.", """
`malloc(count * sizeof *squares)` (or `count * sizeof(int)`), and
`free(squares);` after the last use.""")
ex("memory2", "11_memory", "Write: a growable array with realloc.", """
push: `if (v->len == v->capacity) { size_t new_cap = v->capacity ? v->
capacity * 2 : 4; int *bigger = realloc(v->data, new_cap * sizeof
*bigger); if (!bigger) return false; v->data = bigger; v->capacity =
new_cap; } v->data[v->len++] = value; return true;`.
vec_free: free(v->data) and set data to NULL, len and capacity to 0.""")
ex("memory3", "11_memory", "Fix: returning a pointer to a local.", """
`size_t size = strlen("hello, ") + strlen(name) + 1; char *buffer =
malloc(size); if (!buffer) return NULL; snprintf(buffer, size, "hello,
%s", name); return buffer;` and in main `free(greeting);` after
printing.""")
ex("memory4", "11_memory", "Fix: use after free and double free.", """
Move the `free(numbers);` after the last read of the array (after the
two printfs) and delete the second free.""")
ex("memory5", "11_memory", "Fix: leaks on error paths, goto cleanup.", """
Declare `char *input = NULL; char *output = NULL; int result = 0;` at
the top. Each failure sets result and does `goto cleanup;` (the
`size < 0` check can still return directly, nothing is allocated yet).
At the end: `cleanup: free(output); free(input); return result;`.""",
skip_check_unsolved=True)
ex("memory6", "11_memory", "Write: calloc and two 2D layouts.", """
grid_new: malloc the struct, then `g->cells = calloc(rows * cols, sizeof
*g->cells)`; on failure free the struct and return NULL.
grid_at: `return &g->cells[r * g->cols + c];`.
grid_free: free cells, then the struct.
matrix_new: `int **m = malloc(rows * sizeof *m)`; for each row
`m[r] = calloc(cols, sizeof *m[r])`; if a row fails, call
`matrix_free(m, r)` (frees the r rows allocated so far) and return NULL.
matrix_free: free each row, then m.""")
ex("memory7", "11_memory", "Write: strdup and a two-pass join.", """
my_strdup: `size_t n = strlen(s) + 1; char *c = malloc(n); if (c)
memcpy(c, s, n); return c;`.
join: pass 1 adds strlen of every part plus strlen(sep) between parts,
plus 1. malloc that. Pass 2 memcpy each part and separator, advancing a
write pointer, then write the '\\0'.""")
ex("memory8", "11_memory", "Write: an owning struct with create/destroy.", """
person_create: malloc the struct; copy the name (malloc strlen + 1 and
memcpy); if the copy fails, free the struct and return NULL.
person_rename: make the copy first; only if it succeeds free the old
name and store the new one.
person_destroy: free the name, then the struct. Accept NULL.""")
ex("memory9", "11_memory", "Fix: three malloc sizing mistakes.", """
`malloc(strlen(text) + 1)`, `malloc(sizeof *pt)`, and
`malloc(n * sizeof *values)`.""")

# ---------------------------------------------------------------- 12_function_pointers
ex("fnptr1", "12_function_pointers", "Fix: declaring a function pointer.", """
`int (*op)(int, int);` with the parentheses, and
`typedef int (*binary_op)(int, int);` above pick.""")
ex("fnptr2", "12_function_pointers", "Write: qsort comparators.", """
by_int: `int x = *(const int *)a, y = *(const int *)b; return (x > y) -
(x < y);`.
by_length_then_alpha: the elements are `const char *`, so
`const char *x = *(const char *const *)a;`. Compare strlen first; if
equal, `return strcmp(x, y);`.
by_salary_desc: `const struct employee *x = a, *y = b;` and compare
y->salary against x->salary (swapped for descending).""")
ex("fnptr3", "12_function_pointers", "Write: map, count_if, reduce.", """
Define `static int square(int x)`, `static bool is_odd(int x)`,
`static int add(int a, int b)`, `static int max2(int a, int b)` above
main. map: `a[i] = f(a[i])`. count_if: count where `p(a[i])`. reduce:
`int acc = init; for (...) acc = f(acc, a[i]); return acc;`.""")
ex("fnptr4", "12_function_pointers", "Write: a dispatch table.", """
Four static functions, then `{"add", add}, {"sub", sub}, {"mul", mul},
{"div", div_}` in the table (drop the {NULL, NULL} row or keep it and
stop at it). run: loop over the table, `strcmp(commands[i].name, name)
== 0`, then `printf("%s %d %d = %d\\n", name, a, b, commands[i].run(a,
b));` and return. After the loop print the unknown-command line.""")
ex("fnptr5", "12_function_pointers", "Write: callbacks with a context pointer.", """
for_each: `for (size_t i = 0; i < n; i++) f(a[i], ctx);`.
accumulate: `struct stats *st = ctx;` then update sum, min, max.
print_indexed: `int *index = ctx; printf("[%d] %d\\n", *index, value);
(*index)++;`.""")

# ---------------------------------------------------------------- 13_data_structures
ex("list1", "13_data_structures", "Write: a linked list, push_front, print, free.", """
push_front: `struct node *n = malloc(sizeof *n); if (!n) return false;
n->value = value; n->next = *head; *head = n; return true;`.
print: "(empty)" for NULL; otherwise walk with `for (n = head; n; n =
n->next)` printing the value and " -> " when n->next is not NULL.
free_list: `while (head) { struct node *next = head->next; free(head);
head = next; }`.""")
ex("list2", "13_data_structures", "Write: push_back, length, contains, remove.", """
push_back: allocate the node with next = NULL, then walk `struct node
**pp = head; while (*pp) pp = &(*pp)->next; *pp = n;`.
remove_first: `struct node **pp = head; while (*pp && (*pp)->value !=
value) pp = &(*pp)->next; if (!*pp) return false; struct node *d = *pp;
*pp = d->next; free(d); return true;`.""")
ex("list3", "13_data_structures", "Write: reverse and insert_sorted.", """
reverse: `struct node *prev = NULL, *cur = head; while (cur) { struct
node *next = cur->next; cur->next = prev; prev = cur; cur = next; }
return prev;`.
insert_sorted: allocate n; `struct node **pp = head; while (*pp &&
(*pp)->value < value) pp = &(*pp)->next; n->next = *pp; *pp = n;`.""")
ex("stack1", "13_data_structures", "Write: a stack and bracket matching.", """
stack_push is memory2's push with chars. stack_pop: `if (s->len == 0)
return false; *out = s->items[--s->len]; return true;`.
balanced: for each char, push openers; for a closer, pop (fail if
empty) and check it is the matching opener; after the loop the stack
must be empty. Call stack_free before every return.""")
ex("queue1", "13_data_structures", "Write: a ring-buffer queue.", """
is_empty: count == 0. is_full: count == CAPACITY.
enqueue: `q->items[(q->head + q->count) % CAPACITY] = value; q->count++`.
dequeue: `*out = q->items[q->head]; q->head = (q->head + 1) % CAPACITY;
q->count--`.""")
ex("tree1", "13_data_structures", "Write: a binary search tree.", """
insert: `if (*root == NULL) { allocate, set value, children NULL, *root
= n; return true; }` then `if (value < (*root)->value) return
insert(&(*root)->left, value); if (value > ...) return insert(&(*root)->
right, value); return true;` (duplicate: nothing to do).
inorder: left, print, right. height: 0 for NULL, else 1 + max of the
children. tree_free: free children first, then the node.""")
ex("hashmap1", "13_data_structures", "Write: a chained hash map with string keys.", """
hash_string: `unsigned long h = 5381; for each char c: h = h * 33 +
(unsigned char)c;`.
A helper that returns `struct entry **` for a key makes everything
short: start at `&m->buckets[hash % BUCKETS]`, walk while the entry
exists and strcmp differs. put: if *pp exists update the value, else
allocate an entry and a copy of the key, link it at *pp, count++.
get: `*pp ? &(*pp)->value : NULL`. remove: unlink `*pp = e->next`, free
key and entry, count--. map_free: walk each bucket's list.""")

# ---------------------------------------------------------------- 14_preprocessor
ex("macros1", "14_preprocessor", "Fix: parenthesize macro arguments.", """
`#define SQUARE(x) ((x) * (x))`: parentheses around each use of x and
around the whole expansion.""")
ex("macros2", "14_preprocessor", "Fix: multi-statement macros and side effects.", """
SWAP: `#define SWAP(x, y) do { tmp = x; x = y; y = tmp; } while (0)`
(use backslashes to continue the line if you split it).
MAX: do the increment in its own statement before the macro call:
`i++; int m = MAX(i, 10);`.""")
ex("macros3", "14_preprocessor", "Write: stringify, ARRAY_LEN, CHECK.", """
`#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))`
`#define SHOW(e) printf(#e " = %d\\n", (e))`
`#define CHECK(c) do { if (c) printf("ok: " #c "\\n"); else
printf("FAIL: " #c "\\n"); } while (0)`""")
ex("macros4", "14_preprocessor", "Fix: an include guard in a header.", """
In shapes.h, put `#ifndef SHAPES_H` and `#define SHAPES_H` at the top
and `#endif` at the bottom (or `#pragma once` at the top). Save the
header, then press `r` in watch mode if it does not re-check by
itself.""", extra_sources=["draw.c", "draw.h", "shapes.h"])
ex("macros5", "14_preprocessor", "Fix: headers, extern and static linkage.", """
Add `#include "counter.h"`. `add_to_total` and `total` are static in
counter.c and cannot be reached from here. Reset through the interface:
`counter_bump(-counter_value());` (which also counts as a bump, hence
bumps: 3).""", extra_sources=["counter.c", "counter.h"])
ex("macros6", "14_preprocessor", "Write: conditional compilation and -D flags.", """
Top of file:
`#ifndef LOG_LEVEL / #define LOG_LEVEL 1 / #endif`, then
`#if LOG_LEVEL > 3 / #error "..." / #endif`.
Define log_info under `#if LOG_LEVEL >= 1` as a do/while(0) that
printfs "[info] " followed by __VA_ARGS__ and a newline, with an
`#else` branch `#define log_info(...) ((void)0)`. Same for log_debug at
level 2. Wrap the two color printfs in `#ifdef FEATURE_COLOR ...
#endif`.""", required_flags=["-DFEATURE_COLOR", "-DLOG_LEVEL=2"])

# ---------------------------------------------------------------- 15_io
ex("io1", "15_io", "Write: argc and argv.", args=["-v", "alpha", "beta", "gamma"], hint="""
`printf("%d arguments\\n", argc - 1);` then loop i from 1 to argc-1
printing "[%d] %s". `int first = 1; if (argc > 1 && strcmp(argv[1],
"-v") == 0) { print verbose on; first = 2; } else print off;` then loop
from `first` printing "positional: %s".""")
ex("io2", "15_io", "Write: stderr and exit codes.", args=["7", "6", "x", "5"], expected_exit=1, hint="""
Write a parse_int with strtol (see strings8). Loop over argv[1..]; on
success add to sum, otherwise `fprintf(stderr, "invalid number: %s\\n",
argv[i]); invalid++;`. Print the sum with printf and `return invalid;`.""")
ex("io3", "15_io", "Write: reading stdin with fgets.", stdin="the quick brown fox...\njumps over\n\nthe lazy dog\n", hint="""
`char line[256]; while (fgets(line, sizeof line, stdin))`: count the
line, add strlen(line) to chars (it includes the newline), count words
with the in_word state machine from strings9, then strip the newline
with `line[strcspn(line, "\\n")] = '\\0';` and compare strlen(line)
with the longest so far (strcpy it into a second buffer when longer).""")
ex("io4", "15_io", "Fix: scanf pitfalls.", stdin="Ada 36\nGrace 45\noops\nLinus 54\n", hint="""
Read lines with fgets into a `char line[128]`, then
`if (sscanf(line, "%15s %d", name, &age) == 2)` print; else strip the
newline and print "bad line: %s". The three bugs were the missing `&`,
the unchecked return value (a loop that never advances on bad input),
and `%s` without a width.""")
ex("io5", "15_io", "Write: writing and reading a file.", hint="""
write_numbers: `FILE *f = fopen(path, "w"); if (!f) return -1;` loop
`fprintf(f, "%d\\n", i);` then `fclose(f); return count;`.
sum_file: fopen with "r", return -1 if NULL; `while (fgets(line, sizeof
line, f)) sum += strtol(line, NULL, 10);` then fclose and return sum.""")
ex("io6", "15_io", "Write: errno, strerror and failing properly.", args=["/nonexistent/clings/input.txt"], expected_exit=1, hint="""
count_lines: fopen; on NULL `fprintf(stderr, "%s: %s\\n", path,
strerror(errno)); return -1;`. Otherwise count lines with fgets, fclose,
`*out = n; return 0;`.
main: print "counting lines in %s" with argv[1], call count_lines, and
`return EXIT_FAILURE;` when it fails; otherwise print the count and
return EXIT_SUCCESS.""")

# ---------------------------------------------------------------- 16_undefined_behavior
ex("ub1", "16_undefined_behavior", "Fix: uninitialized variables.", required_flags=["-ftrivial-auto-var-init=pattern"], hint="""
`int total = 0;` and `int largest = values[0];` (or INT_MIN from
<limits.h>).""")
ex("ub2", "16_undefined_behavior", "Fix: signed integer overflow.", """
Make factorial return `unsigned long long` and compute in that type.
Before `result *= i`, check `if (result > ULLONG_MAX / i) return 0;`.
Update the printf formats in main to %llu.""")
ex("ub3", "16_undefined_behavior", "Fix: sequence points and division.", """
`i = i + 1;` (or just `i++;`). In the loop: `a[k] = k; k++;` as two
statements. safe_div: `if (b == 0 || (a == INT_MIN && b == -1)) return
0;` before dividing.""")
ex("ub4", "16_undefined_behavior", "Fix: misaligned access and type punning.", """
read_u32_at: `uint32_t v; memcpy(&v, buf + offset, sizeof v); return v;`.
read_u16_be: `((unsigned)buf[offset] << 8) | buf[offset + 1]`, cast to
uint16_t.""")
ex("ub5", "16_undefined_behavior", "Fix: five classic bugs in one file.", """
1. `i < 5` in squares. 2. Move `free(v)` after the printf. 3. Return
UINT32_MAX when bits >= 32. 4. `malloc(strlen(src) + 1)`. 5. `return s
== NULL ? 0 : strlen(s);`.""")

# ---------------------------------------------------------------- 17_projects
ex("project1", "17_projects", "Project: word frequency counter.",
   stdin="The quick brown fox jumps over the lazy dog.\nThe dog sleeps; the FOX does not!\n",
   args=["5"], hint="""
Read lines with fgets. For each line keep a `const char *cursor` and
call a next_word function that skips non-alnum characters, copies
alnum characters lower-cased into a buffer, and stops. Bump the word in
a growable array of {char *word; int count;}: linear search with
strcmp, append a malloc'd copy with count 1 if not found. After the
input: qsort with a comparator that orders by count descending, then
strcmp. Print the first N and the distinct count. Free every word and
the array.""")
ex("project2", "17_projects", "Project: a string builder with appendf.", """
strbuf_reserve(sb, extra): needed = len + extra + 1; if needed > cap,
double cap (starting at 16) until it fits, realloc, and if the buffer
was empty before, write data[0] = '\\0'.
append: reserve(strlen(text)), memcpy including the terminator, len +=
n. appendf: va_start; n = vsnprintf(NULL, 0, fmt, args); va_end;
reserve(n); va_start again; vsnprintf(data + len, n + 1, fmt, args);
va_end; len += n. clear: len = 0 and data[0] = '\\0' if data exists.
free: free(data) and re-init.""")
ex("project3", "17_projects", "Project: an RPN calculator.",
   stdin="3 4 +\n5 1 2 + 4 * + 3 -\n5 2 /\n1 +\n1 0 /\n1 x +\n1 2\n\n2 5 -\n",
   expected_exit=1, hint="""
Tokenize each line with strtok(line, " \\t\\n"). Try strtod first
(valid when end != tok and *end == '\\0'); push. Otherwise the token
must be exactly one of + - * /; pop b then a (underflow if either pop
fails), compute (division by zero check), push. After the loop: no
tokens -> "empty"; more than one value -> "too many values"; otherwise
the single value is the result, printed with %g. Count failures and
return 1 if any. For "unknown token" you need the token text: either
copy it into a small buffer before the strtok state moves on, or keep an
untouched copy of the line.""")
ex("project4", "17_projects", "Project: a tiny records database.",
   stdin="ada,eng,105000\nbo,sales,70000\n\ngrace,eng,120000\nbad line\nlinus,eng,98000\nmei,sales,82000\n",
   args=["sort", "salary", "filter", "eng", "print", "total"], hint="""
db_add_line: strip the newline, strtok three fields on ",", reject if
any is missing or a fourth exists, strtol the salary with end checks,
duplicate name and dept with malloc+memcpy, push the record (growable
array as in memory2).
db_filter: walk the rows, copying kept rows down to index `kept` and
freeing the others; set len = kept.
Comparators: by_name is strcmp on names; by_dept compares dept then
name; by_salary orders descending then by name. A small table
{field, comparator} picks the one named in argv.
main: read stdin (skip lines that are only whitespace, report others
that fail to parse to stderr), then walk argv: "sort" and "filter"
consume the next argument; "print" uses `printf("%-8s %-12s %7ld\\n",
...)`; "total" sums salaries. Free everything at the end.""")
