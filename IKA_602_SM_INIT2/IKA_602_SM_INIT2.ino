#define GO 13
#define RDY A0

#define SENSOR_IZQUIERDA A1
#define SENSOR_CENTRO A2
#define SENSOR_DERECHA A3

int PWM_A = 3;
int AIN2 = 4;
int AIN1 = 5;
int STBY = 6;
int BIN1 = 7;
int BIN2 = 8;
int PWM_B = 9;

int Trigger=10;
int Echo=11;



void setup() {
    pinMode(GO,INPUT);
    pinMode(RDY,INPUT);
    
    pinMode(SENSOR_IZQUIERDA, INPUT);
    pinMode(SENSOR_CENTRO, INPUT);
    pinMode(SENSOR_DERECHA, INPUT);

    pinMode(PWM_A, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWM_B, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);

    pinMode(Trigger,OUTPUT);
    pinMode(Echo, INPUT);
  

    
    digitalWrite(STBY, HIGH);
    Serial.begin(9600);
}

void  motores(int velA, int dirA, int velB, int dirB){
    digitalWrite(AIN1, dirA);
    digitalWrite(AIN2, !dirA); //Niega la velocidad derecha, si es HIGH lo pasa a LOW y viceversa
    digitalWrite(PWM_A, velA);

    digitalWrite(BIN1, dirB);
    digitalWrite(BIN2, !dirB); //Niega la velocidad derecha, si es HIGH lo pasa a LOW y viceversa
    digitalWrite(PWM_A, velB);
}

      float distancia(){ 
              digitalWrite(Trigger, LOW);
              delayMicroseconds(2);
              digitalWrite(Trigger, HIGH);
              delayMicroseconds(5);
              digitalWrite(Trigger,LOW);
              long tiempo = pulseIn(Echo, HIGH);
              return (tiempo * 0.0343) / 2;
              Serial.println(tiempo);
            }
            //vgffvvyyyfgvygygygygvgggyvfgg
            //Prueba 2


void loop() {
//if(GO==HIGH){
    float medida= distancia();
    Serial.print("Distancia:"); Serial.print(medida);Serial.print("cm");
    if(medida> 0 && medida < 30){
      motores(150, HIGH, 150,  HIGH);
    } else { 
      motores(0, HIGH, 0, HIGH);
    }
    delay(20);
    
    int izquierda = analogRead(SENSOR_IZQUIERDA) > 100 ? 1 : 0;
    int centro = analogRead(SENSOR_CENTRO)> 100 ? 1 : 0;
    int derecha = analogRead(SENSOR_DERECHA)> 100 ? 1 : 0;
    delay(100);
    Serial.println(" \t ");
    Serial.print(izquierda); Serial.println(" | Izquierda: "); 
    Serial.print(centro);    Serial.println(" | Centro: "); 
    Serial.println(derecha); Serial.println(" | Derecha: "); 
    
    // Detectar línea 
    if (izquierda == 0 && centro == 0 && derecha == 0) {
        Serial.println("Todos los sensores detectan BLANCO");
    } 
    
    
    else if (izquierda == 1 && centro == 1 && derecha == 1) {
        Serial.println("Todos los sensores detectan NEGRO");
    } 
    
    
    else if (izquierda == 1 && centro == 0 && derecha == 1) {
        Serial.println("Línea detectada en el CENTRO");
        motores(150, HIGH, 150,  HIGH); //avanzar hacia enfrente 
    } 
    
    
    else if (izquierda == 0 && centro == 1 && derecha == 1) {
        Serial.println("Línea detectada a la IZQUIERDA");
        motores(100, LOW, 150, HIGH); // girrar a la izquierda
    } 
    
    
    else if (izquierda == 1 && centro == 1 && derecha == 0) {
        Serial.println("Línea detectada a la DERECHA");
        motores(150, HIGH, 100, LOW); //girar a la derecha
    } 
    
    
    else if(izquierda==0 && centro==1 && derecha ==0){
      Serial.println("Línea detectada enfrente");
      motores(150, LOW, 150, LOW); //retroceder
    }
    
    delay(100);
    


//}
}
