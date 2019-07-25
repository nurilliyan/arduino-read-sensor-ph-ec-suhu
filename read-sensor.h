/*
 * Deklarasi pH
 * Digunakan untuk menentukan tipe variabel dan penentuan pin input analog pH
 */
#define Offset 0.14                      //Nilai penyimpangan
#define SensorPin A0                     //Pin Analog 0 untuk input data sensor pH meter SEN0161
#define pHsamplingInterval 25            //Interval waktu pembacaan analog sampel pH tiap 25 mili detik
#define pHprintInterval 1000             //Nilai pH di print out atau ditampilkan setiap 1000 mili detik
#define ArrayLenth  40                   //Jumlah maksimal panjang data [index] didalam array 
unsigned int pHArray[ArrayLenth];        //Hasil nilai rata-rata analog yang masuk dari sensor
byte pHArrayIndex=0;                     //Index pembacaan analog pH mulai dari index pertama [0]
unsigned long pHsamplingTime;            //Deklarasi variabel pHsamplingTime
unsigned long pHprintTime;               //Deklarasi variabel pHprintTime
float pHvoltage;                         //Tipe data untuk hasil tegangan pH berupa float
float pHValue;                           //Tipe data untuk hasil nilai pH berupa float

/*
 * Deklarasi EC
 * Digunakan untuk menentukan tipe variabel dan penetuan pin analog input EC dan digital input suhu
 */
#define ECOffset 0.07                     //Nilai penyimpangan
#define ECsensorPin A1                    //Pin Analog 1 untuk input data sensor EC meter DFR0300
#define AnalogSampleInterval 50           //Interval waktu pembacaan analog sampel EC tiap 50 mili detik
#define printInterval 1000                //Nilai EC print out atau ditampilkan setiap 1000 mili detik
#define numReadings 20                    //Jumlah maksimal panjang data [index] didalam array
unsigned int readings[numReadings];       //Membaca jumlah index hasil pembacaan analog
unsigned int AnalogAverage = 0;           //Hasil nilai rata-rata analog
byte index = 0;                           //Index pembacaan analog EC mulai dari index pertama [0]
unsigned long AnalogValueTotal = 0;       //Jumlah nilai total analog yang terbaca dalam array
unsigned long AnalogSampleTime;           //Deklarasi variabel AnalogSampleTime
unsigned long printTime;                  //Deklarasi variabel printTime (untuk EC dan suhu DS18B20)
float CoefficientVolatge;                 //Koefisien votage yang digunakan untuk menghitung EC
float averageVoltage=0;                   //Hasil tegangan EC dengan tipe data berupa float
float ECcurrent;                          //Tipe dan untuk hasil nilai EC berupa float

/*
 * Deklarasi Suhu DS18B20
 * Digunakan untuk menentukan tipe variabel dan penentuan pin input Suhu DS18B20
 */
#include <OneWire.h>                      //Modul Sensor Suhu
#define StartConvert 0                    //Memulai mengkonversi hasil pembacaan suhu dari sensor 
#define ReadTemperature 1                 //Memulai pengukuran hasil pembacaan suhu dari sensor 
#define DS18B20_Pin 2                     //Pin Digital 2 untuk sensor suhu DS18B20
unsigned int tempSampleInterval=1000;     //Interval waktu pembacaan suhu
unsigned long tempSampleTime;             //Deklarasi variabel tempSampleTime
float temperature;                        //Tipe data untuk hasil nilai suhu berupa float
OneWire ds(DS18B20_Pin);                  //(Modul tamabahan)Temperature chip i/o pada digital input 2


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}