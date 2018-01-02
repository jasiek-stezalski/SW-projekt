#include "stdafx.h"
#include "nasz_modul.cpp"

SC_MODULE(procesor1) {

	sc_port<sc_fifo_in_if<int> > slider;
	sc_inout<sc_uint<16>> state;
	sc_out<sc_uint<16>> modul_out;
	nasz_modul modul;
	int old_state = 0;
	int new_state = 0;

	void task1() {
		while (1) {
			// Odczyt slidera
			new_state = slider->read();

			// Wybor podopcji
			if ((old_state == 1 && (new_state == 10 || new_state == 11)) 
				|| (old_state == 4 && (new_state == 12 || new_state == 13 || new_state == 14 || new_state == 15))) {
				old_state = new_state;
			}
			// Cofniêcie z podopcji do opcji 1
			else if ((old_state == 10 || old_state == 11) && new_state == 0) {
				old_state = 1;
			}
			// Cofniecie z podopcji do opcji 4
			else if ((old_state == 12 || old_state == 13 || old_state == 14 || old_state == 15) && new_state == 0) {
				old_state = 4;
			}
			// Obsluga bledow
			else if (old_state != 0 && new_state == old_state) {
				cout << "Error - Ten slider jest juz wlaczony" << endl;
			}
			else if (new_state != 0 && old_state != 0 ) {
				cout << "Error - Juz inny slider jest wlaczony" << endl;
			}
			// Cofniecie do glownego menu
			else if (new_state == 0 || new_state > 7) {
				old_state = 0;
				system("cls");
				cout << "Wybor trybu pracy sprzetu HIFI \n\n";
				cout << "Dostepne opcje: \n1.Radio \n2.Kaseta \n3.Gramofon \n4.Plyta \n5.DVD Film \n6.AUX \n7.Ustawienia \n0.Cofnij \n" << endl;
			}
			// Poprawny wybor slidera
			else if (new_state != 0 && old_state == 0) {
				old_state = new_state;
			}
			state.write(old_state);
			modul_out.write(0);
		}
	}

	void task2() {
		if (state.read() == 1) {
			system("cls");
			cout << "Radio" << endl;
			cout << "\nWybor zakresu fali, dostepne opcje:" << endl;
			cout << "10.AM \n11.FM \n0.Cofnij \n";
		}
		else if (state.read() == 10) {
			cout << "Radio : AM" << endl;
		}
		else if (state.read() == 11) {
			cout << "Radio : FM" << endl;
		}
	}

	void task3() {
		if (state.read() == 2) {
			cout << "Kaseta" << endl;
		}
	}

	void task4() {
		if (state.read() == 3) {
			cout << "Gramofon" << endl;
		}
	}

	void task5() {
		if (state.read() == 4) {
			system("cls");
			cout << "Plyta" << endl;
			cout << "\nWybor rodzaju plyty, dostepne opcje: " << endl;
			cout << "12.CD Audio \n13.CD MP3 \n14.DVD Audio \n15.DVD MP3 \n0.Cofnij \n";
		}
		else if (state.read() == 12) {
			cout << "Plyta : CD Audio" << endl;
		}
		else if (state.read() == 13) {
			cout << "Plyta : CD MP3" << endl;
		}
		else if (state.read() == 14) {
			cout << "Plyta : DVD Audio" << endl;
		}
		else if (state.read() == 15) {
			cout << "Plyta : DVD MP3" << endl;
		}
	}

// Task obslugiwany przez nasz modul sprzetowy
	void task6() {
		if (state.read() == 5) {
			modul_out.write(5);
		}
	}

	void task7() {
		if (state.read() == 6) {
			cout << "AUX" << endl;
		}
	}

	SC_CTOR(procesor1) : modul("nasz_modul") {
		modul.modul_in(modul_out);

		SC_THREAD(task1);
		SC_METHOD(task2);
		sensitive << state;
		SC_METHOD(task3);
		sensitive << state;
		SC_METHOD(task4);
		sensitive << state;
		SC_METHOD(task5);
		sensitive << state;
		SC_METHOD(task6);
		sensitive << state;
		SC_METHOD(task7);
		sensitive << state;
	}
};