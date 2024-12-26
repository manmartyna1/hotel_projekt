#ifndef MENUGLOWNE_H
#define MENUGLOWNE_H

#include "Klasy.h" // Do³¹czamy pe³n¹ definicjê ZarzadzanieRezerwacjami

class MenuGlowne {
private:
    ZarzadzanieRezerwacjami& zarzadzanie; // Referencja do ZarzadzanieRezerwacjami

public:
    MenuGlowne(ZarzadzanieRezerwacjami& zarz); // Konstruktor

    void wyswietlMenu();
    void zalogujAdministratora();
    void zalogujGoscia();
    void noweOknoZakladaniaKonta();
    void zalozKonto();
    void wybierzPokoj(); // Deklaracja metody wybierzPokoj
    void wybierzOpcje();
};

#endif // MENUGLOWNE_H
