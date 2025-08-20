// DAVI TIBURCIO; ENZO GABRIEL; PEDRO GABRIEL
// CURSO TÉCNICO EM ELETRÔNICA 2ºANO

#include <Servo.h>

int ledvermelho = 10;
int ledverde = 11;
int rebolaagachado = 2;
int pinoDoServo = 9;
int displaya = 3;
int displayb = 4;
int displayc = 5;
int displayd = 6;
int displaye = 7;
int displayf = 8;
int displayg = 12;

int PT = A0;
int A1_ant = 0;
int A2_ant = 0;
int num = 0;
int brilho = 0;
int presenca = 0;

Servo meuServo;

void setup() {
  pinMode(ledvermelho, OUTPUT);
  pinMode(ledverde, OUTPUT);

  pinMode(displaya, OUTPUT);
  pinMode(displayb, OUTPUT);
  pinMode(displayc, OUTPUT);
  pinMode(displayd, OUTPUT);
  pinMode(displaye, OUTPUT);
  pinMode(displayf, OUTPUT);
  pinMode(displayg, OUTPUT);

  pinMode(rebolaagachado, INPUT);
  pinMode(A1, INPUT); // Assumindo que A1 e A2 são pinos definidos pelo Arduino
  pinMode(A2, INPUT);

  meuServo.attach(pinoDoServo);
  meuServo.write(0);

  Serial.begin(9600);
}

void loop() {
  // Adiciona os valores de pressão para os botões (+10 e -11)
  if (digitalRead(A1) == HIGH) {
    if (A1_ant == LOW) {
      num += 10;
      A1_ant = HIGH;
    }
  } else {
    A1_ant = LOW;
  }

  if (digitalRead(A2) == HIGH) {
    if (A2_ant == LOW) {
      num -= 11;
      A2_ant = HIGH;
    }
  } else {
    A2_ant = LOW;
  }

  // Contador da variável para desabilitar o circuito
  Serial.print("CONTADOR DA VARIAVEL ");
  Serial.println(num);
  delay(500);

  // Identifica o brilho dos LEDs como um valor variável, com base no potenciômetro
  int leituraPot = analogRead(PT);
  brilho = map(leituraPot, 0, 1023, 0, 255);
  presenca = digitalRead(rebolaagachado);

  if (presenca == HIGH) {
    analogWrite(ledvermelho, brilho);
    analogWrite(ledverde, 0);
    Serial.println("DETECDANDO PRESENÇA"); // Detecção de movimento

    // Timer
    if (meuServo.read() == 0) {
      Serial.print("RESTAM ");
      
      // 3
      digitalWrite(displaya, HIGH);
      digitalWrite(displayb, HIGH);
      digitalWrite(displayc, HIGH);
      digitalWrite(displayd, HIGH);
      digitalWrite(displayg, HIGH);
      digitalWrite(displaye, LOW);
      digitalWrite(displayf, LOW);
      Serial.println("3");
      delay(1000);
      
      // 2
      digitalWrite(displayc, LOW);
      digitalWrite(displaya, HIGH);
      digitalWrite(displayb, HIGH);
      digitalWrite(displayd, HIGH);
      digitalWrite(displaye, HIGH);
      digitalWrite(displayg, HIGH);
      Serial.println("2");
      delay(1000);
      
      // 1
      digitalWrite(displaya, LOW);
      digitalWrite(displayd, LOW);
      digitalWrite(displaye, LOW);
      digitalWrite(displayg, LOW);
      digitalWrite(displayb, HIGH);
      digitalWrite(displayc, HIGH);
      Serial.println("1");
      delay(1000);
      
      // 0 (removidas 2 linhas redundantes que eram sobrescritas imediatamente)
      digitalWrite(displaya, HIGH);
      digitalWrite(displayb, HIGH);
      digitalWrite(displayc, HIGH);
      digitalWrite(displayd, HIGH);
      digitalWrite(displaye, HIGH);
      digitalWrite(displayf, HIGH);
      digitalWrite(displayg, LOW); // Para formar o '0', o segmento 'g' deve ser LOW
      Serial.println("0");
      delay(1000);

      // Timer chega no final, motor gira
      meuServo.write(90);
      Serial.println("MOTOR ACIONADO");
    }
  } else {
    // Ajuste de luminosidade dos LEDs
    analogWrite(ledverde, brilho);
    analogWrite(ledvermelho, 0);

    // Estabelece especificação para o circuito voltar ao estado original
    if (meuServo.read() != 0 && num == 69) {
      Serial.println("FECHANDO O MOTOR");
      meuServo.write(0);
      
      // Display desliga
      digitalWrite(displaya, LOW);
      digitalWrite(displayb, LOW);
      digitalWrite(displayc, LOW);
      digitalWrite(displayd, LOW);
      digitalWrite(displaye, LOW);
      digitalWrite(displayf, LOW);
      digitalWrite(displayg, LOW);
    }
  }
}
