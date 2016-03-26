/*********************************************************************
 *
 * $Id: YPwmInput.cpp 20400 2015-05-21 14:58:16Z mvuilleu $
 *
 * Implements commands to handle PwmInput functions
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
#include "yocto_pwminput.h"

using namespace std;

//--- (YPwmInput definitions)

const char *enumPwmReportModeType[] = {
    "PWM_DUTYCYCLE",
    "PWM_FREQUENCY",
    "PWM_PULSEDURATION",
    "PWM_EDGECOUNT",
    NULL
};

//--- (end of YPwmInput definitions)

bool   isModule(void)      { return false; }

//--- (YPwmInput implementation)
string YFunctionName(void) { return "PwmInput"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of unit is string (Text)
// type of currentValue is double (MeasureVal)
// type of lowestValue is double (MeasureVal)
// type of highestValue is double (MeasureVal)
// type of currentRawValue is double (MeasureVal)
// type of logFrequency is string (YFrequency)
// type of reportFrequency is string (YFrequency)
// type of calibrationParam is string (CalibParams)
// type of resolution is double (MeasureVal)
// type of sensorState is int (Int)
// type of dutyCycle is double (MeasureVal)
// type of pulseDuration is double (MeasureVal)
// type of frequency is double (MeasureVal)
// type of period is double (MeasureVal)
// type of pulseCounter is s64 (UInt)
// type of pulseTimer is s64 (Time)
// type of pwmReportMode is int (PwmReportModeType)
/**
 * Returns the logical name of the PWM input.
 *
 * @return a string corresponding to the logical name of the PWM input
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class PwmInput_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the PWM input.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
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
 * Changes the logical name of the PWM input. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the PWM input
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmInput_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the PWM input.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the PWM input", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
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
 * Returns a short string representing the current state of the PWM input.
 *
 * @return a string corresponding to a short string representing the current state of the PWM input
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class PwmInput_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the PWM input.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
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
 * Returns the measuring unit for the values returned
 * by  get_currentValue and callbacks. This unit changes
 * according to the pwmReportMode settings.
 *
 * @return a string corresponding to the measuring unit for the values returned
 *         by  get_currentValue and callbacks
 *
 * On failure, throws an exception or returns Y_UNIT_INVALID.
 */
class PwmInput_get_unit : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_unit";
  }

  string getDescription()
  {
    return "Returns the measuring unit for the values returnedby get_currentValue and callbacks.";
  }

  string getMoreInfo()
  {
    return "This unit changes according to the pwmReportMode settings.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_unit();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current value of the PwmInput feature as a floating point number. Depending on
 * the pwmReportMode setting, this can be the frequency, in Hz, the duty cycle in % or
 * the pulse length in ms.
 *
 * @return a floating point number corresponding to the current value of the PwmInput feature as a
 * floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTVALUE_INVALID.
 */
class PwmInput_get_currentValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_currentValue";
  }

  string getDescription()
  {
    return "Returns the current value of the PwmInput feature as a floating point number.";
  }

  string getMoreInfo()
  {
    return "Depending on the pwmReportMode setting, this can be the frequency, in Hz, the duty cycle in % or the pulse length in ms.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the recorded minimal value observed.
 *
 * @param newval : a floating point number corresponding to the recorded minimal value observed
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmInput_set_lowestValue : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_lowestValue";
  }

  string getDescription()
  {
    return "Changes the recorded minimal value observed.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the recorded minimal value observed", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_lowestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the minimal value observed for the PWM since the device was started.
 *
 * @return a floating point number corresponding to the minimal value observed for the PWM since the
 * device was started
 *
 * On failure, throws an exception or returns Y_LOWESTVALUE_INVALID.
 */
class PwmInput_get_lowestValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_lowestValue";
  }

  string getDescription()
  {
    return "Returns the minimal value observed for the PWM since the device was started.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_lowestValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the recorded maximal value observed.
 *
 * @param newval : a floating point number corresponding to the recorded maximal value observed
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmInput_set_highestValue : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_highestValue";
  }

  string getDescription()
  {
    return "Changes the recorded maximal value observed.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the recorded maximal value observed", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_highestValue(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the maximal value observed for the PWM since the device was started.
 *
 * @return a floating point number corresponding to the maximal value observed for the PWM since the
 * device was started
 *
 * On failure, throws an exception or returns Y_HIGHESTVALUE_INVALID.
 */
class PwmInput_get_highestValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_highestValue";
  }

  string getDescription()
  {
    return "Returns the maximal value observed for the PWM since the device was started.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_highestValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the uncalibrated, unrounded raw value returned by the sensor, in HZ, as a floating point number.
 *
 * @return a floating point number corresponding to the uncalibrated, unrounded raw value returned by
 * the sensor, in HZ, as a floating point number
 *
 * On failure, throws an exception or returns Y_CURRENTRAWVALUE_INVALID.
 */
class PwmInput_get_currentRawValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_currentRawValue";
  }

  string getDescription()
  {
    return "Returns the uncalibrated, unrounded raw value returned by the sensor, in HZ, as a floating point number.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_currentRawValue();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the datalogger recording frequency for this function, or "OFF"
 * when measures are not stored in the data logger flash memory.
 *
 * @return a string corresponding to the datalogger recording frequency for this function, or "OFF"
 *         when measures are not stored in the data logger flash memory
 *
 * On failure, throws an exception or returns Y_LOGFREQUENCY_INVALID.
 */
class PwmInput_get_logFrequency : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logFrequency";
  }

  string getDescription()
  {
    return "Returns the datalogger recording frequency for this function, or \"OFF\"when measures are not stored in the data logger flash memory.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_logFrequency();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the datalogger recording frequency for this function.
 * The frequency can be specified as samples per second,
 * as sample per minute (for instance "15/m") or in samples per
 * hour (eg. "4/h"). To disable recording for this function, use
 * the value "OFF".
 *
 * @param newval : a string corresponding to the datalogger recording frequency for this function
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmInput_set_logFrequency : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logFrequency";
  }

  string getDescription()
  {
    return "Changes the datalogger recording frequency for this function.";
  }

  string getMoreInfo()
  {
    return "The frequency can be specified as samples per second, as sample per minute (for instance \"15/m\") or in samples per hour (eg. \"4/h\"). To disable recording for this function, use the value \"OFF\".";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the datalogger recording frequency for this function", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_logFrequency(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the timed value notification frequency, or "OFF" if timed
 * value notifications are disabled for this function.
 *
 * @return a string corresponding to the timed value notification frequency, or "OFF" if timed
 *         value notifications are disabled for this function
 *
 * On failure, throws an exception or returns Y_REPORTFREQUENCY_INVALID.
 */
class PwmInput_get_reportFrequency : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_reportFrequency";
  }

  string getDescription()
  {
    return "Returns the timed value notification frequency, or \"OFF\" if timedvalue notifications are disabled for this function.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_reportFrequency();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the timed value notification frequency for this function.
 * The frequency can be specified as samples per second,
 * as sample per minute (for instance "15/m") or in samples per
 * hour (eg. "4/h"). To disable timed value notifications for this
 * function, use the value "OFF".
 *
 * @param newval : a string corresponding to the timed value notification frequency for this function
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmInput_set_reportFrequency : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_reportFrequency";
  }

  string getDescription()
  {
    return "Changes the timed value notification frequency for this function.";
  }

  string getMoreInfo()
  {
    return "The frequency can be specified as samples per second, as sample per minute (for instance \"15/m\") or in samples per hour (eg. \"4/h\"). To disable timed value notifications for this function, use the value \"OFF\".";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the timed value notification frequency for this function", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_reportFrequency(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the resolution of the measured physical values. The resolution corresponds to the numerical precision
 * when displaying value. It does not change the precision of the measure itself.
 *
 * @param newval : a floating point number corresponding to the resolution of the measured physical values
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmInput_set_resolution : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_resolution";
  }

  string getDescription()
  {
    return "Changes the resolution of the measured physical values.";
  }

  string getMoreInfo()
  {
    return "The resolution corresponds to the numerical precision when displaying value. It does not change the precision of the measure itself.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the resolution of the measured physical values", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_resolution(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the resolution of the measured values. The resolution corresponds to the numerical precision
 * of the measures, which is not always the same as the actual precision of the sensor.
 *
 * @return a floating point number corresponding to the resolution of the measured values
 *
 * On failure, throws an exception or returns Y_RESOLUTION_INVALID.
 */
class PwmInput_get_resolution : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_resolution";
  }

  string getDescription()
  {
    return "Returns the resolution of the measured values.";
  }

  string getMoreInfo()
  {
    return "The resolution corresponds to the numerical precision of the measures, which is not always the same as the actual precision of the sensor.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_resolution();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the sensor health state code, which is zero when there is an up-to-date measure
 * available or a positive code if the sensor is not able to provide a measure right now.
 *
 * @return an integer corresponding to the sensor health state code, which is zero when there is an
 * up-to-date measure
 *         available or a positive code if the sensor is not able to provide a measure right now
 *
 * On failure, throws an exception or returns Y_SENSORSTATE_INVALID.
 */
class PwmInput_get_sensorState : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_sensorState";
  }

  string getDescription()
  {
    return "Returns the sensor health state code, which is zero when there is an up-to-date measureavailable or a positive code if the sensor is not able to provide a measure right now.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_sensorState();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
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
class PwmInput_get_dutyCycle : public YapiCommand /* arguments: */
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
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
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
 * Returns the PWM pulse length in milliseconds, as a floating point number.
 *
 * @return a floating point number corresponding to the PWM pulse length in milliseconds, as a
 * floating point number
 *
 * On failure, throws an exception or returns Y_PULSEDURATION_INVALID.
 */
class PwmInput_get_pulseDuration : public YapiCommand /* arguments: */
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
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
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
 * Returns the PWM frequency in Hz.
 *
 * @return a floating point number corresponding to the PWM frequency in Hz
 *
 * On failure, throws an exception or returns Y_FREQUENCY_INVALID.
 */
class PwmInput_get_frequency : public YapiCommand /* arguments: */
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
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
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
 * Returns the PWM period in milliseconds.
 *
 * @return a floating point number corresponding to the PWM period in milliseconds
 *
 * On failure, throws an exception or returns Y_PERIOD_INVALID.
 */
class PwmInput_get_period : public YapiCommand /* arguments: */
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
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
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
 * Returns the pulse counter value. Actually that
 * counter is incremented twice per period. That counter is
 * limited  to 1 billion
 *
 * @return an integer corresponding to the pulse counter value
 *
 * On failure, throws an exception or returns Y_PULSECOUNTER_INVALID.
 */
class PwmInput_get_pulseCounter : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_pulseCounter";
  }

  string getDescription()
  {
    return "Returns the pulse counter value.";
  }

  string getMoreInfo()
  {
    return "Actually that counter is incremented twice per period. That counter is limited to 1 billion";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_pulseCounter();
        char buf[32]; snprintf(buf, 32, "%u", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the parameter (frequency/duty cycle, pulse width, edges count) returned by the
 * get_currentValue function and callbacks. Attention
 *
 * @return a value among Y_PWMREPORTMODE_PWM_DUTYCYCLE, Y_PWMREPORTMODE_PWM_FREQUENCY,
 * Y_PWMREPORTMODE_PWM_PULSEDURATION and Y_PWMREPORTMODE_PWM_EDGECOUNT corresponding to the parameter
 * (frequency/duty cycle, pulse width, edges count) returned by the get_currentValue function and callbacks
 *
 * On failure, throws an exception or returns Y_PWMREPORTMODE_INVALID.
 */
class PwmInput_get_pwmReportMode : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_pwmReportMode";
  }

  string getDescription()
  {
    return "Returns the parameter (frequency/duty cycle, pulse width, edges count) returned by the get_currentValue function and callbacks.";
  }

  string getMoreInfo()
  {
    return "Attention";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_pwmReportMode();
        string strval =  enumString(attrval,enumPwmReportModeType);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Modifies the  parameter  type (frequency/duty cycle, pulse width, or edge count) returned by the
 * get_currentValue function and callbacks.
 * The edge count value is limited to the 6 lowest digits. For values greater than one million, use
 * get_pulseCounter().
 *
 * @param newval : a value among Y_PWMREPORTMODE_PWM_DUTYCYCLE, Y_PWMREPORTMODE_PWM_FREQUENCY,
 * Y_PWMREPORTMODE_PWM_PULSEDURATION and Y_PWMREPORTMODE_PWM_EDGECOUNT
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class PwmInput_set_pwmReportMode : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_pwmReportMode";
  }

  string getDescription()
  {
    return "Modifies the parameter type (frequency/duty cycle, pulse width, or edge count) returned by the get_currentValue function and callbacks.";
  }

  string getMoreInfo()
  {
    return "The edge count value is limited to the 6 lowest digits. For values greater than one million, use get_pulseCounter().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among PWM_DUTYCYCLE, PWM_FREQUENCY, PWM_PULSEDURATION and PWM_EDGECOUNT", "PWM_DUTYCYCLE=0,PWM_FREQUENCY=1,PWM_PULSEDURATION=2,PWM_EDGECOUNT=3", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_pwmReportMode(Y_PWMREPORTMODE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackPwmInput is YPwmInputValueCallback* (YPwmInputValueCallback)
// type of timedReportCallbackPwmInput is YPwmInputTimedReportCallback* (YPwmInputTimedReportCallback)
/**
 * Checks if the sensor is currently able to provide an up-to-date measure.
 * Returns false if the device is unreachable, or if the sensor does not have
 * a current measure to transmit. No exception is raised if there is an error
 * while trying to contact the device hosting $THEFUNCTION$.
 *
 * @return true if the sensor can provide an up-to-date measure, and false otherwise
 */
class apifun_PwmInput_isSensorReady : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "isSensorReady";
  }

  string getDescription()
  {
    return "Checks if the sensor is currently able to provide an up-to-date measure.";
  }

  string getMoreInfo()
  {
    return "Returns false if the device is unreachable, or if the sensor does not have a current measure to transmit. No exception is raised if there is an error while trying to contact the device hosting $THEFUNCTION$.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        bool value = (*list)[i]->isSensorReady();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the data logger on the device. Note that the data logger
 * will only save the measures on this sensor if the logFrequency
 * is not set to "OFF".
 *
 * @return YAPI_SUCCESS if the call succeeds.
 */
class apifun_PwmInput_startDataLogger : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "startDataLogger";
  }

  string getDescription()
  {
    return "Starts the data logger on the device.";
  }

  string getMoreInfo()
  {
    return "Note that the data logger will only save the measures on this sensor if the logFrequency is not set to \"OFF\".";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->startDataLogger();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the datalogger on the device.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 */
class apifun_PwmInput_stopDataLogger : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "stopDataLogger";
  }

  string getDescription()
  {
    return "Stops the datalogger on the device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->stopDataLogger();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves a DataSet object holding historical data for this
 * sensor, for a specified time interval. The measures will be
 * retrieved from the data logger, which must have been turned
 * on at the desired time. See the documentation of the DataSet
 * class for information on how to get an overview of the
 * recorded data, and how to load progressively a large set
 * of measures from the data logger.
 *
 * This function only works if the device uses a recent firmware,
 * as DataSet objects are not supported by firmwares older than
 * version 13000.
 *
 * @param startTime : the start of the desired measure time interval,
 *         as a Unix timestamp, i.e. the number of seconds since
 *         January 1, 1970 UTC. The special value 0 can be used
 *         to include any meaasure, without initial limit.
 * @param endTime : the end of the desired measure time interval,
 *         as a Unix timestamp, i.e. the number of seconds since
 *         January 1, 1970 UTC. The special value 0 can be used
 *         to include any meaasure, without ending limit.
 *
 * @return an instance of YDataSet, providing access to historical
 *         data. Past measures can be loaded progressively
 *         using methods from the YDataSet object.
 */
class apifun_PwmInput_get_recordedData : public YapiCommand /* arguments: startTime endTime */
{
public:

  string getName()
  {
    return "get_recordedData";
  }

  string getDescription()
  {
    return "Retrieves a DataSet object holding historical data for thissensor, for a specified time interval.";
  }

  string getMoreInfo()
  {
    return "The measures will be retrieved from the data logger, which must have been turned on at the desired time. See the documentation of the DataSet class for information on how to get an overview of the recorded data, and how to load progressively a large set of measures from the data logger.\nThis function only works if the device uses a recent firmware, as DataSet objects are not supported by firmwares older than version 13000.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(S64_ARG, "startTime", "the start of the desired measure time interval, as a Unix timestamp, i.e. the number of seconds since January 1, 1970 UTC. The special value 0 can be used to include any meaasure, without initial limit.", "_S64", false));
    res->push_back(new ArgumentDesc(S64_ARG, "endTime", "the end of the desired measure time interval, as a Unix timestamp, i.e. the number of seconds since January 1, 1970 UTC. The special value 0 can be used to include any meaasure, without ending limit.", "_S64", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YDataSet value = (*list)[i]->get_recordedData((*args)[0]->get_s64Value(),
                                                      (*args)[1]->get_s64Value());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Configures error correction data points, in particular to compensate for
 * a possible perturbation of the measure caused by an enclosure. It is possible
 * to configure up to five correction points. Correction points must be provided
 * in ascending order, and be in the range of the sensor. The device will automatically
 * perform a linear interpolation of the error correction between specified
 * points. Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * For more information on advanced capabilities to refine the calibration of
 * sensors, please contact support@yoctopuce.com.
 *
 * @param rawValues : array of floating point numbers, corresponding to the raw
 *         values returned by the sensor for the correction points.
 * @param refValues : array of floating point numbers, corresponding to the corrected
 *         values for the correction points.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_PwmInput_calibrateFromPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:

  string getName()
  {
    return "calibrateFromPoints";
  }

  string getDescription()
  {
    return "Configures error correction data points, in particular to compensate fora possible perturbation of the measure caused by an enclosure.";
  }

  string getMoreInfo()
  {
    return "It is possible to configure up to five correction points. Correction points must be provided in ascending order, and be in the range of the sensor. The device will automatically perform a linear interpolation of the error correction between specified points. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.\nFor more information on advanced capabilities to refine the calibration of sensors, please contact support@yoctopuce.com.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "rawValues", "array of floating point numbers, corresponding to the raw values returned by the sensor for the correction points.", "_FLOATARR", false));
    res->push_back(new ArgumentDesc(FLOATARR_ARG, "refValues", "array of floating point numbers, corresponding to the corrected values for the correction points.", "_FLOATARR", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->calibrateFromPoints((*args)[0]->get_floatArrValue(),
                                        (*args)[1]->get_floatArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves error correction data points previously entered using the method
 * calibrateFromPoints.
 *
 * @param rawValues : array of floating point numbers, that will be filled by the
 *         function with the raw sensor values for the correction points.
 * @param refValues : array of floating point numbers, that will be filled by the
 *         function with the desired values for the correction points.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_PwmInput_loadCalibrationPoints : public YapiCommand /* arguments: rawValues refValues */
{
public:

  string getName()
  {
    return "loadCalibrationPoints";
  }

  string getDescription()
  {
    return "Retrieves error correction data points previously entered using the methodcalibrateFromPoints.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        vector<double> rawValues;
        vector<double> refValues;
        (*list)[i]->loadCalibrationPoints(rawValues,
                                          refValues);
        PrintResult(resultformat, this->getName()+".rawValues",YFunctionInfoCache((*list)[i]), rawValues, true);
        PrintResult(resultformat, this->getName()+".refValues",YFunctionInfoCache((*list)[i]), refValues, true);
      }
  }
};

/**
 * Returns the pulse counter value as well as its timer.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_PwmInput_resetCounter : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "resetCounter";
  }

  string getDescription()
  {
    return "Returns the pulse counter value as well as its timer.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetCounter();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retrieves any available timed report from the functions.
 *
 * @param minWait: the minimum time to wait for a timed report,
 *         or zero to wait at least up to the first timed report.
 * @param maxWait: the maximum time to wait for a timed report,
 *         or zero to wait no more than up to the first timed report.
 *
 */
class apifun_PwmInput_get_timedReport : public YapiCommand /* arguments: minWait maxWait */
{
public:

  string getName()
  {
    return "get_timedReport";
  }

  string getDescription()
  {
    return "Retrieves any available timed report from the functions.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "minWait", "the minimum time to wait for a timed report, or zero to wait at least up to the first timed report.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum time to wait for a timed report, or zero to wait no more than up to the first timed report.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YPwmInput*>* list = enumerateTargets<YPwmInput>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->registerTimedReportCallback(cmdlineTimedReportCallback);
      }
    waitForCallbacks((*args)[0]->get_intValue(), (*args)[1]->get_intValue());
  }
};

//--- (end of YPwmInput implementation)

//--- (PwmInput functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YPwmInput>(cmdList);
    cmdList->push_back((YapiCommand*) (new PwmInput_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new PwmInput_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_unit()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_currentValue()));
    cmdList->push_back((YapiCommand*) (new PwmInput_set_lowestValue()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_lowestValue()));
    cmdList->push_back((YapiCommand*) (new PwmInput_set_highestValue()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_highestValue()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_currentRawValue()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_logFrequency()));
    cmdList->push_back((YapiCommand*) (new PwmInput_set_logFrequency()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_reportFrequency()));
    cmdList->push_back((YapiCommand*) (new PwmInput_set_reportFrequency()));
    cmdList->push_back((YapiCommand*) (new PwmInput_set_resolution()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_resolution()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_sensorState()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_dutyCycle()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_pulseDuration()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_frequency()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_period()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_pulseCounter()));
    cmdList->push_back((YapiCommand*) (new PwmInput_get_pwmReportMode()));
    cmdList->push_back((YapiCommand*) (new PwmInput_set_pwmReportMode()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_isSensorReady()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_startDataLogger()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_stopDataLogger()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_get_recordedData()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_calibrateFromPoints()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_loadCalibrationPoints()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_resetCounter()));
    cmdList->push_back((YapiCommand*) (new apifun_PwmInput_get_timedReport()));
  }

//--- (end of PwmInput functions)
