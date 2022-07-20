const int SEGMENT[11][8] = {
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW}, //0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW}, //1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW}, //2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW}, //3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW}, //4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW}, //5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, //6
  {HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW, LOW}, //7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, //8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW}, //9
  {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW} //OFF
};

const int OUT_PIN[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19};
const int IN_PIN[] = {22, 24, 26};

void setup() {
  for (int i : OUT_PIN) {
    pinMode(i, OUTPUT);
  }
  for (int i : IN_PIN) {
    pinMode(i, INPUT);
  }
}

void loop() {
  
}

void segStep(int l, int r) {
  for (int n = 0; n < 4; n++) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    _step(n);
    if (n % 2 == 0) {
      segL(l);
    } else {
      segR(r);
    }
    delay(1);
  }
}

void stepping() {
  for (int n = 0; n < 4; n++) {
    _step(n);
  }
}

void _step(int n) {
  int ptn[4][4] = {
    {HIGH, HIGH, LOW, LOW},
    {LOW, HIGH, HIGH, LOW},
    {LOW, LOW, HIGH, HIGH},
    {HIGH, LOW, LOW, HIGH}
  };

  for (int i = 12; i <= 15; i++) {
    digitalWrite(i, ptn[n][i - 12]);
  }
  clk();
}

void clk() {
  digitalWrite(5, HIGH);
  delay(10);
  digitalWrite(5, LOW);
}

void segW(int l, int r) {
  segL(l);
  delay(10);
  segR(r);
  delay(10);
}

void segR(int num) {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  seg(num);
}

void segL(int num) {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  seg(num);
}

void seg(int num) {
  for (int i = 12; i <= 19; i++) {
    digitalWrite(i, SEGMENT[num][i - 12]);
  }
}
