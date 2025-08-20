// DAVI TIBURCIO DE ARAUJO
// CURSO TÉCNICO EM ELETRÔNICO 2ºANO

#include <Keypad.h>

const byte LINHAS = 4;
const byte COLUNAS = 4;
char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinosLinhas[LINHAS] = {11, 10, 9, A1};
byte pinosColunas[COLUNAS] = {A2, A3, A4, A5};
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

int ledVermelho = 13;
int ledVerde = 12;
int displayA = 2;
int displayB = 3;
int displayC = 4;
int displayD = 5;
int displayE = 6;
int displayF = 8;
int displayG = 7;
int pinoPot = A0;

const int TAMANHO_SENHA = 4;
char senhaMestra[TAMANHO_SENHA + 1] = "0316";
char senhaDigitada[TAMANHO_SENHA + 1] = "";
int indiceSenha = 0;

bool sistemaTravado = true;
unsigned long tempoDestravado = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(displayA, OUTPUT);
  pinMode(displayB, OUTPUT);
  pinMode(displayC, OUTPUT);
  pinMode(displayD, OUTPUT);
  pinMode(displayE, OUTPUT);
  pinMode(displayF, OUTPUT);
  pinMode(displayG, OUTPUT);

  indiceSenha = 0;
  senhaDigitada[0] = '\0';
  sistemaTravado = true;
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledVerde, LOW);

  digitalWrite(displayA, LOW); digitalWrite(displayB, LOW);
  digitalWrite(displayC, LOW); digitalWrite(displayD, LOW);
  digitalWrite(displayE, LOW); digitalWrite(displayF, LOW);
  digitalWrite(displayG, LOW);
  
  Serial.println("Sistema de Seguranca Iniciado. Digite a senha:");
}

void loop() {
  if (sistemaTravado) {
    char teclaPressionada = teclado.getKey();

    if (teclaPressionada) { 
      
      if (teclaPressionada >= '0' && teclaPressionada <= '9') {
        if (indiceSenha < TAMANHO_SENHA) {
          senhaDigitada[indiceSenha] = teclaPressionada;
          indiceSenha++;
          senhaDigitada[indiceSenha] = '\0'; 


          digitalWrite(displayA, LOW); digitalWrite(displayB, LOW); digitalWrite(displayC, LOW);
          digitalWrite(displayD, LOW); digitalWrite(displayE, LOW); digitalWrite(displayF, LOW);
          digitalWrite(displayG, LOW);

          if (teclaPressionada == '0') {
            digitalWrite(displayA, HIGH); digitalWrite(displayB, HIGH); digitalWrite(displayC, HIGH);
            digitalWrite(displayD, HIGH); digitalWrite(displayE, HIGH); digitalWrite(displayF, HIGH);
          } else if (teclaPressionada == '1') {
            digitalWrite(displayB, HIGH); digitalWrite(displayC, HIGH);
          } else if (teclaPressionada == '2') {
            digitalWrite(displayA, HIGH); digitalWrite(displayB, HIGH); digitalWrite(displayD, HIGH);
            digitalWrite(displayE, HIGH); digitalWrite(displayG, HIGH);
          } else if (teclaPressionada == '3') {
            digitalWrite(displayA, HIGH); digitalWrite(displayB, HIGH); digitalWrite(displayC, HIGH);
            digitalWrite(displayD, HIGH); digitalWrite(displayG, HIGH);
          } else if (teclaPressionada == '4') {
            digitalWrite(displayB, HIGH); digitalWrite(displayC, HIGH);
            digitalWrite(displayF, HIGH); digitalWrite(displayG, HIGH);
          } else if (teclaPressionada == '5') {
            digitalWrite(displayA, HIGH); digitalWrite(displayC, HIGH);
            digitalWrite(displayD, HIGH); digitalWrite(displayF, HIGH);
            digitalWrite(displayG, HIGH);
          } else if (teclaPressionada == '6') {
            digitalWrite(displayA, HIGH); digitalWrite(displayC, HIGH);
            digitalWrite(displayD, HIGH); digitalWrite(displayE, HIGH);
            digitalWrite(displayF, HIGH); digitalWrite(displayG, HIGH);
          } else if (teclaPressionada == '7') {
            digitalWrite(displayA, HIGH); digitalWrite(displayB, HIGH);
            digitalWrite(displayC, HIGH);
          } else if (teclaPressionada == '8') {
            digitalWrite(displayA, HIGH); digitalWrite(displayB, HIGH); digitalWrite(displayC, HIGH);
            digitalWrite(displayD, HIGH); digitalWrite(displayE, HIGH); digitalWrite(displayF, HIGH);
            digitalWrite(displayG, HIGH);
          } else if (teclaPressionada == '9') {
            digitalWrite(displayA, HIGH); digitalWrite(displayB, HIGH);
            digitalWrite(displayC, HIGH); digitalWrite(displayD, HIGH);
            digitalWrite(displayF, HIGH); digitalWrite(displayG, HIGH);
          }

          Serial.print("Senha de agora: ");
          Serial.println(senhaDigitada);
        }
      }
      else if (teclaPressionada == '*') {
        if (indiceSenha > 0) {
          indiceSenha--;
          senhaDigitada[indiceSenha] = '\0';

          digitalWrite(displayA, LOW); digitalWrite(displayB, LOW); digitalWrite(displayC, LOW);
          digitalWrite(displayD, LOW); digitalWrite(displayE, LOW); digitalWrite(displayF, LOW);
          digitalWrite(displayG, LOW);
          Serial.print("Ultimo digito apagado. Senha de agora: ");
          Serial.println(senhaDigitada);
        } else {
          Serial.println("Não ha nenhum digito para apagar");
        }
      }

      if (indiceSenha == TAMANHO_SENHA) {
        if (strcmp(senhaDigitada, senhaMestra) == 0) {
          Serial.println("Senha valida. Acesso liberado.");
          sistemaTravado = false;
          digitalWrite(ledVerde, HIGH);
          digitalWrite(ledVermelho, LOW);
 
          digitalWrite(displayA, LOW); digitalWrite(displayB, LOW); digitalWrite(displayC, LOW);
          digitalWrite(displayD, LOW); digitalWrite(displayE, LOW); digitalWrite(displayF, LOW);
          digitalWrite(displayG, LOW);
          tempoDestravado = millis();
        } else {
          Serial.println("Senha invalida. Favor, tentar novamente.");

          indiceSenha = 0;
          senhaDigitada[0] = '\0';
          sistemaTravado = true;
          digitalWrite(ledVermelho, HIGH);
          digitalWrite(ledVerde, LOW);
          digitalWrite(displayA, LOW); digitalWrite(displayB, LOW); digitalWrite(displayC, LOW);
          digitalWrite(displayD, LOW); digitalWrite(displayE, LOW); digitalWrite(displayF, LOW);
          digitalWrite(displayG, LOW);

          for(int i=0; i<3; i++){
            digitalWrite(ledVermelho, LOW); delay(100);
            digitalWrite(ledVermelho, HIGH); delay(100);
          }
        }
      }
    }
  } 
  else {
    int leituraPot = analogRead(pinoPot);
    long tempoParaTravar = map(leituraPot, 0, 1023, 5000, 30000); 

    if (millis() - tempoDestravado > tempoParaTravar) {
      Serial.println("Tempo esgotado. Travando sistema automaticamente.");

      indiceSenha = 0;
      senhaDigitada[0] = '\0';
      sistemaTravado = true;
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledVerde, LOW);
      digitalWrite(displayA, LOW); digitalWrite(displayB, LOW); digitalWrite(displayC, LOW);
      digitalWrite(displayD, LOW); digitalWrite(displayE, LOW); digitalWrite(displayF, LOW);
      digitalWrite(displayG, LOW);
    }
  }
}
