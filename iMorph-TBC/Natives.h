#pragma once
#include "pch.h"
#include <algorithm>
#include <regex>

inline auto ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
inline uintptr_t OfInGame = 0xC6DC1B;
inline uintptr_t FnPlayLevelUpAnimation = 0x614DE0;
inline uintptr_t FnGetBaseFromToken = 0x541EA0;
inline uintptr_t FnUpdateDisplayInfo = 0x622520;
inline uintptr_t FnFrameScriptExecute = 0x706C80;
inline uintptr_t FnFrameScriptGetText = 0x707200;
inline uintptr_t FnUnknownTexture = 0x618970;
inline uintptr_t FnOnMountDisplayChanged = 0x6222E0;

inline std::vector<std::string> Split(const std::string& input, const std::string& regex)
{
	// passing -1 as the submatch index parameter performs splitting
	const std::regex re(regex);
	const std::sregex_token_iterator first{ input.begin(), input.end(), re, -1 };
	const std::sregex_token_iterator last;
	return {first, last};
}

inline uintptr_t GetPointerDescriptor(const uintptr_t address, const int32_t offset)
{
	const auto descriptor = *reinterpret_cast<uintptr_t*>(address + 8);
	return descriptor + offset * 4;
}

template <typename T>
T GetAbsoluteDescriptor(const uintptr_t address, const int32_t offset)
{
	const auto descriptor = *reinterpret_cast<uintptr_t*>(address + 8);
	return *reinterpret_cast<T*>(descriptor + offset);
}

template <typename T>
T GetDescriptor(const uintptr_t address, const int32_t i)
{
	return GetAbsoluteDescriptor<T>(address, i * 4);
}

template <typename T>
bool SetAbsoluteDescriptor(const uintptr_t address, const int32_t offset, T value)
{
	const auto descriptor = *reinterpret_cast<uintptr_t*>(address + 8);
	return *reinterpret_cast<T*>(descriptor + offset) = value;
}

template <typename T> //convert project to this at some point
T GetValue(const uintptr_t address, const uint16_t descIndex, const uint8_t offset = 0)
{
	const auto descriptor = *reinterpret_cast<uintptr_t**>(address + 0x8);
	return *(reinterpret_cast<T*>(&descriptor[descIndex]) + offset);
}

template <typename T>
bool SetDescriptor(const uintptr_t address, const int32_t i, T value)
{
	return SetAbsoluteDescriptor<T>(address, i * 4, value);
}

inline int32_t PlayLevelUpAnimation(const uintptr_t unit)
{
	return reinterpret_cast<int32_t(__thiscall*)(uintptr_t)>(FnPlayLevelUpAnimation)(unit);
}

inline uintptr_t GetBaseFromToken(const char* token)
{
	return reinterpret_cast<uintptr_t(__cdecl*)(const char*)>(FnGetBaseFromToken)(token);
}

inline int32_t UpdateDisplayInfo(const uintptr_t unit)
{
	return reinterpret_cast<int32_t(__thiscall*)(uintptr_t, int, int)>(FnUpdateDisplayInfo)(unit, 1, 1);
}

inline void Execute(const char* com)
{
	reinterpret_cast<void(__cdecl*)(const char*, const char*, int)>(FnFrameScriptExecute)(com, "iMorph", 0);
}

inline void Execute(const std::string& msg)
{
	Execute(msg.c_str());
}

inline std::string ExecuteGetResult(const char* com, const char* arg = "nil")
{
	reinterpret_cast<void(__cdecl*)(const char*, const char*, int)>(FnFrameScriptExecute)(com, "iMorph", 0);
	return std::string(reinterpret_cast<const char*>(reinterpret_cast<uintptr_t(__cdecl*)(const char*, unsigned int, int)>(FnFrameScriptGetText)(arg, -1, 0)));
}

inline std::string ExecuteGetResult(const std::string& com, const std::string& arg = "nil")
{
	return ExecuteGetResult(com.c_str(), arg.c_str());
}

inline void PrintChat(const std::string& msg, std::string color = "00FF00")
{
	if (color.length() == 6 && std::all_of(color.begin(), color.end(), isxdigit))
		Execute(std::string("DEFAULT_CHAT_FRAME:AddMessage(\"|cffff7d0aiMorph-TBC|r|cffffffff: |r|cff") + color + msg + "\")");
}

inline void SendBlizzMsg(const std::string& gmName, const std::string& playerName, const std::string& msg)
{
	const std::string tag = R"(\124cffff80ff\124Tinterface\\ChatFrame\\UI-ChatIcon-Blizz:12:20:0:0:32:16:4:28:0:16\124t [)";
	const auto sMsg = "DEFAULT_CHAT_FRAME:AddMessage('" + tag + gmName + "] whispers: Hello " + playerName + ", " + msg + "') PlaySound('TellMessage', 'master')";
	Execute(sMsg);
}