/*********************************************************************
 *
 * $Id: YModule.cpp 20908 2015-07-23 06:46:26Z seb $
 *
 * Implements commands to handle Module functions
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

using namespace std;

//--- (generated code: YModule definitions)

const char *enumOnOff[] = {
    "OFF",
    "ON",
    NULL
};

const char *enumFlashSettings[] = {
    "LOADED",
    "SAVED",
    "MODIFIED",
    NULL
};

//--- (end of generated code: YModule definitions)

bool   isModule(void)      { return true; }

//--- (generated code: YModule implementation)
string YFunctionName(void) { return "Module control interface"; }

// type of productName is string (Text)
// type of serialNumber is string (Text)
// type of logicalName is string (Text)
// type of productId is int (XWord)
// type of productRelease is int (XWord)
// type of firmwareRelease is string (Text)
// type of persistentSettings is int (FlashSettings)
// type of luminosity is int (Percent)
// type of beacon is int (OnOff)
// type of upTime is s64 (Time)
// type of usbCurrent is int (UsedCurrent)
// type of rebootCountdown is int (Int)
// type of userVar is int (Int)
/**
 * Returns the commercial name of the module, as set by the factory.
 *
 * @return a string corresponding to the commercial name of the module, as set by the factory
 *
 * On failure, throws an exception or returns Y_PRODUCTNAME_INVALID.
 */
class Module_get_productName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_productName";
  }

  string getDescription()
  {
    return "Returns the commercial name of the module, as set by the factory.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_productName();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the serial number of the module, as set by the factory.
 *
 * @return a string corresponding to the serial number of the module, as set by the factory
 *
 * On failure, throws an exception or returns Y_SERIALNUMBER_INVALID.
 */
class Module_get_serialNumber : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_serialNumber";
  }

  string getDescription()
  {
    return "Returns the serial number of the module, as set by the factory.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_serialNumber();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the logical name of the module.
 *
 * @return a string corresponding to the logical name of the module
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Module_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
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
 * Changes the logical name of the module. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the module
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the module.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the module", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
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
 * Returns the USB device identifier of the module.
 *
 * @return an integer corresponding to the USB device identifier of the module
 *
 * On failure, throws an exception or returns Y_PRODUCTID_INVALID.
 */
class Module_get_productId : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_productId";
  }

  string getDescription()
  {
    return "Returns the USB device identifier of the module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_productId();
        char buf[32]; snprintf(buf,32,"0x%04x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the hardware release version of the module.
 *
 * @return an integer corresponding to the hardware release version of the module
 *
 * On failure, throws an exception or returns Y_PRODUCTRELEASE_INVALID.
 */
class Module_get_productRelease : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_productRelease";
  }

  string getDescription()
  {
    return "Returns the hardware release version of the module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_productRelease();
        char buf[32]; snprintf(buf,32,"0x%04x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the version of the firmware embedded in the module.
 *
 * @return a string corresponding to the version of the firmware embedded in the module
 *
 * On failure, throws an exception or returns Y_FIRMWARERELEASE_INVALID.
 */
class Module_get_firmwareRelease : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_firmwareRelease";
  }

  string getDescription()
  {
    return "Returns the version of the firmware embedded in the module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_firmwareRelease();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current state of persistent module settings.
 *
 * @return a value among Y_PERSISTENTSETTINGS_LOADED, Y_PERSISTENTSETTINGS_SAVED and
 * Y_PERSISTENTSETTINGS_MODIFIED corresponding to the current state of persistent module settings
 *
 * On failure, throws an exception or returns Y_PERSISTENTSETTINGS_INVALID.
 */
class Module_get_persistentSettings : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_persistentSettings";
  }

  string getDescription()
  {
    return "Returns the current state of persistent module settings.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_persistentSettings();
        string strval =  enumString(attrval,enumFlashSettings);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the luminosity of the  module informative leds (from 0 to 100).
 *
 * @return an integer corresponding to the luminosity of the  module informative leds (from 0 to 100)
 *
 * On failure, throws an exception or returns Y_LUMINOSITY_INVALID.
 */
class Module_get_luminosity : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_luminosity";
  }

  string getDescription()
  {
    return "Returns the luminosity of the module informative leds (from 0 to 100).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_luminosity();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the luminosity of the module informative leds. The parameter is a
 * value between 0 and 100.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : an integer corresponding to the luminosity of the module informative leds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_luminosity : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_luminosity";
  }

  string getDescription()
  {
    return "Changes the luminosity of the module informative leds.";
  }

  string getMoreInfo()
  {
    return "The parameter is a value between 0 and 100. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the luminosity of the module informative leds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_luminosity(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the state of the localization beacon.
 *
 * @return either Y_BEACON_OFF or Y_BEACON_ON, according to the state of the localization beacon
 *
 * On failure, throws an exception or returns Y_BEACON_INVALID.
 */
class Module_get_beacon : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_beacon";
  }

  string getDescription()
  {
    return "Returns the state of the localization beacon.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_beacon();
        string strval =  enumString(attrval,enumOnOff);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Turns on or off the module localization beacon.
 *
 * @param newval : either Y_BEACON_OFF or Y_BEACON_ON
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_beacon : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_beacon";
  }

  string getDescription()
  {
    return "Turns on or off the module localization beacon.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either OFF or ON", "OFF=0,ON=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_beacon(Y_BEACON_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the number of milliseconds spent since the module was powered on.
 *
 * @return an integer corresponding to the number of milliseconds spent since the module was powered on
 *
 * On failure, throws an exception or returns Y_UPTIME_INVALID.
 */
class Module_get_upTime : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_upTime";
  }

  string getDescription()
  {
    return "Returns the number of milliseconds spent since the module was powered on.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        s64 attrval = (*list)[i]->get_upTime();
        char buf[32]; snprintf(buf, 32, "%u [ms]", (u32)attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the current consumed by the module on the USB bus, in milli-amps.
 *
 * @return an integer corresponding to the current consumed by the module on the USB bus, in milli-amps
 *
 * On failure, throws an exception or returns Y_USBCURRENT_INVALID.
 */
class Module_get_usbCurrent : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_usbCurrent";
  }

  string getDescription()
  {
    return "Returns the current consumed by the module on the USB bus, in milli-amps.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_usbCurrent();
        char buf[32]; snprintf(buf, 32, "%d [mA]", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the remaining number of seconds before the module restarts, or zero when no
 * reboot has been scheduled.
 *
 * @return an integer corresponding to the remaining number of seconds before the module restarts, or zero when no
 *         reboot has been scheduled
 *
 * On failure, throws an exception or returns Y_REBOOTCOUNTDOWN_INVALID.
 */
class Module_get_rebootCountdown : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_rebootCountdown";
  }

  string getDescription()
  {
    return "Returns the remaining number of seconds before the module restarts, or zero when noreboot has been scheduled.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rebootCountdown();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the value previously stored in this attribute.
 * On startup and after a device reboot, the value is always reset to zero.
 *
 * @return an integer corresponding to the value previously stored in this attribute
 *
 * On failure, throws an exception or returns Y_USERVAR_INVALID.
 */
class Module_get_userVar : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_userVar";
  }

  string getDescription()
  {
    return "Returns the value previously stored in this attribute.";
  }

  string getMoreInfo()
  {
    return "On startup and after a device reboot, the value is always reset to zero.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_userVar();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the value previously stored in this attribute.
 * On startup and after a device reboot, the value is always reset to zero.
 *
 * @param newval : an integer
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Module_set_userVar : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_userVar";
  }

  string getDescription()
  {
    return "Returns the value previously stored in this attribute.";
  }

  string getMoreInfo()
  {
    return "On startup and after a device reboot, the value is always reset to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_userVar(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackModule is YModuleValueCallback* (YModuleValueCallback)
// type of logCallback is YModuleLogCallback* (YModuleLogCallback)
/**
 * Saves current settings in the nonvolatile memory of the module.
 * Warning: the number of allowed save operations during a module life is
 * limited (about 100000 cycles). Do not call this function within a loop.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_saveToFlash : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "saveToFlash";
  }

  string getDescription()
  {
    return "Saves current settings in the nonvolatile memory of the module.";
  }

  string getMoreInfo()
  {
    return "Warning: the number of allowed save operations during a module life is limited (about 100000 cycles). Do not call this function within a loop.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->saveToFlash();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reloads the settings stored in the nonvolatile memory, as
 * when the module is powered on.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_revertFromFlash : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "revertFromFlash";
  }

  string getDescription()
  {
    return "Reloads the settings stored in the nonvolatile memory, aswhen the module is powered on.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->revertFromFlash();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Schedules a simple module reboot after the given number of seconds.
 *
 * @param secBeforeReboot : number of seconds before rebooting
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_reboot : public YapiCommand /* arguments: secBeforeReboot */
{
public:

  string getName()
  {
    return "reboot";
  }

  string getDescription()
  {
    return "Schedules a simple module reboot after the given number of seconds.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "secBeforeReboot", "number of seconds before rebooting", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->reboot((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Schedules a module reboot into special firmware update mode.
 *
 * @param secBeforeReboot : number of seconds before rebooting
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_triggerFirmwareUpdate : public YapiCommand /* arguments: secBeforeReboot */
{
public:

  string getName()
  {
    return "triggerFirmwareUpdate";
  }

  string getDescription()
  {
    return "Schedules a module reboot into special firmware update mode.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "secBeforeReboot", "number of seconds before rebooting", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->triggerFirmwareUpdate((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Tests whether the byn file is valid for this module. This method is useful to test if the module
 * needs to be updated.
 * It is possible to pass a directory as argument instead of a file. In this case, this method returns
 * the path of the most recent
 * appropriate byn file. If the parameter onlynew is true, the function discards firmware that are
 * older or equal to
 * the installed firmware.
 *
 * @param path    : the path of a byn file or a directory that contains byn files
 * @param onlynew : returns only files that are strictly newer
 *
 * @return : the path of the byn file to use or a empty string if no byn files matches the requirement
 *
 * On failure, throws an exception or returns a string that start with "error:".
 */
class apifun_Module_checkFirmware : public YapiCommand /* arguments: path onlynew */
{
public:

  string getName()
  {
    return "checkFirmware";
  }

  string getDescription()
  {
    return "Tests whether the byn file is valid for this module.";
  }

  string getMoreInfo()
  {
    return "This method is useful to test if the module needs to be updated. It is possible to pass a directory as argument instead of a file. In this case, this method returns the path of the most recent appropriate byn file. If the parameter onlynew is true, the function discards firmware that are older or equal to the installed firmware.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "path", "the path of a byn file or a directory that contains byn files", "_STRING", false));
    res->push_back(new ArgumentDesc(BOOL_ARG, "onlynew", "returns only files that are strictly newer", "_BOOL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->checkFirmware((*args)[0]->get_stringValue(),
                                                 (bool)(*args)[1]->get_boolValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Prepares a firmware update of the module. This method returns a YFirmwareUpdate object which
 * handles the firmware update process.
 *
 * @param path : the path of the byn file to use.
 *
 * @return : A YFirmwareUpdate object.
 */
class apifun_Module_updateFirmware : public YapiCommand /* arguments: path */
{
public:

  string getName()
  {
    return "updateFirmware";
  }

  string getDescription()
  {
    return "Prepares a firmware update of the module.";
  }

  string getMoreInfo()
  {
    return "This method returns a YFirmwareUpdate object which handles the firmware update process.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "path", "the path of the byn file to use.", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YFirmwareUpdate value = (*list)[i]->updateFirmware((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns all the settings of the module. Useful to backup all the logical names and calibrations parameters
 * of a connected module.
 *
 * @return a binary buffer with all the settings.
 *
 * On failure, throws an exception or returns  YAPI_INVALID_STRING.
 */
class apifun_Module_get_allSettings : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_allSettings";
  }

  string getDescription()
  {
    return "Returns all the settings of the module.";
  }

  string getMoreInfo()
  {
    return "Useful to backup all the logical names and calibrations parameters of a connected module.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_allSettings();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Restores all the settings of the module. Useful to restore all the logical names and calibrations parameters
 * of a module from a backup.Remember to call the saveToFlash() method of the module if the
 * modifications must be kept.
 *
 * @param settings : a binary buffer with all the settings.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Module_set_allSettings : public YapiCommand /* arguments: settings */
{
public:

  string getName()
  {
    return "set_allSettings";
  }

  string getDescription()
  {
    return "Restores all the settings of the module.";
  }

  string getMoreInfo()
  {
    return "Useful to restore all the logical names and calibrations parameters of a module from a backup.Remember to call \"YModule {target} saveToFlash\" if the modifications must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(BIN_ARG, "settings", "a binary buffer with all the settings.", "_BIN", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_allSettings((*args)[0]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Downloads the specified built-in file and returns a binary buffer with its content.
 *
 * @param pathname : name of the new file to load
 *
 * @return a binary buffer with the file content
 *
 * On failure, throws an exception or returns  YAPI_INVALID_STRING.
 */
class apifun_Module_download : public YapiCommand /* arguments: pathname */
{
public:

  string getName()
  {
    return "download";
  }

  string getDescription()
  {
    return "Downloads the specified built-in file and returns a binary buffer with its content.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pathname", "name of the new file to load", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->download((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the icon of the module. The icon is a PNG image and does not
 * exceeds 1536 bytes.
 *
 * @return a binary buffer with module icon, in png format.
 *         On failure, throws an exception or returns  YAPI_INVALID_STRING.
 */
class apifun_Module_get_icon2d : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_icon2d";
  }

  string getDescription()
  {
    return "Returns the icon of the module.";
  }

  string getMoreInfo()
  {
    return "The icon is a PNG image and does not exceeds 1536 bytes.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_icon2d();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a string with last logs of the module. This method return only
 * logs that are still in the module.
 *
 * @return a string with last logs of the module.
 *         On failure, throws an exception or returns  YAPI_INVALID_STRING.
 */
class apifun_Module_get_lastLogs : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_lastLogs";
  }

  string getDescription()
  {
    return "Returns a string with last logs of the module.";
  }

  string getMoreInfo()
  {
    return "This method return only logs that are still in the module.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YModule*>* list = enumerateTargets<YModule>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_lastLogs();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YModule implementation)

//--- (generated code: Module functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YModule>(cmdList);
    cmdList->push_back((YapiCommand*) (new Module_get_productName()));
    cmdList->push_back((YapiCommand*) (new Module_get_serialNumber()));
    cmdList->push_back((YapiCommand*) (new Module_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new Module_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new Module_get_productId()));
    cmdList->push_back((YapiCommand*) (new Module_get_productRelease()));
    cmdList->push_back((YapiCommand*) (new Module_get_firmwareRelease()));
    cmdList->push_back((YapiCommand*) (new Module_get_persistentSettings()));
    cmdList->push_back((YapiCommand*) (new Module_get_luminosity()));
    cmdList->push_back((YapiCommand*) (new Module_set_luminosity()));
    cmdList->push_back((YapiCommand*) (new Module_get_beacon()));
    cmdList->push_back((YapiCommand*) (new Module_set_beacon()));
    cmdList->push_back((YapiCommand*) (new Module_get_upTime()));
    cmdList->push_back((YapiCommand*) (new Module_get_usbCurrent()));
    cmdList->push_back((YapiCommand*) (new Module_get_rebootCountdown()));
    cmdList->push_back((YapiCommand*) (new Module_get_userVar()));
    cmdList->push_back((YapiCommand*) (new Module_set_userVar()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_saveToFlash()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_revertFromFlash()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_reboot()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_triggerFirmwareUpdate()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_checkFirmware()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_updateFirmware()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_allSettings()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_set_allSettings()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_download()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_icon2d()));
    cmdList->push_back((YapiCommand*) (new apifun_Module_get_lastLogs()));
  }

//--- (end of generated code: Module functions)
