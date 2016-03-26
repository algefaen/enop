/*********************************************************************
 *
 * $Id: YNetwork.cpp 20815 2015-07-09 17:23:30Z mvuilleu $
 *
 * Implements commands to handle Network functions
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
#include "yocto_network.h"

using namespace std;

//--- (YNetwork definitions)

const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

const char *enumReadiness[] = {
    "DOWN",
    "EXISTS",
    "LINKED",
    "LAN_OK",
    "WWW_OK",
    NULL
};

const char *enumHTTPMethod[] = {
    "POST",
    "GET",
    "PUT",
    NULL
};

const char *enumCallbackEncoding[] = {
    "FORM",
    "JSON",
    "JSON_ARRAY",
    "CSV",
    "YOCTO_API",
    "JSON_NUM",
    "EMONCMS",
    "AZURE",
    NULL
};

//--- (end of YNetwork definitions)

bool   isModule(void)      { return false; }

//--- (YNetwork implementation)
string YFunctionName(void) { return "Network"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of readiness is int (Readiness)
// type of macAddress is string (MACAddress)
// type of ipAddress is string (IPAddress)
// type of subnetMask is string (IPAddress)
// type of router is string (IPAddress)
// type of ipConfig is string (IPConfig)
// type of primaryDNS is string (IPAddress)
// type of secondaryDNS is string (IPAddress)
// type of ntpServer is string (IPAddress)
// type of userPassword is string (UserPassword)
// type of adminPassword is string (AdminPassword)
// type of httpPort is int (UInt31)
// type of defaultPage is string (Text)
// type of discoverable is int (Bool)
// type of wwwWatchdogDelay is int (UInt31)
// type of callbackUrl is string (Text)
// type of callbackMethod is int (HTTPMethod)
// type of callbackEncoding is int (CallbackEncoding)
// type of callbackCredentials is string (Credentials)
// type of callbackMinDelay is int (UInt31)
// type of callbackMaxDelay is int (UInt31)
// type of poeCurrent is int (UsedCurrent)
/**
 * Returns the logical name of the network interface, corresponding to the network name of the module.
 *
 * @return a string corresponding to the logical name of the network interface, corresponding to the
 * network name of the module
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Network_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the network interface, corresponding to the network name of the module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
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
 * Changes the logical name of the network interface, corresponding to the network name of the module.
 * You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the network interface, corresponding
 * to the network name of the module
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the network interface, corresponding to the network name of the module.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the network interface, corresponding to the network name of the module", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
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
 * Returns a short string representing the current state of the network interface.
 *
 * @return a string corresponding to a short string representing the current state of the network interface
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Network_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the network interface.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
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
 * Returns the current established working mode of the network interface.
 * Level zero (DOWN_0) means that no hardware link has been detected. Either there is no signal
 * on the network cable, or the selected wireless access point cannot be detected.
 * Level 1 (LIVE_1) is reached when the network is detected, but is not yet connected.
 * For a wireless network, this shows that the requested SSID is present.
 * Level 2 (LINK_2) is reached when the hardware connection is established.
 * For a wired network connection, level 2 means that the cable is attached at both ends.
 * For a connection to a wireless access point, it shows that the security parameters
 * are properly configured. For an ad-hoc wireless connection, it means that there is
 * at least one other device connected on the ad-hoc network.
 * Level 3 (DHCP_3) is reached when an IP address has been obtained using DHCP.
 * Level 4 (DNS_4) is reached when the DNS server is reachable on the network.
 * Level 5 (WWW_5) is reached when global connectivity is demonstrated by properly loading the
 * current time from an NTP server.
 *
 * @return a value among Y_READINESS_DOWN, Y_READINESS_EXISTS, Y_READINESS_LINKED, Y_READINESS_LAN_OK
 * and Y_READINESS_WWW_OK corresponding to the current established working mode of the network interface
 *
 * On failure, throws an exception or returns Y_READINESS_INVALID.
 */
class Network_get_readiness : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_readiness";
  }

  string getDescription()
  {
    return "Returns the current established working mode of the network interface.";
  }

  string getMoreInfo()
  {
    return "Level zero (DOWN_0) means that no hardware link has been detected. Either there is no signal on the network cable, or the selected wireless access point cannot be detected. Level 1 (LIVE_1) is reached when the network is detected, but is not yet connected. For a wireless network, this shows that the requested SSID is present. Level 2 (LINK_2) is reached when the hardware connection is established. For a wired network connection, level 2 means that the cable is attached at both ends. For a connection to a wireless access point, it shows that the security parameters are properly configured. For an ad-hoc wireless connection, it means that there is at least one other device connected on the ad-hoc network. Level 3 (DHCP_3) is reached when an IP address has been obtained using DHCP. Level 4 (DNS_4) is reached when the DNS server is reachable on the network. Level 5 (WWW_5) is reached when global connectivity is demonstrated by properly loading the current time from an NTP server.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_readiness();
        string strval =  enumString(attrval,enumReadiness);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the MAC address of the network interface. The MAC address is also available on a sticker
 * on the module, in both numeric and barcode forms.
 *
 * @return a string corresponding to the MAC address of the network interface
 *
 * On failure, throws an exception or returns Y_MACADDRESS_INVALID.
 */
class Network_get_macAddress : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_macAddress";
  }

  string getDescription()
  {
    return "Returns the MAC address of the network interface.";
  }

  string getMoreInfo()
  {
    return "The MAC address is also available on a sticker on the module, in both numeric and barcode forms.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_macAddress();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the IP address currently in use by the device. The address may have been configured
 * statically, or provided by a DHCP server.
 *
 * @return a string corresponding to the IP address currently in use by the device
 *
 * On failure, throws an exception or returns Y_IPADDRESS_INVALID.
 */
class Network_get_ipAddress : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_ipAddress";
  }

  string getDescription()
  {
    return "Returns the IP address currently in use by the device.";
  }

  string getMoreInfo()
  {
    return "The address may have been configured statically, or provided by a DHCP server.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_ipAddress();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the subnet mask currently used by the device.
 *
 * @return a string corresponding to the subnet mask currently used by the device
 *
 * On failure, throws an exception or returns Y_SUBNETMASK_INVALID.
 */
class Network_get_subnetMask : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_subnetMask";
  }

  string getDescription()
  {
    return "Returns the subnet mask currently used by the device.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_subnetMask();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the IP address of the router on the device subnet (default gateway).
 *
 * @return a string corresponding to the IP address of the router on the device subnet (default gateway)
 *
 * On failure, throws an exception or returns Y_ROUTER_INVALID.
 */
class Network_get_router : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_router";
  }

  string getDescription()
  {
    return "Returns the IP address of the router on the device subnet (default gateway).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_router();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the IP address of the primary name server to be used by the module.
 *
 * @return a string corresponding to the IP address of the primary name server to be used by the module
 *
 * On failure, throws an exception or returns Y_PRIMARYDNS_INVALID.
 */
class Network_get_primaryDNS : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_primaryDNS";
  }

  string getDescription()
  {
    return "Returns the IP address of the primary name server to be used by the module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_primaryDNS();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the IP address of the primary name server to be used by the module.
 * When using DHCP, if a value is specified, it overrides the value received from the DHCP server.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 *
 * @param newval : a string corresponding to the IP address of the primary name server to be used by the module
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_primaryDNS : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_primaryDNS";
  }

  string getDescription()
  {
    return "Changes the IP address of the primary name server to be used by the module.";
  }

  string getMoreInfo()
  {
    return "When using DHCP, if a value is specified, it overrides the value received from the DHCP server. Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the IP address of the primary name server to be used by the module", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_primaryDNS(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the IP address of the secondary name server to be used by the module.
 *
 * @return a string corresponding to the IP address of the secondary name server to be used by the module
 *
 * On failure, throws an exception or returns Y_SECONDARYDNS_INVALID.
 */
class Network_get_secondaryDNS : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_secondaryDNS";
  }

  string getDescription()
  {
    return "Returns the IP address of the secondary name server to be used by the module.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_secondaryDNS();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the IP address of the secondary name server to be used by the module.
 * When using DHCP, if a value is specified, it overrides the value received from the DHCP server.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 *
 * @param newval : a string corresponding to the IP address of the secondary name server to be used by the module
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_secondaryDNS : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_secondaryDNS";
  }

  string getDescription()
  {
    return "Changes the IP address of the secondary name server to be used by the module.";
  }

  string getMoreInfo()
  {
    return "When using DHCP, if a value is specified, it overrides the value received from the DHCP server. Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the IP address of the secondary name server to be used by the module", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_secondaryDNS(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the IP address of the NTP server to be used by the device.
 *
 * @return a string corresponding to the IP address of the NTP server to be used by the device
 *
 * On failure, throws an exception or returns Y_NTPSERVER_INVALID.
 */
class Network_get_ntpServer : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_ntpServer";
  }

  string getDescription()
  {
    return "Returns the IP address of the NTP server to be used by the device.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_ntpServer();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the IP address of the NTP server to be used by the module.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 *
 * @param newval : a string corresponding to the IP address of the NTP server to be used by the module
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_ntpServer : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_ntpServer";
  }

  string getDescription()
  {
    return "Changes the IP address of the NTP server to be used by the module.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the IP address of the NTP server to be used by the module", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_ntpServer(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a hash string if a password has been set for "user" user,
 * or an empty string otherwise.
 *
 * @return a string corresponding to a hash string if a password has been set for "user" user,
 *         or an empty string otherwise
 *
 * On failure, throws an exception or returns Y_USERPASSWORD_INVALID.
 */
class Network_get_userPassword : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_userPassword";
  }

  string getDescription()
  {
    return "Returns a hash string if a password has been set for \"user\" user,or an empty string otherwise.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_userPassword();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the password for the "user" user. This password becomes instantly required
 * to perform any use of the module. If the specified value is an
 * empty string, a password is not required anymore.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the password for the "user" user
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_userPassword : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_userPassword";
  }

  string getDescription()
  {
    return "Changes the password for the \"user\" user.";
  }

  string getMoreInfo()
  {
    return "This password becomes instantly required to perform any use of the module. If the specified value is an empty string, a password is not required anymore. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the password for the \"user\" user", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_userPassword(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a hash string if a password has been set for user "admin",
 * or an empty string otherwise.
 *
 * @return a string corresponding to a hash string if a password has been set for user "admin",
 *         or an empty string otherwise
 *
 * On failure, throws an exception or returns Y_ADMINPASSWORD_INVALID.
 */
class Network_get_adminPassword : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_adminPassword";
  }

  string getDescription()
  {
    return "Returns a hash string if a password has been set for user \"admin\",or an empty string otherwise.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_adminPassword();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the password for the "admin" user. This password becomes instantly required
 * to perform any change of the module state. If the specified value is an
 * empty string, a password is not required anymore.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the password for the "admin" user
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_adminPassword : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_adminPassword";
  }

  string getDescription()
  {
    return "Changes the password for the \"admin\" user.";
  }

  string getMoreInfo()
  {
    return "This password becomes instantly required to perform any change of the module state. If the specified value is an empty string, a password is not required anymore. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the password for the \"admin\" user", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_adminPassword(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the HTML page to serve for the URL "/"" of the hub.
 *
 * @return an integer corresponding to the HTML page to serve for the URL "/"" of the hub
 *
 * On failure, throws an exception or returns Y_HTTPPORT_INVALID.
 */
class Network_get_httpPort : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_httpPort";
  }

  string getDescription()
  {
    return "Returns the HTML page to serve for the URL \"/\"\" of the hub.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_httpPort();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the default HTML page returned by the hub. If not value are set the hub return
 * "index.html" which is the web interface of the hub. It is possible de change this page
 * for file that has been uploaded on the hub.
 *
 * @param newval : an integer corresponding to the default HTML page returned by the hub
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_httpPort : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_httpPort";
  }

  string getDescription()
  {
    return "Changes the default HTML page returned by the hub.";
  }

  string getMoreInfo()
  {
    return "If not value are set the hub return \"index.html\" which is the web interface of the hub. It is possible de change this page for file that has been uploaded on the hub.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the default HTML page returned by the hub", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_httpPort(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the HTML page to serve for the URL "/"" of the hub.
 *
 * @return a string corresponding to the HTML page to serve for the URL "/"" of the hub
 *
 * On failure, throws an exception or returns Y_DEFAULTPAGE_INVALID.
 */
class Network_get_defaultPage : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_defaultPage";
  }

  string getDescription()
  {
    return "Returns the HTML page to serve for the URL \"/\"\" of the hub.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_defaultPage();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the default HTML page returned by the hub. If not value are set the hub return
 * "index.html" which is the web interface of the hub. It is possible de change this page
 * for file that has been uploaded on the hub.
 *
 * @param newval : a string corresponding to the default HTML page returned by the hub
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_defaultPage : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_defaultPage";
  }

  string getDescription()
  {
    return "Changes the default HTML page returned by the hub.";
  }

  string getMoreInfo()
  {
    return "If not value are set the hub return \"index.html\" which is the web interface of the hub. It is possible de change this page for file that has been uploaded on the hub.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the default HTML page returned by the hub", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_defaultPage(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the activation state of the multicast announce protocols to allow easy
 * discovery of the module in the network neighborhood (uPnP/Bonjour protocol).
 *
 * @return either Y_DISCOVERABLE_FALSE or Y_DISCOVERABLE_TRUE, according to the activation state of
 * the multicast announce protocols to allow easy
 *         discovery of the module in the network neighborhood (uPnP/Bonjour protocol)
 *
 * On failure, throws an exception or returns Y_DISCOVERABLE_INVALID.
 */
class Network_get_discoverable : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_discoverable";
  }

  string getDescription()
  {
    return "Returns the activation state of the multicast announce protocols to allow easydiscovery of the module in the network neighborhood (uPnP/Bonjour protocol).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_discoverable();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the activation state of the multicast announce protocols to allow easy
 * discovery of the module in the network neighborhood (uPnP/Bonjour protocol).
 *
 * @param newval : either Y_DISCOVERABLE_FALSE or Y_DISCOVERABLE_TRUE, according to the activation
 * state of the multicast announce protocols to allow easy
 *         discovery of the module in the network neighborhood (uPnP/Bonjour protocol)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_discoverable : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_discoverable";
  }

  string getDescription()
  {
    return "Changes the activation state of the multicast announce protocols to allow easydiscovery of the module in the network neighborhood (uPnP/Bonjour protocol).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE, according to the activation state of the multicast announce protocols to allow easy discovery of the module in the network neighborhood (uPnP/Bonjour protocol)", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_discoverable(Y_DISCOVERABLE_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the allowed downtime of the WWW link (in seconds) before triggering an automated
 * reboot to try to recover Internet connectivity. A zero value disables automated reboot
 * in case of Internet connectivity loss.
 *
 * @return an integer corresponding to the allowed downtime of the WWW link (in seconds) before
 * triggering an automated
 *         reboot to try to recover Internet connectivity
 *
 * On failure, throws an exception or returns Y_WWWWATCHDOGDELAY_INVALID.
 */
class Network_get_wwwWatchdogDelay : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_wwwWatchdogDelay";
  }

  string getDescription()
  {
    return "Returns the allowed downtime of the WWW link (in seconds) before triggering an automatedreboot to try to recover Internet connectivity.";
  }

  string getMoreInfo()
  {
    return "A zero value disables automated reboot in case of Internet connectivity loss.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_wwwWatchdogDelay();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the allowed downtime of the WWW link (in seconds) before triggering an automated
 * reboot to try to recover Internet connectivity. A zero value disables automated reboot
 * in case of Internet connectivity loss. The smallest valid non-zero timeout is
 * 90 seconds.
 *
 * @param newval : an integer corresponding to the allowed downtime of the WWW link (in seconds)
 * before triggering an automated
 *         reboot to try to recover Internet connectivity
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_wwwWatchdogDelay : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_wwwWatchdogDelay";
  }

  string getDescription()
  {
    return "Changes the allowed downtime of the WWW link (in seconds) before triggering an automatedreboot to try to recover Internet connectivity.";
  }

  string getMoreInfo()
  {
    return "A zero value disables automated reboot in case of Internet connectivity loss. The smallest valid non-zero timeout is 90 seconds.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the allowed downtime of the WWW link (in seconds) before triggering an automated reboot to try to recover Internet connectivity", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_wwwWatchdogDelay(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the callback URL to notify of significant state changes.
 *
 * @return a string corresponding to the callback URL to notify of significant state changes
 *
 * On failure, throws an exception or returns Y_CALLBACKURL_INVALID.
 */
class Network_get_callbackUrl : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_callbackUrl";
  }

  string getDescription()
  {
    return "Returns the callback URL to notify of significant state changes.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_callbackUrl();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the callback URL to notify significant state changes. Remember to call the
 * saveToFlash() method of the module if the modification must be kept.
 *
 * @param newval : a string corresponding to the callback URL to notify significant state changes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_callbackUrl : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_callbackUrl";
  }

  string getDescription()
  {
    return "Changes the callback URL to notify significant state changes.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method of the module if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the callback URL to notify significant state changes", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_callbackUrl(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the HTTP method used to notify callbacks for significant state changes.
 *
 * @return a value among Y_CALLBACKMETHOD_POST, Y_CALLBACKMETHOD_GET and Y_CALLBACKMETHOD_PUT
 * corresponding to the HTTP method used to notify callbacks for significant state changes
 *
 * On failure, throws an exception or returns Y_CALLBACKMETHOD_INVALID.
 */
class Network_get_callbackMethod : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_callbackMethod";
  }

  string getDescription()
  {
    return "Returns the HTTP method used to notify callbacks for significant state changes.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_callbackMethod();
        string strval =  enumString(attrval,enumHTTPMethod);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the HTTP method used to notify callbacks for significant state changes.
 *
 * @param newval : a value among Y_CALLBACKMETHOD_POST, Y_CALLBACKMETHOD_GET and Y_CALLBACKMETHOD_PUT
 * corresponding to the HTTP method used to notify callbacks for significant state changes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_callbackMethod : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_callbackMethod";
  }

  string getDescription()
  {
    return "Changes the HTTP method used to notify callbacks for significant state changes.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among POST, GET and PUT corresponding to the HTTP method used to notify callbacks for significant state changes", "POST=0,GET=1,PUT=2", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_callbackMethod(Y_CALLBACKMETHOD_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the encoding standard to use for representing notification values.
 *
 * @return a value among Y_CALLBACKENCODING_FORM, Y_CALLBACKENCODING_JSON,
 * Y_CALLBACKENCODING_JSON_ARRAY, Y_CALLBACKENCODING_CSV, Y_CALLBACKENCODING_YOCTO_API,
 * Y_CALLBACKENCODING_JSON_NUM, Y_CALLBACKENCODING_EMONCMS and Y_CALLBACKENCODING_AZURE corresponding
 * to the encoding standard to use for representing notification values
 *
 * On failure, throws an exception or returns Y_CALLBACKENCODING_INVALID.
 */
class Network_get_callbackEncoding : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_callbackEncoding";
  }

  string getDescription()
  {
    return "Returns the encoding standard to use for representing notification values.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_callbackEncoding();
        string strval =  enumString(attrval,enumCallbackEncoding);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the encoding standard to use for representing notification values.
 *
 * @param newval : a value among Y_CALLBACKENCODING_FORM, Y_CALLBACKENCODING_JSON,
 * Y_CALLBACKENCODING_JSON_ARRAY, Y_CALLBACKENCODING_CSV, Y_CALLBACKENCODING_YOCTO_API,
 * Y_CALLBACKENCODING_JSON_NUM, Y_CALLBACKENCODING_EMONCMS and Y_CALLBACKENCODING_AZURE corresponding
 * to the encoding standard to use for representing notification values
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_callbackEncoding : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_callbackEncoding";
  }

  string getDescription()
  {
    return "Changes the encoding standard to use for representing notification values.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among FORM, JSON, JSON_ARRAY, CSV, YOCTO_API, JSON_NUM, EMONCMS and AZURE corresponding to the encoding standard to use for representing notification values", "FORM=0,JSON=1,JSON_ARRAY=2,CSV=3,YOCTO_API=4,JSON_NUM=5,EMONCMS=6,AZURE=7", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_callbackEncoding(Y_CALLBACKENCODING_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns a hashed version of the notification callback credentials if set,
 * or an empty string otherwise.
 *
 * @return a string corresponding to a hashed version of the notification callback credentials if set,
 *         or an empty string otherwise
 *
 * On failure, throws an exception or returns Y_CALLBACKCREDENTIALS_INVALID.
 */
class Network_get_callbackCredentials : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_callbackCredentials";
  }

  string getDescription()
  {
    return "Returns a hashed version of the notification callback credentials if set,or an empty string otherwise.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_callbackCredentials();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the credentials required to connect to the callback address. The credentials
 * must be provided as returned by function get_callbackCredentials,
 * in the form username:hash. The method used to compute the hash varies according
 * to the the authentication scheme implemented by the callback, For Basic authentication,
 * the hash is the MD5 of the string username:password. For Digest authentication,
 * the hash is the MD5 of the string username:realm:password. For a simpler
 * way to configure callback credentials, use function callbackLogin instead.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the credentials required to connect to the callback address
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_callbackCredentials : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_callbackCredentials";
  }

  string getDescription()
  {
    return "Changes the credentials required to connect to the callback address.";
  }

  string getMoreInfo()
  {
    return "The credentials must be provided as returned by function get_callbackCredentials, in the form username:hash. The method used to compute the hash varies according to the the authentication scheme implemented by the callback, For Basic authentication, the hash is the MD5 of the string username:password. For Digest authentication, the hash is the MD5 of the string username:realm:password. For a simpler way to configure callback credentials, use function callbackLogin instead. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the credentials required to connect to the callback address", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_callbackCredentials(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Connects to the notification callback and saves the credentials required to
 * log into it. The password is not stored into the module, only a hashed
 * copy of the credentials are saved. Remember to call the
 * saveToFlash() method of the module if the modification must be kept.
 *
 * @param username : username required to log to the callback
 * @param password : password required to log to the callback
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_Network_callbackLogin : public YapiCommand /* arguments: username password */
{
public:

  string getName()
  {
    return "callbackLogin";
  }

  string getDescription()
  {
    return "Connects to the notification callback and saves the credentials required tolog into it.";
  }

  string getMoreInfo()
  {
    return "The password is not stored into the module, only a hashed copy of the credentials are saved. Remember to call the saveToFlash() method of the module if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "username", "username required to log to the callback", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "password", "password required to log to the callback", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->callbackLogin((*args)[0]->get_stringValue(),
                                  (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the minimum waiting time between two callback notifications, in seconds.
 *
 * @return an integer corresponding to the minimum waiting time between two callback notifications, in seconds
 *
 * On failure, throws an exception or returns Y_CALLBACKMINDELAY_INVALID.
 */
class Network_get_callbackMinDelay : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_callbackMinDelay";
  }

  string getDescription()
  {
    return "Returns the minimum waiting time between two callback notifications, in seconds.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_callbackMinDelay();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the minimum waiting time between two callback notifications, in seconds.
 *
 * @param newval : an integer corresponding to the minimum waiting time between two callback
 * notifications, in seconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_callbackMinDelay : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_callbackMinDelay";
  }

  string getDescription()
  {
    return "Changes the minimum waiting time between two callback notifications, in seconds.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the minimum waiting time between two callback notifications, in seconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_callbackMinDelay(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the maximum waiting time between two callback notifications, in seconds.
 *
 * @return an integer corresponding to the maximum waiting time between two callback notifications, in seconds
 *
 * On failure, throws an exception or returns Y_CALLBACKMAXDELAY_INVALID.
 */
class Network_get_callbackMaxDelay : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_callbackMaxDelay";
  }

  string getDescription()
  {
    return "Returns the maximum waiting time between two callback notifications, in seconds.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_callbackMaxDelay();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the maximum waiting time between two callback notifications, in seconds.
 *
 * @param newval : an integer corresponding to the maximum waiting time between two callback
 * notifications, in seconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Network_set_callbackMaxDelay : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_callbackMaxDelay";
  }

  string getDescription()
  {
    return "Changes the maximum waiting time between two callback notifications, in seconds.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the maximum waiting time between two callback notifications, in seconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_callbackMaxDelay(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the current consumed by the module from Power-over-Ethernet (PoE), in milli-amps.
 * The current consumption is measured after converting PoE source to 5 Volt, and should
 * never exceed 1800 mA.
 *
 * @return an integer corresponding to the current consumed by the module from Power-over-Ethernet
 * (PoE), in milli-amps
 *
 * On failure, throws an exception or returns Y_POECURRENT_INVALID.
 */
class Network_get_poeCurrent : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_poeCurrent";
  }

  string getDescription()
  {
    return "Returns the current consumed by the module from Power-over-Ethernet (PoE), in milli-amps.";
  }

  string getMoreInfo()
  {
    return "The current consumption is measured after converting PoE source to 5 Volt, and should never exceed 1800 mA.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_poeCurrent();
        char buf[32]; snprintf(buf, 32, "%d [mA]", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackNetwork is YNetworkValueCallback* (YNetworkValueCallback)
/**
 * Changes the configuration of the network interface to enable the use of an
 * IP address received from a DHCP server. Until an address is received from a DHCP
 * server, the module uses the IP parameters specified to this function.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 *
 * @param fallbackIpAddr : fallback IP address, to be used when no DHCP reply is received
 * @param fallbackSubnetMaskLen : fallback subnet mask length when no DHCP reply is received, as an
 *         integer (eg. 24 means 255.255.255.0)
 * @param fallbackRouter : fallback router IP address, to be used when no DHCP reply is received
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Network_useDHCP : public YapiCommand /* arguments: fallbackIpAddr fallbackSubnetMaskLen fallbackRouter */
{
public:

  string getName()
  {
    return "useDHCP";
  }

  string getDescription()
  {
    return "Changes the configuration of the network interface to enable the use of anIP address received from a DHCP server.";
  }

  string getMoreInfo()
  {
    return "Until an address is received from a DHCP server, the module uses the IP parameters specified to this function. Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "fallbackIpAddr", "fallback IP address, to be used when no DHCP reply is received", "_STRING", false));
    res->push_back(new ArgumentDesc(INT_ARG, "fallbackSubnetMaskLen", "fallback subnet mask length when no DHCP reply is received, as an integer (eg. 24 means 255.255.255.0)", "_INT", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "fallbackRouter", "fallback router IP address, to be used when no DHCP reply is received", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->useDHCP((*args)[0]->get_stringValue(),
                            (int)(*args)[1]->get_intValue(),
                            (*args)[2]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the configuration of the network interface to use a static IP address.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 *
 * @param ipAddress : device IP address
 * @param subnetMaskLen : subnet mask length, as an integer (eg. 24 means 255.255.255.0)
 * @param router : router IP address (default gateway)
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Network_useStaticIP : public YapiCommand /* arguments: ipAddress subnetMaskLen router */
{
public:

  string getName()
  {
    return "useStaticIP";
  }

  string getDescription()
  {
    return "Changes the configuration of the network interface to use a static IP address.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method and then to reboot the module to apply this setting.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "ipAddress", "device IP address", "_STRING", false));
    res->push_back(new ArgumentDesc(INT_ARG, "subnetMaskLen", "subnet mask length, as an integer (eg. 24 means 255.255.255.0)", "_INT", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "router", "router IP address (default gateway)", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->useStaticIP((*args)[0]->get_stringValue(),
                                (int)(*args)[1]->get_intValue(),
                                (*args)[2]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Pings str_host to test the network connectivity. Sends four ICMP ECHO_REQUEST requests from the
 * module to the target str_host. This method returns a string with the result of the
 * 4 ICMP ECHO_REQUEST requests.
 *
 * @param host : the hostname or the IP address of the target
 *
 * @return a string with the result of the ping.
 */
class apifun_Network_ping : public YapiCommand /* arguments: host */
{
public:

  string getName()
  {
    return "ping";
  }

  string getDescription()
  {
    return "Pings str_host to test the network connectivity.";
  }

  string getMoreInfo()
  {
    return "Sends four ICMP ECHO_REQUEST requests from the module to the target str_host. This method returns a string with the result of the 4 ICMP ECHO_REQUEST requests.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "host", "the hostname or the IP address of the target", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YNetwork*>* list = enumerateTargets<YNetwork>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->ping((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YNetwork implementation)

//--- (Network functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YNetwork>(cmdList);
    cmdList->push_back((YapiCommand*) (new Network_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new Network_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new Network_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new Network_get_readiness()));
    cmdList->push_back((YapiCommand*) (new Network_get_macAddress()));
    cmdList->push_back((YapiCommand*) (new Network_get_ipAddress()));
    cmdList->push_back((YapiCommand*) (new Network_get_subnetMask()));
    cmdList->push_back((YapiCommand*) (new Network_get_router()));
    cmdList->push_back((YapiCommand*) (new Network_get_primaryDNS()));
    cmdList->push_back((YapiCommand*) (new Network_set_primaryDNS()));
    cmdList->push_back((YapiCommand*) (new Network_get_secondaryDNS()));
    cmdList->push_back((YapiCommand*) (new Network_set_secondaryDNS()));
    cmdList->push_back((YapiCommand*) (new Network_get_ntpServer()));
    cmdList->push_back((YapiCommand*) (new Network_set_ntpServer()));
    cmdList->push_back((YapiCommand*) (new Network_get_userPassword()));
    cmdList->push_back((YapiCommand*) (new Network_set_userPassword()));
    cmdList->push_back((YapiCommand*) (new Network_get_adminPassword()));
    cmdList->push_back((YapiCommand*) (new Network_set_adminPassword()));
    cmdList->push_back((YapiCommand*) (new Network_get_httpPort()));
    cmdList->push_back((YapiCommand*) (new Network_set_httpPort()));
    cmdList->push_back((YapiCommand*) (new Network_get_defaultPage()));
    cmdList->push_back((YapiCommand*) (new Network_set_defaultPage()));
    cmdList->push_back((YapiCommand*) (new Network_get_discoverable()));
    cmdList->push_back((YapiCommand*) (new Network_set_discoverable()));
    cmdList->push_back((YapiCommand*) (new Network_get_wwwWatchdogDelay()));
    cmdList->push_back((YapiCommand*) (new Network_set_wwwWatchdogDelay()));
    cmdList->push_back((YapiCommand*) (new Network_get_callbackUrl()));
    cmdList->push_back((YapiCommand*) (new Network_set_callbackUrl()));
    cmdList->push_back((YapiCommand*) (new Network_get_callbackMethod()));
    cmdList->push_back((YapiCommand*) (new Network_set_callbackMethod()));
    cmdList->push_back((YapiCommand*) (new Network_get_callbackEncoding()));
    cmdList->push_back((YapiCommand*) (new Network_set_callbackEncoding()));
    cmdList->push_back((YapiCommand*) (new Network_get_callbackCredentials()));
    cmdList->push_back((YapiCommand*) (new Network_set_callbackCredentials()));
    cmdList->push_back((YapiCommand*) (new alias_Network_callbackLogin()));
    cmdList->push_back((YapiCommand*) (new Network_get_callbackMinDelay()));
    cmdList->push_back((YapiCommand*) (new Network_set_callbackMinDelay()));
    cmdList->push_back((YapiCommand*) (new Network_get_callbackMaxDelay()));
    cmdList->push_back((YapiCommand*) (new Network_set_callbackMaxDelay()));
    cmdList->push_back((YapiCommand*) (new Network_get_poeCurrent()));
    cmdList->push_back((YapiCommand*) (new apifun_Network_useDHCP()));
    cmdList->push_back((YapiCommand*) (new apifun_Network_useStaticIP()));
    cmdList->push_back((YapiCommand*) (new apifun_Network_ping()));
  }

//--- (end of Network functions)
