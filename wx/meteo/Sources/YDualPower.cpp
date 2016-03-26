/*********************************************************************
 *
 * $Id: YDualPower.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle DualPower functions
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
#include "yocto_dualpower.h"

using namespace std;

//--- (YDualPower definitions)

const char *enumPwrCtrl[] = {
    "AUTO",
    "FROM_USB",
    "FROM_EXT",
    "OFF",
    NULL
};

const char *enumPwrState[] = {
    "OFF",
    "FROM_USB",
    "FROM_EXT",
    NULL
};

//--- (end of YDualPower definitions)

bool   isModule(void)      { return false; }

//--- (YDualPower implementation)
string YFunctionName(void) { return "External power supply control interface"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of powerState is int (DualPwrState)
// type of powerControl is int (DualPwrControl)
// type of extVoltage is int (UInt31)
/**
 * Returns the logical name of the power control.
 *
 * @return a string corresponding to the logical name of the power control
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class DualPower_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the power control.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDualPower*>* list = enumerateTargets<YDualPower>(target,modulelist);
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
 * Changes the logical name of the power control. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the power control
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DualPower_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the power control.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the power control", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDualPower*>* list = enumerateTargets<YDualPower>(target,modulelist);
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
 * Returns a short string representing the current state of the power control.
 *
 * @return a string corresponding to a short string representing the current state of the power control
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class DualPower_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the power control.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDualPower*>* list = enumerateTargets<YDualPower>(target,modulelist);
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
 * Returns the current power source for module functions that require lots of current.
 *
 * @return a value among Y_POWERSTATE_OFF, Y_POWERSTATE_FROM_USB and Y_POWERSTATE_FROM_EXT
 * corresponding to the current power source for module functions that require lots of current
 *
 * On failure, throws an exception or returns Y_POWERSTATE_INVALID.
 */
class DualPower_get_powerState : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_powerState";
  }

  string getDescription()
  {
    return "Returns the current power source for module functions that require lots of current.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDualPower*>* list = enumerateTargets<YDualPower>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_powerState();
        string strval =  enumString(attrval,enumPwrState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the selected power source for module functions that require lots of current.
 *
 * @return a value among Y_POWERCONTROL_AUTO, Y_POWERCONTROL_FROM_USB, Y_POWERCONTROL_FROM_EXT and
 * Y_POWERCONTROL_OFF corresponding to the selected power source for module functions that require lots of current
 *
 * On failure, throws an exception or returns Y_POWERCONTROL_INVALID.
 */
class DualPower_get_powerControl : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_powerControl";
  }

  string getDescription()
  {
    return "Returns the selected power source for module functions that require lots of current.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDualPower*>* list = enumerateTargets<YDualPower>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_powerControl();
        string strval =  enumString(attrval,enumPwrCtrl);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the selected power source for module functions that require lots of current.
 *
 * @param newval : a value among Y_POWERCONTROL_AUTO, Y_POWERCONTROL_FROM_USB, Y_POWERCONTROL_FROM_EXT
 * and Y_POWERCONTROL_OFF corresponding to the selected power source for module functions that require
 * lots of current
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DualPower_set_powerControl : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_powerControl";
  }

  string getDescription()
  {
    return "Changes the selected power source for module functions that require lots of current.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among AUTO, FROM_USB, FROM_EXT and OFF corresponding to the selected power source for module functions that require lots of current", "AUTO=0,FROM_USB=1,FROM_EXT=2,OFF=3", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDualPower*>* list = enumerateTargets<YDualPower>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_powerControl(Y_POWERCONTROL_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the measured voltage on the external power source, in millivolts.
 *
 * @return an integer corresponding to the measured voltage on the external power source, in millivolts
 *
 * On failure, throws an exception or returns Y_EXTVOLTAGE_INVALID.
 */
class DualPower_get_extVoltage : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_extVoltage";
  }

  string getDescription()
  {
    return "Returns the measured voltage on the external power source, in millivolts.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDualPower*>* list = enumerateTargets<YDualPower>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_extVoltage();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackDualPower is YDualPowerValueCallback* (YDualPowerValueCallback)
//--- (end of YDualPower implementation)

//--- (DualPower functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YDualPower>(cmdList);
    cmdList->push_back((YapiCommand*) (new DualPower_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new DualPower_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new DualPower_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new DualPower_get_powerState()));
    cmdList->push_back((YapiCommand*) (new DualPower_get_powerControl()));
    cmdList->push_back((YapiCommand*) (new DualPower_set_powerControl()));
    cmdList->push_back((YapiCommand*) (new DualPower_get_extVoltage()));
  }

//--- (end of DualPower functions)
