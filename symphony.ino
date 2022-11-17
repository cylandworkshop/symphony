const int N = 4;
const int mgn[N] = {16, 17, 18, 19};

const int out[N] = {9, 8, 7, 6};
int prev[N] = {0,0,0,0};

uint32_t start_time[N] = {0,0,0,0};

const int TRIG_DELAY = 200;

void setup() {
  Serial.begin(115200);

  for(int i = 0; i < N; i++) {
    pinMode(mgn[i], INPUT_PULLUP);
  }

  for(int i = 0; i < N; i++) {
    pinMode(out[i], OUTPUT);
  }
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  for(int i = 0; i < N; i++) {
    uint8_t r = digitalRead(mgn[i]);
    
    if (r == LOW && prev[i] == 1) {
      // start of trigger
      start_time[i] = millis();
      prev[i] = 0;
    }
    if (r == HIGH && prev[i] == 0) {
      digitalWrite(out[i], LOW);
      prev[i] = 1;
    }

    digitalWrite(out[i], millis() - start_time[i] < TRIG_DELAY ? HIGH : LOW);
  }


  Serial.print(prev[0]);
  Serial.print(" ");
  Serial.print(prev[1]);
  Serial.print(" ");
  Serial.print(prev[2]);
  Serial.print(" ");
  Serial.println(prev[3]);

  delay(1);
}
