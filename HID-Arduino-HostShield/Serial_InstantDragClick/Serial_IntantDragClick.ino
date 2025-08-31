#include "Mouse.h"
#include <hiduniversal.h>
#include "hidmouserptparser.h"
#include "Keyboard.h"

void onButtonDown(uint16_t buttonId_);
void onButtonUp(uint16_t buttonId_);
void onMouseMove(int16_t x, int16_t y, int8_t wheel);
void onScroll(int8_t scrollValue);

// 오른쪽 버튼 관련 변수
unsigned long clickIntervalRight = 0;       
const unsigned long holdThresholdRight = 300;
unsigned long buttonRightDownTime = 0;     
unsigned long lastClickTimeButtonRight = 0;

// 왼쪽 버튼 관련 변수
unsigned long clickIntervalLeft = 0;       
const unsigned long holdThresholdLeft = 300;
unsigned long buttonLeftDownTime = 0;     
unsigned long lastClickTimeButtonLeft = 0;

// 마우스 XButton 설정
#define MOUSE_NEXT 16
#define MOUSE_PREV 8

USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseReportParser Mou(nullptr);

volatile bool buttonEvent = false;
volatile uint16_t buttonId = 0;
volatile bool isButtonRightDown = false;
volatile bool isButtonLeftDown = false;

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
    Usb.Task();

    // buttonRightDownTime 오른쪽 마우스 클릭 설정
    if (isButtonRightDown && buttonRightDownTime == 0) {
        buttonRightDownTime = millis();
    } 
    else if (!isButtonRightDown) {
        buttonRightDownTime = 0;
    }

    // buttonLeftDownTime 왼쪽 마우스 클릭 설정
    if (isButtonLeftDown && buttonLeftDownTime == 0) {
        buttonLeftDownTime = millis();
    } 
    else if (!isButtonLeftDown) {
        buttonLeftDownTime = 0;
    }

    // 오른쪽 버튼 드래그 클릭 (현재 오른쪽 CPS: 약 17.5)
    //clickIntervalRight값이 높으면 CPS가 낮아지고, 반대로 낮으면 CPS가 높아짐
    if (isButtonRightDown && buttonId == MOUSE_RIGHT && (millis() - buttonRightDownTime >= holdThresholdRight)) {
        if (millis() - lastClickTimeButtonRight >= clickIntervalRight) {
            clickIntervalRight = random(45, 65);
            Mouse.press(MOUSE_RIGHT);
            Mouse.release(MOUSE_RIGHT);
            delay(random(0,2));
            lastClickTimeButtonRight = millis();
        }
    }

    // 왼쪽 버튼 드래그 클릭 (현재 왼쪽 CPS: 약 13.5)
    //clickIntervalLeft값이 높으면 CPS가 낮아지고, 반대로 낮으면 CPS가 높아짐
    if (isButtonLeftDown && buttonId == MOUSE_LEFT && (millis() - buttonLeftDownTime >= holdThresholdLeft)) {
        if (millis() - lastClickTimeButtonLeft >= clickIntervalLeft) {
            clickIntervalLeft = random(60, 85);
            Mouse.press(MOUSE_LEFT);
            Mouse.release(MOUSE_LEFT);
            delay(random(0,2));
            lastClickTimeButtonLeft = millis();
        }
    }
}

void onButtonDown(uint16_t buttonId_)
{
    buttonEvent = true;
    buttonId = buttonId_;

    switch(buttonId)
    {
        case MOUSE_LEFT:
        isButtonLeftDown = true;
            Mouse.press(MOUSE_LEFT);
            break;
        case MOUSE_RIGHT:
        isButtonRightDown = true;
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

    switch(buttonId)
    {
        case MOUSE_LEFT:
            isButtonLeftDown = false;
            Mouse.release(MOUSE_LEFT);
            break;
        case MOUSE_RIGHT:
            isButtonRightDown = false;
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
