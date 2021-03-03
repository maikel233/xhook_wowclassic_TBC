// DllMain.cpp : Defines the exported functions for the DLL application.

#include "Radar.h"
#include "EntityList.h"
#include "Camera.h"
#include "DllMain.h"
// Detours imports
#include "detours.h"
// DX11 imports
#include <D3D11.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "detours.lib")
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
// D3X HOOK DEFINITIONS
typedef HRESULT(__fastcall *IDXGISwapChainPresent)(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall *ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
// Definition of WndProc Hook. Its here to avoid dragging dependencies on <windows.h> types.

// Main D3D11 Objects
ID3D11DeviceContext *pContext = NULL;
ID3D11Device *pDevice = NULL;
ID3D11RenderTargetView *mainRenderTargetView;
static IDXGISwapChain*  pSwapChain = NULL;
static WNDPROC OriginalWndProcHandler = nullptr;
HWND window = nullptr;
IDXGISwapChainPresent fnIDXGISwapChainPresent;
DWORD_PTR* pDeviceContextVTable = NULL;
ID3D11DrawIndexed fnID3D11DrawIndexed;
// Boolean
BOOL g_bInitialised = false;
bool g_ShowMenu = false;
bool g_PresentHooked = false;
//imgui
ColorVar Settings::UI::accentColor = ImColor(43, 115, 178, 74);  //    |-»
ColorVar Settings::UI::mainColor = ImColor(46, 133, 200, 255);
ColorVar Settings::UI::bodyColor = ImColor(28, 33, 32, 228);
ColorVar Settings::UI::fontColor = ImColor(255, 255, 255, 255);

namespace ImGui
{

	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	inline bool Combo(const char* label, int* currIndex, std::vector<std::string>& values) {
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	inline bool
		ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height_in_items = -1) {
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size(), height_in_items);
	}

	class Tab
	{
	private:

		std::vector<std::string> labels;

	public:

		void add(std::string name)
		{
			labels.push_back(name);
		}

		void draw(int* selected)
		{
			ImGuiStyle& style = GetStyle();
			ImVec4 color = style.Colors[ImGuiCol_Button];
			ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
			ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
			ImVec2 max = GetContentRegionMax();
			float size_x = max.x / labels.size() - 20.f;
			float size_y = max.y / labels.size() - 40.f;

			for (size_t i = 0; i < labels.size(); i++)
			{
				if (i == *selected)
				{
					style.Colors[ImGuiCol_Button] = colorActive;
					style.Colors[ImGuiCol_ButtonActive] = colorActive;
					style.Colors[ImGuiCol_ButtonHovered] = colorActive;
				}
				else
				{
					style.Colors[ImGuiCol_Button] = color;
					style.Colors[ImGuiCol_ButtonActive] = colorActive;
					style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				}

				if (Button(labels.at(i).c_str(), { size_x, size_y }))
					*selected = i;

				/*if (i != labels.size() - 1)
				SameLine();*/
			}

			style.Colors[ImGuiCol_Button] = color;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		}
	};
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ImGui::GetIO();
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(window, &mPos);
	ImGui::GetIO().MousePos.x = mPos.x;
	ImGui::GetIO().MousePos.y = mPos.y;

	if (uMsg == WM_KEYUP)
	{
		if (wParam == VK_INSERT)
		{
			g_ShowMenu = !g_ShowMenu;

			if (g_ShowMenu)
				io.MouseDrawCursor = true;
			else
				io.MouseDrawCursor = false;
		}
	}

	if (g_ShowMenu)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

		return true;
	}
	return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
}

void __stdcall hookD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	fnID3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain *pSwapChain, ID3D11Device **ppDevice, ID3D11DeviceContext **ppContext)
{
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}

HRESULT __fastcall Present(IDXGISwapChain *pChain, UINT SyncInterval, UINT Flags)
{
	if (!g_bInitialised) {
		g_PresentHooked = true;
		std::cout << "\t[+] Present Hook called by first time" << std::endl;
		if (FAILED(GetDeviceAndCtxFromSwapchain(pChain, &pDevice, &pContext)))
			return fnIDXGISwapChainPresent(pChain, SyncInterval, Flags);
		pSwapChain = pChain;
		DXGI_SWAP_CHAIN_DESC sd;

		pChain->GetDesc(&sd);
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		window = sd.OutputWindow;

		//Set OriginalWndProcHandler to the Address of the Original WndProc function
		OriginalWndProcHandler = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)hWndProc);

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
		ImGui::GetIO().ImeWindowHandle = window;


		
		ID3D11Texture2D* pBackBuffer;

		pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
		pBackBuffer->Release();

		g_bInitialised = true;
	}


	ImGui_ImplWin32_NewFrame();
	//Draw::Renderer::Pointer()->Initialize();
	ImGui_ImplDX11_NewFrame();


	ImGui::NewFrame();

	static ImGuiStyle* style = &ImGui::GetStyle();

	static bool Executeonce;
	if (!Executeonce)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		ImVec4 mainColorHovered = ImVec4(Settings::UI::mainColor.Color().Value.x + 0.1f, Settings::UI::mainColor.Color().Value.y + 0.1f, Settings::UI::mainColor.Color().Value.z + 0.1f, Settings::UI::mainColor.Color().Value.w);
		ImVec4 mainColorActive = ImVec4(Settings::UI::mainColor.Color().Value.x + 0.2f, Settings::UI::mainColor.Color().Value.y + 0.2f, Settings::UI::mainColor.Color().Value.z + 0.2f, Settings::UI::mainColor.Color().Value.w);
		ImVec4 menubarColor = ImVec4(Settings::UI::bodyColor.Color().Value.x, Settings::UI::bodyColor.Color().Value.y, Settings::UI::bodyColor.Color().Value.z, Settings::UI::bodyColor.Color().Value.w - 0.8f);
		ImVec4 frameBgColor = ImVec4(Settings::UI::bodyColor.Color().Value.x, Settings::UI::bodyColor.Color().Value.y, Settings::UI::bodyColor.Color().Value.z, Settings::UI::bodyColor.Color().Value.w + .1f);
		ImVec4 tooltipBgColor = ImVec4(Settings::UI::bodyColor.Color().Value.x, Settings::UI::bodyColor.Color().Value.y, Settings::UI::bodyColor.Color().Value.z, Settings::UI::bodyColor.Color().Value.w + .05f);

		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2(8, 8);
		style.WindowMinSize = ImVec2(32, 32);
		style.WindowRounding = 3.0f;
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.FramePadding = ImVec2(4, 3);
		style.FrameRounding = 2.0f;
		style.ItemSpacing = ImVec2(8, 4);
		style.ItemInnerSpacing = ImVec2(4, 4);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 3.0f;
		style.ScrollbarSize = 12.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 2.0f;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.DisplayWindowPadding = ImVec2(22, 22);
		style.DisplaySafeAreaPadding = ImVec2(4, 4);
		style.AntiAliasedLines = true;
		style.CurveTessellationTol = 1.25f;

		style.Colors[ImGuiCol_Text] = Settings::UI::fontColor.Color();
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = Settings::UI::bodyColor.Color();
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(.0f, .0f, .0f, .0f);
		style.Colors[ImGuiCol_PopupBg] = tooltipBgColor;
		style.Colors[ImGuiCol_Border] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = frameBgColor;
		style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
		style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
		style.Colors[ImGuiCol_TitleBg] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w);
		style.Colors[ImGuiCol_ScrollbarGrab] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_Separator] = mainColorActive;
		style.Colors[ImGuiCol_CheckMark] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
		style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_Button] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
		style.Colors[ImGuiCol_Header] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
		style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
		style.Colors[ImGuiCol_Column] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGrip] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
		style.Colors[ImGuiCol_PlotLines] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
		style.Colors[ImGuiCol_PlotHistogram] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorHovered;
		style.Colors[ImGuiCol_TextSelectedBg] = mainColorHovered;
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);
	//	Executeonce = true; // If you want static colors
	}

	Radar::RenderWindow();
	ShowEntityList::RenderWindow();

	if (g_ShowMenu) {
		ImGui::GetIO().MouseDrawCursor = 1;
		Configs::RenderWindow();
		GMenu::Menu(g_ShowMenu);
	}

	else { ImGui::GetIO().MouseDrawCursor = 0; }

	Draw::Renderer::Pointer()->BeginScene(); 
	////Draw in EndScene.
	Draw::Renderer::Pointer()->EndScene(); 

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return fnIDXGISwapChainPresent(pChain, SyncInterval, Flags);
}

void detourDirectXPresent()
{
	std::cout << "[+] Calling fnIDXGISwapChainPresent Detour" << std::endl;
	DetourTransactionBegin();
	std::cout << "Poszlo detour transaction\n";
	DetourUpdateThread(GetCurrentThread());
	std::cout << "Poszlo update thread\n";
	// Detours the original fnIDXGISwapChainPresent with our Present
	DetourAttach(&(LPVOID&)fnIDXGISwapChainPresent, (PBYTE)Present);
	std::cout << "Poszedl attach\n";
	DetourTransactionCommit();
}

void detourDirectXDrawIndexed()
{
	std::cout << "[+] Calling fnID3D11DrawIndexed Detour" << std::endl;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	// Detours the original fnIDXGISwapChainPresent with our Present fnID3D11DrawIndexed, (PBYTE)hookD3D11DrawIndexed
	DetourAttach(&(LPVOID&)fnID3D11DrawIndexed, (PBYTE)hookD3D11DrawIndexed);
	DetourTransactionCommit();
}

void retrieveValues()
{
	DWORD_PTR hDxgi = (DWORD_PTR)GetModuleHandle("dxgi.dll");
	#if defined(ENV64BIT)
		fnIDXGISwapChainPresent = (IDXGISwapChainPresent)((DWORD_PTR)hDxgi + 0x5070);
	#elif defined (ENV32BIT)
		fnIDXGISwapChainPresent = (IDXGISwapChainPresent)((DWORD_PTR)hDxgi + 0x10230);
	#endif
	std::cout << "[+] Present Addr: " << std::hex << fnIDXGISwapChainPresent << " test test test" << std::endl;
}

void printValues()
{
	std::cout << "[+] ID3D11DeviceContext Addr: " << std::hex << pContext << std::endl;
	std::cout << "[+] ID3D11Device Addr: " << std::hex << pDevice << std::endl;
	std::cout << "[+] ID3D11RenderTargetView Addr: " << std::hex << mainRenderTargetView << std::endl;
	std::cout << "[+] IDXGISwapChain Addr: " << std::hex << pSwapChain << std::endl;		
}

LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }

void GetPresent()
{
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 2;
	sd.BufferDesc.Height = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	D3D_FEATURE_LEVEL FeatureLevelsRequested = D3D_FEATURE_LEVEL_11_0;
	UINT numFeatureLevelsRequested = 1;
	D3D_FEATURE_LEVEL FeatureLevelsSupported;
	HRESULT hr;
	IDXGISwapChain *swapchain = 0;
	ID3D11Device *dev = 0;
	ID3D11DeviceContext *devcon = 0;
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&FeatureLevelsRequested,
		numFeatureLevelsRequested,
		D3D11_SDK_VERSION,
		&sd,
		&swapchain,
		&dev,
		&FeatureLevelsSupported,
		&devcon)))
	{
		std::cout << "[-] Failed to hook Present with VT method." << std::endl;
		return;
	}
	DWORD_PTR* pSwapChainVtable = NULL;
	pSwapChainVtable = (DWORD_PTR*)swapchain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	fnIDXGISwapChainPresent = (IDXGISwapChainPresent)(DWORD_PTR)pSwapChainVtable[8];
	g_PresentHooked = true;
	std::cout << "[+] Present Addr:" << fnIDXGISwapChainPresent << std::endl;
	Sleep(2000);
}

void * SwapChain[18];
void * Device[40];
void * Context[108];


//SlowFall, NoFallDmg & Unlimited jumps
void FreezeJump()
{

	if (!Settings::Hacks::Movement::JumpState)
		return;
			
		float ZAxis = LuaScript::ActivePlayer->GetUnitPosition().z;

		if (Settings::Hacks::Movement::SuperSlowFall)
		{
			Sleep(20); // Some users will dc on 20ms try a higher number but this will decrease your in air time. I should probably check in jump state + max jump alt?
			LuaScript::ActivePlayer->StopFall = 824;		
			return;
		}

		  if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		  {
			  Sleep(50); 
	
			  if (LuaScript::ActivePlayer->GetUnitPosition().z == ZAxis)
				  return;

			  if (LuaScript::ActivePlayer->GetUnitPosition().z != ZAxis)
			  {
				  Sleep(600); 
				  LuaScript::ActivePlayer->StopFall = 824;
			  }
		  }
	  
}

void ModifyJumpHeight()
{
	//Useless dc at jump...
	if (!Settings::Hacks::Movement::JumpStatev2)
		return;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		LuaScript::ActivePlayer->JumpHeight = Settings::Hacks::Movement::jumpHeight;
	}
}

void C2M_Test(bool Go, Vector3 destination)
{
	if (!Go)
		return;

	WObject* LocalPlayer = LuaScript::ActivePlayer;

	//Vector destination = Unit->GetUnitPosition();
	GameMethods::ClickToMove(LocalPlayer->Ptr(), destination);
	
	LuaScript::SetHardwareEvent();
}
namespace WoW
{
	bool Funcs::IsGhost(Vector3 Corpse)
	{
		if (Corpse.x != 0 || Corpse.y != 0 || Corpse.z != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Funcs::IsEntityAlive(WObject* entity)
	{
		int TypeID = entity->GetType();

		if (TypeID == CGPlayer || TypeID == CGUnit || TypeID == CGActivePlayer)
		{
			if (entity->sUnitField->Health > 0)
				return false;
		}
		return true;
	}

	bool Funcs::InRangeOf(WObject* Entity, const Vector3& v, float distance)
	{
		return Entity->GetUnitPosition().Distance(v) <= distance;
	}

	void Funcs::ReleaseSpirit()
	{
		GameMethods::Execute("RepopMe()");

	}

	void Funcs::ReviveAtCorpse()
	{
		GameMethods::Execute("RetrieveCorpse()");
	}
}

void StartQualityOfLife()
{

	if (!Settings::Hacks::Movement::CTM)
		return;

	if (!LuaScript::ActivePlayer)
		return;

	__try
	{
		WObject* LocalPlayer = (WObject*)LuaScript::ActivePlayer;


		if (WoW::Funcs::IsEntityAlive(LocalPlayer))
		{
			Sleep(1250);	
			printf("[+] Releasing Spirit!\n");
			WoW::Funcs::ReleaseSpirit(); //Spamming this will crash your game.
		}


		Vector3 Corpse;
		Corpse.x = *reinterpret_cast<float*>(Offsets::Base + 0x21F67B0);
		Corpse.y = *reinterpret_cast<float*>(Offsets::Base + 0x21F67B4);
		Corpse.z = *reinterpret_cast<float*>(Offsets::Base + 0x21F67B8);
		if (Corpse.x != 0 && Corpse.y != 0 && Corpse.z != 0)
		{
			if (WoW::Funcs::IsGhost(Corpse))
			{
				if (WoW::Funcs::InRangeOf(LocalPlayer, Corpse, 20.0))
				{
					Sleep(1250);
					printf("[+] Reviving!\n");
					WoW::Funcs::ReviveAtCorpse();
					C2M_Test(false, Corpse);
				}
				else
				{
					printf("[+] Walking to Corpse\n");
					C2M_Test(true, Corpse);
				}
			}
		}
		else
		{
			//Continue...
		}
	}
	__except (Utils::filterException(GetExceptionCode(), GetExceptionInformation())) {
		printf("[!] Auto Mode Exception Caught!\n");
		LuaScript::ReInitObjMgr(true);
	}
}

void GExecute_IGFunctions()
{
	static bool once;

	if (!GameMethods::ObjMgrIsValid(0))
		return;

	FreezeJump();
	ModifyJumpHeight();
	StartQualityOfLife();
	//C2M_Test();

	if (Settings::Hacks::Movement::TogglePlayerState) {
		once = true;


		if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Ground)
			LuaScript::ActivePlayer->Collision_StateHack = 0x3F8000003FEE38E4;								//Yes
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Swimming)
			LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_SWIMMING;			//Yes
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::UnderWaterWalking)
			LuaScript::ActivePlayer->Collision_StateHack = 0x15DDDBE549C238E4;								//Yes
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::WaterWalking)
			LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_WATERWALKING;		//Disconnect
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::FallingSlow)
			LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_FALLING_SLOW;		//Nope
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::CanFly)
			LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_CAN_FLY;				//Nope
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::DisableCollision)
			LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_DISABLE_COLLISION; // Nope
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Root)
			LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_ROOT;
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::Loggedoff)
			LuaScript::ActivePlayer->Collision_StateHack = 0x00000C;
		else if (Settings::Hacks::Movement::CurrentPlayerState == PlayerState::DisableGravity)
			LuaScript::ActivePlayer->Collision_StateHack = MovementFlags::MOVEMENTFLAG_DISABLE_GRAVITY; } // Nope

	else {
		if (once)
			LuaScript::ActivePlayer->Collision_StateHack = 0x3F8000003FEE38E4; // Walking state
			once = false;
		 }
}

void LoopFuncs()
{
	while (true)
	{ if (Settings::Objectmanager::ObjMgrisdone) {
			GExecute_IGFunctions(); } }
}

void ConsoleSetup()
{
	// With this trick we'll be able to print content to the console, and if we have luck we could get information printed by the game.
	AllocConsole();
	SetConsoleTitle("[+] XHOOK");
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
}

int WINAPI main()
{
	ConsoleSetup();
	GetPresent();

	// If GetPresent failed we have this backup method to get Present Address
	if (!g_PresentHooked) {
		std::cout << "Waiting...\n";
		retrieveValues();
	}

	// After this call, Present should be hooked and controlled by me.
	detourDirectXPresent();
	while (!g_bInitialised) {
		Sleep(1000);
	}

	printValues();

	std::cout << "[+] pDeviceContextVTable0 Addr: " << std::hex << pContext << std::endl;
	pDeviceContextVTable = (DWORD_PTR*)pContext;
	std::cout << "[+] pDeviceContextVTable1 Addr: " << std::hex << pDeviceContextVTable << std::endl;
	pDeviceContextVTable = (DWORD_PTR*)pDeviceContextVTable[0];
	std::cout << "[+] pDeviceContextVTable2 Addr: " << std::hex << pDeviceContextVTable << std::endl;
	//fnID3D11DrawIndexed
	fnID3D11DrawIndexed = (ID3D11DrawIndexed)pDeviceContextVTable[12];

	std::cout << "[+] pDeviceContextVTable Addr: " << std::hex << pDeviceContextVTable << std::endl;
	std::cout << "[+] fnID3D11DrawIndexed Addr: " << std::hex << fnID3D11DrawIndexed << std::endl;
	//detourDirectXDrawIndexed();

	//Execute our WoW Funcs
	LoopFuncs();

	Sleep(4000);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

