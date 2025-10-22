// Escala dó-ré-mi-fá-sol-lá-si (aprox. oitava 4)
const int SCALE_FREQS[] = {262, 294, 330, 349, 392, 440, 494};

const int BUZZER_PIN = 8;
const int BUTTON_PIN = 2;     // com INPUT_PULLUP
const int POT_PIN    = A0;    // controla duração
const int LED_PIN    = 13;

class Buzzer {
  int pin;
public:
  Buzzer(int p): pin(p) { pinMode(pin, OUTPUT); }
  void play(int freq, int durMs) {
    tone(pin, freq, durMs);
    delay(durMs); // espera terminar
    noTone(pin);
  }
};

class Scale {
  const int* notes;
  int size;
  int idx;
public:
  Scale(const int* arr, int n): notes(arr), size(n), idx(0) {}
  int next() {
    int f = notes[idx];
    idx = (idx + 1) % size;
    return f;
  }
  void reset(){ idx = 0; }
};

class Button {
  int pin;
  bool lastStable = HIGH;
  unsigned long lastChange = 0;
  const unsigned long debounce = 30; // ms
public:
  Button(int p): pin(p) { pinMode(pin, INPUT_PULLUP); }
  bool pressed() {
    bool reading = digitalRead(pin);
    if (reading != lastStable && (millis() - lastChange) > debounce) {
      lastChange = millis();
      lastStable = reading;
      // ativo em LOW (pullup): transição HIGH->LOW é clique
      if (lastStable == LOW) return true;
    }
    return false;
  }
};

Buzzer buzzer(BUZZER_PIN);
Scale  scale(SCALE_FREQS, sizeof(SCALE_FREQS)/sizeof(int));
Button btn(BUTTON_PIN);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  // Dica: abra o Monitor Serial se quiser mensagens
  Serial.begin(9600);
  Serial.println("Pressione o botao para tocar a proxima nota.");
}

void loop() {
  if (btn.pressed()) {
    // lê o potenciômetro e mapeia para 120..800 ms
    int pot = analogRead(POT_PIN);
    int dur = map(pot, 0, 1023, 120, 800);

    int freq = scale.next();

    digitalWrite(LED_PIN, HIGH);
    buzzer.play(freq, dur);
    digitalWrite(LED_PIN, LOW);

    Serial.print("Freq: "); Serial.print(freq);
    Serial.print(" Hz - Dur: "); Serial.print(dur);
    Serial.println(" ms");
  }
}
