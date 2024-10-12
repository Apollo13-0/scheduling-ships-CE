// Arduino mega 2560

// Decoder D,C,B,A -> 24,23,22,25
// Decoder D,C,B,A -> 28,27,26,29
// Led indicador de barco siguiente derecho -> 30,31,32
// Led indicador de barco siguiente izquierdo -> 33,34,35
// 25% canal -> 36,37,38
// 50% canal -> 39,40,41
// 75% canal -> 42,43,44
// 100% canal -> 45,46,47
// Letrero -> 48

// Barco tipo 0 -> Normal (rojo)
// Barco tipo 1 -> Pesquero (verde)
// Barco tipo 2 -> Patrulla (azul)

// lista de pines
int digitalPin[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48};
int leftOcean[] = {};
int rigthOcean[] = {};

// test displayChannel
int len = 20;
int boat = 0;
int nextBoat = 1;
int numBoats = 5;

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

void displayNextBoat(char ocean, int type) {
  int pinR = (ocean == 'L') ? 30 : 33;
  int pinG = (ocean == 'L') ? 31 : 34;
  int pinB = (ocean == 'L') ? 32 : 35;

  if (type == 0) {
    digitalWrite(pinR, LOW); 
    digitalWrite(pinG, HIGH);
    digitalWrite(pinB, HIGH);
  } else if (type == 1) {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinG, LOW); 
    digitalWrite(pinB, HIGH);
  } else if (type == 2) {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinB, LOW);
  } else {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinB, HIGH);
  }
}

void displayChannel(int boatType, int pos, int channelLen, int sentido) {
  int pinR = 0;
  int pinG = 0;
  int pinB = 0;

  int red = (boatType == 0) ? 0 : 1;
  int green = (boatType == 1) ? 0 : 1;
  int blue = (boatType == 2) ? 0 : 1;

  // Sentido del canal
  digitalWrite(48, sentido == 0 ? HIGH : LOW);

  // Calcular el porcentaje recorrido por el barcon en el canal usando pos y channelLen
  int percentage = (pos * 100) / channelLen;
  if (percentage <= 25) {
    digitalWrite(36, red); 
    digitalWrite(37, green);
    digitalWrite(38, blue);
  } else if (percentage <= 50) {
    digitalWrite(39, red); 
    digitalWrite(40, green);
    digitalWrite(41, blue);
  } else if (percentage <= 75) {
    digitalWrite(42, red); 
    digitalWrite(43, green);
    digitalWrite(44, blue);
  } else {
    digitalWrite(45, red);
    digitalWrite(46, green);
    digitalWrite(47, blue);
  }
}

void cleanChannel() {
  for (int i = 36; i < 48; i++) {
    digitalWrite(i, 1);
  }
}

void setup() {
  
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < 26; i++) {
    pinMode(digitalPin[i], OUTPUT);
  }

  for (int i = 30; i < 48; i++) {
    digitalWrite(i, 1);
  }


}

void loop() {
  // Read serial data
  if (Serial.available() > 0) {
    char data = Serial.read();

    // Updata global data
    // leftOcean
    // rigthOcean
    // channelLen
    
  }

  
  displayNumBoats('R', 5);
  
  for (int i = 0; i < len; i++) {
    displayNumBoats('L', numBoats);
    displayNextBoat('L', nextBoat);
    displayNextBoat('R', 2);
    displayChannel(boat, i, len, 0);
    delay(1000);
    
  }
  numBoats--;

  cleanChannel();
}
