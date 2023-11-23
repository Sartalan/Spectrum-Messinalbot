# [Informe del Proyecto]


## > Messinalbot.

- Messinalbot fue un proyecto creado por el grupo ***Spectrum*** originalmente con la intención de ser simplemente un robot Futbolista, pero una vez terminado el proyecto y sus respectivos códigos para controlarlo, se decidió adaptar tanto su PCB como su diseño al de un robot Sumo; ambos cumpliendo las reestricciones reglamentarias de la LNR.

## > Funcionamiento

- Su circuito consiste fundamentalmente de los siguientes componentes:
  1. Un microcontrolador ESP32 en reemplazo del famoso Arduino que le permite compilar código del mismo IDE, y es más; poseer la posibilidad de crear proyectos WIFI y Bluetooth por sus respectivos módulos incorporados.
  2. Un circuito integrado DRV8833 como Puente H para así controlar su movimiento (a más información de su funcionamiento, consultar su datasheet)
  3. Dos sensores ultrasonido HC-SR04
  4. Dos sensores infrarrojo CNY70
  5. Dos pulsadores; uno para su encendido y el otro como entrada de datos de un pin GPIO para así implementarle cualquier lógica que se desee.

## ***Pinout del ESP32:***

*Datasheet:* https://docs.ai-thinker.com/_media/esp32/docs/nodemcu-32s_product_specification.pdf

## > Código:

- El robot contiene dos códigos preparados para su movimiento; uno utilizando una app que por vía de Bluetooth y utilizando librerias se encargará de recibir datos que posteriormente manejará dentro de un Switch Case que le terminaran por dar así la posibilidad de moverse, y el otro funcionará a partir de un servidor generado por el mismo ESP32 que alojará una web, y ésta web sería la que se encargaría de mandar los datos correspondientes al movimiento del robot a partir de un protocolo de comunicación llamado “WebSocket”. Estos mismos datos enviados serían accionados al presionar las teclas: “W”; ”A”; ”S”; ”D” y cambiarían el diseño de un control en pantalla para un mayor atractivo y entendimiento.

*A más información del código leer su archivo [README.md](http://README.md) correspondiente.*

## > Diseño 3D

- Su diseño esta adaptado a las medidas impuestas por la LNR para su participación en esta como Futbolista, siendo estas: 200x150mm.
  
  A su vez, el modelo está originalmente creado a medida para contener motorreductores amarillos Arduino y sus respectivas ruedas, y es justamente por ello, que nuestro repositorio de Github contiene 2 modelos; uno con los componentes extras agregados, para una mayor visualización, y otro sin ningún componente agregado, para una mayor accesibilidad en su edición.
  
  ### Links:
  
  - Diseño 3D de Messibot en TinkerCAD
    
    [3D design Robot_Cuarto | Tinkercad](https://www.tinkercad.com/things/4UyoocaAXjU-robotcuarto)

    ---
    
    Sí quiere echarle un vistazo a nuestro proyecto sin necesidad de descargarlo, siempre puede visitar nuestra web recopilatoria, la cual contiene un simple vistazo de lo explicado anteriormente:
+ Web: https://sartalan.github.io/Spectrum-Messinalbot.page/
