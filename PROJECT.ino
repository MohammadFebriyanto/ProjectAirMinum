byte indikator = 13;

byte sensorInt = 0; 
byte flowsensor = 2;
const int button = 4;

float konstanta = 4.5; //konstanta flow meter

volatile byte pulseCount;

float debit;
unsigned int flowmlt;
unsigned long totalmlt;

unsigned long oldTime;

void setup()
{

// Inisialisasi port serial
Serial.begin(9600);

pinMode(indikator, OUTPUT);
digitalWrite(indikator, HIGH);

pinMode(button, INPUT);

pinMode(flowsensor, INPUT);
digitalWrite(flowsensor, HIGH);

pulseCount = 0;
debit = 0.0;
flowmlt = 0;
totalmlt = 0;
oldTime = 0;

attachInterrupt(sensorInt, pulseCounter, FALLING);
}


void loop()
{
if((millis() - oldTime) > 1000) { 
  detachInterrupt(sensorInt);
  debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / konstanta;
  oldTime = millis();
  flowmlt = (debit / 60) * 1000;
  totalmlt += flowmlt;

  unsigned int frac;
  if (digitalRead(button) == HIGH) {
    Serial.print("MENGHITUNG TOTAL AIR ANDA");
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.println(".");
    delay(500);
    /*Serial.print("Debit air: ");
    Serial.print(int(debit));
    Serial.print("L/min");
    Serial.print("\t");*/

    Serial.print("Volume: "); 
    Serial.print(totalmlt);
    Serial.println("mL");
    Serial.println();
    Serial.println();
    totalmlt=0;
    }
  pulseCount = 0;

  attachInterrupt(sensorInt, pulseCounter, FALLING);

  if ((debit==0) && (millis()-oldTime > 5000))  {
     Serial.println("============"); 
     totalmlt=0;
  }
  }


}

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
