#define GO A0
#define RDY 13

#define SENSOR_IZQUIERDA A1
#define SENSOR_CENTRO A3
#define SENSOR_DERECHA A2

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
    digitalWrite(AIN1, !dirA);
    digitalWrite(AIN2, dirA); //Niega la velocidad derecha, si es HIGH lo pasa a LOW y viceversa
    analogWrite(PWM_A, velA);

    digitalWrite(BIN1, dirB);
    digitalWrite(BIN2, !dirB); //Niega la velocidad derecha, si es HIGH lo pasa a LOW y viceversa
    analogWrite(PWM_B, velB);
}

      float distancia(){ 
       long suma = 0;
    for (int i = 0; i < 5; i++) {
        digitalWrite(Trigger, LOW);
        delayMicroseconds(2);
        digitalWrite(Trigger, HIGH);
        delayMicroseconds(5);
        digitalWrite(Trigger, LOW);
        long tiempo = pulseIn(Echo, HIGH, 3000); // Timeout de 30ms
        if (tiempo == 0) return 999; // Si no detecta nada, devuelve un valor alto
        suma += tiempo;
    }
    long tiempo = suma / 5; // Promedio de 5 mediciones
    return (tiempo * 0.0343) / 2;
    }

    
   
        

void loop() {
  //if(GO==HIGH){
 
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

    // Convertir el tiempo en distancia (cm)
    distance = (duration * 0.0343) / 2;

    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    float medida= distancia();
    Serial.print("Distancia:"); Serial.print(medida);Serial.print("cm");
    if(medida> 0 && medida < 30){
      if(medida<15){
      motores(150, HIGH, 150,  HIGH);
    } 

    
    delay(20);
    
    int izquierda = analogRead(SENSOR_IZQUIERDA) > 100 ? 1 : 0;
    int centro = analogRead(SENSOR_CENTRO)> 100 ? 1 : 0;
    int derecha = analogRead(SENSOR_DERECHA)> 100 ? 1 : 0;
    delay(100);

   //   Serial.println(" \t ");
    Serial.print(izquierda); Serial.println(" | Izquierda "); 
    Serial.print(centro);    Serial.println(" | Centro "); 
    Serial.print(derecha);   Serial.println(" | Derecha "); 
    
    // Detectar línea 
    if (izquierda == 0 && centro == 0 && derecha == 0) {
        Serial.println("Todos los sensores detectan BLANCO");
        motores(0, HIGH, 0, HIGH);
    } 
    
    
    else if (izquierda == 1 && centro == 1 && derecha == 1) {
        Serial.println("Todos los sensores detectan NEGRO");
        motores(150, LOW, 150, HIGH );
        delay(250);
        motores(200, LOW, 150,HIGH );
    } 
    
    
    else if (izquierda == 1 && centro == 0 && derecha == 1) {
        Serial.println("Línea detectada en el CENTRO");
        motores(150, HIGH, 150,  HIGH); //avanzar hacia enfrente 
    } 
    
    
    else if (izquierda == 0 && centro == 1 && derecha == 1) {
        Serial.println("Línea detectada a la DERECHA");
        motores(100, LOW, 150, HIGH); // girrar a la izquierda
    } 
    
    
    else if (izquierda == 1 && centro == 1 && derecha == 0) {
        Serial.println("Línea detectada a la IZQUIERDA");
        motores(150, HIGH, 100, LOW); //girar a la derecha
    } 
    
    
    else if(izquierda==0 && centro==1 && derecha ==0){
      Serial.println("Línea detectada enfrente");
      motores(150, LOW, 150, LOW); //retroceder
    }
    
    delay(100);
    


 
  }}

