#include "Klasy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Implementacja konstruktora dla klasy Pokoj
Pokoj::Pokoj(int numer, bool zajety) : numer(numer), zajety(zajety) {}

// Implementacja klasy StanDostepnosci
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
    ofstream plik(nazwaPliku, ios::trunc);
    if (plik.is_open()) {
        for (const auto& pokoj : pokoje) {
            plik << pokoj.numer << " " << (pokoj.zajety ? "zajety" : "wolny") << endl;
        }
        plik.close();
    }
    else {
        cerr << "Nie mozna zapisac danych do pliku: " << nazwaPliku << endl;
    }
}

// Implementacja klasy ZarzadzanieRezerwacjami
void ZarzadzanieRezerwacjami::wyswietlRezerwacje() {
    cout << "========== LISTA REZERWACJI ==========" << endl;
    ifstream plik("zarezerwowane.txt");
    if (!plik.is_open()) {
        cout << "Brak zapisanych rezerwacji." << endl;
        return;
    }

    string linia;
    while (getline(plik, linia)) {
        cout << linia << endl;
    }

    plik.close();
    cout << "======================================" << endl;
}

void ZarzadzanieRezerwacjami::zmienStatusPokoju(int numerPokoju, const string& nowyStatus) {
    cout << "Zmieniam status pokoju nr " << numerPokoju << " na \"" << nowyStatus << "\"." << endl;

    ofstream plik("status_pokoi.txt", ios::app);
    if (plik.is_open()) {
        plik << "Pokoj nr " << numerPokoju << " - Status: " << nowyStatus << endl;
        plik.close();
    }
    else {
        cerr << "Nie mozna zapisac nowego statusu pokoju." << endl;
    }
}
