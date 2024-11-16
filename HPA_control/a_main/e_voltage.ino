void Volt() {
  VoltValue = analogRead(analogPin);    //данные с аналогового пина
  ResVoltValue =  (float) analogRead(analogPin) * Settings.VoltCorr * ((Settings.DIV_R1+Settings.DIV_R2)/Settings.DIV_R2) / 1024.0;   //преобразуем согласно корректировки делителя
  ProcVol = map(ResVoltValue, 0.00, 12.60, 0.0, 100.0);    //Преобразуем в проценты из расчета на 3S аккум
  constrain (ProcVol, 0, 100);
  Serial.print("Voltage = ");   //Выводим в порт слово
  Serial.print(ResVoltValue);   //Пишем напряжение
  Serial.print(" ");
  Serial.print(ProcVol);
  Serial.print(" % ");
  Serial.print(VoltValue);
  Serial.println(" ");
  VoltTime = millis();
}