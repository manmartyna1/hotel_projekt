#include "Klasy.h"
#include <iostream>
#include <fstream>

using namespace std;

// Implementacja klasy Goœæ
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

// Implementacja klasy Pokój
Pokoj::Pokoj(int numer, const string& status) : numer(numer), status(status) {}

int Pokoj::getNumer() const { return numer; }
void Pokoj::setNumer(int numer) { this->numer = numer; }

string Pokoj::getStatus() const { return status; }
void Pokoj::setStatus(const string& status) { this->status = status; }

void Pokoj::wyswietlDane() const {
    cout << "Pokoj nr: " << numer << ", Status: " << status << endl;
}

// Implementacja klasy Zarz¹dzanie Rezerwacjami
void ZarzadzanieRezerwacjami::dodajRezerwacje(const Gosc& gosc, const Pokoj& pokoj) {
    pokoje.push_back(pokoj);
    goscie.push_back(gosc);
    cout << "Dodano rezerwacje: " << gosc.getImie() << " " << gosc.getNazwisko()
        << " - Pokoj nr: " << pokoj.getNumer() << endl;
}

void ZarzadzanieRezerwacjami::wyswietlRezerwacje() const {
    cout << "Lista rezerwacji: " << endl;
    for (size_t i = 0; i < goscie.size(); ++i) {
        goscie[i].wyswietlDane();
        pokoje[i].wyswietlDane();
    }
}

// ======== IMPLEMENTACJA KLASY StanDostepnosci ========

// Konstruktor
StanDostepnosci::StanDostepnosci() : pokoje(100, false) {
    // Inicjalizujemy wszystkie pokoje jako wolne (false)
}

// Wczytaj dostêpnoœæ z pliku
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

// Zapisz dostêpnoœæ do pliku
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

// SprawdŸ dostêpnoœæ pokoju
bool StanDostepnosci::sprawdzDostepnosc(int numerPokoju) const {
    if (numerPokoju < 1 || numerPokoju > 100) {
        cout << "Numer pokoju " << numerPokoju << " jest nieprawidlowy!" << endl;
        return false;
    }
    return !pokoje[numerPokoju - 1];  // Zwracamy true, jeœli pokój jest wolny (false = wolny)
}

// Oznacz pokój jako zajêty/wolny
void StanDostepnosci::oznaczPokoj(int numerPokoju, bool zajety) {
    if (numerPokoju < 1 || numerPokoju > 100) {
        cout << "Numer pokoju " << numerPokoju << " jest nieprawidlowy!" << endl;
        return;
    }
    pokoje[numerPokoju - 1] = zajety;
}

// Wyœwietl typy pokoi
void StanDostepnosci::wyswietlInformacje() const {
    cout << "========== INFORMACJE O TYPACH POKOI ==========" << endl;
    cout << "Pokoje 1-15: Standard jednoosobowy" << endl;
    cout << "Pokoje 16-30: Komfort jednoosobowy" << endl;
    cout << "Pokoje 31-45: Standard dwuosobowy" << endl;
    cout << "Pokoje 46-60: Apartamenty" << endl;
    cout << "==============================================" << endl;
}
