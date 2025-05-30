#define VERDE_MASINI 2
#define GALBEN_MASINI 3
#define ROSU_MASINI 4
#define VERDE_TRAMVAI 7
#define ROSU_TRAMVAI 8
#define VERDE_PIETONI 10
#define ROSU_PIETONI 9
#define BUTON_PIETONI2 12
#define BUTON_PIETONI1 11
#define TRIG_ULTRASONIC 5
#define ECOU_ULTRASONIC 6

void setup() {
    pinMode(VERDE_MASINI, OUTPUT);
    pinMode(GALBEN_MASINI, OUTPUT);
    pinMode(ROSU_MASINI, OUTPUT);
    pinMode(VERDE_TRAMVAI, OUTPUT);
    pinMode(ROSU_TRAMVAI, OUTPUT);
    pinMode(VERDE_PIETONI, OUTPUT);
    pinMode(ROSU_PIETONI, OUTPUT);
    pinMode(BUTON_PIETONI1, INPUT);
    pinMode(BUTON_PIETONI2, INPUT);
    pinMode(TRIG_ULTRASONIC, OUTPUT);
    pinMode(ECOU_ULTRASONIC, INPUT);
    Serial.begin(9600);

    stareInitiala();
}

void loop() {
    // 1. Prioritate tramvai
    if (distantaTramvaiCM() < 6) {
        semaforTramvai();
        return; // după tramvai, repornește ciclul
    }

    // 2. Prioritate pietoni dacă nu vine tramvai
    if (digitalRead(BUTON_PIETONI1) == HIGH || digitalRead(BUTON_PIETONI2) == HIGH) {
        semaforPietoni();
        return; // după pietoni, repornește ciclul
    }

    // 3. Stare inițială (mașini verde, restul roșu)
    stareInitiala();
    delay(200);
}

void stareInitiala() {
    digitalWrite(VERDE_MASINI, HIGH);
    digitalWrite(GALBEN_MASINI, LOW);
    digitalWrite(ROSU_MASINI, LOW);
    digitalWrite(ROSU_PIETONI, HIGH);
    digitalWrite(VERDE_PIETONI, LOW);
    digitalWrite(ROSU_TRAMVAI, HIGH);
    digitalWrite(VERDE_TRAMVAI, LOW);
}

// Functie pentru distanța masurată cu ultrasonic
long distantaTramvaiCM() {
    long duration, cm;
    digitalWrite(TRIG_ULTRASONIC, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_ULTRASONIC, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_ULTRASONIC, LOW);
    duration = pulseIn(ECOU_ULTRASONIC, HIGH, 20000); // timeout 20ms
    if (duration == 0) return 1000; // dacă nu răspunde, consideră că nu e tramvai
    cm = duration / 29 / 2;
    return cm;
}

// Secvența semafor pentru tramvai
void semaforTramvai() {
    //Intermitent verde
    for (int i = 0; i < 3; i++) {
        digitalWrite(VERDE_MASINI, LOW);
        delay(500);
        digitalWrite(VERDE_MASINI, HIGH);
        delay(500);
    }
    // Mașini galben 2s, apoi roșu 10s (cât timp tramvaiul trece)
    digitalWrite(VERDE_MASINI, LOW);
    digitalWrite(GALBEN_MASINI, HIGH);
    delay(2000);

    digitalWrite(GALBEN_MASINI, LOW);
    digitalWrite(ROSU_MASINI, HIGH);
    digitalWrite(ROSU_TRAMVAI, LOW);
    digitalWrite(VERDE_TRAMVAI, HIGH);
    delay(10000);
    // Cât timp tramvaiul e detectat aproape, menține roșu mașini, verde tramvai
    while (distantaTramvaiCM() < 6) {
        delay(200);
    }

    delay(5000); // scurtă pauză după ce tramvaiul a trecut

    // Tramvai a trecut, revii la starea inițială
    digitalWrite(VERDE_TRAMVAI, LOW);
    digitalWrite(ROSU_TRAMVAI, HIGH);
    digitalWrite(ROSU_MASINI, LOW);
    digitalWrite(VERDE_MASINI, HIGH);
}

// Secvență semafor pentru pietoni
void semaforPietoni() {
    // 1. Mai stă 3 secunde starea inițială
    stareInitiala();
    delay(3000);

    // 2. Verde mașini intermitent de 3 ori (~0.5s on/off)
    for (int i = 0; i < 3; i++) {
        digitalWrite(VERDE_MASINI, LOW);
        delay(500);
        digitalWrite(VERDE_MASINI, HIGH);
        delay(500);
    }

    // 3. Galben mașini 2s
    digitalWrite(VERDE_MASINI, LOW);
    digitalWrite(GALBEN_MASINI, HIGH);
    delay(2000);

    // 4. Roșu mașini 10s + verde pietoni 10s
    digitalWrite(GALBEN_MASINI, LOW);
    digitalWrite(ROSU_MASINI, HIGH);
    digitalWrite(ROSU_PIETONI, LOW);
    digitalWrite(VERDE_PIETONI, HIGH);
    delay(10000);

    // 5. Revii la starea inițială
    stareInitiala();
}