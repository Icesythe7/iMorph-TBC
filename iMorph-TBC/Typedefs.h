#pragma once
#include <cstdint>
#include <d3d9.h>

typedef HRESULT(WINAPI* oEndScene) (LPDIRECT3DDEVICE9);
typedef HRESULT(WINAPI* oReset) (LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
typedef int32_t(__thiscall* oUpdateDisplayInfo)(uintptr_t, int32_t, int32_t);
typedef int32_t(__thiscall* oUnknownTexture)(uintptr_t);
typedef int32_t(__thiscall* oOnMountDisplayChanged)(uintptr_t, int32_t);

inline oEndScene Od9EndScene = nullptr;
inline oReset Od9Reset = nullptr;
inline oUpdateDisplayInfo FpUpdateDisplayInfo = nullptr;
inline oUnknownTexture FpUnknownTexture = nullptr;
inline oOnMountDisplayChanged FpOnMountDisplayChanged = nullptr;