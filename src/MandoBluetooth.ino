//Librerias
#include "BluetoothSerial.h"

//Variables

//Control
String Variable = "";
bool Estado_Led=false;
//Motores

//PINES (VERSIÓN 2025)
const byte MotorB[]={16,17};
const byte MotorA[]={18,19};

//Buzzer
const byte Buzzer=27;


//Creación del PWM para la ESP32
const uint16_t Frecuencia = 5000;
const byte Resolucion = 10;
const byte Canales[] ={0,1,2,3};

//Variables de Control de Velocidad
uint16_t velocidades[]={0,0};


//BLUETOOTH

String device_name = "SR_kit";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;



void setup() {

  //Inicialización de la Comunicación Serial
  Serial.begin(115200);
  
  //Bluetooth
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("El dispositivo de nombre \"%s\" inició.\nSe puede conectar con Bluetooth!\n", device_name.c_str());

  //Inicialización de los Pines para el Control de los Motores
  Inicialiar_Pines();

  //Creación del PWM
  CrearPWM();
  //Se envia una señal de HIGH al pin EEP del DRV8833 para salir del modo SLEEP
  pinMode(4, OUTPUT);
  digitalWrite(4, 1);
}

void loop() {
  if (SerialBT.available()) {
    //Obtención de la variable
    char receivedChar = (char)SerialBT.read();
    Variable = "";
    Variable += receivedChar;
    //Derecha
    if(Variable.equals("3")){

      //MotorA
      ledcWrite(Canales[0],0);
      ledcWrite(Canales[1],500);
      //MotorB
      ledcWrite(Canales[2],1000);
      ledcWrite(Canales[3],0);
      //Imprimir
      Serial.println("Derecha");
    }
    //Izquierda
    if(Variable == "4"){

      //MotorA
      ledcWrite(Canales[0],1000);
      ledcWrite(Canales[1],0);
      //MotorB
      ledcWrite(Canales[2],0);
      ledcWrite(Canales[3],500);
      //Imprimir
      Serial.println("Izquierda");
    }
    //Adelante
    if(Variable == "1"){

      //MotorA
      ledcWrite(Canales[0],1000);
      ledcWrite(Canales[1],0);
      //MotorB
      ledcWrite(Canales[2],1000);
      ledcWrite(Canales[3],0);
      //Imprimir
      Serial.println("Adelante");
    }
    //Atras
    if(Variable == "2"){

      //MotorA
      ledcWrite(Canales[0],0);
      ledcWrite(Canales[1],1000);
      //MotorB
      ledcWrite(Canales[2],0);
      ledcWrite(Canales[3],1000);
      //Imprimir
      Serial.println("Atras");
    }
    if(Variable == "5"){
      ledcWrite(Canales[0],0);
      ledcWrite(Canales[1],0);
      ledcWrite(Canales[2],0);
      ledcWrite(Canales[3],0);
      Serial.println("Stop");
    }
    if(Variable == "6"){
      digitalWrite(Buzzer, HIGH);
      delay(500);
      digitalWrite(Buzzer, LOW);
    }
  }
}

void Inicialiar_Pines(){
  pinMode(MotorA[0],OUTPUT);
  pinMode(MotorA[1],OUTPUT);
  pinMode(MotorB[0],OUTPUT);
  pinMode(MotorB[1],OUTPUT);
  pinMode(MotorB[1],OUTPUT);
  pinMode(Buzzer,OUTPUT);
}
void CrearPWM(){
  ledcSetup(Canales[0],Frecuencia,Resolucion); 
  ledcSetup(Canales[1],Frecuencia,Resolucion); 
  ledcSetup(Canales[2],Frecuencia,Resolucion); 
  ledcSetup(Canales[3],Frecuencia,Resolucion); 
  ledcAttachPin(MotorA[0],Canales[0]);
  ledcAttachPin(MotorA[1],Canales[1]);
  ledcAttachPin(MotorB[0],Canales[2]);
  ledcAttachPin(MotorB[1],Canales[3]);
}
