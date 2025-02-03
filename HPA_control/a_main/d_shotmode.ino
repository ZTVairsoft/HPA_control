void AutoShot() {                              //авто огонь
  int count = 0;                               //вводим переменную количества совершенных выстрелос
  while (count < Settings.NumOfShotsAuto && triggerState == true) {    //делаем пока значение счетчика выстрелов не станет больше количества разрешенных выстрелов
    if (Settings.NumOfShotsAuto > 0) count++;  //+1 к счетчику выстрелов внутри функции
    //Serial.print("auto:");
    //Serial.println(count);
    digitalWrite(solPin, HIGH);  //открываем соленоид
    delay(Settings.Shot_time);   //задержка в открытом состоянии
    LastShot = millis();
    LS = 1;
    if (Settings.tracer == 1) {
      LSTr = 1;
      TracLastShot = millis();
      digitalWrite(ExtraPin, HIGH);
    }
    WR.ShotCount1++;  //+1 к счетчику выстрелов
    //Serial.println(WR.ShotCount1);
    digitalWrite(solPin, LOW);          //отключаем соленоид
    delay(Settings.Shot_wait);          //делаем перерыв
    triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
    if (triggerState == false) {  //если отжимаем спуск то прерываем очередь
      break;
    }
  }
  while (triggerState == true) {  //в случае превышения количества выстрелов останавливаемся и ждём когда спуск будет отжат
    delay(1);
    triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
  }
}

void DoubleShot() {            //функция стрельбы в 2 движения нажатие и отпускание для CQB
  digitalWrite(solPin, HIGH);  //открываем соленоид
  delay(Settings.Shot_time);   //задержка в открытом состоянии
  LastShot = millis();
  LS = 1;
  if (Settings.tracer == 1) {
    LSTr = 1;
    TracLastShot = millis();
    digitalWrite(ExtraPin, HIGH);
  }
  WR.ShotCount1++;  //+1 к счетчику выстрелов
  //Serial.println(WR.ShotCount1);
  digitalWrite(solPin, LOW);                        //отключаем соленоид
  delay(Settings.Shot_wait);  //задержка от дребезга контактов
  triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
  while (triggerState == true) {            //ожидание когда спуск будет отпущен
    triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
    delay(1);                                       //задержка между проверками
  }

  digitalWrite(solPin, HIGH);  //открываем соленоид
  delay(Settings.Shot_time);   //задержка в открытом состоянии
  LastShot = millis();
  LS = 1;
  if (Settings.tracer == 1) {
    LSTr = 1;
    TracLastShot = millis();
    digitalWrite(ExtraPin, HIGH);
  }
  WR.ShotCount1++;  //+1 к счетчику выстрелов
  //Serial.println(WR.ShotCount1);
  digitalWrite(solPin, LOW);                        //отключаем соленоид
  delay(Settings.Shot_wait);
}

void SingleShot() {            //функция стрельбы одиночкой
  digitalWrite(solPin, HIGH);  //открываем соленоид
  delay(Settings.Shot_time);   //задержка в открытом состоянии
  LastShot = millis();
  LS = 1;
  if (Settings.tracer == 1) {
    LSTr = 1;
    TracLastShot = millis();
    digitalWrite(ExtraPin, HIGH);
  }
  WR.ShotCount1++;  //+1 к счетчику выстрелов
  //Serial.println(WR.ShotCount1);
  digitalWrite(solPin, LOW);              //отключаем соленоид
  if (Settings.Mode2 == 1) {
    delay(Settings.Shot_wait + Settings.Shot_delay);  //задержка от дребезга контактов
  } else {
    delay(Settings.Shot_wait);   //задержка от дребезга контактов
  }
  delay(Settings.Shot_wait);              //задержка от дребезга контактов
  triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
  while (triggerState == true) {  //ожидание когда спуск будет отпущен
    triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
    delay(1);                             //задержка между проверками
  }
}

void ShortShot() {                           //стрельба короткими очередями
  int count = 0;                             //вводим переменную количества совершенных выстрелос
  while (count < Settings.NumOfShotsSemi && triggerState == true) {  //делаем пока значение счетчика выстрелов не станет больше количества разрешенных выстрелов
    count++;                     //+1 к счетчику выстрелов внутри функции
    digitalWrite(solPin, HIGH);  //открываем соленоид
    delay(Settings.Shot_time);   //задержка в открытом состоянии
    LastShot = millis();
    LS = 1;
    if (Settings.tracer == 1) {
      LSTr = 1;
      TracLastShot = millis();
      digitalWrite(ExtraPin, HIGH);
    }
    WR.ShotCount1++;  //+1 к счетчику выстрелов
    //Serial.println(WR.ShotCount1);
    digitalWrite(solPin, LOW);          //отключаем соленоид
    delay(Settings.Shot_wait);          //делаем перерыв
    triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
    if (triggerState == false) {  //если отжимаем спуск то прерываем очередь
      break;
    }
  }
  triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
  while (triggerState == true) {  //в случае превышения количества выстрелов останавливаемся и ждём когда спуск будет отжат
    triggerState = digitalRead(TrigPin) ^ Settings.ConvTrig; //проверяем состояние спуска
    delay(1);
  }
}