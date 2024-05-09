#include <HardwareSerial.h>


unsigned long previousMillis = 0;
const int interval = 1000;

HardwareSerial pointA(1);
HardwareSerial pointB(2);

void setup() {
  // put your setup code here, to run once:
  pointA.begin(9600, SERIAL_8N1, 3, 1);
  pointB.begin(9600, SERIAL_8N1, 16, 17);
  Serial.begin(9600);
  Serial.println("Initializing...");
}

void loop() {
  send();
  receive();
  delay(10);
}
void send() {
  unsigned long currentMillis = millis();  // lấy thời gian hiện tại

  // kiểm tra xem đã đủ thời gian chưa để in ký tự
  if (currentMillis - previousMillis >= interval) {
    // lưu lại thời gian hiện tại để kiểm tra trong lần gọi tiếp theo
    previousMillis = currentMillis;

    // in một ký tự (ví dụ: 'A')
    pointB.println("Ax");
    Serial.println("Send data: Ax");
  }
}
void receive() {
  while (pointA.available() > 0) {
    // Đọc dữ liệu đến khi hết dữ liệu trong bộ nhớ đệm
    String data = pointA.readStringUntil('x');  // Đọc đến khi gặp ký tự xuống dòng ('\n')
    // In dữ liệu đã nhận được
    Serial.print("Received data: ");
    Serial.println(data);
  }
}