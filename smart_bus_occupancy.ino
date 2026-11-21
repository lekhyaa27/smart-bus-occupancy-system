
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SENSOR1 6
#define SENSOR2 7

#define TOTAL_SEATS 40

int people = 0;
int totalEntered = 0;
int seatsLeft = TOTAL_SEATS;

int state = 0;
int prev1 = HIGH;
int prev2 = HIGH;

unsigned long startTime = 0;
unsigned long timeout = 1500;

bool ready = true;

void setup() {
  pinMode(SENSOR1, INPUT_PULLUP);
  pinMode(SENSOR2, INPUT_PULLUP);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Bus Occupancy");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  delay(2000);
  lcd.clear();
}

void displayData() {
  seatsLeft = TOTAL_SEATS - people;

  lcd.setCursor(0, 0);
  lcd.print("P:");
  lcd.print(people);
  lcd.print(" Seats:");
  lcd.print(seatsLeft);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("Boarded:");
  lcd.print(totalEntered);
  lcd.print("    ");

  Serial.print("People Inside: ");
  Serial.println(people);

  Serial.print("Total Boarded: ");
  Serial.println(totalEntered);

  Serial.print("Seats Left: ");
  Serial.println(seatsLeft);
  Serial.println("----------------");
}

void loop() {
  int s1 = digitalRead(SENSOR1);
  int s2 = digitalRead(SENSOR2);

  bool firstDetected = (prev1 == HIGH && s1 == LOW);
  bool secondDetected = (prev2 == HIGH && s2 == LOW);

  if (ready) {

    if (state == 0) {
      if (firstDetected && !secondDetected) {
        state = 1;
        startTime = millis();
      }
      else if (secondDetected && !firstDetected) {
        state = 2;
        startTime = millis();
      }
    }

    else if (state == 1 && secondDetected) {
      // Passenger entered: Sensor 1 followed by Sensor 2
      if (people < TOTAL_SEATS) {
        people++;
        totalEntered++;
      }

      displayData();
      state = 0;
      ready = false;
    }

    else if (state == 2 && firstDetected) {
      // Passenger exited: Sensor 2 followed by Sensor 1
      if (people > 0) {
        people--;
      }

      displayData();
      state = 0;
      ready = false;
    }

    if (state != 0 && millis() - startTime > timeout) {
      state = 0;
    }
  }

  if (!ready && s1 == HIGH && s2 == HIGH) {
    ready = true;
  }

  prev1 = s1;
  prev2 = s2;

  delay(20);
}
