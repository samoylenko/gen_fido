#if !defined( AFX_CFGDLG_H__520459AD_1253_11D5_99FA_AAAAD4F6AE39__INCLUDED_ )
#define AFX_CFGDLG_H__520459AD_1253_11D5_99FA_AAAAD4F6AE39__INCLUDED_

//----------------------------------------------------------------------------------------------

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------------------------------------------------------

class CCfgDlg : public CDialog
{
public:
        int m_nStatus;
        int m_nPos;
        HWND m_hwndWamp;
        void GenLine();
        BOOL m_bModal;
        TCHAR *m_pszAppName;
        void SetDefaults();
        CCfgDlg( CWnd* pParent = NULL );
    CToolTipCtrl m_ToolTip;

//----------------------------------------------------------------------------------------------

    //{{AFX_DATA(CCfgDlg)
	enum { IDD = IDD_CFGDLG };
        CSpinButtonCtrl m_spnCutSymbs;
        CButton m_btnStop;
        CButton m_btnPrev;
        CButton m_btnPlay;
        CButton m_btnPaus;
        CButton m_btnNext;
        BOOL    m_bActive;
        BOOL    m_bCutStr;
        BOOL    m_bPaused;
        BOOL    m_bStopped;
        BOOL    m_bToDOS;
        int             m_nCutSymbs;
        CString m_strError;
        CString m_strFile;
        CString m_strNoWamp;
        CString m_strPaused;
        CString m_strPlaying;
        CString m_strStopped;
        CString m_strTpl;
        CString m_strLine;
	BOOL	m_bAddDots;
	//}}AFX_DATA

//----------------------------------------------------------------------------------------------

        //{{AFX_VIRTUAL(CCfgDlg)
        public:
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

//----------------------------------------------------------------------------------------------

protected:

//----------------------------------------------------------------------------------------------
        //{{AFX_MSG(CCfgDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnBtnDefaults();
        afx_msg void OnBtnFile();
        afx_msg void OnDestroy();
        afx_msg void OnBtnPrev();
        afx_msg void OnBtnPlay();
        afx_msg void OnBtnNext();
        afx_msg void OnBtnPaus();
        afx_msg void OnBtnStop();
	//}}AFX_MSG

//----------------------------------------------------------------------------------------------

    DECLARE_MESSAGE_MAP()
};

//----------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

//----------------------------------------------------------------------------------------------

#endif // !defined( AFX_CFGDLG_H__520459AD_1253_11D5_99FA_AAAAD4F6AE39__INCLUDED_ )
