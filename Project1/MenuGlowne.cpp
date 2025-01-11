#include "MenuGlowne.h"
#include "Klasy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

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
    cin >> haslo;
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
    getline(cin, haslo);

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

void MenuGlowne::menuGoscia() {
    int wybor;

    do {
        cout << "========== MENU GOSCIA ==========" << endl;
        cout << "1. Zloz rezerwacje" << endl;
        cout << "2. Odwolaj rezerwacje" << endl;
        cout << "3. Powrot do menu glownego" << endl;
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
            cout << "Powrot do menu glownego..." << endl;
            break;
        default:
            cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
        }
    } while (wybor != 3);
}

void MenuGlowne::zlozRezerwacje() {
    int wybor;
    do {
        cout << "========== REZERWACJA ==========" << endl;
        cout << "1. Sprawdz dostepne pokoje" << endl;
        cout << "2. Dokonaj rezerwacji" << endl;
        cout << "3. Wroc" << endl;
        cout << "=================================" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1: {
            stanDostepnosci.wyswietlInformacje();

            ifstream plik("zarezerwowane_pokoje.txt");
            if (plik.is_open()) {
                cout << "Oto pokoje, ktore sa juz zajete:" << endl;
                string linia;
                while (getline(plik, linia)) {
                    if (!linia.empty()) {
                        cout << "Pokoj nr " << linia << endl;
                    }
                }
                plik.close();
            }
            else {
                cout << "Brak danych o zajetych pokojach." << endl;
            }
            break;
        }
        case 2: {
            int numerPokoju;
            cout << "Podaj numer pokoju, ktory chcesz zarezerwowac: ";
            cin >> numerPokoju;

            if (stanDostepnosci.sprawdzDostepnosc(numerPokoju)) {
                stanDostepnosci.oznaczPokoj(numerPokoju, true);
                ofstream plik("zarezerwowane_pokoje.txt", ios::app);
                if (plik.is_open()) {
                    plik << numerPokoju << endl;
                    plik.close();
                }
                cout << "Zarezerwowano pokoj nr " << numerPokoju << "." << endl;
            }
            else {
                cout << "Pokoj nr " << numerPokoju << " jest zajety lub nie istnieje." << endl;
            }
            break;
        }
        case 3:
            cout << "Powrot do menu..." << endl;
            break;
        default:
            cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
        }
    } while (wybor != 3);
}

void MenuGlowne::odwolajRezerwacje() {
    int numerPokoju;
    cout << "Podaj numer pokoju, ktorego rezerwacje chcesz odwolac: ";
    cin >> numerPokoju;

    if (!stanDostepnosci.sprawdzDostepnosc(numerPokoju)) {
        stanDostepnosci.oznaczPokoj(numerPokoju, false);
        stanDostepnosci.zapiszDostepnoscDoPliku("zarezerwowane_pokoje.txt");
        cout << "Rezerwacja pokoju nr " << numerPokoju << " zostala odwolana." << endl;
    }
    else {
        cout << "Pokoj nr " << numerPokoju << " nie jest zarezerwowany." << endl;
    }
}

void MenuGlowne::noweOknoZakladaniaKonta() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string imie, nazwisko, email, haslo;

    cout << "========== ZALOZ KONTO ==========" << endl;
    cout << "Podaj imie: ";
    getline(cin, imie);
    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);
    cout << "Podaj email: ";
    getline(cin, email);
    cout << "Podaj haslo: ";
    getline(cin, haslo);

    string sciezka = "daneuzytkownicy.txt";
    ofstream plik(sciezka, ios::app);
    if (!plik.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << sciezka << " do zapisu." << endl;
        return;
    }
    plik << email << ":" << haslo << endl;
    plik.close();

    cout << "Konto zostalo zalozone dla uzytkownika: " << imie << " " << nazwisko << endl;
}

void MenuGlowne::zalozKonto() {
    noweOknoZakladaniaKonta();
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
            zalozKonto();
            break;
        case 4:
            cout << "Wyjscie z programu." << endl;
            break;
        default:
            cout << "Nieprawidlowa opcja, sprobuj ponownie!" << endl;
        }
    } while (wybor != 4);
}
