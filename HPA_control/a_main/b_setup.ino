void setup() {
  Serial.begin(115200);

  EEPROM.begin(1024);

  mem1.begin(0, 'a');
  mem2.begin(mem1.nextAddr(), 'a');
  mem3.begin(mem2.nextAddr(), 'a');

  delay(500); //задержка для выхода из сна, можно успеть переключить переключатель огня что бы не включился Wi-Fi

  if (digitalRead(FIREMODESW) == HIGH && WF.apply == 0) {  //если переключатель режимов нажат то запускается wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(AP_SSID, AP_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println(WiFi.localIP());
    //Serial.println("192.168.4.1");
    Serial.println(WF.WF_SSID);
    Serial.println(WF.WF_PASS);
    Serial.println(WF.apply);
  } else if (digitalRead(FIREMODESW) == HIGH) {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(WF.WF_SSID, WF.WF_PASS);
    //WiFi.softAP(WF.WF_SSID);
    Serial.print("AP: ");
    Serial.println(WiFi.softAPIP());
  } else {
    WiFi.mode(WIFI_OFF);
  }



  // подключаем конструктор и запускаем
  ui.attachBuild(build);
  ui.attach(action);
  ui.start();
  ui.enableOTA();

  if (!LittleFS.begin()) Serial.println("FS Error");
  ui.downloadAuto(true);


  // Serial.println(stat);

  // for (uint16_t i = memory.startAddr(); i < memory.endAddr() + 1; i++)
  //   Serial.write(EEPROM.read(i));
  // Serial.println();

  //назначаем пины
  pinMode(SOLPIN, OUTPUT);
  pinMode(TRIGPIN, INPUT);
  pinMode(FIREMODESW, INPUT);
  pinMode(TRACER, OUTPUT);
  
  pinMode(PROGSAFE, INPUT);

  if (Settings.isTracer == 1) {
    digitalWrite(TRACER, HIGH);
  }
}