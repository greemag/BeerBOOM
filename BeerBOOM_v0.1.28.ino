// ============================================================
// Example:     LCDML_serialmonitor
// ============================================================
// Description:
// This example includes the complete functionality over some
// tabs. All Tabs which are started with "LCDML_display_.."
// generates an output on the display / console / ....
// This example is for the author to test the complete functionality
// ============================================================
// *********************************************************************
// special settings
// *********************************************************************
// enable this line when you are not usigng a standard arduino
// for example when your chip is an ESP or a STM or SAM or something else

//#define _LCDML_cfg_use_ram 
  #define _BB_version   " 0.1.28"
// 0.1.26 обновление меню , редактирование рецептов.
// 0.1.27 
// 0.1.28 изменение пинов управления реле и симистровов

// 0.2. запись рецептов, текущего времени через Serial

  #define DS_PIN 17
  #define Z_PIN 13
  #define RELAY1_PIN 14
  #define RELAY2_PIN 15
  #define SIMISTR1_PIN 6
  #define SIMISTR2_PIN 5
  
// *********************************************************************
// includes
// *********************************************************************
  #include <LiquidCrystal.h>
  #include <microDS3231.h>
  #include <LCDMenuLib2.h>
  #include <avr/eeprom.h>
  #include <OneWire.h>
  #include <GyverRelay.h>

// *********************************************************************
// LCDML display settings
// *********************************************************************
  // settings for LCD
  #define _LCDML_DISP_cols  20
  #define _LCDML_DISP_rows  4
  
  // enable this line (set to 1) to show a header above the first menu element
  // this function can be changed in LCDML_display_menu tab
  #define _LCDML_DSIP_use_header 1

  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
 // #define _LCDML_DISP_cfg_scrollbar                  0     // enable a scrollbar
  #define _sizeof_data 32 
  #define _sizeof_recipt 32 
     
  // LCD object
  LiquidCrystal lcd (7,8,9,10,11,12);
  MicroDS3231 rtc;
  OneWire  ds(DS_PIN);
  uint8_t data[4][8];  
  struct recipt_t {
  int16_t timer ;
  int8_t temp ;   
  int8_t stat ;  
    };
//  recipt_t* recipt = {1800,90,0};//,{1500,90,3},{600,90,3},{900,90,3}};

   recipt_t recipt[8];
  //int8_t last_temp = 0;   
  boolean lastresult;
   boolean newresult;
  byte recipt_step = 0;
  byte n_step=0;
  byte readblock;
  byte addr[8];
  byte an;
  unsigned long previousMillis = 0;
  unsigned long nextsteptimer = 0;
  float temp1;
  const long interval = 1000;
  boolean lastTSS;
  uint8_t Zummer_state = 0;
  const long Zummer_interval = 500;
  unsigned long Zummer_previousMillis = 0;
  uint8_t Relay_state = 0;
  boolean change_simistr;
  boolean saveyn;
  byte setting_verbose = B1111;
  unsigned long simistr_previousMillis = 0;
  int timer_p;
// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

// *********************************************************************
// Global variables
// *********************************************************************


// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows-_LCDML_DSIP_use_header, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);
GyverRelay regulator(REVERSE);

 LCDML_add (0 , LCDML_0 , 1 , "Settings" , NULL); 
 LCDML_add (1 , LCDML_0_1 , 1 , "Info" , mFunc_information);
 
 LCDML_add (2 , LCDML_0_1 , 2 , "Data&Time" , mFunc_timer_info); 
 
 LCDML_add (3 , LCDML_0_1 , 3 , "Check relay" , NULL); 
 LCDML_addAdvanced (4 , LCDML_0_1_3 , 1 , NULL, "RELAY1"   , mFunc_relay, 1 , _LCDML_TYPE_default); 
 LCDML_addAdvanced (5 , LCDML_0_1_3 , 2 , NULL, "RELAY2"   , mFunc_relay, 2 , _LCDML_TYPE_default); 
 LCDML_addAdvanced (6 , LCDML_0_1_3 , 3 , NULL, "SIMISTR1" , mFunc_relay, 3 , _LCDML_TYPE_default); 
 LCDML_addAdvanced (7 , LCDML_0_1_3 , 4 , NULL, "SIMISTR2" , mFunc_relay, 4 , _LCDML_TYPE_default); 
 LCDML_add (8 , LCDML_0_1_3 , 5 , "BUZZER" , mFunc_zummer); 
 LCDML_add (9 , LCDML_0_1_3 , 6 , "Back" , mFunc_back);
 LCDML_add (10, LCDML_0_1 , 4 , "TempSensor1" , NULL); 
 LCDML_addAdvanced (11 , LCDML_0_1_4 , 1 , NULL, "Address" , mFunc_TempAddressSetup, 0, _LCDML_TYPE_default);  
 LCDML_add (12 , LCDML_0_1_4 , 2 , "Maximal" , NULL); 
 LCDML_add (13 , LCDML_0_1_4 , 3 , "Gisteresis" , NULL); 
 LCDML_add (14 , LCDML_0_1_4 , 4 , "Back" , mFunc_back);
 
 LCDML_add (15 , LCDML_0_1 , 5 , "TempSensor2" , NULL); 
 LCDML_addAdvanced (16 , LCDML_0_1_5 , 1 , NULL, "Address" , mFunc_TempAddressSetup, 1, _LCDML_TYPE_default); 
 LCDML_add (17 , LCDML_0_1_5 , 2 , "Maximal" , NULL); 
 LCDML_add (18 , LCDML_0_1_5 , 3 , "Back" , mFunc_back);
 
 LCDML_add (19 , LCDML_0_1 , 6 , "TempSensor3" , NULL); 
 LCDML_addAdvanced (20 , LCDML_0_1_6 , 1 , NULL, "Address" , mFunc_TempAddressSetup, 2, _LCDML_TYPE_default);  
 LCDML_add (21 , LCDML_0_1_6 , 2 , "Maximal" , NULL); 
 LCDML_add (22 , LCDML_0_1_6 , 3 , "Back" , mFunc_back); 

 LCDML_add (23 , LCDML_0_1 , 7 , "Encoder" , NULL); 
 LCDML_add (24 , LCDML_0_1_7 , 1 , "FastTimer" , NULL); 
 LCDML_add (25 , LCDML_0_1_7 , 2 , "setDirection" , NULL); 
 LCDML_add (26 , LCDML_0_1_7 , 3 , "Back" , mFunc_back); 

 LCDML_add (27 , LCDML_0_1 , 8 ,"Back" , mFunc_back);
 LCDML_add (28 , LCDML_0 , 2 , "Brewing" , NULL);
 LCDML_addAdvanced (29 , LCDML_0_2 , 1 , NULL, "Recipe 1" , mFunc_RecipeMenu, 0, _LCDML_TYPE_default);  
 LCDML_addAdvanced (30 , LCDML_0_2 , 2 , NULL, "Recipe 2" , mFunc_RecipeMenu, 1, _LCDML_TYPE_default);  
 LCDML_addAdvanced (31 , LCDML_0_2 , 3 , NULL, "Recipe 3" , mFunc_RecipeMenu, 2, _LCDML_TYPE_default);  
 LCDML_addAdvanced (32 , LCDML_0_2 , 4 , NULL, "Recipe 4" , mFunc_RecipeMenu, 3, _LCDML_TYPE_default);  
 LCDML_addAdvanced (33 , LCDML_0_2 , 5 , NULL, "Recipe 5" , mFunc_RecipeMenu, 4, _LCDML_TYPE_default);  
 LCDML_addAdvanced (34 , LCDML_0_2 , 6 , NULL, "Recipe 6" , mFunc_RecipeMenu, 5, _LCDML_TYPE_default);  
 LCDML_addAdvanced (35 , LCDML_0_2 , 7 , NULL, "Recipe 7" , mFunc_RecipeMenu, 6, _LCDML_TYPE_default);  
 LCDML_addAdvanced (36 , LCDML_0_2 , 8 , NULL, "Recipe 8" , mFunc_RecipeMenu, 7, _LCDML_TYPE_default);  
 LCDML_add (37 , LCDML_0_2 , 9 , "Back" , mFunc_back);
 LCDML_addAdvanced (38 , LCDML_0_2  , 10  , COND_hide,  "Edit recipe"   , NULL,   0,   _LCDML_TYPE_default); 
 LCDML_addAdvanced (39 , LCDML_0_2_10 , 1 , NULL, "Steps" , mDyn_ER_Step, 0, _LCDML_TYPE_dynParam); 
 LCDML_addAdvanced (40 , LCDML_0_2_10 , 2 , NULL, "Timer" , mDyn_ER_Timer, 0, _LCDML_TYPE_dynParam);  
 LCDML_addAdvanced (41 , LCDML_0_2_10 , 3 , NULL, "Temp"  , mDyn_ER_Temp, 0, _LCDML_TYPE_dynParam);  
 LCDML_addAdvanced (42 , LCDML_0_2_10 , 4 , NULL, "Relay 1:" , mDyn_ER_Relay1, 0, _LCDML_TYPE_dynParam);  
 LCDML_addAdvanced (43 , LCDML_0_2_10 , 5 , NULL, "Relay 2:" , mDyn_ER_Relay2, 0, _LCDML_TYPE_dynParam);  
 LCDML_addAdvanced (44 , LCDML_0_2_10 , 6 , NULL, "Buzzer:" , mDyn_ER_Buzzer, 0, _LCDML_TYPE_dynParam);  
 LCDML_addAdvanced (45 , LCDML_0_2_10 , 7 , NULL, "Update recipe" , mDyn_ER_Begin, 0, _LCDML_TYPE_dynParam);  
 //LCDML_add (45 , LCDML_0_2_10, 8 , "Begin" , mFunc_start); 
 LCDML_add (46 , LCDML_0_2_10_7, 1 , "Yes" , mFunc_Save); 
 LCDML_add (47 , LCDML_0_2_10_7, 2 , "No" , mFunc_start); 
 LCDML_add (48 , LCDML_0_2_10, 8 , "Back" , mFunc_back); 
 LCDML_add (49 , LCDML_0 , 3 , "ManualSet" , NULL);
 LCDML_addAdvanced (50 , LCDML_0_3 , 1 , NULL, "Relays" , mDyn_para, 2, _LCDML_TYPE_dynParam);  
 LCDML_addAdvanced (51 , LCDML_0_3 , 2 , NULL, "Timer" , mDyn_para2, 2, _LCDML_TYPE_dynParam);  
 LCDML_addAdvanced (52 , LCDML_0_3 , 3 , NULL, "Temp" , mDyn_para3, 2, _LCDML_TYPE_dynParam);  
 LCDML_add (53 , LCDML_0_3, 4 , "Begin" , mFunc_start); 
 LCDML_add (54 , LCDML_0_3, 5 , "Back" , mFunc_back); 
 
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    54

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // serial init; only be needed if serial control is used
    Serial.begin(9600);                // start serial
    Serial.println(F(_BB_version)); // only for examples
    eeprom_read_block((void*)&data, 0, _sizeof_data);
    eeprom_read_block((void*)&recipt, _sizeof_data + 0*_sizeof_recipt , _sizeof_recipt);

 if (setting_verbose & B1 << 1 ) {
    for (byte n=0; n<4; n++){
    for (byte i=0; i<8; i++) { 
           Serial.print(data[n][i],HEX);
    }
    Serial.println();
    }
    for (byte n=0; n<8; n++){
     Serial.print(recipt[n].timer,DEC);Serial.print(" ");Serial.print(recipt[n].temp,DEC);Serial.print(" ");Serial.print(recipt[n].stat,DEC);
    Serial.println();
    }
 }      
 //   eeprom_write_block((void*)&data, 0, sizeof(data));
    // LCD Begin
    lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);
  
    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    //LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
    LCDML.SCREEN_disable();

    // Some needful methods

    // You can jump to a menu function from anywhere with
 //   ds.reset_search();
//    LCDML.OTHER_jumpToFunc(mFunc_information); // the parameter is the function name

 digitalWrite(RELAY1_PIN  ,HIGH);
    digitalWrite(RELAY2_PIN  ,HIGH);
    digitalWrite(SIMISTR1_PIN,HIGH);
    digitalWrite(SIMISTR2_PIN,HIGH);
    digitalWrite(Z_PIN,LOW);
pinMode(RELAY1_PIN,OUTPUT);
pinMode(RELAY2_PIN,OUTPUT); 
pinMode(SIMISTR1_PIN,OUTPUT);
pinMode(SIMISTR2_PIN,OUTPUT);
pinMode(Z_PIN,OUTPUT);

  Relay_state=B11111;

  }


// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    LCDML.loop();
    
  unsigned long currentMillis =   millis();


   if ( lastresult ^ newresult || change_simistr) {
    if (currentMillis - simistr_previousMillis >= 100) {
      simistr_previousMillis = currentMillis;
  if ( setting_verbose & B1 << 5) {
        Serial.print(F("INRElayState:"));
        Serial.println(Relay_state,BIN); 
        Serial.print(F("INChangeSIMISTR:"));
        Serial.println(change_simistr);
     //   Serial.print(F 
     }        
       lastresult = newresult;
          
       if (newresult) {
          
              if (change_simistr) {
               switch (Relay_state){
                 case  B11100 :  change_simistr = false; break;
                 case  B10100 : Relay_state =  B11101; break;
                 case  B10110 : Relay_state =  B10101; break;
 
                } }else {
                  change_simistr = true;
                  Relay_state =  B10111; 
                }

          } else  
          {
              if (change_simistr) {
               switch  (Relay_state){
               case B11110:  change_simistr = false; break;
               case B10110:  Relay_state =  B11111; break;
               case B10100:  Relay_state =  B10111; break;}
              } else {
                change_simistr = true;
                Relay_state=B10101;
             }
          }
         if ( setting_verbose & B1 << 5) {
        Serial.print(F("ExitRElayState:"));
        Serial.println(Relay_state,BIN); 
        Serial.print(F("ChangeSIMISTR:"));
        Serial.println(change_simistr);
     //   Serial.print(F("change status"));
         }    
   }
   }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    temp1 = TempSensorData(*(data));
 
    ds.reset();
    ds.skip();  
    ds.write(0x44);
  }
  
  if (Relay_state & B1) {
 
    digitalWrite(RELAY1_PIN  ,Relay_state & B1 << 1);
    digitalWrite(RELAY2_PIN  ,Relay_state & B1 << 2);
    digitalWrite(SIMISTR1_PIN,Relay_state & B1 << 3);
    digitalWrite(SIMISTR2_PIN,Relay_state & B1 << 4);
      Relay_state = Relay_state & ~B1;  
    if ( setting_verbose & B1 << 1) {
 
    Serial.print(F("stat_relay :"));
    Serial.println(Relay_state,BIN);
    
   }   
  }
  if (Zummer_state) {
  if (currentMillis - Zummer_previousMillis >= Zummer_interval) {
    Zummer_previousMillis = currentMillis;
    Zummer_state=Zummer_state >> 1;
    digitalWrite(Z_PIN,Zummer_state & B1 );
    }
  }

//       if (Serial.available() > 0) {
//    // get incoming byte:
//   
//    recipt.timer = currentMillis;
//    
//    recipt.stat = Serial.parseInt();
//    recipt.temp = TempSensorData(*(data));
//    eeprom_write_block((void*)&recipt, _sizeof_data + recipt_step * _sizeof_recipt, _sizeof_recipt);
//    recipt_step++;
//
//       }
 


// NEXT STEP
if (recipt_step) {
  if (currentMillis == previousMillis) {
        regulator.input = temp1;
        newresult = regulator.getResult();
  
  if ( setting_verbose & B1 << 4) {
    Serial.print(F("temp1 :"));
    Serial.println(temp1);
    Serial.print(F("setpoint :"));
    Serial.println(regulator.setpoint);
    Serial.print(F("regulator 1 :"));
    Serial.println(newresult);
  }     
}
    if (nextsteptimer) {
    // BY TIMER
    if (currentMillis > nextsteptimer)  next_step(currentMillis);
    }
    else {
      // BY TEMP

    if ( (int)temp1 == recipt[recipt_step].temp)  next_step(currentMillis);
      
      }

    }
   
// END NEXT


    
  }


  void next_step(unsigned long cM) {
   if (recipt[recipt_step].timer) nextsteptimer = (unsigned long)recipt[recipt_step].timer * 1000 + cM; else nextsteptimer = 0;
   timer_p = recipt[recipt_step].timer;
  if ( setting_verbose & B1 << 1) {
    Serial.print(F("now  :"));
    Serial.println(cM);
    Serial.print(F("step :"));
    Serial.println(recipt_step,DEC);
    Serial.print(F("timer:"));
    Serial.println(recipt[recipt_step].timer,DEC);
    Serial.print(F("next :"));
    Serial.println(nextsteptimer);
    Serial.print(F("temp :"));
    Serial.println(recipt[recipt_step].temp);
    Serial.print(F("stat :"));
    Serial.println(recipt[recipt_step].stat,BIN);
    
   }   
   if ( nextsteptimer && cM > nextsteptimer) {
        Serial.println(F("ERRROR"));
        lcd.print(F("ERRROR"));
        nextsteptimer = 0;
        recipt_step = 0;
   }  else {
      
    if ( recipt[recipt_step-1].stat & B1 << 3 && recipt_step)     Zummer_state = B10010010;
     
  regulator.setpoint = recipt[recipt_step].temp;    // установка (ставим на 40 градусов)
  regulator.hysteresis = 3;   // ширина гистерезиса
  regulator.k = 0.7;          // коэффициент обратной связи (подбирается по факту)
  recipt_step++;
   }
 }
