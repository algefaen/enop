/*********************************************************************
 *
 * $Id: YColorLed.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle ColorLed functions
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
#include "yocto_colorled.h"

using namespace std;

//--- (YColorLed definitions)

//--- (end of YColorLed definitions)

bool   isModule(void)      { return false; }

//--- (YColorLed implementation)
string YFunctionName(void) { return "ColorLed"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of rgbColor is int (U24Color)
// type of hslColor is int (U24Color)
// type of rgbColorAtPowerOn is int (U24Color)
// type of blinkSeqSize is int (UInt31)
// type of blinkSeqMaxSize is int (UInt31)
// type of blinkSeqSignature is int (UInt31)
// type of command is string (Text)
/**
 * Returns the logical name of the RGB led.
 *
 * @return a string corresponding to the logical name of the RGB led
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class ColorLed_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the RGB led.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
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
 * Changes the logical name of the RGB led. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the RGB led
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the RGB led.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the RGB led", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
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
 * Returns a short string representing the current state of the RGB led.
 *
 * @return a string corresponding to a short string representing the current state of the RGB led
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class ColorLed_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the RGB led.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
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
 * Returns the current RGB color of the led.
 *
 * @return an integer corresponding to the current RGB color of the led
 *
 * On failure, throws an exception or returns Y_RGBCOLOR_INVALID.
 */
class ColorLed_get_rgbColor : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_rgbColor";
  }

  string getDescription()
  {
    return "Returns the current RGB color of the led.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rgbColor();
        char buf[32]; snprintf(buf,32,"#%06x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current color of the led, using a RGB color. Encoding is done as follows: 0xRRGGBB.
 *
 * @param newval : an integer corresponding to the current color of the led, using a RGB color
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_rgbColor : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_rgbColor";
  }

  string getDescription()
  {
    return "Changes the current color of the led, using a RGB color.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xRRGGBB.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the current color of the led, using a RGB color", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_rgbColor(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the current HSL color of the led.
 *
 * @return an integer corresponding to the current HSL color of the led
 *
 * On failure, throws an exception or returns Y_HSLCOLOR_INVALID.
 */
class ColorLed_get_hslColor : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_hslColor";
  }

  string getDescription()
  {
    return "Returns the current HSL color of the led.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_hslColor();
        char buf[32]; snprintf(buf,32,"#%06x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the current color of the led, using a color HSL. Encoding is done as follows: 0xHHSSLL.
 *
 * @param newval : an integer corresponding to the current color of the led, using a color HSL
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_hslColor : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_hslColor";
  }

  string getDescription()
  {
    return "Changes the current color of the led, using a color HSL.";
  }

  string getMoreInfo()
  {
    return "Encoding is done as follows: 0xHHSSLL.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the current color of the led, using a color HSL", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_hslColor(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Performs a smooth transition in the RGB color space between the current color and a target color.
 *
 * @param rgb_target  : desired RGB color at the end of the transition
 * @param ms_duration : duration of the transition, in millisecond
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_ColorLed_rgbMove : public YapiCommand /* arguments: rgb_target ms_duration */
{
public:

  string getName()
  {
    return "rgbMove";
  }

  string getDescription()
  {
    return "Performs a smooth transition in the RGB color space between the current color and a target color.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "rgb_target", "desired RGB color at the end of the transition", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "duration of the transition, in millisecond", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->rgbMove((int)(*args)[0]->get_intValue(),
                            (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Performs a smooth transition in the HSL color space between the current color and a target color.
 *
 * @param hsl_target  : desired HSL color at the end of the transition
 * @param ms_duration : duration of the transition, in millisecond
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class alias_ColorLed_hslMove : public YapiCommand /* arguments: hsl_target ms_duration */
{
public:

  string getName()
  {
    return "hslMove";
  }

  string getDescription()
  {
    return "Performs a smooth transition in the HSL color space between the current color and a target color.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "hsl_target", "desired HSL color at the end of the transition", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "ms_duration", "duration of the transition, in millisecond", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->hslMove((int)(*args)[0]->get_intValue(),
                            (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the configured color to be displayed when the module is turned on.
 *
 * @return an integer corresponding to the configured color to be displayed when the module is turned on
 *
 * On failure, throws an exception or returns Y_RGBCOLORATPOWERON_INVALID.
 */
class ColorLed_get_rgbColorAtPowerOn : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_rgbColorAtPowerOn";
  }

  string getDescription()
  {
    return "Returns the configured color to be displayed when the module is turned on.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_rgbColorAtPowerOn();
        char buf[32]; snprintf(buf,32,"#%06x",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the color that the led will display by default when the module is turned on.
 *
 * @param newval : an integer corresponding to the color that the led will display by default when the
 * module is turned on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class ColorLed_set_rgbColorAtPowerOn : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_rgbColorAtPowerOn";
  }

  string getDescription()
  {
    return "Changes the color that the led will display by default when the module is turned on.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the color that the led will display by default when the module is turned on", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_rgbColorAtPowerOn(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Return the blinking sequence signature. Since blinking
 * sequences cannot be read from the device, this can be used
 * to detect if a specific blinking sequence is already
 * programmed.
 *
 * @return an integer
 *
 * On failure, throws an exception or returns Y_BLINKSEQSIGNATURE_INVALID.
 */
class ColorLed_get_blinkSeqSignature : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_blinkSeqSignature";
  }

  string getDescription()
  {
    return "Return the blinking sequence signature.";
  }

  string getMoreInfo()
  {
    return "Since blinking sequences cannot be read from the device, this can be used to detect if a specific blinking sequence is already programmed.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_blinkSeqSignature();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackColorLed is YColorLedValueCallback* (YColorLedValueCallback)
/**
 * Add a new transition to the blinking sequence, the move will
 * be performed in the HSL space.
 *
 * @param HSLcolor : desired HSL color when the traisntion is completed
 * @param msDelay : duration of the color transition, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_addHslMoveToBlinkSeq : public YapiCommand /* arguments: HSLcolor msDelay */
{
public:

  string getName()
  {
    return "addHslMoveToBlinkSeq";
  }

  string getDescription()
  {
    return "Add a new transition to the blinking sequence, the move willbe performed in the HSL space.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "HSLcolor", "desired HSL color when the traisntion is completed", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "msDelay", "duration of the color transition, in milliseconds.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addHslMoveToBlinkSeq((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Add a new transition to the blinking sequence, the move will
 * be performed in the RGB space.
 *
 * @param RGBcolor : desired RGB color when the transition is completed
 * @param msDelay : duration of the color transition, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_addRgbMoveToBlinkSeq : public YapiCommand /* arguments: RGBcolor msDelay */
{
public:

  string getName()
  {
    return "addRgbMoveToBlinkSeq";
  }

  string getDescription()
  {
    return "Add a new transition to the blinking sequence, the move willbe performed in the RGB space.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "RGBcolor", "desired RGB color when the transition is completed", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "msDelay", "duration of the color transition, in milliseconds.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->addRgbMoveToBlinkSeq((int)(*args)[0]->get_intValue(),
                                         (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts the preprogrammed blinking sequence. The sequence will
 * run in loop until it is stopped by stopBlinkSeq or an explicit
 * change.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_startBlinkSeq : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "startBlinkSeq";
  }

  string getDescription()
  {
    return "Starts the preprogrammed blinking sequence.";
  }

  string getMoreInfo()
  {
    return "The sequence will run in loop until it is stopped by stopBlinkSeq or an explicit change.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->startBlinkSeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops the preprogrammed blinking sequence.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_stopBlinkSeq : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "stopBlinkSeq";
  }

  string getDescription()
  {
    return "Stops the preprogrammed blinking sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->stopBlinkSeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Resets the preprogrammed blinking sequence.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *         On failure, throws an exception or returns a negative error code.
 */
class apifun_ColorLed_resetBlinkSeq : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "resetBlinkSeq";
  }

  string getDescription()
  {
    return "Resets the preprogrammed blinking sequence.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YColorLed*>* list = enumerateTargets<YColorLed>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetBlinkSeq();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YColorLed implementation)

//--- (ColorLed functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YColorLed>(cmdList);
    cmdList->push_back((YapiCommand*) (new ColorLed_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_rgbColor()));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_rgbColor()));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_hslColor()));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_hslColor()));
    cmdList->push_back((YapiCommand*) (new alias_ColorLed_rgbMove()));
    cmdList->push_back((YapiCommand*) (new alias_ColorLed_hslMove()));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_rgbColorAtPowerOn()));
    cmdList->push_back((YapiCommand*) (new ColorLed_set_rgbColorAtPowerOn()));
    cmdList->push_back((YapiCommand*) (new ColorLed_get_blinkSeqSignature()));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_addHslMoveToBlinkSeq()));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_addRgbMoveToBlinkSeq()));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_startBlinkSeq()));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_stopBlinkSeq()));
    cmdList->push_back((YapiCommand*) (new apifun_ColorLed_resetBlinkSeq()));
  }

//--- (end of ColorLed functions)
