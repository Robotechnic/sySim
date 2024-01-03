# sySim

- [sySim](#sysim)
	- [Command line interface](#command-line-interface)
		- [Simulation parameters](#simulation-parameters)
		- [Logging parameters](#logging-parameters)
		- [Message checking](#message-checking)
		- [Visualization](#visualization)
		- [Configuration file](#configuration-file)
	- [How to add a new protocol](#how-to-add-a-new-protocol)
	- [API reference](#api-reference)
		- [Software Interface](#software-interface)
		- [Simulator Interface](#simulator-interface)
		- [Package Interface](#package-interface)
		- [Queue Interface](#queue-interface)

## Command line interface

### Simulation parameters

| name | short name | description | type | default |
| :--: | :--------: | :---------: | :--: | :-----: |
| messages | m | Number of messages to send | int | 10 |
| loss | l | Packet loss probability | float | 0.0 |
| corruption | c | Packet corruption probability | float | 0.0 |
| delay | d | Average delay between packets" | float | 5.0 |
| maxTime | t | Maximum time to run the simulation | float | 200.0 |
| seed | s | Seed for the random number generator | int | 42 |
| bidirectional | b | If set, the channel will be bidirectional | flag | off

### Logging parameters

| name | short name | description | type | default |
| :--: | :--------: | :---------: | :--: | :-----: |
| loglevel | L | Logging level | int | 2
| logfile | - | If set, the logging will also be written to this file | string |
| quiet | q | If set, the program won't print anything to stdout | flag | off
| color | k | If set, the program will use colors in the output | flag | off

### Message checking

| name | short name | description | type | default |
| :--: | :--------: | :---------: | :--: | :-----: |
| check | - | If set, the simulator will check that the payloads are received in the correct order | flag | off
| ignore | f | If set, the simulator will continue even if the messages are not received in the correct order" | flag | off

### Visualization

> [!INFO]
> Not yet implemented

| name | short name | description | type | default |
| :--: | :--------: | :---------: | :--: | :-----: |
| visualize | v | If set, the simulator will export an svg file with the visualization of the simulation | string |

### Configuration file

| name | short name | description | type | default |
| :--: | :--------: | :---------: | :--: | :-----: |
| conf | C | If set, the simulator will read the configuration from this file | string |

## How to add a new protocol

You just need to create a new file in the [protocols](protocols) folder and run `cmake` again to regenerate the build files.

## API reference

### Software Interface

The simulator provides some functions to alow the protocols to send messages and interact with the simulator.

---

```c
void starttimer(double increment);
```

Starts a timer that will call the `timeout` function after `increment` seconds for the current side.

---

```c
void stoptimer(void);
```

Stops the timer for the current side.

---

```c
void tolayer3(Packet *packet);
```

Sends a packet to the other side of the channel. The packet may be lost or corrupted depending on the simulation parameters.

---

```c
void tolayer5(const Payload *message);
```

Sends a message to the application layer. You must call this function when you receive a message from the other side of the channel. This function is responsible for checking that the messages are correct and in order.

### Simulator Interface

The protocol must implement the following functions:

---

```c
void *A_init();
void *B_init();
```

These functions are called when the simulation starts. It returns the state of the protocol. You can use this state to store any information you need.

---

```c
void A_send(void *state, Payload payload);
void B_send(void *state, Payload payload);
```

These functions are called when the application layer wants to send a message. You must send the message to the other side of the channel but not necessarily immediately.

---

```c
void A_recv(void *state, const Packet *packet);
void B_recv(void *state, const Packet *packet);
```

These functions are called when a packet is received from the other side of the channel.

---

```c
void A_timeout(void *state);
void B_timeout(void *state);
```

These functions are called when the timer expires. If you want to restart the timer you must call `starttimer` again.

---

```c
void A_free(void *state);
void B_free(void *state);
```

These functions are called when the simulation ends. You must free the memory allocated for the state of the protocol.

### Package Interface

This provides you an interface to create and manage packages. This interface is mainly created by this macro:

---

```c
DEFINE_PACKET(name, fields...)
```

This macro creates a struct with the given name and fields. It also creates the following functions:

---

```c
name *name_new(const Payload *payload);
```

Creates a new package with the given payload. It does initialise all the other fields to 0, so you must set them manually afterwards.

---

```c
Packet *name_dup(const name *packet);https://www.thingiverse.com/
```

Creates a copy of the given package including the custom fields.

Then, you can manipulate the packages as normal structs.

---

```c
Payload payload_new(const char data[PAYLOAD_SIZE]);
```

Creates a new payload with the given data.

The following functions are provided to encode and decode integers into payloads. They aren't currently used by the simulator but they may be useful.

---

```c
Payload encode_int(int value);
```

Encodes an integer into a payload. The integer will be encoded in big endian.

---

```c
int decode_int(const Payload *payload);
```

Decodes an integer from a payload. The integer must be encoded in big endian.

### Queue Interface

This simulator provides you a queue implementation. You can use it to store whatever you want.

> [!CAUTION]
> The queue is implemented in a way that it doesn't take ownership of the elements, it won't free them when they are removed from the queue or when the queue is destroyed so you need to take care of that.

---

```c
Queue *queue_new(size_t size);
```

Creates a new queue with preallocated space for `size` elements.

---

```c
void queue_push(Queue *queue, void *element);
```

Pushes an element to the queue.

---

```c
void *queue_pop(Queue *queue);
```

Pops an element from the queue.

---

```c
void *queue_peek(Queue *queue);
```

Returns the first element of the queue without removing it.

> [!NOTE]
> This mean that the queue keep the pointer to the element so you must not free it until you remove it from the queue.

---

```c
void *queue_back(Queue *queue);
```

Returns the last inserted element of the queue without removing it.

> [!NOTE]
> This mean that the queue keep the pointer to the element so you must not free it until you remove it from the queue.

---

```c
size_t queue_size(Queue *queue);
```

Returns the number of elements in the queue.

---

```c
bool queue_empty(Queue *queue);
```

Returns true if the queue is empty.

---

```c
void queue_free(Queue *queue, queue_free_fn free_fn);
```

Frees the memory allocated for the queue. If `free_fn` is not NULL, it will be called for each element in the queue.
