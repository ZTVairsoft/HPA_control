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

  if (millis() - VoltTime > 5000) {  //проверка напряжения
    Volt();
  }

  if (Settings.tracer == 1 && LSTr == 0 && Settings.tracTime * 1000 <= millis()) {  //Выключение трассерки после включения
    digitalWrite(ExtraPin, LOW);
  }

  if (Settings.tracer == 1 && LSTr == 1 && TracLastShot + (Settings.tracTime * 1000) <= millis()) {  //ВЫключение трассерки после заданного времени
    digitalWrite(ExtraPin, LOW);
    LSTr = 0;
  }

  if (Settings.ConvSel == 0) {
    if (digitalRead(FireModeSw) == HIGH) {        //переключатель огня нажат
      Mode1 = 2;                                  //режим очереди
      firemode = true;                            //нажат
    } else if (digitalRead(FireModeSw) == LOW) {  //переключатель огня не нажат
      Mode1 = 1;                                  //режим одиночки
      firemode = false;                           //отжат
    }
  } else {
    if (digitalRead(FireModeSw) == HIGH) {        //переключатель огня нажат
      Mode1 = 1;                                  //режим одиночки
      firemode = false;                           //отжат
    } else if (digitalRead(FireModeSw) == LOW) {  //переключатель огня не нажат
      Mode1 = 2;                                  //режим очереди
      firemode = true;                            //нажат
    }
  }

  if (Settings.ConvSafe == false && digitalRead(ProgSafe) == HIGH || Settings.ConvSafe == true && digitalRead(ProgSafe) == LOW) {  //проверка предохранителя
    FlagSafe = true;
  } else {
    FlagSafe = false;
  }

  if (digitalRead(TrigPin) == HIGH){
    trig = true;
  }else{trig = false;}

  if (digitalRead(TrigPin) == HIGH && Settings.ConvTrig == false && FlagSafe == false || digitalRead(TrigPin) == LOW && Settings.ConvTrig == true && FlagSafe == false) {  //проверка нажатия на спуск
    if (Settings.Mode2 == 0) {                                                                                                                                             //Автомат
      if (Mode1 == 1) {                                                                                                                                                    //если стоит на одиночке то
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