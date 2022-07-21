# Praktikum 4

### Bugfixes, die wir nach dem letzten Praktikum gemacht haben:

- Wenn ein Zombie stirbt, wird sein QLabel entfernt
- Kampf zwischen NPC und Hero funktioniert
- Levelchanger funktioniert

# Praktikum 5

### Aufgabe 1

- wir verwenden einen ungerichteten Graphen
- Für den Zombie mit dem AttackController verwenden wir ein eigene QPixmap (entnommen vom Herrn Roths Moodle)
- Implementierung des Graphen stammt aus Foliensatz
- Als Algorithmus verwenden wir eine einfache Breitensuche auch aus dem Foliensatz
- Für die einzelnen Aktionen der Wegsuche verwenden wir eine Binäre Suche (Graph::findKnoten(int row, int col))

### Aufgabe 2

- Wir haben eine neue Klasse "Levelverwaltung" für das Laden/Speichern der Levels implementiert
- Die level1.json und level2.json sind im Projektverzeichnis drin
- In der Main müssen Sie die Pfade anpassen 
- **Beim ersten Aufruf muss ein neues Spiel generiert werden**
- Das Spiel kann über dem Button im Spiel gespeichert werden, diese Dateien heißen "backup" + index + ".json"
  - Diese liegen wahrscheinlich im Build Verzeichnis
  - Wir haben die single include Datei (json.hpp) von nlohmann für das einlesen und einspeichern von .json Files genutzt