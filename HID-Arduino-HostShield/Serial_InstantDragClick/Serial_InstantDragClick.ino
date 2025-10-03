#include "Mouse.h"
#include <hiduniversal.h>
#include "hidmouserptparser.h"
#include "Keyboard.h"

// 함수 선언
void onButtonDown(uint16_t buttonId_);
void onButtonUp(uint16_t buttonId_);
void onMouseMove(int16_t x, int16_t y, int8_t wheel);
void onScroll(int8_t scrollValue);

// 오른쪽 버튼 관련 변수
unsigned long clickIntervalRight = 0;
unsigned long buttonRightDownTime = 0;    
unsigned long lastClickTimeButtonRight = 0;
unsigned long RightButtonDragClickCount = 0;
const unsigned long RightButtonDragClickTime = 1750;

// 왼쪽 버튼 관련 변수 (XButton1 → 드래그 클릭 전용)
unsigned long clickIntervalLeft = 0;       
unsigned long buttonLeftDownTime = 0;     
unsigned long lastClickTimeButtonLeft = 0;
unsigned long LeftButtonDragClickCount = 0;
const unsigned long LeftButtonDragClickTime = 1350;

// 드래그클릭 활성화 시간 조건
const unsigned long holdThresholdLeft = 0;
const unsigned long holdThresholdRight = 60;

// 마우스 XButton 설정
#define MOUSE_NEXT 16
#define MOUSE_PREV 8

USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseReportParser Mou(nullptr);

volatile bool buttonEvent = false;
volatile uint16_t buttonId = 0;
volatile bool isButtonRightDown = false;
volatile bool isButtonLeftDown = false;   // ← XButton1 눌렀을 때만 true

// millis() 기반 딜레이 관리 변수
unsigned long rightPauseUntil = 0;
unsigned long leftPauseUntil = 0;

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

    // 오른쪽 버튼 눌렀을 때 시간 기록
    if (isButtonRightDown && buttonRightDownTime == 0) {
        buttonRightDownTime = millis();
    } 
    else if (!isButtonRightDown) {
        buttonRightDownTime = 0;
        RightButtonDragClickCount = 0;
    }

    // 왼쪽(XButton1) 버튼 눌렀을 때 시간 기록
    if (isButtonLeftDown && buttonLeftDownTime == 0) {
        buttonLeftDownTime = millis();
    } 
    else if (!isButtonLeftDown) {
        buttonLeftDownTime = 0;
        LeftButtonDragClickCount = 0;
    }

    // 오른쪽 버튼 드래그 클릭
    if (isButtonRightDown && buttonId == MOUSE_RIGHT && (millis() - buttonRightDownTime >= holdThresholdRight)) {
        if ((millis() - buttonRightDownTime ) / RightButtonDragClickTime > RightButtonDragClickCount) {
            RightButtonDragClickCount += 1;
            if (millis() < rightPauseUntil) return;
            rightPauseUntil = millis() + random(200, 250);
        }
        if (millis() > rightPauseUntil && millis() - lastClickTimeButtonRight >= clickIntervalRight) {
            clickIntervalRight = random(25, 60);
            Mouse.press(MOUSE_RIGHT);
            Mouse.release(MOUSE_RIGHT);
            delay(random(0,2));
            lastClickTimeButtonRight = millis();
        }
    }

    // 왼쪽 드래그 클릭 (XButton1 → Left 드래그클릭 전용)
    if (isButtonLeftDown && buttonId == MOUSE_LEFT && (millis() - buttonLeftDownTime >= holdThresholdLeft)) {
        if ((millis() - buttonLeftDownTime ) / LeftButtonDragClickTime > LeftButtonDragClickCount) {
            LeftButtonDragClickCount += 1;
            if (millis() < leftPauseUntil) return;
            leftPauseUntil = millis() + random(250, 350);
        }
        if (millis() > leftPauseUntil && millis() - lastClickTimeButtonLeft >= clickIntervalLeft) {
            clickIntervalLeft = random(55, 75);
            Mouse.press(MOUSE_LEFT);
            Mouse.release(MOUSE_LEFT);
            delay(random(0,2));
            lastClickTimeButtonLeft = millis();
        }
    }
}

// 버튼 눌렀을 때 처리
void onButtonDown(uint16_t buttonId_)
{
    buttonEvent = true;
    buttonId = buttonId_;

    switch(buttonId)
    {
        case MOUSE_LEFT:   // ← 실제 왼쪽 버튼은 단일 클릭만
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
            Mouse.press(MOUSE_RIGHT);
            break;

        case MOUSE_NEXT:   // ← XButton1(Next) → 드래그클릭 전용
            isButtonLeftDown = true;
            buttonId = MOUSE_LEFT;
            break;
        default:
            break;
    }
}

// 버튼 뗐을 때 처리
void onButtonUp(uint16_t buttonId_)
{
    buttonEvent = true;
    buttonId = buttonId_;

    switch(buttonId)
    {
        case MOUSE_LEFT:
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
            Mouse.release(MOUSE_RIGHT);
            break;

        case MOUSE_NEXT:
            isButtonLeftDown = false;
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
