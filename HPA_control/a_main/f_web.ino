void build() {
//здесь 2 цикла в build создаем страничку, а в action отрабатываем нажатия
//можно сориентироваться смотря на страничку и сопоставляя с кодом в build

  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);
  //GP.THEME(GP_LIGHT);

  GP.UI_MENU("Меню", GP_RED);   // начать меню
  GP.UI_LINK("/", "Домашняя страница");
  GP.UI_LINK("/settings", "Настройки");
  GP.UI_LINK("/ota_update", "Обновление");

  GP.UI_BODY();

  GP.UPDATE("rof,cof,vol,pr,vo,vc,vi,volcor,btn,cow,sf,sa,na,OV,R1,R2");

  GP.TITLE("ZTV2 v.2.0");
  GP.HR();

if (ui.uri("/")) {

  M_BOX(GP.LABEL("Mode"); GP.SELECT("vi", "Стандартный,Стандартный с отсечкой на авто,Стандартный с отсечкой и авто,CQB режим,Режим пулемета", Settings.Mode2); GP.BREAK(););

  M_BLOCK_THIN_TAB(
    "Скорострельность",
    GP.LABEL("Время открытия клапана");
    M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwO", "◄"); GP.SLIDER("vo", Settings.Shot_time, 10, 100); GP.BUTTON_MINI("frwO", "►");); GP.BREAK();
    GP.LABEL("Время закрытия клапана");
    M_BOX(GP.LABEL("мс"); GP.BUTTON_MINI("bkwC", "◄"); GP.SLIDER("vc", Settings.Shot_wait, 10, 100); GP.BUTTON_MINI("frwC", "►");); GP.BREAK();
    GP.LABEL("Выстрелов в минуту: ");
    GP.LABEL_BLOCK("NAN", "rof"); GP.BREAK();

  );

  M_BLOCK_THIN_TAB(
    "Ограничения",
    GP.LABEL("Кол-во выстрелов при отсечке");
    M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwS", "◄"); GP.SLIDER("sf", Settings.NumOfShotsSemi, 1, 10); GP.BUTTON_MINI("frwS", "►");); GP.BREAK();
    GP.LABEL("Кол-во выстрелов при авто");
    M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwA", "◄"); GP.SLIDER("sa", Settings.NumOfShotsAuto, 1, 100); GP.BUTTON_MINI("frwA", "►");); GP.BREAK();
    GP.LABEL("Минут до сохранения настрела");
    M_BOX(GP.LABEL(""); GP.BUTTON_MINI("bkwT", "◄"); GP.SLIDER("na", Settings.TimeLastShot, 1, 100); GP.BUTTON_MINI("frwT", "►");); GP.BREAK();

    GP.LABEL("Настрел: ");
    GP.LABEL("NAN", "cof"); GP.BREAK();
    GP.LABEL("Кол-во записей: ");
    GP.LABEL("NAN", "cow"); GP.BREAK();
  );
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
    GP.BUTTON_MINI("btnS", "Сброс настроек");
  );
}else if (ui.uri("/settings")) {
    M_BLOCK_TAB(
    "Настройка делителя",
    M_BOX(GP.LABEL("R1");    GP.NUMBER_F("R1", "", Settings.DIV_R1);  );
    M_BOX(GP.LABEL("R2");    GP.NUMBER_F("R2", "", Settings.DIV_R2);  );
    M_BOX(GP.LABEL("Опорное");    GP.NUMBER_F("OV", "", Settings.VoltCorr);  );

      GP.LABEL("Напряжение: ");
  GP.LABEL("", "vol");
  GP.LABEL("В");
  GP.BREAK();
  GP.LABEL("Процент заряда: ");
  GP.LABEL("NAN", "pr");
  GP.LABEL("%");
  GP.BREAK();
  );

}else if (ui.uri("/update")) {

}

GP.UI_END();

  GP.BUILD_END();
}

void action() {
  int ROF = (1000 / (Settings.Shot_time + Settings.Shot_wait)) * 60;
  if (ui.click()) {

    if (ui.clickInt("vo", Settings.Shot_time)) {
    }

    if (ui.clickInt("vc", Settings.Shot_wait)) {
    }

    if (ui.clickInt("sf", Settings.NumOfShotsSemi)) {
    }

    if (ui.clickInt("sa", Settings.NumOfShotsAuto)) {
    }

    if (ui.clickInt("na", Settings.TimeLastShot)) {
    }

    if (ui.clickInt("vi", Settings.Mode2)) {
    }

    if (ui.clickInt("volcor", Settings.VoltCorr)) {
    }

    if (ui.click("btn")) {
      WR.WriteCount++;
      mem1.updateNow();  // обновить сейчас
      mem2.updateNow();
      Serial.println("Изменения сохранены");
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
    if (ui.click("frwO")) Settings.Shot_time++;
    if (ui.click("frwC")) Settings.Shot_wait++;
    if (ui.click("frwS")) Settings.NumOfShotsSemi++;
    if (ui.click("frwA")) Settings.NumOfShotsAuto++;
    if (ui.click("frwT")) Settings.TimeLastShot++;

    if (ui.clickFloat("R1", Settings.DIV_R1)) {}
    if (ui.clickFloat("R2", Settings.DIV_R2)) {}
    if (ui.clickFloat("OV", Settings.VoltCorr)) {}

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

  }
}