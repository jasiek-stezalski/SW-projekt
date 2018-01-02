#include "stdafx.h"
#include "slider.cpp"
#include "szyna.cpp"
#include "procesor1.cpp"
#include "procesor2.cpp"

int sc_main(int argc, char* argv[]) {
	sc_signal<sc_uint<16>, SC_MANY_WRITERS> state;
	sc_signal<sc_uint<16>, SC_MANY_WRITERS> nasz_modul;
	szyna szyna("szyna");

	system("cls");
	cout << "Wybor trybu pracy sprzetu HIFI \n\n";
	cout << "Dostepne opcje: \n1.Radio \n2.Kaseta \n3.Gramofon \n4.Plyta \n5.DVD Film \n6.AUX \n7.Ustawienia \n0.Cofnij \n"<< endl;

	slider s("s");
	procesor1 p1("p1");
	procesor2 p2("p2");

	s.out(szyna.avalon);
	p1.slider(szyna.avalon); 
	p1.state(state); 
	p2.state(state);

	p1.modul_out(nasz_modul);

	sc_start(); 

	return 0;

}