/*********************************************************************
 *
 * $Id: YRealTimeClock.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle RealTimeClock functions
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
#include "yocto_realtimeclock.h"

using namespace std;

//--- (YRealTimeClock definitions)

const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

//--- (end of YRealTimeClock definitions)

bool   isModule(void)      { return false; }

//--- (YRealTimeClock implementation)
string YFunctionName(void) { return "Real Time Clock"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of unixTime is s64 (UTCTime)
// type of dateTime is string (Text)
// type of utcOffset is int (Int)
// type of timeSet is int (Bool)
/**
 * Returns the logical name of the clock.
 *
 * @return a string corresponding to the logical name of the clock
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class RealTimeClock_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the clock.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
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
 * Changes the logical name of the clock. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the clock
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class RealTimeClock_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the clock.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the clock", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
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
 * Returns a short string representing the current state of the clock.
 *
 * @return a string corresponding to a short string representing the current state of the clock
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class RealTimeClock_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the clock.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
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
 * Returns the current time in Unix format (number of elapsed seconds since Jan 1st, 1970).
 *
 * @return an integer corresponding to the current time in Unix format (number of elapsed seconds
 * since Jan 1st, 1970)
 *
 * On failure, throws an exception or returns Y_UNIXTIME_INVALID.
 */
class RealTimeClock_get_unixTime : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_unixTime";
  }

  string getDescription()
  {
    return "Returns the current time in Unix format (number of elapsed seconds since Jan 1st, 1970).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_unixTime();
        char buf[64]; snprintf(buf, 64, "%u [s] since Jan 1, 1970", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current time. Time is specifid in Unix format (number of elapsed seconds since Jan 1st, 1970).
 * If current UTC time is known, utcOffset will be automatically adjusted for the new specified time.
 *
 * @param newval : an integer corresponding to the current time
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class RealTimeClock_set_unixTime : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_unixTime";
  }

  string getDescription()
  {
    return "Changes the current time.";
  }

  string getMoreInfo()
  {
    return "Time is specifid in Unix format (number of elapsed seconds since Jan 1st, 1970). If current UTC time is known, utcOffset will be automatically adjusted for the new specified time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(S64_ARG, "newval", "an integer corresponding to the current time", "_S64", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_unixTime(s64((*args)[0]->get_s64Value()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the number of seconds between current time and UTC time (time zone).
 *
 * @return an integer corresponding to the number of seconds between current time and UTC time (time zone)
 *
 * On failure, throws an exception or returns Y_UTCOFFSET_INVALID.
 */
class RealTimeClock_get_utcOffset : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_utcOffset";
  }

  string getDescription()
  {
    return "Returns the number of seconds between current time and UTC time (time zone).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_utcOffset();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the number of seconds between current time and UTC time (time zone).
 * The timezone is automatically rounded to the nearest multiple of 15 minutes.
 * If current UTC time is known, the current time will automatically be updated according to the
 * selected time zone.
 *
 * @param newval : an integer corresponding to the number of seconds between current time and UTC time (time zone)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class RealTimeClock_set_utcOffset : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_utcOffset";
  }

  string getDescription()
  {
    return "Changes the number of seconds between current time and UTC time (time zone).";
  }

  string getMoreInfo()
  {
    return "The timezone is automatically rounded to the nearest multiple of 15 minutes. If current UTC time is known, the current time will automatically be updated according to the selected time zone.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the number of seconds between current time and UTC time (time zone)", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_utcOffset(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns true if the clock has been set, and false otherwise.
 *
 * @return either Y_TIMESET_FALSE or Y_TIMESET_TRUE, according to true if the clock has been set, and
 * false otherwise
 *
 * On failure, throws an exception or returns Y_TIMESET_INVALID.
 */
class RealTimeClock_get_timeSet : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_timeSet";
  }

  string getDescription()
  {
    return "Returns true if the clock has been set, and false otherwise.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRealTimeClock*>* list = enumerateTargets<YRealTimeClock>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_timeSet();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackRealTimeClock is YRealTimeClockValueCallback* (YRealTimeClockValueCallback)
//--- (end of YRealTimeClock implementation)

//--- (RealTimeClock functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YRealTimeClock>(cmdList);
    cmdList->push_back((YapiCommand*) (new RealTimeClock_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new RealTimeClock_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new RealTimeClock_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new RealTimeClock_get_unixTime()));
    cmdList->push_back((YapiCommand*) (new RealTimeClock_set_unixTime()));
    cmdList->push_back((YapiCommand*) (new RealTimeClock_get_utcOffset()));
    cmdList->push_back((YapiCommand*) (new RealTimeClock_set_utcOffset()));
    cmdList->push_back((YapiCommand*) (new RealTimeClock_get_timeSet()));
  }

//--- (end of RealTimeClock functions)
