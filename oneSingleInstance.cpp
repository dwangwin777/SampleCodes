    HANDLE hMutexOneInstance = 
    CreateMutex(NULL,TRUE,_T("PreventMultipleDsVisionInstance"));
    if(GetLastError() == ERROR_ALREADY_EXISTS)
        bFound = true;
    if(hMutexOneInstance) 
        ReleaseMutex(hMutexOneInstance);
		
int ViewRightAVDecoder::StartInitializationThread(void * pThis)
{
	bool bInitializing = false;
	HANDLE mtx = CreateMutex(NULL,TRUE,_T("ViewRightAVDecoder::StartInitializationThread"));
	if (mtx != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		bInitializing = true;
	}
	DebugLog::GetInstance()->Write(DebugLog::DLOG_Trace, L"ViewRightAVDecoder::StartInitializationThread: %S", bInitializing?"StartInitializationThread already in process":"StartInitializationThread Successful");
	if (bInitializing)
	{
		return VRAV_Error;
	}
    int iRet = ((ViewRightAVDecoder *)pThis)->Initialize();
	if (mtx)
	{
		CloseHandle(mtx);
	}
	return iRet;
}		

SHORT CViewRightActiveXControlSDKCtrl::Open(LPCTSTR mrl, VARIANT_BOOL UseQuickTune)
{
	bool bInitializing = false;
	HANDLE mtx = CreateMutex(NULL,TRUE,_T("CViewRightActiveXControlSDKCtrl::Open"));
	if (mtx != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		bInitializing = true;
	}
	DebugLog::GetInstance()->Write(DebugLog::DLOG_Trace, L"ViewRightAVDecoder::StartInitializationThread: %S;mtx=%d\n", bInitializing?"StartInitializationThread already in process":"StartInitializationThread Successful",
		mtx == NULL ?0 : 1);
	if (mtx)
	{
//		ReleaseMutex(mtx);
	}
	if (bInitializing)
		return -1;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_pVR)
	{
#ifdef VIEWRIGHT_WEB
		if(m_bWindowless)
		{			
			WNDCLASS	wc;
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			wc.lpfnWndProc = (WNDPROC)CViewRightActiveXControlSDKCtrl::WindowlessMessagingProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = GetModuleHandle(NULL);
			wc.hIcon = NULL;
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wc.lpszMenuName = TEXT("");
			wc.lpszClassName = TEXT("Windowless Messaging");
			RegisterClass(&wc);
			m_windowlessHWND = CreateWindowEx(WS_EX_TOPMOST, _T("Windowless Messaging"),
													_T("Windowless Messaging"),
													WS_POPUP, 0,0,
													0, 0, HWND_MESSAGE , NULL, GetModuleHandle(NULL), NULL);

		}	
		CStringA mrlString(mrl);
		char * mrlArray = mrlString.GetBuffer(mrlString.GetLength());
		mrlString.ReleaseBuffer();
		//TODO why do we have to check we are not in full screen mode????
		bool bFullScreen;
		m_pVR->GetFullScreen(bFullScreen);
		if(!bFullScreen && m_pFullScreenControl)
		{
			void * redrawFunc = NULL;
			if(m_bWindowless)
			{
				redrawFunc = (void *)CViewRightActiveXControlSDKCtrl::WindowlessRedraw;
			}
			m_pVR->SetParentWindow(&m_hWnd, sizeof(m_hWnd),m_pFullScreenControl,redrawFunc);
		}
		int iRet = (SHORT) m_pVR->Open(mrlArray);
		CloseHandle(mtx);
		return iRet;