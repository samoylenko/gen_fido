typedef struct
{
    int       nVersion;
    TCHAR     *pszDesc;
    int       (*pInit)();
    void      (*pCfg)();
    void      (*pQuit)();
    HWND      hwndWinamp;
    HINSTANCE hDllInstance;

} WAMPGENPLGN;

//----------------------------------------------------------------------------------------------

#define GPPHDR_VER 0x10
