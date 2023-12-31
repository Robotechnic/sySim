#include "package/package.h"

Payload payload_new(const char data[PAYLOAD_SIZE]) {
    Payload payload;
    memcpy(payload.data, data, PAYLOAD_SIZE);
    return payload;
}

Payload encode_int(int value) {
    char data[PAYLOAD_SIZE];
    for (int i = 0; i < sizeof(int); i++) {
        data[i] = (value >> (i * 8)) & 0xFF;
    }
    return payload_new(data);
}

Payload enpty_payload() {
    char data[20] = {0};
    return payload_new(data);
}

int decode_int(const Payload *payload) {
    int value = 0;
    for (int i = 0; i < sizeof(int); i++) {
        value |= (payload->data[i] & 0xFF) << (i * 8);
    }
    return value;
}
