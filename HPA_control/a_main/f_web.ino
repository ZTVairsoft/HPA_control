void build() {
  //здесь 2 цикла в build создаем страничку, а в action отрабатываем нажатия
  //можно сориентироваться смотря на страничку и сопоставляя с кодом в build

  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);
  //GP.THEME(GP_LIGHT);

  GP.UI_MENU("Меню", GP_RED);  // начать меню
  GP.UI_LINK("/", "Домашняя страница");
  GP.UI_LINK("/settings", "Дополгительные настройки");
  GP.UI_LINK("/info", "Информация");
  GP.UI_LINK("/ota_update", "Обновление");

  GP.UI_BODY();

  GP.UPDATE("rof,cof,vol,pr,vo,vc,vd,vi,volcor,btn,cow,sf,sa,na,OV,R1,R2,TrSl,DSSl,DSTr,led1,led2,led3");

  GP.TITLE("ZTV ВВД v.2.0");
  GP.HR();

  if (ui.uri("/")) {

    M_BOX(GP.LABEL("Режим"); GP.SELECT("vi", "Автомат,Снайпер,CQB режим,Режим пулемета", Settings.Mode2); GP.BREAK(););

    M_BLOCK_THIN_TAB(
      "Скорострельность",
      GP.LABEL("Время открытия клапана");
      M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwO", "◄"); GP.SLIDER("vo", Settings.Shot_time, 10, 100); GP.BUTTON_MINI("frwO", "►");); GP.BREAK();
      GP.LABEL("Время закрытия клапана");
      M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwC", "◄"); GP.SLIDER("vc", Settings.Shot_wait, 5, 100); GP.BUTTON_MINI("frwC", "►");); GP.BREAK();
      GP.LABEL("Время между выстрелами");
      M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwD", "◄"); GP.SLIDER("vd", Settings.Shot_delay, 0, 1000); GP.BUTTON_MINI("frwD", "►");); GP.BREAK();
      GP.LABEL("Выстрелов в минуту: ");
      GP.LABEL_BLOCK("NAN", "rof"); GP.BREAK();
      M_BOX(GP.SWITCH("CvTr", Settings.ConvTrig); GP.LABEL("инверт. спуск"););
      M_BOX(GP.SWITCH("CvFM", Settings.ConvSel); GP.LABEL("инверт. переключ. огня"););
      M_BOX(GP.SWITCH("CvSf", Settings.ConvSafe); GP.LABEL("инверт. предохранитель"););
      M_BOX(GP.SWITCH("TWF", Settings.Double_Shot); GP.LABEL("двойной спуск для CQB"););
      GP.BREAK();
      M_SPOILER(
        "Состояние кнопок",
        M_BOX(GP.LED("led1"); GP.LABEL("предохранитель: "); GP.BREAK(););
        M_BOX(GP.LED("led2"); GP.LABEL("режим огня: "); GP.BREAK(););
        M_BOX(GP.LED("led3"); GP.LABEL("спуск. крючек: "); GP.BREAK(););););

    M_BLOCK_THIN_TAB(
      "Ограничения",
      GP.LABEL("Кол-во выстрелов при отсечке");
      M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwS", "◄"); GP.SLIDER("sf", Settings.NumOfShotsSemi, 0, 10); GP.BUTTON_MINI("frwS", "►");); GP.BREAK();
      GP.LABEL("Кол-во выстрелов при авто");
      M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwA", "◄"); GP.SLIDER("sa", Settings.NumOfShotsAuto, 0, 100); GP.BUTTON_MINI("frwA", "►");); GP.BREAK();
      GP.LABEL("Минут до сохранения настрела");
      M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwT", "◄"); GP.SLIDER("na", Settings.TimeLastShot, 1, 10); GP.BUTTON_MINI("frwT", "►");); GP.BREAK();

      GP.LABEL("Настрел: ");
      GP.LABEL("NAN", "cof"); GP.BREAK();
      GP.LABEL("Кол-во записей: ");
      GP.LABEL("NAN", "cow"); GP.BREAK(););

    M_BLOCK_THIN_TAB(
      "Питание трассерного Hop-up",
      GP.SWITCH("TrSw", Settings.tracer);
      GP.BREAK();
      GP.LABEL("Сек. до откл. подсветки");
      M_BOX(GP.LABEL(""); GP.SLIDER("TrSl", Settings.tracTime, 1, 5););
      GP.BREAK(););

    M_BLOCK_THIN_TAB(
      "Автоотключение при бездействии",
      GP.SWITCH("DSTr", Settings.deepSleep);
      GP.BREAK();
      GP.LABEL("Минут до отключения");
      M_BOX(GP.LABEL(""); GP.SLIDER("DSSl", Settings.deepSleepMin, 1, 300););
      GP.BREAK(););
    // GP.LABEL("коррект. напр.");
    // GP.SPINNER("volcor", Settings.VoltCorr);
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
    M_BOX(GP.SWITCH("BS", Settings.batSafe); GP.LABEL("отключение при разряде"););
    M_BLOCK_THIN_TAB(
      "Настройка делителя",
      M_BOX(GP.LABEL("R1"); GP.NUMBER_F("R1", "", Settings.DIV_R1););
      M_BOX(GP.LABEL("R2"); GP.NUMBER_F("R2", "", Settings.DIV_R2););
      M_BOX(GP.LABEL("Опорное"); GP.NUMBER_F("OV", "", Settings.VoltCorr););

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
  if (Settings.Mode2 == 1) {
    ROF = (1000 / (Settings.Shot_time + Settings.Shot_wait + Settings.Shot_delay)) * 60;
  } else {
    ROF = (1000 / (Settings.Shot_time + Settings.Shot_wait)) * 60;
  }

  if (ui.click()) {

    if (ui.clickInt("vo", Settings.Shot_time)) {
    }

    if (ui.clickInt("vc", Settings.Shot_wait)) {
    }

    if (ui.clickInt("vd", Settings.Shot_delay)) {
    }

    if (ui.clickInt("sf", Settings.NumOfShotsSemi)) {
    }

    if (ui.clickInt("sa", Settings.NumOfShotsAuto)) {
    }

    if (ui.clickInt("na", Settings.TimeLastShot)) {
    }

    if (ui.clickInt("vi", Settings.Mode2)) {
    }

    if (ui.clickInt("bt", Settings.batType)) {
    }

    if (ui.clickBool("TrSw", Settings.tracer)) {
    }

    if (ui.clickBool("DSTr", Settings.deepSleep)) {
    }

    if (ui.clickBool("CvTr", Settings.ConvTrig)) {
    }

    if (ui.clickBool("CvFM", Settings.ConvSel)) {
    }

    if (ui.clickBool("CvSf", Settings.ConvSafe)) {
    }

    if (ui.clickBool("TWF", Settings.Double_Shot)) {
    }

    if (ui.clickBool("BS", Settings.batSafe)) {
    }

    if (ui.clickInt("TrSl", Settings.tracTime)) {
    }

    if (ui.clickInt("DSSl", Settings.deepSleepMin)) {
    }

    if (ui.clickInt("volcor", Settings.VoltCorr)) {
    }

    if (ui.click("btn")) {
      WR.WriteCount++;
      mem1.updateNow();  // обновить сейчас
      mem2.updateNow();
      Serial.println("Изменения сохранены");
    }
    if (ui.click("WFbtn")) {
      WR.WriteCount++;
      Serial.println(WF.WF_SSID);
      Serial.println(WF.WF_PASS);
      Serial.println(WF.apply);
      WF.apply = 1;
      mem3.updateNow();  // обновить сейчас
      Serial.println("Изменения сохранены");

      ESP.restart();
    }

    if (ui.click("WFRbtn")) {
      WR.WriteCount++;
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

    if (ui.click("bkwO")) Settings.Shot_time--;
    if (ui.click("bkwC")) Settings.Shot_wait--;
    if (ui.click("bkwS")) Settings.NumOfShotsSemi--;
    if (ui.click("bkwA")) Settings.NumOfShotsAuto--;
    if (ui.click("bkwT")) Settings.TimeLastShot--;
    if (ui.click("bkwD")) Settings.Shot_delay--;

    if (ui.click("frwO")) Settings.Shot_time++;
    if (ui.click("frwC")) Settings.Shot_wait++;
    if (ui.click("frwS")) Settings.NumOfShotsSemi++;
    if (ui.click("frwA")) Settings.NumOfShotsAuto++;
    if (ui.click("frwT")) Settings.TimeLastShot++;
    if (ui.click("frwD")) Settings.Shot_delay++;

    if (ui.clickFloat("R1", Settings.DIV_R1)) {}
    if (ui.clickFloat("R2", Settings.DIV_R2)) {}
    if (ui.clickFloat("OV", Settings.VoltCorr)) {}

    if (ui.clickString("ssd", WF.WF_SSID)) {}
    if (ui.clickString("pass", WF.WF_PASS)) {}
  }
  if (ui.update()) {

    if (ui.update("rof")) ui.answer(ROF);

    if (ui.update("cof")) ui.answer(WR.ShotCount1);

    if (ui.update("cow")) ui.answer(WR.WriteCount);

    if (ui.update("vol")) ui.answer(ResVoltValue, 2);

    if (ui.update("pr")) ui.answer(ProcVol);

    if (ui.update("vo")) ui.answer(Settings.Shot_time);

    if (ui.update("vc")) ui.answer(Settings.Shot_wait);

    if (ui.update("sf")) ui.answer(Settings.NumOfShotsSemi);

    if (ui.update("sa")) ui.answer(Settings.NumOfShotsAuto);

    if (ui.update("na")) ui.answer(Settings.TimeLastShot);

    if (ui.update("led1")) ui.answer(safetyState);

    if (ui.update("led2")) ui.answer(autoModeState);

    if (ui.update("led3")) ui.answer(triggerState);
  }
}