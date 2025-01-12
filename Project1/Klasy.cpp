#include "Klasy.h"
#include <fstream>
#include <iostream>

Pokoj::Pokoj(int numer, bool zajety) : numer(numer), zajety(zajety) {}

StanDostepnosci::StanDostepnosci() {
    for (int i = 1; i <= 100; ++i) {
        pokoje.push_back(Pokoj(i));
    }
}

bool StanDostepnosci::sprawdzDostepnosc(int numerPokoju) {
    for (const auto& pokoj : pokoje) {
        if (pokoj.numer == numerPokoju) {
            return !pokoj.zajety;
        }
    }
    return false;
}

void StanDostepnosci::oznaczPokoj(int numerPokoju, bool zajety) {
    for (auto& pokoj : pokoje) {
        if (pokoj.numer == numerPokoju) {
            pokoj.zajety = zajety;
            return;
        }
    }
}

void StanDostepnosci::zapiszDostepnoscDoPliku(const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku, std::ios::trunc);
    if (plik.is_open()) {
        for (const auto& pokoj : pokoje) {
            plik << pokoj.numer << " " << (pokoj.zajety ? "zajety" : "wolny") << std::endl;
        }
        plik.close();
    }
    else {
        std::cerr << "Nie mozna zapisac danych do pliku: " << nazwaPliku << std::endl;
    }
}
