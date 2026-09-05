// project4.c - solution

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

static char *dup_string(const char *s)
{
    size_t n = strlen(s) + 1;
    char *copy = malloc(n);

    if (copy != NULL) {
        memcpy(copy, s, n);
    }
    return copy;
}

static void record_free(struct record *r)
{
    free(r->name);
    free(r->dept);
    r->name = NULL;
    r->dept = NULL;
}

static bool db_push(struct db *db, struct record r)
{
    if (db->len == db->cap) {
        size_t new_cap = db->cap == 0 ? 8 : db->cap * 2;
        struct record *bigger = realloc(db->rows, new_cap * sizeof *bigger);
        if (bigger == NULL) {
            return false;
        }
        db->rows = bigger;
        db->cap = new_cap;
    }
    db->rows[db->len++] = r;
    return true;
}

// Parses "name,dept,salary". Modifies line. Returns false if malformed.
static bool db_add_line(struct db *db, char *line)
{
    line[strcspn(line, "\n")] = '\0';
    char *name = strtok(line, ",");
    char *dept = strtok(NULL, ",");
    char *salary_text = strtok(NULL, ",");
    if (name == NULL || dept == NULL || salary_text == NULL || strtok(NULL, ",") != NULL) {
        return false;
    }
    char *end;
    long salary = strtol(salary_text, &end, 10);
    if (end == salary_text || *end != '\0' || salary < 0) {
        return false;
    }
    struct record r = {dup_string(name), dup_string(dept), salary};
    if (r.name == NULL || r.dept == NULL || !db_push(db, r)) {
        record_free(&r);
        return false;
    }
    return true;
}

static void db_filter(struct db *db, const char *dept)
{
    size_t kept = 0;

    for (size_t i = 0; i < db->len; i++) {
        if (strcmp(db->rows[i].dept, dept) == 0) {
            db->rows[kept++] = db->rows[i];
        } else {
            record_free(&db->rows[i]);
        }
    }
    db->len = kept;
}

static void db_free(struct db *db)
{
    for (size_t i = 0; i < db->len; i++) {
        record_free(&db->rows[i]);
    }
    free(db->rows);
    db->rows = NULL;
    db->len = 0;
    db->cap = 0;
}

static int by_name(const void *a, const void *b)
{
    return strcmp(((const struct record *)a)->name, ((const struct record *)b)->name);
}

static int by_dept(const void *a, const void *b)
{
    int c = strcmp(((const struct record *)a)->dept, ((const struct record *)b)->dept);
    return c != 0 ? c : by_name(a, b);
}

static int by_salary(const void *a, const void *b)
{
    long x = ((const struct record *)a)->salary;
    long y = ((const struct record *)b)->salary;
    if (x != y) {
        return x > y ? -1 : 1;
    }
    return by_name(a, b);
}

static const struct {
    const char *field;
    int (*compare)(const void *, const void *);
} sort_keys[] = {
    {"name", by_name},
    {"dept", by_dept},
    {"salary", by_salary},
};

static bool db_sort(struct db *db, const char *field)
{
    for (size_t i = 0; i < sizeof sort_keys / sizeof sort_keys[0]; i++) {
        if (strcmp(sort_keys[i].field, field) == 0) {
            qsort(db->rows, db->len, sizeof db->rows[0], sort_keys[i].compare);
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    struct db db = {NULL, 0, 0};
    char line[256];
    int status = 0;

    while (fgets(line, sizeof line, stdin) != NULL) {
        if (line[strspn(line, " \t\n")] == '\0') {
            continue;
        }
        char copy[256];
        strcpy(copy, line);
        if (!db_add_line(&db, line)) {
            copy[strcspn(copy, "\n")] = '\0';
            fprintf(stderr, "malformed record: %s\n", copy);
        }
    }

    for (int i = 1; i < argc; i++) {
        const char *cmd = argv[i];
        if (strcmp(cmd, "sort") == 0 && i + 1 < argc) {
            if (!db_sort(&db, argv[++i])) {
                fprintf(stderr, "unknown sort field: %s\n", argv[i]);
                status = 2;
            }
        } else if (strcmp(cmd, "filter") == 0 && i + 1 < argc) {
            db_filter(&db, argv[++i]);
        } else if (strcmp(cmd, "print") == 0) {
            for (size_t r = 0; r < db.len; r++) {
                printf("%-8s %-12s %7ld\n", db.rows[r].name, db.rows[r].dept, db.rows[r].salary);
            }
        } else if (strcmp(cmd, "total") == 0) {
            long total = 0;
            for (size_t r = 0; r < db.len; r++) {
                total += db.rows[r].salary;
            }
            printf("total: %ld\n", total);
        } else {
            fprintf(stderr, "unknown command: %s\n", cmd);
            status = 2;
        }
    }

    db_free(&db);
    return status;
}
