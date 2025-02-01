void AutoShot() {                              //авто огонь
  int count = 0;                               //вводим переменную количества совершенных выстрелос
  while (count < Settings.NumOfShotsAuto) {    //делаем пока значение счетчика выстрелов не станет больше количества разрешенных выстрелов
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
    if (digitalRead(TrigPin) == LOW) {  //если отжимаем спуск то прерываем очередь
      break;
    }
  }
  while (digitalRead(TrigPin) == HIGH) {  //в случае превышения количества выстрелов останавливаемся и ждём когда спуск будет отжат
    delay(1);
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
  while (digitalRead(TrigPin) == HIGH) {            //ожидание когда спуск будет отпущен
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
  while (digitalRead(TrigPin) == HIGH) {  //ожидание когда спуск будет отпущен
    delay(1);                             //задержка между проверками
  }
}

void ShortShot() {                           //стрельба короткими очередями
  int count = 0;                             //вводим переменную количества совершенных выстрелос
  while (count < Settings.NumOfShotsSemi) {  //делаем пока значение счетчика выстрелов не станет больше количества разрешенных выстрелов
    //Serial.println(count);
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
    if (digitalRead(TrigPin) == LOW) {  //если отжимаем спуск то прерываем очередь
      break;
    }
  }
  while (digitalRead(TrigPin) == HIGH) {  //в случае превышения количества выстрелов останавливаемся и ждём когда спуск будет отжат
    delay(1);
  }
}