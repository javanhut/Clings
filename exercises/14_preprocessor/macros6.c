// macros6.c
//
// CONCEPT
// *Conditional compilation* includes or excludes code at preprocessing
// time:
//
//     #ifdef NAME  /  #ifndef NAME       is NAME defined (at all)?
//     #if EXPR                           integer constant expression;
//                                        undefined names count as 0
//     #if defined(A) && !defined(B)      combinations
//     #elif / #else / #endif
//     #error "message"                   abort compilation with a message
//
// Names can be defined in the file (`#define FEATURE_COLOR 1`) or from
// the compiler command line: `-DFEATURE_COLOR` (defines it as 1) or
// `-DLOG_LEVEL=2`. That is how build systems select features, platforms
// and debug/release variants. The compiler predefines some: `__linux__`,
// `__APPLE__`, `_WIN32`, `__GNUC__`, `__STDC_VERSION__`.
//
// A common structure is a "config" block at the top that fills in
// defaults for anything the build did not specify:
//     #ifndef LOG_LEVEL
//     #define LOG_LEVEL 1
//     #endif
//
// WHEN YOU USE THIS
// Portability (different code per OS), optional features, debug-only
// checks and logging that compile to nothing in release builds, and
// `#error` to fail early when a required option is missing.
//
// TASK
// Clings compiles this file with -DFEATURE_COLOR and -DLOG_LEVEL=2.
// Write the preprocessor logic so that:
//   - LOG_LEVEL defaults to 1 when not given on the command line,
//   - `log_info` lines are printed only when LOG_LEVEL >= 1, and
//     `log_debug` lines only when LOG_LEVEL >= 2, and when they are not
//     printed the calls compile to nothing at all (no function call),
//   - the greeting is wrapped in "[color]" markers only when
//     FEATURE_COLOR is defined,
//   - compiling with LOG_LEVEL above 3 fails with #error.
//
// EXPECTED OUTPUT
//     [info] starting
//     [debug] log level is 2
//     [color]Hello[/color]
//     [info] done

#include <stdio.h>

// TODO: default LOG_LEVEL, #error check, log_info / log_debug macros

int main(void)
{
    log_info("starting");
    log_debug("log level is %d", LOG_LEVEL);

    // TODO: only with FEATURE_COLOR
    printf("[color]");
    printf("Hello");
    printf("[/color]");
    printf("\n");

    log_info("done");
    return 0;
}
