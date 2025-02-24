//Así quedó para la última competición de GDL del 20/02/2025
#include <NewPing.h>

#define GO 13
#define RDY 14

#define SENSOR_LEFT A3
#define SENSOR_CENTER A2
#define SENSOR_RIGHT A1
bool rutine=true;
int PWM_A = 3;
int AIN2 = 4;
int AIN1 = 5;
int STBY = 6;
int BIN1 = 7;
int BIN2 = 8;
int PWM_B = 9;

int Trigger = 10;
int Echo = 11;

int distance;
int us;



NewPing sonar (9,8,200);//(Pintrig,pinecho, dist.máx)

void setup() {
  INIT_pines();
    digitalWrite(STBY, HIGH);        //Arreglo sónico
    Serial.begin(9600);
}


void medir() {
    long duration;
    float distance;

    // Enviar pulso ultrasónico
    digitalWrite(Trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger, LOW);

    // Medir el tiempo de respuesta del eco
    duration = pulseIn(Echo, HIGH);
    distance = (duration * 0.0343) / 2;      //2 debido a la ida y vuelta, el decimal por la temperatura

    /*   us = sonar.ping_median(10);
       distance = us/US_ROUNDTRIP_CM;
       Serial.println(distance);*/
    Serial.print("Distancia: ");
    Serial.print(distance);
    //Serial.println(" cm");

    if (distance <=30) {
    // Si la distancia es menor o igual a 49, el oponente está cerca y debe atacar
    Serial.println("/ Attack mode");
    motores(250, LOW, 250, HIGH);
} else if (distance > 31) {
    // Si la distancia es mayor a 50, el robot debe girar sobre su eje
    Serial.println("/ Searching");
    motores(220, LOW, 220, LOW); // Gira sobre su eje
delay(200);
}    
}

void loop() {
 if(digitalRead(RDY)==HIGH && digitalRead(GO)==LOW ){

    digitalWrite(PWM_A,0);
    digitalWrite(PWM_B,0);
if(digitalRead(GO)==HIGH){
 if(rutine){
  rutine = false;                                       //           }
      motores(250, LOW, 250, HIGH);                       //          }
       delay(500);                                          //         }
        motores(220, LOW, 220, LOW); // Gira sobre su eje     //        } Método para inicar las rutinas de combate, ir, tocar la línea y regresar al combate
         delay(300);                                        //         }
           motores(250, LOW, 250, HIGH);                 //           }
           delay(100);                                //             }
 }
    int left    = analogRead(SENSOR_LEFT)     > 100 ? 1 : 0;
    int center  = analogRead(SENSOR_CENTER)   > 100 ? 1 : 0;
    int right   = analogRead(SENSOR_RIGHT)    > 100 ? 1 : 0;
    
    delay(100);
    Serial.println(" ");//imprime renglón en blanco.
    Serial.print(left);   Serial.println(" | Izquierda"); 
    Serial.print(center); Serial.println(" | Centro"); 
    Serial.print(right);  Serial.println(" | Derecha"); 
    
   /* if (izquierda == 0 && centro == 0 && derecha == 0) {
        Serial.println("Todos los sensores detectan BLANCO");
        motores(0, HIGH, 0, HIGH);
        medir();
    } else if (izquierda == 1 && centro == 1 && derecha == 1) {
        Serial.println("Todos los sensores detectan NEGRO");
        motores(250, LOW, 250, HIGH);
        medir();
    } else if (izquierda == 1 && centro == 0 && derecha == 1) {
        Serial.println("Línea detectada en el CENTRO");
        motores(150, HIGH, 150, HIGH);
        medir();
    } else if (izquierda == 0 && centro == 1 && derecha == 1) {
        Serial.println("Línea detectada a la DERECHA");
        motores(100, LOW, 150, HIGH);
        medir();
    } else if (izquierda == 1 && centro == 1 && derecha == 0) {
        Serial.println("Línea detectada a la IZQUIERDA");
        motores(150, HIGH, 100, LOW);
        medir();
    } else if (izquierda == 0 && centro == 1 && derecha == 0) {
        Serial.println("Línea detectada enfrente");
        motores(150, LOW, 150, LOW);*/
        medir();
                  delay(200);

       }
     }
   }



void INIT_pines(){

    pinMode(PWM_A, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWM_B, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);

    pinMode(Trigger, OUTPUT);
    pinMode(Echo, INPUT);
    pinMode(GO, INPUT);
    pinMode(RDY, INPUT);
    
    pinMode(SENSOR_LEFT, INPUT);
    pinMode(SENSOR_CENTER, INPUT);
    pinMode(SENSOR_RIGHT, INPUT);
}

void motores(int velA, int dirA, int velB, int dirB) {
    digitalWrite(AIN1, !dirA);
    digitalWrite(AIN2, dirA);
    analogWrite(PWM_A, velA);

    digitalWrite(BIN1, dirB);
    digitalWrite(BIN2, !dirB);
    analogWrite(PWM_B, velB);
}
