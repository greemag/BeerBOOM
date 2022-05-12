/* ===================================================================== *
 *                                                                       *
 * Dynamic content                                                       *
 *                                                                       *
 * ===================================================================== *
 */
 void mDyn_para(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
        }

      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft())
      {
        recipt[n_step].temp++;
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].temp--;
      }


    
    }
  }

  char buf[20];
  sprintf (buf, "Relays: %d", recipt[n_step].temp);
  // use the line from function parameters
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(buf);

}

 void mDyn_para3(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
        }

      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft())
      {
        recipt[n_step].stat++;
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].stat--;
      }


    
    }
  }

  char buf[20];
  sprintf (buf, "Relays: %d", recipt[n_step].stat);
  // use the line from function parameters
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(buf);

}
 void mDyn_para2(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
        
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
        }

      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft())
      {
        recipt[n_step].timer++;
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].timer--;
      }


    
    }
  }

  char buf[20];
  sprintf (buf, "Timer: %d", recipt[n_step].timer);
  // use the line from function parameters
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(buf);

}
 void mDyn_ER_Temp(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
        }

      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft())
      {
        recipt[n_step].temp++;
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].temp--;
      }


    
    }
  }

  char buf[20];
  sprintf (buf, "Temp: %d", recipt[n_step].temp);
  // use the line from function parameters
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(buf);

}
 void mDyn_ER_Relay1(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
             LCDML.MENU_enScroll();
        }
      }
      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft() or LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].stat = recipt[n_step].stat ^ B1;
      }
   
    }
  }
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(F("Relay1: O"));
  if ( recipt[n_step].stat & B1 )  lcd.print("n");
  else  lcd.print("ff");

}
 void mDyn_ER_Relay2(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
             LCDML.MENU_enScroll();
        }
      }
      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft() or LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].stat = recipt[n_step].stat ^ B10;
      }
   
    }
  }
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(F("Relay2: O"));
  if ( recipt[n_step].stat & B10 )  lcd.print("n");
  else  lcd.print("ff");

}

 void mDyn_ER_Buzzer(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          LCDML.MENU_disScroll();
        }
        else
        {
             LCDML.MENU_enScroll();
        }
      }
      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft() or LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].stat = recipt[n_step].stat ^ B10000;
      }
   
    }
  }
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(F("Buzzer: O"));
  if ( recipt[n_step].stat & B10000 )  lcd.print("n");
  else  lcd.print("ff");

}

 void mDyn_ER_Timer(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
        }

      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft())
      {
        recipt[n_step].timer++;
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        recipt[n_step].timer--;
      }


    
    }
  }

  char buf[20];
  sprintf (buf, "Timer: %d", recipt[n_step].timer);
  // use the line from function parameters
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(buf);

}

 void mDyn_ER_Step(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
       if(LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
        }

      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkUp() or LCDML.BT_checkLeft())
      {
        n_step++;
        if ( n_step == 8 ) n_step = 0;
      }

      // This check have only an effect when MENU_disScroll is set
      if(LCDML.BT_checkDown() or LCDML.BT_checkRight())
      {
        n_step--;
          if ( n_step == 255 ) n_step = 7;

      }


    
    }
  }

  char buf[20];
  sprintf (buf, "Step: %d", n_step);
  // use the line from function parameters
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(buf);

}
 void mDyn_ER_Begin(uint8_t line)
// *********************************************************************
{
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if(LCDML.BT_checkAny())
    {
      if(LCDML.BT_checkEnter())
      {
            LCDML.OTHER_jumpToFunc(mFunc_Save);

     
      }
    
   
    }
  }
  lcd.setCursor(1, (line + _LCDML_DSIP_use_header));
  lcd.print(F("Begin brewing"));
 

}
