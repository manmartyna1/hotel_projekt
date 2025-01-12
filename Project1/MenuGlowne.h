#ifndef MENUGLOWNE_H
#define MENUGLOWNE_H

#include "Klasy.h"
#include <string>

class MenuGlowne {
private:
    ZarzadzanieRezerwacjami& zarzadzanie;
    StanDostepnosci& stanDostepnosci;

    std::string ukryjHaslo();
    bool czyPokojZajety(int numerPokoju, const std::string& dataPrzyjazdu, const std::string& dataOdjazdu);

public:
    MenuGlowne(ZarzadzanieRezerwacjami& zarz, StanDostepnosci& stan);

    void wyswietlEkranPoczatkowy();
    void wyswietlMenu();
    void zalogujAdministratora();
    void zalogujGoscia();
    void noweOknoZakladaniaKonta();
    void zalozKonto();
    void zlozRezerwacje();
    void sprawdzDostepnosc();
    void odwolajRezerwacje();
    void menuGoscia();
    void wybierzOpcje();
};

#endif // MENUGLOWNE_H
