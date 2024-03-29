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


//#######################################################################################################
void setup() {
  Serial.begin(9600);                 // Serial komunikasi atau baud rate
  /*
  * Print Out Ke Dalam Excel
  * Excel yang digunakan merupakan workbook dari plxdag, dimana didalam excel dapat langsung membaca hasil kalibrasi sensor
  */
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Waktu, Nilai Tegangan pH, Nilai pH, Nilai Tegangan EC, Niali EC, Nilai Suhu");
  Serial.println("RESETTIMER");
  /*
  * Inisilisasi pH
  * Menginisilisaasi variabel
  */
  pHsamplingTime=millis();           //pHsamplingTime dijalankan dengan fungsi millis() dari 0 mili detik
  pHprintTime=millis();              //pHprintTime dijalankan dengan fungsi millis() dari 0 mili detik
  /*
  * Inisilisasi EC dan Suhu
  * Menginisilisaasi semua baccan ke millis() = 0
  */
  for (byte thisReading = 0; thisReading < numReadings; thisReading++)     //Mulai Looping dimana (thisReading=0; thisReading<20; thisReading++)
    readings[thisReading] = 0;                                             //readings[thisReading] dimulai dari index 0 atau readings[0]       
  TempProcess(StartConvert);                                               //Memulai konversi sensor suhu DS18B20 dari 12 bit yang terbaca
  AnalogSampleTime=millis();                                               //AnalogSampleTime dijalankan dengan fungsi millis() dari 0 mili detik
  printTime=millis();                                                      //printTime dijalankan dengan fungsi millis() dari 0 mili detik
  tempSampleTime=millis();                                                 //tempSampleTime dijalankan dengan fungsi millis() dari 0 mili detik
}
//#######################################################################################################


//#######################################################################################################
void loop() {
   /*
   * Menghitung Rata-rata nilai pH dalam array
   * Setiap Sesekali menghitung nilai sampel pH pada tiap index dalam array dan menghitung rata-rata
   */
   if(millis()-pHsamplingTime > pHsamplingInterval)            //Jika pHsamplingTime > 1000 mili detik
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);           //Maka nilai analog dari sensor pH dibaca mulai dari index pertama sampai terakhir
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;              //Jika sudah terbaca ada 40 index data yang masuk, maka index dikembalikan ke posisi awal 
      pHvoltage = avergearray(pHArray, ArrayLenth)*5.0/1024;   //Rumus menghitung tegangan pH dimana nilai pHarray dan ArrayLenth dihitung dalam fungsi avergearray()
      pHValue = 3.5*pHvoltage+Offset;                          //Rumus menghitung nilai pH
      pHsamplingTime=millis();                                 //Nilai pHsamplingTime dikembalikan pada kondisi awal yaitu 0 mili detik
  }
  /*
   * Menghitung Rata-rata nilai analog EC dalam array
   * Setiap Sesekali menghitung nilai sampel analog EC pada tiap index dalam array dan menghitung rata-rata
   */
  if(millis()-AnalogSampleTime>=AnalogSampleInterval)         //Jika AnalogSampleTime >= 50 mili detik
  {
    AnalogSampleTime=millis();                                //Maka AnalogSampleTime = 0 mili deitk
    readings[index] = analogRead(ECsensorPin);                //Readings[index] membaca hasil analog index ke ...
    AnalogValueTotal = AnalogValueTotal + readings[index];    //Menghitung jumlah total analog yang terbaca dari total readings[index] yang terbaca
    index = index + 1;                                        //Maju ke posisi index berikutnya dalam array
    if (index >= numReadings)                                 //Jika posisi index sudah mencapai akhir dari jumlah index dalam array >= 20
    index = 0;                                                //Kembalikan nilai index ke 0
    AnalogAverage = AnalogValueTotal / numReadings;           //Menghitung rata-rata Analog yang terbaca dari dalam array
    averageVoltage = AnalogAverage*5000/1024;                 //Hasil nilai penghitungan rata-rata tegangan yang dihasilkan dari analog (mV)
    CoefficientVolatge = averageVoltage;                      //CoefficientVoltage = tegangan (mV)
    if(CoefficientVolatge<150 && CoefficientVolatge>=596){    //Jika nilai tegangan yang terbaca <150 mV dan >= 596 mV
      ECcurrent=0;                                            //Maka nilai EC dikembalikan ke 0
    }
    else                                                      //Jika tidak atau lainnya
    { 
      ECcurrent=6.84*CoefficientVolatge-64.32;                 //Nilai EC terhitung dalam satuan mS/cm                     
      ECcurrent = ECcurrent+ECOffset;                          //Nilai EC yang sesungguhnya setelah diketahui selisih dengan nilai penyimpangannya
    }
  }
  /*
   * Membaca suhu dan mengkonversi
   * Setiap sesekali suhu dibaca dan mulai dikonversi oleh DS18B20. Namnu, interval minimum antara mulai konversi dengan mambaca suhu minimal 750 ms agar mendapat data akurat
   */
   if(millis()-tempSampleTime>=tempSampleInterval)            //Jika tempSampleTime >= 1000 mili detik
  {
    tempSampleTime=millis();                                  //Maka tempSampleTime = 0 mili detik
    temperature = TempProcess(ReadTemperature);               //Baca suhu sekarang dari sensor DS18B20
    TempProcess(StartConvert);                                //konversi hasil bacaan suhu sensor DS18B20 dari data biner menjadi float
  }
   /*
    * Tampilan hasil pembacaan pH, EC, dan suhu
    * Mencetak hasil pengukuran dalam serial monitor dan ecxel untuk rekapan data kalibrasi pH, EC, dan suhu
   */
   if(millis()- pHprintTime >= pHprintInterval && millis()-printTime>=printInterval)  //jika pHprintTime >= 1000 mili detik & printTime >= 1000 mili detik
   {
   printTime=millis();                                     //Maka prinTime dikembalikan ke fungsi millis() awal
   pHprintTime=millis();                                   //Maka pHprinTime dikembalikan ke fungsi millis() awal        
   pHvoltage = pHvoltage*1000;                             //Membuat nilai tegangan pH dari V menjadi mV    
   Serial.print("DATA,TIME,");                             //Digunakan untuk menghubungkan antara plxdiag dengan arduino
// 1. Print Out Tegangan Suhu dan Suhu                     
      Serial.print((int)pHvoltage);                      //Print out tegangan pH dalam mV dengan tipe data integer
      Serial.print(",");
      Serial.print(pHValue,2);                             //Print out hasil nilai pH (dua desimal)
// 2. Print Out Tegangan EC dan EC
      Serial.print(",");
      Serial.print(averageVoltage);                      //Print out tegangan EC dalam mV
      Serial.print(",");
      Serial.print(ECcurrent,2);                           //Print out hasil nilai EC (dua desimal)
//  3. Print Out Nilai Suhu
      Serial.print(",");
      Serial.print(temperature,2);                         //Print out hasil nilai temperature atau suhu (Celcius)
      Serial.print(",");
      Serial.println("");                                  //Print out untuk membuat baris baru
  }
}
//#######################################################################################################


//#######################################################################################################
/*
 * Fungsi avergearray()
 * Untuk menghitung rata-rata jumlah analog yang masuk pada pH
 */
double avergearray(int* arr, int number){        //Membaca & mengenmbalikan nilai (arr = pHarray) & (number = arrayLenth)
  int i;                                         //Deklarasi variabel i dengan tipe data integer
  int max,min;                                   //Deklarasi variael min & max dengan tipe data integer
  double avg;                                    //Deklarasi variabel avg (average) dengan tipe data double
  long amount=0;                                 //Deklarasi variabel amount dengan tipe data long
  if(number<=0){                                 //Kemungkinan 1. Jika panjang data index (number) terbaca <= 0
    return 0;                                    //Maka nilai dikemablikan ke 0 (karna tidak ada data yang terbaca dari sennsor)
  }
  if(number<5){                                  //Kemungkinan 2. Jika panjang data index (number) terbaca < 5
    for(i=0;i<number;i++){                       //Maka lakukan Looping dimulai dari i=0 sampai i=4 (ada maksimal 5 index yang terbaca)
      amount+=arr[i];                            //Maka nilai hasil analog pembacaan sensor (amount) ditambah mulai i=0 sampai i=4
    }
    avg = amount/number;                         //Maka nilai hasil rata-rata analog yang terbaca amount/number
    return avg;
  }else{                                         //Jika tidak masuk di kemungkinan 1 & 2 maka lanjut ke kemungkinan ke 3 
    if(arr[0]<arr[1]){                           //Jika nilai pembacaan analog pH index[0] < index[1]
      min = arr[0];max=arr[1];                   //Maka nilai min = hasil analog index[0]  & nilai max = hasil analog index[1]
    }
    else{                                        //Jika nilai pembacaan analog pH index[0] tidak < index[1]
      min=arr[1];max=arr[0];                     //Maka nilai min = hasil analog index[1]  & nilai max = hasil analog index[0]
    }
    for(i=2;i<number;i++){                       //Looping untuk i dimulai dari 2 & i < total index yang terbaca oleh sensor (number)
      if(arr[i]<min){                            //Jika hasil analog index ke i < nilai min (arr < min)
        amount+=min;                             //Maka amount = min
        min=arr[i];                              //Maka nilai min = nilai minimal yang terbaca pada index ke [i]
      }else {                                    
        if(arr[i]>max){                          //Jika hasi analog index ke i > nilai max (arr > max)
          amount+=max;                           //Maka amount = max
          max=arr[i];                            //Maka nilai max = nilai maximal yang terbaca pada index ke [i]
        }else{
          amount+=arr[i];                        //min<=arr<=max        
        }
      }
    }
    avg = (double)amount/(number-2);             //Nilai rata-rata analog diperoleh dari (nilai minimal + nilai maksimal) / jumlah data
  }
  return avg;                                    //Return atau kembalikan nilai rata-rata analog yang masuk dari sensor (avg)
}
/*
 * Fungsi avergearray()
 * Untuk membaca hasil pengukuran suhu yang masuk dalam Arduino dalam bentuk bit
*/
float TempProcess(bool ch)
{
  //returns the temperature from one DS18B20 in DEG Celsius
  static byte data[12];
  static byte addr[8];
  static float TemperatureSum;
  if(!ch){
          if ( !ds.search(addr)) {
              ds.reset_search();
              return 0;
          }      
          if ( OneWire::crc8( addr, 7) != addr[7]) {
              return 0;
          }        
          if ( addr[0] != 0x10 && addr[0] != 0x28) {
              return 0;
          }      
          ds.reset();
          ds.select(addr);
          ds.write(0x44,1); 
  }
  else{  
          byte present = ds.reset();
          ds.select(addr);    
          ds.write(0xBE); 
          for (int i = 0; i < 9; i++) {
            data[i] = ds.read();
          }         
          ds.reset_search();           
          byte MSB = data[1];
          byte LSB = data[0];        
          float tempRead = ((MSB << 8) | LSB); 
          TemperatureSum = tempRead / 16;
    }
    return TemperatureSum;  
}