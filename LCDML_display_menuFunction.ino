/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:

// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    //LCDML_UNUSED(param);
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);

    // uncomment this line when the menu should go back to the last called position
    // this could be a cursor position or the an active menu function
    // GBA means => go back advanced
    //LCDML.FUNC_setGBA() 

    //
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button or event status change

    // uncomment this line when the screensaver should not be called when this function is running
    // reset screensaver timer
    //LCDML.SCREEN_resetTimer();

    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
    // this function is always called when the functions ends.
    // this means when you are calling a jumpTo ore a goRoot function
    // that this part is called before a function is closed
  }
}


 * ===================================================================== *
 */

//  ***************************************************
boolean TempSensorSearch(byte* TSaddr)
//  ***************************************************
{
 if ( !ds.search(TSaddr)) {
    lcd.print(F("No more addresses."));
    return false; 
     }  
 if (OneWire::crc8(TSaddr, 7) != TSaddr[7]) {
       lcd.println(F("CRC is not valid!"));
       return false;
       }
 for(byte i = 0; i < 8; i++) {
       Serial.print(TSaddr[i],HEX);
       lcd.print(TSaddr[i],HEX);
     }
       Serial.println();
 return true;
  
}

//  ***************************************************
float TempSensorData(byte* TSaddr)
//  ***************************************************
{
  

 byte data[12];
     // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button or event status change
 ds.reset();
 ds.select(TSaddr);
 ds.write(0xBE);         // Read Scratchpad
  for (byte i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  
  }
  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
         if (cfg == 0x00) raw = raw & ~7; //  9 bit res, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
 if (setting_verbose & B1 << 2){
    for (byte i=0; i<8; i++) { 
           Serial.print(TSaddr[i],HEX);
    }
    Serial.print(" ");
    for (byte i=0; i<12; i++) { 
           Serial.print(data[i],HEX);
    }
    Serial.print(" ");

    Serial.println(raw);
    
 }
  return (float)raw / 16.0;
  
}



// *********************************************************************
void mFunc_TempAddressSetup(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
   // LCDML_UNUSED(param);
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    for(byte i = 0; i < 8; i++) {
       addr[i] = data[param][i];
        lcd.print(addr[i],HEX);
    }
    // uncomment this line when the menu should go back to the last called position
    // this could be a cursor position or the an active menu function
    // GBA means => go back advanced
    //LCDML.FUNC_setGBA() 
    //
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
 float celsius = TempSensorData(addr);
 Serial.print("  Temp = ");
  Serial.print(celsius);
  Serial.println();
 
  lcd.setCursor(0,1);
  lcd.print (F("Temp="));
  lcd.print (celsius);
  lcd.print (F("    "));
    
   
  
    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
       if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
      {
       lcd.setCursor(0, 0);
          lastTSS = TempSensorSearch(addr);
       } 
        if (LCDML.BT_checkQuit())  LCDML.FUNC_goBackToMenu();

        if (LCDML.BT_checkEnter()) {
         if (lastTSS) 
         for (byte i = 0; i < 8 ; i++){
            data[param][i] = addr[i];
          
          }
          eeprom_write_block((void*)&data, 0, sizeof(data));
         LCDML.FUNC_goBackToMenu();
        }
        
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    
    // loop end
    // you can here reset some global vars or delete it
    // this function is always called when the functions ends.
    // this means when you are calling a jumpTo ore a goRoot function
    // that this part is called before a function is closed
  }
}

// *********************************************************************
void mFunc_information(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    // setup function
   lcd.setCursor(10, 0);
   
   lcd.print (rtc.getDateString());

  LCDML.FUNC_setLoopInterval(1000); 
  //   lcd.print (sensor.getTemp());
       lcd.setCursor(0,3);
lcd.print (F("TS1=      TS2=      "));
 if (recipt_step) {
lcd.setCursor(0,1);
lcd.print(F("Brewing... Step:"));
lcd.setCursor(0,2);
lcd.print(F("temp=   timer="));
}
timer_p= (unsigned long) (nextsteptimer - millis() )/1000;
 }
  

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    lcd.setCursor(0, 0);
     lcd.print (rtc.getTimeString());
timer_p--;
 if (recipt_step) {
lcd.setCursor(18,1);
lcd.print(recipt_step);
lcd.setCursor(5,2);
 lcd.print (F("  "));
 lcd.setCursor(5,2);
lcd.print(recipt[recipt_step-1].temp,DEC);
lcd.setCursor(14,2);
 lcd.print (F("      "));
lcd.setCursor(14,2);
lcd.print(timer_p ,DEC );


 }
   float celsius;     
 for (byte n = 0 ; n < 2; n++) {
 celsius = TempSensorData(*(data+n)); 
 byte b =  4 + n*10;
 lcd.setCursor( b,3);
  lcd.print (F("      "));
 lcd.setCursor( b,3);
  lcd.print (celsius);

 
 } 

 
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if(LCDML.BT_checkAny()) { // check if any button is pressed (enter, up, down, left, right)
      // LCDML_goToMenu stops a running menu function and goes to the menu
       if (LCDML.BT_checkLeft() || LCDML.BT_checkUp() && recipt_step) // check if button left is pressed
      {
       next_step(millis());
       } 
     else  LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

void mFunc_Save(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
 
   //  
    eeprom_write_block((void*)&recipt, readblock, _sizeof_recipt);
   mFunc_start(0);
 
//    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds



    }
   

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

void mFunc_start(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
 
   //  
   
     lcd.print(F("Starting....."));
  if (setting_verbose & B1 << 1 ) {
    for (byte n=0; n<8; n++){
     Serial.print(recipt[n].timer,DEC);Serial.print(" ");Serial.print(recipt[n].temp,DEC);Serial.print(" ");Serial.print(recipt[n].stat,DEC);
    Serial.println();
    }
 }  
     next_step(millis());
     LCDML.OTHER_jumpToFunc(mFunc_information);
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    //LCDML.TIMER_msReset(g_timer_1);
    //  LCDML.FUNC_goBackToMenu();
    }
   

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}



// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (global variable)
void mFunc_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
 
   //  
   
     lcd.print(" ");
     
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    //LCDML.TIMER_msReset(g_timer_1);
    //  LCDML.FUNC_goBackToMenu();
    }
   

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


void mFunc_RecipeMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
   // LCDML_UNUSED(param);


   readblock=_sizeof_data+param*_sizeof_recipt;
    eeprom_read_block((void*)&recipt, readblock, _sizeof_recipt);
    recipt_step = 0;
   for (byte n=0; n<8; n++) {
     lcd.setCursor((n & B1) * 10 , n >> 1);
     lcd.print(recipt[n].timer/60,DEC);lcd.print(" ");lcd.print(recipt[n].temp,DEC);lcd.print(" ");lcd.print(recipt[n].stat,HEX);
       }
 
   
    LCDML.OTHER_jumpToFunc(mDyn_ER_Step);

    //LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    //LCDML.TIMER_msReset(g_timer_1);
    //  LCDML.FUNC_goBackToMenu();
    }
   

    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
    
  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

void mFunc_zummer(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    //  
   Zummer_state = B10010010;
    LCDML.FUNC_goBackToMenu();
}
    
    
   

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


void mFunc_relay(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
   Relay_state =  Relay_state ^ B1 << param | B1;
   LCDML.FUNC_goBackToMenu();
}
   
  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

// *********************************************************************
void mFunc_backRecipeMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    
    // Jump to main screen
    LCDML.OTHER_jumpToFunc(mFunc_RecipeMenu);
  }
}
// *********************************************************************
void mFunc_EditRecipe(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    
    // Jump to main screen
   // LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}
