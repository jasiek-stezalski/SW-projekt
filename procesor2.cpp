#include "stdafx.h"

SC_MODULE(procesor2) {

	sc_inout<sc_uint<16>> state;

	void task8() {
		if (state.read() == 7) {
			cout << "Procesor nr 2: \n";
			cout << "Ustawienie poziomu glosnosci" << endl;
		}
	}

	SC_CTOR(procesor2) {
		SC_METHOD(task8);
		sensitive << state;
	}
};