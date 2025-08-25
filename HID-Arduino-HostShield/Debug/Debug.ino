#include <SPI.h>
#include <usbhub.h>
#include <hidboot.h>
#include <string.h>

class MouseRptParser : public HIDReportParser {
public:
  void Parse(USBHID* hid, bool is_rpt_id, uint8_t len, uint8_t* buf);
};

USB Usb;
USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb, true);
MouseRptParser Prs;

void setup() {
  Serial.begin(57600);
  Usb.Init();
  HidMouse.SetReportParser(0, &Prs);
}

void loop() {
  Usb.Task();
}

void MouseRptParser::Parse(USBHID* hid, bool is_rpt_id, uint8_t len, uint8_t* buf) {
  if (!buf || !len) return;

  for (uint8_t i = 0; i < len; i++) {
    if (buf[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
