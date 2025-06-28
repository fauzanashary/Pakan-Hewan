Pakan Kucing Otomatis dengan ESP8266
Proyek pakan kucing otomatis berbasis IoT menggunakan ESP8266, sensor ultrasonik, dan motor servo. Alat ini secara cerdas mendeteksi level pakan dalam mangkuk dan mengisinya kembali secara otomatis. Dilengkapi dengan antarmuka web untuk pemantauan real-time melalui Access Point WiFi sendiri.

✨ Fitur Utama
 * Pengisian Otomatis: Dispenser terbuka saat sensor mendeteksi mangkuk kosong.
 * Deteksi Level Pakan: Menggunakan sensor jarak ultrasonik HC-SR04 untuk akurasi.
 * Antarmuka Web Monitoring: Pantau status pakan dan dispenser melalui browser di alamat IP 192.168.4.1.
 * Mode Access Point: Tidak memerlukan router internet. ESP8266 membuat jaringan WiFi sendiri.
 * Konfigurasi Mudah: Durasi pengisian, jeda, dan sensitivitas sensor dapat diatur dengan mudah di dalam kode.
🛠️ Komponen yang Dibutuhkan
 * Mikrokontroler ESP8266 (NodeMCU atau Wemos D1 Mini direkomendasikan).
 * Sensor Jarak Ultrasonik HC-SR04.
 * Motor Servo SG90 atau sejenisnya.
 * Kabel Jumper.
 * Power Supply 5V (bisa dari port USB atau adaptor).
 * Rangka/wadah untuk dispenser (dapat dibuat dengan 3D print, akrilik, atau bahan lainnya).
🔌 Skema Koneksi (Wiring)
Hubungkan semua komponen sesuai dengan tabel di bawah ini:
| Komponen | Pin ESP8266 |
|---|---|
| Motor Servo (Sinyal) | D3 (GPIO 0) |
| Sensor Ultrasonik (TRIG) | D1 (GPIO 5) |
| Sensor Ultrasonik (ECHO) | D2 (GPIO 4) |
| VCC (Servo & Sensor) | Vin / 5V |
| GND (Servo & Sensor) | GND |
Catatan: Jika mengalami masalah saat boot, coba pindahkan pin Servo dari D3 (GPIO 0) ke pin lain seperti D5 (GPIO 14) dan perbarui #define SERVO_PIN di dalam kode.
🚀 Instalasi dan Cara Penggunaan
 * Clone Repositori
   git clone https://github.com/USERNAME/REPO-NAME.git
cd REPO-NAME

 * Setup Arduino IDE
   * Buka Arduino IDE.
   * Pastikan Anda sudah menginstal ESP8266 Core untuk Arduino. Jika belum, ikuti panduan ini.
   * Buka file .ino dari repositori ini.
 * Instalasi Library
   * Buka Sketch > Include Library > Manage Libraries....
   * Cari dan instal library berikut:
     * ESP8266WebServer (biasanya sudah termasuk dalam ESP8266 Core)
     * Servo (biasanya sudah termasuk dalam Arduino IDE)
 * Konfigurasi (Opsional)
   * Buka file kode .ino. Anda dapat menyesuaikan parameter berikut sesuai kebutuhan:
   <!-- end list -->
   // WiFi Access Point
const char *ssid = "PakanKucing_AP";
const char *password = "12345678"; 

// Batas ketinggian pakan (dalam cm)
const int JARAK_BUKA = 2;

// Waktu servo terbuka (dalam milidetik)
const unsigned long DURASI_BUKA = 5000;

// Jeda minimal antar pengisian (dalam milidetik)
const unsigned long JEDA_ISI_PAKAN = 30000;

 * Upload ke ESP8266
   * Pilih board yang sesuai (misalnya: "NodeMCU 1.0 (ESP-12E Module)") dan Port COM yang benar.
   * Klik tombol Upload.
 * Jalankan Alat
   * Setelah proses upload selesai, nyalakan perangkat Anda.
   * Ambil smartphone atau laptop, cari jaringan WiFi bernama "PakanKucing_AP".
   * Hubungkan ke jaringan tersebut dengan kata sandi "12345678".
   * Buka browser dan kunjungi alamat http://192.168.4.1.
   * Anda akan melihat halaman monitoring yang menampilkan jarak pakan dan status dispenser. Halaman ini akan me-refresh secara otomatis.
⚙️ Cara Kerja Kode
 * setup(): Menginisialisasi Serial, membuat Access Point WiFi, mendefinisikan route untuk server web, dan mengatur pin untuk sensor serta servo.
 * loop():
   * server.handleClient(): Terus-menerus mendengarkan permintaan dari klien (browser).
   * getDistance(): Mengukur jarak pakan saat ini.
   * Logika utama memeriksa dua kondisi:
     * Jika pakan kosong (jarak >= JARAK_BUKA) dan sudah melewati waktu jeda (JEDA_ISI_PAKAN), maka panggil bukaPintuPakan().
     * Jika pintu sedang terbuka, sebuah timer akan berjalan. Setelah DURASI_BUKA tercapai, panggil tutupPintuPakan().
 * handleRoot(): Fungsi yang dipanggil saat browser mengakses alamat IP. Fungsi ini membuat halaman HTML dinamis yang berisi data terbaru dari sensor.
🤝 Berkontribusi
Kontribusi Anda sangat kami hargai! Jika Anda memiliki ide untuk perbaikan atau menemukan bug, silakan buka issue atau buat pull request.
 * Fork repositori ini.
 * Buat branch baru (git checkout -b fitur/FiturBaru).
 * Commit perubahan Anda (git commit -am 'Menambahkan fitur baru').
 * Push ke branch Anda (git push origin fitur/FiturBaru).
 * Buat Pull Request baru.
📜 Lisensi
Proyek ini dilisensikan di bawah Lisensi MIT. Lihat file LICENSE untuk detail lebih lanjut.
