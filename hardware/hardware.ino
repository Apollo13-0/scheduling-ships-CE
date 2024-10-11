// Arduino mega 2560
// Pin digital 22,23, 24 led rgb #1
// Pin digital 25,26, 27 led rgb #2
// Pin digital 28,29, 30 led rgb #3
// Pin digital 31,32, 33 led rgb #4
// Pin digital 34,35, 36 led rgb #5
// Pin digital 37,38, 39 led rgb #6
// Pin digital 40,41, 42, 43 decoder
// Pin digital 44,45, 46, 47 decoder

// Decoder D,C,B,A -> 24,23,22,25
// Decoder D,C,B,A -> 28,27,26,29

// lista de pines
int digitalPin[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};
int leftOcean[] = {};
int rigthOcean[] = {};

void numeroABinario4Bits(int numero, int binario[4]) {

  if (numero < 0 || numero > 15) {
    Serial.println("Error: El número debe estar entre 0 y 15.");
    return;
  }

  for (int i = 0; i < 4; i++) {
    binario[i] = (numero >> (3 - i)) & 1;  // Cambiamos el orden
  }
}

void displayNumBoats(char ocean,int num) {
  int binario[4];
  numeroABinario4Bits(num, binario);

  int pinD = (ocean == 'L') ? 24 : 28;
  int pinC = (ocean == 'L') ? 23 : 27;
  int pinB = (ocean == 'L') ? 22 : 26;
  int pinA = (ocean == 'L') ? 25 : 29;

  digitalWrite(pinD, binario[0]); // D
  digitalWrite(pinC, binario[1]); // C
  digitalWrite(pinB, binario[2]); // B
  digitalWrite(pinA, binario[3]); // A

}

void setup() {
  
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < 26; i++) {
    pinMode(digitalPin[i], OUTPUT);
  }

}

void loop() {
  int binario[4];
  
  for (int i = 0; i < 10; i++) {
    displayNumBoats('L', i);
    displayNumBoats('R', i);

    delay(1000);
  }
}
