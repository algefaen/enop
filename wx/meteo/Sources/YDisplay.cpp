/*********************************************************************
 *
 * $Id: YDisplay.cpp 19661 2015-03-10 14:41:23Z mvuilleu $
 *
 * Implements commands to handle Display functions
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
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <istream>
#include <stdio.h>
#include "cmdline_common.h"
#include "yocto_api.h"
#include "yocto_display.h"

using namespace std;

//--- (generated code: YDisplay definitions)

const char *enumBool[] = {
    "FALSE",
    "TRUE",
    NULL
};

const char *enumDisplayType[] = {
    "MONO",
    "GRAY",
    "RGB",
    NULL
};

const char *enumOrientation[] = {
    "LEFT",
    "UP",
    "RIGHT",
    "DOWN",
    NULL
};

//--- (end of generated code: YDisplay definitions)

//--- (generated code: YDisplayLayer definitions)

const char *Align[] = {
    "TOP_LEFT",
    "CENTER_LEFT",
    "BASELINE_LEFT",
    "BOTTOM_LEFT",
    "TOP_CENTER",
    "CENTER",
    "BASELINE_CENTER",
    "BOTTOM_CENTER",
    "TOP_DECIMAL",
    "CENTER_DECIMAL",
    "BASELINE_DECIMAL",
    "BOTTOM_DECIMAL",
    "TOP_RIGHT",
    "CENTER_RIGHT",
    "BASELINE_RIGHT",
    "BOTTOM_RIGHT",
    NULL
};

//--- (end of generated code: YDisplayLayer definitions)

bool   isModule(void)      { return false; }

// some Display Layer generic code
static vector<SwitchDesc*>* GetLayerSwitch()
{
    vector<SwitchDesc*>* res = new vector<SwitchDesc*>();
	res->push_back(new SwitchDesc("-layer",INT_ARG, "layer#", "Index of the layer you want to work with, first layer is 0, use get_layerCount to know the layer count.", "_INT", true,"0"));
	return res;
}


static YDisplayLayer *GetCmdLayer(YapiCommand *cmd, YDisplay* display, vector<SwitchDesc*>* switches )
{  int layerindex = (int)cmd->getSwitchIntValue(switches,"-layer");
    int layercount = display->get_layerCount();
    if ((layerindex<0) || (layerindex>=layercount))
    {   char buf[16];
        sprintf(buf, "%d", layercount-1);
        YapiCommand::fatalError("Invalid layer index for "+display->get_friendlyName()+", valid values are [0.."+string(buf)+"]");
    }
	return display->get_displayLayer(layerindex);
}

/**
 * Output a message in the console area, and advance the console pointer accordingly.
 * The console pointer position is automatically moved to the beginning
 * of the next line when a newline character is met, or when the right margin
 * is hit. When the new text to display extends below the lower margin, the
 * console area is automatically scrolled up.
 *
 * @param text: the message to display
 *
 * @return nothing.
 */
class apifun_pipe : public YapiCommand /* arguments: text */
{
public:

    string getName()
    {
        return "pipe";
    }

    string getDescription()
    {
        return "Echo any data provided on stdin to the console output of the display.";
    }

    string getMoreInfo()
    {
        return "The console pointer position is automatically moved to the beginning\nof the next line when a newline character is met, or when the right margin\nis hit. When the new text to display extends below the lower margin, the\nconsole area is automatically scrolled up.";
    }

    vector<ArgumentDesc*>* getArgumentDesc()
    {
        vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
        return res;
    }

    vector<SwitchDesc*>* getSwitchDesc()
    {
        return GetLayerSwitch();
    }

    void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
    {
        vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
        unsigned int i;
        string value = "";
        string line;
        int w,h;
        for (i = 0; i < list->size(); i++)
        {
            YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
            w = (*list)[i]->get_displayWidth();
            h = (*list)[i]->get_displayHeight();
            layer->setConsoleMargins(0, 0, w, h);
        }
        while(std::getline(std::cin, line))
        {
            for (i = 0; i < list->size(); i++)
            {
                YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
                layer->consoleOut(line+"\n");
                layer->flush_now();
                PrintResult(resultformat, this->getName(),(*list)[i], value, true);
            }
        }
    }
};


//--- (generated code: YDisplayLayer implementation)

/**
 * Reverts the layer to its initial state (fully transparent, default settings).
 * Reinitializes the drawing pointer to the upper left position,
 * and selects the most visible pen color. If you only want to erase the layer
 * content, use the method clear() instead.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_reset : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "reset";
  }

  string getDescription()
  {
    return "Reverts the layer to its initial state (fully transparent, default settings).";
  }

  string getMoreInfo()
  {
    return "Reinitializes the drawing pointer to the upper left position, and selects the most visible pen color. If you only want to erase the layer content, use the method clear() instead.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->reset();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Erases the whole content of the layer (makes it fully transparent).
 * This method does not change any other attribute of the layer.
 * To reinitialize the layer attributes to defaults settings, use the method
 * reset() instead.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_clear : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "clear";
  }

  string getDescription()
  {
    return "Erases the whole content of the layer (makes it fully transparent).";
  }

  string getMoreInfo()
  {
    return "This method does not change any other attribute of the layer. To reinitialize the layer attributes to defaults settings, use the method reset() instead.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->clear();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Selects the pen color for all subsequent drawing functions,
 * including text drawing. The pen color is provided as an RGB value.
 * For grayscale or monochrome displays, the value is
 * automatically converted to the proper range.
 *
 * @param color : the desired pen color, as a 24-bit RGB value
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_selectColorPen : public YapiCommand /* arguments: color */
{
public:

  string getName()
  {
    return "selectColorPen";
  }

  string getDescription()
  {
    return "Selects the pen color for all subsequent drawing functions,including text drawing.";
  }

  string getMoreInfo()
  {
    return "The pen color is provided as an RGB value. For grayscale or monochrome displays, the value is automatically converted to the proper range.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "color", "the desired pen color, as a 24-bit RGB value", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->selectColorPen((int)(*args)[0]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Selects the pen gray level for all subsequent drawing functions,
 * including text drawing. The gray level is provided as a number between
 * 0 (black) and 255 (white, or whichever the lighest color is).
 * For monochrome displays (without gray levels), any value
 * lower than 128 is rendered as black, and any value equal
 * or above to 128 is non-black.
 *
 * @param graylevel : the desired gray level, from 0 to 255
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_selectGrayPen : public YapiCommand /* arguments: graylevel */
{
public:

  string getName()
  {
    return "selectGrayPen";
  }

  string getDescription()
  {
    return "Selects the pen gray level for all subsequent drawing functions,including text drawing.";
  }

  string getMoreInfo()
  {
    return "The gray level is provided as a number between 0 (black) and 255 (white, or whichever the lighest color is). For monochrome displays (without gray levels), any value lower than 128 is rendered as black, and any value equal or above to 128 is non-black.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "graylevel", "the desired gray level, from 0 to 255", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->selectGrayPen((int)(*args)[0]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Selects an eraser instead of a pen for all subsequent drawing functions,
 * except for bitmap copy functions. Any point drawn using the eraser
 * becomes transparent (as when the layer is empty), showing the other
 * layers beneath it.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_selectEraser : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "selectEraser";
  }

  string getDescription()
  {
    return "Selects an eraser instead of a pen for all subsequent drawing functions,except for bitmap copy functions.";
  }

  string getMoreInfo()
  {
    return "Any point drawn using the eraser becomes transparent (as when the layer is empty), showing the other layers beneath it.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->selectEraser();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Enables or disables anti-aliasing for drawing oblique lines and circles.
 * Anti-aliasing provides a smoother aspect when looked from far enough,
 * but it can add fuzzyness when the display is looked from very close.
 * At the end of the day, it is your personal choice.
 * Anti-aliasing is enabled by default on grayscale and color displays,
 * but you can disable it if you prefer. This setting has no effect
 * on monochrome displays.
 *
 * @param mode : <t>true</t> to enable antialiasing, <t>false</t> to
 *         disable it.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_setAntialiasingMode : public YapiCommand /* arguments: mode */
{
public:

  string getName()
  {
    return "setAntialiasingMode";
  }

  string getDescription()
  {
    return "Enables or disables anti-aliasing for drawing oblique lines and circles.";
  }

  string getMoreInfo()
  {
    return "Anti-aliasing provides a smoother aspect when looked from far enough, but it can add fuzzyness when the display is looked from very close. At the end of the day, it is your personal choice. Anti-aliasing is enabled by default on grayscale and color displays, but you can disable it if you prefer. This setting has no effect on monochrome displays.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(BOOL_ARG, "mode", "<t>true</t> to enable antialiasing, <t>false</t> to disable it.", "_BOOL", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->setAntialiasingMode((bool)(*args)[0]->get_boolValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws a single pixel at the specified position.
 *
 * @param x : the distance from left of layer, in pixels
 * @param y : the distance from top of layer, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawPixel : public YapiCommand /* arguments: x y */
{
public:

  string getName()
  {
    return "drawPixel";
  }

  string getDescription()
  {
    return "Draws a single pixel at the specified position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawPixel((int)(*args)[0]->get_intValue(),
                         (int)(*args)[1]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws an empty rectangle at a specified position.
 *
 * @param x1 : the distance from left of layer to the left border of the rectangle, in pixels
 * @param y1 : the distance from top of layer to the top border of the rectangle, in pixels
 * @param x2 : the distance from left of layer to the right border of the rectangle, in pixels
 * @param y2 : the distance from top of layer to the bottom border of the rectangle, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawRect : public YapiCommand /* arguments: x1 y1 x2 y2 */
{
public:

  string getName()
  {
    return "drawRect";
  }

  string getDescription()
  {
    return "Draws an empty rectangle at a specified position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x1", "the distance from left of layer to the left border of the rectangle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y1", "the distance from top of layer to the top border of the rectangle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "x2", "the distance from left of layer to the right border of the rectangle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y2", "the distance from top of layer to the bottom border of the rectangle, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawRect((int)(*args)[0]->get_intValue(),
                        (int)(*args)[1]->get_intValue(),
                        (int)(*args)[2]->get_intValue(),
                        (int)(*args)[3]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws a filled rectangular bar at a specified position.
 *
 * @param x1 : the distance from left of layer to the left border of the rectangle, in pixels
 * @param y1 : the distance from top of layer to the top border of the rectangle, in pixels
 * @param x2 : the distance from left of layer to the right border of the rectangle, in pixels
 * @param y2 : the distance from top of layer to the bottom border of the rectangle, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawBar : public YapiCommand /* arguments: x1 y1 x2 y2 */
{
public:

  string getName()
  {
    return "drawBar";
  }

  string getDescription()
  {
    return "Draws a filled rectangular bar at a specified position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x1", "the distance from left of layer to the left border of the rectangle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y1", "the distance from top of layer to the top border of the rectangle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "x2", "the distance from left of layer to the right border of the rectangle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y2", "the distance from top of layer to the bottom border of the rectangle, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawBar((int)(*args)[0]->get_intValue(),
                       (int)(*args)[1]->get_intValue(),
                       (int)(*args)[2]->get_intValue(),
                       (int)(*args)[3]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws an empty circle at a specified position.
 *
 * @param x : the distance from left of layer to the center of the circle, in pixels
 * @param y : the distance from top of layer to the center of the circle, in pixels
 * @param r : the radius of the circle, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawCircle : public YapiCommand /* arguments: x y r */
{
public:

  string getName()
  {
    return "drawCircle";
  }

  string getDescription()
  {
    return "Draws an empty circle at a specified position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer to the center of the circle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer to the center of the circle, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "r", "the radius of the circle, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawCircle((int)(*args)[0]->get_intValue(),
                          (int)(*args)[1]->get_intValue(),
                          (int)(*args)[2]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws a filled disc at a given position.
 *
 * @param x : the distance from left of layer to the center of the disc, in pixels
 * @param y : the distance from top of layer to the center of the disc, in pixels
 * @param r : the radius of the disc, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawDisc : public YapiCommand /* arguments: x y r */
{
public:

  string getName()
  {
    return "drawDisc";
  }

  string getDescription()
  {
    return "Draws a filled disc at a given position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer to the center of the disc, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer to the center of the disc, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "r", "the radius of the disc, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawDisc((int)(*args)[0]->get_intValue(),
                        (int)(*args)[1]->get_intValue(),
                        (int)(*args)[2]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Selects a font to use for the next text drawing functions, by providing the name of the
 * font file. You can use a built-in font as well as a font file that you have previously
 * uploaded to the device built-in memory. If you experience problems selecting a font
 * file, check the device logs for any error message such as missing font file or bad font
 * file format.
 *
 * @param fontname : the font file name
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_selectFont : public YapiCommand /* arguments: fontname */
{
public:

  string getName()
  {
    return "selectFont";
  }

  string getDescription()
  {
    return "Selects a font to use for the next text drawing functions, by providing the name of thefont file.";
  }

  string getMoreInfo()
  {
    return "You can use a built-in font as well as a font file that you have previously uploaded to the device built-in memory. If you experience problems selecting a font file, check the device logs for any error message such as missing font file or bad font file format.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "fontname", "the font file name", "_STRING", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->selectFont((*args)[0]->get_stringValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws a text string at the specified position. The point of the text that is aligned
 * to the specified pixel position is called the anchor point, and can be chosen among
 * several options. Text is rendered from left to right, without implicit wrapping.
 *
 * @param x : the distance from left of layer to the text anchor point, in pixels
 * @param y : the distance from top of layer to the text anchor point, in pixels
 * @param anchor : the text anchor point, chosen among the Y_ALIGN enumeration:
 *         Y_ALIGN_TOP_LEFT,    Y_ALIGN_CENTER_LEFT,    Y_ALIGN_BASELINE_LEFT,    Y_ALIGN_BOTTOM_LEFT,
 *         Y_ALIGN_TOP_CENTER,  Y_ALIGN_CENTER,         Y_ALIGN_BASELINE_CENTER,  Y_ALIGN_BOTTOM_CENTER,
 *         Y_ALIGN_TOP_DECIMAL, Y_ALIGN_CENTER_DECIMAL, Y_ALIGN_BASELINE_DECIMAL, Y_ALIGN_BOTTOM_DECIMAL,
 *         Y_ALIGN_TOP_RIGHT,   Y_ALIGN_CENTER_RIGHT,   Y_ALIGN_BASELINE_RIGHT,   Y_ALIGN_BOTTOM_RIGHT.
 * @param text : the text string to draw
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawText : public YapiCommand /* arguments: x y anchor text */
{
public:

  string getName()
  {
    return "drawText";
  }

  string getDescription()
  {
    return "Draws a text string at the specified position.";
  }

  string getMoreInfo()
  {
    return "The point of the text that is aligned to the specified pixel position is called the anchor point, and can be chosen among several options. Text is rendered from left to right, without implicit wrapping.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer to the text anchor point, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer to the text anchor point, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "anchor", "the text anchor point, chosen among the ALIGN enumeration: TOP_LEFT, CENTER_LEFT, BASELINE_LEFT, BOTTOM_LEFT, TOP_CENTER, CENTER, BASELINE_CENTER, BOTTOM_CENTER, TOP_DECIMAL, CENTER_DECIMAL, BASELINE_DECIMAL, BOTTOM_DECIMAL, TOP_RIGHT, CENTER_RIGHT, BASELINE_RIGHT, BOTTOM_RIGHT.", "TOP_LEFT=0,CENTER_LEFT=1,BASELINE_LEFT=2,BOTTOM_LEFT=3,TOP_CENTER=4,CENTER=5,BASELINE_CENTER=6,BOTTOM_CENTER=7,TOP_DECIMAL=8,CENTER_DECIMAL=9,BASELINE_DECIMAL=10,BOTTOM_DECIMAL=11,TOP_RIGHT=12,CENTER_RIGHT=13,BASELINE_RIGHT=14,BOTTOM_RIGHT=15", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "text", "the text string to draw", "_STRING", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawText((int)(*args)[0]->get_intValue(),
                        (int)(*args)[1]->get_intValue(),
                        (Y_ALIGN)(*args)[2]->get_intValue(),
                        (*args)[3]->get_stringValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws a GIF image at the specified position. The GIF image must have been previously
 * uploaded to the device built-in memory. If you experience problems using an image
 * file, check the device logs for any error message such as missing image file or bad
 * image file format.
 *
 * @param x : the distance from left of layer to the left of the image, in pixels
 * @param y : the distance from top of layer to the top of the image, in pixels
 * @param imagename : the GIF file name
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawImage : public YapiCommand /* arguments: x y imagename */
{
public:

  string getName()
  {
    return "drawImage";
  }

  string getDescription()
  {
    return "Draws a GIF image at the specified position.";
  }

  string getMoreInfo()
  {
    return "The GIF image must have been previously uploaded to the device built-in memory. If you experience problems using an image file, check the device logs for any error message such as missing image file or bad image file format.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer to the left of the image, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer to the top of the image, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(STRING_ARG, "imagename", "the GIF file name", "_STRING", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawImage((int)(*args)[0]->get_intValue(),
                         (int)(*args)[1]->get_intValue(),
                         (*args)[2]->get_stringValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws a bitmap at the specified position. The bitmap is provided as a binary object,
 * where each pixel maps to a bit, from left to right and from top to bottom.
 * The most significant bit of each byte maps to the leftmost pixel, and the least
 * significant bit maps to the rightmost pixel. Bits set to 1 are drawn using the
 * layer selected pen color. Bits set to 0 are drawn using the specified background
 * gray level, unless -1 is specified, in which case they are not drawn at all
 * (as if transparent).
 *
 * @param x : the distance from left of layer to the left of the bitmap, in pixels
 * @param y : the distance from top of layer to the top of the bitmap, in pixels
 * @param w : the width of the bitmap, in pixels
 * @param bitmap : a binary object
 * @param bgcol : the background gray level to use for zero bits (0 = black,
 *         255 = white), or -1 to leave the pixels unchanged
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_drawBitmap : public YapiCommand /* arguments: x y w bitmap bgcol */
{
public:

  string getName()
  {
    return "drawBitmap";
  }

  string getDescription()
  {
    return "Draws a bitmap at the specified position.";
  }

  string getMoreInfo()
  {
    return "The bitmap is provided as a binary object, where each pixel maps to a bit, from left to right and from top to bottom. The most significant bit of each byte maps to the leftmost pixel, and the least significant bit maps to the rightmost pixel. Bits set to 1 are drawn using the layer selected pen color. Bits set to 0 are drawn using the specified background gray level, unless -1 is specified, in which case they are not drawn at all (as if transparent).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer to the left of the bitmap, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer to the top of the bitmap, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "w", "the width of the bitmap, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(BIN_ARG, "bitmap", "a binary object", "_BIN", false));
    res->push_back(new ArgumentDesc(INT_ARG, "bgcol", "the background gray level to use for zero bits (0 = black, 255 = white), or -1 to leave the pixels unchanged", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    value = value + " "+ (*args)[4]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->drawBitmap((int)(*args)[0]->get_intValue(),
                          (int)(*args)[1]->get_intValue(),
                          (int)(*args)[2]->get_intValue(),
                          (*args)[3]->get_binValue(),
                          (int)(*args)[4]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Moves the drawing pointer of this layer to the specified position.
 *
 * @param x : the distance from left of layer, in pixels
 * @param y : the distance from top of layer, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_moveTo : public YapiCommand /* arguments: x y */
{
public:

  string getName()
  {
    return "moveTo";
  }

  string getDescription()
  {
    return "Moves the drawing pointer of this layer to the specified position.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->moveTo((int)(*args)[0]->get_intValue(),
                      (int)(*args)[1]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Draws a line from current drawing pointer position to the specified position.
 * The specified destination pixel is included in the line. The pointer position
 * is then moved to the end point of the line.
 *
 * @param x : the distance from left of layer to the end point of the line, in pixels
 * @param y : the distance from top of layer to the end point of the line, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_lineTo : public YapiCommand /* arguments: x y */
{
public:

  string getName()
  {
    return "lineTo";
  }

  string getDescription()
  {
    return "Draws a line from current drawing pointer position to the specified position.";
  }

  string getMoreInfo()
  {
    return "The specified destination pixel is included in the line. The pointer position is then moved to the end point of the line.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of layer to the end point of the line, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of layer to the end point of the line, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->lineTo((int)(*args)[0]->get_intValue(),
                      (int)(*args)[1]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Outputs a message in the console area, and advances the console pointer accordingly.
 * The console pointer position is automatically moved to the beginning
 * of the next line when a newline character is met, or when the right margin
 * is hit. When the new text to display extends below the lower margin, the
 * console area is automatically scrolled up.
 *
 * @param text : the message to display
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_consoleOut : public YapiCommand /* arguments: text */
{
public:

  string getName()
  {
    return "consoleOut";
  }

  string getDescription()
  {
    return "Outputs a message in the console area, and advances the console pointer accordingly.";
  }

  string getMoreInfo()
  {
    return "The console pointer position is automatically moved to the beginning of the next line when a newline character is met, or when the right margin is hit. When the new text to display extends below the lower margin, the console area is automatically scrolled up.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "text", "the message to display", "_STRING", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->consoleOut((*args)[0]->get_stringValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets up display margins for the consoleOut function.
 *
 * @param x1 : the distance from left of layer to the left margin, in pixels
 * @param y1 : the distance from top of layer to the top margin, in pixels
 * @param x2 : the distance from left of layer to the right margin, in pixels
 * @param y2 : the distance from top of layer to the bottom margin, in pixels
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_setConsoleMargins : public YapiCommand /* arguments: x1 y1 x2 y2 */
{
public:

  string getName()
  {
    return "setConsoleMargins";
  }

  string getDescription()
  {
    return "Sets up display margins for the consoleOut function.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x1", "the distance from left of layer to the left margin, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y1", "the distance from top of layer to the top margin, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "x2", "the distance from left of layer to the right margin, in pixels", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y2", "the distance from top of layer to the bottom margin, in pixels", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    value = value + " "+ (*args)[3]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->setConsoleMargins((int)(*args)[0]->get_intValue(),
                                 (int)(*args)[1]->get_intValue(),
                                 (int)(*args)[2]->get_intValue(),
                                 (int)(*args)[3]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets up the background color used by the clearConsole function and by
 * the console scrolling feature.
 *
 * @param bgcol : the background gray level to use when scrolling (0 = black,
 *         255 = white), or -1 for transparent
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_setConsoleBackground : public YapiCommand /* arguments: bgcol */
{
public:

  string getName()
  {
    return "setConsoleBackground";
  }

  string getDescription()
  {
    return "Sets up the background color used by the clearConsole function and bythe console scrolling feature.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "bgcol", "the background gray level to use when scrolling (0 = black, 255 = white), or -1 for transparent", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->setConsoleBackground((int)(*args)[0]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets up the wrapping behaviour used by the consoleOut function.
 *
 * @param wordwrap : true to wrap only between words,
 *         false to wrap on the last column anyway.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_setConsoleWordWrap : public YapiCommand /* arguments: wordwrap */
{
public:

  string getName()
  {
    return "setConsoleWordWrap";
  }

  string getDescription()
  {
    return "Sets up the wrapping behaviour used by the consoleOut function.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(BOOL_ARG, "wordwrap", "true to wrap only between words, false to wrap on the last column anyway.", "_BOOL", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->setConsoleWordWrap((bool)(*args)[0]->get_boolValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Blanks the console area within console margins, and resets the console pointer
 * to the upper left corner of the console.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_clearConsole : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "clearConsole";
  }

  string getDescription()
  {
    return "Blanks the console area within console margins, and resets the console pointerto the upper left corner of the console.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->clearConsole();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Sets the position of the layer relative to the display upper left corner.
 * When smooth scrolling is used, the display offset of the layer is
 * automatically updated during the next milliseconds to animate the move of the layer.
 *
 * @param x : the distance from left of display to the upper left corner of the layer
 * @param y : the distance from top of display to the upper left corner of the layer
 * @param scrollTime : number of milliseconds to use for smooth scrolling, or
 *         0 if the scrolling should be immediate.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_setLayerPosition : public YapiCommand /* arguments: x y scrollTime */
{
public:

  string getName()
  {
    return "setLayerPosition";
  }

  string getDescription()
  {
    return "Sets the position of the layer relative to the display upper left corner.";
  }

  string getMoreInfo()
  {
    return "When smooth scrolling is used, the display offset of the layer is automatically updated during the next milliseconds to animate the move of the layer.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "x", "the distance from left of display to the upper left corner of the layer", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "y", "the distance from top of display to the upper left corner of the layer", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "scrollTime", "number of milliseconds to use for smooth scrolling, or 0 if the scrolling should be immediate.", "_INT", false));
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    value = value + " "+ (*args)[2]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->setLayerPosition((int)(*args)[0]->get_intValue(),
                                (int)(*args)[1]->get_intValue(),
                                (int)(*args)[2]->get_intValue());
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Hides the layer. The state of the layer is perserved but the layer is not displayed
 * on the screen until the next call to unhide(). Hiding the layer can positively
 * affect the drawing speed, since it postpones the rendering until all operations are
 * completed (double-buffering).
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_hide : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "hide";
  }

  string getDescription()
  {
    return "Hides the layer.";
  }

  string getMoreInfo()
  {
    return "The state of the layer is perserved but the layer is not displayed on the screen until the next call to unhide(). Hiding the layer can positively affect the drawing speed, since it postpones the rendering until all operations are completed (double-buffering).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->hide();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Shows the layer. Shows the layer again after a hide command.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_DisplayLayer_unhide : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "unhide";
  }

  string getDescription()
  {
    return "Shows the layer.";
  }

  string getMoreInfo()
  {
    return "Shows the layer again after a hide command.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        layer->unhide();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the display width, in pixels.
 *
 * @return an integer corresponding to the display width, in pixels
 *
 * On failure, throws an exception or returns Y_DISPLAYWIDTH_INVALID.
 */
class apifun_DisplayLayer_get_displayWidth : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_displayWidth";
  }

  string getDescription()
  {
    return "Returns the display width, in pixels.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        int value = layer->get_displayWidth();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the display height, in pixels.
 *
 * @return an integer corresponding to the display height, in pixels
 *
 * On failure, throws an exception or returns Y_DISPLAYHEIGHT_INVALID.
 */
class apifun_DisplayLayer_get_displayHeight : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_displayHeight";
  }

  string getDescription()
  {
    return "Returns the display height, in pixels.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        int value = layer->get_displayHeight();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the width of the layers to draw on, in pixels.
 *
 * @return an integer corresponding to the width of the layers to draw on, in pixels
 *
 * On failure, throws an exception or returns Y_LAYERWIDTH_INVALID.
 */
class apifun_DisplayLayer_get_layerWidth : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_layerWidth";
  }

  string getDescription()
  {
    return "Returns the width of the layers to draw on, in pixels.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        int value = layer->get_layerWidth();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the height of the layers to draw on, in pixels.
 *
 * @return an integer corresponding to the height of the layers to draw on, in pixels
 *
 * On failure, throws an exception or returns Y_LAYERHEIGHT_INVALID.
 */
class apifun_DisplayLayer_get_layerHeight : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_layerHeight";
  }

  string getDescription()
  {
    return "Returns the height of the layers to draw on, in pixels.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  vector<SwitchDesc*>* getSwitchDesc()
  {
    return GetLayerSwitch();
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        YDisplayLayer* layer = GetCmdLayer(this, (*list)[i], switches);
        int value = layer->get_layerHeight();
        layer->flush_now();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YDisplayLayer implementation)

//--- (generated code: YDisplay implementation)
string YFunctionName(void) { return "Display"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of enabled is int (Bool)
// type of startupSeq is string (Text)
// type of brightness is int (Percent)
// type of orientation is int (Orientation)
// type of displayWidth is int (UInt31)
// type of displayHeight is int (UInt31)
// type of displayType is int (DisplayType)
// type of layerWidth is int (UInt31)
// type of layerHeight is int (UInt31)
// type of layerCount is int (UInt31)
// type of command is string (Text)
/**
 * Returns the logical name of the display.
 *
 * @return a string corresponding to the logical name of the display
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class Display_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the display.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
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
 * Changes the logical name of the display. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the display
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Display_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the display.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the display", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
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
 * Returns a short string representing the current state of the display.
 *
 * @return a string corresponding to a short string representing the current state of the display
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class Display_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the display.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
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
 * Returns true if the screen is powered, false otherwise.
 *
 * @return either Y_ENABLED_FALSE or Y_ENABLED_TRUE, according to true if the screen is powered, false otherwise
 *
 * On failure, throws an exception or returns Y_ENABLED_INVALID.
 */
class Display_get_enabled : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_enabled";
  }

  string getDescription()
  {
    return "Returns true if the screen is powered, false otherwise.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_enabled();
        string strval =  enumString(attrval,enumBool);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the power state of the display.
 *
 * @param newval : either Y_ENABLED_FALSE or Y_ENABLED_TRUE, according to the power state of the display
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Display_set_enabled : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_enabled";
  }

  string getDescription()
  {
    return "Changes the power state of the display.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "either FALSE or TRUE, according to the power state of the display", "FALSE=0,TRUE=1", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_enabled(Y_ENABLED_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the name of the sequence to play when the displayed is powered on.
 *
 * @return a string corresponding to the name of the sequence to play when the displayed is powered on
 *
 * On failure, throws an exception or returns Y_STARTUPSEQ_INVALID.
 */
class Display_get_startupSeq : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_startupSeq";
  }

  string getDescription()
  {
    return "Returns the name of the sequence to play when the displayed is powered on.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string attrval = (*list)[i]->get_startupSeq();
        string strval =  attrval;
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the name of the sequence to play when the displayed is powered on.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the name of the sequence to play when the displayed is powered on
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Display_set_startupSeq : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_startupSeq";
  }

  string getDescription()
  {
    return "Changes the name of the sequence to play when the displayed is powered on.";
  }

  string getMoreInfo()
  {
    return "Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the name of the sequence to play when the displayed is powered on", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_startupSeq(string((*args)[0]->get_stringValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the luminosity of the  module informative leds (from 0 to 100).
 *
 * @return an integer corresponding to the luminosity of the  module informative leds (from 0 to 100)
 *
 * On failure, throws an exception or returns Y_BRIGHTNESS_INVALID.
 */
class Display_get_brightness : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_brightness";
  }

  string getDescription()
  {
    return "Returns the luminosity of the module informative leds (from 0 to 100).";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_brightness();
        char buf[32]; snprintf(buf, 32,"%u%%", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the brightness of the display. The parameter is a value between 0 and
 * 100. Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : an integer corresponding to the brightness of the display
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Display_set_brightness : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_brightness";
  }

  string getDescription()
  {
    return "Changes the brightness of the display.";
  }

  string getMoreInfo()
  {
    return "The parameter is a value between 0 and 100. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "an integer corresponding to the brightness of the display", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_brightness(int((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the currently selected display orientation.
 *
 * @return a value among Y_ORIENTATION_LEFT, Y_ORIENTATION_UP, Y_ORIENTATION_RIGHT and
 * Y_ORIENTATION_DOWN corresponding to the currently selected display orientation
 *
 * On failure, throws an exception or returns Y_ORIENTATION_INVALID.
 */
class Display_get_orientation : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_orientation";
  }

  string getDescription()
  {
    return "Returns the currently selected display orientation.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_orientation();
        string strval =  enumString(attrval,enumOrientation);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the display orientation. Remember to call the saveToFlash()
 * method of the module if the modification must be kept.
 *
 * @param newval : a value among Y_ORIENTATION_LEFT, Y_ORIENTATION_UP, Y_ORIENTATION_RIGHT and
 * Y_ORIENTATION_DOWN corresponding to the display orientation
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class Display_set_orientation : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_orientation";
  }

  string getDescription()
  {
    return "Changes the display orientation.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method of the module if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "newval", "a value among LEFT, UP, RIGHT and DOWN corresponding to the display orientation", "LEFT=0,UP=1,RIGHT=2,DOWN=3", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_orientation(Y_ORIENTATION_enum((*args)[0]->get_intValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the display width, in pixels.
 *
 * @return an integer corresponding to the display width, in pixels
 *
 * On failure, throws an exception or returns Y_DISPLAYWIDTH_INVALID.
 */
class Display_get_displayWidth : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_displayWidth";
  }

  string getDescription()
  {
    return "Returns the display width, in pixels.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_displayWidth();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the display height, in pixels.
 *
 * @return an integer corresponding to the display height, in pixels
 *
 * On failure, throws an exception or returns Y_DISPLAYHEIGHT_INVALID.
 */
class Display_get_displayHeight : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_displayHeight";
  }

  string getDescription()
  {
    return "Returns the display height, in pixels.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_displayHeight();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the display type: monochrome, gray levels or full color.
 *
 * @return a value among Y_DISPLAYTYPE_MONO, Y_DISPLAYTYPE_GRAY and Y_DISPLAYTYPE_RGB corresponding to
 * the display type: monochrome, gray levels or full color
 *
 * On failure, throws an exception or returns Y_DISPLAYTYPE_INVALID.
 */
class Display_get_displayType : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_displayType";
  }

  string getDescription()
  {
    return "Returns the display type: monochrome, gray levels or full color.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_displayType();
        string strval =  enumString(attrval,enumDisplayType);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the width of the layers to draw on, in pixels.
 *
 * @return an integer corresponding to the width of the layers to draw on, in pixels
 *
 * On failure, throws an exception or returns Y_LAYERWIDTH_INVALID.
 */
class Display_get_layerWidth : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_layerWidth";
  }

  string getDescription()
  {
    return "Returns the width of the layers to draw on, in pixels.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_layerWidth();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the height of the layers to draw on, in pixels.
 *
 * @return an integer corresponding to the height of the layers to draw on, in pixels
 *
 * On failure, throws an exception or returns Y_LAYERHEIGHT_INVALID.
 */
class Display_get_layerHeight : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_layerHeight";
  }

  string getDescription()
  {
    return "Returns the height of the layers to draw on, in pixels.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_layerHeight();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the number of available layers to draw on.
 *
 * @return an integer corresponding to the number of available layers to draw on
 *
 * On failure, throws an exception or returns Y_LAYERCOUNT_INVALID.
 */
class Display_get_layerCount : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_layerCount";
  }

  string getDescription()
  {
    return "Returns the number of available layers to draw on.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int attrval = (*list)[i]->get_layerCount();
        char buf[32]; snprintf(buf, 32,"%d", attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackDisplay is YDisplayValueCallback* (YDisplayValueCallback)
/**
 * Clears the display screen and resets all display layers to their default state.
 * Using this function in a sequence will kill the sequence play-back. Don't use that
 * function to reset the display at sequence start-up.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_resetAll : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "resetAll";
  }

  string getDescription()
  {
    return "Clears the display screen and resets all display layers to their default state.";
  }

  string getMoreInfo()
  {
    return "Using this function in a sequence will kill the sequence play-back. Don't use that function to reset the display at sequence start-up.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->resetAll();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Smoothly changes the brightness of the screen to produce a fade-in or fade-out
 * effect.
 *
 * @param brightness : the new screen brightness
 * @param duration : duration of the brightness transition, in milliseconds.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_fade : public YapiCommand /* arguments: brightness duration */
{
public:

  string getName()
  {
    return "fade";
  }

  string getDescription()
  {
    return "Smoothly changes the brightness of the screen to produce a fade-in or fade-outeffect.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "brightness", "the new screen brightness", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "duration", "duration of the brightness transition, in milliseconds.", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->fade((int)(*args)[0]->get_intValue(),
                         (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Starts to record all display commands into a sequence, for later replay.
 * The name used to store the sequence is specified when calling
 * saveSequence(), once the recording is complete.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_newSequence : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "newSequence";
  }

  string getDescription()
  {
    return "Starts to record all display commands into a sequence, for later replay.";
  }

  string getMoreInfo()
  {
    return "The name used to store the sequence is specified when calling saveSequence(), once the recording is complete.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->newSequence();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops recording display commands and saves the sequence into the specified
 * file on the display internal memory. The sequence can be later replayed
 * using playSequence().
 *
 * @param sequenceName : the name of the newly created sequence
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_saveSequence : public YapiCommand /* arguments: sequenceName */
{
public:

  string getName()
  {
    return "saveSequence";
  }

  string getDescription()
  {
    return "Stops recording display commands and saves the sequence into the specifiedfile on the display internal memory.";
  }

  string getMoreInfo()
  {
    return "The sequence can be later replayed using playSequence().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "sequenceName", "the name of the newly created sequence", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->saveSequence((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Replays a display sequence previously recorded using
 * newSequence() and saveSequence().
 *
 * @param sequenceName : the name of the newly created sequence
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_playSequence : public YapiCommand /* arguments: sequenceName */
{
public:

  string getName()
  {
    return "playSequence";
  }

  string getDescription()
  {
    return "Replays a display sequence previously recorded usingnewSequence() and saveSequence().";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "sequenceName", "the name of the newly created sequence", "_STRING", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->playSequence((*args)[0]->get_stringValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Waits for a specified delay (in milliseconds) before playing next
 * commands in current sequence. This method can be used while
 * recording a display sequence, to insert a timed wait in the sequence
 * (without any immediate effect). It can also be used dynamically while
 * playing a pre-recorded sequence, to suspend or resume the execution of
 * the sequence. To cancel a delay, call the same method with a zero delay.
 *
 * @param delay_ms : the duration to wait, in milliseconds
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_pauseSequence : public YapiCommand /* arguments: delay_ms */
{
public:

  string getName()
  {
    return "pauseSequence";
  }

  string getDescription()
  {
    return "Waits for a specified delay (in milliseconds) before playing nextcommands in current sequence.";
  }

  string getMoreInfo()
  {
    return "This method can be used while recording a display sequence, to insert a timed wait in the sequence (without any immediate effect). It can also be used dynamically while playing a pre-recorded sequence, to suspend or resume the execution of the sequence. To cancel a delay, call the same method with a zero delay.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "delay_ms", "the duration to wait, in milliseconds", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->pauseSequence((int)(*args)[0]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Stops immediately any ongoing sequence replay.
 * The display is left as is.
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_stopSequence : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "stopSequence";
  }

  string getDescription()
  {
    return "Stops immediately any ongoing sequence replay.";
  }

  string getMoreInfo()
  {
    return "The display is left as is.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->stopSequence();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Uploads an arbitrary file (for instance a GIF file) to the display, to the
 * specified full path name. If a file already exists with the same path name,
 * its content is overwritten.
 *
 * @param pathname : path and name of the new file to create
 * @param content : binary buffer with the content to set
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_upload : public YapiCommand /* arguments: pathname content */
{
public:

  string getName()
  {
    return "upload";
  }

  string getDescription()
  {
    return "Uploads an arbitrary file (for instance a GIF file) to the display, to thespecified full path name.";
  }

  string getMoreInfo()
  {
    return "If a file already exists with the same path name, its content is overwritten.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "pathname", "path and name of the new file to create", "_STRING", false));
    res->push_back(new ArgumentDesc(BIN_ARG, "content", "binary buffer with the content to set", "_BIN", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->upload((*args)[0]->get_stringValue(),
                           (*args)[1]->get_binValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Copies the whole content of a layer to another layer. The color and transparency
 * of all the pixels from the destination layer are set to match the source pixels.
 * This method only affects the displayed content, but does not change any
 * property of the layer object.
 * Note that layer 0 has no transparency support (it is always completely opaque).
 *
 * @param srcLayerId : the identifier of the source layer (a number in range 0..layerCount-1)
 * @param dstLayerId : the identifier of the destination layer (a number in range 0..layerCount-1)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_copyLayerContent : public YapiCommand /* arguments: srcLayerId dstLayerId */
{
public:

  string getName()
  {
    return "copyLayerContent";
  }

  string getDescription()
  {
    return "Copies the whole content of a layer to another layer.";
  }

  string getMoreInfo()
  {
    return "The color and transparency of all the pixels from the destination layer are set to match the source pixels. This method only affects the displayed content, but does not change any property of the layer object. Note that layer 0 has no transparency support (it is always completely opaque).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "srcLayerId", "the identifier of the source layer (a number in range 0..layerCount-1)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "dstLayerId", "the identifier of the destination layer (a number in range 0..layerCount-1)", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->copyLayerContent((int)(*args)[0]->get_intValue(),
                                     (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Swaps the whole content of two layers. The color and transparency of all the pixels from
 * the two layers are swapped. This method only affects the displayed content, but does
 * not change any property of the layer objects. In particular, the visibility of each
 * layer stays unchanged. When used between onae hidden layer and a visible layer,
 * this method makes it possible to easily implement double-buffering.
 * Note that layer 0 has no transparency support (it is always completely opaque).
 *
 * @param layerIdA : the first layer (a number in range 0..layerCount-1)
 * @param layerIdB : the second layer (a number in range 0..layerCount-1)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_Display_swapLayerContent : public YapiCommand /* arguments: layerIdA layerIdB */
{
public:

  string getName()
  {
    return "swapLayerContent";
  }

  string getDescription()
  {
    return "Swaps the whole content of two layers.";
  }

  string getMoreInfo()
  {
    return "The color and transparency of all the pixels from the two layers are swapped. This method only affects the displayed content, but does not change any property of the layer objects. In particular, the visibility of each layer stays unchanged. When used between onae hidden layer and a visible layer, this method makes it possible to easily implement double-buffering. Note that layer 0 has no transparency support (it is always completely opaque).";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "layerIdA", "the first layer (a number in range 0..layerCount-1)", "_INT", false));
    res->push_back(new ArgumentDesc(INT_ARG, "layerIdB", "the second layer (a number in range 0..layerCount-1)", "_INT", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YDisplay*>* list = enumerateTargets<YDisplay>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->swapLayerContent((int)(*args)[0]->get_intValue(),
                                     (int)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of generated code: YDisplay implementation)

static void RegisterDisplayLayerCommands(vector<YapiCommand*>* cmdList)
{
    //--- (generated code: DisplayLayer functions)
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_reset()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_clear()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_selectColorPen()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_selectGrayPen()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_selectEraser()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_setAntialiasingMode()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawPixel()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawRect()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawBar()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawCircle()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawDisc()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_selectFont()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawText()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawImage()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_drawBitmap()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_moveTo()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_lineTo()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_consoleOut()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_setConsoleMargins()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_setConsoleBackground()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_setConsoleWordWrap()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_clearConsole()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_setLayerPosition()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_hide()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_unhide()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_get_displayWidth()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_get_displayHeight()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_get_layerWidth()));
    cmdList->push_back((YapiCommand*) (new apifun_DisplayLayer_get_layerHeight()));
//--- (end of generated code: DisplayLayer functions)
    cmdList->push_back((YapiCommand*) (new apifun_pipe()));
}

//--- (generated code: Display functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YDisplay>(cmdList);
    cmdList->push_back((YapiCommand*) (new Display_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new Display_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new Display_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new Display_get_enabled()));
    cmdList->push_back((YapiCommand*) (new Display_set_enabled()));
    cmdList->push_back((YapiCommand*) (new Display_get_startupSeq()));
    cmdList->push_back((YapiCommand*) (new Display_set_startupSeq()));
    cmdList->push_back((YapiCommand*) (new Display_get_brightness()));
    cmdList->push_back((YapiCommand*) (new Display_set_brightness()));
    cmdList->push_back((YapiCommand*) (new Display_get_orientation()));
    cmdList->push_back((YapiCommand*) (new Display_set_orientation()));
    cmdList->push_back((YapiCommand*) (new Display_get_displayWidth()));
    cmdList->push_back((YapiCommand*) (new Display_get_displayHeight()));
    cmdList->push_back((YapiCommand*) (new Display_get_displayType()));
    cmdList->push_back((YapiCommand*) (new Display_get_layerWidth()));
    cmdList->push_back((YapiCommand*) (new Display_get_layerHeight()));
    cmdList->push_back((YapiCommand*) (new Display_get_layerCount()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_resetAll()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_fade()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_newSequence()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_saveSequence()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_playSequence()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_pauseSequence()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_stopSequence()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_upload()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_copyLayerContent()));
    cmdList->push_back((YapiCommand*) (new apifun_Display_swapLayerContent()));
    RegisterDisplayLayerCommands(cmdList);
  }

//--- (end of generated code: Display functions)

