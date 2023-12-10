#ifndef PACKAGE_H
#define PACKAGE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEFINE_PACKAGE(name, fields)                                                               \
    struct name##_t {                                                                              \
        int id;                                                                                    \
        Payload *payload;                                                                          \
        struct fields;                                                                             \
    };                                                                                             \
    typedef struct name##_t name;

typedef struct payload_t {
    size_t size;
    char *data;
} Payload;

struct package_t {
    int id;
    Payload *payload;
};

typedef struct package_t Package;

Package *package_new(int id, Payload *payload);
void package_free(Package *package);

Payload *payload_new(size_t size, char *data);
Payload *encode_int(int value);
Payload *encode_string(char *value);

char *decode_string(Payload *payload);
int decode_int(Payload *payload);

void payload_free(Payload *payload);

#endif // PACKAGE_H