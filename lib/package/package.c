#include "package/package.h"

Payload *__payload_new(size_t size, char *data, bool take_ownership) {
	Payload *payload = malloc(sizeof(Payload));
	payload->size = size;
	if (take_ownership) {
		payload->data = malloc(size);
		memcpy(payload->data, data, size);
	} else {
		payload->data = data;
	}
	return payload;
}

Payload *payload_new(size_t size, char *data) {
	return __payload_new(size, data, true);
}

Payload *encode_int(int value) {
	char *data = malloc(sizeof(char) * sizeof(int));
	for (int i = 0; i < sizeof(int); i++) {
		data[i] = (value >> (i * 8)) & 0xFF;
	}
	return __payload_new(sizeof(int), data, false);
}

Payload *encode_string(char *string) {
	size_t size = strlen(string) + 1;
	char *data = malloc(size);
	memcpy(data, string, size);
	return __payload_new(size, data, false);
}

int decode_int(Payload *payload) {
	int value = 0;
	for (int i = 0; i < sizeof(int); i++) {
		value |= (payload->data[i] & 0xFF) << (i * 8);
	}
	return value;
}

char *decode_string(Payload *payload) {
	size_t size = payload->size;
	char *data = malloc(size);
	memcpy(data, payload->data, size);
	return data;
}

void payload_free(Payload *payload) {
	free(payload->data);
	free(payload);
}
