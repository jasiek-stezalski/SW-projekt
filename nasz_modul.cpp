#include "stdafx.h"

SC_MODULE(nasz_modul) {

	sc_in<sc_uint<16>> modul_in;

	void task6() {
		if (modul_in.read() == 5) {
			cout << "Modul sprzetowy:\n";
			cout << "DVD Film" << endl;
		}
	}

	SC_CTOR(nasz_modul) {
		SC_METHOD(task6);
		sensitive << modul_in;
	}
};