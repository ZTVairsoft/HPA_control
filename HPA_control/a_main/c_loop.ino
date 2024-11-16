void loop() {
  ui.tick();

  // if (memory.tick()) Serial.println("Updated!");
  mem1.tick();
  mem2.tick();

  /*if (millis() - VoltTime > 5000){
  for (uint16_t i = memory.startAddr(); i < memory.endAddr() + 1; i++)
    Serial.write(EEPROM.read(i));
  Serial.println();
}*/

  if (WiFi.status() != WL_CONNECTED && millis() - LastShot >= Settings.TimeLastShot * 60000 && LS == 1) {
    WR.WriteCount++;
    mem2.update();
    LS = 0;
  }

  if (millis() - VoltTime > 5000) { //проверка напряжения
    Volt();
  }


  if (digitalRead(FireModeSw) == HIGH) {        //переключатель огня нажат
    Mode1 = 2;                                  //режим очереди
  } else if (digitalRead(FireModeSw) == LOW) {  //переключатель огня не нажат
    Mode1 = 1;                                  //режим одиночки
  }

  if (digitalRead(TrigPin) == HIGH) {
    if (Settings.Mode2 == 0) {  //обычный с очередью
      if (Mode1 == 1) {         //если стоит на одиночке то
        SingleShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        AutoShot();
      }
    } else if (Settings.Mode2 == 1) {  //обычный с отсечкой
      if (Mode1 == 1) {                //если стоит на одиночке то
        SingleShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        ShortShot();
      }
    } else if (Settings.Mode2 == 2) {  //обычный с отсечкой и очередью
      if (Mode1 == 1) {                //если стоит на одиночке то
        ShortShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        AutoShot();
      }
    } else if (Settings.Mode2 == 3) {  //CQB Mode со стрельбой одиночкой на любых положениях
      if (Mode1 == 1) {                //если стоит на одиночке то
        SingleShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        SingleShot();
      }
    } else if (Settings.Mode2 == 4) {  //режим пулеметный, в любом положении стрельба очередями
      if (Mode1 == 1) {                //если стоит на одиночке то
        AutoShot();
      } else if (Mode1 == 2) {  //или стоит на очереди
        AutoShot();
      }
    }
  }
}