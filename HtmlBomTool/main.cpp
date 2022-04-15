#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// 已有实例则本程序退出，防止重复打开
	HANDLE hMutex = CreateMutex(NULL, FALSE, "HtmlBomTool");
	if (hMutex && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return FALSE;
	}

	// 文件选择对话框
	TCHAR szFileName[MAX_PATH] = { 0 };
	OPENFILENAME openFile = { 0 };
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrFilter = "json文件(*.json)\0*.json\0";
	openFile.lpstrFile = szFileName;
	openFile.nFilterIndex = 1;
	openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	openFile.lpstrTitle = "选择由立创EDA中PCB导出的json文件";
	if (GetOpenFileName(&openFile))
	{
		// 生成命令并执行
		TCHAR szPath[MAX_PATH] = { 0 };
		TCHAR szCmd[MAX_PATH] = { 0 };
		strcpy_s(szPath, MAX_PATH, __argv[0]);
		*strrchr(szPath, '\\') = 0;
		sprintf_s(szCmd, "cmd /c cd \"%s\" & py generate_interactive_bom.py \"%s\"", szPath, openFile.lpstrFile);
		WinExec(szCmd, SW_HIDE);
	}
	return 0;
}
