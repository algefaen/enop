/*********************************************************************
 *
 * $Id: YPwmPowerSource.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle PwmPowerSource functions
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
#include "yocto_pwmpowersource.h"

using namespace std;

//--- (YPwmPowerSource definitions)

const char *enumPwmPwrMode[] = {
    "USB_5V",
    "USB_3V",
    "EXT_V",
    "OPNDRN",
    NULL
};

//--- (end of YPwmPowerSource definitions)

bool   isModule(void)      { return false; }

//--- (YPwmPowerSource implementation)
string YFunctionName(void) { return "PwmPowerSource"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of powerMode is int (PwmPwrState)
/**
 * Returns the logical name of the voltage source.
 *
 * @return a string corresponding to the logical name of the voltage source
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class PwmPowerSource_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the voltage source.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmPowerSource*>* list = enumerateTargets<YPwmPowerSource>(target,modulelist);
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
 * Changes the logical name of the voltage source. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the voltage source
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmPowerSource_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the voltage source.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the voltage source", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmPowerSource*>* list = enumerateTargets<YPwmPowerSource>(target,modulelist);
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
 * Returns a short string representing the current state of the voltage source.
 *
 * @return a string corresponding to a short string representing the current state of the voltage source
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class PwmPowerSource_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the voltage source.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmPowerSource*>* list = enumerateTargets<YPwmPowerSource>(target,modulelist);
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
 * Changes  the PWM power source. PWM can use isolated 5V from USB, isolated 3V from USB or
 * voltage from an external power source. The PWM can also work in open drain  mode. In that
 * mode, the PWM actively pulls the line down.
 * Warning: this setting is common to all PWM on the same device. If you change that parameter,
 * all PWM located on the same device are  affected.
 * If you want the change to be kept after a device reboot, make sure  to call the matching
 * module saveToFlash().
 *
 * @param newval : a value among Y_POWERMODE_USB_5V, Y_POWERMODE_USB_3V, Y_POWERMODE_EXT_V and
 * Y_POWERMODE_OPNDRN corresponding to  the PWM power source
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmPowerSource_set_powerMode : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_powerMode";
  }

  string getDescription()
  {
    return "Changes the PWM power source.";
  }

  string getMoreInfo()
  {
    return "PWM can use isolated 5V from USB, isolated 3V from USB or voltage from an external power source. The PWM can also work in open drain mode. In that mode, the PWM actively pulls the line down. Warning: this setting is common to all PWM on the same device. If you change that parameter, all PWM located on the same device are affected. If you want the change to be kept after a device reboot, make sure to call the matching module saveToFlash().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among USB_5V, USB_3V, EXT_V and OPNDRN corresponding to the PWM power source", "USB_5V=0,USB_3V=1,EXT_V=2,OPNDRN=3", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmPowerSource*>* list = enumerateTargets<YPwmPowerSource>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_powerMode(Y_POWERMODE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackPwmPowerSource is YPwmPowerSourceValueCallback* (YPwmPowerSourceValueCallback)
//--- (end of YPwmPowerSource implementation)

//--- (PwmPowerSource functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YPwmPowerSource>(cmdList);
    cmdList->push_back((YapiCommand*) (new PwmPowerSource_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new PwmPowerSource_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new PwmPowerSource_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new PwmPowerSource_set_powerMode()));
  }

//--- (end of PwmPowerSource functions)
