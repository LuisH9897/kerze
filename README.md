# LED-Steuerung mit Erschütterungserkennung

Dieses Projekt demonstriert die Ansteuerung einer RGB-LED mit verschiedenen Betriebsarten, die über eine Erschütterungserkennung (z. B. Drahtfalle oder Taster) gewechselt werden können.  
Die Farbsteuerung erfolgt dabei über den HSV-Farbraum und unterschiedliche Effekte (Kerzenflackern, Farbwechsel, Weißlicht).

---

## Funktionen
- **Betriebsarten** (umschaltbar über Erschütterung/Taster an Pin 4):
  1. **Alles aus**  
  2. **Kerzenflackern** (Simulation mithilfe von Sinusfunktionen und Zufallsfaktoren)  
  3. **Party-Modus** (kontinuierlicher Farbwechsel im HSV-Farbraum)  
  4. **Dauerhaft Weiß**  

- **Erschütterungserkennung:**  
  Erkennt Änderungen am Eingangssignal (Pin 4). Nach mehreren Erschütterungen wird die Betriebsart zyklisch weitergeschaltet.

- **LED-Steuerung:**  
  - PWM-Ausgabe über die Pins **9 (Rot)**, **10 (Grün)** und **11 (Blau)**.  
  - Farben werden entweder direkt oder über den HSV-Farbraum berechnet.  

---

## Hardware
- **RGB-LED** (gemeinsame Kathode oder Anode, je nach Anpassung).  
- **Pins:**  
  - Rot: **9**  
  - Grün: **10**  
  - Blau: **11**  
  - Eingang für Erschütterung/Drahtfalle: **4** (mit `INPUT_PULLUP`)  

- **Erschütterungssensor:**  
  - Für den Anfang wurde ein **Taster** verwendet (Pin 4 gegen GND).  
  - Für eine realistischere Darstellung kann eine **Drahtfalle** gebaut werden:  
    - z. B. ein **Haken** und zwei **Ösen**, die durch eine Bewegung den Kontakt zwischen **Pin 4** und **GND** herstellen oder unterbrechen.  

---

## Hinweise
- Die `delay(25)` in der Erschütterungserkennung sorgt für eine sanfte Ablaufgeschwindigkeit.  
- Die Zufallsfaktoren werden alle ~25 Sekunden neu berechnet, um das Flackern natürlicher wirken zu lassen.  
- Für die **Drahtfalle** ist es sinnvoll, stabile Lötpunkte an Pin 4 und GND zu verwenden.  
