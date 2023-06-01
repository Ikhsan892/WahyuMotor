#define sensorProx 23
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorProx, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int nilaiProx = digitalRead(sensorProx);
  if (nilaiProx == LOW ){
    counter++;
    while(!nilaiProx);
    
  }
   Serial.println(counter);
 
  
}
