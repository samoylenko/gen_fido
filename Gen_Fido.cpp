#include "stdafx.h"
#include "Gen_Fido.h"
#include "CfgDlg.h"

//----------------------------------------------------------------------------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static TCHAR THIS_FILE[] = __FILE__;
#endif // _DEBUG

//----------------------------------------------------------------------------------------------

#define TIMERID  0x100
#define TIMERFRQ 1000

//----------------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CGen_FidoApp, CWinApp)
	//{{AFX_MSG_MAP(CGen_FidoApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------

CGen_FidoApp::CGen_FidoApp()
{  

} // CGen_FidoApp::CGen_FidoApp

//----------------------------------------------------------------------------------------------

WAMPGENPLGN  g_Plugin;
GENFIDOCFG   g_Config;

CGen_FidoApp g_App;
CCfgDlg      g_CfgDlg;
CFile        g_File;

TCHAR        g_szAppName[] = _T( "PowerMike's Fido Plug-In v3.0" );

TCHAR        g_szDesc[257];
TCHAR        g_szCfgName[MAX_PATH + 1];

WNDPROC      wprocOld;

//----------------------------------------------------------------------------------------------

void WriteConfig();
void ReadConfig();
void Quit();
void Config();
void AskWriteConfig();
void UpdateConfig( BOOL bMem );
void ReadIni();
void CrtFile();
void ToDOS( TCHAR *pszLine );
void TestWampVer();

INT  Init();

LRESULT WINAPI WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

//----------------------------------------------------------------------------------------------

extern "C" __declspec( dllexport ) WAMPGENPLGN *winampGetGeneralPurposePlugin()
{
    g_Plugin.nVersion     = GPPHDR_VER;
    g_Plugin.pInit        = Init;
    g_Plugin.pCfg         = Config;
    g_Plugin.pQuit        = Quit;

    g_CfgDlg.m_pszAppName = g_szAppName;
 
    return &g_Plugin;

} // winampGetGeneralPurposePlugin

//----------------------------------------------------------------------------------------------

INT Init()
{
    TCHAR *pFN;

    GetModuleFileName( g_Plugin.hDllInstance, g_szCfgName, sizeof( g_szCfgName ) );

    pFN = g_szCfgName + _tcslen( g_szCfgName );
    while( ( *pFN != _T( '\\' ) )&&( pFN-- >= g_szCfgName ) );
    _stprintf( g_szDesc, _T( "%s :: ( %s )" ), g_szAppName, ++pFN );
    g_Plugin.pszDesc  = g_szDesc;

    while( ( *pFN++ != _T( '.' ) )&&( *pFN ) );
    _tcscpy( pFN, _T( "CFG" ) );

    ReadConfig();
    TestWampVer();

    g_CfgDlg.m_hwndWamp = g_Plugin.hwndWinamp;

    SetTimer( g_Plugin.hwndWinamp, TIMERID, TIMERFRQ, NULL);
    wprocOld = ( WNDPROC )SetWindowLong(g_Plugin.hwndWinamp, GWL_WNDPROC, ( long )WndProc );
    
    return 0;

} // Init

//----------------------------------------------------------------------------------------------

void Config()
{
    if( g_CfgDlg.DoModal() == IDOK )
    {
        WriteConfig();

        if( g_Config.bActive )
        {
            g_CfgDlg.GenLine();
            CrtFile();

        } // if( g_Config.bActive )

    } // if( g_CfgDlg.DoModal() == IDOK )
    else
    {
        UpdateConfig( FALSE );

    } // if( g_CfgDlg.DoModal() != IDOK )

} // Config

//----------------------------------------------------------------------------------------------

void Quit()
{
    if( g_Config.bActive )
    {
        g_CfgDlg.m_strLine = g_CfgDlg.m_strNoWamp;
        CrtFile();
    }

} // Quit

//----------------------------------------------------------------------------------------------

void ReadConfig()
{
    if( g_File.Open(

        g_szCfgName, 
        CFile::modeRead

    ) ) // g_File.Open
    {
        g_File.Read( &g_Config, sizeof( g_Config ) );
        g_File.Close();

        switch( g_Config.nCfgVer )
        {
        case CFGVER:

            UpdateConfig( FALSE );
            break;

        case V20CFG:

            g_Config.bAddDots = TRUE;
            UpdateConfig( FALSE );

            if( MessageBox(

                g_Plugin.hwndWinamp,
                _T( "Finded version of configuration file is from v2.0. Rewrite it?" ),
                g_szAppName,
                MB_ICONQUESTION | MB_YESNO

            ) == IDYES ) // MessageBox
            {
                WriteConfig();

            } // if( MessageBox() == IDYES )
           
            break;

        default:

            MessageBox(

                g_Plugin.hwndWinamp,
                _T( "Unknown version of configuration file. Setting to defaults." ),
                g_szAppName,
                MB_ICONWARNING | MB_OK

            ); // MessageBox

            g_CfgDlg.SetDefaults();
            AskWriteConfig();
            
        } // switch( g_Config.nCfgVer )

    } // if( g_File.Open() )
    else
    {
        MessageBox(

            g_Plugin.hwndWinamp,
            _T( "Error reading configuration file. Setting to defaults." ),
            g_szAppName,
            MB_ICONWARNING | MB_OK

        ); // MessageBox

        g_CfgDlg.SetDefaults();
        AskWriteConfig();
        
    } // if( !g_File.Open() )

    UpdateConfig( TRUE );

} // ReadConfig

//----------------------------------------------------------------------------------------------

void WriteConfig()
{
    UpdateConfig( TRUE );

    if( g_File.Open(

        g_szCfgName, 
        CFile::modeCreate | CFile::modeWrite

    ) ) // g_File.Open
    {
        g_File.Write( &g_Config, sizeof( g_Config ) );
        g_File.Close();

    } // if( g_File.Open() )
    else
    {
        MessageBox(

            g_Plugin.hwndWinamp,
            _T( "Error writing configuration file" ),
            g_szAppName,
            MB_ICONWARNING | MB_OK

        ); // MessageBox

    } // if( !g_File.Open() )

} // WriteConfig

//----------------------------------------------------------------------------------------------

void AskWriteConfig()
{
    if( MessageBox(

        g_Plugin.hwndWinamp,
        _T( "Rewrite configuration file?" ),
        g_szAppName,
        MB_ICONQUESTION | MB_YESNO

    ) == IDYES ) // MessageBox
    {
        WriteConfig();

    } // if( MessageBox() == IDYES )

} // AskWriteConfig

//----------------------------------------------------------------------------------------------

void UpdateConfig( BOOL bMem )
{
    if( bMem )
    {
        g_Config.nCfgVer   = CFGVER;
        g_Config.bActive   = g_CfgDlg.m_bActive;
        g_Config.bCutStr   = g_CfgDlg.m_bCutStr;
        g_Config.bPaused   = g_CfgDlg.m_bPaused;
        g_Config.bStopped  = g_CfgDlg.m_bStopped;
        g_Config.bToDOS    = g_CfgDlg.m_bToDOS;
        g_Config.nCutSymbs = g_CfgDlg.m_nCutSymbs;

        _tcscpy( g_Config.szError,   ( LPCSTR )g_CfgDlg.m_strError   );
        _tcscpy( g_Config.szFile,    ( LPCSTR )g_CfgDlg.m_strFile    );
        _tcscpy( g_Config.szNoWamp,  ( LPCSTR )g_CfgDlg.m_strNoWamp  );
        _tcscpy( g_Config.szPaused,  ( LPCSTR )g_CfgDlg.m_strPaused  );
        _tcscpy( g_Config.szPlaying, ( LPCSTR )g_CfgDlg.m_strPlaying );
        _tcscpy( g_Config.szStopped, ( LPCSTR )g_CfgDlg.m_strStopped );
        _tcscpy( g_Config.szTpl,     ( LPCSTR )g_CfgDlg.m_strTpl     );

        g_Config.bAddDots  = g_CfgDlg.m_bAddDots;

    } // if( bMem )
    else
    {
        g_CfgDlg.m_bActive    = g_Config.bActive;
        g_CfgDlg.m_bCutStr    = g_Config.bCutStr;
        g_CfgDlg.m_bPaused    = g_Config.bPaused;
        g_CfgDlg.m_bStopped   = g_Config.bStopped;
        g_CfgDlg.m_bToDOS     = g_Config.bToDOS;
        g_CfgDlg.m_nCutSymbs  = g_Config.nCutSymbs;

        g_CfgDlg.m_strError   = g_Config.szError;
        g_CfgDlg.m_strFile    = g_Config.szFile; 
        g_CfgDlg.m_strNoWamp  = g_Config.szNoWamp;
        g_CfgDlg.m_strPaused  = g_Config.szPaused;
        g_CfgDlg.m_strPlaying = g_Config.szPlaying;
        g_CfgDlg.m_strStopped = g_Config.szStopped;
        g_CfgDlg.m_strTpl     = g_Config.szTpl;

        g_CfgDlg.m_bAddDots   = g_Config.bAddDots;

    } // if( !bMem )

} // UpdateConfig

//----------------------------------------------------------------------------------------------

void CrtFile()
{
    TCHAR szLine[513];

    _tcscpy( szLine, ( LPCSTR )g_CfgDlg.m_strLine );

    if( g_Config.bToDOS )
    {
        ToDOS( szLine );

    } // if( g_CfgDlg.m_bToDOS )

    if( g_File.Open(
        
        g_Config.szFile,
        CFile::modeCreate | CFile::modeWrite

    ) ) // g_File.Open
    {
        g_File.Write( szLine, _tcslen( szLine ) );
        g_File.Close();

    } // if( g_File.Open() )

} // CrtFile

//----------------------------------------------------------------------------------------------

void ToDOS( TCHAR *pszLine )
{
    while( *pszLine )
    {
        if( *pszLine == _T( 'Í' ) )
        {
            *pszLine =  _T( 'H' );

        } // if( *pszLine == _T( 'Í' ) )

        if( *pszLine == _T( 'ð' ) )
        {
            *pszLine =  _T( 'p' );

        } // if( *pszLine == _T( 'p' ) )

        if( ( *pszLine >= _T( 'À' ) )&&( *pszLine <= _T( 'ï' ) ) )
        {
           *pszLine -= _T( 0x40 );

        } // if( ( *pszLine >= _T( 'À' ) )&&( *pszLine <= _T( 'ï' ) ) )
        else
        {
            if( (*pszLine >= _T( 'ð' ) )&&( *pszLine <= _T( 'ÿ' ) ) )
            {
                *pszLine -= _T( 0x10 );

            } // if( (*pszLine >= _T( 'ð' ) )&&( *pszLine <= _T( 'ÿ' ) ) )
        }

        pszLine++;
    }

} // ToDOS

//----------------------------------------------------------------------------------------------

void TestWampVer()
{
    INT nVer = SendMessage(g_Plugin.hwndWinamp, WM_WA_IPC, 0, IPC_GETVERSION);

    if( nVer < 0x2005 )
    {
        MessageBox(

            g_Plugin.hwndWinamp, 
            _T( "This plug-in supports Winamp v2.05 and above only" ),
            g_szAppName,
            MB_ICONWARNING | MB_OK

        ); // MessageBox

        g_CfgDlg.m_bActive = FALSE;

    } // if( nVer < 0x2005 )

} // TestWampVer

//----------------------------------------------------------------------------------------------

LRESULT WINAPI WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    INT nResP, nResS;

    if( uMsg == WM_TIMER )
    {
        if( wParam == TIMERID )
        {
            nResP = ::SendMessage( g_Plugin.hwndWinamp, WM_WA_IPC, 0, IPC_GETLISTPOS );
            nResS = ::SendMessage( g_Plugin.hwndWinamp, WM_WA_IPC, 0, IPC_ISPLAYING  );

            if( ( g_CfgDlg.m_nPos != nResP )||( g_CfgDlg.m_nStatus != nResS ) )
            {
                g_CfgDlg.m_nPos    = nResP;
                g_CfgDlg.m_nStatus = nResS;

                g_CfgDlg.GenLine();

                if( g_Config.bActive )
                {
                    CrtFile();

                } // if( g_CfgDlg.m_bActive )

            } // if( ( g_CfgDlg.m_nPos != nResP )||( g_CfgDlg.m_nStatus != nResS ) )

        } // if( wParam == TIMERID )

    } // if( uMsg == WM_TIMER )

    return CallWindowProc( wprocOld, hwnd, uMsg, wParam, lParam );

} // WndProc

//----------------------------------------------------------------------------------------------
