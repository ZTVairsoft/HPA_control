void setup() {
  Serial.begin(115200);
  if (digitalRead(FireModeSw) == HIGH) {
  WiFi.mode(WIFI_STA);
  //WiFi.mode(WIFI_AP);
  WiFi.begin(AP_SSID, AP_PASS);
  //WiFi.softAP(AP_SSID, AP_PASS);
  //WiFi.softAP(AP_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  //Serial.println("192.168.4.1");
  }

  // подключаем конструктор и запускаем
  ui.attachBuild(build);
  ui.attach(action);
  ui.start();
  ui.enableOTA();

  if (!LittleFS.begin()) Serial.println("FS Error");
  ui.downloadAuto(true);

  EEPROM.begin(512);

  mem1.begin(0, 'a');
  mem2.begin(mem1.nextAddr(), 'a');
  // Serial.println(stat);

  // for (uint16_t i = memory.startAddr(); i < memory.endAddr() + 1; i++)
  //   Serial.write(EEPROM.read(i));
  // Serial.println();

  pinMode(solPin, OUTPUT);
  pinMode(TrigPin, INPUT);
  pinMode(FireModeSw, INPUT);
  pinMode(ExtraPin, OUTPUT);
}