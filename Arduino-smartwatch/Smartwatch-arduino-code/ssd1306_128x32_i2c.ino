#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


//My variables
char input;

int i = 0;

char timeStamp1;
char timeStamp2;
char timeStamp3;
char timeStamp4;
char timeStamp5;
char timeStamp6;
char timeStamp7;
char timeStamp8;
char timeStamp9;
char timeStamp10;
char timeStamp11;
char timeStamp12;
char timeStamp13;


int test = 0;

int print1;
int print2;
int print3;
int print4;
int print5;
int print6;

String print1String;
String print2String;
String print3String;
String print4String;
String print5String;
String print6String;

String printThis;



String date1String;
String date2String;
String date3String;
String date4String;
String date5String;
String date6String;
String date7String;

String printThisDateString;



int bInt = 100;

char batLevelChar1;
char batLevelChar2;
char batLevelChar3;
char batLevelChar4;
char batLevelChar5;
char batLevelChar6;
char batLevelChar7;

String batLevelString1;
String batLevelString2;
String batLevelString3;
String batLevelString4;
String batLevelString5;
String batLevelString6;
String batLevelString7;

String printWhatsapp = "";
String printViber = "";
String printEmail = "";
String printPhone = "";

int printWhatsappInt = 0;
int printViberInt = 0;
int printEmailInt = 0;
int printPhoneInt = 0;

boolean printWhatsappBoolean = false;
boolean printViberBoolean = false;
boolean printEmailBoolean = false;
boolean printPhoneBoolean = false;

String printBatLevelString;



int vibrationMotor = 6;
boolean vibrationMotorBoolean = false;
long previousMillisVibration = 0;
long intervalVibration = 250;

boolean vibrationMotorBoolean2 = false;
long previousMillisVibration2 = 0;

boolean stopVibration = false;
boolean phoneVibration = false;

int x;



//Time Interval
unsigned long currentMillis;
long previousMillis = 0;
long interval = 1000;
bool startCounting = false;

bool captureCountOnce = false;




void setup()   {
  Serial.begin(9600);
  Serial.println(">>START<<");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();



  // text display tests
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 8);
  display.print("Pair BT");
  display.display();

  pinMode(vibrationMotor, OUTPUT);
}


void loop() {

  if (startCounting == true) {

    currentMillis = millis();

    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      timeCount();
    }
  }


  //Serial.println(currentMillis);


  if (vibrationMotorBoolean == true) {
    digitalWrite(vibrationMotor, HIGH);

    if (currentMillis - previousMillisVibration > intervalVibration) {
      digitalWrite(vibrationMotor, LOW);
      vibrationMotorBoolean = false;

      if (phoneVibration == true) {
        if (x > 6) {
          x = 0;
          phoneVibration = false;
        }else {
          x ++; 
          vibrationMotorBoolean2 = true;
          previousMillisVibration2 = currentMillis;
        }   
      } else {
        if (stopVibration == false) {
          vibrationMotorBoolean2 = true;
          previousMillisVibration2 = currentMillis;
        }
      }

      previousMillisVibration = currentMillis;
    }
  }
  if (vibrationMotorBoolean2 == true) {
    if (currentMillis - previousMillisVibration2 > intervalVibration) {
      vibrationMotorBoolean2 = false;

      previousMillisVibration = currentMillis;
      vibrationMotorBoolean = true;

      stopVibration = true;

      previousMillisVibration2 = currentMillis;
    }
  }



  if (Serial.available() > 0) {
    input = Serial.read();

    //Capture Time stamp
    if (i < 14) {
      captureTimeStamps();
    }



    //capture bytestream
    if (bInt == 8) {
      bInt = 0;
    }

    if (bInt < 7) {

      switch (bInt) {

        case 0:
          batLevelChar1 = input;
          break;

        case 1:
          batLevelChar2 = input;
          break;

        case 2:
          batLevelChar3 = input;
          break;

        case 3:
          batLevelChar4 = input;
          break;

        case 4:
          batLevelChar5 = input;
          break;

        case 5:
          batLevelChar6 = input;
          break;

        case 6:
          batLevelChar7 = input;
          break;

        default:
          break;
      }
      bInt = bInt + 1;
    }

    if (input == 'b') {
      bInt = 0;
    }
  }
}

void timeCount (void) {

  for (int b = 0; b < 127; b++) {
    for (int c = 8; c < 22; c++) {
      display.drawPixel(b, c, BLACK);
    }
  }


  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 8);

  //Only do this once

  if (captureCountOnce == false) {
    print1 = int(timeStamp8) - 48;
    print2 = int(timeStamp9) - 48;
    print3 = int(timeStamp10) - 48;
    print4 = int(timeStamp11) - 48;
    print5 = int(timeStamp12) - 48;
    print6 = int(timeStamp13) - 48;
  }
  captureCountOnce = true;


  //Time Increment logic
  print6 = print6 + 1;

  if (print6 == 10) {
    print6 = 0;
    print5 = print5 + 1;
  }

  if ((print5 * 10 + print6) == 60) {
    print6 = 0;
    print5 = 0;
    print4 = print4 + 1;
  }


  if (print4 == 10) {
    print4 = 0;
    print3 = print3 + 1;
  }

  if ((print3 * 10 + print4) == 60) {
    print3 = 0;
    print4 = 0;
    print2 = print2 + 1;
  }


  if (print2 == 10) {
    print2 = 0;
    print1 = print1 + 1;
  }

  if ((print1 * 10 + print2) == 24) {
    print1 = 0;
    print2 = 0;
  }


  print1String = String(print1);
  print2String = String(print2);
  print3String = String(print3);
  print4String = String(print4);
  print5String = String(print5);
  print6String = String(print6);

  printThis = print1String + print2String + ":" + print3String + print4String + ":" + print5String + print6String;

  display.print(printThis);
  display.display();





  //Display Battery Level
  displayBatteryLevel();
}




void displayBatteryLevel(void) {

  for (int b = 0; b < 127; b++) {
    for (int c = 0; c < 8; c++) {
      display.drawPixel(b, c, BLACK);
    }
  }

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);


  batLevelString1 = String(batLevelChar1);
  batLevelString2 = String(batLevelChar2);
  batLevelString3 = String(batLevelChar3);

  if (batLevelString1 == "0") {
    batLevelString1 = "";
  }

  if (batLevelString2 == "0" && batLevelString1 == "0") {
    batLevelString2 = "";
  }


  batLevelString4 = String(batLevelChar4);
  batLevelString5 = String(batLevelChar5);
  batLevelString6 = String(batLevelChar6);
  batLevelString7 = String(batLevelChar7);



  if (batLevelString4 == "1") {
    printWhatsapp = "W ";
    batLevelString4 = "0";
    batLevelChar4 = "0";
    printWhatsappBoolean = true;

    stopVibration = false;
    previousMillisVibration = currentMillis;
    vibrationMotorBoolean = true;
  }
  if (printWhatsappBoolean == true) {
    if (printWhatsappInt > 30) {
      printWhatsapp = "";
      printWhatsappInt = 0;
      printWhatsappBoolean = false;
    }
    printWhatsappInt ++;
  }



  if (batLevelString5 == "1") {
    printViber = "V ";
    batLevelString5 = "0";
    batLevelChar5 = "0";
    printViberBoolean = true;

    stopVibration = false;
    previousMillisVibration = currentMillis;
    vibrationMotorBoolean = true;
  }
  if (printViberBoolean == true) {
    if (printViberInt > 30) {
      printViber = "";
      printViberInt = 0;
      printViberBoolean = false;
    }
    printViberInt ++;
  }


  if (batLevelString6 == "1") {
    printEmail = "E ";
    batLevelString6 = "0";
    batLevelChar6 = "0";
    printEmailBoolean = true;

    stopVibration = false;
    previousMillisVibration = currentMillis;
    vibrationMotorBoolean = true;
  }
  if (printEmailBoolean == true) {
    if (printEmailInt > 180) {
      printEmail = "";
      printEmailInt = 0;
      printEmailBoolean = false;
    }
    printEmailInt ++;
  }


  if (batLevelString7 == "1") {
    printPhone = "P ";
    batLevelString7 = "0";
    batLevelChar7 = "0";
    printPhoneBoolean = true;

    phoneVibration = true;
    stopVibration = false;
    previousMillisVibration = currentMillis;
    vibrationMotorBoolean = true;
  }
  if (printPhoneBoolean == true) {
    if (printPhoneInt > 30) {
      printPhone = "";
      printPhoneInt = 0;
      printPhoneBoolean = false;
    }
    printPhoneInt ++;
  }




  printBatLevelString = batLevelString1 + batLevelString2 + batLevelString3 + " % " + printWhatsapp + printViber + printEmail + printPhone;

  display.print(printBatLevelString);
  display.display();
}





void displayDate(void) {
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 25);

  date1String = String(timeStamp1);
  date2String = String(timeStamp2);
  date3String = String(timeStamp3);
  date4String = String(timeStamp4);
  date5String = String(timeStamp5);
  date6String = String(timeStamp6);
  date7String = String(timeStamp7);

  printThisDateString = date1String + date2String + date3String + "   " + date6String + date7String + "." + date4String + date5String;

  display.print(printThisDateString);
  display.display();
}


void captureTimeStamps (void) {

  switch (i) {
    case 0:
      timeStamp1 = input;
      break;

    case 1:
      timeStamp2 = input;
      break;

    case 2:
      timeStamp3 = input;
      break;

    case 3:
      timeStamp4 = input;
      break;

    case 4:
      timeStamp5 = input;
      break;

    case 5:
      timeStamp6 = input;
      break;

    case 6:
      timeStamp7 = input;
      break;

    case 7:
      timeStamp8 = input;
      break;

    case 8:
      timeStamp9 = input;
      break;

    case 9:
      timeStamp10 = input;
      break;

    case 10:
      timeStamp11 = input;
      break;

    case 11:
      timeStamp12 = input;
      break;

    case 12:
      timeStamp13 = input;

      startCounting = true;
      displayDate();
      break;


    default:
      break;
  }

  i = i + 1;
}
















void testGraphics(void) {

  testdrawline();
  display.display();
  delay(500);
  display.clearDisplay();

  testdrawrect();
  display.display();
  delay(500);
  display.clearDisplay();

  testfillrect();
  display.display();
  delay(500);
  display.clearDisplay();

  testdrawcircle();
  display.display();
  delay(500);
  display.clearDisplay();
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];

  // initialize
  for (uint8_t f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;

    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(50);

    // then erase it + move it
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
  }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
  delay(1);
}

void testdrawcircle(void) {
  for (int16_t i = 0; i < 55; i += 2) {
    display.drawCircle(display.width() / 2, display.height() / 2, i, WHITE);
    display.display();
    delay(1);
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i = 0; i < display.height() / 2; i += 3) {
    // alternate colors
    display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, color % 2);
    display.display();
    delay(1);
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i = 0; i < min(display.width(), display.height()) / 2; i += 5) {
    display.drawTriangle(display.width() / 2, display.height() / 2 - i,
                         display.width() / 2 - i, display.height() / 2 + i,
                         display.width() / 2 + i, display.height() / 2 + i, WHITE);
    display.display();
    delay(1);
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i = min(display.width(), display.height()) / 2; i > 0; i -= 5) {
    display.fillTriangle(display.width() / 2, display.height() / 2 - i,
                         display.width() / 2 - i, display.height() / 2 + i,
                         display.width() / 2 + i, display.height() / 2 + i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
}

void testdrawroundrect(void) {
  for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
    display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, display.height() / 4, WHITE);
    display.display();
    delay(1);
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
    display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, display.height() / 4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
}

void testdrawrect(void) {
  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, WHITE);
    display.display();
    delay(1);
  }
}

void testdrawline() {
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(0, 0, display.width() - 1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(100);

  display.clearDisplay();
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, display.height() - 1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.height() - 1, display.width() - 1, i, WHITE);
    display.display();
    delay(1);
  }
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 8);
  display.clearDisplay();
  display.println("It's a me!");
  display.display();
  delay(1);

  /*
    display.startscrollright(0x00, 0x0F);
    delay(4000);
    display.stopscroll();

    delay(1000);
  */

  display.startscrollleft(0x00, 0x0F);
  delay(4000);
  display.stopscroll();
}
