#include "protocol/protocol.h"

char sendto_to_char(side sdt) {
	switch (sdt) {
	case A:
		return 'A';
	case B:
		return 'B';
	default:
		return 'X';
	}
}