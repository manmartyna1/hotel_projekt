#include "MenuGlowne.h"
#include "Klasy.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Konstruktor klasy MenuGlowne
MenuGlowne::MenuGlowne(ZarzadzanieRezerwacjami& zarz) : zarzadzanie(zarz) {}

// Wyœwietlenie menu g³ównego
void MenuGlowne::wyswietlMenu() {
    cout << "========== MENU GLOWNE ==========" << endl;
    cout << "1. Zaloguj sie jako administrator" << endl;
    cout << "2. Zaloguj sie jako gosc" << endl;
    cout << "3. Zaloz konto" << endl;
    cout << "4. Wyjscie" << endl;
}

// Implementacja logowania jako administrator
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

// Implementacja logowania jako goœæ
void MenuGlowne::zalogujGoscia() {
    cin.ignore();
    string email, haslo;

    cout << "========== LOGOWANIE ==========" << endl;
    cout << "Podaj email: ";
    getline(cin, email);
    cout << "Podaj haslo: ";
    getline(cin, haslo);

    // Ustal œcie¿kê rêcznie
    string sciezka = "C:\\Users\\Lenovo\\Desktop\\hotel_projekt\\Project1\\uzytkownicy.txt";

    ifstream plik(sciezka);
    if (!plik.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku uzytkownicy.txt. Sprawdz sciezke: " << sciezka << endl;
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
                plik.close();
                wybierzPokoj();  // Przejœcie do wyboru pokoju
                return;
            }
        }
    }

    plik.close();
    if (!zalogowano) {
        cout << "Niepoprawny email lub haslo!" << endl;
    }
}

// Okno wyboru pokoju
void MenuGlowne::wybierzPokoj() {
    StanDostepnosci stanDostepnosci;
    stanDostepnosci.zaladujDostepnoscZPliku("dostepnosc.txt");

    stanDostepnosci.wyswietlInformacje();

    int numerPokoju;
    bool pokojZajety = true;

    // Pêtla umo¿liwiaj¹ca ponowny wybór pokoju, jeœli jest zajêty
    do {
        cout << "Podaj numer pokoju, ktorym jestes zainteresowany: ";
        cin >> numerPokoju;

        if (stanDostepnosci.sprawdzDostepnosc(numerPokoju)) {
            cout << "Pokoj nr: " << numerPokoju << " jest wolny. Rezerwacja zostanie dokonana." << endl;
            stanDostepnosci.oznaczPokoj(numerPokoju, true);  // Oznaczamy pokój jako zajêty
            stanDostepnosci.zapiszDostepnoscDoPliku("dostepnosc.txt");  // Zapis do pliku
            pokojZajety = false;  // Wyjœcie z pêtli
        }
        else {
            cout << "Pokoj nr: " << numerPokoju << " jest zajety. Wybierz inny pokoj." << endl;
        }
    } while (pokojZajety);  // Powtarzamy, dopóki u¿ytkownik nie wybierze wolnego pokoju
}

// Nowe okno do zak³adania konta
void MenuGlowne::noweOknoZakladaniaKonta() {
    cin.ignore();
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

    // Ustal œcie¿kê rêcznie
    string sciezka = "C:\\Users\\Lenovo\\Desktop\\hotel_projekt\\Project1\\uzytkownicy.txt";

    ofstream plik(sciezka, ios::app);  // Dopisujemy dane do pliku
    if (!plik.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku uzytkownicy.txt do zapisu. Sprawdz sciezke: " << sciezka << endl;
        return;
    }
    plik << email << ":" << haslo << endl;
    plik.close();

    cout << "Dane zostaly zapisane do pliku uzytkownicy.txt." << endl;
    cout << "Konto zostalo zalozone dla uzytkownika: " << imie << " " << nazwisko << endl;
    cout << "Wroc do menu glownego, aby sie zalogowac." << endl;
}

// Opcja za³o¿enia konta
void MenuGlowne::zalozKonto() {
    noweOknoZakladaniaKonta();
}

// Wybranie opcji
void MenuGlowne::wybierzOpcje() {
    int wybor;
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
