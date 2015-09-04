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

CCfgDlg::CCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCfgDlg)
	m_bActive = FALSE;
	m_bCutStr = FALSE;
	m_bPaused = FALSE;
	m_bStopped = FALSE;
	m_bToDOS = FALSE;
	m_nCutSymbs = 0;
	m_strError = _T("");
	m_strFile = _T("");
	m_strNoWamp = _T("");
	m_strPaused = _T("");
	m_strPlaying = _T("");
	m_strStopped = _T("");
	m_strTpl = _T("");
	m_strLine = _T("");
	m_bAddDots = FALSE;
	//}}AFX_DATA_INIT

} // CCfgDlg::CCfgDlg

//----------------------------------------------------------------------------------------------

void CCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgDlg)
	DDX_Control(pDX, IDC_SPNCUTSYMBS, m_spnCutSymbs);
	DDX_Control(pDX, IDC_BTNSTOP, m_btnStop);
	DDX_Control(pDX, IDC_BTNPREV, m_btnPrev);
	DDX_Control(pDX, IDC_BTNPLAY, m_btnPlay);
	DDX_Control(pDX, IDC_BTNPAUS, m_btnPaus);
	DDX_Control(pDX, IDC_BTNNEXT, m_btnNext);
	DDX_Check(pDX, IDC_CHECKACTIVE, m_bActive);
	DDX_Check(pDX, IDC_CHKCUTSTR, m_bCutStr);
	DDX_Check(pDX, IDC_CHKPAUSED, m_bPaused);
	DDX_Check(pDX, IDC_CHKSTOPPED, m_bStopped);
	DDX_Check(pDX, IDC_CHKTODOS, m_bToDOS);
	DDX_Text(pDX, IDC_EDTCUTSYMBS, m_nCutSymbs);
	DDV_MinMaxInt(pDX, m_nCutSymbs, 0, 256);
	DDX_Text(pDX, IDC_EDTERROR, m_strError);
	DDV_MaxChars(pDX, m_strError, 256);
	DDX_Text(pDX, IDC_EDTFILE, m_strFile);
	DDX_Text(pDX, IDC_EDTNOWAMP, m_strNoWamp);
	DDX_Text(pDX, IDC_EDTPAUSED, m_strPaused);
	DDV_MaxChars(pDX, m_strPaused, 256);
	DDX_Text(pDX, IDC_EDTPLAYING, m_strPlaying);
	DDV_MaxChars(pDX, m_strPlaying, 256);
	DDX_Text(pDX, IDC_EDTSTOPPED, m_strStopped);
	DDV_MaxChars(pDX, m_strStopped, 256);
	DDX_Text(pDX, IDC_EDTTPL, m_strTpl);
	DDV_MaxChars(pDX, m_strTpl, 256);
	DDX_Text(pDX, IDC_EDTTEST, m_strLine);
	DDV_MaxChars(pDX, m_strLine, 512);
	DDX_Check(pDX, IDC_CHKADDDOTS, m_bAddDots);
	//}}AFX_DATA_MAP
} // CCfgDlg::DoDataExchange

//----------------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CCfgDlg, CDialog)
	//{{AFX_MSG_MAP(CCfgDlg)
	ON_BN_CLICKED(IDC_BTNDEFAULTS, OnBtnDefaults)
	ON_BN_CLICKED(IDC_BTNFILE, OnBtnFile)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNPREV, OnBtnPrev)
	ON_BN_CLICKED(IDC_BTNPLAY, OnBtnPlay)
	ON_BN_CLICKED(IDC_BTNNEXT, OnBtnNext)
	ON_BN_CLICKED(IDC_BTNPAUS, OnBtnPaus)
	ON_BN_CLICKED(IDC_BTNSTOP, OnBtnStop)
	ON_BN_CLICKED(IDC_CHKCUTSTR, GenLine)
	ON_BN_CLICKED(IDC_CHKPAUSED, GenLine)
	ON_BN_CLICKED(IDC_CHKSTOPPED, GenLine)
	ON_EN_CHANGE(IDC_EDTCUTSYMBS, GenLine)
	ON_EN_CHANGE(IDC_EDTERROR, GenLine)
	ON_EN_CHANGE(IDC_EDTPAUSED, GenLine)
	ON_EN_CHANGE(IDC_EDTPLAYING, GenLine)
	ON_EN_CHANGE(IDC_EDTSTOPPED, GenLine)
	ON_EN_CHANGE(IDC_EDTTPL, GenLine)
	ON_BN_CLICKED(IDC_CHKADDDOTS, GenLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------

BOOL CCfgDlg::OnInitDialog() 
{
    HINSTANCE hRes = AfxGetResourceHandle();

    CDialog::OnInitDialog();
	
    m_btnPrev.SetIcon( LoadIcon( hRes, MAKEINTRESOURCE( IDI_PREV ) ) );
    m_btnPlay.SetIcon( LoadIcon( hRes, MAKEINTRESOURCE( IDI_PLAY ) ) );
    m_btnPaus.SetIcon( LoadIcon( hRes, MAKEINTRESOURCE( IDI_PAUS ) ) );
    m_btnStop.SetIcon( LoadIcon( hRes, MAKEINTRESOURCE( IDI_STOP ) ) );
    m_btnNext.SetIcon( LoadIcon( hRes, MAKEINTRESOURCE( IDI_NEXT ) ) );

    m_spnCutSymbs.SetRange( 0, 256 );

    m_bModal = TRUE;

    m_ToolTip.Create( this, 0 );
    m_ToolTip.Activate( TRUE );

    m_ToolTip.AddTool( GetDlgItem( IDC_EDTTPL      ), IDS_TIPEDTTPL      );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTCUTSYMBS ), IDS_TIPEDTCUTSYMBS );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTERROR    ), IDS_TIPEDTERROR    );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTFILE     ), IDS_TIPEDTFILE     );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTNOWAMP   ), IDS_TIPEDTNOWAMP   );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTPAUSED   ), IDS_TIPEDTPAUSED   );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTPLAYING  ), IDS_TIPEDTPLAYING  );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTSTOPPED  ), IDS_TIPEDTSTOPPED  );
    m_ToolTip.AddTool( GetDlgItem( IDC_EDTTEST     ), IDS_TIPEDTTEST     );

    return TRUE;  
            
} // CCfgDlg::OnInitDialog

//----------------------------------------------------------------------------------------------

void CCfgDlg::SetDefaults()
{
    m_bActive    = FALSE;
    m_bCutStr    = TRUE;
    m_bPaused    = FALSE;
    m_bStopped   = TRUE;
    m_bToDOS     = TRUE;
    m_nCutSymbs  = 76;
    m_strError   = _T( "[ invalid playlist ]"   );
    m_strFile    = _T( "c:\\winamp.txt"         );
    m_strNoWamp  = _T( "[ no winamp ]"          );
    m_strPaused  = _T( "paused"                 );
    m_strPlaying = _T( "playing"                );
    m_strStopped = _T( "[ winamp is stopped ]"  );
    m_strTpl     = _T( "[ winamp is %2 ] :: %1" );

    m_bAddDots   = TRUE;

} // CCfgDlg::SetDefaults

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnBtnDefaults() 
{
    if( MessageBox(

        _T( "Are you sure?" ),
        m_pszAppName,
        MB_ICONQUESTION | MB_YESNO

    ) == IDYES ) // MessageBox
    {
        SetDefaults();
		UpdateData( FALSE );
        GenLine();

    } // if( MessageBox() ) == IDYES

} // CCfgDlg::OnBtnDefaults

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnBtnFile() 
{
    CFileDialog fileDlg( FALSE );

    fileDlg.m_ofn.lpstrFilter = _T( "All files (*.*)\0*.*\0" );
    fileDlg.m_ofn.lpstrTitle  = _T( "Save as"          );

    if( fileDlg.DoModal() == IDOK )
    {
        m_strFile = fileDlg.GetPathName();
        UpdateData( FALSE );

    } // if( fileDlg.DoModal() == IDOK )

} // CCfgDlg::OnBtnFile

//----------------------------------------------------------------------------------------------

void CCfgDlg::GenLine()
{
    TCHAR *pszTitle;
    INT   nIdx;

    if( m_bModal )
    {
        UpdateData( TRUE );

    } // if( m_bModal )

    m_strLine = m_strTpl;

    pszTitle = (TCHAR *)::SendMessage(

        m_hwndWamp,
        WM_WA_IPC,
        m_nPos,
        IPC_GETPLAYLISTTITLE

    ); // SendMessage

    if( pszTitle )
    {
        if(( m_nStatus == 0 )&&( m_bStopped ))
        {
            m_strLine = m_strStopped;

        } // if(( m_nStatus == 0 )&&( m_bStopped ))

        if(( m_nStatus == 3 )&&( m_bPaused ))
        {
            m_strLine = m_strPaused;

        } // if(( m_nStatus == 3 )&&( m_bPaused ))

        if( ( nIdx = m_strLine.Find( _T( "%1" ), 0 ) ) != -1 )
        {
            m_strLine.Delete( nIdx, 2        );
            m_strLine.Insert( nIdx, pszTitle );

        } // if( ( nIdx = m_strPaused.Find( _T( "%1" ), 0 ) ) != -1 )

        if( ( nIdx = m_strLine.Find( _T( "%2" ), 0 ) ) != -1 )
        {
            m_strLine.Delete( nIdx, 2 );

            switch(m_nStatus)
            {
            case 0:
                m_strLine.Insert( nIdx, m_strStopped );
                break;

            case 1:
                m_strLine.Insert( nIdx, m_strPlaying );
                break;

            case 3:
                m_strLine.Insert( nIdx, m_strPaused  );
                break;
            }

        } // if( ( nIdx = m_strPaused.Find( _T( "%2" ), 0 ) ) != -1 )

    } // if( pszTitle )
    else
    {
        m_strLine = m_strError;

    } // if( !pszTitle )

    if( ( m_bCutStr)&&( m_strLine.GetLength() > m_nCutSymbs ) )
    {
        m_strLine = m_strLine.Left( m_nCutSymbs );
        
        if( m_bAddDots )
        {
            m_strLine += _T( "..." );

        } // if( m_bAddDots )

    } // if( m_bCutStr )

    m_strLine = m_strLine.Left( 512 );

    if( m_bModal )
    {
        UpdateData( FALSE );

    } // if( m_bModal )

} // CCfgDlg::GenLine

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
    m_bModal = FALSE;
  
} // CCfgDlg::OnDestroy

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnBtnPrev() 
{
        ::SendMessage( m_hwndWamp, WM_COMMAND, WINAMP_BUTTON1, 0 );
        GenLine();

} // CCfgDlg::OnBtnPrev

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnBtnPlay() 
{
        ::SendMessage( m_hwndWamp, WM_COMMAND, WINAMP_BUTTON2, 0 );
        GenLine();
    
} // CCfgDlg::OnBtnPlay

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnBtnNext() 
{
        ::SendMessage( m_hwndWamp, WM_COMMAND, WINAMP_BUTTON5, 0 );
        GenLine();

} // CCfgDlg::OnBtnNext

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnBtnPaus() 
{
        ::SendMessage( m_hwndWamp, WM_COMMAND, WINAMP_BUTTON3, 0 );
        GenLine();
	
} // CCfgDlg::OnBtnPaus

//----------------------------------------------------------------------------------------------

void CCfgDlg::OnBtnStop() 
{
        ::SendMessage( m_hwndWamp, WM_COMMAND, WINAMP_BUTTON4, 0 );
        GenLine();
	
} // CCfgDlg::OnBtnStop

//----------------------------------------------------------------------------------------------

BOOL CCfgDlg::PreTranslateMessage( MSG* pMsg ) 
{
    m_ToolTip.RelayEvent( pMsg );
    
	return CDialog::PreTranslateMessage( pMsg );

} // CCfgDlg::PreTranslateMessage

//----------------------------------------------------------------------------------------------
