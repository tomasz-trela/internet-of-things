#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

void setup() {
  Serial.begin(9600);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 0);
  analogWrite(LED_BLUE, 0);

  Serial.println("--- Sterowanie diodami LED ---");
  Serial.println("Wpisz komende w formacie R,G,B (np. 255,0,128) i nacisnij Enter.");
  Serial.println("R, G, B to wartosci jasnosci od 0 do 255.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    parseCommand(command);
  }
}

void parseCommand(String command) {
  int firstComma = command.indexOf(',');
  int secondComma = command.indexOf(',', firstComma + 1);

  if (firstComma > 0 && secondComma > 0) {
    String r_str = command.substring(0, firstComma);
    String g_str = command.substring(firstComma + 1, secondComma);
    String b_str = command.substring(secondComma + 1);

    int r_val = r_str.toInt();
    int g_val = g_str.toInt();
    int b_val = b_str.toInt();

    r_val = constrain(r_val, 0, 255);
    g_val = constrain(g_val, 0, 255);
    b_val = constrain(b_val, 0, 255);

    analogWrite(LED_RED, r_val);
    analogWrite(LED_GREEN, g_val);
    analogWrite(LED_BLUE, b_val);

    Serial.print("OK. Ustawiono: Czerwony=");
    Serial.print(r_val);
    Serial.print(", Zielony=");
    Serial.print(g_val);
    Serial.print(", Niebieski=");
    Serial.println(b_val);
  } else {
    Serial.print("Blad! Nieprawidlowy format komendy: '");
    Serial.print(command);
    Serial.println("'. Uzyj formatu R,G,B (np. 255,0,128).");
  }
}