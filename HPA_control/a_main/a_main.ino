#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <LittleFS.h>

#define AP_SSID "ZTV"     //логин
#define AP_PASS "12345678"  //пароль от wifi готовой точки доступа

#include <GyverPortal.h>
GyverPortal ui(&LittleFS);

#include <EEManager.h>  // подключаем либу

#define SOLPIN D6      //пин соленоида основного
#define TRIGPIN D5     //пин спускового крючка
#define FIREMODESW D7  //Переключатель режимов огня
//#define analogPin A0   //разъем для замера напряжения на батарее
#define TRACER D8    //Пин для подключения второго соленойда или другой нагрузки, но учитывая ток который сможет потянуть транзистор (можно заменить на D7 - GPIO13)
#define PROGSAFE D2     //Пин программного предохранителя (задействует пин I2C из за чего нельзя ничего повесить будет)

#define AUTOMODE 0  //РЕЖИМ АВТОМАТА
#define SNIPERMODE 1 //РЕЖИМ СНАЙПЕРСКИЙ
#define CQBMODE 2 //CQB РЕЖИМ
#define MACHINEGUNMODE 3  //РЕЖИМ ПУЛЕМЕТА

#define SEMI 1  //одиночка
#define AUTO 2  //очередь

int autoMode = 0;               //режим стрельбы 1-одиночка, 2-очередь
int voltValue = 0;           //Значение с аналогового пина
unsigned long voltTime = 0;  //Время с последней проверки напряжения
bool isResFl; //
float resVoltValue = 0.0;
float procVol = 0.0;
unsigned long lastShot = 0;  //время последнего выстрела
bool isLS;                     //флаг для отсчета времени до сохранения настрела
bool isLSTr;                  //флаг для трассерки
unsigned long tracLastShot = 0; //время последнего выстрела для трассерки
bool isFlagSafe;  //флаг предохранителя
bool isFireMode;  //флаг переключателя режимов огна
bool isTrig;      //флаг спускового крючка
unsigned long deepSleepTime = 0;  //миллисекунд до ухода в сон
bool isBatSafeFlag = false; //флаг для отключения в случае разряда аккумулятора


bool triggerState;
bool safetyState;
bool autoModeState;


struct {                    //структура в которой хранятся настройки
  int shotTime = 25;       //1. время в милисекундах открытия клапана
  int shotWait = 25;       //2. время в милисекундах закрытия клапана
  int convSel = false;          //3. настройка конвертации для нормально замкнутых (1) и нормально открытых контактов (0) для переключателя режимов огня
  int numOfShotsSemi = 5;   //4. Количество выстрелов при одиночном режиме
  int numOfShotsAuto = 55;  //5. Количество выстрелов при автоматическом режиме стрельбы
  int weightBall = 0.28;    //6. Вес шара
  int Mode = 0;            //7. Тип стрельбы
  /*подрежим стрельбы
0-обычный режим, автомат
1-режим снайперский
2-режим CQB
3-режим пулемета
*/
  int delForErr = 1;     //8. Задержка от дребезга
  int timeLastShot = 1;  //9. время после последнего выстрела для сохранения количества совершенных выстрелов в eeprom
  int writeCount = 0;    //15. Кол-во записей в eeprom. Заявлено что eeprom esp поддерживает около 10.000 перезаписей после чего сделать переход к следующей ячейке.
  int shotDelay = 0;  //задержка между выстрелами
  int convTrig = false;  //конвертация спускового крючка, 0 - нормально замкнутый, 1 - нормально разомкнутый
  bool isDoubleShot = false;   //включение двойного выстрела
  bool isConvSafe = false;      //конвертация предохранителя
  bool isTracer = 0;  //включение трассерки
  int tracTime = 1; //секунд до отключения трассерной подсветки
  float voltCorr = 1.0;  //напряжение для рассчета напряжения на аккумуляторе
  float divR1 = 120.0;  //сопротивление R1 на делителе
  float divR2 = 10.0;   //сопротивление R2 на делителе
  int batType = 0;  //тип литиевого аккумулятора, 0-2s, 1-3s
  bool isDeepSleep = false; //переключатель глубокого сна
  int deepSleepMin = 120; //минут до ухода в глубокий сон
  bool isBatSafe = 0; //отключение в случае разряда аккумулятора
  int zap1;
  int zap2;
  int zap3;
  bool zap4;
  bool zap5;
  bool zap6;
  float zap7;
  float zap8;
  float zap9;
} Settings;              //Название структуры к которой обращаемся

struct {                         //структура в которой храним настрел
  unsigned long shotCount = 0;  //кол-во выстрелов
  int writeCount = 0;            //кол-во записей в eeprom
} WR;

struct {
  String WF_SSID = "AP_ZTV";
  String WF_PASS = "12345678";
  bool apply = 1;
} WF;

IPAddress apIP(63, 63, 63, 63);

EEManager mem1(Settings);  // передаём нашу переменную (фактически её адрес)
EEManager mem2(WR);
EEManager mem3(WF);