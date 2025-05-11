#ifndef FUNCTIONS_H
#define FUNCTIONS_H
template <class T>
class Singleton;

class Function;
class MaintainSystem;
class Monitor;
class Timing;

class Functions
{
private:
    Functions();
    Functions(Functions &)=delete;
    Functions(Functions &&)=delete;
    Functions &operator=(const Functions&)=delete;
    Functions &operator=(Functions&&)=delete;
    friend Singleton<Functions>;
public:
    ~Functions();
    static Functions*instance();
    typedef enum
    {
        FUNCTION_ID_TIMING,
        FUNCTION_ID_MONITOR,
        FUNCTION_ID_SCAN_SPECIMEN_BARCODE,
        FUNCTION_ID_SCAN_REAGENTDISC_BARCODE,
    }FunctionID;
public:
    Monitor *get_monitor();
    MaintainSystem *getMaintain();
    Timing *getTimimg();

private:
    Function *_monitor;
    Function *_maintain;
    Function *_timing;
};

#endif // FUNCTIONS_H
