void enterDeepSleep() {
  ESP.deepSleep(0, WAKE_RF_DISABLED); // Сон на неопределенное время

  // Настройка прерываний для пробуждения
  pinMode(FireModeSw, INPUT);
  attachInterrupt(digitalPinToInterrupt(FireModeSw), wakeUp, CHANGE);

  // Переход в глубокий сон
  ESP.deepSleep(0);
}

void wakeUp() {
  // Обработчик прерывания для пробуждения
  // Ничего не делаем, просто выходим из сна
}