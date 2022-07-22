#define CLOCK_MS 10

void setup() {
  // アウトプットピン
  const int OUT_PIN[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19};
  // インプットプットピン
  const int IN_PIN[] = {22, 24, 26};
  
  // アウトプットピンの初期化
  for (int i : OUT_PIN) {
    pinMode(i, OUTPUT);
  }

  // インプットピンの初期化
  for (int i : IN_PIN) {
    pinMode(i, INPUT);
  }
  // 一度だけ実行するコードはこの下に
  
}

void loop() {
  // 繰り返し実行するコードはこの下に
  
}

// セグメント両側点灯しつつステッピングを回す関数
void segStep(int l, int r) {
  for (int n = 0; n < 4; n++) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    _step(n);
    
    segL(l);
    delay(1);// 点灯時間を確保
    segR(r);
    delay(1);
  }
}

// ステッピング右回転
void steppingR() {
  for (int n = 3; n >= 0; n--) {
    _step(n);
  }
}

// ステッピング左回転
void steppingL() {
  for (int n = 0; n < 4; n++) {
    _step(n);
  }
}

// ステッピング1/4ステップ
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

// クロック
void clk() {
  digitalWrite(5, HIGH);
  delay(CLOCK_MS);
  digitalWrite(5, LOW);
}

// セグメント両点灯
void segW(int l, int r) {
  segL(l);
  segR(r);
}

// 右セグメント点灯
void segR(int num) {
  seg(10);// ここでリセットかけるとdelayいらない
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  seg(num);
}

// 左セグメント点灯
void segL(int num) {
  seg(10);// ここでリセットかけるとdelayいらない
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  seg(num);
}

// セグメントにデータ送信
void seg(int num) {
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
  for (int i = 12; i <= 19; i++) {
    digitalWrite(i, SEGMENT[num][i - 12]);
  }
}
