/*********************************************************************
 *
 * $Id: YPowerOutput.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle PowerOutput functions
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
#include "yocto_poweroutput.h"

using namespace std;

//--- (YPowerOutput definitions)

const char *enumPowerOuputVoltage[] = {
    "OFF",
    "OUT3V3",
    "OUT5V",
    NULL
};

//--- (end of YPowerOutput definitions)

bool   isModule(void)      { return false; }

//--- (YPowerOutput implementation)
string YFunctionName(void) { return "External power supply control interface"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of voltage is int (PowerOuputVoltage)
/**
 * Returns the logical name of the power ouput control.
 *
 * @return a string corresponding to the logical name of the power ouput control
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class PowerOutput_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the power ouput control.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerOutput*>* list = enumerateTargets<YPowerOutput>(target,modulelist);
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
 * Changes the logical name of the power ouput control. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the power ouput control
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerOutput_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the power ouput control.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the power ouput control", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPowerOutput*>* list = enumerateTargets<YPowerOutput>(target,modulelist);
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
 * Returns a short string representing the current state of the power ouput control.
 *
 * @return a string corresponding to a short string representing the current state of the power ouput control
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class PowerOutput_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the power ouput control.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerOutput*>* list = enumerateTargets<YPowerOutput>(target,modulelist);
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
 * Returns the voltage on the power ouput featured by
 * the module.
 *
 * @return a value among Y_VOLTAGE_OFF, Y_VOLTAGE_OUT3V3 and Y_VOLTAGE_OUT5V corresponding to the
 * voltage on the power ouput featured by
 *         the module
 *
 * On failure, throws an exception or returns Y_VOLTAGE_INVALID.
 */
class PowerOutput_get_voltage : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_voltage";
  }

  string getDescription()
  {
    return "Returns the voltage on the power ouput featured bythe module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPowerOutput*>* list = enumerateTargets<YPowerOutput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_voltage();
        string strval =  enumString(attrval,enumPowerOuputVoltage);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the voltage on the power output provided by the
 * module. Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a value among Y_VOLTAGE_OFF, Y_VOLTAGE_OUT3V3 and Y_VOLTAGE_OUT5V corresponding to
 * the voltage on the power output provided by the
 *         module
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PowerOutput_set_voltage : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_voltage";
  }

  string getDescription()
  {
    return "Changes the voltage on the power output provided by themodule.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among OFF, OUT3V3 and OUT5V corresponding to the voltage on the power output provided by the module", "OFF=0,OUT3V3=1,OUT5V=2", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPowerOutput*>* list = enumerateTargets<YPowerOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_voltage(Y_VOLTAGE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackPowerOutput is YPowerOutputValueCallback* (YPowerOutputValueCallback)
//--- (end of YPowerOutput implementation)

//--- (PowerOutput functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YPowerOutput>(cmdList);
    cmdList->push_back((YapiCommand*) (new PowerOutput_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new PowerOutput_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new PowerOutput_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new PowerOutput_get_voltage()));
    cmdList->push_back((YapiCommand*) (new PowerOutput_set_voltage()));
  }

//--- (end of PowerOutput functions)
