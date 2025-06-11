// RAMPS 1.4 Pinbelegung (Arduino Mega)
#define X_MIN_PIN     3
#define X_MAX_PIN     2
#define X_STEP_PIN   54
#define X_DIR_PIN    55
#define X_ENABLE_PIN 38

#define Y_MIN_PIN    14
#define Y_MAX_PIN    15
#define Y_STEP_PIN   60
#define Y_DIR_PIN    61
#define Y_ENABLE_PIN 56

#define STEP_DELAY   50  // µs delay (anpassen je nach Treiber und Geschwindigkeit)
#define DIPPING_TIME  1  // Sekunden (anpassen wie lange die Probe eingetaucht wird)
#define NUM_CYCLES  100  // Anzahl der Thermoschockzyklen

int iteration = 0;

void setup() {
  Serial.begin(115200);

  // Endstop Pins als Input mit Pullup konfigurieren
  pinMode(X_MIN_PIN, INPUT_PULLUP);
  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MIN_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);

  // Stepper Pins konfigurieren
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);

  // Enable Pins konfigurieren und Motoren aktivieren
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  digitalWrite(X_ENABLE_PIN, LOW); // Motor X aktivieren
  digitalWrite(Y_ENABLE_PIN, LOW); // Motor Y aktivieren


  Serial.println("Endstop Status Monitor gestartet...");

  Serial.println("Home Y...");
  y_min();

  Serial.println("Home X...");
  x_min();
}

void loop() {
  if(iteration < NUM_CYCLES){
    String loop_status = "Loop N° " + String(iteration);
    Serial.println(loop_status);
    
    thermoschock();
    iteration++;
  }
  else if(iteration == NUM_CYCLES){
    Serial.println("Cycles complete!");
    iteration++;
  }
}

void thermoschock(){
  x_max();
  y_max();
  delay(DIPPING_TIME*1000);
  y_min();

  x_min();
  y_max();
  delay(DIPPING_TIME*1000);
  y_min();
}

void y_min(){
  digitalWrite(Y_DIR_PIN, LOW);  // Richtung negativ
  while (digitalRead(Y_MIN_PIN) == HIGH) { // Noch nicht ausgelöst
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY);
  }
  Serial.print("↑");
}

void y_max(){
  digitalWrite(Y_DIR_PIN, HIGH);  // Richtung negativ
  while (digitalRead(Y_MAX_PIN) == HIGH) { // Noch nicht ausgelöst
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY);
  }
  Serial.print("↓");
}

void x_min(){
  digitalWrite(X_DIR_PIN, LOW);  // Richtung negativ
  while (digitalRead(X_MIN_PIN) == HIGH) { // Noch nicht ausgelöst
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY);
  }
  Serial.print("←");
}

void x_max(){
  digitalWrite(X_DIR_PIN, HIGH);  // Richtung negativ
  while (digitalRead(X_MAX_PIN) == HIGH) { // Noch nicht ausgelöst
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY);
  }
  Serial.print("→");
}