/*********************************************************************
 *
 * $Id: cmdline_common.h 20164 2015-04-27 10:36:46Z seb $
 *
 * declaration of cmdline  API generic class & functions
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

#include <string>
#include <vector>

#include "yocto_api.h"
#include "yocto_files.h"
#include "yocto_wireless.h"
#include "yocto_cellular.h"
#include "yocto_display.h"

using namespace std;

// snprintf is called sprintf_s in VisualC++
#ifdef _MSC_VER
#define snprintf sprintf_s
#endif

/*
 * handling of commands arguements.
 */
typedef enum {
    INT_ARG, UNSIGNED_ARG, STRING_ARG, DOUBLE_ARG ,BIN_ARG, LONG_ARG, INTARR_ARG, FLOATARR_ARG, BOOL_ARG, S64_ARG
} argTypes;

class ArgumentDesc {
public:
    ArgumentDesc(argTypes type, string name, string descrption, string acceptedValues, bool optional);
    ~ArgumentDesc();
    string name;
    string description;
    argTypes type;
    vector<string*>* acceptedValues;
    bool optional;

	string getTypeAsString();

    s64 intValue;
    u64 unsignedValue;
    string stringValue;
    double doubleValue;
    vector<int> intArrValue;
    vector<double> floatArrValue;
    string binValue;
    bool  boolValue;

    virtual s64 get_longValue();
    virtual s64 get_intValue();
    virtual u64 get_unsignedValue();
    virtual string get_stringValue(void);
    virtual double get_doubleValue(void);
    virtual string get_binValue(void);
    virtual bool get_boolValue(void);
    virtual s64 get_s64Value(void);
    virtual vector<int> get_intArrValue(void);
    virtual vector<double> get_floatArrValue(void);
    string to_str(void);

    virtual void set_longValue(s64 value);
    virtual void set_intValue(s64 value);
    virtual void set_unsignedValue(u64 value);
    virtual void set_stringValue(string value, bool escape_backslash);
    virtual void set_doubleValue(double value);
    virtual void set_boolValue(bool value);
    virtual void set_s64Value(s64 value);
    virtual void set_intArrValue(vector<int> value);
    virtual void set_floatArrValue(vector<double> value);
    virtual void set_binValue(string value);
};




class SwitchDesc: public ArgumentDesc
{
	 string switchString;
	 string defaultStrValue;
	 bool  set;
public:
   SwitchDesc(string switchstr, argTypes type, string name, string descrption, string acceptedValues, bool optional,string defaultValue):
		ArgumentDesc( type,  name,  descrption,  acceptedValues,  optional),
		switchString(switchstr)
		{ set=false;
		  defaultStrValue=defaultValue;
		};
   bool compare(string name);

   void set_longValue(s64 value);
   void set_intValue(s64 value);
   void set_unsignedValue(u64 value);
   void set_stringValue(string value, bool escape_backslash);
   void set_doubleValue(double value);

   s64 get_longValue();
   s64 get_intValue();
   u64 get_unsignedValue();
   string get_stringValue(void);
   double get_doubleValue(void);

   string getSwitchName();
   string getDefaultValue();


};

class YapiCommand {
public:
    static void fatalError(string errmsg);
    static string execname(string argv0);

    virtual string getName(void) = 0;
    virtual string getDescription(void) = 0;
    virtual string getMoreInfo(void);
    virtual bool requireTarget(void);
    virtual vector<ArgumentDesc*>* getArgumentDesc(void);
	virtual vector<SwitchDesc*>*  getSwitchDesc(void);
    void showHelp(string execname);
	string helpformat(int marginFirstLine, int margin, int width, string data);
    static string getClass();
    static bool isInteger(string data);
    static bool isUnsigned(string data);
    static bool isDouble(string data);
    static bool isBool(string data);
    static bool isIntArr(string data);
    static bool isFloatArr(string data);

    s64 getSwitchIntValue(vector<SwitchDesc*>* params,string name);


	static SwitchDesc* findSwitch(string switchname, vector<SwitchDesc*>*);
    bool checkArgumentValue(ArgumentDesc* param, string currentValue, bool escape_backslash);
    static vector<int> parseIntArr(string data);
    static vector<double> parseFloatArr(string data);
    static s64 atoi(string data);
    static bool parseBool(string data);
    static string simplifyString(string s);
    bool MatchCmdLine(int argc, const char * argv[], int currentIndex,int* foundindex);
    bool MissingTarget(int argc, const char * argv[], int currentIndex);
    vector<ArgumentDesc*>* checkArguments(int argc, const char * argv[], int currentIndex, bool escape_backslash);
	vector<SwitchDesc*>* checkSwitches(int argc, const char * argv[], int startIndex,int endIndex);
    virtual void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* desc , vector<SwitchDesc*>* switches) = 0;

};


class YFunctionInfoCache {
protected:
    string _hardwareId;
    string _functionId;
    string _logicalName;
    string _friendlyName;
    string _serialNumber;
    string _moduleLogicalName;

public:
    YFunctionInfoCache(void);
    YFunctionInfoCache(string serial);
    YFunctionInfoCache(YFunction *fun);
    string get_identifierOrName(void);
    string get_hardwareId(void);
    string get_functionId(void);
    string get_logicalName(void);
    string get_friendlyName(void);
    string get_serialNumber(void);
    string get_moduleLogicalName(void);
};

void cmdlineTimedReportCallback(YSensor *func, YMeasure measure);
void cmdlineValueCallback(YFunction *func, const string& value);
void waitForCallbacks(s64 minTime, s64 maxTime);

void OutputLine(string line, string result);
string enumString(int numval, const char *enumdef[]);
string bitString(const char *names, u64 val);
void RegisterCommands(vector<YapiCommand*>* cmdList);
string YFunctionName(void);
bool isModule(void);
int main(int argc, const char * argv[]);

#ifdef __WIN32__
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif


void PrintResult(string format, string command, YFunctionInfoCache target, const string& result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, int result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, unsigned result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, s64 result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, double result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, YMeasure& result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<YMeasure> result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<string> result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<int> result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<double> result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, YDataSet& result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, YFirmwareUpdate& result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<YDataSet> result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, YFileRecord& result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<YFileRecord> result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, YWlanRecord& result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<YWlanRecord> result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, YCellRecord& result, bool is_get);
void PrintResult(string format, string command, YFunctionInfoCache target, vector<YCellRecord> result, bool is_get);

/*
 * template function for inventory
 */

template <class yFct> vector<yFct*> *enumerateTargets(string target, vector<YModule*> *modulelist) {
    vector<yFct*>* res = new vector<yFct*>();
    yFct* m;
    string simplified = YapiCommand::simplifyString(target);

    //  any or every ones
    if ((simplified.compare("ANY") == 0) || (simplified.compare("ALL") == 0)) {
        m = yFct::First();
        if (m == NULL)
            YapiCommand::fatalError("No " + YapiCommand::getClass() + " found");
        res->push_back(m);
        modulelist->push_back(m->get_module());
        if (simplified.compare("ANY") == 0) return res;
        do {
            m = m->next();
            if (m != NULL)
                if (m->isOnline()) {
                    res->push_back(m);
                    bool found = 0;
                    YModule* HostModule = m->get_module();
                    string HostModuleSerial = HostModule->get_serialNumber();
                    for (unsigned int i = 0; i < modulelist->size(); i++)
                        if ((*modulelist)[i]->get_serialNumber() == HostModuleSerial)
                            found = true;
                    if (!found) modulelist->push_back(HostModule);
                }



        }        while (m != NULL);
        return res;
    }

    // specific one
    m = yFct::Find(target);
    if (!m->isOnline())
        YapiCommand::fatalError("No online " + YapiCommand::getClass() + " named " + target);

    // fix :
    m = isModule() ? yFct::Find(m->get_module()->get_serialNumber()) : yFct::Find(m->get_hardwareId());
    if (!m->isOnline())
        YapiCommand::fatalError("No online " + YapiCommand::getClass() + " named " + target);

    res->push_back(m);
    modulelist->push_back(m->get_module());

    return res;
}

/*
 * template class for inventory command
 */
template <class yFct> class InventoryCmd : public YapiCommand {
public:

    string getDescription() {
        if (isModule()) return "List all available modules Module, give both serial number and logical name if available.";
        else return "Display all available " + (string) YFunctionName() + " functions, give both serial number and logical name if available.";
    }

    string getName() {
        return "inventory";
    }

    bool requireTarget() {
        return false;
    }

    void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches) {
        vector<yFct*>* list = enumerateTargets<yFct > ("ALL", modulelist);

        for (unsigned int i = 0; i < list->size(); i++) {
            string ms = (*list)[i]->get_module()->get_serialNumber();
            string ml = (*list)[i]->get_module()->get_logicalName();


            if (isModule()) {
                printf("%-20s ", ms.c_str());
                if (ml != "")printf("(%s)", ml.c_str());
                printf("\n");
            } else {
                string res = "";
                string l = (*list)[i]->get_logicalName();
                string hwid = (*list)[i]->get_hardwareId();
                unsigned int p = (unsigned)hwid.find(".");
                string h = hwid.substr(p + 1, hwid.length() - p);

                printf("%s.%s", ms.c_str(), h.c_str());
                if ((l != "") || (ml != "")) {
                    if (l == "") l = h;
                    if (ml == "") ml = ms;
                    printf("  (%s.%s)", ml.c_str(), l.c_str());
                }
                printf("\n");
            }

        }
    }

};

/*
 * template class for version command
 */
template <class yFct> class versionCmd : public YapiCommand {
public:

    string getDescription() {
        return "Shows Yocto-API version.";
    }

    string getName() {
        return "version";
    }

    bool requireTarget() {
        return false;
    }

    void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches) {
        printf("OK: version = %s\n", YAPI::GetAPIVersion().c_str());

    }

};

/*
 * template class for describe command
 */
template <class yFct> class DescribeCmd : public YapiCommand {
public:

    string getName() {
        return "describe";
    }

    string getDescription() {
        if (isModule()) return "Display info about  modules";
        else return "Display  info about  " + (string) YFunctionName() + " functions.";
    }

    vector<ArgumentDesc*>* getArgumentDesc()
    {
        vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
        res->push_back(new ArgumentDesc(BOOL_ARG, "verbose", "Include all attributes in description (default value = false)", "_BOOL", true));
        res->at(0)->set_boolValue(false);
        return res;
    }


    void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches) {
        char buffer[256];
        bool verbose = (*args)[0]->get_boolValue();
        vector<yFct*>* list = enumerateTargets<yFct > (target, modulelist);
        for (unsigned int i = 0; i < list->size(); i++) {
            string l = (*list)[i]->get_module()->get_logicalName().c_str();
            string hwid = (*list)[i]->get_hardwareId();
            unsigned int p = (unsigned)hwid.find(".");
            string fctHwdName = hwid.substr(p + 1, hwid.length() - p);

            printf("%-30s : %s\n", "Module serial number", (*list)[i]->get_module()->get_serialNumber().c_str());
            printf("%-30s : %s\n", "Module logical name", l != "" ? l.c_str() : "(not set)");
            printf("%-30s : %s\n", "Module product name", (*list)[i]->get_module()->get_productName().c_str());
            printf("%-30s : 0x%x\n", "Module product ID", (*list)[i]->get_module()->get_productId());
            printf("%-30s : %s\n", "Module firmware", (*list)[i]->get_module()->get_firmwareRelease().c_str());
            string uptime = "";
            s64 up = (*list)[i]->get_module()->get_upTime() / 1000;
            if (up > 86400) {
                snprintf(buffer, 256, "%dd ", (int) (up / 86400));
                uptime = string(buffer);
                up = up % 86400;
            }
            if ((up > 3600) || (uptime != "")) {
                snprintf(buffer, 256, "%dh ", (int) (up / 3600));
                uptime += string(buffer);
                up = up % 3600;
            }
            if ((up > 60) || (uptime != "")) {
                snprintf(buffer, 256, "%dm ", (int) (up / 60));
                uptime += string(buffer);
                up = up % 60;
            }
            snprintf(buffer, 256, "%ds", (int) up);
            uptime += string(buffer);
            printf("%-30s : %s\n", "Module uptime", uptime.c_str());
            if (!isModule()) {
                string l = (*list)[i]->get_logicalName().c_str();
                printf("%-30s : %s\n", "Function hardware name", fctHwdName.c_str());
                printf("%-30s : %s\n", "Function logical name", l != "" ? l.c_str() : "(not set)");

            }
            if(verbose) {
                string apitxt = (*list)[i]->_download("api/"+fctHwdName+".txt");
                string delim = "\r\n", line;
                size_t pos = apitxt.find(delim);
                size_t seppos;
                string attrname, attrval;
                while(pos != string::npos) {
                    apitxt.erase(0, pos + delim.length());
                    pos = apitxt.find(delim);
                    if(pos != string::npos) {
                        line = apitxt.substr(0, pos);
                    } else {
                        line = apitxt;
                    }
                    seppos = line.find(": ");
                    if(seppos == string::npos) continue;
                    attrname = line.substr(0,seppos);
                    attrval = line.substr(seppos+2);
                    if(attrval[0] == '"' && attrval[attrval.length()-1] == '"') {
                        attrval = attrval.substr(1,attrval.length()-2);
                    }
                    printf("%-30s : %s\n", attrname.c_str(), attrval.c_str());
                }
            }

            printf("\n");
        }
    }
};


/**
 * Retrieves any available timed report from the functions.
 *
 * @param minWait: the minimum time to wait for a timed report,
 *         or zero to wait at least up to the first timed report.
 * @param maxWait: the maximum time to wait for a timed report,
 *         or zero to wait no more than up to the first timed report.
 *
 */
/*
 * template class for get_valueChange command
 */
template <class yFct> class get_valueChange : public YapiCommand { /* arguments: minWait maxWait */

public:

    string getName()
    {
        return "get_valueChange";
    }

    string getDescription()
    {
        return "Retrieves any available timed report from the functions.";
    }

    vector<ArgumentDesc*>* getArgumentDesc()
    {
        vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
        res->push_back(new ArgumentDesc(INT_ARG, "minWait", "the minimum time to wait for a timed report, or zero to wait at least up to the first timed report.", "_INT", false));
        res->push_back(new ArgumentDesc(INT_ARG, "maxWait", "the maximum time to wait for a timed report, or zero to wait no more than up to the first timed report.", "_INT", false));
        return res;
    }

    void execute(string target,vector<YModule*> *modulelist,string resultformat, vector<ArgumentDesc*>* args , vector<SwitchDesc*>* switches)
    {
        vector<yFct*>* list = enumerateTargets<yFct>(target,modulelist);
        unsigned int i;
        for (i = 0; i < list->size(); i++)
        {
            (*list)[i]->registerValueCallback(cmdlineValueCallback);
        }
        waitForCallbacks((*args)[0]->get_intValue(), (*args)[1]->get_intValue());
    }
};


/*
 * template class for inventory command
 */
template <class yFct> class FirmwareUpdateCmd : public YapiCommand {

protected:

    int _doUpgrade(string resultformat, YFunctionInfoCache infos, YFirmwareUpdate *update)
    {
        string      errmsg;
        u64 start = YAPI::GetTickCount();
        int status = update->startUpdate();
        PrintResult(resultformat, this->getName(), infos, YapiWrapper::ysprintf("%d", status) + "% " + update->get_progressMessage(), true);
        while (status < 100 && status >= 0) {
            int newstatus = update->get_progress();
            if (newstatus != status) {
                PrintResult(resultformat, this->getName(), infos, YapiWrapper::ysprintf("%d", newstatus) + "% " + update->get_progressMessage(), true);
            }
            status = newstatus;
            YAPI::Sleep(500, errmsg);
        }
        u64 stop = YAPI::GetTickCount();
        double nbsec = (stop - start) / 1000.0;
        if (status < 0){
           PrintResult(resultformat, this->getName(), infos, YapiWrapper::ysprintf("%d", status) + " Firmware Update failed: " + update->get_progressMessage(), true);
            return -1;
        } else{
            PrintResult(resultformat, this->getName(), infos, YapiWrapper::ysprintf("%d", status) + "% Firmware Updated Successfully in " + YapiWrapper::ysprintf("%f", nbsec), true);
        }
        return 1;
    }



    int _upgradeSerial(string resultformat, const string& serial, const string& path, bool onlynew)
    {

        YModule *module = YModule::FindModule(serial);
        string product = module->get_productName();
        string current = module->get_firmwareRelease();
        YFunctionInfoCache infos = YFunctionInfoCache(module);

        // check if a new firmare is available on yoctopuce.com
        string newfirm = module->checkFirmware(path, onlynew);
        if (newfirm == "") {
            PrintResult(resultformat, this->getName(), infos, product + " " + serial + "(rev=" + current + ") is up to date", true);
            return 0;
        } else {
            PrintResult(resultformat, this->getName(), infos, product + " " + serial + "(rev=" + current + ") need be updated", true);
            PrintResult(resultformat, this->getName(), infos, "with firmware " + newfirm, true);
            // execute the firmware upgrade
            YFirmwareUpdate update = module->updateFirmware(newfirm);
            return this->_doUpgrade(resultformat, infos, &update);
        }
    }

    int _upgradeBootloader(string resultformat, const string& serial, const string& path)
    {
        string      errmsg;
        YFunctionInfoCache infos = YFunctionInfoCache(serial);

        string newfirm = YFirmwareUpdate::CheckFirmware(serial, path, 0);
        if (newfirm == "") {
            PrintResult(resultformat, this->getName(), infos, "No firmware found for device " + serial, true);
            return 0;
        } else {
            PrintResult(resultformat, this->getName(), infos, "Update firmware of device " + serial, true);
            PrintResult(resultformat, this->getName(), infos, "with firmware " + newfirm, true);
            // execute the firmware upgrade
            YFirmwareUpdate *update = new YFirmwareUpdate(serial, newfirm, "");
            return this->_doUpgrade(resultformat, infos, update);
        }
    }



    int _upgradeSerialList(string resultformat, vector<string> allserials, const string& path, bool onlynew)
    {
        int count = 0;
        for (std::vector<string>::iterator it = allserials.begin(); it != allserials.end(); ++it) {
            string serial = *it;
            if (_upgradeSerial(resultformat, serial, path, onlynew) >= 0) {
                count++;
            }
        }
        return count;
    }



public:

    string getDescription() {
        return "Download and update the firmware.";
    }

    string getName() {
        return "downloadAndUpdate";
    }

    string getMoreInfo()
    {
        return "Download and update the firmware of devices in the correct orders (all hubs, then all shields, and finally devices)."
            "If no arguments is provided this the firmware will use the most recent firmware available on www.yoctopuce.com. You can specify a path of a directory"
            " if you want to use only firmware that you have selected, in this case the only .byn files stored in this directory will be used."
            " Settings and calibrations of devices will be preserved during the update.";
    }


    vector<ArgumentDesc*>* getArgumentDesc()
    {
        vector<ArgumentDesc*>* res = new vector<ArgumentDesc*>();
        res->push_back(new ArgumentDesc(STRING_ARG, "path", "An directory where to search for byn file or www.yotctopuce.com. (default value = www.yoctopuce.com)", "_STRING", true));
        res->at(0)->set_stringValue("www.yoctopuce.com", 0);
        res->push_back(new ArgumentDesc(BOOL_ARG, "onlynew", "Update only if firmware a strictly newer that the installed version. (default value = true)", "_BOOL", true));
        res->at(1)->set_boolValue(true);
        return res;
    }


    void execute(string target, vector<YModule*> *modulelist, string resultformat, vector<ArgumentDesc*>* args, vector<SwitchDesc*>* switches)
    {
        vector<string> hubs;
        vector<string> shields;
        vector<string> devices;
        string path = (*args)[0]->get_stringValue();
        bool onlynew = (*args)[1]->get_boolValue();
   		unsigned int i;
        int bootloader_success = 0;

        YFunctionInfoCache dummyInfo;
        if (resultformat == "") {
            resultformat = "ok: [result].";
        }


        u64 bootstart = YAPI::GetTickCount();
        vector<string> bootloaders = YFirmwareUpdate::GetAllBootLoaders();
        for (std::vector<string>::iterator it = bootloaders.begin(); it != bootloaders.end(); ++it) {
            string serial = *it;
            if (_upgradeBootloader(resultformat, serial, path) >= 0) {
                bootloader_success++;
            }
        }
        u64 bootstop = YAPI::GetTickCount();


        vector<yFct*>* list = enumerateTargets<yFct>(target, modulelist);
        for (i = 0; i < list->size(); i++)
        {
             //first step construct the list of all hub /shield and devices connected
            YModule *module = (*list)[i]->get_module();
            string product = module->get_productName();
            string serial = module->get_serialNumber();
            if (product == "YoctoHub-Shield") {
                shields.push_back(serial);
            } else if (product.substr(0, 8) == "YoctoHub"){
                hubs.push_back(serial);
            } else if (product != "VirtualHub"){
                unsigned int j;
                for (j = 0; j < devices.size(); j++) {
                    if (devices[j] == serial) {
                        break;
                    }
                }
                if (j == devices.size()) {
                    devices.push_back(serial);
                }
            }
        }


        u64 start = YAPI::GetTickCount();
        // first upgrades all Hubs...
        int hubs_success = _upgradeSerialList(resultformat, hubs, path, onlynew);
        u64 hubs_stop = YAPI::GetTickCount();
        // ... then all shield..
        int shields_success = _upgradeSerialList(resultformat, shields, path, onlynew);
        u64 shields_stop = YAPI::GetTickCount();
        // ... and finally all devices
        int devices_success = _upgradeSerialList(resultformat, devices, path, onlynew);
        u64 devices_stop = YAPI::GetTickCount();

        double duration = (hubs_stop - start) / 1000.0;
        string msg = YapiWrapper::ysprintf("%d / %d hubs in %fs", hubs_success, hubs.size(), duration);
        if (hubs_success > 0) {
            msg += YapiWrapper::ysprintf(" %fs per hub", (duration / hubs_success));
        }
        PrintResult(resultformat, this->getName(), dummyInfo, msg, true);

        duration = (shields_stop - hubs_stop) / 1000.0;
        msg = YapiWrapper::ysprintf("%d / %d shields in %fs", shields_success, shields.size(),duration);
        if (shields_success > 0) {
            msg += YapiWrapper::ysprintf(" %fs per shield", (duration / shields_success));
        }
        PrintResult(resultformat, this->getName(), dummyInfo, msg, true);

        duration = (devices_stop - shields_stop) / 1000.0;
        msg = YapiWrapper::ysprintf("%d / %d devices in %fs", devices_success, devices.size(), duration);
        if (devices_success > 0){
            msg += YapiWrapper::ysprintf(" %fs per device", (duration / devices_success));
        }
        PrintResult(resultformat, this->getName(), dummyInfo, msg, true);

        if (bootloaders.size() > 0) {
            duration = (bootstop - bootstart) / 1000.0;
            msg = YapiWrapper::ysprintf("%d / %d bootloaders in %fs", bootloader_success, bootloaders.size(), duration);
            if (devices_success > 0){
                msg += YapiWrapper::ysprintf(" %fs per bootloaders", (duration / devices_success));
            }
            PrintResult(resultformat, this->getName(), dummyInfo, msg, true);
        }
        int globalres = (bootloaders.size() + devices.size() + shields.size() + hubs.size()) - (hubs_success + shields_success + devices_success + bootloader_success);
        if (globalres == 0){
            PrintResult(resultformat, this->getName(), dummyInfo, "All devices are now up to date", true);
        }
    }

};

/*
 * template function for description for registering
 * generic functions available in all cmd lines
 */

template <class yFct> void RegisterGenericFunctions(vector<YapiCommand*>* cmdList) {
    cmdList->push_back(new InventoryCmd<yFct>());
    cmdList->push_back(new DescribeCmd<yFct>());
    cmdList->push_back(new versionCmd<yFct>());
    cmdList->push_back(new get_valueChange<yFct>());
    cmdList->push_back(new FirmwareUpdateCmd<yFct>());
}

typedef map<string, SwitchDesc* > SwitchList;
