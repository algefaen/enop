/*********************************************************************
 *
 * $Id: yocto_pressure.cpp 19609 2015-03-05 10:38:00Z seb $
 *
 * Implements yFindPressure(), the high-level API for Pressure functions
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


#define _CRT_SECURE_NO_DEPRECATE //do not use windows secure crt
#include "yocto_pressure.h"
#include "yapi/yjson.h"
#include "yapi/yapi.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

YPressure::YPressure(const string& func): YSensor(func)
//--- (Pressure initialization)
    ,_valueCallbackPressure(NULL)
    ,_timedReportCallbackPressure(NULL)
//--- (end of Pressure initialization)
{
    _className="Pressure";
}

YPressure::~YPressure()
{
//--- (YPressure cleanup)
//--- (end of YPressure cleanup)
}
//--- (YPressure implementation)
// static attributes


/**
 * Retrieves $AFUNCTION$ for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 *
 * This function does not require that $THEFUNCTION$ is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YPressure.isOnline() to test if $THEFUNCTION$ is
 * indeed online at a given time. In case of ambiguity when looking for
 * $AFUNCTION$ by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 *
 * @param func : a string that uniquely characterizes $THEFUNCTION$
 *
 * @return a YPressure object allowing you to drive $THEFUNCTION$.
 */
YPressure* YPressure::FindPressure(string func)
{
    YPressure* obj = NULL;
    obj = (YPressure*) YFunction::_FindFromCache("Pressure", func);
    if (obj == NULL) {
        obj = new YPressure(func);
        YFunction::_AddToCache("Pressure", func, obj);
    }
    return obj;
}

/**
 * Registers the callback function that is invoked on every change of advertised value.
 * The callback is invoked only during the execution of ySleep or yHandleEvents.
 * This provides control over the time when the callback is triggered. For good responsiveness, remember to call
 * one of these two functions periodically. To unregister a callback, pass a null pointer as argument.
 *
 * @param callback : the callback function to call, or a null pointer. The callback function should take two
 *         arguments: the function object of which the value has changed, and the character string describing
 *         the new advertised value.
 * @noreturn
 */
int YPressure::registerValueCallback(YPressureValueCallback callback)
{
    string val;
    if (callback != NULL) {
        YFunction::_UpdateValueCallbackList(this, true);
    } else {
        YFunction::_UpdateValueCallbackList(this, false);
    }
    _valueCallbackPressure = callback;
    // Immediately invoke value callback with current value
    if (callback != NULL && this->isOnline()) {
        val = _advertisedValue;
        if (!(val == "")) {
            this->_invokeValueCallback(val);
        }
    }
    return 0;
}

int YPressure::_invokeValueCallback(string value)
{
    if (_valueCallbackPressure != NULL) {
        _valueCallbackPressure(this, value);
    } else {
        YSensor::_invokeValueCallback(value);
    }
    return 0;
}

/**
 * Registers the callback function that is invoked on every periodic timed notification.
 * The callback is invoked only during the execution of ySleep or yHandleEvents.
 * This provides control over the time when the callback is triggered. For good responsiveness, remember to call
 * one of these two functions periodically. To unregister a callback, pass a null pointer as argument.
 *
 * @param callback : the callback function to call, or a null pointer. The callback function should take two
 *         arguments: the function object of which the value has changed, and an YMeasure object describing
 *         the new advertised value.
 * @noreturn
 */
int YPressure::registerTimedReportCallback(YPressureTimedReportCallback callback)
{
    if (callback != NULL) {
        YFunction::_UpdateTimedReportCallbackList(this, true);
    } else {
        YFunction::_UpdateTimedReportCallbackList(this, false);
    }
    _timedReportCallbackPressure = callback;
    return 0;
}

int YPressure::_invokeTimedReportCallback(YMeasure value)
{
    if (_timedReportCallbackPressure != NULL) {
        _timedReportCallbackPressure(this, value);
    } else {
        YSensor::_invokeTimedReportCallback(value);
    }
    return 0;
}

YPressure *YPressure::nextPressure(void)
{
    string  hwid;

    if(YISERR(_nextFunction(hwid)) || hwid=="") {
        return NULL;
    }
    return YPressure::FindPressure(hwid);
}

YPressure* YPressure::FirstPressure(void)
{
    vector<YFUN_DESCR>   v_fundescr;
    YDEV_DESCR             ydevice;
    string              serial, funcId, funcName, funcVal, errmsg;

    if(YISERR(YapiWrapper::getFunctionsByClass("Pressure", 0, v_fundescr, sizeof(YFUN_DESCR), errmsg)) ||
       v_fundescr.size() == 0 ||
       YISERR(YapiWrapper::getFunctionInfo(v_fundescr[0], ydevice, serial, funcId, funcName, funcVal, errmsg))) {
        return NULL;
    }
    return YPressure::FindPressure(serial+"."+funcId);
}

//--- (end of YPressure implementation)

//--- (Pressure functions)
//--- (end of Pressure functions)
