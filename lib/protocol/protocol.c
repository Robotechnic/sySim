#include "protocol/protocol.h"

char side_to_char(side sdt) {
	switch (sdt) {
	case A:
		return 'A';
	case B:
		return 'B';
	default:
		return 'X';
	}
}