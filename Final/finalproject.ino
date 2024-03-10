#include <Servo.h> // ไลบรารี่ Servo ควรติดตั้ง

Servo myservo;
int State = 0;
int ledPin = 13;
int digitalPin = 3;
int val = 0;

const int pingPin = 9;
int inPin = 8;
int ledr = 2; // red
int ledy = 4;
int ledg = 5;
long duration, cm;

void setup()
{
  pinMode(ledr, OUTPUT);
  digitalWrite(ledr, LOW);

  pinMode(ledy, OUTPUT);
  digitalWrite(ledy, LOW);

  pinMode(ledg, OUTPUT);
  digitalWrite(ledg, LOW);

  pinMode(pingPin, OUTPUT);

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);    // sets the pin as output
  pinMode(digitalPin, INPUT); // sets the pin as input
  pinMode(12, INPUT);
  myservo.attach(12);
  myservo.write(160); // Setup Servo เปิดฝาเอาขยะออก
  delay(5000);        // หน่วงเวลา 10 วินาที
  myservo.write(0);   // Setup กลับตำแหน่ง 0 องศา
}
void loop()
{

  pinMode(pingPin, OUTPUT);

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);

  Serial.print("cm");

  delay(1000);

  Serial.println();
  digitalWrite(ledr, LOW);
  digitalWrite(ledy, LOW);
  digitalWrite(ledg, LOW);
  if (cm >= 12)
  {
    digitalWrite(ledg, HIGH);
  }
  else if (cm < 2)
  {
    digitalWrite(ledr, HIGH);
  }
  else if (cm < 6)
  {
    digitalWrite(ledy, HIGH);
  }
  else
  {

    Serial.println(" cm");
  }
  delay(100);

  int Sr = digitalRead(12); // รับค่า Sensor จากขา 2
  Serial.print("Sevo = ");
  Serial.println(State);
  if (State == 0)
  {
    if (val == 0)
    {                   // เมื่อ Sr เซ็นเซอร์มีค่า = 1
      myservo.write(0); // Servo อยู่ที่ตำแหน่ง 0
      delay(100);
    }
    else if (val == 1)
    {                     // เมื่อ Sr เซ็นเซอร์มีค่า = 0
      myservo.write(160); // Servo หมุนไปที่ 160 องศา
      State = 1;          // State มีค่าเท่ากับ 1
    }
  }
  if (State == 1)
  {              // เมื่อ State = 1
    delay(3000); // หน่วงเวลา 3 นาที
    State = 0;   // State มีค่า = 0
  }
  val = digitalRead(digitalPin); // อ่านค่าสัญญาณ digital ขา8 ที่ต่อกับเซ็นเซอร์
  Serial.print("val = ");        // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(val);           // พิมพ์ค่าของตัวแปร val
  if (val == 1)
  {                             // ค่า เป็น 0 ตรวจจับเจอวัตถุ สั่งให้ไฟ LED ติด
    digitalWrite(ledPin, HIGH); // สั่งให้ LED ติดสว่าง
  }
  else
  {
    digitalWrite(ledPin, LOW); // สั่งให้ LED ดับ
  }
  delay(100);
} // กลับไปวนลูป

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}