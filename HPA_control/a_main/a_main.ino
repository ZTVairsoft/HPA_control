#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <Arduino.h>
#include <LittleFS.h>

#define AP_SSID "ZTV"     //логин
#define AP_PASS "12345678"  //пароль от wifi к которой будем подключаться

#include <GyverPortal.h>
GyverPortal ui(&LittleFS);
//GyverPortal ui;

#include <EEManager.h>  // подключаем либу

#define solPin D6      //пин соленоида основного
#define TrigPin D5     //пин спускового крючка
#define FireModeSw D7  //Переключатель режимов огня
//#define analogPin A0   //разъем для замера напряжения на батарее
#define ExtraPin D8    //Пин для подключения второго соленойда или другой нагрузки, но учитывая ток который сможет потянуть транзистор (можно заменить на D7 - GPIO13)
#define ProgSafe D2     //Пин программного предохранителя (задействует пин I2C из за чего нельзя ничего повесить будет)

int Mode1 = 0;               //режим стрельбы 1-одиночка, 2-очередь
int VoltValue = 0;           //Значение с аналогового пина
unsigned long VoltTime = 0;  //Время с последней проверки напряжения
//float Napr = 0;
bool ResFl;
float ResVoltValue = 0.0;
float ProcVol = 0.0;
unsigned long LastShot = 0;  //время последнего выстрела
bool LS;                     //флаг для отсчета времени до сохранения настрела
bool LSTr;                  //флаг для трассерки
unsigned long TracLastShot = 0; //время последнего выстрела для трассерки
bool FlagSafe;  //флаг предохранителя
bool firemode;  //флаг переключателя режимов огна
bool trig;      //флаг спускового крючка
unsigned long deepSleepTime = 0;  //миллисекунд до ухода в сон


bool triggerState;
bool safetyState;
bool autoModeState;


struct {                    //структура в которой хранятся настройки
  int Shot_time = 25;       //1. время в милисекундах открытия клапана
  int Shot_wait = 25;       //2. время в милисекундах закрытия клапана
  int ConvSel = false;          //3. настройка конвертации для нормально замкнутых (1) и нормально открытых контактов (0) для переключателя режимов огня
  int NumOfShotsSemi = 5;   //4. Количество выстрелов при одиночном режиме
  int NumOfShotsAuto = 55;  //5. Количество выстрелов при автоматическом режиме стрельбы
  int WeightBall = 0.28;    //6. Вес шара
  int Mode2 = 0;            //7. Тип стрельбы
  /*подрежим стрельбы
0-обычный режим, автомат
1-режим снайперский
2-режим CQB
3-режим пулемета
*/
  int DelForErr = 1;     //8. Задержка от дребезга
  int TimeLastShot = 1;  //9. время после последнего выстрела для сохранения количества совершенных выстрелов в eeprom
  int WriteCount = 0;    //15. Кол-во записей в eeprom. Заявлено что eeprom esp поддерживает около 10.000 перезаписей после чего сделать переход к следующей ячейке.
  int Shot_delay = 0;  //задержка между выстрелами
  int ConvTrig = false;  //конвертация спускового крючка, 0 - нормально замкнутый, 1 - нормально разомкнутый
  bool Double_Shot = false;   //включение двойного выстрела
  bool ConvSafe = false;      //конвертация предохранителя
  bool tracer = 0;  //включение трассерки
  int tracTime = 1; //секунд до отключения трассерной подсветки
  float VoltCorr = 1.0;  //напряжение для рассчета напряжения на аккумуляторе
  float DIV_R1 = 100.0;  //сопротивление R1 на делителе
  float DIV_R2 = 10.0;   //сопротивление R2 на делителе
  int batType = 2;  //количество банок в аккумуляторе
  bool deepSleep = false; //переключатель глубокого сна
  int deepSleepMin = 120; //минут до ухода в глубокий сон
} Settings;              //Название структуры к которой обращаемся

struct {                         //структура в которой храним настрел
  unsigned long ShotCount1 = 0;  //кол-во выстрелов
  int WriteCount = 0;            //кол-во записей в eeprom
} WR;

struct {
  String WF_SSID = "AP_ZTV";
  String WF_PASS = "12345678";
  bool apply = 1;
} WF;

IPAddress apIP(63, 63, 63, 63);

EEManager mem1(Settings);  // передаём нашу переменную (фактически её адрес)
EEManager mem2(WR);
EEManager mem3(WF)