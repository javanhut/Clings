// macros6.c - solution

#include <stdio.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL 1
#endif

#if LOG_LEVEL > 3
#error "LOG_LEVEL must be between 0 and 3"
#endif

#if LOG_LEVEL >= 1
#define log_info(...)                   \
    do {                                \
        printf("[info] " __VA_ARGS__);  \
        printf("\n");                   \
    } while (0)
#else
#define log_info(...) ((void)0)
#endif

#if LOG_LEVEL >= 2
#define log_debug(...)                  \
    do {                                \
        printf("[debug] " __VA_ARGS__); \
        printf("\n");                   \
    } while (0)
#else
#define log_debug(...) ((void)0)
#endif

int main(void)
{
    log_info("starting");
    log_debug("log level is %d", LOG_LEVEL);

#ifdef FEATURE_COLOR
    printf("[color]");
#endif
    printf("Hello");
#ifdef FEATURE_COLOR
    printf("[/color]");
#endif
    printf("\n");

    log_info("done");
    return 0;
}
