#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// WiFi Access Point
const char *ssid = "PakanKucing_AP";
const char *password = "12345678"; 

ESP8266WebServer server(80);
Servo myServo;

// Pin sensor ultrasonik
#define TRIG 5
#define ECHO 4

// Pin servo
#define SERVO_PIN 0

// Batas ketinggian pakan
const int JARAK_BUKA = 2;

// Waktu kontrol
const unsigned long DURASI_BUKA = 5000;         // Waktu servo terbuka
const unsigned long JEDA_ISI_PAKAN = 30000;     // Jeda antar pengisian

// Status
bool sedangMengisi = false;
unsigned long waktuMulaiIsi = 0;
unsigned long waktuTerakhirIsi = 0;
String statusPintu = "Tertutup";

// Fungsi jarak
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Servo kontrol
void bukaPintuPakan() {
  myServo.write(0); // 0 derajat = buka
  sedangMengisi = true;
  statusPintu = "Terbuka";
  waktuMulaiIsi = millis();
  Serial.println("🔓 Pakan terbuka!");
}

void tutupPintuPakan() {
  myServo.write(90); // 90 derajat = tutup
  sedangMengisi = false;
  statusPintu = "Tertutup";
  waktuTerakhirIsi = millis();
  Serial.println("🔒 Pakan tertutup!");
}

// Halaman web
void handleRoot() {
  long jarak = getDistance();

  String statusHTML;
  if (statusPintu == "Terbuka") {
    statusHTML = "<b style='color:red;'>Pakan Terbuka</b>";
  } else {
    statusHTML = "<b style='color:green;'>Pakan Tertutup</b>";
  }

  String html = "<html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='1'>";
  html += "<style>body{text-align:center;font-family:Arial;margin-top:50px;}";
  html += "button{font-size:20px;padding:10px;margin:10px;width:150px;}</style>";
  html += "</head><body>";
  html += "<h1>Monitor Pakan Kucing</h1>";
  html += "<p>Jarak Pakan: <b>" + String(jarak) + " cm</b></p>";
  html += "<p>Status: " + statusHTML + "</p>";
  html += "<p><small>Auto-refresh setiap 1 detik</small></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("📡 Access Point 'PakanKucing_AP' Aktif");
  Serial.println("🔗 Koneksi di IP: 192.168.4.1");

  server.on("/", handleRoot);
  server.begin();
  Serial.println("🌍 Server Web Dimulai");

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  myServo.attach(SERVO_PIN);
  tutupPintuPakan(); // Awal tertutup
}

void loop() {
  server.handleClient();

  long jarak = getDistance();
  Serial.print("📏 Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  unsigned long waktuSekarang = millis();

  // Jika belum sedang mengisi dan waktu cukup lama sejak terakhir isi
  if (!sedangMengisi && (waktuSekarang - waktuTerakhirIsi >= JEDA_ISI_PAKAN)) {
    if (jarak >= JARAK_BUKA) {
      bukaPintuPakan();  // buka dan mulai timer
    }
  }

  // Jika sedang mengisi, cek apakah waktunya menutup
  if (sedangMengisi && (waktuSekarang - waktuMulaiIsi >= DURASI_BUKA)) {
    tutupPintuPakan();  // tutup setelah 5 detik
  }

  delay(200); // loop ringan
}
