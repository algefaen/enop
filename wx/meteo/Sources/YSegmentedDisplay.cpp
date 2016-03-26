/*********************************************************************
 *
 * $Id: YSegmentedDisplay.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle SegmentedDisplay functions
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
#include "yocto_segmenteddisplay.h"

using namespace std;

//--- (YSegmentedDisplay definitions)

const char *enumDisplayMode[] = {
    "DISCONNECTED",
    "MANUAL",
    "AUTO1",
    "AUTO60",
    NULL
};

//--- (end of YSegmentedDisplay definitions)

bool   isModule(void)      { return false; }

//--- (YSegmentedDisplay implementation)
string YFunctionName(void) { return "SegmentedDisplay"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of displayedText is string (Text)
// type of displayMode is int (DisplayMode)
/**
 * Returns the logical name of the segmented displays.
 *
 * @return a string corresponding to the logical name of the segmented displays
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class SegmentedDisplay_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the segmented displays.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSegmentedDisplay*>* list = enumerateTargets<YSegmentedDisplay>(target,modulelist);
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
 * Changes the logical name of the segmented displays. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the segmented displays
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SegmentedDisplay_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the segmented displays.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the segmented displays", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSegmentedDisplay*>* list = enumerateTargets<YSegmentedDisplay>(target,modulelist);
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
 * Returns a short string representing the current state of the segmented displays.
 *
 * @return a string corresponding to a short string representing the current state of the segmented displays
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class SegmentedDisplay_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the segmented displays.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSegmentedDisplay*>* list = enumerateTargets<YSegmentedDisplay>(target,modulelist);
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
 * Returns the text currently displayed on the screen.
 *
 * @return a string corresponding to the text currently displayed on the screen
 *
 * On failure, throws an exception or returns Y_DISPLAYEDTEXT_INVALID.
 */
class SegmentedDisplay_get_displayedText : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_displayedText";
  }

  string getDescription()
  {
    return "Returns the text currently displayed on the screen.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YSegmentedDisplay*>* list = enumerateTargets<YSegmentedDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_displayedText();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the text currently displayed on the screen.
 *
 * @param newval : a string corresponding to the text currently displayed on the screen
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class SegmentedDisplay_set_displayedText : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_displayedText";
  }

  string getDescription()
  {
    return "Changes the text currently displayed on the screen.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the text currently displayed on the screen", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YSegmentedDisplay*>* list = enumerateTargets<YSegmentedDisplay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_displayedText(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

// type of valueCallbackSegmentedDisplay is YSegmentedDisplayValueCallback* (YSegmentedDisplayValueCallback)
//--- (end of YSegmentedDisplay implementation)

//--- (SegmentedDisplay functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YSegmentedDisplay>(cmdList);
    cmdList->push_back((YapiCommand*) (new SegmentedDisplay_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new SegmentedDisplay_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new SegmentedDisplay_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new SegmentedDisplay_get_displayedText()));
    cmdList->push_back((YapiCommand*) (new SegmentedDisplay_set_displayedText()));
  }

//--- (end of SegmentedDisplay functions)
