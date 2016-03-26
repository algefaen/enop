/*********************************************************************
 *
 * $Id: YLed.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle Led functions
 *
 * - - - - - - - - - License information: - - - - - - - - - 
 *
 *  Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 *  Yoctopuce Sarl (hereafter Licensor) grants to you a perpetual
 *  non-exclusive license to use, modify, copy and integrate this
 *  file into your software for the sole purpose of interfacing
 *  with Yoctopuce products.
 *
 *  You may reproduce and distribute copies of this file in
 *  source or object form, as long as the sole purpose of this
 *  code is to interface with Yoctopuce products. You must retain
 *  this notice in the distributed source file.
 *
 *  You should refer to Yoctopuce General Terms and Conditions
 *  for additional information regarding your rights and
 *  obligations.
 *
 *  THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *  WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING 
 *  WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *  EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *  INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 *  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR 
 *  SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 *  LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *  CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *  BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *  WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/


#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "cmdline_common.h"
#include "yocto_api.h"
#include "yocto_led.h"

using namespace std;

//--- (YLed definitions)

const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

const char *enumBlink[] = {
    "STILL",
    "RELAX",
    "AWARE",
    "RUN",
    "CALL",
    "PANIC",
    NULL
};

//--- (end of YLed definitions)

bool   isModule(void)      { return false; }

//--- (YLed implementation)
string YFunctionName(void) { return "Led"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of power is int (OnOff)
// type of luminosity is int (Percent)
// type of blinking is int (Blink)
/**
 * Returns the logical name of the led.
 *
 * @return a string corresponding to the logical name of the led
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Led_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the led.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_logicalName();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the logical name of the led. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the led
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Led_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the led.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the led", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    if (!YAPI::CheckLogicalName((*args)[0]->get_stringValue())) {
        throw std::string("Invalid name :" + (*args)[0]->get_stringValue());
    }
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_logicalName(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a short string representing the current state of the led.
 *
 * @return a string corresponding to a short string representing the current state of the led
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Led_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the led.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_advertisedValue();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current led state.
 *
 * @return either Y_POWER_OFF or Y_POWER_ON, according to the current led state
 *
 * On failure, throws an exception or returns Y_POWER_INVALID.
 */
class Led_get_power : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_power";
  }

  string getDescription()
  {
    return "Returns the current led state.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_power();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the state of the led.
 *
 * @param newval : either Y_POWER_OFF or Y_POWER_ON, according to the state of the led
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Led_set_power : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_power";
  }

  string getDescription()
  {
    return "Changes the state of the led.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON, according to the state of the led", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_power(Y_POWER_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the current led intensity (in per cent).
 *
 * @return an integer corresponding to the current led intensity (in per cent)
 *
 * On failure, throws an exception or returns Y_LUMINOSITY_INVALID.
 */
class Led_get_luminosity : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_luminosity";
  }

  string getDescription()
  {
    return "Returns the current led intensity (in per cent).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_luminosity();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current led intensity (in per cent).
 *
 * @param newval : an integer corresponding to the current led intensity (in per cent)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Led_set_luminosity : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_luminosity";
  }

  string getDescription()
  {
    return "Changes the current led intensity (in per cent).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the current led intensity (in per cent)", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_luminosity(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the current led signaling mode.
 *
 * @return a value among Y_BLINKING_STILL, Y_BLINKING_RELAX, Y_BLINKING_AWARE, Y_BLINKING_RUN,
 * Y_BLINKING_CALL and Y_BLINKING_PANIC corresponding to the current led signaling mode
 *
 * On failure, throws an exception or returns Y_BLINKING_INVALID.
 */
class Led_get_blinking : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_blinking";
  }

  string getDescription()
  {
    return "Returns the current led signaling mode.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_blinking();
        string strval =  enumString(attrval,enumBlink);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current led signaling mode.
 *
 * @param newval : a value among Y_BLINKING_STILL, Y_BLINKING_RELAX, Y_BLINKING_AWARE, Y_BLINKING_RUN,
 * Y_BLINKING_CALL and Y_BLINKING_PANIC corresponding to the current led signaling mode
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Led_set_blinking : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_blinking";
  }

  string getDescription()
  {
    return "Changes the current led signaling mode.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among STILL, RELAX, AWARE, RUN, CALL and PANIC corresponding to the current led signaling mode", "STILL=0,RELAX=1,AWARE=2,RUN=3,CALL=4,PANIC=5", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YLed*>* list = enumerateTargets<YLed>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_blinking(Y_BLINKING_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackLed is YLedValueCallback* (YLedValueCallback)
//--- (end of YLed implementation)

//--- (Led functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YLed>(cmdList);
    cmdList->push_back((YapiCommand*) (new Led_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new Led_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new Led_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new Led_get_power()));
    cmdList->push_back((YapiCommand*) (new Led_set_power()));
    cmdList->push_back((YapiCommand*) (new Led_get_luminosity()));
    cmdList->push_back((YapiCommand*) (new Led_set_luminosity()));
    cmdList->push_back((YapiCommand*) (new Led_get_blinking()));
    cmdList->push_back((YapiCommand*) (new Led_set_blinking()));
  }

//--- (end of Led functions)
