/*********************************************************************
 *
 * $Id: YPwmOutput.cpp 20287 2015-05-08 13:40:21Z seb $
 *
 * Implements commands to handle PwmOutput functions
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
#include "yocto_pwmoutput.h"

using namespace std;

//--- (YPwmOutput definitions)

const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

//--- (end of YPwmOutput definitions)

bool   isModule(void)      { return false; }

//--- (YPwmOutput implementation)
string YFunctionName(void) { return "PwmOutput"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of enabled is int (Bool)
// type of frequency is double (MeasureVal)
// type of period is double (MeasureVal)
// type of dutyCycle is double (MeasureVal)
// type of pulseDuration is double (MeasureVal)
// type of pwmTransition is string (PwmTransition)
// type of enabledAtPowerOn is int (Bool)
// type of dutyCycleAtPowerOn is double (MeasureVal)
/**
 * Returns the logical name of the PWM.
 *
 * @return a string corresponding to the logical name of the PWM
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class PwmOutput_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the PWM.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
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
 * Changes the logical name of the PWM. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the PWM
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the PWM.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the PWM", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
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
 * Returns a short string representing the current state of the PWM.
 *
 * @return a string corresponding to a short string representing the current state of the PWM
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class PwmOutput_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the PWM.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
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
 * Returns the state of the PWMs.
 *
 * @return either Y_ENABLED_FALSE or Y_ENABLED_TRUE, according to the state of the PWMs
 *
 * On failure, throws an exception or returns Y_ENABLED_INVALID.
 */
class PwmOutput_get_enabled : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_enabled";
  }

  string getDescription()
  {
    return "Returns the state of the PWMs.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_enabled();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Stops or starts the PWM.
 *
 * @param newval : either Y_ENABLED_FALSE or Y_ENABLED_TRUE
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_enabled : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_enabled";
  }

  string getDescription()
  {
    return "Stops or starts the PWM.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_enabled(Y_ENABLED_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the PWM frequency. The duty cycle is kept unchanged thanks to an
 * automatic pulse width change.
 *
 * @param newval : a floating point number corresponding to the PWM frequency
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_frequency : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_frequency";
  }

  string getDescription()
  {
    return "Changes the PWM frequency.";
  }

  string getMoreInfo()
  {
    return "The duty cycle is kept unchanged thanks to an automatic pulse width change.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the PWM frequency", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_frequency(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the PWM frequency in Hz.
 *
 * @return a floating point number corresponding to the PWM frequency in Hz
 *
 * On failure, throws an exception or returns Y_FREQUENCY_INVALID.
 */
class PwmOutput_get_frequency : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_frequency";
  }

  string getDescription()
  {
    return "Returns the PWM frequency in Hz.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_frequency();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the PWM period in milliseconds.
 *
 * @param newval : a floating point number corresponding to the PWM period in milliseconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_period : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_period";
  }

  string getDescription()
  {
    return "Changes the PWM period in milliseconds.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the PWM period in milliseconds", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_period(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the PWM period in milliseconds.
 *
 * @return a floating point number corresponding to the PWM period in milliseconds
 *
 * On failure, throws an exception or returns Y_PERIOD_INVALID.
 */
class PwmOutput_get_period : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_period";
  }

  string getDescription()
  {
    return "Returns the PWM period in milliseconds.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_period();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the PWM duty cycle, in per cents.
 *
 * @param newval : a floating point number corresponding to the PWM duty cycle, in per cents
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_dutyCycle : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_dutyCycle";
  }

  string getDescription()
  {
    return "Changes the PWM duty cycle, in per cents.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the PWM duty cycle, in per cents", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_dutyCycle(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the PWM duty cycle, in per cents.
 *
 * @return a floating point number corresponding to the PWM duty cycle, in per cents
 *
 * On failure, throws an exception or returns Y_DUTYCYCLE_INVALID.
 */
class PwmOutput_get_dutyCycle : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_dutyCycle";
  }

  string getDescription()
  {
    return "Returns the PWM duty cycle, in per cents.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_dutyCycle();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the PWM pulse length, in milliseconds. A pulse length cannot be longer than period,
 * otherwise it is truncated.
 *
 * @param newval : a floating point number corresponding to the PWM pulse length, in milliseconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_pulseDuration : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_pulseDuration";
  }

  string getDescription()
  {
    return "Changes the PWM pulse length, in milliseconds.";
  }

  string getMoreInfo()
  {
    return "A pulse length cannot be longer than period, otherwise it is truncated.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the PWM pulse length, in milliseconds", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_pulseDuration(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the PWM pulse length in milliseconds, as a floating point number.
 *
 * @return a floating point number corresponding to the PWM pulse length in milliseconds, as a
 * floating point number
 *
 * On failure, throws an exception or returns Y_PULSEDURATION_INVALID.
 */
class PwmOutput_get_pulseDuration : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_pulseDuration";
  }

  string getDescription()
  {
    return "Returns the PWM pulse length in milliseconds, as a floating point number.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_pulseDuration();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the state of the PWM at device power on.
 *
 * @return either Y_ENABLEDATPOWERON_FALSE or Y_ENABLEDATPOWERON_TRUE, according to the state of the
 * PWM at device power on
 *
 * On failure, throws an exception or returns Y_ENABLEDATPOWERON_INVALID.
 */
class PwmOutput_get_enabledAtPowerOn : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_enabledAtPowerOn";
  }

  string getDescription()
  {
    return "Returns the state of the PWM at device power on.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_enabledAtPowerOn();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the state of the PWM at device power on. Remember to call the matching module saveToFlash()
 * method, otherwise this call will have no effect.
 *
 * @param newval : either Y_ENABLEDATPOWERON_FALSE or Y_ENABLEDATPOWERON_TRUE, according to the state
 * of the PWM at device power on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_enabledAtPowerOn : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_enabledAtPowerOn";
  }

  string getDescription()
  {
    return "Changes the state of the PWM at device power on.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE, according to the state of the PWM at device power on", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_enabledAtPowerOn(Y_ENABLEDATPOWERON_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the PWM duty cycle at device power on. Remember to call the matching
 * module saveToFlash() method, otherwise this call will have no effect.
 *
 * @param newval : a floating point number corresponding to the PWM duty cycle at device power on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmOutput_set_dutyCycleAtPowerOn : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_dutyCycleAtPowerOn";
  }

  string getDescription()
  {
    return "Changes the PWM duty cycle at device power on.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the PWM duty cycle at device power on", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_dutyCycleAtPowerOn(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackPwmOutput is YPwmOutputValueCallback* (YPwmOutputValueCallback)
/**
 * Performs a smooth transistion of the pulse duration toward a given value. Any period,
 * frequency, duty cycle or pulse width change will cancel any ongoing transition process.
 *
 * @param ms_target   : new pulse duration at the end of the transition
 *         (floating-point number, representing the pulse duration in milliseconds)
 * @param ms_duration : total duration of the transition, in milliseconds
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_PwmOutput_pulseDurationMove : public YapiCommand /* arguments: ms_target ms_duration */
{
public:

  string getName()
  {
    return "pulseDurationMove";
  }

  string getDescription()
  {
    return "Performs a smooth transistion of the pulse duration toward a given value.";
  }

  string getMoreInfo()
  {
    return "Any period, frequency, duty cycle or pulse width change will cancel any ongoing transition process.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "ms_target", "new pulse duration at the end of the transition (floating-point number, representing the pulse duration in milliseconds)", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "total duration of the transition, in milliseconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->pulseDurationMove((*args)[0]->get_doubleValue(),
                                      (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Performs a smooth change of the pulse duration toward a given value.
 *
 * @param target      : new duty cycle at the end of the transition
 *         (floating-point number, between 0 and 1)
 * @param ms_duration : total duration of the transition, in milliseconds
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_PwmOutput_dutyCycleMove : public YapiCommand /* arguments: target ms_duration */
{
public:

  string getName()
  {
    return "dutyCycleMove";
  }

  string getDescription()
  {
    return "Performs a smooth change of the pulse duration toward a given value.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "target", "new duty cycle at the end of the transition (floating-point number, between 0 and 1)", "_DOUBLE", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "total duration of the transition, in milliseconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmOutput*>* list = enumerateTargets<YPwmOutput>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->dutyCycleMove((*args)[0]->get_doubleValue(),
                                  (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YPwmOutput implementation)

//--- (PwmOutput functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YPwmOutput>(cmdList);
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_enabled()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_enabled()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_frequency()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_frequency()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_period()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_period()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_dutyCycle()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_dutyCycle()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_pulseDuration()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_pulseDuration()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_get_enabledAtPowerOn()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_enabledAtPowerOn()));
    cmdList->push_back((YapiCommand*) (new PwmOutput_set_dutyCycleAtPowerOn()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmOutput_pulseDurationMove()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmOutput_dutyCycleMove()));
  }

//--- (end of PwmOutput functions)
