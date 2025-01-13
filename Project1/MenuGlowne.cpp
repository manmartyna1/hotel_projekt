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

void MenuGlowne::wyswietlMenuAdministratora() {
    cout << "========== MENU ADMINISTRATORA ==========" << endl;
    cout << "1. Wyswietl liste pokoi" << endl;
    cout << "2. Zmien status pokoju" << endl;
    cout << "3. Powrot do menu glownego" << endl;
}

void MenuGlowne::zalogujAdministratora() {
    string haslo;
    cout << "Podaj haslo administratora: ";
    haslo = ukryjHaslo();
    if (haslo == "admin123") {
        int wybor;
        do {
            wyswietlMenuAdministratora();
            cout << "Wybierz opcje: ";
            cin >> wybor;

            switch (wybor) {
            case 1:
                zarzadzanie.wyswietlRezerwacje(); // Wyœwietlenie listy pokoi
                break;
            case 2:
                zmienStatusPokoju(); // Zmiana statusu pokoju
                break;
            case 3:
                return; // Powrót do menu g³ównego
            default:
                cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
            }
        } while (true);
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

void MenuGlowne::menuGoscia() {
    int wybor;

    do {
        cout << "========== MENU GOSCIA ==========" << endl;
        cout << "1. Zloz rezerwacje" << endl;
        cout << "2. Odwolaj rezerwacje" << endl;
        cout << "3. Sprawdz dostepnosc pokoi" << endl;
        cout << "4. Powrot do menu glownego" << endl;
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
            cout << "Powrot do menu glownego..." << endl;
            break;
        default:
            cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
        }
    } while (wybor != 4);
}

void MenuGlowne::zlozRezerwacje() {
    string dataPrzyjazdu, dataOdjazdu;
    cout << "Podaj date przyjazdu (yyyy-mm-dd): ";
    cin >> dataPrzyjazdu;
    cout << "Podaj date odjazdu (yyyy-mm-dd): ";
    cin >> dataOdjazdu;

    int numerPokoju;
    cout << "Podaj numer pokoju, ktory chcesz zarezerwowac: ";
    cin >> numerPokoju;

    // Sprawdzanie, czy pokój jest zajêty
    if (czyPokojZajety(numerPokoju, dataPrzyjazdu, dataOdjazdu)) {
        cout << "Pokoj nr " << numerPokoju << " jest juz zarezerwowany w podanym terminie." << endl;
    }
    else {
        // Rezerwacja pokoju
        ofstream plik("zarezerwowane.txt", ios::app);
        if (plik.is_open()) {
            plik << numerPokoju << " " << dataPrzyjazdu << " " << dataOdjazdu << endl;
            plik.close();
            cout << "Zarezerwowano pokoj nr " << numerPokoju << " od " << dataPrzyjazdu << " do " << dataOdjazdu << "." << endl;
        }
        else {
            cout << "Blad: Nie mozna zapisac rezerwacji do pliku." << endl;
        }
    }
}

void MenuGlowne::sprawdzDostepnosc() {
    ifstream plik("zarezerwowane.txt");
    if (!plik.is_open()) {
        cout << "Brak danych o zajetych pokojach." << endl;
        return;
    }

    cout << "========== DOSTEPNOSC POKOI ==========" << endl;
    cout << "Pokoje dostepne w przedzialach: \n";

    string linia;
    while (getline(plik, linia)) {
        cout << linia << endl;
    }

    plik.close();
    cout << "=====================================" << endl;
}

bool MenuGlowne::czyPokojZajety(int numerPokoju, const string& dataPrzyjazdu, const string& dataOdjazdu) {
    ifstream plik("zarezerwowane.txt");
    if (!plik.is_open()) {
        return false; // Jeœli plik nie istnieje, traktujemy, ¿e pokój jest wolny
    }

    string linia;
    while (getline(plik, linia)) {
        int zarezerwowanyNumer;
        string zarezerwowanaPrzyjazd, zarezerwowanaOdjazd;

        // Parsowanie linii
        istringstream iss(linia);
        iss >> zarezerwowanyNumer >> zarezerwowanaPrzyjazd >> zarezerwowanaOdjazd;

        // Sprawdzanie kolizji terminów
        if (zarezerwowanyNumer == numerPokoju &&
            !(dataOdjazdu <= zarezerwowanaPrzyjazd || dataPrzyjazdu >= zarezerwowanaOdjazd)) {
            plik.close();
            return true; // Pokój zajêty w tym terminie
        }
    }

    plik.close();
    return false; // Pokój jest wolny
}

void MenuGlowne::zmienStatusPokoju() {
    int numerPokoju;
    string nowyStatus;

    cout << "Podaj numer pokoju, ktorego status chcesz zmienic: ";
    cin >> numerPokoju;
    cin.ignore();

    cout << "Podaj nowy status pokoju (np. 'dostêpny', 'zarezerwowany', 'w konserwacji'): ";
    getline(cin, nowyStatus);

    // U¿yj metody klasy ZarzadzanieRezerwacjami do zmiany statusu
    zarzadzanie.zmienStatusPokoju(numerPokoju, nowyStatus);
    cout << "Status pokoju nr " << numerPokoju << " zosta³ zmieniony na '" << nowyStatus << "'." << endl;
}

void MenuGlowne::odwolajRezerwacje() {
    int numerPokoju;
    cout << "Podaj numer pokoju, ktorego rezerwacje chcesz odwolac: ";
    cin >> numerPokoju;

    if (!stanDostepnosci.sprawdzDostepnosc(numerPokoju)) {
        stanDostepnosci.oznaczPokoj(numerPokoju, false);
        stanDostepnosci.zapiszDostepnoscDoPliku("zarezerwowane.txt");
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
    haslo = ukryjHaslo();

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

string MenuGlowne::ukryjHaslo() {
    string haslo;
    char znak;
    while ((znak = _getch()) != '\r') { // '\r' to Enter w Windows
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
