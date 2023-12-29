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

/**
 * @brief Create a new Payload object with the given data
 *
 * @param data the data to be copied to the payload
 * @return Payload the new payload
 */
Payload payload_new(const char data[PAYLOAD_SIZE]);

/**
 * @brief Encode an integer into a payload
 *
 * @param value the integer to be encoded
 * @return Payload the encoded payload
 */
Payload encode_int(int value);

/**
 * @brief Create an empty payload
 *
 * @return Payload the empty payload
 */
Payload enpty_payload();

/**
 * @brief Decode an integer from a payload
 *
 * @param payload the payload to be decoded
 * @return int the decoded integer
 */
int decode_int(const Payload *payload);

#endif // PACKAGE_H