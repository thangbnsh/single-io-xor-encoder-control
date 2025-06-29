// Cấu hình chân
#define MOTOR_IO   18     // AIN1: điều khiển chiều quay
#define STBY_PIN   26     // STBY: bật driver
#define PWM_PIN    5      // PWMA: điều chỉnh tốc độ qua PWM
#define ENCODER_A  19     // C2 - Encoder Channel A
#define ENCODER_B  21     // C1 - Encoder Channel B

volatile long encoderCount = 0;

// Hàm xử lý ngắt encoder
void IRAM_ATTR encoderISR() {
  int A = digitalRead(ENCODER_A);
  int B = digitalRead(ENCODER_B);
  if (A == B)
    encoderCount++;
  else
    encoderCount--;
}

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_IO, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);
  digitalWrite(STBY_PIN, HIGH);      // Bật driver
  digitalWrite(MOTOR_IO, LOW);       // Quay thuận

  // PWM theo API mới (v3.0.0): KHÔNG truyền duty vào ledcAttach()
  ledcAttach(PWM_PIN, 20000, 8);     // freq = 20kHz, resolution = 8-bit
  ledcWrite(PWM_PIN, 128);           // thiết lập duty = 128 (50%)
  
  // Cấu hình encoder
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR, CHANGE);
}


void loop() {
  static long lastCount = 0;
  static unsigned long lastTime = 0;

  // --- Quay thuận với tốc độ tăng dần ---
  for (int duty = 0; duty <= 255; duty += 25) {
    ledcWrite(PWM_PIN, duty);
    Serial.print("Quay thuận - Duty: ");
    Serial.print(duty);
    Serial.print(" / Encoder: ");
    Serial.println(encoderCount);
    delay(500);
  }

  // --- Dừng ---
  ledcWrite(PWM_PIN, 0);
  delay(1000);

  // --- Đảo chiều quay ---
  digitalWrite(MOTOR_IO, HIGH);   // Quay ngược (AIN1 = 1 → AIN2 = 0 qua XOR)

  // --- Quay ngược với tốc độ giảm dần ---
  for (int duty = 255; duty >= 0; duty -= 25) {
    ledcWrite(PWM_PIN, duty);
    Serial.print("Quay ngược - Duty: ");
    Serial.print(duty);
    Serial.print(" / Encoder: ");
    Serial.println(encoderCount);
    delay(500);
  }

  // --- Dừng ---
  ledcWrite(PWM_PIN, 0);
  delay(2000);

  // Quay lại chiều thuận
  digitalWrite(MOTOR_IO, LOW);
}
