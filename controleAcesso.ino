
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte PASSWORD_LENGTH = 4;
const char PASSWORD[PASSWORD_LENGTH] = "123";

const byte LINHAS = 4;
const byte COLUNAS = 4;

const char TECLAS[LINHAS][COLUNAS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};

byte pinosLinhas[LINHAS] = {4, 5, 6, 7};
byte pinosColunas[COLUNAS] = {8, 9, 10, 11};
char inputKeypad[PASSWORD_LENGTH];
byte countInputKeypad = 0;

Keypad teclado = Keypad(makeKeymap(TECLAS), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

void setup() {
    lcd.begin();
    lcd.backlight();
}

void clearController() {
    countInputKeypad = 0;
}

void loop() {

    lcd.setCursor(1, 0);
    lcd.print("CONTROLE DE ACESSO");

    char teclaPressionada = teclado.getKey();
    
    if (teclaPressionada && countInputKeypad <= PASSWORD_LENGTH) {
        inputKeypad[countInputKeypad] = teclaPressionada;
        lcd.setCursor(countInputKeypad, 1);
        lcd.print(inputKeypad[countInputKeypad]);
        countInputKeypad++; 
    }

    if ((PASSWORD_LENGTH - 1) == countInputKeypad) {
        delay(1000);
        lcd.clear();

        if (!strcmp(inputKeypad, PASSWORD)) {
            lcd.setCursor(2, 2);
            lcd.print("ACESSO LIBERADO");
            delay(2000);
        } else {
            lcd.setCursor(2, 2);
            lcd.print("ACESSO NEGADO");
            delay(2000);
        }

        clearController();
        lcd.clear();
    }
}


