#include<Windows.h>
#include"resource.h"

//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//
#define IDC_MAIN_EDIT	101
HWND hEdit;
const char g_szClassName[] = "myWindowClass";
char textSaved[20];


///C-brut

typedef struct radix
{
	char caracter;
	radix**next;
	unsigned int nr_fii;

};
radix*rad;

void inserare(radix*&p, char caracter)
{
	radix*q = (radix*)malloc(sizeof(radix));
	q->caracter = caracter;
	q->nr_fii = 0;
	if (p == NULL)
	{
		q->next = NULL;
		p = q;
	}
	else
	{
		p->nr_fii++;
		p->next = (radix**)realloc(p->next, p->nr_fii*sizeof(radix*));
		q->next = NULL;
		(p->next)[p->nr_fii - 1] = q;
	}
}
void parcurgere(radix*rad,FILE*fis2)
{
	int i;
	if (rad != NULL)
	{
		fprintf(fis2, "%c", char(int(rad->caracter)));
		for (i = 0; i < rad->nr_fii; i++)
		{
			parcurgere((rad->next)[i],fis2);
		}
	}
}
void constructie(radix*rad, char*cuv, int index)
{
	int i;
	for (i = index; i < strlen(cuv); i++)
	{
		inserare(rad, cuv[i]);
		rad = (rad->next)[rad->nr_fii - 1];
	}
}
radix*gasire_pointer(radix*rad, char car, int&ok)
{
	for (int i = 0; i < rad->nr_fii; i++)
	{
		if (rad->next[i]->caracter == car)
		{
			return rad->next[i];
		}
	}
	ok = 1;
	return rad;  ///
}
void functie(char*cuv, radix*rad)
{
	int ok = 0;
	int i = 0;
	radix*fin = NULL, *aux = NULL;
	fin = gasire_pointer(rad, cuv[i], ok);
	aux = fin;
	while (ok != 1)
	{
		i++;
		aux = fin;
		fin = gasire_pointer(fin, cuv[i], ok);
	}
	constructie(aux, cuv, i);
}

//


// Step 4: the Window Procedure


///LOAD TEXT
BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName)
{
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize;

		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF)
		{
			LPSTR pszFileText;

			pszFileText =(LPSTR) GlobalAlloc(GPTR, dwFileSize + 1);
			if (pszFileText != NULL)
			{
				DWORD dwRead;

				if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
				{
					pszFileText[dwFileSize] = 0; // Add null terminator
					if (SetWindowText(hEdit, pszFileText))
						bSuccess = TRUE; // It worked!
				}
				GlobalFree(pszFileText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}
/////

//WRITTING TEXT

BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR pszFileName)
{
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength;

		dwTextLength = GetWindowTextLength(hEdit);
		// No need to bother if there's no text.
		if (dwTextLength > 0)
		{
			LPSTR pszText;
			DWORD dwBufferSize = dwTextLength + 1;

			pszText = (LPSTR)GlobalAlloc(GPTR, dwBufferSize);
			if (pszText != NULL)
			{
				if (GetWindowText(hEdit, pszText, dwBufferSize))
				{
					DWORD dwWritten;

					if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
						bSuccess = TRUE;
				}
				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}

///
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


	switch (msg)
	{

	case WM_CREATE:
	{
					  HFONT hfDefault;
					  	  hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
						  WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
						  0, 0, 200, 200, hwnd, NULL, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)
						  MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);

					  //caseta text nr 2
					  HFONT hfDefault2;
					  hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
						  WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
						  200, 200, 400, 400, hwnd, NULL, GetModuleHandle(NULL), NULL);
					  if (hEdit == NULL)
						  MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);

	}
		break;


	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case ID_FILE_OPEN:
		{
							 OPENFILENAME ofn;
							 char szFileName[MAX_PATH] = "";

							 ZeroMemory(&ofn, sizeof(ofn));

							 ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
							 ofn.hwndOwner = hwnd;
							 ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
							 ofn.lpstrFile = szFileName;
							 ofn.nMaxFile = MAX_PATH;
							 ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
							 ofn.lpstrDefExt = "txt";

							 if (GetOpenFileName(&ofn))
							 {
								 // Do something usefull with the filename stored in szFileName
								 MessageBox(hwnd, szFileName, "Ati ales",
									 MB_OK | MB_ICONEXCLAMATION);
								static char text[100];

								LoadTextFileToEdit(hEdit, szFileName);
								// MessageBox(hwnd, text, text, MB_OK | MB_ICONERROR);
								// SaveTextFileFromEdit(hwnd, szFileName);
							 }

		}
			break;
		case ID_FILE_SAVE:
		{
							 int val=0;
							 val = GetWindowText(hEdit, &textSaved[0], 50);
							 MessageBox(hwnd, textSaved, "Text inserat din:",
								 MB_OK | MB_ICONEXCLAMATION);

							 OPENFILENAME ofn;
							 char szFileName[MAX_PATH] = "";

							 ZeroMemory(&ofn, sizeof(ofn));

							 ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
							 ofn.hwndOwner = hwnd;
							 ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
							 ofn.lpstrFile = szFileName;
							 ofn.nMaxFile = MAX_PATH;
							 ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
							 ofn.lpstrDefExt = "txt";

							 if (GetOpenFileName(&ofn))
							 {
								 // Do something usefull with the filename stored in szFileName
								 MessageBox(hwnd, szFileName, "Text Salvat in:",
									 MB_OK | MB_ICONEXCLAMATION);
								
							 }
							 SaveTextFileFromEdit(hEdit, szFileName);

		}
			break;
		case ID_RUN:
		{	
					   char cuv[20];
					   inserare(rad, ' ');
					   FILE*fis= fopen("fis.txt", "rt");
					   FILE*fis2;
					   while (!feof(fis))
					   {
						   fscanf(fis, "%s", cuv);
						   functie(cuv, rad);
					   }
					   fclose(fis);
					   fis2 = fopen("f.txt", "wt");
					   parcurgere(rad, fis2);
					   fclose(fis2);
					   LoadTextFileToEdit(hEdit, "f.txt");
		}
			break;
		case 1:
			{
				  int VAL = 0;
				  //	char *t = &textSaved[0];
				  VAL = GetWindowText(hEdit, &textSaved[0], 50);

				  ::MessageBox(hwnd, textSaved, textSaved, MB_OK);
				  break;

			}
		}
		break;


	case WM_SIZE:
	{
					HWND hEdit;
					RECT rcClient;

					GetClientRect(hwnd, &rcClient);

					hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
					SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
	}
		break;


	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
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

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW );
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 850, 420,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}