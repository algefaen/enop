/*********************************************************************
 *
 * $Id: YAudioIn.cpp 20797 2015-07-06 16:49:40Z mvuilleu $
 *
 * Implements commands to handle AudioIn functions
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
#include "yocto_audioin.h"

using namespace std;

//--- (YAudioIn definitions)

const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

//--- (end of YAudioIn definitions)

bool   isModule(void)      { return false; }

//--- (YAudioIn implementation)
string YFunctionName(void) { return "AudioIn"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of volume is int (Percent)
// type of mute is int (Bool)
// type of volumeRange is string (ValueRange)
// type of signal is int (Int)
// type of noSignalFor is int (Int)
/**
 * Returns the logical name of the audio input.
 *
 * @return a string corresponding to the logical name of the audio input
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class AudioIn_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the audio input.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
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
 * Changes the logical name of the audio input. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the audio input
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AudioIn_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the audio input.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the audio input", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
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
 * Returns a short string representing the current state of the audio input.
 *
 * @return a string corresponding to a short string representing the current state of the audio input
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class AudioIn_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the audio input.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
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
 * Returns audio input gain, in per cents.
 *
 * @return an integer corresponding to audio input gain, in per cents
 *
 * On failure, throws an exception or returns Y_VOLUME_INVALID.
 */
class AudioIn_get_volume : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_volume";
  }

  string getDescription()
  {
    return "Returns audio input gain, in per cents.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
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
 * Changes audio input gain, in per cents.
 *
 * @param newval : an integer corresponding to audio input gain, in per cents
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AudioIn_set_volume : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_volume";
  }

  string getDescription()
  {
    return "Changes audio input gain, in per cents.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to audio input gain, in per cents", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
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
 * Returns the state of the mute function.
 *
 * @return either Y_MUTE_FALSE or Y_MUTE_TRUE, according to the state of the mute function
 *
 * On failure, throws an exception or returns Y_MUTE_INVALID.
 */
class AudioIn_get_mute : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_mute";
  }

  string getDescription()
  {
    return "Returns the state of the mute function.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_mute();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the state of the mute function. Remember to call the matching module
 * saveToFlash() method to save the setting permanently.
 *
 * @param newval : either Y_MUTE_FALSE or Y_MUTE_TRUE, according to the state of the mute function
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class AudioIn_set_mute : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_mute";
  }

  string getDescription()
  {
    return "Changes the state of the mute function.";
  }

  string getMoreInfo()
  {
    return "Remember to call the matching module saveToFlash() method to save the setting permanently.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE, according to the state of the mute function", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_mute(Y_MUTE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the supported volume range. The low value of the
 * range corresponds to the minimal audible value. To
 * completely mute the sound, use set_mute()
 * instead of the set_volume().
 *
 * @return a string corresponding to the supported volume range
 *
 * On failure, throws an exception or returns Y_VOLUMERANGE_INVALID.
 */
class AudioIn_get_volumeRange : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_volumeRange";
  }

  string getDescription()
  {
    return "Returns the supported volume range.";
  }

  string getMoreInfo()
  {
    return "The low value of the range corresponds to the minimal audible value. To completely mute the sound, use set_mute() instead of the set_volume().";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_volumeRange();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the detected input signal level.
 *
 * @return an integer corresponding to the detected input signal level
 *
 * On failure, throws an exception or returns Y_SIGNAL_INVALID.
 */
class AudioIn_get_signal : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_signal";
  }

  string getDescription()
  {
    return "Returns the detected input signal level.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YAudioIn*>* list = enumerateTargets<YAudioIn>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_signal();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackAudioIn is YAudioInValueCallback* (YAudioInValueCallback)
//--- (end of YAudioIn implementation)

//--- (AudioIn functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YAudioIn>(cmdList);
    cmdList->push_back((YapiCommand*) (new AudioIn_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new AudioIn_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new AudioIn_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new AudioIn_get_volume()));
    cmdList->push_back((YapiCommand*) (new AudioIn_set_volume()));
    cmdList->push_back((YapiCommand*) (new AudioIn_get_mute()));
    cmdList->push_back((YapiCommand*) (new AudioIn_set_mute()));
    cmdList->push_back((YapiCommand*) (new AudioIn_get_volumeRange()));
    cmdList->push_back((YapiCommand*) (new AudioIn_get_signal()));
  }

//--- (end of AudioIn functions)
