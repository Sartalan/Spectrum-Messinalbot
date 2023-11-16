
// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


// Replace with your network credentials
const char* ssid = "Polenta3000";
const char* password = "Tecnica5";

//Estudiantes
//educar_2018
int Numero;

#define STBY 5
#define Motor1a 17
#define Motor1b 16
#define Motor2a 18
#define Motor2b 19

char move = 'default';
int ledState = 0;
bool getA, getS, getD, getW = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">

<style>
        :root {
    --pads-color:#000000;
}

:root {
    --left-radius:1em 0 0 1em;
    --right-radius:0 1em 1em 0;
    --bottom-radius:0 0 1em 1em;
    --top-radius:1em 1em 0 0;
}
/*GRID POSITION*/
/*! ------------------------------------- */
.top {
    grid-column: 2;
    grid-row:1;
    border-radius: var(--top-radius);
}
.bottom {
    grid-column: 2;
    grid-row: 3;
    border-radius: var(--bottom-radius);
}
.right {
    grid-column: 3;
    grid-row: 2;
    border-radius: var(--right-radius);
}
.left {
    grid-column: 1;
    grid-row: 2;
    border-radius: var(--left-radius);
}

/*Styles Customization*/
/*! ------------------------------------- */

* {
    padding: 0;
    margin: 0;
    box-sizing: border-box;
}

body {
    background-color: #181717;
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
}

.controller-box {
    width: 20em;
    height: 20em;
    background-color:transparent;
    display: grid;
    position: relative;
    grid-template-columns: 1fr 1fr 1fr;
    grid-template-rows: 1fr 1fr 1fr;
}

/*! Center controller btn*/
/*! ------------- */
.center {
    background-color: var(--pads-color);
    grid-column: 2;
    grid-row: 2;
    display: flex;
    align-items: center;
    justify-content: center;
}

.center-icon {
    width: 3em;
    height: 3em;
}

/*!Buttons*/
/*! ------------- */

.controller-btn {
    background-color: var(--pads-color);
    display: flex;
    justify-content: center;
    align-items: center;
    cursor: pointer;
}

.controller-btn > .arrow-in {
    width: 6em;
    height: 6em;
    filter: invert(1);
}

/*? Button Functionality*/
/*! ------------------------------------- */


.controller-btn.active

 {
    background-color: #cecdc7;
}

.controller-btn.active .arrow {
  color: #000000;

}

.velocidadBtn {
            border-radius: 3em;
        }

        .btnThree {
            background-color: rgb(19, 225, 212);
                grid-column: 4;
                grid-row: 100%;
            }
        .btnTwo {
          background-color: rgb(19, 225, 212);
                grid-column: 3;
                grid-row: 100%;
            }
        .btnOne {
            background-color: rgb(19, 225, 212);
                grid-column: 2;
                grid-row: 100%;
            }

        .velocityNav {
            position: absolute;
            top: 10px;
            width: 100%;
            height: 3.5em;

            display: grid;
            grid-template-columns:10px 60px 60px 60px  75%;
            grid-template-rows: 100%;
            grid-gap: 1em;
        }

            .arrow {
              font-family: 'Fira Sans';

              user-select: none;
              color: white;
              font-size: 3.5em;
            }

            .CIRCULO {
              position: absolute;
              top: 0;
              left: 0;
              right: 0;
              bottom: 0;
              margin: auto;
              height: 21em;
              width: 21em;
              border-radius: 10em;
              box-shadow: -3px 6px #ffffff;
              z-index: -5;
              background-image: linear-gradient(top, #fcab00 0%, #ffda09 5%, #ffda09 9%, #ef9800 14%, #ef9800 20%, #fdee00 44%, #fdee00 67%, #ffb400 84%, #ffb400 100%);
background-image: -webkit-gradient(linear, left top, left bottom, color-stop(0, #fcab00), color-stop(0.045, #ffda09), color-stop(0.09, #ffda09), color-stop(0.145, #ef9800), color-stop(0.2, #ef9800), color-stop(0.435, #fdee00), color-stop(0.67, #fdee00), color-stop(0.835, #ffb400), color-stop(1, #ffb400));
background-image: -moz-linear-gradient(top, #fcab00 0%, #ffda09 5%, #ffda09 9%, #ef9800 14%, #ef9800 20%, #fdee00 44%, #fdee00 67%, #ffb400 84%, #ffb400 100%);
background-image: -o-linear-gradient(top, #fcab00 0%, #ffda09 5%, #ffda09 9%, #ef9800 14%, #ef9800 20%, #fdee00 44%, #fdee00 67%, #ffb400 84%, #ffb400 100%);
background-image: -ms-linear-gradient(top, #fcab00 0%, #ffda09 5%, #ffda09 9%, #ef9800 14%, #ef9800 20%, #fdee00 44%, #fdee00 67%, #ffb400 84%, #ffb400 100%);
            }
</style>


<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>

  <div class="CIRCULO"></div>
  <div class="controller-box">

        <div class="center"></div>

       <div class="left controller-btn">
            <div class="arrow arrow-left">A</div>
        </div>

        <div class="right controller-btn">
          <div class="arrow arrow-right">D</div>

        </div>

        <div class="bottom controller-btn">
          <div class="arrow arrow-bottom">S</div>
          
        </div>

        <div class="top controller-btn">
          <div class="arrow arrow-top">W</div>
        </div>

    </div>
  
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
   
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }

  function onMessage(event) {
    var state;
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }
    document.getElementById('state').innerHTML = state;
  }

  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  
  //Controller Functionality Start
// ------------------------------------- 

  function initButton() {

  let izquierda = document.querySelector('.left')
  let derecha = document.querySelector('.right')
  let abajo = document.querySelector('.bottom')
  let arriba = document.querySelector('.top')

  let izquierdaFlecha = document.querySelector('.arrow-left')
  let derechaFlecha = document.querySelector('.arrow-right')
  let abajoFlecha = document.querySelector('.arrow-bottom')
  let arribaFlecha = document.querySelector('.arrow-top')

  let Estado = 0
  let senalEnviada = 0 
      window.addEventListener("keydown", function (event) {
            
            let letra = (event.code)
  
      switch (letra) {
        default:

          izquierda.classList.remove('active')
          derecha.classList.remove('active')
          abajo.classList.remove('active')
          arriba.classList.remove('active')

          izquierdaFlecha.classList.remove('active')
          derechaFlecha.classList.remove('active')
          abajoFlecha.classList.remove('active')
          arribaFlecha.classList.remove('active')

        break;
                
            //!--------------IZQUIERDA---------------

          case 'KeyA':
          Estado=1;
          
          if(Estado && !senalEnviada){
          console.log('Presionaste A y soy el boton de la izquierda =D')
          izquierdaFlecha.classList.add('active')
          izquierda.classList.add('active')
          websocket.send('IZQUIERDA');
          senalEnviada=1;
          }

        break;

            //!--------------DERECHA---------------

          case 'KeyD':
          Estado=1;
          if(Estado && !senalEnviada){
          console.log('Presionaste D y soy el boton de la derecha =D')     
          derechaFlecha.classList.add('active')
          derecha.classList.add('active')    
          websocket.send('DERECHA');
          senalEnviada=1;
          }

        break;

            //!--------------ABAJO---------------
           
          case 'KeyS':
          Estado=1;
          if(Estado && !senalEnviada){
          console.log('Presionaste S y soy el boton de abajo =D') 
          websocket.send('ABAJO');         
          abajoFlecha.classList.add('active')
          abajo.classList.add('active')
          senalEnviada=1;
          }

        break;           

            //!--------------ARRIBA---------------

          case 'KeyW':
          Estado=1;
          if(Estado && !senalEnviada){
          console.log('Presionaste W y soy el boton de arriba =D')    
          arribaFlecha.classList.add('active')
          arriba.classList.add('active')
          websocket.send('ARRIBA');
          senalEnviada=1;
          }
        break;    
}})

//SÍ TOCA LA TECLA        ↑ <=
  //-------------------------------
//SÍ SUELTA LA TECLA      => ↓


      window.addEventListener("keyup", function (event) {

          let letra = (event.code)

      switch (letra) {


            //!--------------MENOS_IZQUIERDA---------------

          case 'KeyA':

            console.log('Dejó de presionarse A y soy el boton de la izquierda =D')
            izquierda.classList.remove('active')
            izquierdaFlecha.classList.remove('active')
            websocket.send('MENOSIZQUIERDA');
            Estado=0
            senalEnviada=0

        break;
                
            //!--------------MENOSDERECHA---------------

          case 'KeyD':

            console.log('Dejo de presionarse D y soy el boton de la derecha =D')
            derechaFlecha.classList.remove('active')
            derecha.classList.remove('active')
            websocket.send('MENOSDERECHA');
            Estado=0
            senalEnviada=0

        break;
                
            //!--------------MENOSABAJO---------------
        
            case 'KeyS':

              console.log('Dejo de presionarse S y soy el boton de abajo =D')
              abajoFlecha.classList.remove('active')
              abajo.classList.remove('active')
              websocket.send('MENOSABAJO');
              Estado=0
              senalEnviada=0

          break;
                
            //!--------------MENOSARRIBA---------------

            case 'KeyW':

              console.log('Dejo de presionarse W y soy el boton de arriba =D')
              arribaFlecha.classList.remove('active')
              arriba.classList.remove('active')
              websocket.send('MENOSARRIBA');
              Estado=0
              senalEnviada=0

          break;               
            }

        })

  }

  function toggle(){


    websocket.send('alan');

  }
</script>
</body>
</html>
)rawliteral";

void notifyClients() {
  ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;

//----------------

    if (strcmp((char*)data, "IZQUIERDA") == 0) {

      Serial.println("Voy hacia la izquierda");
      move = 'A';
      getA = 0;
      
    } if (strcmp((char*)data, "DERECHA") == 0) {

       Serial.println("Voy hacia la derecha");
      move = 'D';
      getD = 0;

    }
    if (strcmp((char*)data, "ABAJO") == 0) {

      Serial.println("Voy hacia abajo");
      move = 'S';
      getS = 0;
       
    }

    if (strcmp((char*)data, "ARRIBA") == 0) {
      
      Serial.println("Voy hacia adelante");
      move = 'W';
      getA = 0;
    }

    //-------------- MENOS

    if (strcmp((char*)data, "MENOSARRIBA") == 0) {
        move = 'default';
    }
     if (strcmp((char*)data, "MENOSDERECHA") == 0) {
        move = 'default'; 
    }
     if (strcmp((char*)data, "MENOSIZQUIERDA") == 0) {
        move = 'default';
    }
     if (strcmp((char*)data, "MENOSABAJO") == 0) {
        move = 'default';
    }

    

  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(Motor1a, OUTPUT);
  pinMode(Motor1b, OUTPUT);
  pinMode(Motor2a, OUTPUT);
  pinMode(Motor2b, OUTPUT);

  digitalWrite(Motor1a, LOW);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, LOW);
  digitalWrite(Motor2b, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();

 switch (move)
{


  case 'A':
        
          Serial.println("A");
          digitalWrite(Motor1a, HIGH);
          digitalWrite(Motor1b, LOW);
          digitalWrite(Motor2a, LOW);
          digitalWrite(Motor2b, HIGH);
          digitalWrite(STBY, HIGH);
          
        
        break;

  case 'D':
          
          Serial.println("D");
          digitalWrite(Motor1a, LOW);
          digitalWrite(Motor1b, HIGH);
          digitalWrite(Motor2a, HIGH);
          digitalWrite(Motor2b, LOW);
          digitalWrite(STBY, HIGH);

        break;
  case 'W':

        
          Serial.println("W");
          digitalWrite(Motor1a, HIGH);
          digitalWrite(Motor1b, LOW);
          digitalWrite(Motor2a, HIGH);
          digitalWrite(Motor2b, LOW);
          digitalWrite(STBY, HIGH);
          

        break;

  case 'S':

        
          Serial.println("S");
          digitalWrite(Motor1a, LOW);
          digitalWrite(Motor1b, HIGH);
          digitalWrite(Motor2a, LOW);
          digitalWrite(Motor2b, HIGH);
          digitalWrite(STBY, HIGH);
          
        
        break;

    default:

        
        digitalWrite(Motor1a, LOW);
        digitalWrite(Motor1b, LOW);
        digitalWrite(Motor2a, LOW);
        digitalWrite(Motor2b, LOW);
        digitalWrite(STBY, LOW);
        break;
}
}