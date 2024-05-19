#define led2 3
#define button 10
#define debounceDelay 20 // Ajuste o delay conforme necessário (em milissegundos)

int lastButtonState = LOW; // Estado anterior do botão (HIGH devido ao pull-up)
int currentButtonState;      // Estado atual do botão
unsigned long lastDebounceTime = 0; // Tempo da última alteração de estado

void setup() {
  Serial.begin(9600);
  pinMode(led2, OUTPUT);
  pinMode(button, INPUT); // Usa resistor de pull-up interno
  digitalWrite(led2, HIGH); // LED aceso por padrão // Buzzer ligado por padrão
}

void loop() {
  int reading = digitalRead(button);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Se o tempo de debounce passou, considere a leitura estável
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Se o estado atual é diferente do estado armazenado, altere-o
    if (reading != currentButtonState) {
      currentButtonState = reading;

      // Apenas executa a ação quando o botão é pressionado (LOW, devido ao pull-up)
      if (currentButtonState == LOW) {
        digitalWrite(led2, HIGH); // Apaga o LED
      } else {
        digitalWrite(led2, LOW); // Mantém o LED aceso
        Serial.println("Medicação Tomada");
      }
    }
  }

  // Armazena a leitura como último estado
  lastButtonState = reading;
}
