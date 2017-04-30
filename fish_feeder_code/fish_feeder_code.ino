/*
 * Pemberi makan ikan otomatis
 * Alat yang diperlukan:
 * 1. Arduino
 * 2. Servo
 * 3. LED
 * 4. Resistor 220 Ohm
 * 5. Piezo Buzzer
 * 6. Wadah pellet ikan berbentuk silinder dengan penutup
 */

#include <Servo.h> // Aktifkan modul servo
 
Servo servo1;  // membuat object servo1
 
int pos = 0;    // posisi servo (sudut derajat)

long feeding_delay = 43200000; // Masukkan selang waktu / interval pemberian pakan (dalam millidetik), 
                    //contoh: makan 2x sehari -> tiap 12 jam -> 12 x 60 x 60 x 1000 = 43200000

long endtime; // akhir countdown
long now; // waktu now

void setup() 
{ 
  pinMode(9, OUTPUT); // pin untuk piezo buzzer
  pinMode(2, OUTPUT); // pin untuk nyala kelap-kelip LED
  servo1.attach(10);  // menggunakan pin 10 untuk servo
  servo1.write(0); // menyetel servo ke posisi awal
  delay(15);
} 
 
 
void loop() // Ketika rangkaian diberi power maka akan langsung memberi makan (servo berputar), dilanjutkan dengan menunggu
            // sampai waktu pemberian makan selanjutnya
{ 
  alarm2(); // bunyi alarm
  
  for(pos = 0; pos < 180; pos += 1)  // servo bergerak dari posisi 0 derajat ke 180 derajat per 1 derajat
  {                                 
    servo1.write(pos);              // servo pada posisi 'pos' sesuai value di for loop
    delay(3);                       // delay 3ms per 1 derajat pergerakan servo
  } 
  for(pos = 180; pos>=1; pos-=1)     // servo kembali ke posisi awal setelah mencapai 180 derajat
  {                                
    servo1.write(pos);               
    delay(3);                       
  }
  
  // variable
  now = millis(); // var now akan selalu terupdate dengan value dari millis()
  endtime = now + feeding_delay; // menentukan waktu pemberian makan selanjutnya
  
  while(now < endtime) { //sembari menunggu sampai waktu pemberian makan berikutnya lampu indikator akan menyala
   lampu();
   servo1.write(0);
   now = millis();   
  }

   
}

// nada alarm
void alarm2(){  
    tone(9,630,100);
    delay(200);
    tone(9,755,100);
    delay(200);
    tone(9,1175,100);
    delay(600);
    tone(9,630,100);
    delay(200);
    tone(9,755,100);
    delay(200);
    tone(9,1175,100);
    delay(200);
}

// ritme nyala lampu LED
void lampu() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);    
  delay(2000);            
}
