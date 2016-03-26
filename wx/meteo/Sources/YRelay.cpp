/*********************************************************************
 *
 * $Id: YRelay.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle Relay functions
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
#include "yocto_relay.h"

using namespace std;

//--- (YRelay definitions)

const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

const char *enumToggle[] = {
    "A",
    "B",
    NULL
};

const char *enumToggleAtPowerOn[] = {
    "UNCHANGED",
    "A",
    "B",
    NULL
};

//--- (end of YRelay definitions)

bool   isModule(void)      { return false; }

//--- (YRelay implementation)
string YFunctionName(void) { return "Relay"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of state is int (Toggle)
// type of stateAtPowerOn is int (ToggleAtPowerOn)
// type of maxTimeOnStateA is s64 (Time)
// type of maxTimeOnStateB is s64 (Time)
// type of output is int (OnOff)
// type of pulseTimer is s64 (Time)
// type of countdown is s64 (Time)
/**
 * Returns the logical name of the relay.
 *
 * @return a string corresponding to the logical name of the relay
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Relay_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the relay.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
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
 * Changes the logical name of the relay. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the relay
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Relay_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the relay.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the relay", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
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
 * Returns a short string representing the current state of the relay.
 *
 * @return a string corresponding to a short string representing the current state of the relay
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Relay_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the relay.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
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
 * Returns the state of the relays (A for the idle position, B for the active position).
 *
 * @return either Y_STATE_A or Y_STATE_B, according to the state of the relays (A for the idle
 * position, B for the active position)
 *
 * On failure, throws an exception or returns Y_STATE_INVALID.
 */
class Relay_get_state : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_state";
  }

  string getDescription()
  {
    return "Returns the state of the relays (A for the idle position, B for the active position).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_state();
        string strval =  enumString(attrval,enumToggle);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the state of the relays (A for the idle position, B for the active position).
 *
 * @param newval : either Y_STATE_A or Y_STATE_B, according to the state of the relays (A for the idle
 * position, B for the active position)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Relay_set_state : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_state";
  }

  string getDescription()
  {
    return "Changes the state of the relays (A for the idle position, B for the active position).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either A or B, according to the state of the relays (A for the idle position, B for the active position)", "A=0,B=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_state(Y_STATE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the state of the relays at device startup (A for the idle position, B for the active
 * position, UNCHANGED for no change).
 *
 * @return a value among Y_STATEATPOWERON_UNCHANGED, Y_STATEATPOWERON_A and Y_STATEATPOWERON_B
 * corresponding to the state of the relays at device startup (A for the idle position, B for the
 * active position, UNCHANGED for no change)
 *
 * On failure, throws an exception or returns Y_STATEATPOWERON_INVALID.
 */
class Relay_get_stateAtPowerOn : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_stateAtPowerOn";
  }

  string getDescription()
  {
    return "Returns the state of the relays at device startup (A for the idle position, B for the active position, UNCHANGED for no change).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_stateAtPowerOn();
        string strval =  enumString(attrval,enumToggleAtPowerOn);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Preset the state of the relays at device startup (A for the idle position,
 * B for the active position, UNCHANGED for no modification). Remember to call the matching module saveToFlash()
 * method, otherwise this call will have no effect.
 *
 * @param newval : a value among Y_STATEATPOWERON_UNCHANGED, Y_STATEATPOWERON_A and Y_STATEATPOWERON_B
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Relay_set_stateAtPowerOn : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_stateAtPowerOn";
  }

  string getDescription()
  {
    return "Preset the state of the relays at device startup (A for the idle position,B for the active position, UNCHANGED for no modification).";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method, otherwise this call will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among UNCHANGED, A and B", "UNCHANGED=0,A=1,B=2", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_stateAtPowerOn(Y_STATEATPOWERON_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retourne the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state A before automatically
 * switching back in to B state. Zero means no maximum time.
 *
 * @return an integer
 *
 * On failure, throws an exception or returns Y_MAXTIMEONSTATEA_INVALID.
 */
class Relay_get_maxTimeOnStateA : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_maxTimeOnStateA";
  }

  string getDescription()
  {
    return "Retourne the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state A before automatically switching back in to B state.";
  }

  string getMoreInfo()
  {
    return "Zero means no maximum time.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_maxTimeOnStateA();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Sets the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state A before automatically
 * switching back in to B state. Use zero for no maximum time.
 *
 * @param newval : an integer
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Relay_set_maxTimeOnStateA : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_maxTimeOnStateA";
  }

  string getDescription()
  {
    return "Sets the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state A before automatically switching back in to B state.";
  }

  string getMoreInfo()
  {
    return "Use zero for no maximum time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(S64_ARG, "newval", "an integer", "_S64", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_maxTimeOnStateA(s64((*args)[0]->get_s64Value()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Retourne the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state B before automatically
 * switching back in to A state. Zero means no maximum time.
 *
 * @return an integer
 *
 * On failure, throws an exception or returns Y_MAXTIMEONSTATEB_INVALID.
 */
class Relay_get_maxTimeOnStateB : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_maxTimeOnStateB";
  }

  string getDescription()
  {
    return "Retourne the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state B before automatically switching back in to A state.";
  }

  string getMoreInfo()
  {
    return "Zero means no maximum time.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_maxTimeOnStateB();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Sets the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state B before automatically
 * switching back in to A state. Use zero for no maximum time.
 *
 * @param newval : an integer
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Relay_set_maxTimeOnStateB : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_maxTimeOnStateB";
  }

  string getDescription()
  {
    return "Sets the maximum time (ms) allowed for $THEFUNCTIONS$ to stay in state B before automatically switching back in to A state.";
  }

  string getMoreInfo()
  {
    return "Use zero for no maximum time.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(S64_ARG, "newval", "an integer", "_S64", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_maxTimeOnStateB(s64((*args)[0]->get_s64Value()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the output state of the relays, when used as a simple switch (single throw).
 *
 * @return either Y_OUTPUT_OFF or Y_OUTPUT_ON, according to the output state of the relays, when used
 * as a simple switch (single throw)
 *
 * On failure, throws an exception or returns Y_OUTPUT_INVALID.
 */
class Relay_get_output : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_output";
  }

  string getDescription()
  {
    return "Returns the output state of the relays, when used as a simple switch (single throw).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_output();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the output state of the relays, when used as a simple switch (single throw).
 *
 * @param newval : either Y_OUTPUT_OFF or Y_OUTPUT_ON, according to the output state of the relays,
 * when used as a simple switch (single throw)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Relay_set_output : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_output";
  }

  string getDescription()
  {
    return "Changes the output state of the relays, when used as a simple switch (single throw).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON, according to the output state of the relays, when used as a simple switch (single throw)", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_output(Y_OUTPUT_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the number of milliseconds remaining before the relays is returned to idle position
 * (state A), during a measured pulse generation. When there is no ongoing pulse, returns zero.
 *
 * @return an integer corresponding to the number of milliseconds remaining before the relays is
 * returned to idle position
 *         (state A), during a measured pulse generation
 *
 * On failure, throws an exception or returns Y_PULSETIMER_INVALID.
 */
class Relay_get_pulseTimer : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_pulseTimer";
  }

  string getDescription()
  {
    return "Returns the number of milliseconds remaining before the relays is returned to idle position(state A), during a measured pulse generation.";
  }

  string getMoreInfo()
  {
    return "When there is no ongoing pulse, returns zero.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_pulseTimer();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Sets the relay to output B (active) for a specified duration, then brings it
 * automatically back to output A (idle state).
 *
 * @param ms_duration : pulse duration, in millisecondes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_Relay_pulse : public YapiCommand /* arguments: ms_duration */
{
public:

  string getName()
  {
    return "pulse";
  }

  string getDescription()
  {
    return "Sets the relay to output B (active) for a specified duration, then brings itautomatically back to output A (idle state).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "pulse duration, in millisecondes", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->pulse((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Schedules a pulse.
 *
 * @param ms_delay : waiting time before the pulse, in millisecondes
 * @param ms_duration : pulse duration, in millisecondes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_Relay_delayedPulse : public YapiCommand /* arguments: ms_delay ms_duration */
{
public:

  string getName()
  {
    return "delayedPulse";
  }

  string getDescription()
  {
    return "Schedules a pulse.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "ms_delay", "waiting time before the pulse, in millisecondes", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "pulse duration, in millisecondes", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->delayedPulse((int)(*args)[0]->get_intValue(),
                                 (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the number of milliseconds remaining before a pulse (delayedPulse() call)
 * When there is no scheduled pulse, returns zero.
 *
 * @return an integer corresponding to the number of milliseconds remaining before a pulse (delayedPulse() call)
 *         When there is no scheduled pulse, returns zero
 *
 * On failure, throws an exception or returns Y_COUNTDOWN_INVALID.
 */
class Relay_get_countdown : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_countdown";
  }

  string getDescription()
  {
    return "Returns the number of milliseconds remaining before a pulse (delayedPulse() call)When there is no scheduled pulse, returns zero.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRelay*>* list = enumerateTargets<YRelay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_countdown();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackRelay is YRelayValueCallback* (YRelayValueCallback)
//--- (end of YRelay implementation)

//--- (Relay functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YRelay>(cmdList);
    cmdList->push_back((YapiCommand*) (new Relay_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new Relay_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new Relay_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new Relay_get_state()));
    cmdList->push_back((YapiCommand*) (new Relay_set_state()));
    cmdList->push_back((YapiCommand*) (new Relay_get_stateAtPowerOn()));
    cmdList->push_back((YapiCommand*) (new Relay_set_stateAtPowerOn()));
    cmdList->push_back((YapiCommand*) (new Relay_get_maxTimeOnStateA()));
    cmdList->push_back((YapiCommand*) (new Relay_set_maxTimeOnStateA()));
    cmdList->push_back((YapiCommand*) (new Relay_get_maxTimeOnStateB()));
    cmdList->push_back((YapiCommand*) (new Relay_set_maxTimeOnStateB()));
    cmdList->push_back((YapiCommand*) (new Relay_get_output()));
    cmdList->push_back((YapiCommand*) (new Relay_set_output()));
    cmdList->push_back((YapiCommand*) (new Relay_get_pulseTimer()));
    cmdList->push_back((YapiCommand*) (new alias_Relay_pulse()));
    cmdList->push_back((YapiCommand*) (new alias_Relay_delayedPulse()));
    cmdList->push_back((YapiCommand*) (new Relay_get_countdown()));
  }

//--- (end of Relay functions)
