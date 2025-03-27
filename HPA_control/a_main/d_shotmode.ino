void FireSolenoid() {
  digitalWrite(SOLPIN, HIGH);  // Открываем соленоид
  delay(Settings.shotTime);    // Задержка в открытом состоянии
  lastShot = millis();
  isLS = 1;
  if (Settings.isTracer == 1) {
    isLSTr = 1;
    tracLastShot = millis();
    digitalWrite(TRACER, HIGH);
  }
  WR.shotCount++;  // +1 к счетчику выстрелов
  digitalWrite(SOLPIN, LOW);  // Отключаем соленоид
}

void WaitForTriggerRelease() {
  while (triggerState == true) {
    triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; // Проверяем состояние спуска
    delay(1);
  }
}

void PerformShot() {
  FireSolenoid();
  delay(Settings.shotWait);  // Задержка между выстрелами
}

void AutoShot() {
  int count = 0;
  while (count < Settings.numOfShotsAuto && triggerState == true) {
    PerformShot();
    count++;
    triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig;
    if (triggerState == false) {
      break;
    }
  }
  WaitForTriggerRelease();
}

void DoubleShot() {
  PerformShot();
  WaitForTriggerRelease();
  PerformShot();
}

void SingleShot() {
  PerformShot();
  if (Settings.Mode == 1) {
    delay(Settings.shotWait + Settings.shotDelay);
  } else {
    delay(Settings.shotWait);
  }
  WaitForTriggerRelease();
}

void ShortShot() {
  int count = 0;
  while (count < Settings.numOfShotsSemi && triggerState == true) {
    PerformShot();
    count++;
    triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig;
    if (triggerState == false) {
      break;
    }
  }
  WaitForTriggerRelease();
}