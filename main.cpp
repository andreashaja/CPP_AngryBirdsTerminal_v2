#include<iostream>
#include <chrono>
#include <thread>

using namespace std; 

struct Object {
  double pos_x{0.0};
  double pos_y{0.0};
  double size{0.0}; // Durchmesser des umschließenden Kreises
  double weight{0.0}; // Gewicht in g
};
 
int main()
{ 
  // Anzahl der sichtbaren Zeilen im Terminal herausfinden
  int cnt_rows{0};
  while(cnt_rows<100)
  {
    cout << "o" << endl;
    ++cnt_rows;
  }
  cout << "Bitte gib die Anzahl der sichtbaren 'o' im Terminal ein :";
  int visible_rows{0};
  cin >> visible_rows; 

  // Array für Bilddaten anlegen
  char screen_buffer[30][40]{};
  int num_cols = sizeof(screen_buffer[0]) / sizeof(char); // Anzahl Spalten im Array herausfinden
  int num_rows = sizeof(screen_buffer) / sizeof(screen_buffer[0]); // Anzahl Zeilen im Array herausfinden
  num_rows = min(num_rows, visible_rows); // Anzahl Zeilen auf sichtbaren Bereich beschränken

  // Spielparameter definieren
  const int num_birds = 3;
  double gravity = 9.81; // m/s^2
  int anim_freq = 2; // Animationsgeschwindigkeit in Hertz
  int anim_millis = 1000*1.0/anim_freq; // Animationsgeschwindigkeit in Millisekunden

  // Äußere Schleife über alle "Leben"
  int cnt_birds{0};
  while(cnt_birds<num_birds)
  {
    // Abschusswinkel in Grad abfragen

    // Abschussgeschwindigkeit in m/s abfragen

    
  }


  // Terminal in Dauerschleife animieren
  int cnt_anim{0};
  while(1)
  {
    // Ausführung für Animationsdauer anhalten
    std::this_thread::sleep_for(std::chrono::milliseconds(anim_millis));

    // Objekte animieren (Baustelle)
    cnt_anim = cnt_anim<num_rows-1 ? cnt_anim+1 : num_rows-1;
    screen_buffer[cnt_anim][0] = 'x'; 

    // Aktuelles Bild zeichnen
    int cnt_rows{0};
    while(cnt_rows<num_rows) // Schleife über alle Zeilen
    {
      int cnt_cols{0};
      while(cnt_cols<num_cols) // Schleife über alle Spalten
      {
        cout << screen_buffer[cnt_rows][cnt_cols];
        ++cnt_cols;
      }
      cout << endl; // Zeilenumbruch am Ende einer Zeile
      ++cnt_rows;
    }
    
  } // Ende der Animationsschleife
  


  return 0;
} 