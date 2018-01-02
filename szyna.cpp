#include "stdafx.h"

SC_MODULE(szyna) {

	sc_fifo<int> avalon;

	SC_CTOR(szyna) {
		sc_fifo<int> avalon(7);
	}

};
