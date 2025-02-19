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


void setup() {
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

}5144ed 3sx          

void encontrarlinea(){
  motores(250, HIGH, 250, HIGH);
  if(izquierda == 1 && centro == 0 && derecha == 1){
    motores(200, HIGH, 150, LOW);
    distancia();
  }
}

void 



void loop() {
   float medida= distancia();
    Serial.print("Distancia:"); Serial.print(medida);Serial.print("cm");
    if(medida> 0 && medida < 30){
      if(medida<15){
      motores(150, HIGH, 150,  HIGH);
    } else { 
      motores(0, HIGH, 0, HIGH);
    }
    }else{
      motores(0, HIGH, 0, HIGH);
    }
    delay(20);

  int izquierda = analogRead(SENSOR_IZQUIERDA) > 100 ? 1 : 0;
  int centro = analogRead(SENSOR_CENTRO)> 100 ? 1 : 0;
  int derecha = analogRead(SENSOR_DERECHA)> 100 ? 1 : 0;
  
  Serial.print(izquierda); Serial.println(" | Izquierda: "); 
  Serial.print(centro);    Serial.println(" | Centro: "); 
  Serial.println(derecha); Serial.println(" | Derecha: "); 
  
  encontrarlinea();



}
