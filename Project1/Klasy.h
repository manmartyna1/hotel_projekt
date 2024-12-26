#ifndef KLASY_H
#define KLASY_H

#include <string>
#include <vector>
#include <iostream> // Dla std::cout i std::endl

using namespace std;

// Klasa Go��
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

// Klasa Pok�j
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

// Klasa Zarz�dzanie Rezerwacjami
class ZarzadzanieRezerwacjami {
private:
    vector<Pokoj> pokoje;
    vector<Gosc> goscie;

public:
    void dodajRezerwacje(const Gosc& gosc, const Pokoj& pokoj);
    void wyswietlRezerwacje() const;
};

class StanDostepnosci {
private:
    std::vector<bool> pokoje;  // Tablica zaj�to�ci pokoi (false = wolny, true = zaj�ty)

public:
    StanDostepnosci();                                      // Konstruktor
    void zaladujDostepnoscZPliku(const std::string& nazwaPliku);  // Wczytaj dost�pno�� z pliku
    void zapiszDostepnoscDoPliku(const std::string& nazwaPliku);  // Zapisz dost�pno�� do pliku
    bool sprawdzDostepnosc(int numerPokoju) const;               // Sprawd� dost�pno�� pokoju
    void oznaczPokoj(int numerPokoju, bool zajety);              // Oznacz pok�j jako zaj�ty/wolny
    void wyswietlInformacje() const;                            // Wy�wietl typy pokoi
};

#endif // KLASY_H
