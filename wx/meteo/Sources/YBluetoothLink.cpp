/*********************************************************************
 *
 * $Id: YBluetoothLink.cpp 20644 2015-06-12 16:04:33Z seb $
 *
 * Implements commands to handle BluetoothLink functions
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
#include "yocto_bluetoothlink.h"

using namespace std;

//--- (YBluetoothLink definitions)

const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

const char *enumBtState[] = {
    "DOWN",
    "FREE",
    "SEARCH",
    "EXISTS",
    "LINKED",
    "PLAY",
    NULL
};

//--- (end of YBluetoothLink definitions)

bool   isModule(void)      { return false; }

//--- (YBluetoothLink implementation)
string YFunctionName(void) { return "BluetoothLink"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of ownAddress is string (MACAddress)
// type of pairingPin is string (Text)
// type of remoteAddress is string (MACAddress)
// type of remoteName is string (Text)
// type of mute is int (Bool)
// type of preAmplifier is int (Percent)
// type of volume is int (Percent)
// type of linkState is int (BtState)
// type of linkQuality is int (Percent)
// type of command is string (Text)
/**
 * Returns the logical name of the cellular interface.
 *
 * @return a string corresponding to the logical name of the cellular interface
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class BluetoothLink_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the cellular interface.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
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
 * Changes the logical name of the cellular interface. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the cellular interface
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class BluetoothLink_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the cellular interface.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the cellular interface", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
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
 * Returns a short string representing the current state of the cellular interface.
 *
 * @return a string corresponding to a short string representing the current state of the cellular interface
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class BluetoothLink_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the cellular interface.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
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
 * Returns the MAC-48 address of the bluetooth interface, which is unique on the bluetooth network.
 *
 * @return a string corresponding to the MAC-48 address of the bluetooth interface, which is unique on
 * the bluetooth network
 *
 * On failure, throws an exception or returns Y_OWNADDRESS_INVALID.
 */
class BluetoothLink_get_ownAddress : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_ownAddress";
  }

  string getDescription()
  {
    return "Returns the MAC-48 address of the bluetooth interface, which is unique on the bluetooth network.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_ownAddress();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns an opaque string if a PIN code has been configured in the device to access
 * the SIM card, or an empty string if none has been configured or if the code provided
 * was rejected by the SIM card.
 *
 * @return a string corresponding to an opaque string if a PIN code has been configured in the device to access
 *         the SIM card, or an empty string if none has been configured or if the code provided
 *         was rejected by the SIM card
 *
 * On failure, throws an exception or returns Y_PAIRINGPIN_INVALID.
 */
class BluetoothLink_get_pairingPin : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_pairingPin";
  }

  string getDescription()
  {
    return "Returns an opaque string if a PIN code has been configured in the device to access the SIM card, or an empty string if none has been configured or if the code providedwas rejected by the SIM card.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_pairingPin();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the PIN code used by the module for bluetooth pairing.
 * Remember to call the saveToFlash() method of the module to save the
 * new value in the device flash.
 *
 * @param newval : a string corresponding to the PIN code used by the module for bluetooth pairing
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class BluetoothLink_set_pairingPin : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_pairingPin";
  }

  string getDescription()
  {
    return "Changes the PIN code used by the module for bluetooth pairing.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" to save the new value in the device flash.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the PIN code used by the module for bluetooth pairing", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_pairingPin(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the MAC-48 address of the remote device to connect to.
 *
 * @return a string corresponding to the MAC-48 address of the remote device to connect to
 *
 * On failure, throws an exception or returns Y_REMOTEADDRESS_INVALID.
 */
class BluetoothLink_get_remoteAddress : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_remoteAddress";
  }

  string getDescription()
  {
    return "Returns the MAC-48 address of the remote device to connect to.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_remoteAddress();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the MAC-48 address defining which remote device to connect to.
 *
 * @param newval : a string corresponding to the MAC-48 address defining which remote device to connect to
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class BluetoothLink_set_remoteAddress : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_remoteAddress";
  }

  string getDescription()
  {
    return "Changes the MAC-48 address defining which remote device to connect to.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the MAC-48 address defining which remote device to connect to", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_remoteAddress(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the bluetooth name the remote device, if found on the bluetooth network.
 *
 * @return a string corresponding to the bluetooth name the remote device, if found on the bluetooth network
 *
 * On failure, throws an exception or returns Y_REMOTENAME_INVALID.
 */
class BluetoothLink_get_remoteName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_remoteName";
  }

  string getDescription()
  {
    return "Returns the bluetooth name the remote device, if found on the bluetooth network.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_remoteName();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
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
class BluetoothLink_get_mute : public YapiCommand /* arguments: */
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
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
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
class BluetoothLink_set_mute : public YapiCommand /* arguments: newval */
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
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
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
 * Returns the audio pre-amplifier volume, in per cents.
 *
 * @return an integer corresponding to the audio pre-amplifier volume, in per cents
 *
 * On failure, throws an exception or returns Y_PREAMPLIFIER_INVALID.
 */
class BluetoothLink_get_preAmplifier : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_preAmplifier";
  }

  string getDescription()
  {
    return "Returns the audio pre-amplifier volume, in per cents.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_preAmplifier();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the audio pre-amplifier volume, in per cents.
 *
 * @param newval : an integer corresponding to the audio pre-amplifier volume, in per cents
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class BluetoothLink_set_preAmplifier : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_preAmplifier";
  }

  string getDescription()
  {
    return "Changes the audio pre-amplifier volume, in per cents.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the audio pre-amplifier volume, in per cents", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_preAmplifier(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the connected headset volume, in per cents.
 *
 * @return an integer corresponding to the connected headset volume, in per cents
 *
 * On failure, throws an exception or returns Y_VOLUME_INVALID.
 */
class BluetoothLink_get_volume : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_volume";
  }

  string getDescription()
  {
    return "Returns the connected headset volume, in per cents.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
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
 * Changes the connected headset volume, in per cents.
 *
 * @param newval : an integer corresponding to the connected headset volume, in per cents
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class BluetoothLink_set_volume : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_volume";
  }

  string getDescription()
  {
    return "Changes the connected headset volume, in per cents.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the connected headset volume, in per cents", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
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
 * Returns the bluetooth link state.
 *
 * @return a value among Y_LINKSTATE_DOWN, Y_LINKSTATE_FREE, Y_LINKSTATE_SEARCH, Y_LINKSTATE_EXISTS,
 * Y_LINKSTATE_LINKED and Y_LINKSTATE_PLAY corresponding to the bluetooth link state
 *
 * On failure, throws an exception or returns Y_LINKSTATE_INVALID.
 */
class BluetoothLink_get_linkState : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_linkState";
  }

  string getDescription()
  {
    return "Returns the bluetooth link state.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_linkState();
        string strval =  enumString(attrval,enumBtState);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the bluetooth receiver signal strength, in pourcents, or 0 if no connection is established.
 *
 * @return an integer corresponding to the bluetooth receiver signal strength, in pourcents, or 0 if
 * no connection is established
 *
 * On failure, throws an exception or returns Y_LINKQUALITY_INVALID.
 */
class BluetoothLink_get_linkQuality : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_linkQuality";
  }

  string getDescription()
  {
    return "Returns the bluetooth receiver signal strength, in pourcents, or 0 if no connection is established.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_linkQuality();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackBluetoothLink is YBluetoothLinkValueCallback* (YBluetoothLinkValueCallback)
/**
 * Attempt to connect to the previously selected remote device.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_BluetoothLink_connect : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "connect";
  }

  string getDescription()
  {
    return "Attempt to connect to the previously selected remote device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->connect();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Disconnect from the previously selected remote device.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_BluetoothLink_disconnect : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "disconnect";
  }

  string getDescription()
  {
    return "Disconnect from the previously selected remote device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YBluetoothLink*>* list = enumerateTargets<YBluetoothLink>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->disconnect();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YBluetoothLink implementation)

//--- (BluetoothLink functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YBluetoothLink>(cmdList);
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_ownAddress()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_pairingPin()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_set_pairingPin()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_remoteAddress()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_set_remoteAddress()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_remoteName()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_mute()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_set_mute()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_preAmplifier()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_set_preAmplifier()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_volume()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_set_volume()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_linkState()));
    cmdList->push_back((YapiCommand*) (new BluetoothLink_get_linkQuality()));
    cmdList->push_back((YapiCommand*) (new apifun_BluetoothLink_connect()));
    cmdList->push_back((YapiCommand*) (new apifun_BluetoothLink_disconnect()));
  }

//--- (end of BluetoothLink functions)
