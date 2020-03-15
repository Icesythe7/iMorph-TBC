// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Menu.h"
#include <iostream>
#include "MinHook.h"
#include "Typedefs.h"
#include "Ruda-Bold.h"

HWND CHandle;
LONG_PTR OldWndProc;
bool ImGuiInitialized;
std::unique_ptr<Menu> CMenu;

int32_t __fastcall TrampOnMountDisplayChanged(const uintptr_t unit, LPVOID unUsed, const int32_t displayId)
{
	const bool onTaxy = GetDescriptor<int>(CMenu->player, UNIT_FIELD_FLAGS) >> 0x14 & 1;
	if (unit == CMenu->player && !onTaxy && displayId && CMenu->mog_data.mount_id)
		return FpOnMountDisplayChanged(unit, CMenu->mog_data.mount_id);
	return FpOnMountDisplayChanged(unit, displayId);
}

int32_t __fastcall TrampUpdateDisplayInfo(const uintptr_t unit, LPVOID unUsed, const int32_t arg, const int32_t arg2)
{
	if (CMenu->called_by_me) //Function called by iMorph
	{
		CMenu->called_by_me = false;
		return FpUpdateDisplayInfo(unit, arg, arg2);
	}

	if (!CMenu->called_by_me && unit == CMenu->player) //Function called by WoW for my player
	{
		if (CMenu->mog_data.class_id == 11 || CMenu->mog_data.class_id == 7)
		{
			if (!CMenu->mog_data.stay_human)
			{
				const auto form = GetValue<uint8_t>(unit, UNIT_FIELD_BYTES_2, 3);
				switch (form)
				{
					//9634
				case FORM_BEAR: //Bear
				case FORM_DIREBEAR:
					if (CMenu->mog_data.bear)
						SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.bear);
					break;
				case FORM_AQUA: //Aquatic
					if (CMenu->mog_data.aquatic)
						SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.aquatic);
					break;
				case FORM_CAT: // Cat
					if (CMenu->mog_data.cat)
						SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.cat);
					break;
				case FORM_TRAVEL: //Travel
					if (CMenu->mog_data.travel)
						SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.travel);
					break;
				case FORM_MOONKIN: //Moonkin
					if (CMenu->mog_data.moonkin)
						SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.moonkin);
					break;
				case FORM_TREE: //Tree
					if (CMenu->mog_data.tree)
						SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.tree);
					break;
				case FORM_FLIGHT: //Flight
				case FORM_FLIGHT_EPIC:
					SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.mount_id);
					break;
					//Shaman
				case FORM_GHOSTWOLF: //Ghost Wolf
					if (CMenu->mog_data.ghost_wolf)
						SetDescriptor(unit, UNIT_FIELD_DISPLAYID, CMenu->mog_data.ghost_wolf);
					break;
					//Warlock
				//case 22: //Metamorphosis
				//	//maybe later
				//	break;
				default: //Human
					//CMenu->mog_data.WriteModelPlayerData(CMenu->player);
					break;
				}
				return FpUpdateDisplayInfo(unit, arg, arg2);
			}
			return 0;
		}
		return 0;
	}
	return FpUpdateDisplayInfo(unit, arg, arg2);
}

int32_t __fastcall TrampUnknownTexture(const uintptr_t unit, LPVOID unUsed)
{
	if (unit == CMenu->player)
	{
		const auto ptr = reinterpret_cast<byte*>(GetPointerDescriptor(CMenu->player, UNIT_FIELD_BYTES_0));
		const auto origRaceId = ptr[0];
		const auto origGenderId = ptr[2];

		ptr[0] = CMenu->mog_data.race_id; //RaceToId[Races[ItemCurrentRace]];
		ptr[2] = CMenu->mog_data.gender; //ItemCurrentGender;

		const auto rval = FpUnknownTexture(unit);

		ptr[0] = origRaceId;
		ptr[2] = origGenderId;

		return rval;
	}

	return FpUnknownTexture(unit);
}

struct HandleData
{
	unsigned long process_id;
	HWND window_handle;
};

BOOL IsMainWindow(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == static_cast<HWND>(nullptr) && IsWindowVisible(handle);
}

HWND GetConsoleHwnd()
{
#define MY_BUFSIZE 1024
	char pszNewWindowTitle[MY_BUFSIZE];
	char pszOldWindowTitle[MY_BUFSIZE];

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	wsprintf(pszNewWindowTitle, "%d/%d", GetTickCount(), GetCurrentProcessId());
	SetConsoleTitle(pszNewWindowTitle);
	Sleep(40);
	wchar_t wtext[MY_BUFSIZE + 1];
	size_t outSize;
	mbstowcs_s(&outSize, wtext, pszNewWindowTitle, strlen(pszNewWindowTitle) + 1);
	const auto hwndFound = FindWindowW(nullptr, wtext);
	SetConsoleTitle(pszOldWindowTitle);

	return hwndFound;
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	auto& data = *reinterpret_cast<HandleData*>(lParam);
	unsigned long processId = 0;
	GetWindowThreadProcessId(handle, &processId);
	if (data.process_id != processId || !IsMainWindow(handle) || handle == GetConsoleHwnd())
		return TRUE;
	data.window_handle = handle;
	return FALSE;
}

HWND FindMainWindow(const unsigned long processId)
{
	HandleData data;  // NOLINT(cppcoreguidelines-pro-type-member-init, hicpp-member-init)
	data.process_id = processId;
	data.window_handle = nullptr;
	EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&data));
	return data.window_handle;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NewWndProc(HWND hwnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	if (ImGuiInitialized)
	{
		if (message == WM_KEYUP && wParam == VK_F5) //working
			CMenu->menu_visible = !CMenu->menu_visible;

		if (CMenu->menu_visible)
		{
			ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam);
			auto& io = ImGui::GetIO();
			if (io.WantCaptureKeyboard || io.WantCaptureMouse)
				return true;
		}
	}

	return CallWindowProc(reinterpret_cast<WNDPROC>(OldWndProc), hwnd, message, wParam, lParam);
}

HRESULT WINAPI LocalReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto hr = Od9Reset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();
	return hr;
}


HRESULT WINAPI LocalEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ImGuiInitialized)
	{
		CHandle = FindMainWindow(GetCurrentProcessId());
		OldWndProc = SetWindowLongPtr(CHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NewWndProc));

		//Version
		IMGUI_CHECKVERSION();
		//Context
		ImGui::CreateContext();
		//IO
		auto& io = ImGui::GetIO();
		io.DeltaTime = 1.0f / 60.0f;
		//Font
		io.Fonts->AddFontFromMemoryCompressedTTF(&ruda_bold_compressed_data, ruda_bold_compressed_size, 14.0f);
		
		//Window Size
		ImGui_ImplWin32_Init(CHandle);
		//D3D Device
		ImGui_ImplDX9_Init(pDevice);
		//Style
		auto style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		//style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
		style->Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.23f, 0.29f, 0.70f);

		ImGuiInitialized = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	//Menu
	CMenu->Update();
	CMenu->RenderMenu();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return Od9EndScene(pDevice);
}

DWORD WINAPI Initialize(LPVOID param)
{
#if _DEBUG
    AllocConsole();
    SetConsoleTitle("iMorph - TBC Debug Console");
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
#endif

	CMenu = std::make_unique<Menu>();

    if (init(kiero::RenderType::D3D9) == kiero::Status::Success && kiero::bind(42, reinterpret_cast<void**>(&Od9EndScene), static_cast<void*>(LocalEndScene)) == kiero::Status::Success && kiero::bind(16, reinterpret_cast<void**>(&Od9Reset), static_cast<void*>(LocalReset)) == kiero::Status::Success)
	{
		if (MH_CreateHook(reinterpret_cast<LPVOID>(FnUpdateDisplayInfo), &TrampUpdateDisplayInfo, reinterpret_cast<LPVOID*>(&FpUpdateDisplayInfo)) == MH_OK)
			MH_EnableHook(reinterpret_cast<LPVOID>(FnUpdateDisplayInfo));

		if (MH_CreateHook(reinterpret_cast<LPVOID>(FnUnknownTexture), &TrampUnknownTexture, reinterpret_cast<LPVOID*>(&FpUnknownTexture)) == MH_OK)
			MH_EnableHook(reinterpret_cast<LPVOID>(FnUnknownTexture));

		if (MH_CreateHook(reinterpret_cast<LPVOID>(FnOnMountDisplayChanged), &TrampOnMountDisplayChanged, reinterpret_cast<LPVOID*>(&FpOnMountDisplayChanged)) == MH_OK)
			MH_EnableHook(reinterpret_cast<LPVOID>(FnOnMountDisplayChanged));

        while (1 & !GetAsyncKeyState(VK_F4))
            Sleep(1);
    }

#if _DEBUG
    const auto conHandle = GetConsoleWindow();
    FreeConsole();
    PostMessage(conHandle, WM_CLOSE, 0, 0);
#endif
    SetWindowLongPtr(CHandle, GWLP_WNDPROC, OldWndProc);
    ImGui_ImplWin32_Shutdown();
	MH_DisableHook(reinterpret_cast<LPVOID>(FnUpdateDisplayInfo));
	MH_DisableHook(reinterpret_cast<LPVOID>(FnUnknownTexture));
	MH_DisableHook(reinterpret_cast<LPVOID>(FnOnMountDisplayChanged));
    kiero::shutdown();
    FreeLibraryAndExitThread(static_cast<HMODULE>(param), NULL);
}

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD ul_reason_for_call, LPVOID lpReserved)
{
    DisableThreadLibraryCalls(hModule);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialize), hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    default:
        break;
    }
    return TRUE;
}