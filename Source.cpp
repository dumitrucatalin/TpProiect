#include <Windows.h>
#include "resource1.h"

#define IDC_PRESS   2
#define IDC_OTHER	1


HWND g_hToolbar = NULL;

HWND hEdit;

const char g_szClassName[] = "myWindowClass";




BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

///


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
						   char szFileName[MAX_PATH];
						   HINSTANCE hInstance = GetModuleHandle(NULL);

						   GetModuleFileName(hInstance, szFileName, MAX_PATH);
						   MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);

						 

	}
		break;

	case WM_RBUTTONDOWN:
	{
						   char szFileName[MAX_PATH];
						   HINSTANCE hInstance = GetModuleHandle(NULL);

					//	   GetModuleFileName(hInstance, szFileName, MAX_PATH);
						   //   MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
	
						MessageBox(hwnd, "Bye!", "This is also a message",
							MB_OK | MB_ICONEXCLAMATION);
	}
		break;


	case WM_COMMAND:

		switch (LOWORD(wParam))
	 {
	   case  ID_BBBS:
	   {
								
						MessageBox(hwnd, "Bye!", "This is also a message",
							MB_OK | MB_ICONEXCLAMATION);
	   }
		   break;

	   case BUTTON1:
	   {  
					  char buffer[256];
			   SendMessage(hEdit,
			   WM_GETTEXT,
			   sizeof(buffer) / sizeof(buffer[0]),
			   reinterpret_cast<LPARAM>(buffer));
			   MessageBox(NULL,
			   buffer,
			   "Information",
			   MB_ICONINFORMATION);

	  }
		   break;

	   case ID_HELP:
	   {
					   int ret = DialogBox(GetModuleHandle(NULL),
						   MAKEINTRESOURCE(IDD_DIALOG2), hwnd, ToolDlgProc);
					   if (ret == IDOK){
						   MessageBox(hwnd, "Dialog exited with IDOK.", "Notice",
							   MB_OK | MB_ICONINFORMATION);
					   }
					   else if (ret == IDCANCEL){
						   MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice",
							   MB_OK | MB_ICONINFORMATION);
					   }
					   else if (ret == -1){
						   MessageBox(hwnd, "Dialog failed!", "Error",
							   MB_OK | MB_ICONINFORMATION);
					   }
	   }
		   break;
	   case ID_FILE_PRINT:
	   {
							 MessageBox(hwnd, "Ceva interesant!!","Informatie", MB_OK | MB_ICONINFORMATION);
							
	   }
		   break;
	   case ID_TEXT:
	   {
					   
					  DialogBox(GetModuleHandle(NULL),
					  MAKEINTRESOURCE(IDD_DIALOG3), hwnd, ToolDlgProc);

			
	
	   }
		   break;
	//   case IDC_REMOVE:
	   { 
					   MessageBox(hwnd, "Ceva interesant!!", "Informatie", MB_OK | MB_ICONINFORMATION);
					   HWND hList = GetDlgItem(hwnd, IDD_DIALOG3);
					   int count = SendMessage(hList, LB_GETSELCOUNT, 0, 0);

					   int *buf = (int*)GlobalAlloc(GPTR, sizeof(int)* count);
					   SendMessage(hList, LB_GETSELITEMS, (WPARAM)count, (LPARAM)buf);
					    
					  
					   // ... Do stuff with indexes

					   GlobalFree(buf);


	   }
		   break;

	   case IDD_DIALOG3:
	   {

						  
				   switch (HIWORD(wParam))
			 {
					


				   case IDC_EDIT1:
				   {  // Selection changed, do stuff here.


										 int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT1));
										 if (len > 0)
										 {
											 int i;
											 char* buf;

											 buf = (char*)GlobalAlloc(GPTR, len + 1);
											 GetDlgItemText(hwnd, IDC_EDIT1, buf, len + 1);

											 //... do stuff with text ...
											   
											
											 //

											 BOOL bSuccess;
											 int nTimes = GetDlgItemInt(hwnd, IDC_NUMBER, &bSuccess, FALSE);


											 int index = SendDlgItemMessage(hwnd, IDC_LISTBOX, LB_ADDSTRING, 0, (LPARAM)"ceva");
											 SendDlgItemMessage(hwnd, IDD_DIALOG3, LB_SETITEMDATA, (WPARAM)index, (LPARAM)nTimes);




											 GlobalFree((HANDLE)buf);
										 }
				   }

					   break;
			 }
					   break;
						   // ... other controls

	   }

		   break;
	   }
		
	   return true;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		DestroyWindow(g_hToolbar);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = g_szClassName;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE("images.png"));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE("images.png"), IMAGE_ICON, 16, 16, 0);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 120,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}