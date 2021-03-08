/* ---------------------------------------------------------------------
 * The Fearless Engineer - Programmieren und Elektronik
 * Copyright (C) 2021, Dr. Andreas Haja.  
 *
 * Zweck : "Halbzeit"-Projekt zur C++ - Challenge (Tag 7)
 *         --> https://go.tfe.academy/cpp_challenge
 * 
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
// Eigene Datenstruktur für einen Vogel anlegen

//// AUFGABE 2.1
//// Lege einen eigenen Datentyp namens "Bird" an, der vier Variablen vom Typ double namens
//// 'pos_x', 'pos_y', 'v_x' und 'v_y' enthält und eine Variable vom Typ bool namens 'has_been_shot'.
//// Initialisiere alle Variablen zu Null.
class Bird
{
public:
    double pos_x{0.0}; // Position in x in m
    double pos_y{0.0};
    double v_x{0.0}; // Geschwindigkeit in x in m
    double v_y{0.0};

    bool has_been_shot{false}; // wird true, wenn Vogel abgefeuert wurde
};

int main()
{
    // -----------
    // Anzahl der sichtbaren Zeilen im Terminal herausfinden
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
    // Spielparameter definieren
    const int num_cols = 100; // Größe des Spielfeldes in x-Richtung (1 Zelle = 1 Meter)
    const int max_rows = 50;  // Maximale Größe des Spielfeldes in y-Richtung
    const int num_birds = 3;  // Anzahl der verfügbaren Vögel
    int slingshot_pos = 5;    // x-Position der Schleuder in m
    int pig_pos = 65;         // x-Position des Schweins in m
    double gravity = 9.81;    // Erdbeschleunigung in m/s^2
    int anim_freq = 20;       // Animationsgeschwindigkeit in Hertz

    // -----------
    // 2D-Array für Bilddaten anlegen
    char screen_buffer[max_rows][num_cols]{};
    int num_rows = min(max_rows, visible_rows); // Anzahl Zeilen auf sichtbaren Bereich beschränken

    // -----------
    // Zeichnen von Bodenebene und Ziel (Hinweis: y=0 entspricht dem oberen Bildrand)
    int ground_level = num_rows - 1;

    //// AUFGABE A1.1
    //// Zeichne eine Bodenebene am unteren Rand des Terminal ein, die aus '_'-Zeichen besteht
    for (int cnt_cols = 0; cnt_cols < num_cols; ++cnt_cols)
    {
        screen_buffer[ground_level][cnt_cols] = '_';
    }

    //// AUFGABE A1.2
    //// Zeichne das Symbol '@' für das Ziel an der Stelle y=ground_level, x=pig_pos ein
    screen_buffer[ground_level][pig_pos] = '@';

    // -----------
    // Schleuder einzeichnen
    screen_buffer[ground_level][slingshot_pos] = '|';
    screen_buffer[ground_level - 1][slingshot_pos] = '|';
    screen_buffer[ground_level - 2][slingshot_pos - 1] = '\\'; // Achtung: Backslash muss mit "\" als Sonderzeichen markiert werden
    screen_buffer[ground_level - 2][slingshot_pos + 1] = '/';
    screen_buffer[ground_level - 3][slingshot_pos - 2] = '\\';
    screen_buffer[ground_level - 3][slingshot_pos + 2] = '/';

    // -----------
    // Vögel erzeugen und im Spielfeld positionieren

    //// AUFGABE 2.2
    //// Lege ein 1D-Array namens 'birds' vom Datentyp 'Bird' an, das aus 'num_birds' Elementen dieses Typs besteht
    Bird birds[num_birds];

    int score{0};
    int cnt_birds{0};
    while (cnt_birds < num_birds) // Äußere Schleife über alle Vögel
    {
        //// AUFGABE 2.3
        //// Positioniere den aktuellen Vogel an der Stelle x=slingshot_pos, y=ground_level-2 und setze has_been_shot auf true
        birds[cnt_birds].pos_x = slingshot_pos;
        birds[cnt_birds].pos_y = ground_level - 3;
        birds[cnt_birds].has_been_shot = true;

        //// AUFGABE 2.4
        //// Zeichne den Vogel in den screen_buffer als 'o'-Zeichen ein, indem du mit dem Befehl 'round()'
        //// die Fließkomma-Koordinaten in Ganzzahlen umwandelst. Lege dazu zwei neue Integer-Variablen an und
        //// speichere die gerundeten Koordinaten darin.
        int cell_x = round(birds[cnt_birds].pos_x);
        int cell_y = round(birds[cnt_birds].pos_y);
        screen_buffer[cell_y][cell_x] = 'o';

        // -----------
        // 2D-Array im Terminal "zeichnen" (=ausgeben)
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
        // Abschusswinkel in Grad abfragen (90° entspricht senkrecht nach oben)
        cout << "Bitte Abschusswinkel in Grad eingeben : ";
        double angle_deg{0.0};
        cin >> angle_deg;
        double angle = angle_deg * M_PI / 180;

        // -----------
        // Abschussgeschwindigkeit in m/s abfragen
        cout << "Bitte Abschussgeschwindigkeit in m/s eingeben : ";
        double speed{0.0};
        cin >> speed;

        //// AUFGABE 3.1
        // Berechne Startwerte für die x- und y-Geschwindigkeit des aktuellen Vogels als
        // Produkt aus Geschwindigkeit und Cosinus des Winkels (x) bzw. Sinus des Winkels (y)
        birds[cnt_birds].v_x = speed * cos(angle);
        birds[cnt_birds].v_y = speed * sin(angle);

        // -----------
        // Terminal in Dauerschleife animieren
        double dt = 1.0 / anim_freq; // Animationsgeschwindigkeit in Sekunden
        int cnt_anim{0};
        while (1)
        {
            // Ausführung für Animationsdauer anhalten (bitte ignorieren, falls noch zu "abschreckend")
            std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 * dt)));

            // -----------
            // Alte Position des Vogels löschen

            //// AUFGABE 4.1
            //// Runde die aktuelle x- und y-Position des Vogels mit dem Befehl round() und speichere das Ergebnis in old_x und old_y.
            int old_x{0}, old_y{0};
            old_x = round(birds[cnt_birds].pos_x);
            old_y = round(birds[cnt_birds].pos_y);

            //// AUFGABE 4.2
            //// Überschreibe die alte Position des Vogels mit `.` und stelle dabei sicher,
            //// dass ungültige Arrays-Indizes vermieden werden
            if (old_y >= 0 && old_y < max_rows && old_x >= 0 && old_x < num_cols)
                screen_buffer[old_y][old_x] = ' ';

            // -----------
            // Geschwindigkeit des Vogels aktualisieren

            //// AUFGABE 3.2
            //// Ziehe von der aktuellen y-Geschwindigkeit des Vogels das Produkt aus Schwerkraft und Zeit ab
            birds[cnt_birds].v_y -= gravity * dt;
            
            // -----------
            // Position des Vogels aktualisieren

            //// AUFGABE 3.3
            //// Addiere zur x-Position des Vogels das Produkt aus x-Geschwindigkeit und Zeit hinzu.
            //// Subtrahiere von der y-Position des Vogels das Produkt aus y-Geschwindigkeit und Zeit.
            //// (Hinweis: In der Computergrafik zeigt die y-Achse in der Regel von oben nach unten)
            birds[cnt_birds].pos_x += birds[cnt_birds].v_x * dt;
            birds[cnt_birds].pos_y -= birds[cnt_birds].v_y * dt;

            //// AUFGABE 3.4
            //// Prüfe, ob die aktuelle y-Position größer oder gleich der Bodeneben ist oder die x-Position größer oder gleich der Spaltenanzahl - 1
            //// Falls eine der beiden Bedingungen erfüllt ist, verlasse die Schleife.
            if (birds[cnt_birds].pos_y >= ground_level || birds[cnt_birds].pos_x >= num_cols - 1)
                break; // Animationsschleife verlassen

            //// AUFGABE 3.5
            //// Zeichne den Vogel in den screen_buffer als 'o'-Zeichen ein, indem du mit dem Befehl 'round()'
            //// die Fließkomma-Koordinaten in Ganzzahlen umwandelst. Zeichne dann an die aktuelle Position des
            //// Vogels das Zeichen 'o' und achte darauf, dass die neuen Koordinaten innerhalb des 2D-Arrays liegen.
            int new_x{0}, new_y{0};
            new_x = round(birds[cnt_birds].pos_x);
            new_y = round(birds[cnt_birds].pos_y);
            if (new_y >= 0 && new_y < max_rows && new_x >= 0 && new_x < num_cols)
                screen_buffer[new_y][new_x] = 'o';

            // -----------
            // 2D-Array inkl. Ziel und Vogel im Terminal ausgeben
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
        // Auf Treffer prüfen

        //// AUFGABE 5.1
        //// Wenn die gerundete y-Position des Vogels identisch zur Bodenebene ist UND die gerundete x-Position identisch zur Position des Schweins +/- 1 Feld ist,
        //// dann addiere 500 Punkte zur Variablen score hinzu und verlasse mittels break die Schleife.
        // --> Bitte Code HIER ergänzen

        // zu nächstem Vogel wechseln
        ++cnt_birds;
    }

    // -----------
    // Anzahl verbleibender Vögel zählen und Punkte ermitteln

    //// AUFGABE 5.2
    //// Überprüfe für jeden Vogel, ob er bereits abgeschossen wurde. Falls nicht, addiere 100 Punkte zur Variablen score
    // --> Bitte Code HIER ergänzen

    // Ausgabe der erreichten Punkte
    cout << score << " Punkte erreicht!" << endl;
    cout << "Du hast das Spiel " << (score > 0 ? "GEWONNEN" : "VERLOREN") << endl;

    return 0;
}
