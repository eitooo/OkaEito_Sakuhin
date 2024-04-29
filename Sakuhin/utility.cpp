#include    "utility.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

// 指定時間後にスレッドを起動
void Invoke(std::function<void()> Function, int Time)
{
    std::thread([=]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Time));
            //			Sleep(Time);
            Function();
        }).detach();
}

//--------------------------------------------------------------------------------------
// シェーダーファイルを読み込む
//--------------------------------------------------------------------------------------
bool readShader(const char* csoName, std::vector<unsigned char>& byteArray)
{
    FILE* fp;
    int ret = fopen_s(&fp, csoName, "rb");
    if (ret != 0) {
        return false;
    }

    fseek(fp, 0, SEEK_END);

    int size = ftell(fp);

    byteArray.resize(size);

    fseek(fp, 0, SEEK_SET);
    fread(byteArray.data(), byteArray.size(), 1, fp);

    fclose(fp);

    return true;
}

//--------------------------------------------------------------------------------------
// ファイルの拡張子を取得する
//--------------------------------------------------------------------------------------
std::string GetFileExt(const char* filename) {
    std::string extname;

    std::string fullpathstr(filename);
    size_t ext_i = fullpathstr.find_last_of(".");
    extname = fullpathstr.substr(ext_i + 1, fullpathstr.size() - ext_i);
    return extname;
}

//--------------------------------------------------------------------------------------
// シェーダーをコンパイル
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    ID3DBlob* p1 = nullptr;

    HRESULT hr = S_OK;

    WCHAR	filename[512];
    size_t 	wLen = 0;
    int err = 0;

    // char -> wcharに変換
    setlocale(LC_ALL, "japanese");
    err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(
        filename,							// filename LPCWST pFileName
        nullptr,							// D3D_SHADER_MACRO *pDefines
        D3D_COMPILE_STANDARD_FILE_INCLUDE,	// ID3DInclude *pInclude
        szEntryPoint,						// LPCSTR pEntrypoint
        szShaderModel,						// LPCSTR pTarget
        dwShaderFlags,						// UINT Flags1
        0,									// UINT Flags2
        ppBlobOut,							// ID3DBlob** ppCode
        &pErrorBlob);						// ID3DBlob** ppErrorMsg 
    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr) {
            MessageBoxW(NULL,
                L"", L"Error", MB_OK);
        }
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

/*------------------------
 Structuredバッファを作成
--------------------------*/
bool CreateStructuredBuffer(
    ID3D11Device* device,
    unsigned int stride,				// ストライドバイト数
    unsigned int num,					// 個数
    void* data,							// データ格納メモリ先頭アドレス
    ID3D11Buffer** pStructuredBuffer	// RWStructuredBuffer
) {

    HRESULT hr;

    // Structuredバッファ生成
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;		// UAバッファ
    bd.ByteWidth = stride * num;													// バッファの大きさ
    bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;							// RWStructuredBuffer
    bd.StructureByteStride = stride;												// 構造化バッファサイズ
    bd.CPUAccessFlags = 0;															// CPUアクセス不要

    if (data != nullptr) {
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));

        InitData.pSysMem = data;							// バッファの初期値

        hr = device->CreateBuffer(&bd, &InitData, pStructuredBuffer);		// バッファ生成
    }
    else {
        hr = device->CreateBuffer(&bd, nullptr, pStructuredBuffer);		    // バッファ生成
    }

    if (FAILED(hr)) {
        MessageBoxW(nullptr, L"CreateBuffer(StructuredBuffer) error", L"Error", MB_OK);
        return false;
    }

    return true;
}

/*------------------------
 Structuredバッファを作成
--------------------------*/
bool CreateStructuredBufferWrite(
    ID3D11Device* device,
    unsigned int stride,				// ストライドバイト数
    unsigned int num,					// 個数
    void* data,							// データ格納メモリ先頭アドレス
    ID3D11Buffer** pStructuredBuffer	// RWStructuredBuffer
) {

    HRESULT hr;

    // Structuredバッファ生成
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;					// UAバッファ
    bd.Usage = D3D11_USAGE_DYNAMIC;								// バッファ使用方法
    bd.ByteWidth = stride * num;								// バッファの大きさ
    bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;		// RWStructuredBuffer
    bd.StructureByteStride = stride;							// 構造化バッファサイズ
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;					// CPUアクセス不要

    if (data != nullptr) {
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));

        InitData.pSysMem = data;							// バッファの初期値

        hr = device->CreateBuffer(&bd, &InitData, pStructuredBuffer);		// バッファ生成
    }
    else {
        hr = device->CreateBuffer(&bd, nullptr, pStructuredBuffer);		// バッファ生成
    }
    if (FAILED(hr)) {
        MessageBoxW(nullptr, L"CreateBuffer(StructuredBuffer) error", L"Error", MB_OK);
        return false;
    }

    return true;
}

/*------------------------
    ShaderResourceViewを作成
--------------------------*/
bool CreateShaderResourceView(
    ID3D11Device* device,
    ID3D11Buffer* pBuffer,	// Buffer
    ID3D11ShaderResourceView** ppSRV) {

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    pBuffer->GetDesc(&bd);

    D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    srvDesc.BufferEx.FirstElement = 0;

    if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
        srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
        srvDesc.BufferEx.NumElements = bd.ByteWidth / 4;
    }
    else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
        srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        srvDesc.BufferEx.NumElements = bd.ByteWidth / bd.StructureByteStride;
    }
    else {
        return false;
    }

    HRESULT hr;
    hr = device->CreateShaderResourceView(pBuffer, &srvDesc, ppSRV);
    if (FAILED(hr)) {
        MessageBoxW(nullptr, L"CreateShaderResourceView error", L"Error", MB_OK);
        return false;
    }

    return true;
}

/*------------------------
UnOrderedAccessViewを作成
--------------------------*/
bool CreateUnOrderAccessView(
    ID3D11Device* device,
    ID3D11Buffer* pBuffer,	                    // Buffer
    ID3D11UnorderedAccessView** ppUAV) {

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    pBuffer->GetDesc(&bd);

    D3D11_UNORDERED_ACCESS_VIEW_DESC  uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;

    if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
        uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
        uavDesc.Buffer.NumElements = bd.ByteWidth / 4;
    }
    else if (bd.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
        uavDesc.Format = DXGI_FORMAT_UNKNOWN;
        uavDesc.Buffer.NumElements = bd.ByteWidth / bd.StructureByteStride;
    }
    else {
        return false;
    }

    HRESULT hr;
    hr = device->CreateUnorderedAccessView(pBuffer, &uavDesc, ppUAV);
    if (FAILED(hr)) {
        MessageBoxW(nullptr, L"CreateUnorderedAccessView error", L"Error", MB_OK);
        return false;
    }

    return true;
}

/*---------------------------------
STAGINGバッファを作成しコピーする
----------------------------------*/
ID3D11Buffer* CreateAndCopyToBuffer(
    ID3D11Device* device,
    ID3D11DeviceContext* devicecontext,
    ID3D11Buffer* pBuffer	// RWStructuredBuffer
) {

    HRESULT hr;
    ID3D11Buffer* CloneBuffer = nullptr;

    // Structuredバッファ生成
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    pBuffer->GetDesc(&bd);

    bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    bd.Usage = D3D11_USAGE_STAGING;
    bd.BindFlags = 0;
    bd.MiscFlags = 0;

    hr = device->CreateBuffer(&bd, nullptr, &CloneBuffer);
    if (SUCCEEDED(hr)) {
        devicecontext->CopyResource(CloneBuffer, pBuffer);
    }

    return CloneBuffer;
}

/*------------------------
頂点バッファを作成
--------------------------*/
bool CreateVertexBuffer(
    ID3D11Device* device,
    unsigned int stride,				// １頂点当たりバイト数
    unsigned int vertexnum,				// 頂点数
    void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
    ID3D11Buffer** pVertexBuffer		// 頂点バッファ
) {
    HRESULT hr;

    // 頂点バッファ生成
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;							// バッファ使用方法
    bd.ByteWidth = stride * vertexnum;						// バッファの大きさ
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファ

    bd.CPUAccessFlags = 0;									// CPUアクセス不要

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertexdata;							// バッファの初期値

    hr = device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// バッファ生成
    if (FAILED(hr)) {
        MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
        return false;
    }

    return true;
}

/*------------------------
頂点バッファを作成(ＣＰＵ書き込み可能)
--------------------------*/
bool CreateVertexBufferWrite(
    ID3D11Device* device,
    unsigned int stride,				// １頂点当たりバイト数
    unsigned int vertexnum,				// 頂点数
    void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
    ID3D11Buffer** pVertexBuffer		// 頂点バッファ
) {

    HRESULT hr;

    // 頂点バッファ生成
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;							// バッファ使用方法
    bd.ByteWidth = stride * vertexnum;						// バッファの大きさ
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファ
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				// CPUアクセス可能

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertexdata;							// バッファの初期値

    hr = device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// バッファ生成
    if (FAILED(hr)) {
        MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
        return false;
    }

    return true;
}

/*------------------------
頂点バッファ(UAV)を作成
--------------------------*/
bool CreateVertexBufferUAV(
    ID3D11Device* device,
    unsigned int stride,				// １頂点当たりバイト数
    unsigned int vertexnum,				// 頂点数
    void* vertexdata,					// 頂点データ格納メモリ先頭アドレス
    ID3D11Buffer** pVertexBuffer		// 頂点バッファ
) {

    HRESULT hr;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = stride * vertexnum;						// バッファの大きさ
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags =
        D3D11_BIND_VERTEX_BUFFER |
        D3D11_BIND_SHADER_RESOURCE |
        D3D11_BIND_UNORDERED_ACCESS;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertexdata;							// バッファの初期値

    hr = device->CreateBuffer(&bd, &InitData, pVertexBuffer);		// バッファ生成
    if (FAILED(hr)) {
        MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
        return false;
    }

    return true;
}

/*----------------------------
コンスタントバッファを作成(MAPで書き換え可能)
------------------------------*/
bool CreateConstantBufferWrite(
    ID3D11Device* device,					// デバイスオブジェクト
    unsigned int bytesize,					// コンスタントバッファサイズ
    ID3D11Buffer** pConstantBuffer			// コンスタントバッファ
) {

    // コンスタントバッファ生成
    D3D11_BUFFER_DESC bd;

    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;							// バッファ使用方法
    bd.ByteWidth = bytesize;									// バッファの大き
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;					// コンスタントバッファ
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;					// CPUアクセス可能

    HRESULT hr = device->CreateBuffer(&bd, nullptr, pConstantBuffer);
    if (FAILED(hr)) {
        MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
        return false;
    }

    return true;
}
