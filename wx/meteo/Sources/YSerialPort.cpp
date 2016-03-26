/*********************************************************************
 *
 * $Id: YSerialPort.cpp 19811 2015-03-23 13:55:45Z mvuilleu $
 *
 * Implements commands to handle SerialPort functions
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
#include "yocto_serialport.h"

using namespace std;

//--- (YSerialPort definitions)

const char *enumSerialVoltageLevel[] = {
    "OFF",
    "TTL3V",
    "TTL3VR",
    "TTL5V",
    "TTL5VR",
    "RS232",
    "RS485",
    NULL
};

//--- (end of YSerialPort definitions)

bool   isModule(void)      { return false; }

//--- (YSerialPort implementation)
string YFunctionName(void) { return "SerialPort"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of serialMode is string (SerialMode)
// type of protocol is string (Protocol)
// type of voltageLevel is int (SerialVoltageLevel)
// type of rxCount is int (UInt31)
// type of txCount is int (UInt31)
// type of errCount is int (UInt31)
// type of rxMsgCount is int (UInt31)
// type of txMsgCount is int (UInt31)
// type of lastMsg is string (Text)
// type of currentJob is string (Text)
// type of startupJob is string (Text)
// type of command is string (Text)
/**
 * Returns the logical name of the serial port.
 *
 * @return a string corresponding to the logical name of the serial port
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class SerialPort_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the serial port.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
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
 * Changes the logical name of the serial port. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the serial port
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SerialPort_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the serial port.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the serial port", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
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
 * Returns a short string representing the current state of the serial port.
 *
 * @return a string corresponding to a short string representing the current state of the serial port
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class SerialPort_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the serial port.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
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
 * Returns the serial port communication parameters, as a string such as
 * "9600,8N1". The string includes the baud rate, the number of data bits,
 * the parity, and the number of stop bits. An optional suffix is included
 * if flow control is active: "CtsRts" for hardware handshake, "XOnXOff"
 * for logical flow control and "Simplex" for acquiring a shared bus using
 * the RTS line (as used by some RS485 adapters for instance).
 *
 * @return a string corresponding to the serial port communication parameters, as a string such as
 *         "9600,8N1"
 *
 * On failure, throws an exception or returns Y_SERIALMODE_INVALID.
 */
class SerialPort_get_serialMode : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_serialMode";
  }

  string getDescription()
  {
    return "Returns the serial port communication parameters, as a string such as\"9600,8N1\".";
  }

  string getMoreInfo()
  {
    return "The string includes the baud rate, the number of data bits, the parity, and the number of stop bits. An optional suffix is included if flow control is active: \"CtsRts\" for hardware handshake, \"XOnXOff\" for logical flow control and \"Simplex\" for acquiring a shared bus using the RTS line (as used by some RS485 adapters for instance).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_serialMode();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the serial port communication parameters, with a string such as
 * "9600,8N1". The string includes the baud rate, the number of data bits,
 * the parity, and the number of stop bits. An optional suffix can be added
 * to enable flow control: "CtsRts" for hardware handshake, "XOnXOff"
 * for logical flow control and "Simplex" for acquiring a shared bus using
 * the RTS line (as used by some RS485 adapters for instance).
 *
 * @param newval : a string corresponding to the serial port communication parameters, with a string such as
 *         "9600,8N1"
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SerialPort_set_serialMode : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_serialMode";
  }

  string getDescription()
  {
    return "Changes the serial port communication parameters, with a string such as\"9600,8N1\".";
  }

  string getMoreInfo()
  {
    return "The string includes the baud rate, the number of data bits, the parity, and the number of stop bits. An optional suffix can be added to enable flow control: \"CtsRts\" for hardware handshake, \"XOnXOff\" for logical flow control and \"Simplex\" for acquiring a shared bus using the RTS line (as used by some RS485 adapters for instance).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the serial port communication parameters, with a string such as \"9600,8N1\"", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_serialMode(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the type of protocol used over the serial line, as a string.
 * Possible values are "Line" for ASCII messages separated by CR and/or LF,
 * "Frame:[timeout]ms" for binary messages separated by a delay time,
 * "Modbus-ASCII" for MODBUS messages in ASCII mode,
 * "Modbus-RTU" for MODBUS messages in RTU mode,
 * "Char" for a continuous ASCII stream or
 * "Byte" for a continuous binary stream.
 *
 * @return a string corresponding to the type of protocol used over the serial line, as a string
 *
 * On failure, throws an exception or returns Y_PROTOCOL_INVALID.
 */
class SerialPort_get_protocol : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_protocol";
  }

  string getDescription()
  {
    return "Returns the type of protocol used over the serial line, as a string.";
  }

  string getMoreInfo()
  {
    return "Possible values are \"Line\" for ASCII messages separated by CR and/or LF, \"Frame:[timeout]ms\" for binary messages separated by a delay time, \"Modbus-ASCII\" for MODBUS messages in ASCII mode, \"Modbus-RTU\" for MODBUS messages in RTU mode, \"Char\" for a continuous ASCII stream or \"Byte\" for a continuous binary stream.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_protocol();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the type of protocol used over the serial line.
 * Possible values are "Line" for ASCII messages separated by CR and/or LF,
 * "Frame:[timeout]ms" for binary messages separated by a delay time,
 * "Modbus-ASCII" for MODBUS messages in ASCII mode,
 * "Modbus-RTU" for MODBUS messages in RTU mode,
 * "Char" for a continuous ASCII stream or
 * "Byte" for a continuous binary stream.
 * The suffix "/[wait]ms" can be added to reduce the transmit rate so that there
 * is always at lest the specified number of milliseconds between each bytes sent.
 *
 * @param newval : a string corresponding to the type of protocol used over the serial line
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SerialPort_set_protocol : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_protocol";
  }

  string getDescription()
  {
    return "Changes the type of protocol used over the serial line.";
  }

  string getMoreInfo()
  {
    return "Possible values are \"Line\" for ASCII messages separated by CR and/or LF, \"Frame:[timeout]ms\" for binary messages separated by a delay time, \"Modbus-ASCII\" for MODBUS messages in ASCII mode, \"Modbus-RTU\" for MODBUS messages in RTU mode, \"Char\" for a continuous ASCII stream or \"Byte\" for a continuous binary stream. The suffix \"/[wait]ms\" can be added to reduce the transmit rate so that there is always at lest the specified number of milliseconds between each bytes sent.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the type of protocol used over the serial line", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_protocol(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the voltage level used on the serial line.
 *
 * @return a value among Y_VOLTAGELEVEL_OFF, Y_VOLTAGELEVEL_TTL3V, Y_VOLTAGELEVEL_TTL3VR,
 * Y_VOLTAGELEVEL_TTL5V, Y_VOLTAGELEVEL_TTL5VR, Y_VOLTAGELEVEL_RS232 and Y_VOLTAGELEVEL_RS485
 * corresponding to the voltage level used on the serial line
 *
 * On failure, throws an exception or returns Y_VOLTAGELEVEL_INVALID.
 */
class SerialPort_get_voltageLevel : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_voltageLevel";
  }

  string getDescription()
  {
    return "Returns the voltage level used on the serial line.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_voltageLevel();
        string strval =  enumString(attrval,enumSerialVoltageLevel);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the voltage type used on the serial line. Valid
 * values  will depend on the Yoctopuce device model featuring
 * the serial port feature.  Check your device documentation
 * to find out which values are valid for that specific model.
 * Trying to set an invalid value will have no effect.
 *
 * @param newval : a value among Y_VOLTAGELEVEL_OFF, Y_VOLTAGELEVEL_TTL3V, Y_VOLTAGELEVEL_TTL3VR,
 * Y_VOLTAGELEVEL_TTL5V, Y_VOLTAGELEVEL_TTL5VR, Y_VOLTAGELEVEL_RS232 and Y_VOLTAGELEVEL_RS485
 * corresponding to the voltage type used on the serial line
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SerialPort_set_voltageLevel : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_voltageLevel";
  }

  string getDescription()
  {
    return "Changes the voltage type used on the serial line.";
  }

  string getMoreInfo()
  {
    return "Valid values will depend on the Yoctopuce device model featuring the serial port feature. Check your device documentation to find out which values are valid for that specific model. Trying to set an invalid value will have no effect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among OFF, TTL3V, TTL3VR, TTL5V, TTL5VR, RS232 and RS485 corresponding to the voltage type used on the serial line", "OFF=0,TTL3V=1,TTL3VR=2,TTL5V=3,TTL5VR=4,RS232=5,RS485=6", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_voltageLevel(Y_VOLTAGELEVEL_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the total number of bytes received since last reset.
 *
 * @return an integer corresponding to the total number of bytes received since last reset
 *
 * On failure, throws an exception or returns Y_RXCOUNT_INVALID.
 */
class SerialPort_get_rxCount : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_rxCount";
  }

  string getDescription()
  {
    return "Returns the total number of bytes received since last reset.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rxCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of bytes transmitted since last reset.
 *
 * @return an integer corresponding to the total number of bytes transmitted since last reset
 *
 * On failure, throws an exception or returns Y_TXCOUNT_INVALID.
 */
class SerialPort_get_txCount : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_txCount";
  }

  string getDescription()
  {
    return "Returns the total number of bytes transmitted since last reset.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_txCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of communication errors detected since last reset.
 *
 * @return an integer corresponding to the total number of communication errors detected since last reset
 *
 * On failure, throws an exception or returns Y_ERRCOUNT_INVALID.
 */
class SerialPort_get_errCount : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_errCount";
  }

  string getDescription()
  {
    return "Returns the total number of communication errors detected since last reset.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_errCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of messages received since last reset.
 *
 * @return an integer corresponding to the total number of messages received since last reset
 *
 * On failure, throws an exception or returns Y_RXMSGCOUNT_INVALID.
 */
class SerialPort_get_rxMsgCount : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_rxMsgCount";
  }

  string getDescription()
  {
    return "Returns the total number of messages received since last reset.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rxMsgCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the total number of messages send since last reset.
 *
 * @return an integer corresponding to the total number of messages send since last reset
 *
 * On failure, throws an exception or returns Y_TXMSGCOUNT_INVALID.
 */
class SerialPort_get_txMsgCount : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_txMsgCount";
  }

  string getDescription()
  {
    return "Returns the total number of messages send since last reset.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_txMsgCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the latest message fully received (for Line, Frame and Modbus protocols).
 *
 * @return a string corresponding to the latest message fully received (for Line, Frame and Modbus protocols)
 *
 * On failure, throws an exception or returns Y_LASTMSG_INVALID.
 */
class SerialPort_get_lastMsg : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_lastMsg";
  }

  string getDescription()
  {
    return "Returns the latest message fully received (for Line, Frame and Modbus protocols).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_lastMsg();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the name of the job file currently in use.
 *
 * @return a string corresponding to the name of the job file currently in use
 *
 * On failure, throws an exception or returns Y_CURRENTJOB_INVALID.
 */
class SerialPort_get_currentJob : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_currentJob";
  }

  string getDescription()
  {
    return "Returns the name of the job file currently in use.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_currentJob();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the job to use when the device is powered on.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the job to use when the device is powered on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SerialPort_set_currentJob : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_currentJob";
  }

  string getDescription()
  {
    return "Changes the job to use when the device is powered on.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the job to use when the device is powered on", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_currentJob(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the job file to use when the device is powered on.
 *
 * @return a string corresponding to the job file to use when the device is powered on
 *
 * On failure, throws an exception or returns Y_STARTUPJOB_INVALID.
 */
class SerialPort_get_startupJob : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_startupJob";
  }

  string getDescription()
  {
    return "Returns the job file to use when the device is powered on.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_startupJob();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the job to use when the device is powered on.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the job to use when the device is powered on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SerialPort_set_startupJob : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_startupJob";
  }

  string getDescription()
  {
    return "Changes the job to use when the device is powered on.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the job to use when the device is powered on", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_startupJob(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackSerialPort is YSerialPortValueCallback* (YSerialPortValueCallback)
// type of rxptr is int (int)
/**
 * Clears the serial port buffer and resets counters to zero.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_reset : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "reset";
  }

  string getDescription()
  {
    return "Clears the serial port buffer and resets counters to zero.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->reset();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Manually sets the state of the RTS line. This function has no effect when
 * hardware handshake is enabled, as the RTS line is driven automatically.
 *
 * @param val : 1 to turn RTS on, 0 to turn RTS off
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_set_RTS : public YapiCommand /* arguments: val */
{
public:

  string getName()
  {
    return "set_RTS";
  }

  string getDescription()
  {
    return "Manually sets the state of the RTS line.";
  }

  string getMoreInfo()
  {
    return "This function has no effect when hardware handshake is enabled, as the RTS line is driven automatically.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "val", "1 to turn RTS on, 0 to turn RTS off", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_RTS((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads the level of the CTS line. The CTS line is usually driven by
 * the RTS signal of the connected serial device.
 *
 * @return 1 if the CTS line is high, 0 if the CTS line is low.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_get_CTS : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_CTS";
  }

  string getDescription()
  {
    return "Reads the level of the CTS line.";
  }

  string getMoreInfo()
  {
    return "The CTS line is usually driven by the RTS signal of the connected serial device.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_CTS();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a single byte to the serial port.
 *
 * @param code : the byte to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_writeByte : public YapiCommand /* arguments: code */
{
public:

  string getName()
  {
    return "writeByte";
  }

  string getDescription()
  {
    return "Sends a single byte to the serial port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "code", "the byte to send", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeByte((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends an ASCII string to the serial port, as is.
 *
 * @param text : the text string to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_writeStr : public YapiCommand /* arguments: text */
{
public:

  string getName()
  {
    return "writeStr";
  }

  string getDescription()
  {
    return "Sends an ASCII string to the serial port, as is.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "text", "the text string to send", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeStr((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a binary buffer to the serial port, as is.
 *
 * @param buff : the binary buffer to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_writeBin : public YapiCommand /* arguments: buff */
{
public:

  string getName()
  {
    return "writeBin";
  }

  string getDescription()
  {
    return "Sends a binary buffer to the serial port, as is.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(BIN_ARG, "buff", "the binary buffer to send", "_BIN", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeBin((*args)[0]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a byte sequence (provided as a list of bytes) to the serial port.
 *
 * @param byteList : a list of byte codes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_writeArray : public YapiCommand /* arguments: byteList */
{
public:

  string getName()
  {
    return "writeArray";
  }

  string getDescription()
  {
    return "Sends a byte sequence (provided as a list of bytes) to the serial port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INTARR_ARG, "byteList", "a list of byte codes", "_INTARR", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeArray((*args)[0]->get_intArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a byte sequence (provided as a hexadecimal string) to the serial port.
 *
 * @param hexString : a string of hexadecimal byte codes
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_writeHex : public YapiCommand /* arguments: hexString */
{
public:

  string getName()
  {
    return "writeHex";
  }

  string getDescription()
  {
    return "Sends a byte sequence (provided as a hexadecimal string) to the serial port.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "hexString", "a string of hexadecimal byte codes", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeHex((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends an ASCII string to the serial port, followed by a line break (CR LF).
 *
 * @param text : the text string to send
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_writeLine : public YapiCommand /* arguments: text */
{
public:

  string getName()
  {
    return "writeLine";
  }

  string getDescription()
  {
    return "Sends an ASCII string to the serial port, followed by a line break (CR LF).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "text", "the text string to send", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeLine((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a MODBUS message (provided as a hexadecimal string) to the serial port.
 * The message must start with the slave address. The MODBUS CRC/LRC is
 * automatically added by the function. This function does not wait for a reply.
 *
 * @param hexString : a hexadecimal message string, including device address but no CRC/LRC
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_writeMODBUS : public YapiCommand /* arguments: hexString */
{
public:

  string getName()
  {
    return "writeMODBUS";
  }

  string getDescription()
  {
    return "Sends a MODBUS message (provided as a hexadecimal string) to the serial port.";
  }

  string getMoreInfo()
  {
    return "The message must start with the slave address. The MODBUS CRC/LRC is automatically added by the function. This function does not wait for a reply.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "hexString", "a hexadecimal message string, including device address but no CRC/LRC", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->writeMODBUS((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads one byte from the receive buffer, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer,
 * or if there is no data available yet, the function returns YAPI_NO_MORE_DATA.
 *
 * @return the next byte
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_readByte : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "readByte";
  }

  string getDescription()
  {
    return "Reads one byte from the receive buffer, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, or if there is no data available yet, the function returns YAPI_NO_MORE_DATA.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->readByte();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a string, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nChars : the maximum number of characters to read
 *
 * @return a string with receive buffer contents
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_readStr : public YapiCommand /* arguments: nChars */
{
public:

  string getName()
  {
    return "readStr";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a string, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nChars", "the maximum number of characters to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readStr((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a binary buffer, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nChars : the maximum number of bytes to read
 *
 * @return a binary object with receive buffer contents
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_readBin : public YapiCommand /* arguments: nChars */
{
public:

  string getName()
  {
    return "readBin";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a binary buffer, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nChars", "the maximum number of bytes to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readBin((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a list of bytes, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nChars : the maximum number of bytes to read
 *
 * @return a sequence of bytes with receive buffer contents
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_readArray : public YapiCommand /* arguments: nChars */
{
public:

  string getName()
  {
    return "readArray";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a list of bytes, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nChars", "the maximum number of bytes to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->readArray((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads data from the receive buffer as a hexadecimal string, starting at current stream position.
 * If data at current stream position is not available anymore in the receive buffer, the
 * function performs a short read.
 *
 * @param nBytes : the maximum number of bytes to read
 *
 * @return a string with receive buffer contents, encoded in hexadecimal
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_readHex : public YapiCommand /* arguments: nBytes */
{
public:

  string getName()
  {
    return "readHex";
  }

  string getDescription()
  {
    return "Reads data from the receive buffer as a hexadecimal string, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "If data at current stream position is not available anymore in the receive buffer, the function performs a short read.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "nBytes", "the maximum number of bytes to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readHex((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads a single line (or message) from the receive buffer, starting at current stream position.
 * This function is intended to be used when the serial port is configured for a message protocol,
 * such as 'Line' mode or MODBUS protocols.
 *
 * If data at current stream position is not available anymore in the receive buffer,
 * the function returns the oldest available line and moves the stream position just after.
 * If no new full line is received, the function returns an empty line.
 *
 * @return a string with a single line of text
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_readLine : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "readLine";
  }

  string getDescription()
  {
    return "Reads a single line (or message) from the receive buffer, starting at current stream position.";
  }

  string getMoreInfo()
  {
    return "This function is intended to be used when the serial port is configured for a message protocol, such as 'Line' mode or MODBUS protocols.\nIf data at current stream position is not available anymore in the receive buffer, the function returns the oldest available line and moves the stream position just after. If no new full line is received, the function returns an empty line.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->readLine();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Searches for incoming messages in the serial port receive buffer matching a given pattern,
 * starting at current position. This function will only compare and return printable characters
 * in the message strings. Binary protocols are handled as hexadecimal strings.
 *
 * The search returns all messages matching the expression provided as argument in the buffer.
 * If no matching message is found, the search waits for one up to the specified maximum timeout
 * (in milliseconds).
 *
 * @param pattern : a limited regular expression describing the expected message format,
 *         or an empty string if all messages should be returned (no filtering).
 *         When using binary protocols, the format applies to the hexadecimal
 *         representation of the message.
 * @param maxWait : the maximum number of milliseconds to wait for a message if none is found
 *         in the receive buffer.
 *
 * @return an array of strings containing the messages found, if any.
 *         Binary messages are converted to hexadecimal representation.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SerialPort_readMessages : public YapiCommand /* arguments: pattern maxWait */
{
public:

  string getName()
  {
    return "readMessages";
  }

  string getDescription()
  {
    return "Searches for incoming messages in the serial port receive buffer matching a given pattern,starting at current position.";
  }

  string getMoreInfo()
  {
    return "This function will only compare and return printable characters in the message strings. Binary protocols are handled as hexadecimal strings.\nThe search returns all messages matching the expression provided as argument in the buffer. If no matching message is found, the search waits for one up to the specified maximum timeout (in milliseconds).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pattern", "a limited regular expression describing the expected message format, or an empty string if all messages should be returned (no filtering). When using binary protocols, the format applies to the hexadecimal representation of the message.", "_STRING", false));
    res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum number of milliseconds to wait for a message if none is found in the receive buffer.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<string> value = (*list)[i]->readMessages((*args)[0]->get_stringValue(),
                                                        (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Changes the current internal stream position to the specified value. This function
 * does not affect the device, it only changes the value stored in the YSerialPort object
 * for the next read operations.
 *
 * @param absPos : the absolute position index for next read operations.
 *
 * @return nothing.
 */
class apifun_SerialPort_read_seek : public YapiCommand /* arguments: absPos */
{
public:

  string getName()
  {
    return "read_seek";
  }

  string getDescription()
  {
    return "Changes the current internal stream position to the specified value.";
  }

  string getMoreInfo()
  {
    return "This function does not affect the device, it only changes the value stored in the YSerialPort object for the next read operations.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "absPos", "the absolute position index for next read operations.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->read_seek((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the current absolute stream position pointer of the YSerialPort object.
 *
 * @return the absolute position index for next read operations.
 */
class apifun_SerialPort_read_tell : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "read_tell";
  }

  string getDescription()
  {
    return "Returns the current absolute stream position pointer of the YSerialPort object.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->read_tell();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the number of bytes available to read in the input buffer starting from the
 * current absolute stream position pointer of the YSerialPort object.
 *
 * @return the number of bytes available to read
 */
class apifun_SerialPort_read_avail : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "read_avail";
  }

  string getDescription()
  {
    return "Returns the number of bytes available to read in the input buffer starting from thecurrent absolute stream position pointer of the YSerialPort object.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->read_avail();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a text line query to the serial port, and reads the reply, if any.
 * This function is intended to be used when the serial port is configured for 'Line' protocol.
 *
 * @param query : the line query to send (without CR/LF)
 * @param maxWait : the maximum number of milliseconds to wait for a reply.
 *
 * @return the next text line received after sending the text query, as a string.
 *         Additional lines can be obtained by calling readLine or readMessages.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SerialPort_queryLine : public YapiCommand /* arguments: query maxWait */
{
public:

  string getName()
  {
    return "queryLine";
  }

  string getDescription()
  {
    return "Sends a text line query to the serial port, and reads the reply, if any.";
  }

  string getMoreInfo()
  {
    return "This function is intended to be used when the serial port is configured for 'Line' protocol.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "query", "the line query to send (without CR/LF)", "_STRING", false));
    res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum number of milliseconds to wait for a reply.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->queryLine((*args)[0]->get_stringValue(),
                                             (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sends a message to a specified MODBUS slave connected to the serial port, and reads the
 * reply, if any. The message is the PDU, provided as a vector of bytes.
 *
 * @param slaveNo : the address of the slave MODBUS device to query
 * @param pduBytes : the message to send (PDU), as a vector of bytes. The first byte of the
 *         PDU is the MODBUS function code.
 *
 * @return the received reply, as a vector of bytes.
 *
 * On failure, throws an exception or returns an empty array (or a MODBUS error reply).
 */
class apifun_SerialPort_queryMODBUS : public YapiCommand /* arguments: slaveNo pduBytes */
{
public:

  string getName()
  {
    return "queryMODBUS";
  }

  string getDescription()
  {
    return "Sends a message to a specified MODBUS slave connected to the serial port, and reads thereply, if any.";
  }

  string getMoreInfo()
  {
    return "The message is the PDU, provided as a vector of bytes.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to query", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "pduBytes", "the message to send (PDU), as a vector of bytes. The first byte of the PDU is the MODBUS function code.", "_INTARR", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->queryMODBUS((int)(*args)[0]->get_intValue(),
                                                    (*args)[1]->get_intArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads one or more contiguous internal bits (or coil status) from a MODBUS serial device.
 * This method uses the MODBUS function code 0x01 (Read Coils).
 *
 * @param slaveNo : the address of the slave MODBUS device to query
 * @param pduAddr : the relative address of the first bit/coil to read (zero-based)
 * @param nBits : the number of bits/coils to read
 *
 * @return a vector of integers, each corresponding to one bit.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SerialPort_modbusReadBits : public YapiCommand /* arguments: slaveNo pduAddr nBits */
{
public:

  string getName()
  {
    return "modbusReadBits";
  }

  string getDescription()
  {
    return "Reads one or more contiguous internal bits (or coil status) from a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x01 (Read Coils).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to query", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the first bit/coil to read (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "nBits", "the number of bits/coils to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->modbusReadBits((int)(*args)[0]->get_intValue(),
                                                       (int)(*args)[1]->get_intValue(),
                                                       (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads one or more contiguous input bits (or discrete inputs) from a MODBUS serial device.
 * This method uses the MODBUS function code 0x02 (Read Discrete Inputs).
 *
 * @param slaveNo : the address of the slave MODBUS device to query
 * @param pduAddr : the relative address of the first bit/input to read (zero-based)
 * @param nBits : the number of bits/inputs to read
 *
 * @return a vector of integers, each corresponding to one bit.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SerialPort_modbusReadInputBits : public YapiCommand /* arguments: slaveNo pduAddr nBits */
{
public:

  string getName()
  {
    return "modbusReadInputBits";
  }

  string getDescription()
  {
    return "Reads one or more contiguous input bits (or discrete inputs) from a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x02 (Read Discrete Inputs).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to query", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the first bit/input to read (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "nBits", "the number of bits/inputs to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->modbusReadInputBits((int)(*args)[0]->get_intValue(),
                                                            (int)(*args)[1]->get_intValue(),
                                                            (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads one or more contiguous internal registers (holding registers) from a MODBUS serial device.
 * This method uses the MODBUS function code 0x03 (Read Holding Registers).
 *
 * @param slaveNo : the address of the slave MODBUS device to query
 * @param pduAddr : the relative address of the first holding register to read (zero-based)
 * @param nWords : the number of holding registers to read
 *
 * @return a vector of integers, each corresponding to one 16-bit register value.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SerialPort_modbusReadRegisters : public YapiCommand /* arguments: slaveNo pduAddr nWords */
{
public:

  string getName()
  {
    return "modbusReadRegisters";
  }

  string getDescription()
  {
    return "Reads one or more contiguous internal registers (holding registers) from a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x03 (Read Holding Registers).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to query", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the first holding register to read (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "nWords", "the number of holding registers to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->modbusReadRegisters((int)(*args)[0]->get_intValue(),
                                                            (int)(*args)[1]->get_intValue(),
                                                            (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Reads one or more contiguous input registers (read-only registers) from a MODBUS serial device.
 * This method uses the MODBUS function code 0x04 (Read Input Registers).
 *
 * @param slaveNo : the address of the slave MODBUS device to query
 * @param pduAddr : the relative address of the first input register to read (zero-based)
 * @param nWords : the number of input registers to read
 *
 * @return a vector of integers, each corresponding to one 16-bit input value.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SerialPort_modbusReadInputRegisters : public YapiCommand /* arguments: slaveNo pduAddr nWords */
{
public:

  string getName()
  {
    return "modbusReadInputRegisters";
  }

  string getDescription()
  {
    return "Reads one or more contiguous input registers (read-only registers) from a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x04 (Read Input Registers).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to query", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the first input register to read (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "nWords", "the number of input registers to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->modbusReadInputRegisters((int)(*args)[0]->get_intValue(),
                                                                 (int)(*args)[1]->get_intValue(),
                                                                 (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets a single internal bit (or coil) on a MODBUS serial device.
 * This method uses the MODBUS function code 0x05 (Write Single Coil).
 *
 * @param slaveNo : the address of the slave MODBUS device to drive
 * @param pduAddr : the relative address of the bit/coil to set (zero-based)
 * @param value : the value to set (0 for OFF state, non-zero for ON state)
 *
 * @return the number of bits/coils affected on the device (1)
 *
 * On failure, throws an exception or returns zero.
 */
class apifun_SerialPort_modbusWriteBit : public YapiCommand /* arguments: slaveNo pduAddr value */
{
public:

  string getName()
  {
    return "modbusWriteBit";
  }

  string getDescription()
  {
    return "Sets a single internal bit (or coil) on a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x05 (Write Single Coil).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to drive", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the bit/coil to set (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "value", "the value to set (0 for OFF state, non-zero for ON state)", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->modbusWriteBit((int)(*args)[0]->get_intValue(),
                                   (int)(*args)[1]->get_intValue(),
                                   (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets several contiguous internal bits (or coils) on a MODBUS serial device.
 * This method uses the MODBUS function code 0x0f (Write Multiple Coils).
 *
 * @param slaveNo : the address of the slave MODBUS device to drive
 * @param pduAddr : the relative address of the first bit/coil to set (zero-based)
 * @param bits : the vector of bits to be set (one integer per bit)
 *
 * @return the number of bits/coils affected on the device
 *
 * On failure, throws an exception or returns zero.
 */
class apifun_SerialPort_modbusWriteBits : public YapiCommand /* arguments: slaveNo pduAddr bits */
{
public:

  string getName()
  {
    return "modbusWriteBits";
  }

  string getDescription()
  {
    return "Sets several contiguous internal bits (or coils) on a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x0f (Write Multiple Coils).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to drive", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the first bit/coil to set (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "bits", "the vector of bits to be set (one integer per bit)", "_INTARR", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->modbusWriteBits((int)(*args)[0]->get_intValue(),
                                    (int)(*args)[1]->get_intValue(),
                                    (*args)[2]->get_intArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets a single internal register (or holding register) on a MODBUS serial device.
 * This method uses the MODBUS function code 0x06 (Write Single Register).
 *
 * @param slaveNo : the address of the slave MODBUS device to drive
 * @param pduAddr : the relative address of the register to set (zero-based)
 * @param value : the 16 bit value to set
 *
 * @return the number of registers affected on the device (1)
 *
 * On failure, throws an exception or returns zero.
 */
class apifun_SerialPort_modbusWriteRegister : public YapiCommand /* arguments: slaveNo pduAddr value */
{
public:

  string getName()
  {
    return "modbusWriteRegister";
  }

  string getDescription()
  {
    return "Sets a single internal register (or holding register) on a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x06 (Write Single Register).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to drive", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the register to set (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "value", "the 16 bit value to set", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->modbusWriteRegister((int)(*args)[0]->get_intValue(),
                                        (int)(*args)[1]->get_intValue(),
                                        (int)(*args)[2]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets several contiguous internal registers (or holding registers) on a MODBUS serial device.
 * This method uses the MODBUS function code 0x10 (Write Multiple Registers).
 *
 * @param slaveNo : the address of the slave MODBUS device to drive
 * @param pduAddr : the relative address of the first internal register to set (zero-based)
 * @param values : the vector of 16 bit values to set
 *
 * @return the number of registers affected on the device
 *
 * On failure, throws an exception or returns zero.
 */
class apifun_SerialPort_modbusWriteRegisters : public YapiCommand /* arguments: slaveNo pduAddr values */
{
public:

  string getName()
  {
    return "modbusWriteRegisters";
  }

  string getDescription()
  {
    return "Sets several contiguous internal registers (or holding registers) on a MODBUS serial device.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x10 (Write Multiple Registers).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to drive", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduAddr", "the relative address of the first internal register to set (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "values", "the vector of 16 bit values to set", "_INTARR", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->modbusWriteRegisters((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue(),
                                         (*args)[2]->get_intArrValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets several contiguous internal registers (holding registers) on a MODBUS serial device,
 * then performs a contiguous read of a set of (possibly different) internal registers.
 * This method uses the MODBUS function code 0x17 (Read/Write Multiple Registers).
 *
 * @param slaveNo : the address of the slave MODBUS device to drive
 * @param pduWriteAddr : the relative address of the first internal register to set (zero-based)
 * @param values : the vector of 16 bit values to set
 * @param pduReadAddr : the relative address of the first internal register to read (zero-based)
 * @param nReadWords : the number of 16 bit values to read
 *
 * @return a vector of integers, each corresponding to one 16-bit register value read.
 *
 * On failure, throws an exception or returns an empty array.
 */
class apifun_SerialPort_modbusWriteAndReadRegisters : public YapiCommand /* arguments: slaveNo pduWriteAddr values pduReadAddr nReadWords */
{
public:

  string getName()
  {
    return "modbusWriteAndReadRegisters";
  }

  string getDescription()
  {
    return "Sets several contiguous internal registers (holding registers) on a MODBUS serial device,then performs a contiguous read of a set of (possibly different) internal registers.";
  }

  string getMoreInfo()
  {
    return "This method uses the MODBUS function code 0x17 (Read/Write Multiple Registers).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "slaveNo", "the address of the slave MODBUS device to drive", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduWriteAddr", "the relative address of the first internal register to set (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INTARR_ARG, "values", "the vector of 16 bit values to set", "_INTARR", false));
    res->push_back(new ArgumentDesc(INT_ARG, "pduReadAddr", "the relative address of the first internal register to read (zero-based)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "nReadWords", "the number of 16 bit values to read", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        vector<int> value = (*list)[i]->modbusWriteAndReadRegisters((int)(*args)[0]->get_intValue(),
                                                                    (int)(*args)[1]->get_intValue(),
                                                                    (*args)[2]->get_intArrValue(),
                                                                    (int)(*args)[3]->get_intValue(),
                                                                    (int)(*args)[4]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Saves the job definition string (JSON data) into a job file.
 * The job file can be later enabled using selectJob().
 *
 * @param jobfile : name of the job file to save on the device filesystem
 * @param jsonDef : a string containing a JSON definition of the job
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_uploadJob : public YapiCommand /* arguments: jobfile jsonDef */
{
public:

  string getName()
  {
    return "uploadJob";
  }

  string getDescription()
  {
    return "Saves the job definition string (JSON data) into a job file.";
  }

  string getMoreInfo()
  {
    return "The job file can be later enabled using selectJob().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "jobfile", "name of the job file to save on the device filesystem", "_STRING", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "jsonDef", "a string containing a JSON definition of the job", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->uploadJob((*args)[0]->get_stringValue(),
                              (*args)[1]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Load and start processing the specified job file. The file must have
 * been previously created using the user interface or uploaded on the
 * device filesystem using the uploadJob() function.
 *
 * @param jobfile : name of the job file (on the device filesystem)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_SerialPort_selectJob : public YapiCommand /* arguments: jobfile */
{
public:

  string getName()
  {
    return "selectJob";
  }

  string getDescription()
  {
    return "Load and start processing the specified job file.";
  }

  string getMoreInfo()
  {
    return "The file must have been previously created using the user interface or uploaded on the device filesystem using the uploadJob() function.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "jobfile", "name of the job file (on the device filesystem)", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSerialPort*>* list = enumerateTargets<YSerialPort>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->selectJob((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YSerialPort implementation)

//--- (SerialPort functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YSerialPort>(cmdList);
    cmdList->push_back((YapiCommand*) (new SerialPort_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new SerialPort_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_serialMode()));
    cmdList->push_back((YapiCommand*) (new SerialPort_set_serialMode()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_protocol()));
    cmdList->push_back((YapiCommand*) (new SerialPort_set_protocol()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_voltageLevel()));
    cmdList->push_back((YapiCommand*) (new SerialPort_set_voltageLevel()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_rxCount()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_txCount()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_errCount()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_rxMsgCount()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_txMsgCount()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_lastMsg()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_currentJob()));
    cmdList->push_back((YapiCommand*) (new SerialPort_set_currentJob()));
    cmdList->push_back((YapiCommand*) (new SerialPort_get_startupJob()));
    cmdList->push_back((YapiCommand*) (new SerialPort_set_startupJob()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_reset()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_set_RTS()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_get_CTS()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_writeByte()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_writeStr()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_writeBin()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_writeArray()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_writeHex()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_writeLine()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_writeMODBUS()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_readByte()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_readStr()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_readBin()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_readArray()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_readHex()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_readLine()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_readMessages()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_read_seek()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_read_tell()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_read_avail()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_queryLine()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_queryMODBUS()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusReadBits()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusReadInputBits()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusReadRegisters()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusReadInputRegisters()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusWriteBit()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusWriteBits()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusWriteRegister()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusWriteRegisters()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_modbusWriteAndReadRegisters()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_uploadJob()));
    cmdList->push_back((YapiCommand*) (new apifun_SerialPort_selectJob()));
  }

//--- (end of SerialPort functions)
