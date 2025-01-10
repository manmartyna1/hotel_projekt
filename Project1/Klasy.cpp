#include "Klasy.h"
#include <iostream>
#include <fstream>

using namespace std;

// Implementacja klasy Gosc
Gosc::Gosc(const string& imie, const string& nazwisko, const string& email)
    : imie(imie), nazwisko(nazwisko), email(email) {
}

string Gosc::getImie() const { return imie; }
void Gosc::setImie(const string& imie) { this->imie = imie; }
string Gosc::getNazwisko() const { return nazwisko; }
void Gosc::setNazwisko(const string& nazwisko) { this->nazwisko = nazwisko; }
string Gosc::getEmail() const { return email; }
void Gosc::setEmail(const string& email) { this->email = email; }
void Gosc::wyswietlDane() const {
    cout << "Gosc: " << imie << " " << nazwisko << ", Email: " << email << endl;
}

// Implementacja klasy Pokoj
Pokoj::Pokoj(int numer, const string& status) : numer(numer), status(status) {}
int Pokoj::getNumer() const { return numer; }
void Pokoj::setNumer(int numer) { this->numer = numer; }
string Pokoj::getStatus() const { return status; }
void Pokoj::setStatus(const string& status) { this->status = status; }
void Pokoj::wyswietlDane() const {
    cout << "Pokoj nr: " << numer << ", Status: " << status << endl;
}

// Implementacja klasy ZarzadzanieRezerwacjami
ZarzadzanieRezerwacjami::ZarzadzanieRezerwacjami() {
    for (int i = 1; i <= 100; ++i) {
        pokoje.push_back(Pokoj(i, "wolny"));
    }
}

void ZarzadzanieRezerwacjami::dodajRezerwacje(int numerPokoju) {
    for (auto& pokoj : pokoje) {
        if (pokoj.getNumer() == numerPokoju) {
            pokoj.setStatus("zajety");
            return;
        }
    }
}

void ZarzadzanieRezerwacjami::odwolajRezerwacje(int numerPokoju) {
    for (auto& pokoj : pokoje) {
        if (pokoj.getNumer() == numerPokoju) {
            pokoj.setStatus("wolny");
            return;
        }
    }
}

bool ZarzadzanieRezerwacjami::czyPokojZajety(int numerPokoju) const {
    for (const auto& pokoj : pokoje) {
        if (pokoj.getNumer() == numerPokoju) {
            return pokoj.getStatus() == "zajety";
        }
    }
    return false;
}

// Implementacja klasy StanDostepnosci
StanDostepnosci::StanDostepnosci() : pokoje(100, false) {}

void StanDostepnosci::zaladujDostepnoscZPliku(const string& nazwaPliku) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << nazwaPliku << endl;
        return;
    }

    int numerPokoju;
    bool zajety;
    while (plik >> numerPokoju >> zajety) {
        if (numerPokoju >= 1 && numerPokoju <= 100) {
            pokoje[numerPokoju - 1] = zajety;
        }
    }

    plik.close();
}

void StanDostepnosci::zapiszDostepnoscDoPliku(const string& nazwaPliku) {
    ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << nazwaPliku << endl;
        return;
    }

    for (size_t i = 0; i < pokoje.size(); ++i) {
        plik << (i + 1) << " " << pokoje[i] << endl;
    }

    plik.close();
}

bool StanDostepnosci::sprawdzDostepnosc(int numerPokoju) const {
    if (numerPokoju < 1 || numerPokoju > 100) {
        cout << "Numer pokoju " << numerPokoju << " jest nieprawidlowy!" << endl;
        return false;
    }
    return !pokoje[numerPokoju - 1];
}

void StanDostepnosci::oznaczPokoj(int numerPokoju, bool zajety) {
    if (numerPokoju < 1 || numerPokoju > 100) {
        cout << "Numer pokoju " << numerPokoju << " jest nieprawidlowy!" << endl;
        return;
    }
    pokoje[numerPokoju - 1] = zajety;
}

void StanDostepnosci::wyswietlInformacje() const {
    cout << "========== INFORMACJE O TYPACH POKOI ==========" << endl;
    cout << "Pokoje 1-15: Standard jednoosobowy" << endl;
    cout << "Pokoje 16-30: Komfort jednoosobowy" << endl;
    cout << "Pokoje 31-45: Standard dwuosobowy" << endl;
    cout << "Pokoje 46-60: Apartamenty" << endl;
    cout << "==============================================" << endl;
}
