// counter.h - public interface of counter.c

#ifndef COUNTER_H
#define COUNTER_H

// Number of times counter_bump was called. Defined in counter.c.
extern int bump_count;

void counter_bump(int amount);
int counter_value(void);

#endif
