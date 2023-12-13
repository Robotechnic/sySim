#ifndef PACKAGE_H
#define PACKAGE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PAYLOAD_SIZE 20

#define DEFINE_PACKET(name, fields)                                                                \
    struct name##_t {                                                                              \
        size_t size;                                                                               \
        Payload payload;                                                                           \
        fields                                                                                     \
    };                                                                                             \
    typedef struct name##_t name;                                                                  \
    name *name##_new(const Payload *payload) {                                                     \
        name *package = malloc(sizeof(name));                                                      \
        package->size = sizeof(name);                                                              \
        memcpy(&package->payload, payload, sizeof(Payload));                                       \
        return package;                                                                            \
    }                                                                                              \
    Packet *name##_dup(const name *packet) {                                                       \
        name *dup_packet = malloc(sizeof(name));                                                   \
        memcpy(dup_packet, packet, sizeof(name));                                                  \
        return (Packet *)dup_packet;                                                               \
    }

typedef struct payload_t {
    char data[PAYLOAD_SIZE];
} Payload;

struct packet_t {
    size_t size;
    Payload payload;
};

typedef struct packet_t Packet;

Packet *package_new(int id, Payload *payload);
void package_free(Packet *package);

Payload payload_new(const char data[PAYLOAD_SIZE]);
Payload encode_int(int value);
Payload enpty_payload();

int decode_int(const Payload *payload);

void payload_free(Payload *payload);

#endif // PACKAGE_H