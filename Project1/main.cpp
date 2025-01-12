#include "MenuGlowne.h"
#include "Klasy.h"

int main() {
    ZarzadzanieRezerwacjami zarzadzanie;
    StanDostepnosci stan;

    MenuGlowne menu(zarzadzanie, stan);
    menu.wybierzOpcje();

    return 0;
}
