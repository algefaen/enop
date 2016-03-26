/*********************************************************************
 *
 * $Id: YDataLogger.cpp 20704 2015-06-20 19:43:34Z mvuilleu $
 *
 * Implements commands to handle DataLogger functions
 *
 * - - - - - - - - - License information: - - - - - - - - - 
 *
 * Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 * 1) If you have obtained this file from www.yoctopuce.com,
 *    Yoctopuce Sarl licenses to you (hereafter Licensee) the
 *    right to use, modify, copy, and integrate this source file
 *    into your own solution for the sole purpose of interfacing
 *    a Yoctopuce product with Licensee's solution.
 *
 *    The use of this file and all relationship between Yoctopuce 
 *    and Licensee are governed by Yoctopuce General Terms and 
 *    Conditions.
 *
 *    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING 
 *    WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS 
 *    FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *    EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, 
 *    COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR 
 *    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 *    LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *    CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *    BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *    WARRANTY, OR OTHERWISE.
 *
 * 2) If your intent is not to interface with Yoctopuce products,
 *    you are not entitled to use, read or create any derived
 *    material from this source file.
 *
 *********************************************************************/


#include <stdio.h>
#include "cmdline_common.h"
#include "yocto_api.h"
#include "yocto_datalogger.h"

using namespace std;

//--- (generated code: YDataLogger definitions)

const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

const char *enumOffOnPending[] = {
    "OFF",
    "ON",
    "PENDING",
    NULL
};

//--- (end of generated code: YDataLogger definitions)

bool   isModule(void)      { return false; }

//--- (generated code: YDataLogger implementation)
string YFunctionName(void) { return "DataLogger"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of currentRunIndex is int (UInt31)
// type of timeUTC is s64 (UTCTime)
// type of recording is int (OffOnPending)
// type of autoStart is int (OnOff)
// type of beaconDriven is int (OnOff)
// type of clearHistory is int (Bool)
/**
 * Returns the logical name of the data logger.
 *
 * @return a string corresponding to the logical name of the data logger
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class DataLogger_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the data logger.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
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
 * Changes the logical name of the data logger. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the data logger
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DataLogger_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the data logger.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the data logger", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
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
 * Returns a short string representing the current state of the data logger.
 *
 * @return a string corresponding to a short string representing the current state of the data logger
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class DataLogger_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the data logger.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
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
 * Returns the current run number, corresponding to the number of times the module was
 * powered on with the dataLogger enabled at some point.
 *
 * @return an integer corresponding to the current run number, corresponding to the number of times the module was
 *         powered on with the dataLogger enabled at some point
 *
 * On failure, throws an exception or returns Y_CURRENTRUNINDEX_INVALID.
 */
class DataLogger_get_currentRunIndex : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_currentRunIndex";
  }

  string getDescription()
  {
    return "Returns the current run number, corresponding to the number of times the module waspowered on with the dataLogger enabled at some point.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_currentRunIndex();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the Unix timestamp for current UTC time, if known.
 *
 * @return an integer corresponding to the Unix timestamp for current UTC time, if known
 *
 * On failure, throws an exception or returns Y_TIMEUTC_INVALID.
 */
class DataLogger_get_timeUTC : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_timeUTC";
  }

  string getDescription()
  {
    return "Returns the Unix timestamp for current UTC time, if known.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_timeUTC();
        char buf[64]; snprintf(buf, 64, "%u [s] since Jan 1, 1970", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current UTC time reference used for recorded data.
 *
 * @param newval : an integer corresponding to the current UTC time reference used for recorded data
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DataLogger_set_timeUTC : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_timeUTC";
  }

  string getDescription()
  {
    return "Changes the current UTC time reference used for recorded data.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(S64_ARG, "newval", "an integer corresponding to the current UTC time reference used for recorded data", "_S64", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_timeUTC(s64((*args)[0]->get_s64Value()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the current activation state of the data logger.
 *
 * @return a value among Y_RECORDING_OFF, Y_RECORDING_ON and Y_RECORDING_PENDING corresponding to the
 * current activation state of the data logger
 *
 * On failure, throws an exception or returns Y_RECORDING_INVALID.
 */
class DataLogger_get_recording : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_recording";
  }

  string getDescription()
  {
    return "Returns the current activation state of the data logger.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_recording();
        string strval =  enumString(attrval,enumOffOnPending);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the activation state of the data logger to start/stop recording data.
 *
 * @param newval : a value among Y_RECORDING_OFF, Y_RECORDING_ON and Y_RECORDING_PENDING corresponding
 * to the activation state of the data logger to start/stop recording data
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DataLogger_set_recording : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_recording";
  }

  string getDescription()
  {
    return "Changes the activation state of the data logger to start/stop recording data.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among OFF, ON and PENDING corresponding to the activation state of the data logger to start/stop recording data", "OFF=0,ON=1,PENDING=2", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_recording(Y_RECORDING_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the default activation state of the data logger on power up.
 *
 * @return either Y_AUTOSTART_OFF or Y_AUTOSTART_ON, according to the default activation state of the
 * data logger on power up
 *
 * On failure, throws an exception or returns Y_AUTOSTART_INVALID.
 */
class DataLogger_get_autoStart : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_autoStart";
  }

  string getDescription()
  {
    return "Returns the default activation state of the data logger on power up.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_autoStart();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the default activation state of the data logger on power up.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : either Y_AUTOSTART_OFF or Y_AUTOSTART_ON, according to the default activation state
 * of the data logger on power up
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DataLogger_set_autoStart : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_autoStart";
  }

  string getDescription()
  {
    return "Changes the default activation state of the data logger on power up.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON, according to the default activation state of the data logger on power up", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_autoStart(Y_AUTOSTART_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Return true if the data logger is synchronised with the localization beacon.
 *
 * @return either Y_BEACONDRIVEN_OFF or Y_BEACONDRIVEN_ON
 *
 * On failure, throws an exception or returns Y_BEACONDRIVEN_INVALID.
 */
class DataLogger_get_beaconDriven : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_beaconDriven";
  }

  string getDescription()
  {
    return "Return true if the data logger is synchronised with the localization beacon.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_beaconDriven();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the type of synchronisation of the data logger.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : either Y_BEACONDRIVEN_OFF or Y_BEACONDRIVEN_ON, according to the type of
 * synchronisation of the data logger
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class DataLogger_set_beaconDriven : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_beaconDriven";
  }

  string getDescription()
  {
    return "Changes the type of synchronisation of the data logger.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON, according to the type of synchronisation of the data logger", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_beaconDriven(Y_BEACONDRIVEN_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackDataLogger is YDataLoggerValueCallback* (YDataLoggerValueCallback)
/**
 * Clears the data logger memory and discards all recorded data streams.
 * This method also resets the current run index to zero.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DataLogger_forgetAllDataStreams : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "forgetAllDataStreams";
  }

  string getDescription()
  {
    return "Clears the data logger memory and discards all recorded data streams.";
  }

  string getMoreInfo()
  {
    return "This method also resets the current run index to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->forgetAllDataStreams();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of YDataSet objects that can be used to retrieve
 * all measures stored by the data logger.
 *
 * This function only works if the device uses a recent firmware,
 * as YDataSet objects are not supported by firmwares older than
 * version 13000.
 *
 * @return a list of YDataSet object.
 *
 * On failure, throws an exception or returns an empty list.
 */
class apifun_DataLogger_get_dataSets : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_dataSets";
  }

  string getDescription()
  {
    return "Returns a list of YDataSet objects that can be used to retrieveall measures stored by the data logger.";
  }

  string getMoreInfo()
  {
    return "This function only works if the device uses a recent firmware, as YDataSet objects are not supported by firmwares older than version 13000.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDataLogger*>* list = enumerateTargets<YDataLogger>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<YDataSet> value = (*list)[i]->get_dataSets();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YDataLogger implementation)

//--- (generated code: DataLogger functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YDataLogger>(cmdList);
    cmdList->push_back((YapiCommand*) (new DataLogger_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new DataLogger_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new DataLogger_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new DataLogger_get_currentRunIndex()));
    cmdList->push_back((YapiCommand*) (new DataLogger_get_timeUTC()));
    cmdList->push_back((YapiCommand*) (new DataLogger_set_timeUTC()));
    cmdList->push_back((YapiCommand*) (new DataLogger_get_recording()));
    cmdList->push_back((YapiCommand*) (new DataLogger_set_recording()));
    cmdList->push_back((YapiCommand*) (new DataLogger_get_autoStart()));
    cmdList->push_back((YapiCommand*) (new DataLogger_set_autoStart()));
    cmdList->push_back((YapiCommand*) (new DataLogger_get_beaconDriven()));
    cmdList->push_back((YapiCommand*) (new DataLogger_set_beaconDriven()));
    cmdList->push_back((YapiCommand*) (new apifun_DataLogger_forgetAllDataStreams()));
    cmdList->push_back((YapiCommand*) (new apifun_DataLogger_get_dataSets()));
  }

//--- (end of generated code: DataLogger functions)
