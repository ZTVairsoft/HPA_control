void build() {
  //здесь 2 цикла в build создаем страничку, а в action отрабатываем нажатия
  //можно сориентироваться смотря на страничку и сопоставляя с кодом в build

  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);
  //GP.THEME(GP_LIGHT);

  GP.UI_MENU("Меню", GP_RED);  // начать меню
  GP.UI_LINK("/", "Домашняя страница");
  GP.UI_LINK("/settings", "Дополнительные настройки");
  GP.UI_LINK("/info", "Информация");
  GP.UI_LINK("/ota_update", "Обновление");

  GP.UI_BODY();

  GP.UPDATE("rof,cof,vol,pr,vo,vc,vd,vi,volcor,btn,cow,sf,sa,na,OV,R1,R2,TrSl,DSSl,DSTr,led1,led2,led3");

  GP.TITLE("ZTV ВВД v.2.0");
  GP.HR();

  if (ui.uri("/")) {

    M_BOX(GP.LABEL("Режим"); GP.SELECT("vi", "Автомат,Снайпер,CQB режим,Режим пулемета", Settings.Mode); GP.BREAK(););

    M_BLOCK_THIN_TAB(
      "Скорострельность",
      GP.LABEL("Время открытия клапана");
      M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwO", "◄"); GP.SLIDER("vo", Settings.shotTime, 10, 100); GP.BUTTON_MINI("frwO", "►");); GP.BREAK();
      GP.LABEL("Время закрытия клапана");
      M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwC", "◄"); GP.SLIDER("vc", Settings.shotWait, 5, 100); GP.BUTTON_MINI("frwC", "►");); GP.BREAK();
      GP.LABEL("Время между выстрелами");
      M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwD", "◄"); GP.SLIDER("vd", Settings.shotDelay, 0, 1000); GP.BUTTON_MINI("frwD", "►");); GP.BREAK();
      GP.LABEL("Выстрелов в минуту: ");
      GP.LABEL_BLOCK("NAN", "rof"); GP.BREAK();
      M_BOX(GP.SWITCH("CvTr", Settings.convTrig); GP.LABEL("инверт. спуск"););
      M_BOX(GP.SWITCH("CvFM", Settings.convSel); GP.LABEL("инверт. переключ. огня"););
      M_BOX(GP.SWITCH("CvSf", Settings.isConvSafe); GP.LABEL("инверт. предохранитель"););
      M_BOX(GP.SWITCH("TWF", Settings.isDoubleShot); GP.LABEL("двойной спуск для CQB"););
      GP.BREAK();
      M_SPOILER(
        "Состояние кнопок",
        M_BOX(GP.LED("led1"); GP.LABEL("предохранитель: "); GP.BREAK(););
        M_BOX(GP.LED("led2"); GP.LABEL("режим огня: "); GP.BREAK(););
        M_BOX(GP.LED("led3"); GP.LABEL("спуск. крючек: "); GP.BREAK(););););

    M_BLOCK_THIN_TAB(
      "Ограничения",
      GP.LABEL("Кол-во выстрелов при отсечке");
      M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwS", "◄"); GP.SLIDER("sf", Settings.numOfShotsSemi, 0, 10); GP.BUTTON_MINI("frwS", "►");); GP.BREAK();
      GP.LABEL("Кол-во выстрелов при авто");
      M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwA", "◄"); GP.SLIDER("sa", Settings.numOfShotsAuto, 0, 100); GP.BUTTON_MINI("frwA", "►");); GP.BREAK();
      GP.LABEL("Минут до сохранения настрела");
      M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwT", "◄"); GP.SLIDER("na", Settings.timeLastShot, 1, 10); GP.BUTTON_MINI("frwT", "►");); GP.BREAK();

      GP.LABEL("Настрел: ");
      GP.LABEL("NAN", "cof"); GP.BREAK();
      GP.LABEL("Кол-во записей: ");
      GP.LABEL("NAN", "cow"); GP.BREAK(););

    M_BLOCK_THIN_TAB(
      "Питание трассерного Hop-up",
      GP.SWITCH("TrSw", Settings.isTracer);
      GP.BREAK();
      GP.LABEL("Сек. до откл. подсветки");
      M_BOX(GP.LABEL(""); GP.SLIDER("TrSl", Settings.tracTime, 1, 5););
      GP.BREAK(););

    M_BLOCK_THIN_TAB(
      "Автоотключение при бездействии",
      GP.SWITCH("DSTr", Settings.isDeepSleep);
      GP.BREAK();
      GP.LABEL("Минут до отключения");
      M_BOX(GP.LABEL(""); GP.SLIDER("DSSl", Settings.deepSleepMin, 1, 300););
      GP.BREAK(););
    // GP.LABEL("коррект. напр.");
    // GP.SPINNER("volcor", Settings.voltCorr);
    // GP.BREAK();
    GP.LABEL("Напряжение: ");
    GP.LABEL("", "vol");
    GP.LABEL("В");
    GP.BREAK();
    GP.LABEL("Процент заряда: ");
    GP.LABEL("NAN", "pr");
    GP.LABEL("%");
    GP.BREAK();
    GP.BREAK();
    GP.BUTTON("btn", "Сохранить настройки");

    M_SPOILER(
      "Сброс",
      GP.BUTTON_MINI("btnS", "Сброс настроек"););

  } else if (ui.uri("/settings")) {
    M_BOX(GP.LABEL("Аккумулятор"); GP.SELECT("bt", "2S-8.4В,3S-12.6В", Settings.batType); GP.BREAK(););
    M_BOX(GP.SWITCH("BS", Settings.isBatSafe); GP.LABEL("отключение при разряде"););
    M_BLOCK_THIN_TAB(
      "Настройка делителя",
      M_BOX(GP.LABEL("R1"); GP.NUMBER_F("R1", "", Settings.divR1););
      M_BOX(GP.LABEL("R2"); GP.NUMBER_F("R2", "", Settings.divR2););
      M_BOX(GP.LABEL("Опорное"); GP.NUMBER_F("OV", "", Settings.voltCorr););

      GP.LABEL("Напряжение: ");
      GP.LABEL("", "vol");
      GP.LABEL("В");
      GP.BREAK();
      GP.LABEL("Процент заряда: ");
      GP.LABEL("NAN", "pr");
      GP.LABEL("%");
      GP.BREAK(););


    GP.TEXT("ssd", "text", WF.WF_SSID);
    GP.BREAK();
    GP.TEXT("pass", "pass", WF.WF_PASS);
    GP.BREAK();
    GP.BUTTON("WFbtn", "Сохранить");
    GP.BREAK();
    GP.BUTTON_MINI("WFRbtn", "Сброс Wi-fi");



  }else if(ui.uri("/info")){
    GP.LABEL("Прошивка v2.1.0");
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Магазин");
    GP.BREAK();
    GP.UI_LINK("https://vk.com/ztv_airsoft","VK магазин");
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Дополнительные материалы");
    GP.BREAK();
    GP.UI_LINK("https://boosty.to/ztv","Boosty");
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Последние прошивки");
    GP.BREAK();
    GP.UI_LINK("https://github.com/ZTVairsoft/HPA_control", "GitHub");
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Последние релизы");
    GP.BREAK();
    GP.UI_LINK("https://github.com/ZTVairsoft/HPA_control/releases", "Релизы BIN");

  }else if (ui.uri("/update")) {
  }

  GP.UI_END();

  GP.BUILD_END();
}

void action() {
  int ROF;
  if (Settings.Mode == 1) {
    ROF = (1000 / (Settings.shotTime + Settings.shotWait + Settings.shotDelay)) * 60;
  } else {
    ROF = (1000 / (Settings.shotTime + Settings.shotWait)) * 60;
  }

  if (ui.click()) {

    if (ui.clickInt("vo", Settings.shotTime)) {
    }

    if (ui.clickInt("vc", Settings.shotWait)) {
    }

    if (ui.clickInt("vd", Settings.shotDelay)) {
    }

    if (ui.clickInt("sf", Settings.numOfShotsSemi)) {
    }

    if (ui.clickInt("sa", Settings.numOfShotsAuto)) {
    }

    if (ui.clickInt("na", Settings.timeLastShot)) {
    }

    if (ui.clickInt("vi", Settings.Mode)) {
    }

    if (ui.clickInt("bt", Settings.batType)) {
    }

    if (ui.clickBool("TrSw", Settings.isTracer)) {
    }

    if (ui.clickBool("DSTr", Settings.isDeepSleep)) {
    }

    if (ui.clickBool("CvTr", Settings.convTrig)) {
    }

    if (ui.clickBool("CvFM", Settings.convSel)) {
    }

    if (ui.clickBool("CvSf", Settings.isConvSafe)) {
    }

    if (ui.clickBool("TWF", Settings.isDoubleShot)) {
    }

    if (ui.clickBool("BS", Settings.isBatSafe)) {
    }

    if (ui.clickInt("TrSl", Settings.tracTime)) {
    }

    if (ui.clickInt("DSSl", Settings.deepSleepMin)) {
    }

    if (ui.clickInt("volcor", Settings.voltCorr)) {
    }

    if (ui.click("btn")) {
      WR.writeCount++;
      mem1.updateNow();  // обновить сейчас
      mem2.updateNow();
      Serial.println("Изменения сохранены");
    }
    if (ui.click("WFbtn")) {
      WR.writeCount++;
      Serial.println(WF.WF_SSID);
      Serial.println(WF.WF_PASS);
      Serial.println(WF.apply);
      WF.apply = 1;
      mem3.updateNow();  // обновить сейчас
      Serial.println("Изменения сохранены");

      ESP.restart();
    }

    if (ui.click("WFRbtn")) {
      WR.writeCount++;
      mem2.updateNow();  // обновить сейчас
      Serial.println("Сброс Wi-Fi");
      mem3.reset();  // Сброс настроек
      ESP.restart();
    }

    if (ui.click("btnS")) {
      mem1.reset();  // Сброс настроек
      Serial.println("Сброс");
      ESP.restart();
    }

    if (ui.click("bkwO")) Settings.shotTime--;
    if (ui.click("bkwC")) Settings.shotWait--;
    if (ui.click("bkwS")) Settings.numOfShotsSemi--;
    if (ui.click("bkwA")) Settings.numOfShotsAuto--;
    if (ui.click("bkwT")) Settings.timeLastShot--;
    if (ui.click("bkwD")) Settings.shotDelay--;

    if (ui.click("frwO")) Settings.shotTime++;
    if (ui.click("frwC")) Settings.shotWait++;
    if (ui.click("frwS")) Settings.numOfShotsSemi++;
    if (ui.click("frwA")) Settings.numOfShotsAuto++;
    if (ui.click("frwT")) Settings.timeLastShot++;
    if (ui.click("frwD")) Settings.shotDelay++;

    if (ui.clickFloat("R1", Settings.divR1)) {}
    if (ui.clickFloat("R2", Settings.divR2)) {}
    if (ui.clickFloat("OV", Settings.voltCorr)) {}

    if (ui.clickString("ssd", WF.WF_SSID)) {}
    if (ui.clickString("pass", WF.WF_PASS)) {}
  }
  if (ui.update()) {

    if (ui.update("rof")) ui.answer(ROF);

    if (ui.update("cof")) ui.answer(WR.shotCount);

    if (ui.update("cow")) ui.answer(WR.writeCount);

    if (ui.update("vol")) ui.answer(resVoltValue, 2);

    if (ui.update("pr")) ui.answer(procVol);

    if (ui.update("vo")) ui.answer(Settings.shotTime);

    if (ui.update("vc")) ui.answer(Settings.shotWait);

    if (ui.update("sf")) ui.answer(Settings.numOfShotsSemi);

    if (ui.update("sa")) ui.answer(Settings.numOfShotsAuto);

    if (ui.update("na")) ui.answer(Settings.timeLastShot);

    if (ui.update("led1")) ui.answer(safetyState);

    if (ui.update("led2")) ui.answer(autoModeState);

    if (ui.update("led3")) ui.answer(triggerState);
  }
}