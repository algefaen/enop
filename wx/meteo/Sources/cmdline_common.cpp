/*********************************************************************
*
* $Id: cmdline_common.cpp 20164 2015-04-27 10:36:46Z seb $
*
* implementation of cmdline  API generic class & functions
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
*    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
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
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cfloat>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

#include "cmdline_common.h"

string timeformat = "";
string formatstring = "";


ArgumentDesc::ArgumentDesc(argTypes type, string name, string description, string acceptedValues, bool optional)
{
    this->name = name;
    this->description = description;
    this->optional = optional;
    this->type = type;
    this->acceptedValues = new vector<string*>();
    string* res = new string();
    for (unsigned int i = 0; i < acceptedValues.length(); i++) {
        unsigned char c = acceptedValues[i];
        if (c == ',') {
            if (res->compare("") != 0)
                this->acceptedValues->push_back(res);
            res = new string();
        } else {
            (*res) += c;
        }
    }
    if (res->compare("") != 0)
        this->acceptedValues->push_back(res);
}

ArgumentDesc::~ArgumentDesc()
{
}

string ArgumentDesc::to_str(void)
{
    char buffer[1024];
    char *p = buffer;
    size_t i;
    switch (this->type) {
#ifdef __64BITS__
    case S64_ARG:
    case LONG_ARG:
    case INT_ARG:
        snprintf(buffer, 256, "%ld", this->intValue);
        break;
    case UNSIGNED_ARG:
        snprintf(buffer, 256, "%lu", this->unsignedValue);
        break;
#else
    case S64_ARG:
    case LONG_ARG:
    case INT_ARG:
        snprintf(buffer, 256, "%lld", this->intValue);
        break;
    case UNSIGNED_ARG:
        snprintf(buffer, 256, "%llu", this->unsignedValue);
        break;
#endif
    case STRING_ARG:
        snprintf(buffer, 256, "%s", this->stringValue.c_str());
        break;
    case BOOL_ARG:
        snprintf(buffer, 256, this->boolValue ? "true" : "false");
        break;
    case INTARR_ARG:
        buffer[0] = 0;
        for(i = 0; i < this->intArrValue.size(); i++) {
            if(i > 0) *p++ = ',';
            snprintf(p, buffer+1024-p, "%d", this->intArrValue[i]);
            while(*p) p++;
        }
        break;
    case FLOATARR_ARG:
        buffer[0] = 0;
        for(i = 0; i < this->floatArrValue.size(); i++) {
            if(i > 0) *p++ = ',';
            snprintf(p, buffer+1024-p, "%f", this->floatArrValue[i]);
            while(*p) p++;
        }
        break;
    case DOUBLE_ARG:
        snprintf(buffer, 256, "%f", this->doubleValue);
        break;
    case BIN_ARG:
        snprintf(buffer, 256, "(binary buffer)");
        break;
    }
    return string(buffer);
}

s64 ArgumentDesc::get_longValue()
{
    if (this->type != LONG_ARG) throw std::string("Argument type is not LONG");
    return this->intValue;
}

s64 ArgumentDesc::get_intValue()
{
    if (this->type != INT_ARG) throw std::string("Argument type is not INTEGER");
    return this->intValue;
}

u64 ArgumentDesc::get_unsignedValue()
{
    if (this->type != UNSIGNED_ARG) throw std::string("Argument type is not UNSIGNED");
    return this->unsignedValue;
}

string ArgumentDesc::get_stringValue()
{
    if (this->type != STRING_ARG) throw std::string("Argument type is not STRING");
    return this->stringValue;
}

bool ArgumentDesc::get_boolValue()
{
    if (this->type != BOOL_ARG) throw std::string("Argument type is not BOOL");
    return this->boolValue;
}

s64 ArgumentDesc::get_s64Value()
{
    if (this->type != S64_ARG) throw std::string("Argument type is not S64");
    return this->intValue;
}

double ArgumentDesc::get_doubleValue()
{
    if (this->type != DOUBLE_ARG) throw std::string("Argument type is not DOUBLE");
    return this->doubleValue;
}

vector<int> ArgumentDesc::get_intArrValue()
{
    if (this->type != INTARR_ARG) throw std::string("Argument type is not INTARR");
    return this->intArrValue;
}

vector<double> ArgumentDesc::get_floatArrValue()
{
    if (this->type != FLOATARR_ARG) throw std::string("Argument type is not FLOATARR");
    return this->floatArrValue;
}

string ArgumentDesc::get_binValue()
{
    if (this->type != BIN_ARG) throw std::string("Argument type is not BINARY");
    return this->binValue;
}

void ArgumentDesc::set_longValue(s64 value)
{
    if (this->type != LONG_ARG) throw std::string("Argument type is not LONG");
    this->intValue = value;
}

void ArgumentDesc::set_intValue(s64 value)
{
    if (this->type != INT_ARG) throw std::string("Argument type is not INT");
    this->intValue = value;
}

void ArgumentDesc::set_unsignedValue(u64 value)
{
    if (this->type != UNSIGNED_ARG) throw std::string("Argument type is not UNSIGNED");
    this->unsignedValue = value;
}

void ArgumentDesc::set_stringValue(string value, bool escape_backslash)
{

    if (this->type != STRING_ARG) throw std::string("Argument type is not STRING");
    if (escape_backslash) {
        char *buffer = (char*) malloc(value.length() + 1);
        const char * ptr = value.c_str();
        //char first_char = *ptr++;
        char *dst = buffer;
        while (*ptr) {
            if (*ptr == '\\') {
                ptr++;
                switch (*ptr) {
                case '\'':
                    *dst++ = '\'';
                    break;
                case '"':
                    *dst++ = '"';
                    break;
                case '\\':
                    *dst++ = '\\';
                    break;
                case '/':
                    *dst++ = '/';
                    break;
                case 'n':
                    *dst++ = '\n';
                    break;
                case '\r':
                    *dst++ = '\r';
                    break;
                case 't':
                    *dst++ = '\t';
                    break;
                case 'b':
                    if (dst > buffer)
                        dst--;
                    break;
                case '0':
                    *dst++ = 0;
                    break;
                }
            //} else if (*ptr == first_char) {
            //    *dst = 0;
            //    break;
            } else {
                *dst++ = *ptr;
            }
            ptr++;
        }
        *dst = 0;
        this->stringValue = string(buffer);
        free(buffer);
    } else {
        this->stringValue = value;
    }
}

void ArgumentDesc::set_boolValue(bool value)
{
    if (this->type != BOOL_ARG) throw std::string("Argument type is not BOOL");
    this->boolValue = value;
}

void ArgumentDesc::set_s64Value(s64 value)
{
    if (this->type != S64_ARG) throw std::string("Argument type is not S64");
    this->intValue = value;
}

void ArgumentDesc::set_doubleValue(double value)
{
    if (this->type != DOUBLE_ARG) throw std::string("Argument type is not DOUBLE");
    this->doubleValue = value;
}

void ArgumentDesc::set_intArrValue(vector<int> value)
{
    if (this->type != INTARR_ARG) throw std::string("Argument type is not INTARR");
    this->intArrValue = value;
}

void ArgumentDesc::set_floatArrValue(vector<double> value)
{
    if (this->type != FLOATARR_ARG) throw std::string("Argument type is not FLOATARR");
    this->floatArrValue = value;
}

void ArgumentDesc::set_binValue(string value)
{
    if (this->type != BIN_ARG) throw std::string("Argument type is not BINARY");
    this->binValue = value;
}



string ArgumentDesc::getTypeAsString()
{
    switch (this->type) {
    case S64_ARG      :
    case INT_ARG      :
        return "integer";
    case UNSIGNED_ARG :
        return "positive integer";
    case STRING_ARG   :
        return "string";
    case DOUBLE_ARG   :
        return "double";
    case BIN_ARG      :
        return "binary buffer";
    case LONG_ARG     :
        return "long";
    case BOOL_ARG     :
        return "boolean";
    case INTARR_ARG:
        return "array of integers";
    case FLOATARR_ARG :
        return "array of doubles";
    }
    return "parameter";
}


bool SwitchDesc::compare(string name)
{
    return (this->switchString.compare(name)==0);
}

string  SwitchDesc::getSwitchName()
{
    return this->switchString;
}

string  SwitchDesc::getDefaultValue()
{
    return this->defaultStrValue;
}

void SwitchDesc::set_longValue(s64 value)
{
    ArgumentDesc::set_longValue(value);
    set = true;
}

void SwitchDesc::set_intValue(s64 value)
{
    ArgumentDesc::set_intValue(value);
    set = true;
}

void  SwitchDesc::set_unsignedValue(u64 value)
{
    ArgumentDesc::set_unsignedValue(value);
    set = true;
}

void  SwitchDesc::set_stringValue(string value, bool escape_backslash)
{
    ArgumentDesc::set_stringValue(value, escape_backslash);
    set = true;
}

void  SwitchDesc::set_doubleValue(double value)
{
    ArgumentDesc::set_doubleValue(value);
    set = true;
}

s64  SwitchDesc::get_longValue()
{
    if (set) return ArgumentDesc::get_longValue();
    return atol(this->defaultStrValue.c_str());
}

s64  SwitchDesc::get_intValue()
{
    if (set) return ArgumentDesc::get_intValue();
    return atoi(this->defaultStrValue.c_str());
}

u64  SwitchDesc::get_unsignedValue()
{
    if (set) return ArgumentDesc::get_unsignedValue();
    return atoi(this->defaultStrValue.c_str());
}

string  SwitchDesc::get_stringValue(void)
{
    if (set) return ArgumentDesc::get_stringValue();
    return this->defaultStrValue;
}

double  SwitchDesc::get_doubleValue(void)
{
    if (set) return ArgumentDesc::get_doubleValue();
    return atof(this->defaultStrValue.c_str());
}


void YapiCommand::fatalError(string errmsg)
{
    printf("ERR: %s\n", errmsg.c_str());
    exit(-1);
}



string YapiCommand::execname(string argv0)
{
    string res = "";
    for (unsigned int i = 0; i < argv0.length(); i++) {
        unsigned char c = argv0[i];
        if ((c == '/') || (c == '\\')) res = "";
        else res += c;
    }
    return res;
}

string YapiCommand::helpformat(int marginFirstLine, int margin, int width, string data)
{
    string result = "";
    string line = "";

    for (int i=0; i<marginFirstLine; i++) line=line+" ";
    for (size_t k=0; k<data.length(); k++) {
        if (data[k]!='\n') {
            line = line+data[k];
            if (line.length()>(size_t)width) {
                int n = (int)line.length()-1;
                while ((n>1) && (line[n]!=' ')) n--;
                int diff = ((int)line.length()-n);
                k-=diff-1;
                line = line.substr(0,n);
                result = result+line+"\n";
                line="";
                for (int i=0; i<margin; i++) line=line+" ";
            }
        } else {
            result = result+line+"\n";
            line="";
            for (int i=0; i<margin; i++) line=line+" ";
        }
    }

    if (line!="") result = result+line+"\n";
    return result;

}


void YapiCommand::showHelp(string execname)
{
    string extra = this->getMoreInfo();
    string fmt;

    printf("\nCommand %s:\n", this->getName().c_str());
    printf("%s\n",  helpformat(2,2,79,this->getDescription()).c_str());
    if (extra != "") {
        printf("%s\n", helpformat(2,2,79,extra).c_str());
    }
    printf("Usage:\n  ");
    if (this->requireTarget()) fmt = "%s <target> %s";
    else fmt = "%s %s";
    printf(fmt.c_str(), execname.c_str(), this->getName().c_str());
    vector<ArgumentDesc*> *params = this->getArgumentDesc();
    for (unsigned int i = 0; i < params->size(); i++) {
        if ((*params)[i]->optional) printf(" [");
        else printf(" <");
        printf("%s", (*params)[i]->name.c_str());
        if ((*params)[i]->optional)printf("]");
        else printf(">");
    }
    printf("\n\n");
    if (params->size() > 0) {
        bool intArgsUsed = false;
        bool arrayUsed = false;

        printf("Arguments:\n");
        for (unsigned int i = 0; i < params->size(); i++) {
            string  line= (*params)[i]->name+" : "+ (*params)[i]->description;
            printf("%s", helpformat(2,6,79,line).c_str());
            if ((*params)[i]->type == INT_ARG || (*params)[i]->type == UNSIGNED_ARG || (*params)[i]->type ==  LONG_ARG || (*params)[i]->type == INTARR_ARG) intArgsUsed = true;
            if ((*params)[i]->type == INTARR_ARG || (*params)[i]->type == FLOATARR_ARG) arrayUsed = true;
        }
        printf("\n");
        if (intArgsUsed)
            printf("%s",helpformat(2,2,79,"Both decimal and hexadecimal syntax are accepted for integer parameters, hexadecimal syntax is 0xffffff or #ffffff or $ffffff").c_str());
        if (arrayUsed)
            printf("%s",helpformat(2,2,79,"Array are defined as comma seperated list, without any space").c_str());
        printf("\n");
    }
    exit(0);
}

SwitchDesc* YapiCommand::findSwitch(string switchname, vector<SwitchDesc*>* list)
{
    for (unsigned int i = 0; i < list->size(); i++) {
        if ((*list)[i]->compare(switchname)) {
            return (*list)[i];
        }
    }
    return NULL;
}


string YapiCommand::getClass()
{
    return "module";
}

// super atoi function wich understand both decimal
// and hexadecimal integer (with 0xFFFFFF , #FFFFFF, $FFFFFF)
// syntax

s64 YapiCommand::atoi(string data)
{
    if (data == "") return 0;
    int base = 10;
    int index = 0;
    int sign = 1;
    if (data[0] == '-') {
        index = 1;
        sign = -1;
    };
    if ((data[index] == '$') || (data[index] == '#')) {
        index++;
        base = 16;
    } else if (data.substr(index, 2) == "0x") {
        index += 2;
        base = 16;
    };
    s64 res = 0;
    for (unsigned int i = index; i < data.length(); i++) {
        unsigned char c = data[i];
        if ((c >= '0') && (c <= '9')) res = res * base + (c - '0');
        else if (base == 16) {
            if ((c >= 'a') && (c <= 'f')) res = res * base + (c - 'a') + 10;
            else if ((c >= 'A') && (c <= 'F')) res = res * base + (c - 'A') + 10;
        }
    }
    return res*sign;
}


bool YapiCommand::parseBool(string data)
{
    std::transform(data.begin(), data.end(),
        data.begin(), ::tolower);
    if (data == "yes" || data == "true") {
        return true;
    } else if (data == "no" || data == "false") {
        return false;
    }
    return YapiCommand::atoi(data) != 0;
}


vector<int>  YapiCommand::parseIntArr(string data)
{
    vector<int> result = vector<int>();

    const char *start = data.c_str();
    const char *p = start;
    string num;

    while(*p) {
        start = p;
        while(*p && *p != ' ' && *p != ',') p++;
        num = string(start,p-start);
        result.push_back((s32)YapiCommand::atoi(num.c_str()));
        start = p;
        while(*p == ' ' || *p == ',') p++;
    }

    return result;
}

vector<double>  YapiCommand::parseFloatArr(string data)
{
    vector<double> result = vector<double>();

    const char *start = data.c_str();
    const char *p = start;
    string num;

    while(*p) {
        start = p;
        while(*p && *p != ' ' && *p != ',') p++;
        num = string(start,p-start);
        result.push_back(atof(num.c_str()));
        start = p;
        while(*p == ' ' || *p == ',') p++;
    }

    return result;
}

//  makes sure a string is an integer
//  (both decimal and hexadeciamal are accepted)

bool YapiCommand::isInteger(string data)
{
    if (data == "") return 0;
    int base = 10;
    int index = 0;

    if (data[0] == '-') {
        index = 1;
    };
    if ((data[index] == '$') || (data[index] == '#')) {
        index++;
        base = 16;
    } else if (data.substr(index, 2) == "0x") {
        index += 2;
        base = 16;
    };
    for (unsigned i = index; i < data.length(); i++) {
        unsigned char c = data[i];
        if (!(((c >= '0') && (c <= '9'))
                || ((base == 16) &&
                    (((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F')))))) return false;

    }
    return true;
}

//  makes sure a string is an unsigned integer
//  (both decimal and hexadeciamal are accepted)

bool YapiCommand::isUnsigned(string data)
{
    if (data == "") return 0;
    if (data[0] == '-') return 0;
    return isInteger(data);
}

//  makes sure a string is a floating point value

bool YapiCommand::isDouble(string data)
{
    unsigned char c;
    int index = 0;
    if (data == "") return false;
    if (data[0] == '-') index = 1;

    for (unsigned int i = index; i < data.length(); i++) {
        c = data[i];
        if (!(((c >= '0') && (c <= '9')) || (c == '.'))) return false;
    }
    return true;
}


//  makes sure a string is a boolean

bool YapiCommand::isBool(string data)
{
    std::transform(data.begin(), data.end(),
        data.begin(), ::tolower);
    if (data == "yes" || data == "true" || data == "no" || data == "false") {
        return true;
    }
    return YapiCommand::isUnsigned(data);
}


//  makes sure a string is an integer array value

bool YapiCommand::isIntArr(string data)
{
    unsigned char c;
    if (data == "") return true;
    int base = 10;

    for (unsigned int i = 0; i < data.length(); i++) {
        c = data[i];
        if ((c == '$') || (c == '#') || (c == 'x')) {
            base = 16;
            continue;
        }
        if (c == ',') continue;
        if (!(((c >= '0') && (c <= '9'))
                || ((base == 16) &&
                    (((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F')))))) return false;
    }
    return true;
}

//  makes sure a string is a floating point array value

bool YapiCommand::isFloatArr(string data)
{
    unsigned char c;
    if (data == "") return true;

    for (unsigned int i = 0; i < data.length(); i++) {
        c = data[i];
        if (!(((c >= '0') && (c <= '9')) || (c == '.') ||  (c == '-') || (c == ','))) return false;
    }
    return true;
}

// simplifiy a string: convert all char to upcase and remove underscores

string YapiCommand::simplifyString(string s)
{
    string res = "";
    for (unsigned int i = 0; i < s.length(); i++) {
        unsigned char c = s[i];
        if ((c >= 'A') && (c <= 'Z')) res += c;
        else if ((c >= 'a') && (c <= 'z')) res += (c - 32);
        else if (c == '/') res += c;
        else if (c == '-') res += c;
    }
    return res;
}

vector<ArgumentDesc*>* YapiCommand::getArgumentDesc()
{
    vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
    return res;
}

vector<SwitchDesc*>* YapiCommand::getSwitchDesc()
{
    vector<SwitchDesc*>* res = new vector<SwitchDesc*>();
    return res;
}

bool YapiCommand::requireTarget(void)
{
    return true;
}

string YapiCommand::getMoreInfo(void)
{
    return "";
}

bool YapiCommand::MatchCmdLine(int argc, const char * argv[], int currentIndex, int* foundindex)
{
    if (this->requireTarget()) currentIndex++;
    while (currentIndex < argc) {
        string me = simplifyString(this->getName());
        string him = simplifyString(argv[currentIndex]);
        if (me.compare(him) == 0) {
            *foundindex = currentIndex;
            return true;
        }
        currentIndex++;
    }

    return false;
}

bool YapiCommand::MissingTarget(int argc, const char * argv[], int currentIndex)
{
    if (!this->requireTarget()) return false;
    if (currentIndex >= argc) return false;
    string me = simplifyString(this->getName());
    string him = simplifyString(argv[currentIndex]);
    if (me.compare(him) == 0) return true;
    return false;
}

vector<SwitchDesc*>* YapiCommand::checkSwitches(int argc, const char * argv[], int startIndex,int endIndex)
{
    vector<SwitchDesc*> *params = this->getSwitchDesc();

    if (startIndex > endIndex) return params;

    if ((params->size() == 0) && (startIndex <= endIndex))
        YapiCommand::fatalError("Command \"" + this->getName() + "\" takes no option after target.");

    for (int i =startIndex; i<endIndex; i++) {
        string switchname = argv[i];
        bool found= false;
        for (unsigned int j=0; (j<params->size()) && (!found) ; j++) {
            string me  = simplifyString((*params)[j]->getSwitchName());
            if (me.compare(simplifyString(switchname))==0) {
                found  = true;
                if (i>=endIndex)
                    YapiCommand::fatalError("Missing  \""+(*params)[j]->getTypeAsString() + "\" parameter after "+switchname);
                i++;
                string value = argv[i];
                bool ok = this->checkArgumentValue((*params)[j], value, 0);
                if (!ok) YapiCommand::fatalError(value + " is not a valid value for "+switchname);
            }

        }
        if (!found)
            YapiCommand::fatalError("Command \"" + this->getName() + "\" does not support \""+switchname+"\" switch");
    }

    return params;
}

bool YapiCommand::checkArgumentValue(ArgumentDesc* param, string currentValue, bool escape_backslash)
{
    vector<string*>* allowedValues = param->acceptedValues;
    for (unsigned int j = 0; j < allowedValues->size(); j++) {
        if ((*allowedValues)[j]->compare("_LOGICAL") == 0) {
            if (param->type != STRING_ARG) throw std::string("_LOGICAL can be stored in STRING_ARG argument only");
            if (YAPI::CheckLogicalName(currentValue)) {
                param->set_stringValue(currentValue, 0);
                return  true;
            } else YapiCommand::fatalError("\"" + currentValue + "\" is not a valid logical name");
        } else if ((*allowedValues)[j]->compare("_INT") == 0) {
            if (param->type != INT_ARG) throw std::string("_INT can be stored in INT_ARG argument only");
            if (YapiCommand::isInteger(currentValue)) {
                param->set_intValue(YapiCommand::atoi(currentValue.c_str()));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid integer value");
        } else if ((*allowedValues)[j]->compare("_LONG") == 0) {
            if (param->type != LONG_ARG) throw std::string("_LONG can be stored in LONG_ARG argument only");
            if (YapiCommand::isInteger(currentValue)) {
                param->set_longValue(YapiCommand::atoi(currentValue.c_str()));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid integer value");
        } else if ((*allowedValues)[j]->compare("_S64") == 0) {
            if (param->type != S64_ARG) throw std::string("_S64 can be stored in S64_ARG argument only");
            if (YapiCommand::isInteger(currentValue)) {
                param->set_s64Value(YapiCommand::atoi(currentValue.c_str()));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid integer value");
        } else if ((*allowedValues)[j]->compare("_UNSIGNED") == 0) {
            if (param->type != UNSIGNED_ARG) throw std::string("_UNSIGNED can be stored in UNSIGNED_ARG argument only");
            if (YapiCommand::isUnsigned(currentValue)) {
                param->set_unsignedValue(YapiCommand::atoi(currentValue.c_str()));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid unsigned value");
        } else if ((*allowedValues)[j]->compare("_INTARR") == 0) {
            if (param->type != INTARR_ARG) throw std::string("_INTARR can be stored in INTARR_ARG argument only");
            if (YapiCommand::isIntArr(currentValue)) {
                param->set_intArrValue(YapiCommand::parseIntArr(currentValue.c_str()));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid integer array value");
        } else if ((*allowedValues)[j]->compare("_FLOATARR") == 0) {
            if (param->type != FLOATARR_ARG) throw std::string("_FLOATARR can be stored in FLOATARR_ARG argument only");
            if (YapiCommand::isFloatArr(currentValue)) {
                param->set_floatArrValue(YapiCommand::parseFloatArr(currentValue.c_str()));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid float array value");
        } else if ((*allowedValues)[j]->compare("_STRING") == 0) {
            if (param->type != STRING_ARG) throw std::string("_STRING can be stored in STRING_ARG argument only");
            param->set_stringValue(currentValue,escape_backslash);
            return true;
        } else if ((*allowedValues)[j]->compare("_BOOL") == 0) {
            if (param->type != BOOL_ARG) throw std::string("_BOOL can be stored in BOOL_ARG argument only");
            if (YapiCommand::isBool(currentValue)) {
                param->set_boolValue(parseBool(currentValue));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid boolean value");

        } else if ((*allowedValues)[j]->compare("_BIN") == 0) {
            if (param->type != BIN_ARG) throw std::string("_BIN can be stored in BIN_ARG argument only");
            if(currentValue.compare(0,5,"file:") == 0) {
                currentValue = currentValue.substr(5,string::npos);
                std::ifstream is(currentValue.c_str(),std::ifstream::binary);
                if(!is) {
                    YapiCommand::fatalError("cannot open file " + currentValue);
                } else {
                    is.seekg (0, is.end);
                    int length = (int)is.tellg();
                    is.seekg (0, is.beg);
                    char * buffer = new char [length];
                    is.read(buffer,length);
                    is.close();
                    currentValue = string(buffer,length);
                    delete[] buffer;
                }
            } else if(currentValue.compare(0,4,"hex:") == 0) {
                currentValue = currentValue.substr(4,string::npos);
                int length = (int)(currentValue.size()/2);
                char * buffer = new char [length];
                for(int pos = 0; pos < length; pos++) {
                    buffer[pos] = (char)atoi("0x"+currentValue.substr(2*pos,2));
                }
                currentValue = string(buffer,length);
                delete[] buffer;
            } else {
                YapiCommand::fatalError(currentValue + " is not a valid binary buffer value (expected 'file:' or 'hex:')");
            }
            param->set_binValue(currentValue);
            return true;
        } else if ((*allowedValues)[j]->compare("_DOUBLE") == 0) {
            if (param->type != DOUBLE_ARG) throw std::string("_DOUBLE can be stored in DOUBLE_ARG argument only");
            if (YapiCommand::isDouble(currentValue)) {
                param->set_doubleValue(atof(currentValue.c_str()));
                return true;
            } else YapiCommand::fatalError(currentValue + " is not a valid floating point value");
        } else {
            string v = *((*allowedValues)[j]);
            int p = (int)v.find("=", 0);
            if (p > 0) {
                string name = v.substr(0, p);
                string value = v.substr(p + 1, v.length() - p - 1);
                if (YapiCommand::simplifyString(name).compare(YapiCommand::simplifyString(currentValue)) == 0 || value == currentValue) {
                    switch (param->type) {
                    case INT_ARG:
                        param->set_intValue(YapiCommand::atoi(value.c_str()));
                        return true;
                        break;
                    case UNSIGNED_ARG:
                        param->set_unsignedValue(YapiCommand::atoi(value.c_str()));
                        return true;
                        break;
                    case STRING_ARG:
                        param->set_stringValue(value, escape_backslash);
                        return true;
                        break;
                    case DOUBLE_ARG:
                        param->set_doubleValue(atof(value.c_str()));
                        return true;
                        break;
                    case S64_ARG:
                        param->set_s64Value(YapiCommand::atoi(value.c_str()));
                        return true;
                        break;
                    case BOOL_ARG:
                        param->set_boolValue(parseBool(value));
                        return true;
                        break;
                    case INTARR_ARG:
                        param->set_intArrValue(YapiCommand::parseIntArr(value.c_str()));
                        return true;
                        break;
                    case FLOATARR_ARG:
                        param->set_floatArrValue(YapiCommand::parseFloatArr(value.c_str()));
                        return true;
                        break;
                    case BIN_ARG :
                        param->set_binValue(value);
                        return true;
                        break;
                    case LONG_ARG :
                        param->set_intValue(YapiCommand::atoi(value.c_str()));
                        return true;
                        break;
                    }
                }
            }
        }

    }
    return false;
}



vector<ArgumentDesc*>* YapiCommand::checkArguments(int argc, const char * argv[], int currentIndex, bool escape_backslash)
{
    int requiredArgs = 0;
    vector<ArgumentDesc*> *params = this->getArgumentDesc();
    if ((params->size() == 0) && (argc > currentIndex))
        YapiCommand::fatalError("Command \"" + this->getName() + "\" takes no argument.");

    if (argc - currentIndex > (int) params->size())
        YapiCommand::fatalError("Too many arguments for command \"" + this->getName() + "\"");

    for (unsigned i = 0; i < params->size(); i++) {
        if (!(*params)[i]->optional){
            requiredArgs++;
        }
    }

    if (argc - currentIndex < requiredArgs)
        YapiCommand::fatalError("not enough arguments for command \"" + this->getName() + "\"");

    for (int i = 0; i < (int) argc - currentIndex; i++) {
        string currentValue = argv[currentIndex + i];

        bool ok = this->checkArgumentValue((*params)[i], currentValue, escape_backslash);
        if (!ok) YapiCommand::fatalError(currentValue + " is not a valid value");
    }

    return params;
}

s64 YapiCommand::getSwitchIntValue(vector<SwitchDesc*>* params,string name)
{
    for (unsigned i = 0; i < params->size(); i++) {
        string him = (*params)[i]->getSwitchName();
        if (name.compare(him) == 0) {
            return (*params)[i]->get_intValue();
        }
    }
    YapiCommand::fatalError("missing \"" + name + "\"  switch");
    return 0;
}

YFunctionInfoCache::YFunctionInfoCache(YFunction *fun)
{
    _hardwareId = fun->get_hardwareId();
    _functionId = fun->get_functionId();
    _logicalName = fun->get_logicalName();
    _friendlyName = fun->get_friendlyName();
    _serialNumber = fun->get_module()->serialNumber();
    _moduleLogicalName = fun->get_module()->get_logicalName();
}

YFunctionInfoCache::YFunctionInfoCache()
{
    _hardwareId = "unavailable";
    _functionId = "unavailable";
    _logicalName = "unavailable";
    _friendlyName = "unavailable";
    _serialNumber = "unavailable";
    _moduleLogicalName = "unavailable";
}


YFunctionInfoCache::YFunctionInfoCache(string serial)
{
    _hardwareId = serial;
    _functionId = "unavailable";
    _logicalName = "unavailable";
    _friendlyName = "unavailable";
    _serialNumber = serial;
    _moduleLogicalName = "unavailable";
}


string YFunctionInfoCache::get_identifierOrName()
{
    if (isModule()) {
        string logical = _logicalName;
        if (logical != "") return _logicalName;
        return _serialNumber;
    }

    string hwid = _hardwareId;
    unsigned int p = (unsigned)hwid.find(".");
    string res = "";

    string moduleLogical = _moduleLogicalName;
    string fctLogical = _logicalName;
    string moduleSerial = hwid.substr(0, p);
    string fctHwdName = hwid.substr(p + 1, hwid.length() - p);

    return (moduleLogical != "" ? moduleLogical : moduleSerial) + "." + (fctLogical != "" ? fctLogical : fctHwdName);
}

string YFunctionInfoCache::get_hardwareId()
{
    return _hardwareId;
}
string YFunctionInfoCache::get_functionId()
{
    return _functionId;
}
string YFunctionInfoCache::get_logicalName()
{
    return _logicalName;
}
string YFunctionInfoCache::get_friendlyName()
{
    return _friendlyName;
}
string YFunctionInfoCache::get_serialNumber()
{
    return _serialNumber;
}
string YFunctionInfoCache::get_moduleLogicalName()
{
    return _moduleLogicalName;
}

static string timestr(double timestamp)
{
    const char *fmt = timeformat.c_str();
    char   buffer[128], *p = buffer;
    struct tm * timeinfo;
    time_t rawtime = (time_t)timestamp;
    double frac = timestamp - (double)rawtime;
    string result;

    if(!*fmt) fmt = "%Y-%m-%d %H:%M:%S";
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), fmt, timeinfo);
    while(*p) p++;
    sprintf(p, ".%02u", (u32)(floor(frac*100)));
    result = string(buffer);

    return result;
}

void PrintResult(string format, string command, YFunctionInfoCache target, const string& result, bool is_get)
{
    const char *fmt = format.c_str();
    if(!*fmt) {
        if(is_get) fmt = "OK: [identifierOrName].[command] = [result].";
        else       fmt = "OK: [identifierOrName].[command] executed.";
    }

    const char *p = fmt;
    string line;
    while(*p) {
        while(*p && *p != '[') p++;
        if(p > fmt) line += string(fmt,p-fmt);
        if(!*p) break;
        fmt = ++p; // skip [
        while(*p && *p != '[' && *p != ']') p++;
        if(*p != ']') {
            line += '[';
            // closing brace not found, restart after '['
            p = fmt;
        } else {
            string word = string(fmt, p-fmt);
            p++;
            if(word == "identifierOrName") {
                line += target.get_identifierOrName();
            } else if(word == "hardwareId") {
                line += target.get_hardwareId();
            } else if(word == "functionId") {
                line += target.get_functionId();
            } else if(word == "logicalName") {
                line += target.get_logicalName();
            } else if(word == "friendlyName") {
                line += target.get_friendlyName();
            } else if(word == "serialNumber") {
                line += target.get_serialNumber();
            } else if(word == "moduleName") {
                line += target.get_moduleLogicalName();
            } else if(word == "command") {
                line += command;
            } else if(word == "timestamp") {
                line += timestr(YAPI::GetTickCount()/1000.0);
            } else if(word == "result") {
                line += result;
            } else {
                // unknown tag, restart after initial '['
                line += '[';
                p = fmt;
            }
        }
        fmt = p;
    }
    OutputLine(line, result);
}


/*
* specific display functions
*/

void PrintResult(string format, string command, YFunctionInfoCache target, int result, bool is_get)
{
    char buffer[32];
    sprintf(buffer, "%d", result);
    PrintResult(format, command, target, string(buffer), is_get);
}

void PrintResult(string format, string command, YFunctionInfoCache target, unsigned result, bool is_get)
{
    char buffer[32];
    sprintf(buffer, "%u", result);
    PrintResult(format, command, target, string(buffer), is_get);
}

void PrintResult(string format, string command, YFunctionInfoCache target, s64 result, bool is_get)
{
    char buffer[32];
    sprintf(buffer, "%" FMTs64, result);
    PrintResult(format, command, target, string(buffer), is_get);
}

void PrintResult(string format, string command, YFunctionInfoCache target, double result, bool is_get)
{
    char buffer[32];
    sprintf(buffer, "%.4f", result);
    PrintResult(format, command, target, string(buffer), true);
}

void PrintResult(string format, string command, YFunctionInfoCache target, YMeasure& result, bool is_get)
{
    char buffer[128], *p;
    double delta = result.get_endTimeUTC()-result.get_startTimeUTC();

    if(timeformat == "") {
        if (delta<=0.09)    sprintf(buffer, "%.2f", result.get_endTimeUTC());
        else if(delta<=0.9) sprintf(buffer, "%.1f", result.get_endTimeUTC());
        else sprintf(buffer, "%u", (u32)result.get_endTimeUTC());
    } else {
        string tim = timestr(result.get_endTimeUTC());
        sprintf(buffer, "%s", tim.c_str());
    }
    for(p = buffer; *p; p++) { }

    sprintf(p, ";%.4f;%.4f;%.4f", result.get_minValue(), result.get_averageValue(), result.get_maxValue());
    PrintResult(format, command, target, string(buffer), true);
}

void PrintResult(string format, string command, YFunctionInfoCache target, vector<YMeasure> result, bool is_get)
{
    for(size_t i = 0; i < result.size(); i++) {
        PrintResult(format, command, target, result.at(i), true);
    }
}

void PrintResult(string format, string command, YFunctionInfoCache target, vector<string> result, bool is_get)
{
    for(size_t i = 0; i < result.size(); i++) {
        PrintResult(format, command, target, result.at(i), true);
    }
}

void PrintResult(string format, string command, YFunctionInfoCache target, vector<int> result, bool is_get)
{
    char buffer[32];
    string value;

    if(result.size() == 0) {
        PrintResult(format, command, target, "", true);
        return;
    }
    sprintf(buffer, "%d", result.at(0));
    value = string(buffer);
    for(size_t i = 1; i < result.size(); i++) {
        sprintf(buffer, "%d", result.at(i));
        value += string(",")+string(buffer);
    }
    PrintResult(format, command, target, value, true);
}

void PrintResult(string format, string command, YFunctionInfoCache target, vector<double> result, bool is_get)
{
    char buffer[32];
    string value;

    if(result.size() == 0) {
        PrintResult(format, command, target, "", true);
        return;
    }
    sprintf(buffer, "%.4f", result.at(0));
    value = string(buffer);
    for(size_t i = 1; i < result.size(); i++) {
        sprintf(buffer, "%.4f", result.at(i));
        value += string(",")+string(buffer);
    }
    PrintResult(format, command, target, value, true);
}

void PrintResult(string format, string command, YFunctionInfoCache target, YDataSet& result, bool is_get)
{
    PrintResult(format, command, target, "unixTime;minValue;averageValue;maxValue", true);
    size_t written = 0;
    int progress = 0;
    while(progress < 100) {
        progress = result.loadMore();
        vector<YMeasure> measures = result.get_measures();
        vector<YMeasure> added;
        while(written < measures.size()) {
            added.push_back(measures.at(written++));
        }
        if(added.size() > 0) {
            PrintResult(format, command, target, added, true);
        }
    }
}


void PrintResult(string format, string command, YFunctionInfoCache target, YFirmwareUpdate& result, bool is_get)
{
    string errmsg;
    u64 start = YAPI::GetTickCount();
    int status = result.startUpdate();
    do {
        int newstatus = result.get_progress();
        if (newstatus != status) {
            string msg = YapiWrapper::ysprintf("%d%% %s", newstatus, result.get_progressMessage().c_str());
            PrintResult(format, command, target, msg, true);
        }
        YAPI::Sleep(500, errmsg);
        status = newstatus;
    } while (status < 100 && status >= 0);
    if (status < 0){
        PrintResult(format, command, target, YapiWrapper::ysprintf("%d%% Firmware Update failed: %s", status, result.get_progressMessage().c_str()), true);
    } else{
        u64 stop = YAPI::GetTickCount();
        double nbsec = (stop - start) / 1000.0;
        PrintResult(format, command, target, YapiWrapper::ysprintf("%d%% Firmware Updated Successfully in: %.3fs", status, nbsec), true);
    }
}


void PrintResult(string format, string command, YFunctionInfoCache target, vector<YDataSet> result, bool is_get)
{
    for(size_t i = 0; i < result.size(); i++) {
        PrintResult(format, command, target, result.at(i), true);
    }
}

void PrintResult(string format, string command, YFunctionInfoCache target, YFileRecord& result, bool is_get)
{
    char buffer[32];
    sprintf(buffer, ";%d;%08X", result.get_size(), result.get_crc());
    if(format=="") format = "OK;[friendlyName];[command];[result]";
    PrintResult(format, command, target, result.get_name()+string(buffer), true);
}

void PrintResult(string format, string command, YFunctionInfoCache target, vector<YFileRecord> result, bool is_get)
{
    PrintResult(format, command, target, "name;size;crc", true);
    for(size_t i = 0; i < result.size(); i++) {
        PrintResult(format, command, target, result.at(i), true);
    }
}

void PrintResult(string format, string command, YFunctionInfoCache target, YWlanRecord& result, bool is_get)
{
    char buffer[64];
    sprintf(buffer, ";%d;%s;%d%%", result.get_channel(), result.get_security().c_str(), result.get_linkQuality());
    if(format=="") format = "OK;[friendlyName];[command];[result]";
    PrintResult(format, command, target, result.get_ssid()+string(buffer), true);
}

void PrintResult(string format, string command, YFunctionInfoCache target, vector<YWlanRecord> result, bool is_get)
{
    for(size_t i = 0; i < result.size(); i++) {
        PrintResult(format, command, target, result.at(i), true);
    }
}

void PrintResult(string format, string command, YFunctionInfoCache target, YCellRecord& result, bool is_get)
{
    char buffer[128];

    sprintf(buffer, "MCC=%03d;MNC=%02d;LAC=%d;CellID=%d;%ddbm", result.get_mobileCountryCode(), result.get_mobileNetworkCode(),
            result.get_locationAreaCode(), result.get_cellId(), result.get_signalStrength());
    if(result.get_timingAdvance() >= 0) {
        sprintf(buffer+strlen(buffer), ";TA=%d;%s", result.get_timingAdvance(), result.get_cellOperator().c_str());
    }
    if(format=="") format = "OK;[friendlyName];[command];[result]";
    PrintResult(format, command, target, string(buffer), true);
}

void PrintResult(string format, string command, YFunctionInfoCache target, vector<YCellRecord> result, bool is_get)
{
    for(size_t i = 0; i < result.size(); i++) {
        PrintResult(format, command, target, result.at(i), true);
    }
}

int callbackReceived = 0;
void cmdlineTimedReportCallback(YSensor *func, YMeasure measure)
{
    callbackReceived = 1;
    PrintResult(formatstring, "timedReport", YFunctionInfoCache(func), measure, true);
}
void cmdlineValueCallback(YFunction *func, const string&  value)
{
    callbackReceived = 1;
    PrintResult(formatstring, "valueChange", YFunctionInfoCache(func), value, true);
}

void waitForCallbacks(s64 minTime, s64 maxTime)
{
    string errmsg;
    u64 startTime = YAPI::GetTickCount();
    s64 duration;

    do {
        YAPI::Sleep(3,errmsg);
        duration = YAPI::GetTickCount() - startTime;
        if(minTime == 0 || duration >= minTime) {
            if(callbackReceived) break;
        }
    } while(maxTime == 0 || duration < maxTime);
}

/*
 * Output function, once replaceable tokens are expanded
 *
 * This function can handle redirection to a file if the
 * string is of the form: '@filename:line'
 */
void OutputLine(string line, string result)
{
    const char *p = line.c_str();
    if(*p == '@') {
        // output to file
        const char *fmt = p+1;
        while(*fmt && *fmt != ':') fmt++;
        string outfile = string(p+1, fmt-(p+1));
        string status;
        if(!*fmt) {
            line = result;
        } else {
            fmt++;
            line = string(fmt,line.size() - (fmt-p));
        }
        // insert newline as separator if the file exists and is
        // non-empty, but do not append it immediately after each line, as
        // the output might be binary data (eg. for apifunction download)
        FILE *f = fopen(outfile.c_str(), "r+b");
        if(f) {
            fseek(f, 0L, SEEK_END);
            if(ftell(f) > 0L) fwrite(NEWLINE, 1, strlen(NEWLINE), f);
            status = string("OK: append output to ")+outfile;
        } else {
            f = fopen(outfile.c_str(), "wb");
            if(f) status = string("OK: write output to new file ")+outfile;
        }
        if(f) {
            fwrite(line.c_str(), 1, line.size(), f);
            fclose(f);
        } else {
            status = string("ERR: failed to write to ")+outfile;
        }
        // output diagnostic message to standard output
        line = status;
    }

    // write to standard output (implicit add newline at the end)
    fwrite(line.c_str(), 1, line.size(), stdout);
    fwrite(NEWLINE, 1, strlen(NEWLINE), stdout);
}

string enumString(int numval, const char *enumdef[])
{
    if (numval >= 0) {
        int i;
        for (i = 0; i < numval; i++) {
            if (enumdef[i] == NULL) break;
        }
        if (enumdef[i] != NULL) return enumdef[i];
    }
    return "INVALID";
}

string bitString(const char *names, u64 val)
{
    char buffBits[70];
    char c, *p = buffBits;
    u16  n = 0;

    *p++ = '[';
    while((c = *names) != 0) {
        *p++ = ((val & 1) ? c : '.');
        val >>= 1;
        n++;
        names++;
    }
    *p++ = ']';
    *p = 0;

    return string(buffBits);
}

static void registerhubs(string arg)
{
    vector<string*> hublist;

    // split comma separated addresses
    hublist.push_back(new string());
    for (unsigned int i = 0; i < arg.length(); i++) {
        if (arg[i] == ',') hublist.push_back(new string());
        else *hublist[hublist.size() - 1] += arg.at(i);
    }

    // register hub adresses
    string errmsg = "";
    for (unsigned int i = 0; i < hublist.size(); i++) {
        if (YAPI::RegisterHub(*hublist[i], errmsg) != YAPI::SUCCESS)
            YapiCommand::fatalError("Cannot register " + *hublist[i] + ": " + errmsg);
    }

}

static bool cmdSortFct(YapiCommand* a, YapiCommand* b)
{
    return a->getName() < b->getName();
}

static void displayGlobalHelp(string execname, vector<YapiCommand*> cmdList)
{
    SwitchList switchesMap;
    for (unsigned int i = 0; i < cmdList.size(); i++) {
        vector<SwitchDesc*>* s =   cmdList[i]->getSwitchDesc();
        for (unsigned int j = 0; j < s->size(); j++) {
            string key=  (*s)[j]->getSwitchName();
            if (switchesMap.find(key)==switchesMap.end()) {
                switchesMap.insert(std::pair<string, SwitchDesc*>(key, (*s)[j] ));
            }
        }
    }

    string switcheslist= "";
    string switchesDescription = "";
    for (SwitchList::iterator it=switchesMap.begin(); it!=switchesMap.end(); ++it) {
        switcheslist=switcheslist+"["+it->second->getSwitchName().c_str()+" "+it->second->name.c_str()+ "] ";
        string tmp ="  "+it->second->getSwitchName()+" "+it->second->name;
        while (tmp.length()<16) tmp=tmp+" ";
        string desc = it->second->description;
        if  (it->second->optional) desc = desc + " Optional, default value is "+it->second->getDefaultValue();
        unsigned int n=0;
        int len=0;
        string sep = "\n                  ";
        int lastspace =0;
        while (n<desc.length()) {
            char c = desc.at(n);
            if  (c==' ') lastspace=n;
            len++;
            if (len>60) {
                desc = desc.substr(0,lastspace)+sep+desc.substr(lastspace+1);
                n=lastspace+(int)sep.length();
                len = 0;
            }

            n++;


        }

        switchesDescription = tmp+": "+desc+"\n";
    }

    if (isModule())
        printf("Use %s to work with any Yoctopuce device.\n", execname.c_str());
    else
        printf("Use %s to work with any %s function on any Yoctopuce device.\n", execname.c_str(), YFunctionName().c_str());
    printf("Usage:\n\n");
    printf("%s [options] [target] %scommand [command arguments]\n\n", execname.c_str(),switcheslist.c_str());
    printf("\n");
    printf("options:\n");
    printf("  -r remoteAddr : Uses remote IP devices (or VirtalHub), instead of local USB.\n");
    printf("                  remoteAddr is a comma-separated list of IP name or addresses.\n");
    printf("  -f 'fmtString': Specify a custom format template for displaying output of\n");
    printf("                  executed commands. The default format template string is:\n");
    printf("                  'OK: [identifierOrName].[command] = [result].'\n");
    printf("                  For more details, please refer to the documentation.\n");
    printf("  -e            : Enable interpretation of backslash escapes.\n");
    printf("                  remoteAddr is a comma-separated list of IP name or addresses.\n");
    printf("  --csv (-c)    : Uses a CSV compliant output format\n");
    printf("  --save (-s)   : Automatically call \"saveToFlash\"  on the matching module\n");
    printf("                  after command execution. This will save *all* changes\n");
    printf("                  previously made on the device (applies to set_* cmd only).\n");
    printf("  --debug (-d)  : Enable Yocto-API debug mode\n");
    printf("  --version (-v): Show library version number\n");
    printf("%s",switchesDescription.c_str());

    printf("target:\n");
    if (isModule())
        printf("  A valid device serialNumber or logicalName.\n");
    else
        printf("  A valid \"serialNumber.logicalName\" pair for the %s function.\n", YFunctionName().c_str());
    printf("  \"any\" and \"all\" are also valid targets. Note that some commands do not\n");
    printf("  require a target\n");
    printf("\n");
    printf("Available commands (underscore and case-insensitive):\n");

    std::sort(cmdList.begin(), cmdList.end(), cmdSortFct);

    unsigned colHeight = (unsigned)((cmdList.size() + 2) / 3);
    for (unsigned int i = 0; i < colHeight; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            if (j == 0)printf(" ");
            unsigned index = j * colHeight + i;
            if (index < cmdList.size()) {
                string n = cmdList[index]->getName();
                printf(" %s", n.c_str());
                for (unsigned k = (unsigned)n.length(); k < 25; k++) printf(" ");
                if (j == 2)printf("\n");
            } else printf("\n");
        }
    }
    printf("\n\n");
    printf("Type \"%s {command} --help\" for help about a specific command.\n", execname.c_str());
    exit(0);

}

static void log(const string& msg)
{
    printf("DBG: %s",msg.c_str());
}

int main(int argc, const char * argv[])
{
    vector<YapiCommand*> cmdList;
    bool autosave = false;
    bool escape_backslash = false;

    int paramindex = 1;
    bool registered = false;

    // register specific commands
    RegisterCommands(&cmdList);

    // search global flags to be executed BEFORE any registerhub
    while ((paramindex < argc) && (argv[paramindex][0] == '-')) {
        if (strcmp(argv[paramindex], "-d") == 0) {
            YAPI::RegisterLogFunction(log);
        }
        if (strcmp(argv[paramindex], "--help") == 0 || strcmp(argv[paramindex], "-h") == 0) {
            // global help
            displayGlobalHelp(YapiCommand::execname(argv[0]), cmdList);
            exit(0);
        }
        if (strcmp(argv[paramindex], "--version") == 0 || strcmp(argv[paramindex], "-v") == 0) {
            // show version number and exit
            string ver = YAPI::GetAPIVersion();
#if defined(WINDOWS_API)
            const char *platform = "win";
#elif defined(LINUX_API)
            const char *platform = "linux";
#elif defined(OSX_API)
            const char *platform = "osx";
#endif
#if defined(__32BITS__)
            const char *bitcount = "32";
#elif defined(__64BITS__)
            const char *bitcount = "64";
#endif
#if defined(BUILD_ARMEL)
            const char *suffix = "-armel";
#elif defined(BUILD_ARMHF)
            const char *suffix = "-armhf";
#elif defined(__arm__) && defined(CPU_BIG_ENDIAN)
            const char *suffix = "-arm";
#elif defined(__arm__) && !defined(CPU_BIG_ENDIAN)
            const char *suffix = "-arm-littleendian";
#elif defined(CPU_BIG_ENDIAN)
            const char *suffix = "-bigendian";
#else
            const char *suffix = "";
#endif
            const char *p = strrchr(argv[0],'/');
            if(!p) p=strrchr(argv[0],'\\');
            if(p) { p++; } else { p=argv[0]; }
            printf("%s %s %s-%s%s\n", p, ver.c_str(), platform, bitcount, suffix);
            exit(0);
        }
        paramindex++;
    }

    paramindex = 1;

    // process other command options, including RegisterHub
    while ((paramindex < argc) && (argv[paramindex][0] == '-')) {
        if ((strcmp(argv[paramindex], "-r") == 0) && (paramindex < argc - 1)) {
            registerhubs(argv[paramindex + 1]);
            registered = true;
            paramindex++;
        } else if ((strcmp(argv[paramindex], "-f") == 0) && (paramindex < argc - 1)) {
            formatstring = string(argv[paramindex + 1]);
            paramindex++;
        } else if (strcmp(argv[paramindex], "-e") == 0) {
            escape_backslash = 1;
        } else if (strcmp(argv[paramindex], "--save") == 0 || strcmp(argv[paramindex], "-s") == 0) {
            autosave = true;
        } else if (strcmp(argv[paramindex], "--csv") == 0 || strcmp(argv[paramindex], "-c") == 0) {
            timeformat = "%Y-%m-%d %H:%M:%S";
            formatstring = "[identifierOrName];[result]";
        }
        paramindex++;
    }

    // trap Windows-style request for global help
    if (paramindex < argc) {
        string h = YapiCommand::simplifyString(argv[paramindex]);
        if (h.compare("/HELP") == 0) {
            displayGlobalHelp(YapiCommand::execname(argv[0]), cmdList);
            exit(0);
        }
    }

    // trap request for specific command help
    if (paramindex + 1 < argc) {
        string h = YapiCommand::simplifyString(argv[paramindex + 1]);
        if (h.compare("/HELP") == 0 || h.compare("--HELP") == 0 || h.compare("-H") == 0) {
            string cmd = YapiCommand::simplifyString(argv[paramindex]);
            for (unsigned int i = 0; i < cmdList.size(); i++)
                if (cmd.compare(YapiCommand::simplifyString(cmdList[i]->getName())) == 0)
                    cmdList[i]->showHelp(YapiCommand::execname(argv[0]));

            // command no found, lets show global help
            printf("No help available for %s (unknow command)\n\n",cmd.c_str());
            displayGlobalHelp(YapiCommand::execname(argv[0]), cmdList);
            exit(0);
        }
    }


    // not register flag found, lets use default USB
    if (!registered) registerhubs("usb");

    // looking for the right command to execute
    for (unsigned int i = 0; i < cmdList.size(); i++) {
        int foundindex=-1;
        if (cmdList[i]->MatchCmdLine(argc, argv, paramindex, &foundindex)) {
            string target = "";
            if (cmdList[i]->requireTarget()) target = argv[paramindex++];
            else if(paramindex < foundindex &&
                    (YapiCommand::simplifyString(argv[paramindex]) == "ANY" ||
                     YapiCommand::simplifyString(argv[paramindex]) == "ALL")) {
                paramindex++;
            }

            // trap help request in cmd arguments
            for (int j = foundindex + 1; j < argc; j++) {
                if (YapiCommand::simplifyString(argv[j]) == "/HELP" || YapiCommand::simplifyString(argv[j]) == "--help") {
                    cmdList[i]->showHelp(YapiCommand::execname(argv[0]));
                }
            }

            vector<SwitchDesc*>* switches = cmdList[i]->checkSwitches(argc, argv, paramindex,foundindex-1);
            vector<ArgumentDesc*>*   args = cmdList[i]->checkArguments(argc, argv, foundindex + 1, escape_backslash);
            vector<YModule*> modulelist;
            try {
                cmdList[i]->execute(target, &modulelist, formatstring, args,switches);
            } catch (exception& e) {
                YapiCommand::fatalError("internal error: " + (string) e.what());
            }
            // calls SaveToFlash if needed
            if (autosave) {
                if (cmdList[i]->getName().substr(0, 4) == "set_") {
                    if (cmdList[i]->getName().substr(0, 4) != "set_beacon") { // little ugly exception
                        for (unsigned j = 0; j < modulelist.size(); j++) {
                            if (modulelist[j]->isOnline()) {
                                modulelist[j]->saveToFlash();
                                PrintResult(formatstring, "saveToFlash", YFunctionInfoCache(modulelist[j]), "", false);
                            } else {
                                YapiCommand::fatalError(modulelist[j]->get_serialNumber()+".saveToFlash failed (module went offline)");
                            }
                        }
                    }
                }
            }
            YAPI::FreeAPI();
            exit(0);
        } else if (cmdList[i]->MissingTarget(argc, argv, paramindex)) {
            YapiCommand::fatalError(" command " + (string) argv[paramindex] + ": missing target, use  \"" + YapiCommand::execname(argv[0]) + " " + (string) argv[paramindex] + " /help\" for help.");
        }
    }

    string help = "\nUse \"" + YapiCommand::execname(argv[0]) + " /help\" for help.";
    if (paramindex >= argc) {
        YapiCommand::fatalError("missing command." + help);
    } else if (paramindex + 1 >= argc) {
        YapiCommand::fatalError("unknown command:" + (string)argv[paramindex] + help);
    } else{
        YapiCommand::fatalError("unknown command:" + (string)argv[paramindex + 1] + help);
    }
}

