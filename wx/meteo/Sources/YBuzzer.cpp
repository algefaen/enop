/*********************************************************************
 *
 * $Id: YBuzzer.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle Buzzer functions
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
#include "yocto_buzzer.h"

using namespace std;

//--- (YBuzzer definitions)

//--- (end of YBuzzer definitions)

bool   isModule(void)      { return false; }

//--- (YBuzzer implementation)
string YFunctionName(void) { return "Buzzer"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of frequency is double (MeasureVal)
// type of volume is int (Percent)
// type of playSeqSize is int (UInt31)
// type of playSeqMaxSize is int (UInt31)
// type of playSeqSignature is int (UInt31)
// type of command is string (Text)
/**
 * Returns the logical name of the buzzer.
 *
 * @return a string corresponding to the logical name of the buzzer
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Buzzer_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the buzzer.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
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
 * Changes the logical name of the buzzer. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the buzzer
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Buzzer_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the buzzer.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the buzzer", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
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
 * Returns a short string representing the current state of the buzzer.
 *
 * @return a string corresponding to a short string representing the current state of the buzzer
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Buzzer_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the buzzer.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
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
 * Changes the frequency of the signal sent to the buzzer. A zero value stops the buzzer.
 *
 * @param newval : a floating point number corresponding to the frequency of the signal sent to the buzzer
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Buzzer_set_frequency : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_frequency";
  }

  string getDescription()
  {
    return "Changes the frequency of the signal sent to the buzzer.";
  }

  string getMoreInfo()
  {
    return "A zero value stops the buzzer.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the frequency of the signal sent to the buzzer", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
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
 * Returns the  frequency of the signal sent to the buzzer/speaker.
 *
 * @return a floating point number corresponding to the  frequency of the signal sent to the buzzer/speaker
 *
 * On failure, throws an exception or returns Y_FREQUENCY_INVALID.
 */
class Buzzer_get_frequency : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_frequency";
  }

  string getDescription()
  {
    return "Returns the frequency of the signal sent to the buzzer/speaker.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
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
 * Returns the volume of the signal sent to the buzzer/speaker.
 *
 * @return an integer corresponding to the volume of the signal sent to the buzzer/speaker
 *
 * On failure, throws an exception or returns Y_VOLUME_INVALID.
 */
class Buzzer_get_volume : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_volume";
  }

  string getDescription()
  {
    return "Returns the volume of the signal sent to the buzzer/speaker.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_volume();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the volume of the signal sent to the buzzer/speaker.
 *
 * @param newval : an integer corresponding to the volume of the signal sent to the buzzer/speaker
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Buzzer_set_volume : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_volume";
  }

  string getDescription()
  {
    return "Changes the volume of the signal sent to the buzzer/speaker.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the volume of the signal sent to the buzzer/speaker", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_volume(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the playing sequence signature. As playing
 * sequences cannot be read from the device, this can be used
 * to detect if a specific playing sequence is already
 * programmed.
 *
 * @return an integer corresponding to the playing sequence signature
 *
 * On failure, throws an exception or returns Y_PLAYSEQSIGNATURE_INVALID.
 */
class Buzzer_get_playSeqSignature : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_playSeqSignature";
  }

  string getDescription()
  {
    return "Returns the playing sequence signature.";
  }

  string getMoreInfo()
  {
    return "As playing sequences cannot be read from the device, this can be used to detect if a specific playing sequence is already programmed.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_playSeqSignature();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackBuzzer is YBuzzerValueCallback* (YBuzzerValueCallback)
/**
 * Adds a new frequency transition to the playing sequence.
 *
 * @param freq    : desired frequency when the transition is completed, in Hz
 * @param msDelay : duration of the frequency transition, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_addFreqMoveToPlaySeq : public YapiCommand /* arguments: freq msDelay */
{
public:

  string getName()
  {
    return "addFreqMoveToPlaySeq";
  }

  string getDescription()
  {
    return "Adds a new frequency transition to the playing sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "freq", "desired frequency when the transition is completed, in Hz", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "msDelay", "duration of the frequency transition, in milliseconds.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addFreqMoveToPlaySeq((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds a pulse to the playing sequence.
 *
 * @param freq : pulse frequency, in Hz
 * @param msDuration : pulse duration, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_addPulseToPlaySeq : public YapiCommand /* arguments: freq msDuration */
{
public:

  string getName()
  {
    return "addPulseToPlaySeq";
  }

  string getDescription()
  {
    return "Adds a pulse to the playing sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "freq", "pulse frequency, in Hz", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "msDuration", "pulse duration, in milliseconds.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addPulseToPlaySeq((int)(*args)[0]->get_intValue(),
                                      (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Adds a new volume transition to the playing sequence. Frequency stays untouched:
 * if frequency is at zero, the transition has no effect.
 *
 * @param volume    : desired volume when the transition is completed, as a percentage.
 * @param msDuration : duration of the volume transition, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_addVolMoveToPlaySeq : public YapiCommand /* arguments: volume msDuration */
{
public:

  string getName()
  {
    return "addVolMoveToPlaySeq";
  }

  string getDescription()
  {
    return "Adds a new volume transition to the playing sequence.";
  }

  string getMoreInfo()
  {
    return "Frequency stays untouched: if frequency is at zero, the transition has no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "volume", "desired volume when the transition is completed, as a percentage.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "msDuration", "duration of the volume transition, in milliseconds.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addVolMoveToPlaySeq((int)(*args)[0]->get_intValue(),
                                        (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the preprogrammed playing sequence. The sequence
 * runs in loop until it is stopped by stopPlaySeq or an explicit
 * change.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_startPlaySeq : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "startPlaySeq";
  }

  string getDescription()
  {
    return "Starts the preprogrammed playing sequence.";
  }

  string getMoreInfo()
  {
    return "The sequence runs in loop until it is stopped by stopPlaySeq or an explicit change.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->startPlaySeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the preprogrammed playing sequence and sets the frequency to zero.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_stopPlaySeq : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "stopPlaySeq";
  }

  string getDescription()
  {
    return "Stops the preprogrammed playing sequence and sets the frequency to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->stopPlaySeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Resets the preprogrammed playing sequence and sets the frequency to zero.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_resetPlaySeq : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "resetPlaySeq";
  }

  string getDescription()
  {
    return "Resets the preprogrammed playing sequence and sets the frequency to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetPlaySeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Activates the buzzer for a short duration.
 *
 * @param frequency : pulse frequency, in hertz
 * @param duration : pulse duration in millseconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_pulse : public YapiCommand /* arguments: frequency duration */
{
public:

  string getName()
  {
    return "pulse";
  }

  string getDescription()
  {
    return "Activates the buzzer for a short duration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "frequency", "pulse frequency, in hertz", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "duration", "pulse duration in millseconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->pulse((int)(*args)[0]->get_intValue(),
                          (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Makes the buzzer frequency change over a period of time.
 *
 * @param frequency : frequency to reach, in hertz. A frequency under 25Hz stops the buzzer.
 * @param duration :  pulse duration in millseconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_freqMove : public YapiCommand /* arguments: frequency duration */
{
public:

  string getName()
  {
    return "freqMove";
  }

  string getDescription()
  {
    return "Makes the buzzer frequency change over a period of time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "frequency", "frequency to reach, in hertz. A frequency under 25Hz stops the buzzer.", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "duration", "pulse duration in millseconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->freqMove((int)(*args)[0]->get_intValue(),
                             (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Makes the buzzer volume change over a period of time, frequency  stays untouched.
 *
 * @param volume : volume to reach in %
 * @param duration : change duration in millseconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Buzzer_volumeMove : public YapiCommand /* arguments: volume duration */
{
public:

  string getName()
  {
    return "volumeMove";
  }

  string getDescription()
  {
    return "Makes the buzzer volume change over a period of time, frequency stays untouched.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "volume", "volume to reach in %", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "duration", "change duration in millseconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBuzzer*>* list = enumerateTargets<YBuzzer>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->volumeMove((int)(*args)[0]->get_intValue(),
                               (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YBuzzer implementation)

//--- (Buzzer functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YBuzzer>(cmdList);
    cmdList->push_back((YapiCommand*) (new Buzzer_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new Buzzer_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new Buzzer_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new Buzzer_set_frequency()));
    cmdList->push_back((YapiCommand*) (new Buzzer_get_frequency()));
    cmdList->push_back((YapiCommand*) (new Buzzer_get_volume()));
    cmdList->push_back((YapiCommand*) (new Buzzer_set_volume()));
    cmdList->push_back((YapiCommand*) (new Buzzer_get_playSeqSignature()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_addFreqMoveToPlaySeq()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_addPulseToPlaySeq()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_addVolMoveToPlaySeq()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_startPlaySeq()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_stopPlaySeq()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_resetPlaySeq()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_pulse()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_freqMove()));
    cmdList->push_back((YapiCommand*) (new apifun_Buzzer_volumeMove()));
  }

//--- (end of Buzzer functions)
