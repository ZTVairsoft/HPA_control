void Volt() {
  VoltValue = analogRead(A0);    //данные с аналогового пина
  float voltage = VoltValue *  (Settings.VoltCorr / 1023.0);
  ResVoltValue = voltage * (Settings.DIV_R1+Settings.DIV_R2)/Settings.DIV_R2;   //преобразуем согласно корректировки делителя
  if (Settings.batType == 2){
    ProcVol = voltageToPercentage2S(ResVoltValue);    //Преобразуем в проценты из расчета на 2S аккум
  }else if(Settings.batType == 3){
    ProcVol = voltageToPercentage3S(ResVoltValue);    //Преобразуем в проценты из расчета на 3S аккум
  }
  VoltTime = millis();
}

float voltageToPercentage2S(float voltage) {
  const float voltageLevels[] = {8.4, 8.2, 8.0, 7.8, 7.6, 7.4, 7.2, 6.0};
  const float socLevels[] = {100, 90, 70, 50, 30, 15, 5, 0};

  if (voltage >= voltageLevels[0]) return 100.0;
  if (voltage <= voltageLevels[7]) return 0.0;

  for (int i = 0; i < 7; i++) {
    if (voltage >= voltageLevels[i + 1] && voltage < voltageLevels[i]) {
      float slope = (socLevels[i] - socLevels[i + 1]) / (voltageLevels[i] - voltageLevels[i + 1]);
      return socLevels[i] + slope * (voltage - voltageLevels[i]);
    }
  }
  return 0.0;
}

// Функция для преобразования напряжения в проценты заряда (3S)
float voltageToPercentage3S(float voltage) {
  const float voltageLevels[] = {12.6, 12.3, 12.0, 11.7, 11.4, 11.1, 10.8, 9.0};
  const float socLevels[] = {100, 90, 70, 50, 30, 15, 5, 0};

  if (voltage >= voltageLevels[0]) return 100.0;
  if (voltage <= voltageLevels[7]) return 0.0;

  for (int i = 0; i < 7; i++) {
    if (voltage >= voltageLevels[i + 1] && voltage < voltageLevels[i]) {
      float slope = (socLevels[i] - socLevels[i + 1]) / (voltageLevels[i] - voltageLevels[i + 1]);
      return socLevels[i] + slope * (voltage - voltageLevels[i]);
    }
  }
  return 0.0;
}