### HID Arduino Mouse

HID mouse emulation with Arduino + Usb HostShield!

## ENG
- before using this you need an `Arduino Leonardo R3 ATmega32u4` and `soldered Usb HostShield`
<br></br>
- This code was designed for my Glorious Model O mouse, so if it doesn't work with yours, you will need to modify it according to the instructions below
<br></br>
- You will need [Arduino IDE version 1.8.19 or higher](https://www.arduino.cc/en/software)(This code was written for version 1.8.19 and might not work correctly on later versions but who cares)
<br></br>
- Download and unpack the repository archive to `C:\Users\your_username\Documents\Arduino\libraries\HID-Arduino`
<br></br>
- Download and unpack [this archive](https://github.com/felis/USB_Host_Shield_2.0/releases/tag/1.7.0) into `C:\Users\your_username\Documents\Arduino\libraries\USB_Host_Shield_2.0-1.7.0`
<br></br>
- Inside the file, there are two versions of the Arduino script. All of these behaviors are fully adjustable and can be changed to suit your needs.
<br></br>
- All Arduino script files are located in a folder that has the same name as the file itself
<br></br>
`RandomDelay_RandomMove.ino`: This script receives coordinates from a PC and performs a series of human-like movements. Instead of moving directly to the target coordinates,
it intentionally introduces a random delay and first moves to a nearby location before moving to the final, specified coordinates. This staged movement is designed to mimic the unpredictable nature of human-like behavior
<br></br>
`RandomDelay.ino`: In contrast, this version is much simpler. After receiving and moving to a set of coordinates, it only adds a random delay before receiving the next command.
<br></br>
1. Open Arduino script what you want
2. Connect the computer, Arduino Leonardo R3, and USB host shield together
3. Set the board and port under the toos menu, then upload the Arduino script
4. you can just use it if mouse works well
<br></br>
<br></br>
### When the mouse doesn't work well
<br></br>
1. Change `#define ENABLE_UHS_DEBUGGING 0` to `#define ENABLE_UHS_DEBUGGING 1` in `C:\Users\your_username\Documents\Arduino\libraries\USB_Host_Shield_2.0-1.7.0\settings.h`
2. Open `Debug.ino` and upload it
3. Press Ctrl + Shift + M and set them to Both NL&CR and 9600 baud rate
4. Move the mouse and check the serial monitor
5. The serial monitor will likely show something similar to `00 00 00 00 00 00 00 00`. You need to figure out which byte changes, and to what number (octal or hexadecimal), when you press a specific mouse button
If your mouse's X, Y values are octal, you must change void onMouseMove(int16_t x, int16_t y, int8_t wheel) to int8_t x, int8_t y, and so on
If the X buttons don't work, you'll need to change `#define MOUSE_NEXT` and `#define MOUSE_PREV` to the numbers that appear when XButton1 or XButton2 are pressed,
like `#define MOUSE_NEXT (number when XButton2 is pressed)`, `#define MOUSE_PREV (number when XButton2 is pressed)`
If the scroll wheel doesn't work well, you may need to modify `ScrollValue` inside `.\hidmouserptparser.cpp`, but it might be easier to get help from ChatGPT or Gemini
6. Once everything is working correctly, change `#define ENABLE_UHS_DEBUGGING 1` back to `#define ENABLE_UHS_DEBUGGING 0` in `C:\Users\your_username\Documents\Arduino\libraries\USB_Host_Shield_2.0-1.7.0\settings.h`
7. Upload `Debug.ino` again, and then upload the Arduino script file you want to use
<br></br>

## KOR
- 이건 제 글로리어스 모델 O 마우스 위주로 위주로 코딩한거라 사용자의 마우스에 따라 작동이 되지 않을 수 있으며 작동이 되지 않는다면 아래 나와있는대로 따로 코딩을 하셔야 합니다
<br></br>
- 이 코드를 사용하려면 `아두이노 레오나르도 R3 ATMEGA32U4`, `납땜한 아두이노 USB 호스트쉴드`가 필요합니다 없으면 납땜 가격포함 약 2만원정도로 그렇게 안비싸니 하나 사세요
<br></br>
- 아두이노 IDE 버전은 [1.8.19버전 이상](https://www.arduino.cc/en/software)(1.8.19버전에서 작성한거라 상위 버전에선 작동 안할수도 있음)이 필요합니다
  <br></br>
- 파일을 다운받고 압축풀어서 `C:\Users\your_username\Documents\Arduino\libraries\HID-Arduino` 여기에 이렇게 저장해주세요
<br></br>
- [이 파일](https://github.com/felis/USB_Host_Shield_2.0/releases/tag/1.7.0)을 다운받아 압축풀고 `C:\Users\your_username\Documents\Arduino\libraries\USB_Host_Shield_2.0-1.7.0` 여기에 이렇게 저장해주세요
<br></br>
- 모든 아두이노 스크립트 파일은 해당 파일의 이름을 가지고 있는 폴더 안에 있습니다
<br></br>
- 파일 안에는 두가지 버전의 아두이노 스크립트가 있습니다. `RandomDelay_RandomMove.ino`는 PC로부터 좌표를 받고 움직이고 나서 다시 좌표를 받을때 일부러 무작위 딜레이를 걸며 PC에서 좌표가 보내질때 바로 그 좌표로 움직이지 않고
그 주변으로 움직인뒤에 PC에서 보낸 좌표로 움직여 사람처럼 보이게 합니다. `RandomDelay.ino`는 좌표를 받고 움직이고나서 다시 좌표를 받을때 무작위 딜레이만 걸며 이 모든건 다 변경이 가능합니다 
<br></br>
1. 사용하고 싶은 아두이노 스크립트 파일을 여세요
2. 아두이노 레오나르도 보드, 컴퓨터, USB 호스트쉴드를 서로 연결해주세요
3. 툴에 있는 보드와 포트 설정을 해주고나서 아두이노 스크립트를 업로드 해주세요
4. 마우스가 잘 작동된다면 성공!
<br></br>
<br></br>
### 그래도 작동이 잘 되지 않을때
<br></br>
1. `C:\Users\your_username\Documents\Arduino\libraries\USB_Host_Shield_2.0-1.7.0\settings.h` 에서 `#define ENABLE_UHS_DEBUGGING 0`을 `#define ENABLE_UHS_DEBUGGING 1`로 바꾸세요
2. `Debug.ino` 파일을 열고 업로드하세요
3. Ctrl + Shift + M 을 누르고 오른쪽 아래에 있는걸 Both NL & CR,  9600 보드레이트로 설정하세요
4. 마우스를 움직이고 버튼을 누르면서 시리얼 모니터를 확인하세요
5. 자 이제부터가 중요합니다. 시리얼 모니터가 `00 00 00 00 00 00 00 00`과 비슷하게 뜰텐데 마우스에서 어떤 버튼을 눌렀을때 몇 번째가 어떤 숫자로 바뀌는지, 8진수인지 16진수인지를 알아내야합니다
자신의 마우스의 x, y가 8진수라면 모든 `void onMouseMove(int16_t x, int16_t y, int8_t wheel)` 에서 `int8_t x`, `int8_t y` 이런식으로 바꾸거나
X버튼이 먹히지 않는다면 `#define MOUSE_NEXT (XButton2을 눌렀을때 나오는 숫자)`, `#define MOUSE_PREV (XButton2을 눌렀을때 나오는 숫자))` 과 같이 해야하거나
스크롤이 잘 먹히지 않는다면 `.\hidmouserptparser.cpp` 안에있는 `ScrollValue` 값을 변경하거나 해야하지만 챗지피티나 제미나이에게 도움을 받는것이 편할수도 있습니다
6. 이후에 모든것이 잘 작동한다면 다시 `C:\Users\your_username\Documents\Arduino\libraries\USB_Host_Shield_2.0-1.7.0\settings.h` 에서 `#define ENABLE_UHS_DEBUGGING 1`을 `#define ENABLE_UHS_DEBUGGING 0`로 바꾸세요
7. 다시 한 번 더 `Debug.ino`를 업로드한 뒤에 원하는 아두이노 스크립트 파일을 업로드하여 사용하시면 됩니다
<br></br>
<br></br>
<br></br>



## TroubleShooting
- If the mouse's polling rate is very low, it may not work well
- 마우스의 폴링레이트(hz)가 낮다면 잘 작동하지 않을 수 있습니다
<br></br>
- If the Arduino script doesn't compile you must check that you're NOT using the Windows Store version of Arduino IDE and you are using the one from the link in the setup tutorial
- 아두이노 스크립트가 컴파일되지 않는다면 윈도우 스토어 버전 아두이노 IDE를 사용하고 있는게 아닌지 확인하세요
<br></br>
- If your Arduino has issues working in general, try using a different USB port and a better cable. I recommend the one that comes with the Arduino
- 아두이노가 일반적으로 작동하는데 문제가 있다면, 다른 USB 케이블을 사용해보세요(아두이노 살 때 같이 동봉되서 오는 케이블을 사용하는걸 추천합니다)
<br></br>
- If this doesn't work, read it all over again slowly
- 온갖짓을 했는데도 잘 작동하지 않는다면 이걸 다시 처음부터 천천히 읽어보세요 
<br></br>
<br></br>
