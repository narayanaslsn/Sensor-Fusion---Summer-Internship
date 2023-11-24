const int trigPin1 = 2;  // Trig pin of Sonar Sensor 1
const int echoPin1 = 3;  // Echo pin of Sonar Sensor 1

const int trigPin2 = 4;  // Trig pin of Sonar Sensor 2
const int echoPin2 = 5;  // Echo pin of Sonar Sensor 2

const int trigPin3 = 6;  // Trig pin of Sonar Sensor 3
const int echoPin3 = 7;  // Echo pin of Sonar Sensor 3

float SensorData, KalmanFilterData;
float Xt, Xt_update, Xt_prev;
float Pt, Pt_update, Pt_prev;
float Kt, R, Q;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  R=100; Q=1; Pt_prev=1;
}

void loop() {
  float distance1 = getSonarDistance(trigPin1, echoPin1);
  float distance2 = getSonarDistance(trigPin2, echoPin2);
  float distance3 = getSonarDistance(trigPin3, echoPin3);

  float fusedDistance = fuseDistances(distance1, distance2, distance3);

  Serial.print("Sonar 1 Distance: ");
  Serial.print(distance1);
  Serial.print(" cm\t");

  Serial.print("Sonar 2 Distance: ");
  Serial.print(distance2);
  Serial.print(" cm\t");

  Serial.print("Sonar 3 Distance: ");
  Serial.print(distance3);
  Serial.print(" cm\t");

//  Serial.print("Fused Distance: ");
//  Serial.print(fusedDistance);
//  Serial.println(" cm");

  Serial.print("FusedData: ");
  Serial.print(SensorData,3);
  Serial.print(",");
  Serial.print("KalmanFilterData: ");
  Serial.print(KalmanFilterData,3);
  Serial.print(" cm");
  Serial.println();
  delay(1000);
  
}

float getSonarDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;  // Calculate distance in centimeters

  return distance;
}

float fuseDistances(float distance1, float distance2, float distance3) {
  // Apply sensor fusion technique here (e.g., averaging, weighted average, filtering)

  // Example: Simple averaging
  float fusedDistance = (distance1 + distance2 + distance3) / 3;
  SensorData = fusedDistance;
  Xt_update = Xt_prev;
  Pt_update = Pt_prev + Q;
  Kt = Pt_update / (Pt_update + R);
  Xt = Xt_update + ( Kt * (SensorData - Xt_update));
  Pt = (1 - Kt) * Pt_update;
  Xt_prev = Xt;
  Pt_prev = Pt;
  KalmanFilterData=Xt;
 
  return KalmanFilterData;
}
