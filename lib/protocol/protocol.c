#include "protocol/protocol.h"

char sendto_to_char(sendto sdt) {
	switch (sdt) {
	case A:
		return 'A';
	case B:
		return 'B';
	default:
		return 'X';
	}
}