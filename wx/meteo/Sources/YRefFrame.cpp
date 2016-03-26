/*********************************************************************
 *
 * $Id: YRefFrame.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements commands to handle RefFrame functions
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
#include "yocto_refframe.h"

using namespace std;

//--- (YRefFrame definitions)

const char *MountPosition[] = {
    "BOTTOM",
    "TOP",
    "FRONT",
    "REAR",
    "RIGHT",
    "LEFT",
    NULL
};

const char *MountOrientation[] = {
    "TWELVE",
    "THREE",
    "SIX",
    "NINE",
    NULL
};

//--- (end of YRefFrame definitions)

bool   isModule(void)      { return false; }

//--- (YRefFrame implementation)
string YFunctionName(void) { return "Reference frame configuration"; }

// type of logicalName is string (Text)
// type of advertisedValue is string (PubText)
// type of mountPos is int (UInt31)
// type of bearing is double (MeasureVal)
// type of calibrationParam is string (CalibParams)
/**
 * Returns the logical name of the reference frame.
 *
 * @return a string corresponding to the logical name of the reference frame
 *
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
class RefFrame_get_logicalName : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_logicalName";
  }

  string getDescription()
  {
    return "Returns the logical name of the reference frame.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
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
 * Changes the logical name of the reference frame. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 *
 * @param newval : a string corresponding to the logical name of the reference frame
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class RefFrame_set_logicalName : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_logicalName";
  }

  string getDescription()
  {
    return "Changes the logical name of the reference frame.";
  }

  string getMoreInfo()
  {
    return "You can use yCheckLogicalName() prior to this call to make sure that your parameter is valid. Remember to call \"YModule {target} saveToFlash\" if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(STRING_ARG, "newval", "a string corresponding to the logical name of the reference frame", "_LOGICAL", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
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
 * Returns a short string representing the current state of the reference frame.
 *
 * @return a string corresponding to a short string representing the current state of the reference frame
 *
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
class RefFrame_get_advertisedValue : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_advertisedValue";
  }

  string getDescription()
  {
    return "Returns a short string representing the current state of the reference frame.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
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
 * Changes the reference bearing used by the compass. The relative bearing
 * indicated by the compass is the difference between the measured magnetic
 * heading and the reference bearing indicated here.
 *
 * For instance, if you setup as reference bearing the value of the earth
 * magnetic declination, the compass will provide the orientation relative
 * to the geographic North.
 *
 * Similarly, when the sensor is not mounted along the standard directions
 * because it has an additional yaw angle, you can set this angle in the reference
 * bearing so that the compass provides the expected natural direction.
 *
 * Remember to call the saveToFlash()
 * method of the module if the modification must be kept.
 *
 * @param newval : a floating point number corresponding to the reference bearing used by the compass
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class RefFrame_set_bearing : public YapiCommand /* arguments: newval */
{
public:

  string getName()
  {
    return "set_bearing";
  }

  string getDescription()
  {
    return "Changes the reference bearing used by the compass.";
  }

  string getMoreInfo()
  {
    return "The relative bearing indicated by the compass is the difference between the measured magnetic heading and the reference bearing indicated here.\nFor instance, if you setup as reference bearing the value of the earth magnetic declination, the compass will provide the orientation relative to the geographic North.\nSimilarly, when the sensor is not mounted along the standard directions because it has an additional yaw angle, you can set this angle in the reference bearing so that the compass provides the expected natural direction.\nRemember to call the saveToFlash() method of the module if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(DOUBLE_ARG, "newval", "a floating point number corresponding to the reference bearing used by the compass", "_DOUBLE", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    string value = (*args)[0]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_bearing(double((*args)[0]->get_doubleValue()));
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the reference bearing used by the compass. The relative bearing
 * indicated by the compass is the difference between the measured magnetic
 * heading and the reference bearing indicated here.
 *
 * @return a floating point number corresponding to the reference bearing used by the compass
 *
 * On failure, throws an exception or returns Y_BEARING_INVALID.
 */
class RefFrame_get_bearing : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_bearing";
  }

  string getDescription()
  {
    return "Returns the reference bearing used by the compass.";
  }

  string getMoreInfo()
  {
    return "The relative bearing indicated by the compass is the difference between the measured magnetic heading and the reference bearing indicated here.";
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches )
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        double attrval = (*list)[i]->get_bearing();
        char buf[32]; snprintf(buf,32,"%.3f",attrval); string strval =  string(buf);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

// type of valueCallbackRefFrame is YRefFrameValueCallback* (YRefFrameValueCallback)
// type of calibStage is int (int)
// type of calibStageHint is string (str)
// type of calibStageProgress is int (int)
// type of calibProgress is int (int)
// type of calibLogMsg is string (str)
// type of calibSavedParams is string (str)
// type of calibCount is int (int)
// type of calibInternalPos is int (int)
// type of calibPrevTick is int (int)
// type of calibOrient is vector<int> (intArr)
// type of calibDataAccX is vector<double> (floatArr)
// type of calibDataAccY is vector<double> (floatArr)
// type of calibDataAccZ is vector<double> (floatArr)
// type of calibDataAcc is vector<double> (floatArr)
// type of calibAccXOfs is double (float)
// type of calibAccYOfs is double (float)
// type of calibAccZOfs is double (float)
// type of calibAccXScale is double (float)
// type of calibAccYScale is double (float)
// type of calibAccZScale is double (float)
/**
 * Returns the installation position of the device, as configured
 * in order to define the reference frame for the compass and the
 * pitch/roll tilt sensors.
 *
 * @return a value among the Y_MOUNTPOSITION enumeration
 *         (Y_MOUNTPOSITION_BOTTOM,   Y_MOUNTPOSITION_TOP,
 *         Y_MOUNTPOSITION_FRONT,    Y_MOUNTPOSITION_RIGHT,
 *         Y_MOUNTPOSITION_REAR,     Y_MOUNTPOSITION_LEFT),
 *         corresponding to the installation in a box, on one of the six faces.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_RefFrame_get_mountPosition : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_mountPosition";
  }

  string getDescription()
  {
    return "Returns the installation position of the device, as configured in order to define the reference frame for the compass and thepitch/roll tilt sensors.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_mountPosition();
        string strval =  enumString(value,MountPosition);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Returns the installation orientation of the device, as configured
 * in order to define the reference frame for the compass and the
 * pitch/roll tilt sensors.
 *
 * @return a value among the enumeration Y_MOUNTORIENTATION
 *         (Y_MOUNTORIENTATION_TWELVE, Y_MOUNTORIENTATION_THREE,
 *         Y_MOUNTORIENTATION_SIX,     Y_MOUNTORIENTATION_NINE)
 *         corresponding to the orientation of the "X" arrow on the device,
 *         as on a clock dial seen from an observer in the center of the box.
 *         On the bottom face, the 12H orientation points to the front, while
 *         on the top face, the 12H orientation points to the rear.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_RefFrame_get_mountOrientation : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_mountOrientation";
  }

  string getDescription()
  {
    return "Returns the installation orientation of the device, as configured in order to define the reference frame for the compass and thepitch/roll tilt sensors.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_mountOrientation();
        string strval =  enumString(value,MountOrientation);
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), strval, true);
      }
  }
};

/**
 * Changes the compass and tilt sensor frame of reference. The magnetic compass
 * and the tilt sensors (pitch and roll) naturally work in the plane
 * parallel to the earth surface. In case the device is not installed upright
 * and horizontally, you must select its reference orientation (parallel to
 * the earth surface) so that the measures are made relative to this position.
 *
 * @param position : a value among the Y_MOUNTPOSITION enumeration
 *         (Y_MOUNTPOSITION_BOTTOM,   Y_MOUNTPOSITION_TOP,
 *         Y_MOUNTPOSITION_FRONT,    Y_MOUNTPOSITION_RIGHT,
 *         Y_MOUNTPOSITION_REAR,     Y_MOUNTPOSITION_LEFT),
 *         corresponding to the installation in a box, on one of the six faces.
 * @param orientation : a value among the enumeration Y_MOUNTORIENTATION
 *         (Y_MOUNTORIENTATION_TWELVE, Y_MOUNTORIENTATION_THREE,
 *         Y_MOUNTORIENTATION_SIX,     Y_MOUNTORIENTATION_NINE)
 *         corresponding to the orientation of the "X" arrow on the device,
 *         as on a clock dial seen from an observer in the center of the box.
 *         On the bottom face, the 12H orientation points to the front, while
 *         on the top face, the 12H orientation points to the rear.
 *
 * Remember to call the saveToFlash()
 * method of the module if the modification must be kept.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_RefFrame_set_mountPosition : public YapiCommand /* arguments: position orientation */
{
public:

  string getName()
  {
    return "set_mountPosition";
  }

  string getDescription()
  {
    return "Changes the compass and tilt sensor frame of reference.";
  }

  string getMoreInfo()
  {
    return "The magnetic compass and the tilt sensors (pitch and roll) naturally work in the plane parallel to the earth surface. In case the device is not installed upright and horizontally, you must select its reference orientation (parallel to the earth surface) so that the measures are made relative to this position.\n\nRemember to call the saveToFlash() method of the module if the modification must be kept.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    res->push_back(new ArgumentDesc(INT_ARG, "position", "a value among the MOUNTPOSITION enumeration (BOTTOM, TOP, FRONT, RIGHT, REAR, LEFT), corresponding to the installation in a box, on one of the six faces.", "BOTTOM=0,TOP=1,FRONT=2,REAR=3,RIGHT=4,LEFT=5", false));
    res->push_back(new ArgumentDesc(INT_ARG, "orientation", "a value among the enumeration MOUNTORIENTATION (TWELVE, THREE, SIX, NINE) corresponding to the orientation of the \"X\" arrow on the device, as on a clock dial seen from an observer in the center of the box. On the bottom face, the 12H orientation points to the front, while on the top face, the 12H orientation points to the rear.", "TWELVE=0,THREE=1,SIX=2,NINE=3", false));
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    string value = "";
    value = value +  (*args)[0]->to_str();
    value = value + " "+ (*args)[1]->to_str();
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->set_mountPosition((Y_MOUNTPOSITION)(*args)[0]->get_intValue(),
                                      (Y_MOUNTORIENTATION)(*args)[1]->get_intValue());
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Initiates the sensors tridimensional calibration process.
 * This calibration is used at low level for inertial position estimation
 * and to enhance the precision of the tilt sensors.
 *
 * After calling this method, the device should be moved according to the
 * instructions provided by method get_3DCalibrationHint,
 * and more3DCalibration should be invoked about 5 times per second.
 * The calibration procedure is completed when the method
 * get_3DCalibrationProgress returns 100. At this point,
 * the computed calibration parameters can be applied using method
 * save3DCalibration. The calibration process can be canceled
 * at any time using method cancel3DCalibration.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_RefFrame_start3DCalibration : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "start3DCalibration";
  }

  string getDescription()
  {
    return "Initiates the sensors tridimensional calibration process.";
  }

  string getMoreInfo()
  {
    return "This calibration is used at low level for inertial position estimation and to enhance the precision of the tilt sensors.\nAfter calling this method, the device should be moved according to the instructions provided by method get_3DCalibrationHint, and more3DCalibration should be invoked about 5 times per second. The calibration procedure is completed when the method get_3DCalibrationProgress returns 100. At this point, the computed calibration parameters can be applied using method save3DCalibration. The calibration process can be canceled at any time using method cancel3DCalibration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->start3DCalibration();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Continues the sensors tridimensional calibration process previously
 * initiated using method start3DCalibration.
 * This method should be called approximately 5 times per second, while
 * positioning the device according to the instructions provided by method
 * get_3DCalibrationHint. Note that the instructions change during
 * the calibration process.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_RefFrame_more3DCalibration : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "more3DCalibration";
  }

  string getDescription()
  {
    return "Continues the sensors tridimensional calibration process previouslyinitiated using method start3DCalibration.";
  }

  string getMoreInfo()
  {
    return "This method should be called approximately 5 times per second, while positioning the device according to the instructions provided by method get_3DCalibrationHint. Note that the instructions change during the calibration process.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->more3DCalibration();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns instructions to proceed to the tridimensional calibration initiated with
 * method start3DCalibration.
 *
 * @return a character string.
 */
class apifun_RefFrame_get_3DCalibrationHint : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_3DCalibrationHint";
  }

  string getDescription()
  {
    return "Returns instructions to proceed to the tridimensional calibration initiated withmethod start3DCalibration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_3DCalibrationHint();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the global process indicator for the tridimensional calibration
 * initiated with method start3DCalibration.
 *
 * @return an integer between 0 (not started) and 100 (stage completed).
 */
class apifun_RefFrame_get_3DCalibrationProgress : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_3DCalibrationProgress";
  }

  string getDescription()
  {
    return "Returns the global process indicator for the tridimensional calibrationinitiated with method start3DCalibration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_3DCalibrationProgress();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns index of the current stage of the calibration
 * initiated with method start3DCalibration.
 *
 * @return an integer, growing each time a calibration stage is completed.
 */
class apifun_RefFrame_get_3DCalibrationStage : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_3DCalibrationStage";
  }

  string getDescription()
  {
    return "Returns index of the current stage of the calibrationinitiated with method start3DCalibration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_3DCalibrationStage();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the process indicator for the current stage of the calibration
 * initiated with method start3DCalibration.
 *
 * @return an integer between 0 (not started) and 100 (stage completed).
 */
class apifun_RefFrame_get_3DCalibrationStageProgress : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_3DCalibrationStageProgress";
  }

  string getDescription()
  {
    return "Returns the process indicator for the current stage of the calibrationinitiated with method start3DCalibration.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        int value = (*list)[i]->get_3DCalibrationStageProgress();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Returns the latest log message from the calibration process.
 * When no new message is available, returns an empty string.
 *
 * @return a character string.
 */
class apifun_RefFrame_get_3DCalibrationLogMsg : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "get_3DCalibrationLogMsg";
  }

  string getDescription()
  {
    return "Returns the latest log message from the calibration process.";
  }

  string getMoreInfo()
  {
    return "When no new message is available, returns an empty string.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    for (i = 0; i < list->size(); i++)
      {
        string value = (*list)[i]->get_3DCalibrationLogMsg();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Applies the sensors tridimensional calibration parameters that have just been computed.
 * Remember to call the saveToFlash()  method of the module if the changes
 * must be kept when the device is restarted.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_RefFrame_save3DCalibration : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "save3DCalibration";
  }

  string getDescription()
  {
    return "Applies the sensors tridimensional calibration parameters that have just been computed.";
  }

  string getMoreInfo()
  {
    return "Remember to call the saveToFlash() method of the module if the changes must be kept when the device is restarted.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->save3DCalibration();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

/**
 * Aborts the sensors tridimensional calibration process et restores normal settings.
 *
 * On failure, throws an exception or returns a negative error code.
 */
class apifun_RefFrame_cancel3DCalibration : public YapiCommand /* arguments: */
{
public:

  string getName()
  {
    return "cancel3DCalibration";
  }

  string getDescription()
  {
    return "Aborts the sensors tridimensional calibration process et restores normal settings.";
  }

  vector<ArgumentDesc*>* getArgumentDesc()
  {
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
  }

  void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
  {
    vector<YRefFrame*>* list = enumerateTargets<YRefFrame>(target,modulelist);
    unsigned int i;
    string value = "";
    for (i = 0; i < list->size(); i++)
      {
        (*list)[i]->cancel3DCalibration();
        PrintResult(resultformat, this->getName(),YFunctionInfoCache((*list)[i]), value, true);
      }
  }
};

//--- (end of YRefFrame implementation)

//--- (RefFrame functions)
void RegisterCommands(vector<YapiCommand*>* cmdList)
  {
    RegisterGenericFunctions<YRefFrame>(cmdList);
    cmdList->push_back((YapiCommand*) (new RefFrame_get_logicalName()));
    cmdList->push_back((YapiCommand*) (new RefFrame_set_logicalName()));
    cmdList->push_back((YapiCommand*) (new RefFrame_get_advertisedValue()));
    cmdList->push_back((YapiCommand*) (new RefFrame_set_bearing()));
    cmdList->push_back((YapiCommand*) (new RefFrame_get_bearing()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_get_mountPosition()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_get_mountOrientation()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_set_mountPosition()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_start3DCalibration()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_more3DCalibration()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_get_3DCalibrationHint()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_get_3DCalibrationProgress()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_get_3DCalibrationStage()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_get_3DCalibrationStageProgress()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_get_3DCalibrationLogMsg()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_save3DCalibration()));
    cmdList->push_back((YapiCommand*) (new apifun_RefFrame_cancel3DCalibration()));
  }

//--- (end of RefFrame functions)
