#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// ����ʵ���򱾳����˳�����ֹ�ظ���
	HANDLE hMutex = CreateMutex(NULL, FALSE, "HtmlBomTool");
	if (hMutex && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return FALSE;
	}

	// �ļ�ѡ��Ի���
	TCHAR szFileName[MAX_PATH] = { 0 };
	OPENFILENAME openFile = { 0 };
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrFilter = "json�ļ�(*.json)\0*.json\0";
	openFile.lpstrFile = szFileName;
	openFile.nFilterIndex = 1;
	openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	openFile.lpstrTitle = "ѡ��������EDA��PCB������json�ļ�";
	if (GetOpenFileName(&openFile))
	{
		// �������ִ��
		TCHAR szPath[MAX_PATH] = { 0 };
		TCHAR szCmd[MAX_PATH] = { 0 };
		strcpy_s(szPath, MAX_PATH, __argv[0]);
		*strrchr(szPath, '\\') = 0;
		sprintf_s(szCmd, "cmd /c cd \"%s\" & py generate_interactive_bom.py \"%s\"", szPath, openFile.lpstrFile);
		WinExec(szCmd, SW_HIDE);
	}
	return 0;
}
