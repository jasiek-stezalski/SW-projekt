#include "stdafx.h"


SC_MODULE(slider) {
	sc_fifo_out<int> out;

	void read() {
		int val = 0;
		while (1)
		{
			wait(10, SC_NS);
			cin >> val;
			out.write(val);
		}
	}

	SC_CTOR(slider)
	{
		SC_THREAD(read);
	}

};