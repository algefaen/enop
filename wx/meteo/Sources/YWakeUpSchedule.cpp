/*********************************************************************
 *
 * $Id: YWakeUpSchedule.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle WakeUpSchedule functions
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
#include "yocto_wakeupschedule.h"

using namespace std;

//--- (YWakeUpSchedule definitions)

//--- (end of YWakeUpSchedule definitions)

bool   isModule(void)      { return false; }

//--- (YWakeUpSchedule implementation)
string YFunctionName(void) { return "WakeUpSchedule"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of minutesA is int (MinOfHalfHourBits)
// type of minutesB is int (MinOfHalfHourBits)
// type of hours is int (HoursOfDayBits)
// type of weekDays is int (DaysOfWeekBits)
// type of monthDays is int (DaysOfMonthBits)
// type of months is int (MonthsOfYearBits)
// type of nextOccurence is s64 (UTCTime)
/**
 * Returns the logical name of the wake up schedule.
 *
 * @return a string corresponding to the logical name of the wake up schedule
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class WakeUpSchedule_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the wake up schedule.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
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
 * Changes the logical name of the wake up schedule. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the wake up schedule
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpSchedule_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the wake up schedule.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the wake up schedule", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
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
 * Returns a short string representing the current state of the wake up schedule.
 *
 * @return a string corresponding to a short string representing the current state of the wake up schedule
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class WakeUpSchedule_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the wake up schedule.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
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
 * Returns the minutes in the 00-29 interval of each hour scheduled for wake up.
 *
 * @return an integer corresponding to the minutes in the 00-29 interval of each hour scheduled for wake up
 *
 * On failure, throws an exception or returns Y_MINUTESA_INVALID.
 */
class WakeUpSchedule_get_minutesA : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_minutesA";
  }

  string getDescription()
  {
    return "Returns the minutes in the 00-29 interval of each hour scheduled for wake up.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_minutesA();
        string strval =  bitString("012345678901234567890123456789", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the minutes in the 00-29 interval when a wake up must take place.
 *
 * @param newval : an integer corresponding to the minutes in the 00-29 interval when a wake up must take place
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpSchedule_set_minutesA : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_minutesA";
  }

  string getDescription()
  {
    return "Changes the minutes in the 00-29 interval when a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the minutes in the 00-29 interval when a wake up must take place", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_minutesA(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the minutes in the 30-59 intervalof each hour scheduled for wake up.
 *
 * @return an integer corresponding to the minutes in the 30-59 intervalof each hour scheduled for wake up
 *
 * On failure, throws an exception or returns Y_MINUTESB_INVALID.
 */
class WakeUpSchedule_get_minutesB : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_minutesB";
  }

  string getDescription()
  {
    return "Returns the minutes in the 30-59 intervalof each hour scheduled for wake up.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_minutesB();
        string strval =  bitString("012345678901234567890123456789", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the minutes in the 30-59 interval when a wake up must take place.
 *
 * @param newval : an integer corresponding to the minutes in the 30-59 interval when a wake up must take place
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpSchedule_set_minutesB : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_minutesB";
  }

  string getDescription()
  {
    return "Changes the minutes in the 30-59 interval when a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the minutes in the 30-59 interval when a wake up must take place", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_minutesB(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the hours scheduled for wake up.
 *
 * @return an integer corresponding to the hours scheduled for wake up
 *
 * On failure, throws an exception or returns Y_HOURS_INVALID.
 */
class WakeUpSchedule_get_hours : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_hours";
  }

  string getDescription()
  {
    return "Returns the hours scheduled for wake up.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_hours();
        string strval =  bitString("012345678901234567890123", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the hours when a wake up must take place.
 *
 * @param newval : an integer corresponding to the hours when a wake up must take place
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpSchedule_set_hours : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_hours";
  }

  string getDescription()
  {
    return "Changes the hours when a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the hours when a wake up must take place", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_hours(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the days of the week scheduled for wake up.
 *
 * @return an integer corresponding to the days of the week scheduled for wake up
 *
 * On failure, throws an exception or returns Y_WEEKDAYS_INVALID.
 */
class WakeUpSchedule_get_weekDays : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_weekDays";
  }

  string getDescription()
  {
    return "Returns the days of the week scheduled for wake up.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_weekDays();
        string strval =  bitString("MTWTFSS", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the days of the week when a wake up must take place.
 *
 * @param newval : an integer corresponding to the days of the week when a wake up must take place
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpSchedule_set_weekDays : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_weekDays";
  }

  string getDescription()
  {
    return "Changes the days of the week when a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the days of the week when a wake up must take place", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_weekDays(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the days of the month scheduled for wake up.
 *
 * @return an integer corresponding to the days of the month scheduled for wake up
 *
 * On failure, throws an exception or returns Y_MONTHDAYS_INVALID.
 */
class WakeUpSchedule_get_monthDays : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_monthDays";
  }

  string getDescription()
  {
    return "Returns the days of the month scheduled for wake up.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_monthDays();
        string strval =  bitString("1234567890123456789012345678901", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the days of the month when a wake up must take place.
 *
 * @param newval : an integer corresponding to the days of the month when a wake up must take place
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpSchedule_set_monthDays : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_monthDays";
  }

  string getDescription()
  {
    return "Changes the days of the month when a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the days of the month when a wake up must take place", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_monthDays(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the months scheduled for wake up.
 *
 * @return an integer corresponding to the months scheduled for wake up
 *
 * On failure, throws an exception or returns Y_MONTHS_INVALID.
 */
class WakeUpSchedule_get_months : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_months";
  }

  string getDescription()
  {
    return "Returns the months scheduled for wake up.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_months();
        string strval =  bitString("JFMAMJJASOND", attrval);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the months when a wake up must take place.
 *
 * @param newval : an integer corresponding to the months when a wake up must take place
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class WakeUpSchedule_set_months : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_months";
  }

  string getDescription()
  {
    return "Changes the months when a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the months when a wake up must take place", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_months(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackWakeUpSchedule is YWakeUpScheduleValueCallback* (YWakeUpScheduleValueCallback)
/**
 * Returns all the minutes of each hour that are scheduled for wake up.
 */
class apifun_WakeUpSchedule_get_minutes : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_minutes";
  }

  string getDescription()
  {
    return "Returns all the minutes of each hour that are scheduled for wake up.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 value = (*list)[i]->get_minutes();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes all the minutes where a wake up must take place.
 *
 * @param bitmap : Minutes 00-59 of each hour scheduled for wake up.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_WakeUpSchedule_set_minutes : public YapiCommand /* arguments: bitmap */
{
public:

  string getName()
  {
    return "set_minutes";
  }

  string getDescription()
  {
    return "Changes all the minutes where a wake up must take place.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(S64_ARG, "bitmap", "Minutes 00-59 of each hour scheduled for wake up.", "_S64", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YWakeUpSchedule*>* list = enumerateTargets<YWakeUpSchedule>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_minutes((*args)[0]->get_s64Value());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YWakeUpSchedule implementation)

//--- (WakeUpSchedule functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YWakeUpSchedule>(cmdList);
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_minutesA()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_set_minutesA()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_minutesB()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_set_minutesB()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_hours()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_set_hours()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_weekDays()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_set_weekDays()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_monthDays()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_set_monthDays()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_get_months()));
    cmdList->push_back((YapiCommand*) (new WakeUpSchedule_set_months()));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpSchedule_get_minutes()));
    cmdList->push_back((YapiCommand*) (new apifun_WakeUpSchedule_set_minutes()));
  }

//--- (end of WakeUpSchedule functions)
