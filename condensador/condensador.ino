/*  Calculador de capacidad de condensador y tiempo para carga
 *   2020 Esti Zubimendi Solaguren
 *   código obtenido de: https://www.arduino.cc/en/Tutorial/CapacitanceMeter
 *  Se utiliza la fórmula TC = R * C para calcular el valor del condensador
 *
 * Teoría:   Un condensador es un objeto con la capacidad de acumular carga eléctrica
 *          Al producto RC se le llama constante de tiempo del circuito t  y equivale al tiempo que el condensador tardaría en cargarse.
 *          También equivale al tiempo necesario para que el condensador se cargue con una carga equivalente al 63,2%.
 *    TC = R * C
 *
 *    TC = constante de tiempo en segundos
 *    R = resistencia en ohms
 *    C = capacidad en faradios ( 1 microfaradio = 0,0000001 faradios = 10^-6 faradios )
 *
 *    El voltaje del capacitador en un constante de tiempo (one time constant) se define como el 63,2% del voltaje de la corriente.
 *
 *  Configuración de Hardware:
 *  Conectar el condensador que se quiera probar a un punto común y a la toma de tierra.
 *  Una de las resistencias, de 10K ohms (resistencia de carga), al puerto digital 13 y al punto común.
 *  La otra resistencia, de 220 ohms(resistecia de descarga), conectada al puerto ~11 y al punto común.
 *  Conectar el puerto común con el puerto A0.
 */

#define analogPin      0          // pin analógico para calcular el voltaje del condensador
#define chargePin      13         // pin para cargar el condensador - conectado a uno de los extremos de la resistencia de carga
#define dischargePin   11         // pin para descargar el condensador
#define resistorValue  10000.0F   // valor de la resistencia que se está utilizando en este caso 10K ohms
                                  // la F le dice al programa que el número es un float

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                // variables de tipo float para preservar la precisión
float nanoFarads;

void setup(){
  pinMode(chargePin, OUTPUT);     // ponemos chargePin a OUTPUT
  digitalWrite(chargePin, LOW);  

  Serial.begin(9600);             // conexión entre la placa y el ordenador, a velocidad 9600 bits/segundo
}

void loop(){
  digitalWrite(chargePin, HIGH);  // ponemos chargePin a HIGH para que cargue el condensador
  startTime = millis();

  while(analogRead(analogPin) < 648){       // 647 es el 63.2% de 1023, que corresponde al máximo voltaje posible
  }

  elapsedTime= millis() - startTime;
 // convertir milisegundos a segundos ( 10^-3 ) y Faradios a microFaradios ( 10^6 ),  net 10^3 (1000)  
  microFarads = ((float)elapsedTime / resistorValue) * 1000;  
  Serial.print(elapsedTime);       // imprimimos el valor en la consola
  Serial.print(" mS    ");         // imprimimos la magnitud


  if (microFarads > 1){
    Serial.print((long)microFarads);       // volvemos a imprimir el valor en la consola y su magnitud
    Serial.println(" microFarads");        
  }
  else
  {
    // si el valor es menor que un microFaradio, convertir a nanoFaradios (10^-9 faradios)

    nanoFarads = microFarads * 1000.0;      // multiplicar por 1000 para convertir a nanoFaradios (10^-9)
    Serial.print((long)nanoFarads);         // volvemos a imprimir el valor en la consola y su magnitud
    Serial.println(" nanoFarads");      
  }

  /* descargar el condensador  */
  digitalWrite(chargePin, LOW);             // ponemos chargePin a LOW
  pinMode(dischargePin, OUTPUT);            // ponemos dischargePin a OUTPUT
  digitalWrite(dischargePin, LOW);          // ponemos dischargePin a LOW
  while(analogRead(analogPin) > 0){         // esperar a que el condensador esté completamente descargado
  }

  pinMode(dischargePin, INPUT);            // volvemos a poner el dischargePin a INPUT de nuevo
}
