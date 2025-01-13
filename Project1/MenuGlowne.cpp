#include "MenuGlowne.h"
#include "Klasy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <conio.h> // U¿ycie _getch dla Windows
#include <sstream>

using namespace std;

MenuGlowne::MenuGlowne(ZarzadzanieRezerwacjami& zarz, StanDostepnosci& stan) : zarzadzanie(zarz), stanDostepnosci(stan) {}

void MenuGlowne::wyswietlEkranPoczatkowy() {
    cout << "=================================" << endl;
    cout << "          Witamy w Hotelu        " << endl;
    cout << "=================================" << endl;
    cout << "[1] Przejdz do menu glownego" << endl;
    cout << "=================================" << endl;

    int wybor;
    do {
        cout << "Wybierz opcje (1): ";
        cin >> wybor;
        if (wybor != 1) {
            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
    } while (wybor != 1);

    cout << "Przechodzenie do menu glownego..." << endl;
}

void MenuGlowne::wyswietlMenu() {
    cout << "========== MENU GLOWNE ==========" << endl;
    cout << "1. Zaloguj sie jako administrator" << endl;
    cout << "2. Zaloguj sie jako gosc" << endl;
    cout << "3. Zaloz konto" << endl;
    cout << "4. Wyjscie" << endl;
}

void MenuGlowne::zalogujAdministratora() {
    string haslo;
    cout << "Podaj haslo administratora: ";
    haslo = ukryjHaslo();
    if (haslo == "admin123") {
        cout << "Zalogowano jako administrator." << endl;
    }
    else {
        cout << "Niepoprawne haslo!" << endl;
    }
}

void MenuGlowne::zalogujGoscia() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string email, haslo;

    cout << "========== LOGOWANIE ==========" << endl;
    cout << "Podaj email: ";
    getline(cin, email);
    cout << "Podaj haslo: ";
    haslo = ukryjHaslo();

    string sciezka = "daneuzytkownicy.txt";
    ifstream plik(sciezka);
    if (!plik.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << sciezka << endl;
        return;
    }

    string linia;
    bool zalogowano = false;

    while (getline(plik, linia)) {
        size_t separator = linia.find(':');
        if (separator != string::npos) {
            string zapisanyEmail = linia.substr(0, separator);
            string zapisaneHaslo = linia.substr(separator + 1);

            if (email == zapisanyEmail && haslo == zapisaneHaslo) {
                cout << "Zalogowano jako " << email << "." << endl;
                zalogowano = true;
                menuGoscia();
                return;
            }
        }
    }

    plik.close();
    if (!zalogowano) {
        cout << "Niepoprawny email lub haslo!" << endl;
    }
}

void MenuGlowne::zlozRezerwacje() {
    int numerPokoju;
    cout << "Podaj numer pokoju do rezerwacji: ";
    cin >> numerPokoju;
    zarzadzanie.dodajRezerwacje(numerPokoju);
    stanDostepnosci.oznaczPokoj(numerPokoju, true);
    cout << "Pokoj nr " << numerPokoju << " zostal zarezerwowany." << endl;
}

void MenuGlowne::sprawdzDostepnosc() {
    cout << "Lista dostepnych pokoi: " << endl;
    for (int i = 1; i <= 100; ++i) {
        if (stanDostepnosci.sprawdzDostepnosc(i)) {
            cout << "Pokoj nr " << i << " jest wolny." << endl;
        }
    }
}

void MenuGlowne::odwolajRezerwacje() {
    int numerPokoju;
    cout << "Podaj numer pokoju, ktorego rezerwacje chcesz odwolac: ";
    cin >> numerPokoju;
    stanDostepnosci.oznaczPokoj(numerPokoju, false);
    cout << "Rezerwacja pokoju nr " << numerPokoju << " zostala odwolana." << endl;
}

void MenuGlowne::menuGoscia() {
    int wybor;

    do {
        cout << "========== MENU GOSCIA ==========" << endl;
        cout << "1. Zloz rezerwacje" << endl;
        cout << "2. Odwolaj rezerwacje" << endl;
        cout << "3. Sprawdz dostepnosc pokoi" << endl;
        cout << "4. Dokonaj platnosci" << endl;
        cout << "5. Powrot do menu glownego" << endl;
        cout << "=================================" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            zlozRezerwacje();
            break;
        case 2:
            odwolajRezerwacje();
            break;
        case 3:
            sprawdzDostepnosc();
            break;
        case 4:
            dokonajPlatnosci();
            break;
        case 5:
            cout << "Powrot do menu glownego..." << endl;
            break;
        default:
            cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
        }
    } while (wybor != 5);
}

void MenuGlowne::dokonajPlatnosci() {
    ifstream plik("zarezerwowane.txt");
    if (!plik.is_open()) {
        cout << "Brak rezerwacji. Najpierw zloz rezerwacje." << endl;
        return;
    }

    int numerPokoju;
    cout << "Podaj numer pokoju, za ktory chcesz dokonac platnosci: ";
    cin >> numerPokoju;

    string linia;
    bool znaleziono = false;
    while (getline(plik, linia)) {
        int zarezerwowanyNumer;
        istringstream iss(linia);
        iss >> zarezerwowanyNumer;

        if (zarezerwowanyNumer == numerPokoju) {
            znaleziono = true;
            break;
        }
    }
    plik.close();

    if (!znaleziono) {
        cout << "Nie znaleziono rezerwacji dla pokoju nr " << numerPokoju << "." << endl;
        return;
    }

    int metodaPlatnosci;
    cout << "Wybierz metode platnosci: " << endl;
    cout << "1. Gotowka" << endl;
    cout << "2. Przelew" << endl;
    cout << "Wybierz opcje: ";
    cin >> metodaPlatnosci;

    switch (metodaPlatnosci) {
    case 1:
        cout << "Platnosc gotowka zarejestrowana, dokonasz jej na miejscu. Dziekujemy!" << endl;
        break;
    case 2:
        cout << "Platnosc przelewem zarejestrowana. Szczegoly przeslane na e-mail. Dziekujemy!" << endl;
        break;
    default:
        cout << "Nieprawidlowa opcja platnosci." << endl;
    }
}

void MenuGlowne::wybierzOpcje() {
    int wybor;
    wyswietlEkranPoczatkowy();
    do {
        wyswietlMenu();
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            zalogujAdministratora();
            break;
        case 2:
            zalogujGoscia();
            break;
        case 3:
            cout << "Funkcja zalozKonto jeszcze nie zaimplementowana." << endl;
            break;
        case 4:
            cout << "Wyjscie z programu..." << endl;
            return;
        default:
            cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
        }
    } while (wybor != 4);
}

string MenuGlowne::ukryjHaslo() {
    string haslo;
    char znak;
    while ((znak = _getch()) != '\r') { // '\r' to Enter in Windows
        if (znak == '\b') { // Backspace
            if (!haslo.empty()) {
                haslo.pop_back();
                cout << "\b \b";
            }
        }
        else {
            haslo.push_back(znak);
            cout << "*";
        }
    }
    cout << endl;
    return haslo;
}
