#include "MenuGlowne.h"
#include "Klasy.h"

int main() {
    ZarzadzanieRezerwacjami zarzadzanie;
    MenuGlowne menu(zarzadzanie);
    menu.wybierzOpcje();
    return 0;
}
