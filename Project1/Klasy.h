#ifndef KLASY_H
#define KLASY_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Klasa Gosc
class Gosc {
private:
    string imie;
    string nazwisko;
    string email;

public:
    Gosc(const string& imie, const string& nazwisko, const string& email);
    string getImie() const;
    void setImie(const string& imie);
    string getNazwisko() const;
    void setNazwisko(const string& nazwisko);
    string getEmail() const;
    void setEmail(const string& email);
    void wyswietlDane() const;
};

// Klasa Pokoj
class Pokoj {
private:
    int numer;
    string status;

public:
    Pokoj(int numer, const string& status);
    int getNumer() const;
    void setNumer(int numer);
    string getStatus() const;
    void setStatus(const string& status);
    void wyswietlDane() const;
};

// Klasa ZarzadzanieRezerwacjami
class ZarzadzanieRezerwacjami {
private:
    vector<Pokoj> pokoje;

public:
    ZarzadzanieRezerwacjami();
    void dodajRezerwacje(int numerPokoju);
    void odwolajRezerwacje(int numerPokoju);
    bool czyPokojZajety(int numerPokoju) const;
};

// Klasa StanDostepnosci
class StanDostepnosci {
private:
    vector<bool> pokoje;

public:
    StanDostepnosci();
    void zaladujDostepnoscZPliku(const string& nazwaPliku);
    void zapiszDostepnoscDoPliku(const string& nazwaPliku);
    bool sprawdzDostepnosc(int numerPokoju) const;
    void oznaczPokoj(int numerPokoju, bool zajety);
    void wyswietlInformacje() const;
};

#endif
