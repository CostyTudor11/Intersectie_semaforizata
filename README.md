# Intersecție semaforizată controlată cu Arduino Nano

## Scopul proiectului
Proiectul urmărește simularea unei intersecții rutiere cu semafoare funcționale, utilizând o placă Arduino Nano pentru controlul unor semafoare led.

## Lista componentelor
- Arduino Nano – 1 buc
- Semafoare- 7 buc
- Rezistențe 220Ω – 2 buc
- Breadboard – 1 buc
- Fire de conexiune – aprox. 50 buc
- Butoane pentru pietoni – 2 buc 
- Senzor ultrasonic //folosirt pentru a detecta aparitia unui tramvai

## Schema electrică și conectare
![WhatsApp Image 2025-05-30 at 21 18 00_718189c9](https://github.com/user-attachments/assets/2c0a9219-68b2-480b-8fec-cadb259a290d)
![WhatsApp Image 2025-05-30 at 21 18 00_0ecdf10a](https://github.com/user-attachments/assets/f745b463-60fe-4767-b7b5-ed0ee7eda871)

## Descrierea funcționării
Am o functie stareINITIALA in care semaforul VERDE_MASINI este verde iar toate celelalte rosii. Aceasta functie este activa mereu daca nu intervine nimic din exterior.
Am o functie distantaTramvaiCM care masoara distanta folosind senzorul ultrasonic, daca tramvaiul se apropie la o distanta mai mica de 6 cm se activeaza functia semaforTramvai in care e verde intermitent de 3 ori, apoi galben 2s si rosu 10s, dupa cele 10 secunde daca tramvaiul a trecut se revine la stareaINITIALA.
Mai am o functie care la apasarea unuia dintre cele doua butoane se activeaza : pentru inca 3s ramane stareaInitiala, apoi 2s gablen si mai apoi 10s rosu.

## Testare și rezultate
Am incarcat codul pe placuta, si a functionat exact cum ma asteptam.

## Concluzii și posibile îmbunătățiri
Pentru mine a fost prima data cand am lucrat cu un arduino , a fost o experinta foarte placuta.
Se poate imbunatatii prin adaugarea unei functii care sa faca semafoarele rosii la aparitia unei masini de urgenta, asta se poate face folosind un modul bluetooth.
Se poate adauga un senzor de detectie a pietonilor sa nu mai fie nevoie sa apese pe buton.

## Bibliografie și surse
