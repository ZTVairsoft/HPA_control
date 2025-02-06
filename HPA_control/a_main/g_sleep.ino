void enterDeepSleep() {
  // Настройка прерываний для пробуждения
  pinMode(FIREMODESW, INPUT);
  attachInterrupt(digitalPinToInterrupt(FIREMODESW), wakeUp, CHANGE);

  ESP.deepSleep(0, WAKE_RF_DISABLED); // Сон на неопределенное время
}

void wakeUp() {
  // Обработчик прерывания для пробуждения
  // Ничего не делаем, просто выходим из сна
}