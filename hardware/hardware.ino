// Lista de pines
int digitalPin[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48};

// Variables
int leftOceanNumBoats; 
int rigthOceanNumBoats;
char leftOceanNextBoat;
char rigthOceanNextBoat;
int channelLen = 4;
char channel[4];
int sentido;

// Función para convertir un número a binario en 4 bits
void numeroABinario4Bits(int numero, int binario[4]) {
  if (numero < 0 || numero > 15) {
    Serial.println("Error: El número debe estar entre 0 y 15.");
    return;
  }

  for (int i = 0; i < 4; i++) {
    binario[i] = (numero >> (3 - i)) & 1;  // Cambiamos el orden
  }
}

// Función para mostrar el número de barcos
void displayNumBoats(char ocean, int num) {
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

// Función para mostrar el siguiente barco
void displayNextBoat(char ocean, char type) {
  int pinR = (ocean == 'L') ? 30 : 33;
  int pinG = (ocean == 'L') ? 31 : 34;
  int pinB = (ocean == 'L') ? 32 : 35;

  if (type == 'N') {
    digitalWrite(pinR, LOW); 
    digitalWrite(pinG, HIGH);
    digitalWrite(pinB, HIGH);
  } else if (type == 'E') {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinG, LOW); 
    digitalWrite(pinB, HIGH);
  } else if (type == 'P') {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinB, LOW);
  } else {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinB, HIGH);
  }
}

// Función para mostrar el canal y su dirección
void displayChannel(char channel[], int sentido) {
  int red1 = (channel[0] == 'N') ? 0 : 1;
  int green1 = (channel[0] == 'E') ? 0 : 1;
  int blue1 = (channel[0] == 'P') ? 0 : 1;

  int red2 = (channel[1] == 'N') ? 0 : 1;
  int green2 = (channel[1] == 'E') ? 0 : 1;
  int blue2 = (channel[1] == 'P') ? 0 : 1;

  int red3 = (channel[2] == 'N') ? 0 : 1;
  int green3 = (channel[2] == 'E') ? 0 : 1;
  int blue3 = (channel[2] == 'P') ? 0 : 1;

  int red4 = (channel[3] == 'N') ? 0 : 1;
  int green4 = (channel[3] == 'E') ? 0 : 1;
  int blue4 = (channel[3] == 'P') ? 0 : 1;

  // Sentido del canal
  digitalWrite(48, sentido);

  digitalWrite(36, red1); 
  digitalWrite(37, green1);
  digitalWrite(38, blue1);

  digitalWrite(39, red2); 
  digitalWrite(40, green2);
  digitalWrite(41, blue2);

  digitalWrite(42, red3); 
  digitalWrite(43, green3);
  digitalWrite(44, blue3);

  digitalWrite(45, red4);
  digitalWrite(46, green4);
  digitalWrite(47, blue4);
}

// Función para limpiar el canal
void cleanChannel() {
  for (int i = 36; i < 48; i++) {
    digitalWrite(i, 1);
  }
}

void setup() {
  Serial.begin(9600);

  // Configurar todos los pines
  for (int i = 0; i < 26; i++) {
    pinMode(digitalPin[i], OUTPUT);
  }

  for (int i = 30; i < 48; i++) {
    digitalWrite(i, 1);
  }
}
void loop() {
  // Leer datos del puerto serie
  if (Serial.available() > 0) {
    // Leer los datos en un String
    String data = Serial.readStringUntil('\n'); // Leer hasta un salto de línea
    data.trim();
    // Verificar si los datos recibidos son de la longitud correcta
    Serial.println(data.length());
    if (data.length() == 12) {
      // Extraer los valores del string
      leftOceanNumBoats = data.charAt(0) - '0';
      leftOceanNextBoat = data.charAt(1); // Extraer el segundo carácter
      displayNextBoat('L', leftOceanNextBoat);
      // Mostrar el carácter para depurar
      Serial.print("Valor de leftOceanNextBoat: ");
      Serial.println(data.charAt(1));
      displayNextBoat('L', data.charAt(1));

      // Copiar el canal (caracteres en las posiciones 3 a 6)
      data.substring(3, 7).toCharArray(channel, 5);

      sentido = data.charAt(8) - '0';
      rigthOceanNumBoats = data.charAt(10) - '0';
      rigthOceanNextBoat = data.charAt(11);

      // Mostrar los datos en el monitor serie para depuración
      Serial.println("Datos recibidos:");
      Serial.println(data);
      Serial.println("Número de barcos en el océano izquierdo:");
      Serial.println(leftOceanNumBoats);
      Serial.println("Próximo barco en el océano izquierdo:");
      Serial.println(leftOceanNextBoat); // Aquí mostrar de nuevo el valor
      Serial.println("Canal:");
      Serial.println(channel);
      Serial.println("Sentido:");
      Serial.println(sentido);
      Serial.println("Número de barcos en el océano derecho:");
      Serial.println(rigthOceanNumBoats);
      Serial.println("Próximo barco en el océano derecho:");
      Serial.println(rigthOceanNextBoat);
    } else {
      Serial.println("Error: Longitud de datos incorrecta");
    }
  }

   // Mostrar barcos y canal
  displayNumBoats('R', rigthOceanNumBoats);
  displayNumBoats('L', leftOceanNumBoats);
  displayNextBoat('R', rigthOceanNextBoat);
  //displayNextBoat('L', leftOceanNextBoat);
  displayChannel(channel, sentido);
}
