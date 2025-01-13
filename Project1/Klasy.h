#ifndef KLASY_H
#define KLASY_H

#include <vector>
#include <string>

class Pokoj {
public:
    int numer;
    bool zajety;

    Pokoj(int numer, bool zajety = false);
};

class ZarzadzanieRezerwacjami {
public:
    void wyswietlRezerwacje();
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

#endif // KLASY_H
