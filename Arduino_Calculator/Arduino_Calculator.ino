const int btn1 = 2; // number 1 input
const int btn2 = 3; // number 2 input
const int btnAdd = 4;
const int btnSub = 5;
const int btnMul = 6;
const int btnDiv = 7;
const int btnRes = 8; // result button

int num1 = 0;
int num2 = 0;
char operation = ' ';

void setup() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btnAdd, INPUT_PULLUP);
  pinMode(btnSub, INPUT_PULLUP);
  pinMode(btnMul, INPUT_PULLUP);
  pinMode(btnDiv, INPUT_PULLUP);
  pinMode(btnRes, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  // Increment number 1
  if (digitalRead(btn1) == LOW) {
    num1++;
    Serial.print("Num1: ");
    Serial.println(num1);
    waitRelease(btn1);
  }

  // Increment number 2
  if (digitalRead(btn2) == LOW) {
    num2++;
    Serial.print("Num2: ");
    Serial.println(num2);
    waitRelease(btn2);
  }

  // Select operation
  if (digitalRead(btnAdd) == LOW) {
    operation = '+';
    Serial.println("Operation: +");
    waitRelease(btnAdd);
  }

  if (digitalRead(btnSub) == LOW) {
    operation = '-';
    Serial.println("Operation: -");
    waitRelease(btnSub);
  }

  if (digitalRead(btnMul) == LOW) {
    operation = '*';
    Serial.println("Operation: *");
    waitRelease(btnMul);
  }

  if (digitalRead(btnDiv) == LOW) {
    operation = '/';
    Serial.println("Operation: /");
    waitRelease(btnDiv);
  }

  // Calculate result
  if (digitalRead(btnRes) == LOW) {
    float result = 0;

    if (operation == '+') result = num1 + num2;
    else if (operation == '-') result = num1 - num2;
    else if (operation == '*') result = num1 * num2;
    else if (operation == '/' && num2 != 0) result = (float)num1 / num2;
    else Serial.println("Invalid operation");

    Serial.print("Result: ");
    Serial.println(result);

    waitRelease(btnRes);
  }
}

// software debouncing
void waitRelease(int pin) {
  delay(200);
  while (digitalRead(pin) == LOW); // wait till release
}