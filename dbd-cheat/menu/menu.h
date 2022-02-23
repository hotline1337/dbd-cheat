#pragma once
#include <d3d11.h>
#include <dxgi.h>

#include "imgui/kiero.h"
#include "options.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

namespace menu
{
	inline Present oPresent;
	inline HWND window = NULL;
	inline WNDPROC oWndProc;
	inline ID3D11Device* pDevice = NULL;
	inline ID3D11DeviceContext* pContext = NULL;
	inline ID3D11RenderTargetView* mainRenderTargetView;

	inline bool init = false;
	inline bool opened = true;
	inline static int current_tab = 0;

	extern void initialize();
	extern LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	extern HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags, HMODULE hMod);
}
