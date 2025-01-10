#ifndef MENUGLOWNE_H
#define MENUGLOWNE_H

#include "Klasy.h"

class MenuGlowne {
private:
    ZarzadzanieRezerwacjami& zarzadzanie; // Referencja do ZarzadzanieRezerwacjami
    StanDostepnosci& stanDostepnosci; // Referencja do StanDostepnosci

public:
    MenuGlowne(ZarzadzanieRezerwacjami& zarz, StanDostepnosci& stan); // Konstruktor

    void wyswietlEkranPoczatkowy(); // Nowa funkcja do ekranu powitalnego
    void wyswietlMenu();
    void zalogujAdministratora();
    void zalogujGoscia();
    void noweOknoZakladaniaKonta();
    void zalozKonto();
    void zlozRezerwacje();
    void odwolajRezerwacje();
    void menuGoscia();
    void wybierzOpcje();
};

#endif // MENUGLOWNE_H
