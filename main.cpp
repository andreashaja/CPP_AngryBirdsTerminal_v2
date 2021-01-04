#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

struct GameObject
{
    double pos_x{0.0};
    double pos_y{0.0};
    double v_x{0.0};
    double v_y{0.0};
};

int main()
{
    // Anzahl der sichtbaren Zeilen im Terminal herausfinden
    int cnt_rows{100};
    while (cnt_rows > 0)
    {
        cout << cnt_rows << endl;
        --cnt_rows;
    }
    cout << "Bitte gib den Wert der obersten noch sichtbaren Zahl im Terminal ein :";
    int visible_rows{0};
    //cin >> visible_rows;
    visible_rows = 23; // DEBUG

    // Spielparameter definieren
    const int num_birds = 3;
    double gravity = 9.81;     // m/s^2
    int anim_freq = 10;        // Animationsgeschwindigkeit in Hertz
    double ground_floor = 5.0; // Lage des Erdbodens relativ zum unteren Bildschirmrand

    // Vogel und Schwein positionieren
    GameObject bird{5.0, ground_floor + 1.0, 2.0, 2.0};
    GameObject pig{20.0, ground_floor};

    // Array für Bilddaten anlegen
    char screen_buffer[30][40]{};
    int num_cols = sizeof(screen_buffer[0]) / sizeof(char);          // Anzahl Spalten im Array herausfinden
    int num_rows = sizeof(screen_buffer) / sizeof(screen_buffer[0]); // Anzahl Zeilen im Array herausfinden
    num_rows = min(num_rows, visible_rows);                          // Anzahl Zeilen auf sichtbaren Bereich beschränken

    // Äußere Schleife über alle Vögel
    int cnt_birds{0};
    while (cnt_birds < num_birds)
    {
        // Abschusswinkel in Grad abfragen
        double angle = 45 * M_PI / 180; // DEBUG
    
        // Abschussgeschwindigkeit in m/s abfragen
        double speed = 5.0; // DEBUG

        // zu nächstem Vogel wechseln
        ++cnt_birds;
    }

    // Terminal in Dauerschleife animieren
    double dt = 1.0 / anim_freq; // Animationsgeschwindigkeit in Sekunden
    int cnt_anim{0};
    while (bird.pos_y > ground_floor)
    {
        // Ausführung für Animationsdauer anhalten
        std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 * dt)));

        // Objektposition aktualisieren
        bird.pos_x += bird.v_x * dt;
        bird.v_y -= gravity * dt;
        bird.pos_y += bird.v_y * dt;

        int bird_col = bird.pos_x; // 1 Zelle entspricht 1m
        int bird_row = num_rows - bird.pos_y;
        int pig_col = pig.pos_x;
        int pig_row = num_rows - pig.pos_y;

        // Objekte "zeichnen"
        screen_buffer[bird_row][bird_col] = 'b';
        screen_buffer[pig_row][pig_col] = 'P';

        // Aktuelles Bild zeichnen
        int cnt_rows{0};
        while (cnt_rows < num_rows) // Schleife über alle Zeilen
        {
            int cnt_cols{0};
            while (cnt_cols < num_cols) // Schleife über alle Spalten
            {
                char output = screen_buffer[cnt_rows][cnt_cols] == 0 ? '.' : screen_buffer[cnt_rows][cnt_cols];
                cout << output;
                ++cnt_cols;
            }
            cout << endl; // Zeilenumbruch am Ende einer Zeile
            ++cnt_rows;
        }

    } // Ende der Animationsschleife

    return 0;
}
