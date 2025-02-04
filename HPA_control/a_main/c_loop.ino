void loop() {
  ui.tick();

  // if (memory.tick()) Serial.println("Updated!");
  mem1.tick();
  mem2.tick();
  mem3.tick();

  /*if (millis() - VoltTime > 5000){
  for (uint16_t i = memory.startAddr(); i < memory.endAddr() + 1; i++)
    Serial.write(EEPROM.read(i));
  Serial.println();
}*/

  if (WiFi.status() != WL_CONNECTED && millis() - LastShot >= Settings.TimeLastShot * 60000 && LS == 1) {  //сохранение настрела если не включен WiFi
    WR.WriteCount++;
    mem2.update();
    LS = 0;
  }


  if (Settings.tracer == 1 && LSTr == 0 && Settings.tracTime * 1000 <= millis()) {  //Выключение трассерки после включения через заданное время
    digitalWrite(ExtraPin, LOW);
  }

  if (Settings.tracer == 1 && LSTr == 1 && TracLastShot + (Settings.tracTime * 1000) <= millis()) {  //ВЫключение трассерки после заданного времени после выстрела
    digitalWrite(ExtraPin, LOW);
    LSTr = 0;
  }

  if (millis() - VoltTime > 5000) {  //проверка напряжения
    Volt();
  }

  triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig;
  safetyState = digitalRead(ProgSafe) ^ Settings.ConvSafe;
  autoModeState = digitalRead(FireModeSw) ^ Settings.ConvSel;

  deepSleepTime = Settings.deepSleepMin * 1000 * 60;

  if (autoModeState == true) {
    Mode1 = 2;
  } else if (autoModeState == false) {
    Mode1 = 1;
  }

  if (safetyState == true) {
    // Если предохранитель нажат, соленоид отключен
    digitalWrite(solPin, LOW);
    return;
  }

  if (millis() - LastShot >= deepSleepTime || batSafeFlag == true) {
    // Переход в глубокий сон
    Serial.println("сон");
    enterDeepSleep();
  }

  if (triggerState == true) {  //проверка нажатия на спуск
    if (Settings.Mode2 == 0) { //Автомат
      if (Mode1 == 1) {         //если стоит на одиночке то
        SingleShot();
      } else if (Mode1 == 2 && Settings.NumOfShotsSemi > 0) {  //или стоит на очереди
        ShortShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        AutoShot();
      }
    } else if (Settings.Mode2 == 1) {  //Снайпер
      if (Mode1 == 1) {                //если стоит на одиночке то
        SingleShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        SingleShot();
      }
    } else if (Settings.Mode2 == 2) {                     //CQB
      if (Mode1 == 1 && Settings.Double_Shot == false) {  //если стоит на одиночке то
        SingleShot();
      } else if (Mode1 == 2 && Settings.Double_Shot == false) {  //или стоит на очереди
        SingleShot();
      } else if (Mode1 == 1 && Settings.Double_Shot == true) {  //CQB двойное действие
        DoubleShot();                                           //если стоит на одиночке то
      } else if (Mode1 == 2 && Settings.Double_Shot == true) {  //или стоит на очереди
        DoubleShot();
      }
    } else if (Settings.Mode2 == 3) {  //Пулемет
      if (Mode1 == 1) {                //если стоит на одиночке то
        AutoShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        AutoShot();
      }
    }
  }
}