// doner.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "doner.h"
#include "Tools.h"
#include "data.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// ------------------some default----------------
int pageAt = 0;
//TCHAR buffer[MAX_PATH] = { 0 };
////GetModuleFileName(NULL, buffer, MAX_PATH);
//std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
//auto wpath = std::wstring(buffer).substr(0, pos);
//
////setup converter
//using convert_type = std::codecvt_utf8<wchar_t>;
//std::wstring_convert<convert_type, wchar_t> converter;
//
////use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
//std::string Path = converter.to_bytes(wpath);
////std::string Path(wpath.begin(), wpath.end());
//std::string demoLocation = Path.append("\\..\\..\\doner\\projects storage\\demo\\");
auto PathLoc = std::string(__FILE__).find_last_of("\\/");
auto Path = std::string(__FILE__).substr(0, PathLoc).append("\\..\\projects storage\\");
auto DefaultBackground = Path + "src\\defaultBackground.jpg";
//auto w_DefaultB = std::wstring(DefaultBackground.begin(), DefaultBackground.end()).c_str();


// game data
ImGuiIO& io = ImGui::GetIO();
data gameData = data(Path, io);


// the first one in this list is the background texture
std::vector<texture> textureList(20);

//
//Gdiplus::Bitmap* pBackgroundImage = nullptr;
//wchar_t szImagePath[MAX_PATH] = L"";
//
//HBITMAP g_hBackgroundBitmap = (HBITMAP)LoadImage(NULL, L"C:\\Users\\14631\\OneDrive\\Desktop\\DT\\New Folder\\drwwoob\\doner\\projects storage\\defaultBackrgound.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//bool a = (g_hBackgroundBitmap == NULL);


bool startVisual = false;
//int my_image_width = 0;
//int my_image_height = 0;
//ID3D11ShaderResourceView* my_texture = NULL;
//bool ret;


//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//    UNREFERENCED_PARAMETER(hPrevInstance);
//    UNREFERENCED_PARAMETER(lpCmdLine);
//
//    // TODO: Place code here.
//
//    // Initialize global strings
//    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//    LoadStringW(hInstance, IDC_DONER, szWindowClass, MAX_LOADSTRING);
//    MyRegisterClass(hInstance);
//
//    // Perform application initialization:
//    if (!InitInstance (hInstance, nCmdShow))
//    {
//        return FALSE;
//    }
//
//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DONER));
//
//    MSG msg;
//
//    // Main message loop:
//    while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }
//
//    return (int) msg.wParam;
//}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DONER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DONER);
    //wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // Parse the menu selections:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // TODO: Add any drawing code that uses hdc here...
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

// set the loading texture
//void setTexture() {
//    my_image_width = 0;
//    my_image_height = 0;
//    my_texture = NULL;
//    ret = Tools::LoadTextureFromFile(gameData.getPage(pageAt).backgroundName.c_str(), &my_texture, &my_image_width, &my_image_height);
//    IM_ASSERT(ret);
//}
//
//// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        switch (LOWORD((wParam))) {
//		case IDM_FILE_NEW:
//            break;
//		case IDM_FILE_OPEN:
//            break;
//	    case IDM_FILE_SAVE:
//            break;
//        case IDM_FILE_EXIT:
//            DestroyWindow(hDlg);
//        	break;
//    case IDM_SCENE_PAGE_NEXT:
//			pageAt += 1;
//
//            break;
//		default:
//            return DefWindowProc(hDlg, message, wParam, lParam);
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}


//from imgui examples 
// Data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();


// Helper functions
bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// //Function to paint the background image
//void PaintBackground(HWND hWnd, HDC hdc) {
//    if (g_hBackgroundBitmap != NULL) {
//        RECT clientRect;
//        GetClientRect(hWnd, &clientRect);
//        HDC hdcMem = CreateCompatibleDC(hdc);
//        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, g_hBackgroundBitmap);
//        StretchBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcMem, 0, 0, clientRect.right, clientRect.bottom, SRCCOPY);
//        SelectObject(hdcMem, hOldBitmap);
//        DeleteDC(hdcMem);
//    }
//}

//bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
//{
//    // Load from disk into a raw RGBA buffer
//    int image_width = 0;
//    int image_height = 0;
//    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
//    if (image_data == NULL)
//        return false;
//
//    // Create texture
//    D3D11_TEXTURE2D_DESC desc;
//    ZeroMemory(&desc, sizeof(desc));
//    desc.Width = image_width;
//    desc.Height = image_height;
//    desc.MipLevels = 1;
//    desc.ArraySize = 1;
//    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    desc.SampleDesc.Count = 1;
//    desc.Usage = D3D11_USAGE_DEFAULT;
//    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//    desc.CPUAccessFlags = 0;
//
//    ID3D11Texture2D* pTexture = NULL;
//    D3D11_SUBRESOURCE_DATA subResource;
//    subResource.pSysMem = image_data;
//    subResource.SysMemPitch = desc.Width * 4;
//    subResource.SysMemSlicePitch = 0;
//    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);
//
//    // Create texture view
//    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//    ZeroMemory(&srvDesc, sizeof(srvDesc));
//    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//    srvDesc.Texture2D.MipLevels = desc.MipLevels;
//    srvDesc.Texture2D.MostDetailedMip = 0;
//    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
//    pTexture->Release();
//
//    *out_width = image_width;
//    *out_height = image_height;
//    stbi_image_free(image_data);
//
//    return true;
//}



// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    //case WM_CREATE:
    //    // Load the background image
    //    //pBackgroundImage = new Gdiplus::Bitmap(L"background.jpg");
    //    break;

    //case WM_ERASEBKGND:
    //{
    //    // Draw the background image
    //    RECT clientRect;
    //    GetClientRect(hWnd, &clientRect);
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hWnd, &ps);
    //    Gdiplus::Graphics graphics(hdc);
    //    graphics.DrawImage(pBackgroundImage, 0, 0, clientRect.right, clientRect.bottom);
    //    EndPaint(hWnd, &ps);
    //    return TRUE; // Tell Windows that we've erased the background
    //}

    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_PAINT:
    {
        /*PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        PaintBackground(hWnd, hdc);
        EndPaint(hWnd, &ps);*/
    }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hWnd, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        switch (LOWORD((wParam))) {
        case IDM_FILE_NEW:
            gameData.newFile(&startVisual);
            break;
		case IDM_FILE_OPEN:
            break;
        case IDM_FILE_SAVE:
            gameData.save();
            break;
        case IDM_FILE_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_SCENE_PAGE_NEXT:
            pageAt += 1;

            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
        break;

    case WM_DESTROY:
       /* if (g_hBackgroundBitmap != NULL) {
            DeleteObject(g_hBackgroundBitmap);
        }*/
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

// Main code
//int main(int, char**)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    // for background
    // Initialize GDI+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, MAKEINTRESOURCEW(IDC_DONER), L"Doner", nullptr };
    wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    ::RegisterClassExW(&wc);

	LoadStringW(wc.hInstance, IDC_DONER, szWindowClass, MAX_LOADSTRING);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Doner", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext); 




    //--------------------initialize image texture--------------


    //if (background_name.empty()) {
    //    //ImGui::GetBackgroundDrawList()->
    //}
    //else {

	//int my_image_width = 0;
	//int my_image_height = 0;
	//ID3D11ShaderResourceView* my_texture = NULL;
	//bool ret = Tools::LoadTextureFromFile(background_name.c_str(), &my_texture, &my_image_width, &my_image_height);

	// ---------------------need to change------------------------
    // the follow code are for the background to show, name need to be change

    RECT rect;
    ImVec2 windowSize(1, 1);
    if (GetWindowRect(hwnd, &rect))
    {
        windowSize = ImVec2(rect.right - rect.left, rect.bottom - rect.top);
    }

	//bool ret = Page::LoadTextureFromFile(DefaultBackground.c_str(), &my_texture, &my_image_width, &my_image_height, g_pd3dDevice);
	//IM_ASSERT(ret);
	//ImGui::GetBackgroundDrawList()->AddImage((void*)my_texture,ImVec2(0, 0),
 //       windowSize, ImVec2(0, 0), ImVec2(1, 1));
	//ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
	//}


    // --------------------------get data info--------------------------------
    pageAt = gameData.leaveAt;
    // ------------------------- initial textureList--------------------
    // ----------------there's a limit of how many cast can be loaded now, maybe this could be dynamic in the future--------
    //std::fill(textureList.begin(), textureList.begin() + 20);
    //moved to the initiated place


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

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //-----------------------menu window--------------------------
    bool show_welcome_window = true;
    bool show_cast_window = true;
    bool view_data = false;


    // ------------------------Main loop--------------------------------
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;

			//// get the size
   //         windowSize = ImVec2(rect.right - rect.left, rect.bottom - rect.top);


            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();


        // ---------------testing center -------------------------
        //if(a) {
        //     ImGui::Begin("testing");
        //     ImGui::Text("%s", Path.c_str());
        //     ImGui::Text("%s", DefaultBackground.c_str());
        //     ImGui::Text("C:\\Users\\14631\\OneDrive\\Desktop\\DT\\New Folder\\drwwoob\\doner\\projects storage\\defaultBackrgound.jpg");
        //     //ImGui::Text("==%s", w_DefaultB);
        //     ImGui::End();
        //     //auto b = w_DefaultB;
        //}


        // -------------------welcoming scene ------------------
        if (show_welcome_window) {
            cast::showWelcomePage(&gameData, &show_welcome_window, &startVisual);
        }

        //// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        //----------------showing the page---------------------
        //gameData.getPage(pageAt).visualizePage();


        if (GetWindowRect(hwnd, &rect)) {
            windowSize = ImVec2(rect.right - rect.left, rect.bottom - rect.top);
        }


        if (startVisual) {
            gameData.visualizeData3(g_pd3dDevice, windowSize, &textureList);


            //gameData.vidualizeData2(LoadTextureFromFile);
            //gameData.visualizeData(hwnd, g_hBackgroundBitmap);

        }
        else {
            Page::showBackGround(DefaultBackground, windowSize, g_pd3dDevice, textureList.at(0).t, &textureList.at(0).w, &textureList.at(0).h);
        }


        //ImGui::GetBackgroundDrawList()->AddImage((void*)my_texture, ImVec2(0, 0), ImVec2(my_image_width, my_image_height), ImVec2(0, 0), ImVec2(1, 1));

        //-----------------creating modifying window-------------------
        if (show_cast_window)
            cast::showCastWindow(&show_cast_window, pageAt, gameData.getPage(pageAt), windowSize);



        //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        //{
        //    static float f = 0.0f;
        //    static int counter = 0;

        //    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        //    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //    ImGui::Checkbox("Another Window", &show_another_window);

        //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //        counter++;
        //    ImGui::SameLine();
        //    ImGui::Text("counter = %d", counter);

        //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        //    ImGui::End();
        //}

        // Rendering 
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync

    //clean up texture
        for (int i = 0; i < textureList.size(); i++) {
            if (textureList.at(i).t != nullptr)
            {
                textureList.at(i).t->Release();
                textureList.at(i).t = nullptr;
            }
        }
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    Gdiplus::GdiplusShutdown(gdiplusToken);


    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}
