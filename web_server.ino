#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <NTPClient.h>
#include <analogWrite.h>
#include <SD.h>
#include <math.h>

//file html 
#include "html.h" 

//update_time per detik
#define update_time 1000

//pin 
#define CS_PIN 5
#define pin_potensio1 34
#define pin_potensio2 35
#define pin_led 4

//define IP static but will make the internet close
IPAddress ip(192, 168, 43, 26); //sesuaikan dengan ip wifi
IPAddress gateway(192, 168, 43, 1); //sesuaikan dengan ip diatas
IPAddress subnet(255,255,255,0);

//variable
int data_potensio1=0,data_potensio2=0;
String kondisi_lampu = "";
String data_lama_lampu = "";
String data_baru_lampu = "";
String dataString;
int data_baru_suhu = 0;
File dataFile;
String sdCardMode;
//variable fuzzy
float cahayaLuarGelap, cahayaLuarRedup, cahayaLuarTerang, cahayaDalamGelap, cahayaDalamRedup, cahayaDalamTerang;
float minR1, minR2, minR3, minR4, minR5, minR6, minR7, minR8, minR9;
float lampuR1,lampuR2,lampuR3,lampuR4, lampuR5, lampuR6, lampuR7, lampuR8, lampuR9;
float hasil_COA;
//variable waktu
String data_hari, data_tanggal, data_jam;
String waktuManual = "20/10/1998 00:00:00";
int tahun,bulan,tanggal,jam,menit,detik;
int jumlah_tanggal = 30;

//variable sampling time
unsigned long real_time,flag_reset,real_time_before;

//kondisi button Start Stop
String Button = "Auto",lastButton;

//define wifi
const char* username = "Redmi Note 9";
const char* password = "12345678";

//sesuai dengan flash frequency yang di set
WebServer server(80); 

//define NTP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//--------------------Fuction For all--------------------------------//

//_______Fuction for Setup___________//

void get_time_manual(){
  waktuManual = server.arg("Manual");
  //Serial.println(waktuManual);
  tahun = waktuManual.substring(0,4).toInt();
  //Serial.println(tahun);
  bulan = waktuManual.substring(5,7).toInt();
  //Serial.println(bulan);
  tanggal = waktuManual.substring(8,10).toInt();
  //Serial.println(tanggal);
  jam = waktuManual.substring(11,13).toInt();
  //Serial.println(tanggal);
  menit = waktuManual.substring(14,16).toInt();
  //Serial.println(tanggal);
  detik = waktuManual.substring(17,19).toInt();
  //Serial.println(tanggal);
}
//waktu auto membutuhkan internet untuk awalannya setelah itu akan di counting oleh millis()
void get_time_auto(){
  if(!timeClient.update()){
    timeClient.forceUpdate();
  }
  data_hari = timeClient.getFormattedDate();
  Serial.println(data_hari);
  //get data tahun bulan tanggal
  int flag = data_hari.indexOf("T");
  data_tanggal = data_hari.substring(0,flag);
  tahun = data_tanggal.substring(0,4).toInt();
  bulan = data_tanggal.substring(5,7).toInt();
  tanggal = data_tanggal.substring(8,10).toInt();
  //get data jam menit detik
  data_jam = data_hari.substring(flag+1, data_hari.length()-1);
  jam = data_jam.substring(0,2).toInt();
  menit = data_jam.substring(3,5).toInt();
  detik = data_jam.substring(6,8).toInt();
}

//fungsi yang dipanggil untuk load html
void panggil_html() {
  Button = "Start";
  flag_reset = real_time;
  String call = MAIN_page; 
  //mencari nama yang tertera pada html
  if( server.hasArg("Manual") ) {
    get_time_manual();
    server.send(200, "text/html", call);
  }else if(server.hasArg("Auto")){
    get_time_auto();
    server.send(200, "text/html", call);
  }else {
    tanggal = waktuManual.substring(0,2).toInt();
    bulan = waktuManual.substring(3,5).toInt();
    tahun = waktuManual.substring(6,10).toInt();
    jam = waktuManual.substring(11,13).toInt();
    menit = waktuManual.substring(14,16).toInt();
    detik = waktuManual.substring(17,19).toInt();
    server.send(200, "text/html", call);
  }  
}
 
void Start() {
  Button = "Auto";
  String json = "{\"Tanggal\":\""+String(data_tanggal)+"\",\"Waktu\":\""+String(data_jam)+"\",\"Kondisi_lampu\":\""+kondisi_lampu+"\", \"Data_potensio\":\""+ String(hasil_COA) +"\"}";
  server.send(200, "text/plane", json); 
}
void Manual_ON(){
  Button = "Manual_ON"; 
  String json = "{\"Tanggal\":\""+String(data_tanggal)+"\",\"Waktu\":\""+String(data_jam)+"\",\"Kondisi_lampu\":\""+kondisi_lampu+"\", \"Data_potensio\":\""+ String(hasil_COA) +"\"}";
  server.send(200, "text/plane", json);
}
void Manual_OFF(){
  Button = "Manual_OFF"; 
  String json = "{\"Tanggal\":\""+String(data_tanggal)+"\",\"Waktu\":\""+String(data_jam)+"\",\"Kondisi_lampu\":\""+kondisi_lampu+"\", \"Data_potensio\":\""+ String(hasil_COA) +"\"}";
  server.send(200, "text/plane", json);
}
//_______END of Fuction for Setup___________//

//________Fuction for loop___________//
//menghitung jumlah hari dalam 1 bulan
void check_jumlah_tanggal_dalam_1_bulan(int bulan){
  switch(bulan){
    case 2:
    if(tahun%4==0){
      if(tahun%100==0){
        if(tahun%400==0){
          jumlah_tanggal = 29;
        }else{
          jumlah_tanggal = 28;
        }
      }else{
        jumlah_tanggal=29;
      }
    }else{
      jumlah_tanggal=28;
    }
    break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12: jumlah_tanggal = 31; break;

    case 4:
    case 6:
    case 9:
    case 11: jumlah_tanggal = 30;break;

    default: jumlah_tanggal = 30;
  }
}
//counting waktu
void counting_time(){
   detik ++;
    if(detik >= 60){
      detik = 0;
      menit ++;
      if(menit >= 60){
        menit = 0;
        jam ++;
        if(jam >= 24){
          jam = 0;
          tanggal ++;
          if(tanggal >= 28){
            check_jumlah_tanggal_dalam_1_bulan(bulan);
          }
          if(tanggal > jumlah_tanggal){
            tanggal = 1;
            bulan ++;
            if(bulan > 12){
              bulan = 1;
              tahun ++;  
            }
          }
        }
      }
    }
}

//add sensor in here
/*void sensor(){
  if(Current > Speed ) Speed ++ ;
  if(Voltage > Current )Current ++ ;
  Voltage ++;
}*/
//write in sdcard
int SDCARD(String target) {
  if(target == "setup"){
    Serial.print("SD CARD...");
    if (!SD.begin(CS_PIN)) 
      Serial.println("Failed.");
    else
      Serial.println("Ready");
  }
  dataFile = SD.open("DATA_LOGER.txt", FILE_WRITE);
  Serial.println(dataFile);
  //jika file dibuka dengan benar, data  ditulis
  if (dataFile) {
    Serial.println("File Berhasil diBuka");
    if(target == "setup"){   
      dataString += "Kondisi Lampu" ;
      dataString += "t\t" ;
      
      dataString += "Nilai Intensitas" ;
      dataString += "\t" ;
      
      dataString += "Waktu" ;
      dataString += "\t" ;
      
      dataFile.println(dataString);
    }else if(target == "data"){
      dataFile.print(kondisi_lampu);
      dataFile.print("\t");
      dataFile.print(hasil_COA);
      dataFile.print("\t");
      dataFile.println(data_jam);
    }
    dataFile.close();
  }
  else {
  //jika file tidak dapat dibuka, data tidak akan ditulis
    //Serial.println("Gagal membuka file LOG.txt");
  }
  //menunggu interval untuk pembacaan data baru
 dataString = " " ;
}
//fuzzy logic
float Cahaya(float a, float b, float c, float z){
    float hasil;
    if((z>=a)&&(z<b)) hasil = (z-a)/(b-a);
    if((z>=b)&&(z<c)) hasil = (c-z)/(c-b);
    if(z<=a){
        if(a == 0) hasil = 1;
        else hasil = 0;
    }
    if(z>=c){
        if(c == 255) hasil = 1;
        else hasil = 0;
    }
    return hasil;
}

float Min(float a,float b){
    float hasil_min;
    if(a<b)
        hasil_min=a;
    else
        hasil_min=b;
    return hasil_min;
}

void fuzzy(float intensitasCahayaLuar,float intensitasCahayaDalam){
  // Fuzzyfikasi
    cahayaLuarGelap = Cahaya(0, 62, 127, intensitasCahayaLuar);
    //printf("Fungsi keanggotaan cahaya di luar ruangan gelap : %.2f\n", cahayaLuarGelap);
    cahayaLuarRedup = Cahaya(62, 127, 192, intensitasCahayaLuar);
    //printf("Fungsi keanggotaan cahaya di luar ruangan redup : %.2f\n", cahayaLuarRedup);
    cahayaLuarTerang = Cahaya(127, 192, 255, intensitasCahayaLuar);
    //printf("Fungsi keanggotaan cahaya di luar ruangan terang : %.2f\n", cahayaLuarTerang);

    cahayaDalamGelap = Cahaya(0, 62, 127, intensitasCahayaDalam);
    //printf("Fungsi keanggotaan cahaya di dalam ruangan gelap : %.2f\n", cahayaDalamGelap);
    cahayaDalamRedup = Cahaya(62, 127, 192, intensitasCahayaDalam);
    //printf("Fungsi keanggotaan cahaya di dalam ruangan redup : %.2f\n", cahayaDalamRedup);
    cahayaDalamTerang = Cahaya(127, 192, 255, intensitasCahayaDalam);
    //printf("Fungsi keanggotaan cahaya di dalam ruangan terang : %.2f\n", cahayaDalamTerang);

    // rule 1 : IF Cahaya Luar GELAP And Cahaya Dalam GELAP THEN Lampu NYALA
    minR1=Min(cahayaLuarGelap, cahayaDalamGelap);
    //printf("Minimum Cahaya Luar GELAP And Cahaya Dalam GELAP : %.2f\n",minR1);
    lampuR1 = 255;
    // rule 2 : IF Cahaya Luar GELAP And Cahaya Dalam REDUP THEN Lampu REDUP
    minR2=Min(cahayaLuarGelap, cahayaDalamRedup);
    //printf("Minimum Cahaya Luar GELAP And Cahaya Dalam REDUP : %.2f\n",minR2);
    lampuR2 = 255;
    // rule 3 : IF Cahaya Luar GELAP And Cahaya Dalam TERANG THEN Lampu NYALA
    minR3=Min(cahayaLuarGelap, cahayaDalamTerang);
    //printf("Minimum Cahaya Luar GELAP And Cahaya Dalam TERANG : %.2f\n",minR3);
    lampuR3 = 127;
    // rule 4 : IF Cahaya Luar REDUP And Cahaya Dalam GELAP THEN Lampu NYALA
    minR4=Min(cahayaLuarRedup, cahayaDalamGelap);
    //printf("Minimum Cahaya Luar REDUP And Cahaya Dalam GELAP : %.2f\n",minR4);
    lampuR4 = 127;
    // rule 5 : IF Cahaya Luar REDUP And Cahaya Dalam REDUP THEN Lampu REDUP
    minR5=Min(cahayaLuarRedup, cahayaDalamRedup);
    //printf("Minimum Cahaya Luar REDUP And Cahaya Dalam REDUP : %.2f\n",minR5);
    lampuR5 = 127;
    // rule 6 : IF Cahaya Luar REDUP And Cahaya Dalam TERANG THEN Lampu REDUP
    minR6=Min(cahayaLuarRedup, cahayaDalamTerang);
    //printf("Minimum Cahaya Luar REDUP And Cahaya Dalam TERANG : %.2f\n",minR6);
    lampuR6 = 0;
    // rule 7 : IF Cahaya Luar TERANG And Cahaya Dalam GELAP THEN Lampu REDUP
    minR7=Min(cahayaLuarTerang, cahayaDalamGelap);
    //printf("Minimum Cahaya Luar TERANG And Cahaya Dalam GELAP : %.2f\n",minR7);
    lampuR7 = 255;
    // rule 8 : IF Cahaya Luar TERANG And Cahaya Dalam REDUP THEN Lampu MATI
    minR8=Min(cahayaLuarTerang, cahayaDalamRedup);
    //printf("Minimum Cahaya Luar TERANG And Cahaya Dalam REDUP : %.2f\n",minR8);
    lampuR8 = 127;
    // rule 9 : IF Cahaya Luar TERANG And Cahaya Dalam TERANG THEN Lampu MATI
    minR9=Min(cahayaLuarTerang, cahayaDalamTerang);
    //printf("Minimum Cahaya Luar TERANG And Cahaya Dalam TERANG : %.2f\n",minR9);
    lampuR9 = 0;

    // Defuzzyfikasi
    float pembilang = minR1 * lampuR1 + minR2 * lampuR2 + minR3 * lampuR3 + minR4 * lampuR4 + minR5 * lampuR5 + minR6 * lampuR6 + minR7 * lampuR7 + minR8 * lampuR8 + minR9 * lampuR9;
    float penyebut = minR1 + minR2 + minR3 + minR4 + minR5 + minR6 + minR7 + minR8 + minR9;
    hasil_COA = pembilang/penyebut;
    Serial.print("Nilai value Lampu atau LED : ");
    Serial.println(hasil_COA);
}
//actuator and sensor process
void actuator_sensor(){
  data_potensio1 = analogRead(pin_potensio1)/16;
  Serial.print("Nilai value Lampu atau LED luar : ");
  Serial.println(data_potensio1);
  data_potensio2 = analogRead(pin_potensio2)/16;
  Serial.print("Nilai value Lampu atau LED dalam : ");
  Serial.println(data_potensio2);
  fuzzy(data_potensio1,data_potensio2);
  if(Button == "Auto"){
    analogWrite(pin_led,hasil_COA);
    if (hasil_COA == 0)
    {
      kondisi_lampu = "mati";
  //    Serial.println("Lampu Mati");
    }
    
    else if ((hasil_COA >= 1) && (hasil_COA <= 400))
    {
      kondisi_lampu = "redup";
  //    Serial.println("Lampu Redup");
    }
    else if ( (hasil_COA >400) && (hasil_COA <= 1024))
    {
      kondisi_lampu = "terang";
  //    Serial.println("Lampu Terang"); 
    }
  }else if (Button == "Manual_ON"){
    kondisi_lampu = "terang";
    analogWrite(pin_led,255);
  }else if (Button == "Manual_OFF"){
    kondisi_lampu = "mati";
    analogWrite(pin_led,0);
  }
  data_baru_suhu = hasil_COA;
  data_baru_lampu = kondisi_lampu;
  if ( data_lama_lampu != data_baru_lampu)
  {
    sdCardMode="data";
    SDCARD(sdCardMode);
    Serial.println("data telah tersimpan");
    data_lama_lampu = data_baru_lampu;
  }
}

//millis untuk flag 1 detik
void Update_data(){
  real_time = millis() - flag_reset;
  if(real_time - real_time_before >= update_time){
    counting_time();
    real_time_before = real_time;
    /*if(Button == "Start"){
      sensor();
    }*/
    data_jam = String(jam) + ":" +String(menit)+":"+String(detik);
    data_tanggal = String(tanggal) + "/" +String(bulan) + "/" + String(tahun) + " " + String(jam) + ":" + String(menit) + ":" + String(detik);
    actuator_sensor();
    //Serial.println(data_tanggal);
  }
}
//________END of Fuction for loop___________//

//--------------------End of Fuction For all--------------------------------//

void setup()
{
  Serial.begin(115200);
  pinMode(pin_potensio1, INPUT);
  pinMode(pin_potensio2, INPUT);
  pinMode(pin_led, OUTPUT);
  sdCardMode = "setup";
  SDCARD(sdCardMode);

  //if u want to make ip static like u want
  //WiFi.config(ip,gateway,subnet);

  //mulai untuk menghubungkan kepada wifi yang ingin diconnectkan
  WiFi.begin(username, password);     

  //hanya sebagai tanda
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.println(username);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  

  //untuk load html ketika ada 
  server.on("/", panggil_html);     
  //untuk load data using xmlhttp untuk update data ke javacript dan tergantung 
  //hal apa yang di request oleh client pada java script 
  server.on("/Manual_ON", Manual_ON);
  server.on("/Manual_OFF", Manual_OFF);
  server.on("/Start", Start);

  //setting for using network time protocol (NTP) for update time from internet
  timeClient.begin();
  //3600 dikali dengan GMT yang berlaku di daerahmu misal GMT +7 maka : 3600 * +7 = +25200
  timeClient.setTimeOffset(25200);

  server.begin();                 
  Serial.println("Bismillah sukses dengan cara yang baik");
}

void loop()
{
  //Handle client requests
  server.handleClient();

  //update data
  Update_data();

  //untuk mengecek state benar apa tidak 
  //Serial.println(Voltage);
  if(Button != lastButton){
    Serial.println(Button);
    lastButton = Button;
  }
}
