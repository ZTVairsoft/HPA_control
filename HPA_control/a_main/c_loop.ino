void loop() {
  ui.tick();

  mem1.tick();
  mem2.tick();
  mem3.tick();

  if (WiFi.status() != WL_CONNECTED && millis() - lastShot >= Settings.timeLastShot * 60000 && isLS == 1) {  //сохранение настрела если не включен WiFi
    WR.writeCount++;
    mem2.update();
    isLS = 0;
  }


  if (Settings.isTracer == 1 && isLSTr == 0 && Settings.tracTime * 1000 <= millis()) {  //Выключение трассерки после включения через заданное время
    digitalWrite(TRACER, LOW);
  }

  if (Settings.isTracer == 1 && isLSTr == 1 && tracLastShot + (Settings.tracTime * 1000) <= millis()) {  //ВЫключение трассерки после заданного времени после выстрела
    digitalWrite(TRACER, LOW);
    isLSTr = 0;
  }

  if (millis() - voltTime > 5000) {  //проверка напряжения
    Volt();
  }

  triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig;
  safetyState = digitalRead(PROGSAFE) ^ Settings.isConvSafe;
  autoModeState = digitalRead(FIREMODESW) ^ Settings.convSel;

  deepSleepTime = Settings.deepSleepMin * 1000 * 60;  //время до ухода в сон

  autoMode = autoModeState ? 2 : 1;

  if (millis() - lastShot >= deepSleepTime || isBatSafeFlag == true) {
    // Переход в глубокий сон
    Serial.println("сон");  //засыпает и не просыпается зараза
    enterDeepSleep();
  }

  if (safetyState == true) {
    // Если предохранитель нажат, соленоид отключен
    digitalWrite(SOLPIN, LOW);
    return;
  }

  if (triggerState == true) {  //проверка нажатия на спуск
    switch (Settings.Mode) {
      case AUTOMODE:  //режим автомата
        if (autoMode == SEMI) SingleShot();
        else if (Settings.numOfShotsSemi > 0) ShortShot();
        else AutoShot();
        break;
      case SNIPERMODE:  //режим снайпера
        SingleShot();
        break;
      case CQBMODE:  //режим CQB
        if (Settings.isDoubleShot) DoubleShot();
        else SingleShot();
        break;
      case MACHINEGUNMODE:  //режим пулемета
        AutoShot();
        break;
    }
  }
}