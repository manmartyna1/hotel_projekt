#include "MenuGlowne.h"
#include <iostream>

void MenuGlowne::wyswietlMenu() {
    std::cout << "========== MENU GLOWNE ==========" << std::endl;
    std::cout << "1. Zarzadzanie rezerwacjami" << std::endl;
    std::cout << "2. Zarzadzanie pokojami" << std::endl;
    std::cout << "3. Wyjscie" << std::endl;
}

void MenuGlowne::wybierzOpcje() {
    int wybor;
    do {
        wyswietlMenu();
        std::cout << "Wybierz opcje: ";
        std::cin >> wybor;

        switch (wybor) {
        case 1:
            std::cout << "Wybrano Zarzadzanie rezerwacjami!" << std::endl;
            break;
        case 2:
            std::cout << "Wybrano Zarzadzanie pokojami!" << std::endl;
            break;
        case 3:
            std::cout << "Wyjscie z programu." << std::endl;
            break;
        default:
            std::cout << "Nieprawid³owa opcja, sprobuj ponownie!" << std::endl;
        }
    } while (wybor != 3);
}



