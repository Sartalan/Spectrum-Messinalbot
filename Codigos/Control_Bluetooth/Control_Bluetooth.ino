#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define Motor1a 16
#define Motor1b 17
#define Motor2a 18
#define Motor2b 19
int veloc;
BluetoothSerial BT; // Objeto Bluetooth

void callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_START_EVT) {
    Serial.println("Inicializado SPP");
  }
  else if (event == ESP_SPP_SRV_OPEN_EVT ) {
    Serial.println("Cliente conectado");
  }
  else if (event == ESP_SPP_CLOSE_EVT  ) {
    Serial.println("Cliente desconectado");
  }
  else if (event == ESP_SPP_DATA_IND_EVT ) {
    Serial.println("Datos recibidos");
    while (BT.available()) { // Mientras haya datos por recibir
      int incoming = BT.read(); // Lee un byte de los datos recibidos
    }
  }
}
void setup() {
    Serial.begin(115200); // Inicializando la conexión serial para debug
  BT.begin("ESP32_Fulbo"); // Nombre de tu Dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejar");
  BT.register_callback(callback_function); // Registramos la función "callback_function" como función callback.

  pinMode(Motor1a, OUTPUT);
  pinMode(Motor1b, OUTPUT);
  pinMode(Motor2a, OUTPUT);
  pinMode(Motor2b, OUTPUT);
}
void loop() {
  if (BT.available()) // Compruebe si recibimos algo de Bluetooth
  {
    int incoming = BT.read(); // Lee lo que recibimos
    Serial.print("Recibido: ");
    Serial.println(incoming);
    
    switch(incoming){
      
      case 70: // F en ASCII
       Adelante() ; 
        Serial.print("Adelante");
      break;

      case 66: // B en ASCII
       Retroceder();
       Serial.print("Retroceder");
      break;

      case 76: // L en ASCII
       Izquierda();
       Serial.print("Izquierda"); 
      break;
    
      case 82: // R en ASCII
       Derecha();
       Serial.print("Derecha");
      break;





      case 0: // 0 en ASCII
      veloc = 0;
      break;
      case 1: // 1 en ASCII
      veloc = 25; 
      break;
      case 2: // 2 en ASCII
      veloc = 51;
      break;
      case 3: // 3 en ASCII
      veloc = 76;
      break;
      case 4: // 4 en ASCII
      veloc = 102;
      break;
      case 5: // 5 en ASCII
      veloc = 127;
      break;
      case 6: // 6 en ASCII
      veloc = 153;
      break;
      case 7: // 7 en ASCII
      veloc = 179;
      break;
      case 8: // 8 en ASCII
      veloc = 200;
      break;
      case 9: // 9 en ASCII
      veloc = 225;
      break;
      case 113: // q en ASCII
      veloc = 255;
      break;
      default:
        Parar(); 
        Serial.print("Parado");
      break;
    }
  }
}
void Adelante() {

  digitalWrite(Motor1a, veloc);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, veloc);
  digitalWrite(Motor2b, LOW);


}
void Retroceder() {

  digitalWrite(Motor1a, LOW);
  digitalWrite(Motor1b, HIGH);
  digitalWrite(Motor2a, LOW);
  digitalWrite(Motor2b, HIGH);

}
void Izquierda() {

  digitalWrite(Motor1a, LOW);
  digitalWrite(Motor1b, HIGH);
  digitalWrite(Motor2a, HIGH);
  digitalWrite(Motor2b, LOW);

}
void Derecha() {

  digitalWrite(Motor1a, HIGH);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, LOW);
  digitalWrite(Motor2b, HIGH);

}
void Parar() {
  digitalWrite(Motor1a, LOW);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, LOW);
  digitalWrite(Motor2b, LOW);
}
