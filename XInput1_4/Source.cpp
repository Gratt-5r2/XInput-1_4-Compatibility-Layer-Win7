#include <Windows.h>
#include <string>
#include <filesystem>


EXTERN_C_START
typedef DWORD (WINAPI* LPXInputGetStateProc )(DWORD, void*);
typedef DWORD (WINAPI* LPXInputSetStateProc )(DWORD, void*);
typedef DWORD (WINAPI* LPXInputGetCapabilitiesProc )(DWORD, DWORD, void*);
typedef void (WINAPI* LPXInputEnableProc )(BOOL);
typedef DWORD (WINAPI* LPXInputGetBatteryInformationProc )(DWORD, BYTE, void*);
typedef DWORD (WINAPI* LPXInputGetKeystrokeProc )(DWORD, DWORD, void*);
typedef DWORD (WINAPI* LPXInputGetAudioDeviceIdsProc )(DWORD, LPWSTR, UINT*, LPWSTR, UINT*);


struct XInput {
  HMODULE                           g_lpOriginalLibrary             = NULL;
  LPXInputGetStateProc              m_lpXInputGetState              = NULL;
  LPXInputSetStateProc              m_lpXInputSetState              = NULL;
  LPXInputGetCapabilitiesProc       m_lpXInputGetCapabilities       = NULL;
  LPXInputEnableProc                m_lpXInputEnable                = NULL;
  LPXInputGetBatteryInformationProc m_lpXInputGetBatteryInformation = NULL;
  LPXInputGetKeystrokeProc          m_lpXInputGetKeystroke          = NULL;
  LPXInputGetAudioDeviceIdsProc     m_lpXInputGetAudioDeviceIds     = NULL;

  static XInput& GetInstance() {
    static XInput* instance = new XInput();
    return *instance;
  }

private:
  bool LoadOriginalLibrary( std::string libraryName ) {
    char systemDirectory[MAX_PATH];
    auto systemDirectoryLength = GetSystemDirectory( systemDirectory, MAX_PATH );
    auto originalLibraryPath = std::filesystem::path( systemDirectory ) / libraryName;

    g_lpOriginalLibrary = LoadLibrary( originalLibraryPath.string().c_str());

    if( g_lpOriginalLibrary ) {
      m_lpXInputGetState              = (LPXInputGetStateProc)              GetProcAddress( g_lpOriginalLibrary, "XInputGetState" );
      m_lpXInputSetState              = (LPXInputSetStateProc)              GetProcAddress( g_lpOriginalLibrary, "XInputSetState" );
      m_lpXInputGetCapabilities       = (LPXInputGetCapabilitiesProc)       GetProcAddress( g_lpOriginalLibrary, "XInputGetCapabilities" );
      m_lpXInputEnable                = (LPXInputEnableProc)                GetProcAddress( g_lpOriginalLibrary, "XInputEnable" );
      m_lpXInputGetBatteryInformation = (LPXInputGetBatteryInformationProc) GetProcAddress( g_lpOriginalLibrary, "XInputGetBatteryInformation" );
      m_lpXInputGetKeystroke          = (LPXInputGetKeystrokeProc)          GetProcAddress( g_lpOriginalLibrary, "XInputGetKeystroke" );
      m_lpXInputGetAudioDeviceIds     = (LPXInputGetAudioDeviceIdsProc)     GetProcAddress( g_lpOriginalLibrary, "XInputGetAudioDeviceIds" );
    }
  }

  XInput() {
    std::string dllNameList[] = {
      "XInput1_4.dll",
      "XInput1_3.dll",
      "XInput1_2.dll",
      "XInput1_1.dll"
    };

    for( const auto& dllName : dllNameList )
      if( LoadOriginalLibrary( dllName ) )
        return;
  }
};


DWORD WINAPI XInputGetState( DWORD dwUserIndex, void* pState ) {
  return XInput::GetInstance().m_lpXInputGetState ?
    XInput::GetInstance().m_lpXInputGetState( dwUserIndex, pState ) :
    -1;
}

DWORD WINAPI XInputSetState( DWORD dwUserIndex, void* pVibration ) {
  return XInput::GetInstance().m_lpXInputSetState ?
    XInput::GetInstance().m_lpXInputSetState( dwUserIndex, pVibration ) :
    -1;
}

DWORD WINAPI XInputGetCapabilities( DWORD dwUserIndex, DWORD dwFlags, void* pCapabilities ) {
  return XInput::GetInstance().m_lpXInputGetCapabilities ?
    XInput::GetInstance().m_lpXInputGetCapabilities( dwUserIndex, dwFlags, pCapabilities ) :
    -1;
}

void WINAPI XInputEnable( BOOL enable ) {
  if( XInput::GetInstance().m_lpXInputEnable )
    XInput::GetInstance().m_lpXInputEnable( enable );
}

DWORD WINAPI XInputGetBatteryInformation( DWORD dwUserIndex, BYTE devType, void* pBatteryInformation ) {
  return XInput::GetInstance().m_lpXInputGetBatteryInformation ?
    XInput::GetInstance().m_lpXInputGetBatteryInformation( dwUserIndex, devType, pBatteryInformation ) :
    -1;
}

DWORD WINAPI XInputGetKeystroke( DWORD dwUserIndex, DWORD dwReserved, void* pKeystroke ) {
  return XInput::GetInstance().m_lpXInputGetKeystroke ?
    XInput::GetInstance().m_lpXInputGetKeystroke( dwUserIndex, dwReserved, pKeystroke ) :
    -1;
}

DWORD WINAPI XInputGetAudioDeviceIds( DWORD dwUserIndex, LPWSTR pRenderDeviceId, UINT* pRenderCount, LPWSTR pCaptureDeviceId, UINT* pCaptureCount ) {
  return XInput::GetInstance().m_lpXInputGetAudioDeviceIds ?
    XInput::GetInstance().m_lpXInputGetAudioDeviceIds( dwUserIndex, pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount ) :
    -1;
}
EXTERN_C_END