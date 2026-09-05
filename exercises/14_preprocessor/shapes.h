// shapes.h
//
// A header declares things for other files to use: struct definitions,
// prototypes, constants. It must be safe to include more than once,
// because headers include other headers and the same one can arrive
// twice through different routes. This one is not safe yet: the second
// inclusion redefines `struct rect`, which is an error.
//
// TODO: add an include guard.

struct rect {
    int width;
    int height;
};

int rect_area(struct rect r);
