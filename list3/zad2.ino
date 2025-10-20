#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

const unsigned long redPeriod = 900;
const unsigned long greenPeriod = 1000;
const unsigned long bluePeriod = 1100;

unsigned long redLastChange = 0;
unsigned long greenLastChange = 0;
unsigned long blueLastChange = 0;

int redState = LOW;
int greenState = LOW;
int blueState = LOW;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - redLastChange >= redPeriod) {
    redLastChange = currentTime;
    redState = (redState == LOW) ? HIGH : LOW;
    digitalWrite(LED_RED, redState);
  }

  if (currentTime - greenLastChange >= greenPeriod) {
    greenLastChange = currentTime;
    greenState = (greenState == LOW) ? HIGH : LOW;
    digitalWrite(LED_GREEN, greenState);
  }

  if (currentTime - blueLastChange >= bluePeriod) {
    blueLastChange = currentTime;
    blueState = (blueState == LOW) ? HIGH : LOW;
    digitalWrite(LED_BLUE, blueState);
  }

}