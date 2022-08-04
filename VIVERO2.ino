/////////////////////////////////////////////CONFIGURACION DEL LCD KEYPAD SHIELD////////////////////////////////////////////
String Opciones[] = {"Grupo Gloster", "Fecha y Hora", "Temp. y Hum.", "Hum. del Suelo", "Nivel Luz (LDR)", "Nivel Luz (BH), UltraSonico"};


int readKey;

// Control del Menu
int PaginasMenu = 0;
int maxPaginasMenus = round(((sizeof(Opciones) / sizeof(String)) / 2) + .5);
int PosicionCursor = 0;

// Crea los dibujos de las Flechas y el Puntero.
byte FlechasAbajo[8] = {
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};

byte FlechasArriba[8] = {
  0b00100, //   *
  0b01110, //  ***
  0b10101, // * * *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100  //   *
};

byte Puntero[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

#include <Wire.h>
#include <LiquidCrystal.h>

// Setting the LCD shields pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//////////////////////////////////////////////FIN DE LA CONFIGURACION DEL LCD KEYPAD SHIELD////////////////////////////////////////////
//////////////////////////////////////////SENSOR PIR//////////////////////////
const int AlarmaPIR = 13;        // pin para el LED
const int PIRPin = 12;         // pin de entrada (for PIR sensor)
 
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin
/////////////////////////////////////////////////////////////DTH11////////////////////////////////////////////////////////
#include "DHT.h"
#define DHTPIN 12 //Conectamos el Sensor al pin digital 9
#define DHTTYPE DHT22 //Nombramos el Tipo de Sensor
DHT dht(DHTPIN, DHTTYPE);
//////////////////////////////////////////////FIN DE LA CONFIGURACION DHT11////////////////////////////////////////////////

////////////////////////////////////////////////SENSOR DE HUMEDAD DE SUELO/////////////////////////////////////////////////////////
int Humedad = 0; //Variable utilizada para calcular la humedad
int Lectura_Analogica = 1; //variable para leer el valor del pin analogico

//////////////////////////////////////////////////////////////BH1750///////////////////////////////////////////////////
#include <Wire.h>
#include <BH1750.h>

BH1750 Luxometro;

uint16_t Lux_noche=20;
uint16_t Lux_dia=30;
int pinLEDS=13;

//////////////////////////////////////////////////////////////////RTC////////////////////////////////////////////////////////////////////
#include "RTClib.h"
RTC_DS1307 RTC;                  // inicializa el modulo RTC
int r_diaSemana;                  // almacena el resultado del dia de la semana calculado
const int regadera = 11;             // Pin 11 encargado de activar La mangera, se conecta al Rele
const int motor = 12;             // Pin 11 encargado de activar el motor, se conecta al Rele
int segundo;
int minuto;
int hora;
int tiempo_regadera = 5000; // Tiempo continuo que dura el timbre sonando, en milisegundos 5000 = 5 segundos
int tiempo_motor = 5000;
/////////////////////////////////////////////HORARIOS RTC//////////////////////////////////////////////////////////////
////////////////////////PD: SE REUTILIZO LA PROGRAMACION HECHA PARA EL TIMBRE AUTOMATIZADO DE LA ESCUELA DE EDUCACION TECNICA AERONAUTICA N°32 ///////////////////
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

String bienvenida = "¡Bienvenidos! Grupo Gloster - Vivero Automatizado.";
String nombres = "Miembros del Grupo: Baez Kevin, Sosa Alexander y Soto Lucas.";
void setup() {

  // Inicializa la comunicacion
  Serial.begin(9600);

  // Inicializa el LCD y lo limpia.
  lcd.begin(16, 2);
  lcd.clear();

  // Crea los tres tipos de Caracteres en el LCD.
  lcd.createChar(0, Puntero);
  lcd.createChar(1, FlechasArriba);
  lcd.createChar(2, FlechasAbajo);
}

void loop() {
  DibujadodelMenu();
  DibujodelCursor();
  OperaciondelMenu();
  
    
}

//Esta función generará los 2 elementos del menú que pueden caber en la pantalla. Cambiarán a medida que se desplaza por su menú. Las flechas hacia arriba y hacia abajo indicarán la posición actual del menú.
void DibujadodelMenu() {
  Serial.print(PaginasMenu);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(Opciones[PaginasMenu]);
  lcd.setCursor(1, 1);
  lcd.print(Opciones[PaginasMenu + 1]);
  if (PaginasMenu == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (PaginasMenu > 0 and PaginasMenu < maxPaginasMenus) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (PaginasMenu == maxPaginasMenus) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}

// Cuando se llama, esta funcion borrará el cursor actual y lo volvera a dibujar basandose en las Variables PosicionCursor y PaginasMenu.
void DibujodelCursor() {
  for (int x = 0; x < 2; x++) {     // Borrar el Cursor Actual
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  // El menú está configurado para ser progresivo (PaginasMenu 0 = Elemento 1 y Elemento 2, PaginasMenu 1 = Elemento 2 y Elemento 3, PaginasMenu 2 = Elemento 3 y Elemento 4), entonces
  // para determinar dónde debe estar el cursor, debe ver si se encuentra en una página de menú impar o par y en una posición de cursor impar o par.
  if (PaginasMenu % 2 == 0) {
    if (PosicionCursor % 2 == 0) {  // Si la página del menú es par y la posición del cursor es par, eso significa que el cursor debe estar en la línea 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (PosicionCursor % 2 != 0) {  // i la página del menú es par y la posición del cursor es impar, significa que el cursor debe estar en la línea 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (PaginasMenu % 2 != 0) {
    if (PosicionCursor % 2 == 0) {  //Si la página del menú es impar y la posición del cursor es par, eso significa que el cursor debe estar en la línea 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (PosicionCursor % 2 != 0) {  // Si la página del menú es impar y la posición del cursor es impar, eso significa que el cursor debe estar en la línea 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}


void OperaciondelMenu() {
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 0: // Cuando el botón vuelve a 0, no se toman medidas
        break;
      case 1:  // Este caso se ejecutará si se presiona el botón "adelante"
        button = 0;
        switch (PosicionCursor) { // El caso que se selecciona aquí depende de la página de menú en la que se encuentre y de dónde esté el cursor.
          case 0:
            menuElemento1();
            break;
          case 1:
            menuElemento2();
            break;
          case 2:
            menuElemento3();
            break;
          case 3:
            menuElemento4();
            break;
          case 4:
            menuElemento5();
            break;
          case 5:
            menuElemento6();
            break;
          case 6:
            menuElemento7();
            break;
          case 7:
            menuElemento8();
            break;
          case 8:
            menuElemento9();
            break;
          case 9:
            menuElemento10();
            break;
        }
        activeButton = 1;
        DibujadodelMenu();
        DibujodelCursor();
        break;
      case 2:
        button = 0;
        if (PaginasMenu == 0) {
          PosicionCursor = PosicionCursor - 1;
          PosicionCursor = constrain(PosicionCursor, 0, ((sizeof(Opciones) / sizeof(String)) - 1));
        }
        if (PaginasMenu % 2 == 0 and PosicionCursor % 2 == 0) {
          PaginasMenu = PaginasMenu - 1;
          PaginasMenu = constrain(PaginasMenu, 0, maxPaginasMenus);
        }

        if (PaginasMenu % 2 != 0 and PosicionCursor % 2 != 0) {
          PaginasMenu = PaginasMenu - 1;
          PaginasMenu = constrain(PaginasMenu, 0, maxPaginasMenus);
        }

        PosicionCursor = PosicionCursor - 1;
        PosicionCursor = constrain(PosicionCursor, 0, ((sizeof(Opciones) / sizeof(String)) - 1));

        DibujadodelMenu();
        DibujodelCursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (PaginasMenu % 2 == 0 and PosicionCursor % 2 != 0) {
          PaginasMenu = PaginasMenu + 1;
          PaginasMenu = constrain(PaginasMenu, 0, maxPaginasMenus);
        }

        if (PaginasMenu % 2 != 0 and PosicionCursor % 2 == 0) {
          PaginasMenu = PaginasMenu + 1;
          PaginasMenu = constrain(PaginasMenu, 0, maxPaginasMenus);
        }

        PosicionCursor = PosicionCursor + 1;
        PosicionCursor = constrain(PosicionCursor, 0, ((sizeof(Opciones) / sizeof(String)) - 1));
        DibujadodelMenu();
        DibujodelCursor();
        activeButton = 1;
        break;
    }
  }
}

// Se llama a esta función cada vez que se evalúa presionar un botón. La pantalla LCD funciona al observar una caída de voltaje en los botones, todos conectados a A0.
int EvaluarBoton(int x) {
  int result = 0;
  if (x < 50) {
    result = 1; // right
  } else if (x < 195) {
    result = 2; // up
  } else if (x < 380) {
    result = 3; // down
  } else if (x < 790) {
    result = 4; // left
  }
  return result;
}


// Si hay instrucciones de uso comunes en más de 1 de sus elementos de menú, puede llamar a esta función desde el sub
// menús para simplificar un poco las cosas. Si no tiene instrucciones comunes o verbage en varios menús
// Simplemente eliminaría este vacío. También debe eliminar las llamadas a la función drawInstructions () de las funciones de su submenú.
void drawInstructions() {
  lcd.setCursor(0, 1); // Set cursor to the bottom line
  lcd.print("Use ");
  lcd.print(byte(1)); // Up arrow
  lcd.print("/");
  lcd.print(byte(2)); // Down arrow
  lcd.print(" buttons");
}

void menuElemento1() { // Creditos
  int activeButton = 0;
      pinMode(AlarmaPIR, OUTPUT); 
   pinMode(PIRPin, INPUT);
   
 while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Vivero Automa.");
  lcd.setCursor(1, 1);
  lcd.print("Grupo Gloster");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Grupo Gloster:");
  lcd.setCursor(3, 1);
  lcd.print("Baez Kevin");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Grupo Gloster:");
  lcd.setCursor(1, 1);
  lcd.print("Sosa Alexander");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Grupo Gloster:");
  lcd.setCursor(3, 1);
  lcd.print("Soto Lucas");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Vivero Automa.");
  lcd.setCursor(2, 1);
  lcd.print("E.E.T.A N.32");
  delay(3000); 
  }
}

void menuElemento2() { // FECHA Y HORA
  int activeButton = 0;

 pinMode(regadera, OUTPUT);                    // Configura como salida el pin 7
 Wire.begin();                               
 RTC.begin();                                // Inicia la comunicaci¢n con el RTC
 
 //if (RTC.lostPower()) { //En caso de que el programa se apague o haya corte de luz esto volvera a colocarse en su horario correspondiente.
   // Serial.println("EL RTC perdió potencia, vamos a configurar el tiempo!");
    // following line sets the RTC to the date & time this sketch was compile
 RTC.adjust(DateTime(__DATE__, __TIME__)); // Lee la fecha y hora del PC (Solo en la primera carga)
                                             // el anterior se usa solo en la configuracion inicial luego se pone como comentario
                                             // y se vuelve a cargar el programa sin esa linea.   

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
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
 lcd.print(now.day(), DEC);
 lcd.print("/");
 lcd.print(now.month(), DEC);
 lcd.print("/");
 lcd.print(now.year(), DEC);
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
 
  digitalWrite(motor, HIGH);     // apaga el timbre
 delay(500);                    // La informaci¢n se actualiza cada 1/2 seg.
 lcd.setCursor(9,0);            // Borra parte de la pantalla del LCD
 lcd.print("                ");
 lcd.setCursor(8,1);
 lcd.print("                ");
  }
  }
//////////////////////////////// Fin del void ITEM1, inician las Funciones de la regadera automatica/////////////////////////

//////////////////////////////////////COMIENZA LOS VOID MENU//////////////////////////
void menuElemento3() { // Inicia la Funcion del Sensor DHT22 de Temperatura y Humedad. 
  int activeButton = 0;
  //Inicializa el DHT11
   dht.begin();
   
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
    int h = dht.readHumidity();    // Lee la humedad
   int t= dht.readTemperature();
   
   lcd.clear();//Elimina todos los simbolos del LCD
   lcd.setCursor(0,0);//Posiciona la primera letra despues del segmento 5 en linea 1              
   lcd.print("Humedad Relativa ");
   lcd.setCursor(6,1);
   lcd.print(h);//Escribe la humedad
   lcd.print(" %");                     
   delay (2500);
   lcd.clear();
   lcd.setCursor(3,0);
   lcd.print("Temperatura "); 
   lcd.setCursor(6,1);
   lcd.print(t);//Escribe la temperatura
   lcd.print(" C'");                   
   delay (2500);
  }
}

void menuElemento4() { // Inicia la Funcion de la Humedad en Suelo.
  int activeButton = 0;
 
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
   char buffer[10];//Variable para crear una cadena
  Lectura_Analogica = analogRead(A1);//Leer el valor del potenciometro 
  Humedad = map(Lectura_Analogica, 0, 1023, 100, 0);//Escala para utilizarlo con el servo 
  //Mostrar mensajes en la LCD
  lcd.setCursor(0,0); //posicionar el cursor fila 1 columna 1
  lcd.print("  Humedad Suelo");
  lcd.setCursor(0,1); //posicionar el cursor fila 2 columna 3
  lcd.print("   HS = ");
  sprintf(buffer,"%03d",Humedad);//crear una cadena para mostrar siempre 3 digitos
  lcd.print(buffer);//Mostrar el % de humedad
  lcd.print("%                ");
  delay(250);//Esperar 250 ms 
  }
}

void menuElemento5() { // Inicia la Funcion del LDR para Mostrar el Nivel de Luz
  int activeButton = 0;
    
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
 int sensorValue = analogRead(A2);
 double dV = sensorValue;
 double le = (dV/1023)*100;
 int level = le;
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Nivel de Luz:");
 lcd.print(level);
 lcd.print("%");
 lcd.setCursor(0, 1);
  
 if ((level >= 0) && (level <= 5))
 {
  lcd.print("Muy Oscuro"); 
 }
 else if ((level > 5) && (level <= 10))
 {
  lcd.print("Oscuro"); 
 }
 else if ((level > 10) && (level <= 50))
 {
  lcd.print("Claro"); 
 }
 else
 {
  lcd.print("Muy Claro"); 
 }
  
 delay(500); 
  }
}

void menuElemento6() { // Function executes when you select the 6th item from main menu
  int activeButton = 0;
  
  Serial.println("Inicializando sensor...");
  Luxometro.begin(BH1750_CONTINUOUS_HIGH_RES_MODE); //inicializamos el sensor
  pinMode(pinLEDS, OUTPUT);
  digitalWrite(pinLEDS, LOW);

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
     uint16_t lux = Luxometro.readLightLevel();//Realizamos una lectura del sensor
  Serial.print("Luz(iluminancia): ");
  Serial.print(lux);
  Serial.println(" lx");
  if(lux<Lux_noche) 
  {
      digitalWrite(pinLEDS, HIGH);
      lcd.setCursor(0,0); //Empezamos con el primer 
      lcd.println("Noche               ");
      lcd.setCursor(0,1); //Empezamos con el primer 
      lcd.println("Foco Encendido             ");
  }
  else if(lux>Lux_dia)
  {
      digitalWrite(pinLEDS, LOW);
      lcd.setCursor(0,0); //Empezamos con el primer 
      lcd.println("Dia                      ");
      lcd.setCursor(0,1); //Empezamos con el primer 
      lcd.println("Foco Apagado               ");
  }
  }
  }
/////////////////////////////APARTIR DE ACÁ YA NO SE UTILIZA ESTOS VOID MENUELEMENTO7, SE PUEDEN AGREGAR MAS OPCIONES////////////
void menuElemento7() { // La función se ejecuta cuando selecciona el séptimo elemento del menú principal
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 7");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuElemento8() { // La función se ejecuta cuando selecciona el octavo elemento del menú principal
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 8");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuElemento9() { // La función se ejecuta cuando selecciona el noveno elemento del menú principal
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 9");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuElemento10() { // La función se ejecuta cuando selecciona el decimo elemento del menú principal
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 10");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = EvaluarBoton(readKey);
    switch (button) {
      case 4:  // Este caso se ejecutará si se presiona el botón "Atrás"
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
/////////////////////////////// Funcion que activa el Timbre //////////////////////////////////
void activar_regaderaauto(){ 
    digitalWrite(regadera, LOW); 
    lcd.setCursor(0,0);
    lcd.print("Regadera ON ");
    Serial.println("Regadera Activada");
    delay(tiempo_regadera);
}    
void activar_motoraauto(){
    digitalWrite(motor, LOW); 
    lcd.setCursor(0,0);
    lcd.print("Motor ON ");
    Serial.println("Regadera Activada");
    delay(tiempo_motor);
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
   if ((hora==h1_c1) && (minuto==m1_c1) && (segundo==s1_c1))  activar_regaderaauto();
   if ((hora==h2_c1) && (minuto==m2_c1) && (segundo==s2_c1))  activar_regaderaauto(); 
   if ((hora==h3_c1) && (minuto==m3_c1) && (segundo==s3_c1))  activar_regaderaauto();
   if ((hora==h4_c1) && (minuto==m4_c1) && (segundo==s4_c1))  activar_regaderaauto();
   if ((hora==h5_c1) && (minuto==m5_c1) && (segundo==s5_c1))  activar_regaderaauto();
   if ((hora==h6_c1) && (minuto==m6_c1) && (segundo==s6_c1))  activar_regaderaauto();
   if ((hora==h7_c1) && (minuto==m7_c1) && (segundo==s7_c1))  activar_regaderaauto();
   if ((hora==h8_c1) && (minuto==m8_c1) && (segundo==s8_c1))  activar_regaderaauto();
   if ((hora==h9_c1) && (minuto==m9_c1) && (segundo==s9_c1))  activar_regaderaauto();
   if ((hora==h10_c1) && (minuto==m10_c1) && (segundo==s10_c1))  activar_regaderaauto();
   if ((hora==h11_c1) && (minuto==m11_c1) && (segundo==s11_c1))  activar_regaderaauto();
   if ((hora==h12_c1) && (minuto==m12_c1) && (segundo==s12_c1))  activar_regaderaauto();
   if ((hora==h13_c1) && (minuto==m13_c1) && (segundo==s13_c1))  activar_regaderaauto();
   if ((hora==h14_c1) && (minuto==m14_c1) && (segundo==s14_c1))  activar_regaderaauto();
   if ((hora==h15_c1) && (minuto==m15_c1) && (segundo==s15_c1))  activar_regaderaauto();
   if ((hora==h16_c1) && (minuto==m16_c1) && (segundo==s16_c1))  activar_regaderaauto(); 
   if ((hora==h17_c1) && (minuto==m17_c1) && (segundo==s17_c1))  activar_regaderaauto();
   if ((hora==h18_c1) && (minuto==m18_c1) && (segundo==s18_c1))  activar_regaderaauto();
   if ((hora==h19_c1) && (minuto==m19_c1) && (segundo==s19_c1))  activar_regaderaauto();
   if ((hora==h20_c1) && (minuto==m20_c1) && (segundo==s20_c1))  activar_regaderaauto();
   if ((hora==h21_c1) && (minuto==m21_c1) && (segundo==s21_c1))  activar_regaderaauto();   
      
}

 
 
