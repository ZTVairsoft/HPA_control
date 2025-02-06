// void AutoShot() {                              //авто огонь
//   int count = 0;                               //вводим переменную количества совершенных выстрелос
//   while (count < Settings.numOfShotsAuto && triggerState == true) {    //делаем пока значение счетчика выстрелов не станет больше количества разрешенных выстрелов
//     if (Settings.numOfShotsAuto > 0) count++;  //+1 к счетчику выстрелов внутри функции
//     digitalWrite(SOLPIN, HIGH);  //открываем соленоид
//     delay(Settings.shotTime);   //задержка в открытом состоянии
//     lastShot = millis();
//     isLS = 1;
//     if (Settings.isTracer == 1) {
//       isLSTr = 1;
//       tracLastShot = millis();
//       digitalWrite(TRACER, HIGH);
//     }
//     WR.shotCount++;  //+1 к счетчику выстрелов
//     digitalWrite(SOLPIN, LOW);          //отключаем соленоид
//     delay(Settings.shotWait);          //делаем перерыв
//     triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//     if (triggerState == false) {  //если отжимаем спуск то прерываем очередь
//       break;
//     }
//   }
//   while (triggerState == true) {  //в случае превышения количества выстрелов останавливаемся и ждём когда спуск будет отжат
//     delay(1);
//     triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//   }
// }

// void DoubleShot() {            //функция стрельбы в 2 движения нажатие и отпускание для CQB
//   digitalWrite(SOLPIN, HIGH);  //открываем соленоид
//   delay(Settings.shotTime);   //задержка в открытом состоянии
//   lastShot = millis();
//   isLS = 1;
//   if (Settings.isTracer == 1) {
//     isLSTr = 1;
//     tracLastShot = millis();
//     digitalWrite(TRACER, HIGH);
//   }
//   WR.shotCount++;  //+1 к счетчику выстрелов
//   digitalWrite(SOLPIN, LOW);                        //отключаем соленоид
//   delay(Settings.shotWait);  //задержка от дребезга контактов
//   triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//   while (triggerState == true) {            //ожидание когда спуск будет отпущен
//     triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//     delay(1);                                       //задержка между проверками
//   }

//   digitalWrite(SOLPIN, HIGH);  //открываем соленоид
//   delay(Settings.shotTime);   //задержка в открытом состоянии
//   lastShot = millis();
//   isLS = 1;
//   if (Settings.isTracer == 1) {
//     isLSTr = 1;
//     tracLastShot = millis();
//     digitalWrite(TRACER, HIGH);
//   }
//   WR.shotCount++;  //+1 к счетчику выстрелов
//   digitalWrite(SOLPIN, LOW);                        //отключаем соленоид
//   delay(Settings.shotWait);
// }

// void SingleShot() {            //функция стрельбы одиночкой
//   digitalWrite(SOLPIN, HIGH);  //открываем соленоид
//   delay(Settings.shotTime);   //задержка в открытом состоянии
//   lastShot = millis();
//   isLS = 1;
//   if (Settings.isTracer == 1) {
//     isLSTr = 1;
//     tracLastShot = millis();
//     digitalWrite(TRACER, HIGH);
//   }
//   WR.shotCount++;  //+1 к счетчику выстрелов
//   digitalWrite(SOLPIN, LOW);              //отключаем соленоид
//   if (Settings.Mode == 1) {
//     delay(Settings.shotWait + Settings.shotDelay);  //задержка от дребезга контактов
//   } else {
//     delay(Settings.shotWait);   //задержка от дребезга контактов
//   }
//   delay(Settings.shotWait);              //задержка от дребезга контактов
//   triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//   while (triggerState == true) {  //ожидание когда спуск будет отпущен
//     triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//     delay(1);                             //задержка между проверками
//   }
// }

// void ShortShot() {                           //стрельба короткими очередями
//   int count = 0;                             //вводим переменную количества совершенных выстрелос
//   while (count < Settings.numOfShotsSemi && triggerState == true) {  //делаем пока значение счетчика выстрелов не станет больше количества разрешенных выстрелов
//     count++;                     //+1 к счетчику выстрелов внутри функции
//     digitalWrite(SOLPIN, HIGH);  //открываем соленоид
//     delay(Settings.shotTime);   //задержка в открытом состоянии
//     lastShot = millis();
//     isLS = 1;
//     if (Settings.isTracer == 1) {
//       isLSTr = 1;
//       tracLastShot = millis();
//       digitalWrite(TRACER, HIGH);
//     }
//     WR.shotCount++;  //+1 к счетчику выстрелов
//     digitalWrite(SOLPIN, LOW);          //отключаем соленоид
//     delay(Settings.shotWait);          //делаем перерыв
//     triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//     if (triggerState == false) {  //если отжимаем спуск то прерываем очередь
//       break;
//     }
//   }
//   triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//   while (triggerState == true) {  //в случае превышения количества выстрелов останавливаемся и ждём когда спуск будет отжат
//     triggerState = digitalRead(TRIGPIN) ^ Settings.convTrig; //проверяем состояние спуска
//     delay(1);
//   }
// }

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