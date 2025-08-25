#include "Mouse.h"
#include <hiduniversal.h>
#include "hidmouserptparser.h"
#include "Keyboard.h"

void onButtonDown(uint16_t buttonId_);
void onButtonUp(uint16_t buttonId_);
void onMouseMove(int16_t x, int16_t y, int8_t wheel);
void onScroll(int8_t scrollValue);

String split(String data, char separator, int index);

#define MOUSE_NEXT 16
#define MOUSE_PREV 8

USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseReportParser Mou(nullptr);

volatile bool buttonEvent = false;
volatile uint16_t buttonId = 0;
volatile bool isButtonDown = false;

void setup()
{
  Mouse.begin();
  Keyboard.begin();
  Serial.begin(115200);
  Serial.setTimeout(1);

  if (Usb.Init() == -1)
  {
    Serial.println("OSC did not start.");
  }
  
  delay(200);

  if (!Hid.SetReportParser(0, &Mou))
  {
    ErrorMessage<uint8_t> (PSTR("SetReportParser"), 1);
  }
}

void loop()
{
  // 호스트 쉴드에 연결된 마우스 이벤트 처리
  Usb.Task();

  if (buttonEvent)
  {
    if (Serial.dtr())
    {
      char buffer[16];
      const char* type = isButtonDown ? "BD:" : "BU:";
      snprintf(buffer, sizeof(buffer), "%s%u", type, buttonId);
      Serial.println(buffer);
    }
    
    buttonEvent = false;
  }

  // PC에서 시리얼 통신으로 들어오는 명령어를 처리
  if (Serial.available() > 0) {
    String rawdata = Serial.readString();
    String _x = split(rawdata, ',', 0);
    String _y = split(rawdata, ',', 1);
    String _m = split(rawdata, ',', 2);
    if ((_x.length() > 0) && (_y.length() > 0) && (_m.length() > 0)) {
      int x = _x.toInt();
      int y = _y.toInt();
      int m = _m.toInt();
      Mouse.move(x, y);
      delay(random(1,7));
      if (m == 1) {
        Mouse.press(MOUSE_LEFT);
        Mouse.release(MOUSE_LEFT);
      }
    }
  }
}

// split 함수 정의
String split(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void onButtonDown(uint16_t buttonId_)
{
    buttonEvent = true;
    buttonId = buttonId_;
    isButtonDown = true;
    switch(buttonId)
    {
        case MOUSE_LEFT:
            Mouse.press(MOUSE_LEFT);
            break;
        case MOUSE_RIGHT:
            Mouse.press(MOUSE_RIGHT);
            break;
        case MOUSE_MIDDLE:
            Mouse.press(MOUSE_MIDDLE);
            break;
        case MOUSE_PREV:
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press(KEY_LEFT_ARROW);
            break;
        case MOUSE_NEXT:
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press(KEY_RIGHT_ARROW);
            break;
        default:
            break;
    }
}
void onButtonUp(uint16_t buttonId_)
{
    buttonEvent = true;
    buttonId = buttonId_;
    isButtonDown = false;
    switch(buttonId)
    {
        case MOUSE_LEFT:
            Mouse.release(MOUSE_LEFT);
            break;
        case MOUSE_RIGHT:
            Mouse.release(MOUSE_RIGHT);
            break;
        case MOUSE_MIDDLE:
            Mouse.release(MOUSE_MIDDLE);
            break;
        case MOUSE_PREV:
            Keyboard.release(KEY_LEFT_ALT);
            Keyboard.release(KEY_LEFT_ARROW);
            break;
        case MOUSE_NEXT:
            Keyboard.release(KEY_LEFT_ALT);
            Keyboard.release(KEY_RIGHT_ARROW);
            break;
        default:
            break;
    }
}
void onMouseMove(int16_t x, int16_t y, int8_t wheel)
{
    Mouse.move(x, y, wheel);
}
void onScroll(int8_t scrollValue)
{
    Mouse.move(0, 0, scrollValue);
}
