#ifndef KLASY_H
#define KLASY_H

#include <vector>
#include <string>
#include <iostream>

class Pokoj {
public:
    int numer;
    bool zajety;

    Pokoj(int numer, bool zajety = false);
};

class ZarzadzanieRezerwacjami {
public:
    void dodajRezerwacje(int numerPokoju);
    void zmienStatusPokoju(int numerPokoju, const std::string& nowyStatus);
};

class StanDostepnosci {
private:
    std::vector<Pokoj> pokoje;

public:
    StanDostepnosci();
    bool sprawdzDostepnosc(int numerPokoju);
    void oznaczPokoj(int numerPokoju, bool zajety);
    void zapiszDostepnoscDoPliku(const std::string& nazwaPliku);
};

class MetodaPlatnosci { // New Base Class for Payment Methods
public:
    virtual void zaplac(int kwota) = 0;
    virtual ~MetodaPlatnosci() = default;
};

class Gotowka : public MetodaPlatnosci { // Payment by Cash
public:
    void zaplac(int kwota) override {
        std::cout << "Zap³acono gotówk¹: " << kwota << " z³.\n";
    }
};

class Przelew : public MetodaPlatnosci { // Payment by Bank Transfer
public:
    void zaplac(int kwota) override {
        std::cout << "Zap³acono przelewem: " << kwota << " z³.\n";
    }
};

#endif // KLASY_H
