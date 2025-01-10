// Poprawiony kod pliku main.cpp
#include "MenuGlowne.h"
#include "Klasy.h"

int main() {
    ZarzadzanieRezerwacjami zarzadzanie;
    StanDostepnosci stanDostepnosci;
    MenuGlowne menu(zarzadzanie, stanDostepnosci);

    menu.wybierzOpcje();
    return 0;
}
