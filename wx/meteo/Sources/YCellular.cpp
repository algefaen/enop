/*********************************************************************
 *
 * $Id: YCellular.cpp 20167 2015-04-27 14:24:03Z seb $
 *
 * Implements commands to handle Cellular functions
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
#include "yocto_cellular.h"

using namespace std;

//--- (generated code: YCellular definitions)

const char *enumServiceScope[] = {
    "HOMENETWORK",
    "ROAMING",
    "NEVER",
    NULL
};

//--- (end of generated code: YCellular definitions)

bool   isModule(void)      { return false; }

//--- (generated code: YCellular implementation)
string YFunctionName(void) { return "Cellular"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of linkQuality is int (Percent)
// type of cellOperator is string (Text)
// type of imsi is string (IMSI)
// type of message is string (Text)
// type of pin is string (PinPassword)
// type of lockedOperator is string (Text)
// type of enableData is int (ServiceScope)
// type of apn is string (Text)
// type of apnSecret is string (APNPassword)
// type of command is string (Text)
/**
 * Returns the logical name of the cellular interface.
 *
 * @return a string corresponding to the logical name of the cellular interface
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Cellular_get_logicalName : public YapiCommand /* arguments: */
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
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
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
class Cellular_set_logicalName : public YapiCommand /* arguments: newval */
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
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
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
class Cellular_get_advertisedValue : public YapiCommand /* arguments: */
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
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
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
 * Returns the link quality, expressed in percent.
 *
 * @return an integer corresponding to the link quality, expressed in percent
 *
 * On failure, throws an exception or returns Y_LINKQUALITY_INVALID.
 */
class Cellular_get_linkQuality : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_linkQuality";
  }

  string getDescription()
  {
    return "Returns the link quality, expressed in percent.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_linkQuality();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the name of the cell operator currently in use.
 *
 * @return a string corresponding to the name of the cell operator currently in use
 *
 * On failure, throws an exception or returns Y_CELLOPERATOR_INVALID.
 */
class Cellular_get_cellOperator : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_cellOperator";
  }

  string getDescription()
  {
    return "Returns the name of the cell operator currently in use.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_cellOperator();
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
 * On failure, throws an exception or returns Y_IMSI_INVALID.
 */
class Cellular_get_imsi : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_imsi";
  }

  string getDescription()
  {
    return "Returns an opaque string if a PIN code has been configured in the device to access the SIM card, or an empty string if none has been configured or if the code providedwas rejected by the SIM card.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_imsi();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the latest status message from the wireless interface.
 *
 * @return a string corresponding to the latest status message from the wireless interface
 *
 * On failure, throws an exception or returns Y_MESSAGE_INVALID.
 */
class Cellular_get_message : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_message";
  }

  string getDescription()
  {
    return "Returns the latest status message from the wireless interface.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_message();
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
 * On failure, throws an exception or returns Y_PIN_INVALID.
 */
class Cellular_get_pin : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_pin";
  }

  string getDescription()
  {
    return "Returns an opaque string if a PIN code has been configured in the device to access the SIM card, or an empty string if none has been configured or if the code providedwas rejected by the SIM card.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_pin();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the PIN code used by the module to access the SIM card.
 * This function does not change the code on the SIM card itself, but only changes
 * the parameter used by the device to try to get access to it. If the SIM code
 * does not work immediately on first try, it will be automatically forgotten
 * and the message will be set to "Enter SIM PIN". The method should then be
 * invoked again with right correct PIN code. After three failed attempts in a row,
 * the message is changed to "Enter SIM PUK" and the SIM card PUK code must be
 * provided using method sendPUK.
 *
 * Remember to call the saveToFlash() method of the module to save the
 * new value in the device flash.
 *
 * @param newval : a string corresponding to the PIN code used by the module to access the SIM card
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Cellular_set_pin : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_pin";
  }

  string getDescription()
  {
    return "Changes the PIN code used by the module to access the SIM card.";
  }

  string getMoreInfo()
  {
    return "This function does not change the code on the SIM card itself, but only changes the parameter used by the device to try to get access to it. If the SIM code does not work immediately on first try, it will be automatically forgotten and the message will be set to \"Enter SIM PIN\". The method should then be invoked again with right correct PIN code. After three failed attempts in a row, the message is changed to \"Enter SIM PUK\" and the SIM card PUK code must be provided using method sendPUK.\nRemember to call \"YModule {target} saveToFlash\" to save the new value in the device flash.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the PIN code used by the module to access the SIM card", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_pin(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the name of the only cell operator to use if automatic choice is disabled,
 * or an empty string if the SIM card will automatically choose among available
 * cell operators.
 *
 * @return a string corresponding to the name of the only cell operator to use if automatic choice is disabled,
 *         or an empty string if the SIM card will automatically choose among available
 *         cell operators
 *
 * On failure, throws an exception or returns Y_LOCKEDOPERATOR_INVALID.
 */
class Cellular_get_lockedOperator : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_lockedOperator";
  }

  string getDescription()
  {
    return "Returns the name of the only cell operator to use if automatic choice is disabled, or an empty string if the SIM card will automatically choose among availablecell operators.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_lockedOperator();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the name of the cell operator to be used. If the name is an empty
 * string, the choice will be made automatically based on the SIM card. Otherwise,
 * the selected operator is the only one that will be used.
 *
 * @param newval : a string corresponding to the name of the cell operator to be used
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Cellular_set_lockedOperator : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_lockedOperator";
  }

  string getDescription()
  {
    return "Changes the name of the cell operator to be used.";
  }

  string getMoreInfo()
  {
    return "If the name is an empty string, the choice will be made automatically based on the SIM card. Otherwise, the selected operator is the only one that will be used.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the name of the cell operator to be used", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_lockedOperator(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the condition for enabling IP data services (GPRS).
 * When data services are disabled, SMS are the only mean of communication.
 *
 * @return a value among Y_ENABLEDATA_HOMENETWORK, Y_ENABLEDATA_ROAMING and Y_ENABLEDATA_NEVER
 * corresponding to the condition for enabling IP data services (GPRS)
 *
 * On failure, throws an exception or returns Y_ENABLEDATA_INVALID.
 */
class Cellular_get_enableData : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_enableData";
  }

  string getDescription()
  {
    return "Returns the condition for enabling IP data services (GPRS).";
  }

  string getMoreInfo()
  {
    return "When data services are disabled, SMS are the only mean of communication.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_enableData();
        string strval =  enumString(attrval,enumServiceScope);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the condition for enabling IP data services (GPRS).
 * The service can be either fully deactivated, or limited to the SIM home network,
 * or enabled for all partner networks (roaming). Caution: enabling data services
 * on roaming networks may cause prohibitive communication costs !
 *
 * When data services are disabled, SMS are the only mean of communication.
 *
 * @param newval : a value among Y_ENABLEDATA_HOMENETWORK, Y_ENABLEDATA_ROAMING and Y_ENABLEDATA_NEVER
 * corresponding to the condition for enabling IP data services (GPRS)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Cellular_set_enableData : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_enableData";
  }

  string getDescription()
  {
    return "Changes the condition for enabling IP data services (GPRS).";
  }

  string getMoreInfo()
  {
    return "The service can be either fully deactivated, or limited to the SIM home network, or enabled for all partner networks (roaming). Caution: enabling data services on roaming networks may cause prohibitive communication costs !\n When data services are disabled, SMS are the only mean of communication.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among HOMENETWORK, ROAMING and NEVER corresponding to the condition for enabling IP data services (GPRS)", "HOMENETWORK=0,ROAMING=1,NEVER=2", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_enableData(Y_ENABLEDATA_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the Access Point Name (APN) to be used, if needed.
 * When left blank, the APN suggested by the cell operator will be used.
 *
 * @return a string corresponding to the Access Point Name (APN) to be used, if needed
 *
 * On failure, throws an exception or returns Y_APN_INVALID.
 */
class Cellular_get_apn : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_apn";
  }

  string getDescription()
  {
    return "Returns the Access Point Name (APN) to be used, if needed.";
  }

  string getMoreInfo()
  {
    return "When left blank, the APN suggested by the cell operator will be used.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_apn();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the Access Point Name (APN) to be used, if needed.
 * When left blank, the APN suggested by the cell operator will be used.
 *
 * @param newval : a string
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Cellular_set_apn : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_apn";
  }

  string getDescription()
  {
    return "Returns the Access Point Name (APN) to be used, if needed.";
  }

  string getMoreInfo()
  {
    return "When left blank, the APN suggested by the cell operator will be used.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_apn(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns an opaque string if APN authentication parameters have been configured
 * in the device, or an empty string otherwise.
 * To configure these parameters, use set_apnAuth().
 *
 * @return a string corresponding to an opaque string if APN authentication parameters have been configured
 *         in the device, or an empty string otherwise
 *
 * On failure, throws an exception or returns Y_APNSECRET_INVALID.
 */
class Cellular_get_apnSecret : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_apnSecret";
  }

  string getDescription()
  {
    return "Returns an opaque string if APN authentication parameters have been configuredin the device, or an empty string otherwise.";
  }

  string getMoreInfo()
  {
    return "To configure these parameters, use set_apnAuth().";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_apnSecret();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackCellular is YCellularValueCallback* (YCellularValueCallback)
/**
 * Sends a PUK code to unlock the SIM card after three failed PIN code attempts, and
 * setup a new PIN into the SIM card. Only ten consecutives tentatives are permitted:
 * after that, the SIM card will be blocked permanently without any mean of recovery
 * to use it again. Note that after calling this method, you have usually to invoke
 * method set_pin() to tell the YoctoHub which PIN to use in the future.
 *
 * @param puk : the SIM PUK code
 * @param newPin : new PIN code to configure into the SIM card
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Cellular_sendPUK : public YapiCommand /* arguments: puk newPin */
{
public:

  string getName()
  {
    return "sendPUK";
  }

  string getDescription()
  {
    return "Sends a PUK code to unlock the SIM card after three failed PIN code attempts, andsetup a new PIN into the SIM card.";
  }

  string getMoreInfo()
  {
    return "Only ten consecutives tentatives are permitted: after that, the SIM card will be blocked permanently without any mean of recovery to use it again. Note that after calling this method, you have usually to invoke method set_pin() to tell the YoctoHub which PIN to use in the future.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "puk", "the SIM PUK code", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "newPin", "new PIN code to configure into the SIM card", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->sendPUK((*args)[0]->get_stringValue(),
                            (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Configure authentication parameters to connect to the APN. Both
 * PAP and CHAP authentication are supported.
 *
 * @param username : APN username
 * @param password : APN password
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Cellular_set_apnAuth : public YapiCommand /* arguments: username password */
{
public:

  string getName()
  {
    return "set_apnAuth";
  }

  string getDescription()
  {
    return "Configure authentication parameters to connect to the APN.";
  }

  string getMoreInfo()
  {
    return "Both PAP and CHAP authentication are supported.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "username", "APN username", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "password", "APN password", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_apnAuth((*args)[0]->get_stringValue(),
                                (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends an AT command to the GSM module and returns the command output.
 * The command will only execute when the GSM module is in standard
 * command state, and should leave it in the exact same state.
 * Use this function with great care !
 *
 * @param cmd : the AT command to execute, like for instance: "+CCLK?".
 *
 * @return a string with the result of the commands. Empty lines are
 *         automatically removed from the output.
 */
class apifun_Cellular__AT : public YapiCommand /* arguments: cmd */
{
public:

  string getName()
  {
    return "_AT";
  }

  string getDescription()
  {
    return "Sends an AT command to the GSM module and returns the command output.";
  }

  string getMoreInfo()
  {
    return "The command will only execute when the GSM module is in standard command state, and should leave it in the exact same state. Use this function with great care !";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "cmd", "the AT command to execute, like for instance: \"+CCLK?\".", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->_AT((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a list of nearby cellular antennas, as required for quick
 * geolocation of the device. The first cell listed is the serving
 * cell, and the next ones are the neighboor cells reported by the
 * serving cell.
 *
 * @return a list of YCellRecords.
 */
class apifun_Cellular_quickCellSurvey : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "quickCellSurvey";
  }

  string getDescription()
  {
    return "Returns a list of nearby cellular antennas, as required for quickgeolocation of the device.";
  }

  string getMoreInfo()
  {
    return "The first cell listed is the serving cell, and the next ones are the neighboor cells reported by the serving cell.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YCellular*>* list = enumerateTargets<YCellular>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<YCellRecord> value = (*list)[i]->quickCellSurvey();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YCellular implementation)

//--- (generated code: Cellular functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YCellular>(cmdList);
    cmdList->push_back((YapiCommand*) (new Cellular_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new Cellular_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_linkQuality()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_cellOperator()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_imsi()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_message()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_pin()));
    cmdList->push_back((YapiCommand*) (new Cellular_set_pin()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_lockedOperator()));
    cmdList->push_back((YapiCommand*) (new Cellular_set_lockedOperator()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_enableData()));
    cmdList->push_back((YapiCommand*) (new Cellular_set_enableData()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_apn()));
    cmdList->push_back((YapiCommand*) (new Cellular_set_apn()));
    cmdList->push_back((YapiCommand*) (new Cellular_get_apnSecret()));
    cmdList->push_back((YapiCommand*) (new apifun_Cellular_sendPUK()));
    cmdList->push_back((YapiCommand*) (new apifun_Cellular_set_apnAuth()));
    cmdList->push_back((YapiCommand*) (new apifun_Cellular__AT()));
    cmdList->push_back((YapiCommand*) (new apifun_Cellular_quickCellSurvey()));
  }

//--- (end of generated code: Cellular functions)
