### HID Arduino Mouse

HID mouse emulation with ur Arduino + Usb HostShield!

## ENG
- before using this you need an `Arduino Leonardo R3(ATmega32u4)` and `soldered Usb HostShield`
<br></br>
- This code was designed for my Glorious Model O mouse, so if it doesn't work with yours, you will need to modify it according to the instructions below
<br></br>
-You will need [Arduino IDE version 1.8.19 or higher](https://www.arduino.cc/en/software)(This code was written for version 1.8.19 and might not work correctly on later versions but who cares)
<br></br>
- Download and unpack the repository archive to `C:\Users\your_username\Documents\Arduino\libraries\HID-Arduino`
<br></br>
- Download and unpack [this archive](https://github.com/felis/USB_Host_Shield_2.0/releases/tag/1.7.0) into `C:\Users\your_username\Documents\Arduino\libraries\USB_Host_Shield_2.0-1.7.0`
<br></br>
- Inside the file, there are two versions of the Arduino script. All of these behaviors are fully adjustable and can be changed to suit your needs.
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
<br></br>
<br></br>
<br></br>



## TroubleShooting
- If the mouse's polling rate is very low, it may not work well
<br></br>
- If the Arduino script doesn't compile you must check that you're NOT using the Windows Store version of Arduino IDE and you are using the one from the link in the setup tutorial
<br></br>
- If your Arduino has issues working in general, try using a different USB port and a better cable. I recommend the one that comes with the Arduino
<br></br>
- If this doesn't work, read it all over again slowly
<br></br>
<br></br>
<br></br>

