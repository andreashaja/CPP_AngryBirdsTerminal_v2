/* ---------------------------------------------------------------------
 * The Fearless Engineer - Programmieren und Elektronik
 * Copyright (C) 2021, Dr. Andreas Haja.  
 *
 * Zweck : "Halbzeit"-Projekt zur C++ - Challenge (Tag 7)
 *         --> https://go.tfe.academy/cpp_challenge
 * 
 *         MUSTERLÖSUNG
 *
 * Du solltest zusammen mit diesem Programm eine Kopie der MIT-Lizenz erhalten haben.
 * Falls nicht, sieh bitte hier nach: https://opensource.org/licenses/MIT.
 * ----------------------------------------------------------------------
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

// -----------
// Teil 1 : Eigene Datenstruktur für einen Vogel anlegen
struct Bird
{
    //// AUFGABE
    //// Lege vier Variablen vom Typ double an namens 'pos_x', 'pos_y', 'v_x' und 'v_y'
    double pos_x{0.0}; // Position in x in m
    double pos_y{0.0};
    double v_x{0.0}; // Geschwindigkeit in x in m
    double v_y{0.0};

    bool has_been_shot{false}; // wird true, wenn Vogel abgefeuert wurde
};

int main()
{
    // -----------
    // Teil 2 : Anzahl der sichtbaren Zeilen im Terminal herausfinden
    int cnt_lines{100};
    while (cnt_lines > 0)
    {
        cout << cnt_lines << endl;
        --cnt_lines;
    }
    cout << "VORBEREITUNG: Gib den Wert der obersten noch sichtbaren Zahl ein :";
    int visible_rows{0};
    cin >> visible_rows;

    // -----------
    // Teil 3 : Spielparameter definieren
    const int num_cols = 70; // Größe des Spielfeldes in x-Richtung (1 Zelle = 1 Meter)
    const int max_rows = 30; // Maximale Größe des Spielfeldes in y-Richtung
    const int num_birds = 3; // Anzahl der verfügbaren Vögel
    int slingshot_pos = 5;   // x-Position der Schleuder in m
    int pig_pos = 60;        // x-Position des Schweins in m
    double gravity = 9.81;   // Erdbeschleunigung in m/s^2
    int anim_freq = 60;      // Animationsgeschwindigkeit in Hertz

    // -----------
    // Teil 4 : 2D-Array für Bilddaten anlegen
    char screen_buffer[max_rows][num_cols]{};
    int num_rows = min(max_rows, visible_rows); // Anzahl Zeilen auf sichtbaren Bereich beschränken

    // -----------
    // Teil 5 : Bodenebene einzeichnen (Achtung: y=0 entspricht dem oberen Bildrand)
    int ground_level = num_rows - 1;

    //// AUFGABE 5.1
    //// Zeichne eine Bodenebene am unteren Rand des Terminsal ein, die aus '_'-Zeichen besteht
    int cnt_cols{0};
    while (cnt_cols < num_cols)
    {
        screen_buffer[ground_level][cnt_cols] = '_';
        ++cnt_cols;
    }

    // -----------
    // Teil 6 : Schleuder einzeichnen
    screen_buffer[ground_level][slingshot_pos] = '|';
    screen_buffer[ground_level - 1][slingshot_pos] = '|';
    screen_buffer[ground_level - 2][slingshot_pos - 1] = '\\'; // Achtung: Backslash muss mit "\" als Sonderzeichen markiert werden
    screen_buffer[ground_level - 2][slingshot_pos + 1] = '/';

    // -----------
    // Teil 7 : Schwein positionieren und zeichnen

    //// AUFGABE 7.1
    //// Zeichne das Symbol '@' für das Schwein an der Stelle y=ground_level, x=pig_pos ein
    screen_buffer[ground_level][pig_pos] = '@';

    // -----------
    // Teil 8 : 2D-Array zeichnen
    int cnt_rows{0};
    while (cnt_rows < num_rows) // Schleife über alle Zeilen
    {
        int cnt_cols{0};
        while (cnt_cols < num_cols) // Schleife über alle Spalten
        {
            // In freie Zellen Leerzeichen schreiben
            if (screen_buffer[cnt_rows][cnt_cols] == 0)
                screen_buffer[cnt_rows][cnt_cols] = ' ';

            // Jede einzelne Zelle ausgeben
            cout << screen_buffer[cnt_rows][cnt_cols];
            ++cnt_cols;
        }
        cout << endl;
        ++cnt_rows;
    }

    // -----------
    // Teil 9 : 1D-Array für Vögel anlegen

    //// AUFGABE 9.1
    //// Lege ein 1D-Array namens 'birds' vom Datentyp 'Bird' an, das aus num_birds Elementen dieses Typs besteht
    Bird birds[num_birds];

    // -----------
    // Teil 10 : Äußere Schleife über alle Vögel
    int score{0};
    int cnt_birds{0};
    while (cnt_birds < num_birds)
    {
        // -----------
        // Teil 11 : Vogel positionieren

        //// AUFGABE 11.1
        //// Positioniere den aktuellen Vogel an der Stelle x=slingshot_pos, y=ground_level-2 und setze has_been_shot auf true
        birds[cnt_birds].pos_x = slingshot_pos;
        birds[cnt_birds].pos_y = ground_level - 2;
        birds[cnt_birds].has_been_shot = true;

        // -----------
        // Teil 12 : Abschusswinkel in Grad abfragen (90° entspricht senkrecht nach oben)
        cout << "Bitte Abschusswinkel in Grad eingeben : ";
        double angle_deg{0.0};
        cin >> angle_deg;
        double angle = angle_deg * M_PI / 180;

        // -----------
        // Teil 13 : Abschussgeschwindigkeit in m/s abfragen
        cout << "Bitte Abschussgeschwindigkeit in m/s eingeben : ";
        double speed{0.0};
        cin >> speed;

        // -----------
        // Teil 14 : Berechne Abschussgeschwindigkeit des Vogels in x und y

        //// AUFGABE 14.1
        //// Berechne die x- und y-Geschwindigkeit des aktuellen Vogels mit v_x = speed * cos(angle) und v_y = speed * sin(angle)
        birds[cnt_birds].v_x = speed * cos(angle);
        birds[cnt_birds].v_y = speed * sin(angle);

        // -----------
        // Teil 15 : Terminal in Dauerschleife animieren
        double dt = 1.0 / anim_freq; // Animationsgeschwindigkeit in Sekunden
        int cnt_anim{0};
        while (1)
        {
            // -----------
            // Teil 16 : Ausführung für Animationsdauer anhalten
            std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 * dt)));

            // -----------
            // Teil 17 : Vogel an alter Position löschen
            int old_x{0}, old_y{0};

            //// AUFGABE 17.1
            //// Runde die aktuelle x- und y-Position des Vogels mit dem Befehl round() und weise das Ergebnis den Integer-Variablen old_x und old_y zu.
            old_x = round(birds[cnt_birds].pos_x);
            old_y = round(birds[cnt_birds].pos_y);

            if (old_y >= 0 && old_y < max_rows && old_x >= 0 && old_x < num_cols) // ungültige Array-Indizes vermeiden
                screen_buffer[old_y][old_x] = '.';

            // -----------
            // Teil 18 : Geschwindigkeit aktualisieren

            //// AUFGABE 18.1
            //// Ziehe von der aktuellen y-Geschwindigkeit des Vogels das Produkt aus Schwerkraft und Zeit ab
            birds[cnt_birds].v_y -= gravity * dt;

            // -----------
            // Teil 19 : Position des Vogels aktualisieren

            //// AUFGABE 19.1
            //// Addiere zur x-Position des Vogels das Produkt aus x-Geschwindigkeit und Zeit hinzu.
            //// Subtrahiere von der y-Position des Vogels das Produkt aus y-Geschwindigkeit und Zeit.
            birds[cnt_birds].pos_x += birds[cnt_birds].v_x * dt;
            birds[cnt_birds].pos_y -= birds[cnt_birds].v_y * dt; // Operator -= erforderlich, da y-Achse invertiert ist

            // -----------
            // Teil 20 : Vogel auf dem Boden aufgeschlagen oder über den rechten Rand hinausgeflogen?

            //// AUFGABE 20.1
            //// Prüfe, ob die aktuelle y-Position größer oder gleich der Bodeneben ist oder die x-Position größer oder gleich der Spaltenanzahl - 1
            //// Falls eine der beiden Bedingungen erfüllt ist, verlasse die while-Schleife mit break;
            if (birds[cnt_birds].pos_y >= ground_level || birds[cnt_birds].pos_x >= num_cols - 1)
                break; // Animationsschleife verlassen

            // -----------
            // Teil 21 : Vogel an neuer Position zeichnen
            int new_x{0}, new_y{0};

            //// AUFGABE 21.1
            //// Runde die aktuelle x- und y-Position des Vogels und weise das Ergebnis den Variablen new_x und new_y zu
            new_x = round(birds[cnt_birds].pos_x);
            new_y = round(birds[cnt_birds].pos_y);

            if (new_y >= 0 && new_y < max_rows && new_x >= 0 && new_x < num_cols) // Zeichne den Vogel nur, wenn die neuen Koordinaten innerhalb des 2D-Arrays liegen
                screen_buffer[new_y][new_x] = 'o';

            // -----------
            // Teil 22 : Aktuelles Bild zeichnen
            int cnt_rows{0};
            while (cnt_rows < num_rows) // Schleife über alle Zeilen
            {
                int cnt_cols{0};
                while (cnt_cols < num_cols) // Schleife über alle Spalten
                {
                    cout << screen_buffer[cnt_rows][cnt_cols];
                    ++cnt_cols;
                }
                cout << endl; // Zeilenumbruch am Ende einer Zeile
                ++cnt_rows;
            }
        } // Ende der Animationsschleife

        // -----------
        // Teil 23 : Auf Treffer prüfen

        //// AUFGABE 23.1
        //// Wenn die gerundete y-Position des Vogels identisch zur Bodenebene ist UND die gerundete x-Position identisch zur Position des Schweins +/- 1 Feld ist,
        //// dann addiere 500 Punkte zur Variablen score hinzu und verlasse mittels break die Schleife.
        bool hit_x = (round(birds[cnt_birds].pos_x) >= pig_pos - 1) && (round(birds[cnt_birds].pos_x) <= pig_pos + 1);
        bool hit_y = (round(birds[cnt_birds].pos_y) >= ground_level - 1) && (round(birds[cnt_birds].pos_y) <= ground_level + 1);
        if (hit_x && hit_y) // Hat Vogel Schwein getroffen?
        {
            score += 500; // Punkte vergeben
            break;        // Äußere Schleife verlassen
        }

        // zu nächstem Vogel wechseln
        ++cnt_birds;
    }

    // -----------
    // Teil 24 : Anzahl verbleibender Vögel zählen

    //// AUFGABE 24.1
    //// Überprüfe für jeden Vogel, ob er bereits abgeschossen wurde. Falls nicht, addiere 100 Punkte zur Variablen score
    cnt_birds = 0;
    while (cnt_birds < num_birds)
    {
        if (birds[cnt_birds].has_been_shot == false)
            score += 100;

        ++cnt_birds;
    }

    cout << "Du hast " << score << " Punkte erreicht!" << endl;
    cout << "DAS SPIEL IST BEENDET!\n\n";

    return 0;
}
