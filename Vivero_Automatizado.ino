/////////////WIRE/////////
#include <Wire.h>
/////////////BLUETOOTH////
#include <SoftwareSerial.h>
SoftwareSerial I2CBT(10, 11);

byte serialA;
/////////////I2C//////////
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // inicializa la interfaz I2C del LCD 16x2DD

/////////////DTH11////////
#include "DHT.h"
#define DHTPIN 9 //Conectamos el Sensor al pin digital 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/////////////LDR////////////
const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ
const int LDRPin = A0;   //Pin del LDR
 
int V;
int ilum;

/////////////SENSOR DE MOVIMIENTO////////
byte sensorpir = 7;
byte alarmasensor = 13;

/////////////SENSOR DE LUZ AMBIENTAL//////
#include <BH1750.h>

BH1750 Luxometro;

uint16_t Lux_noche = 20;
uint16_t Lux_dia = 30;
int pinFoco = 13;

/////////////SENSOR DE HUMEDAD DE SUELO/////
int Humedad = 0; //Variable utilizada para calcular la humedad
int Lectura_Analogica = 0; //variable para leer el valor del pin analogico

////////////RTC//////////////
#include "RTClib.h"
RTC_DS3231 RTC;                  // inicializa el modulo RTC
int r_diaSemana;                  // almacena el resultado del dia de la semana calculado
const int regadera = 7;             // Pin 7 encargado de activar el timbre, se conecta al Rele
int segundo;
int minuto;
int hora;
int tiempo_regadera = 5000; // Tiempo continuo que dura el timbre sonando, en milisegundos 5000 = 5 segundos
/////////HORARIOS RTC////////
int h1_c1 = 7;   int m1_c1 = 30;   int s1_c1 = 0; //Entrada del Turno Mañana.
int h2_c1 = 8;   int m2_c1 = 10;  int s2_c1 = 0; //Primer cambio de Hora.
int h3_c1 = 8;   int m3_c1 = 50;  int s3_c1 = 0; //Comienzo del Primer Recreo T.Mañana.
int h4_c1 = 9;   int m4_c1 = 00;  int s4_c1 = 0; //Fin del Primer Recreo T.Mañana
int h5_c1 = 9;   int m5_c1 = 40;  int s5_c1 = 0; //Segundo cambio de Hora.
int h6_c1 = 10;  int m6_c1 = 20;  int s6_c1 = 0; //Comienzo del Segundo Recreo.
int h7_c1 = 10;  int m7_c1 = 30;  int s7_c1 = 0; //Fin del Primer Recreo.
int h8_c1 = 11;  int m8_c1 = 10;  int s8_c1 = 0; //Tercer cambio de Hora.
int h9_c1 = 11;  int m9_c1 = 50;  int s9_c1 = 0; //Primer Timbre de Salida.
int h10_c1 = 12; int m10_c1 = 30;  int s10_c1 = 0; //Segundo Timbre de Salida y Final del Turno Mañana.
int h11_c1 = 12; int m11_c1 = 50;  int s11_c1 = 0; //Segundo Timbre de Salida y Final del Turno Mañana.
int h12_c1 = 13; int m12_c1 = 30;  int s12_c1 = 0; //Entrada del Turno de Mañana.
int h13_c1 = 14; int m13_c1 = 10;  int s13_c1 = 0; //Primer cambio de Hora.
int h14_c1 = 14; int m14_c1 = 50;  int s14_c1 = 0; //Comienzo del Primer Recreo T.Tarde
int h15_c1 = 15; int m15_c1 = 0;   int s15_c1 = 0; //Fin del Primer Recreo T.Tarde.
int h16_c1 = 15; int m16_c1 = 40;  int s16_c1 = 0; //Segundo Cambio de Hora.
int h17_c1 = 16; int m17_c1 = 20;  int s17_c1 = 0; //Comienzo del Segundo Recreo T.Tarde.
int h18_c1 = 16; int m18_c1 = 30;  int s18_c1 = 0; //Fin del Segundo Recreo T.Tarde.
int h19_c1 = 17; int m19_c1 = 10;  int s19_c1 = 0; //Tercer Cambio de Hora.
int h20_c1 = 17; int m20_c1 = 50;  int s20_c1 = 0; //Primer Timbre de Salida.
int h21_c1 = 18; int m21_c1 = 30;  int s21_c1 = 0; //Segundo Timbre de Salida y Final del Turno Tarde.
//////////////FIN////////////////

void setup() {
  //////////RTC////////////
   pinMode(regadera, OUTPUT);                    // Configura como salida el pin 7
 Wire.begin();                               
 RTC.begin();                                // Inicia la comunicaci¢n con el RTC
 
 if (RTC.lostPower()) { //En caso de que el programa se apague o haya corte de luz esto volvera a colocarse en su horario correspondiente.
    Serial.println("EL RTC perdió potencia, vamos a configurar el tiempo!");
    // following line sets the RTC to the date & time this sketch was compile
 RTC.adjust(DateTime(__DATE__, __TIME__)); // Lee la fecha y hora del PC (Solo en la primera carga)
                                             // el anterior se usa solo en la configuracion inicial luego se pone como comentario
                                             // y se vuelve a cargar el programa sin esa linea.
 }                                             
 
  //////////LCD I2C/////////
  Serial.begin(9600);                         // Establece la velocidad de datos del puerto serie a 9600
  lcd.init();
  lcd.backlight();                            // Coloca luz de fondo al LCD
  lcd.clear();                                // Borra el  LCD

  //////////Bluetooth//////
  Serial.begin(9600);      //Inicia la velocidad en 9600 baudios

  //////////DHT11/////////
  dht.begin();

  /////////SENSOR MOVIMIENTO//////////
  pinMode(sensorpir, INPUT);
  pinMode(alarmasensor, OUTPUT);
}

void loop() {
  /////////SENSOR DE MOVIMIENTO//////////
  if (digitalRead(sensorpir) == HIGH)
  {
    Serial.println("¡Se ha detectado movimientos!");
    digitalWrite(alarmasensor, HIGH);
    delay(1000);
    digitalWrite(alarmasensor, LOW); 
  }
  /////////SENSOR DE HUMEDAD SUELO//////////
    char buffer[10];//Variable para crear una cadena
  Lectura_Analogica = analogRead(A0);//Leer el valor del potenciometro 
  Humedad = map(Lectura_Analogica, 0, 1023, 100, 0);//Escala para utilizarlo con el servo 
  //Mostrar mensajes en la LCD
  lcd.setCursor(1, 1); //posicionar el cursor fila 1 columna 1
  lcd.print("Sensor de humedad");
  lcd.setCursor(3, 2); //posicionar el cursor fila 2 columna 3
  lcd.print("Humedad=");
  sprintf(buffer,"%03d",Humedad);//crear una cadena para mostrar siempre 3 digitos
  lcd.print(buffer);//Mostrar el % de humedad
  lcd.print("%");
  delay(250);//Esperar 250 ms
  ///////////LDR////////////
     V = analogRead(LDRPin);         
 
   //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //usar si LDR entre GND y A0 
   ilum = ((long)V*A*10)/((long)B*Rc*(1024-V));    //usar si LDR entre A0 y Vcc (como en el esquema anterior)
  
   Serial.println(ilum);   
   delay(1000);

   ///////////////DHT11/////////////
int h = dht.readHumidity();    // Lee la humedad
int t= dht.readTemperature();
   
lcd.clear();//Elimina todos los simbolos del LCD
lcd.setCursor(0,0);//Posiciona la primera letra despues del segmento 5 en linea 1              
lcd.print("Humedad Relativa ");
lcd.setCursor(6,1);
lcd.print(h);//Escribe la humedad
lcd.print(" %");                     
delay (2500);
///////////////////////////////////////////////////              
lcd.clear();
lcd.setCursor(3,0);
lcd.print("Temperatura "); 
lcd.setCursor(6,1);
lcd.print(t);//Escribe la temperatura
lcd.print(" C'");                   
delay (2500);

/////////////RTC/////////////
DateTime now = RTC.now();          // Obtiene la fecha y hora del RTC

 int contacto1 = analogRead(A0);    //Lee el valor de los contactos para escoger el horario
 int contacto4 = analogRead(A1);    // contacto que activa o desactiva los fines de semana
 
 Serial.print(now.year(), DEC);  // A§o
 Serial.print('/');
 Serial.print(now.month(), DEC); // Mes
 Serial.print('/');
 Serial.print(now.day(), DEC);   // Dia
 Serial.print(' ');
 Serial.print(now.hour(), DEC);  // Horas
 Serial.print(':');
 Serial.print(now.minute(), DEC); // Minutos
 Serial.print(':');
 Serial.print(now.second(), DEC); // Segundos
 Serial.println();
 lcd.setCursor(0,0);
 lcd.print("D:");
 lcd.print(now.year(), DEC);
 lcd.print("/");
 lcd.print(now.month(), DEC);
 lcd.print("/");
 lcd.print(now.day(), DEC);
 lcd.print(" ");
 lcd.setCursor(0,1);
 lcd.print("T: ");
 lcd.print(now.hour(), DEC);
 lcd.print(":");
 lcd.print(now.minute(), DEC);
 lcd.print(":");
 lcd.print(now.second(), DEC);
 segundo=now.second();
 minuto=now.minute();
 hora=now.hour();
 //////////////
 int r_diaSemana=dia_de_semana();   // llama a la funcion que calcula el dia de la semana y lo almacena en r_diaSemana
 
 if ((r_diaSemana == 6 || r_diaSemana == 0)&&(contacto4 <= 1000)){  // si el contacto4 de Fin de semana esta apagado y es fin de semana no hace nada
 }
 else {
   if (contacto1 <= 1000)   // Si el contacto 1 esta activo (Horario 1)    
     horario_1();           // llama a la funcion que activa el horario 1

 }
 
 digitalWrite(regadera, HIGH);     // apaga el timbre
 delay(500);                    // La informaci¢n se actualiza cada 1/2 seg.
 lcd.setCursor(9,0);            // Borra parte de la pantalla del LCD
 lcd.print("                ");
 lcd.setCursor(8,1);
 lcd.print("                ");
}














  //////////////////////////////// Fin del void loop(), inician las Funciones (RTC/////////////////////////
  void activar_regadera(){
    digitalWrite(regadera, LOW); 
    lcd.setCursor(0,0);
    lcd.print("REGADERA ON ");
    Serial.println("REGADERA ON");
    delay(tiempo_regadera);
}    
/////////////////////////////// Calcula el dia de la Semana //////////////////////////////////
int dia_de_semana(){
 // Encuentar el dia de la semana de una fecha
 int n_dia;
 int r_dia;
 int n_mes;
 int t_mes;
 int n_anno;
 int d_anno;
 int t_siglo=6;

 DateTime now = RTC.now(); //fecha y hora del RTC
 lcd.setCursor(13,1);

 n_anno=(now.year()-2000);
 d_anno=n_anno/4;
 n_dia=now.day();
 n_mes=now.month();

 switch (n_mes) {
    case 1:
      t_mes=0;
      break;
    case 2:
      t_mes=3;
      break;
    case 3:
      t_mes=3;
      break;
    case 4:
      t_mes=6;
      break;
    case 5:
      t_mes=1;
      break;
    case 6:
      t_mes=4;
      break;
    case 7:
      t_mes=6;
      break;
    case 8:
      t_mes=2;
      break;
    case 9:
      t_mes=5;
      break;
    case 10:
      t_mes=0;
      break;
    case 11:
      t_mes=3;
      break;
    case 12:
      t_mes=5;
      break;
    default: 
      t_mes=t_mes;
    break;
 }

 r_dia=n_dia+t_mes+n_anno+d_anno+t_siglo;
 r_dia = r_dia % 7;

 switch (r_dia) {
    case 1:
       lcd.print("Lun");
        Serial.print(" Lun ");
      break;
      case 2:
       lcd.print("Mar");
       Serial.println(" Mar ");
      break;
      case 3:
       lcd.print("Mie");
       Serial.print(" Mie ");
      break;
      case 4:
       lcd.print("Jue");
       Serial.print(" Jue ");
      break;
      case 5:
       lcd.print("Vie");
       Serial.print(" Vie ");
      break;
      case 6:
       lcd.print("Sab");
       Serial.print(" Sab ");
      break;
      case 0:
       lcd.print("Dom");
       Serial.print(" Dom ");
      break;
      default: 
       lcd.print("---");
       Serial.print(" ---");
      break;
 } 
 return r_dia; 
}

/////////////////////Condicional del Horario 1  //////////////////////////////////
void horario_1(){ 
   lcd.setCursor(13,0);
   lcd.print(" ");
   Serial.print("Horario_1 ");
   if ((hora==h1_c1) && (minuto==m1_c1) && (segundo==s1_c1))  activar_regadera();
   if ((hora==h2_c1) && (minuto==m2_c1) && (segundo==s2_c1))  activar_regadera(); 
   if ((hora==h3_c1) && (minuto==m3_c1) && (segundo==s3_c1))  activar_regadera();
   if ((hora==h4_c1) && (minuto==m4_c1) && (segundo==s4_c1))  activar_regadera();
   if ((hora==h5_c1) && (minuto==m5_c1) && (segundo==s5_c1))  activar_regadera();
   if ((hora==h6_c1) && (minuto==m6_c1) && (segundo==s6_c1))  activar_regadera();
   if ((hora==h7_c1) && (minuto==m7_c1) && (segundo==s7_c1))  activar_regadera();
   if ((hora==h8_c1) && (minuto==m8_c1) && (segundo==s8_c1))  activar_regadera();
   if ((hora==h9_c1) && (minuto==m9_c1) && (segundo==s9_c1))  activar_regadera();
   if ((hora==h10_c1) && (minuto==m10_c1) && (segundo==s10_c1))  activar_regadera();
   if ((hora==h11_c1) && (minuto==m11_c1) && (segundo==s11_c1))  activar_regadera();
   if ((hora==h12_c1) && (minuto==m12_c1) && (segundo==s12_c1))  activar_regadera();
   if ((hora==h13_c1) && (minuto==m13_c1) && (segundo==s13_c1))  activar_regadera();
   if ((hora==h14_c1) && (minuto==m14_c1) && (segundo==s14_c1))  activar_regadera();
   if ((hora==h15_c1) && (minuto==m15_c1) && (segundo==s15_c1))  activar_regadera();
   if ((hora==h16_c1) && (minuto==m16_c1) && (segundo==s16_c1))  activar_regadera(); 
   if ((hora==h17_c1) && (minuto==m17_c1) && (segundo==s17_c1))  activar_regadera();
   if ((hora==h18_c1) && (minuto==m18_c1) && (segundo==s18_c1))  activar_regadera();
   if ((hora==h19_c1) && (minuto==m19_c1) && (segundo==s19_c1))  activar_regadera();
   if ((hora==h20_c1) && (minuto==m20_c1) && (segundo==s20_c1))  activar_regadera();
   if ((hora==h21_c1) && (minuto==m21_c1) && (segundo==s21_c1))  activar_regadera(); 
  }   
