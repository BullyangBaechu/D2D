#include "pch.h"
#include "ImGuiMgr.h"

// external ���� �ʿ� �ִ� Engine ���� �� �� �ִ� ��� ���� �������
#include <Engine/Engine.h>
#include <Engine/Device.h>
#include <Engine/KeyMgr.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "EUI.h"


void ImGui::ShowDemoWindow(bool* p_open);

ImGuiMgr::ImGuiMgr()
    : m_ShowDemo(false)
{

}

ImGuiMgr::~ImGuiMgr()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    for (const auto& pair : m_mapUI)
    {
        delete pair.second;
    }
}

void ImGuiMgr::Init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    //io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    // imgui�� ����ϱ� ���� ������ �ڵ� ���� �־������
    ImGui_ImplWin32_Init(Engine::GetInst()->GetMainWnd());
    // �⺻������ ImGui�� comPtr �� �Ἥ .get()���� ȣ���ؾ���
    ImGui_ImplDX11_Init(DEVICE.Get(), CONTEXT.Get());

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    CreateEditorUI();
}

void ImGuiMgr::Progress()
{
    Tick();

    Render();
}

void ImGuiMgr::Tick()
{
    if (KEY_TAP(KEY::F9))
    {
        m_ShowDemo = !m_ShowDemo;
    }

    // �� �����Ӹ��� UI �� Tick �� ȣ���Ѵ�
    for (const auto& pair : m_mapUI)
    {
        pair.second->Tick();
    }
}



void ImGuiMgr::Render()
{
    // ==========================
    // Start the Dear ImGui frame
    // ==========================
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // ==================
    // RenderUpdate
    // �������� UI �� ���縦 Ȯ���Ѵ�(Begin -> End �� �Ѽ�Ʈ)
    // ==================
    

    // ���÷� ������
    static bool bOpen = true;

    // ui â On/Off �۵� ��� ����
    if (bOpen)
    {
        ImGui::Begin("Test Window", &bOpen);
        ImGui::Button("Sample Button");
        ImGui::End();
    }
   
     
    
    // Demo Window Widget
    if(m_ShowDemo)
        ImGui::ShowDemoWindow(&m_ShowDemo);

    // �� �����Ӹ��� UI ���� ȭ�鿡 �׸���.
    for (const auto& pair : m_mapUI)
    {
        if(pair.second->IsActive())
            pair.second->Render();
    }

    // ===========================
    // Rendering
    // Ȯ�ε� UI ���� ȭ�鿡 �׸���.
    // ===========================
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // ��, ImGui â�� ���� ������ â ������ ����� ���ο� ������, ����Ÿ��, �������� �����ȴٴ� ��
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}



#include "Inspector.h"

void ImGuiMgr::CreateEditorUI()
{
    EUI* pUI = nullptr;

    pUI = new Inspector;
    m_mapUI.insert(make_pair(pUI->GetName(), pUI));
}
