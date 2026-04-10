#include "pch.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <thread>

// Dependencies
#include "Libs/kiero/kiero.h"
#include "Libs/ImGui/imgui.h"
#include "Libs/ImGui/backends/imgui_impl_dx11.h"
#include "Libs/ImGui/backends/imgui_impl_win32.h"
#include "Libs/Fonts/FontData.h"
#include "Utils/Logger.hpp"

// Render
#include "Render/Render.h"


typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

// Globals
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;

bool ShowMenu = true;
bool init = false;

// Hook WndProc untuk handling input mouse/keyboard agar tidak tembus ke game
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Toggle Menu dengan tombol DELETE
    if (uMsg == WM_KEYUP && wParam == VK_DELETE)
        ShowMenu = !ShowMenu;

    if (ShowMenu)
    {
        // Berikan input ke ImGui
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        // Blocking input ke game jika mouse/keyboard sedang digunakan di menu
        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureMouse && (uMsg >= WM_MOUSEFIRST && uMsg <= WM_MOUSELAST))
            return true;
        if (io.WantCaptureKeyboard && (uMsg >= WM_KEYFIRST && uMsg <= WM_KEYLAST))
            return true;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;

            // Create Render Target
            ID3D11Texture2D* pBackBuffer = nullptr;
            HRESULT hrGetBuffer = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            if (FAILED(hrGetBuffer) || pBackBuffer == nullptr)
            {
                // Failed to get back buffer; abort init and call original Present
                if (pBackBuffer)
                    pBackBuffer->Release();
                return oPresent(pSwapChain, SyncInterval, Flags);
            }

            HRESULT hrRTV = pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            // Release the backbuffer after creating RTV regardless of success
            pBackBuffer->Release();
            if (FAILED(hrRTV) || mainRenderTargetView == nullptr)
            {
                // RTV creation failed; abort init and call original Present
                return oPresent(pSwapChain, SyncInterval, Flags);
            }

            // Hook Window Procedure
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            // --- IMGUI INIT ---
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.IniFilename = NULL;

            io.Fonts->AddFontFromMemoryTTF((void*)Montserrat, sizeof(Montserrat), 16.0f);

            ImGui_ImplWin32_Init(window);
            ImGui_ImplDX11_Init(pDevice, pContext);

            init = true;
        }
        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (ShowMenu)
    {
        Noellum::Render::RenderUI();
    }
    else
    {
        ImGui::GetIO().MouseDrawCursor = false;
    }

    // Render ESP overlay (always visible regardless of menu state)

    // Rendering
    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    Utils::Logger::Log("Noellum Module Injected!", "INFO");
    Utils::Logger::Log("Using C++20 Standard in Lab PC", "INFO");
    bool InitHook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            InitHook = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while (!InitHook);

    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
        break;
    }
    return TRUE;
}