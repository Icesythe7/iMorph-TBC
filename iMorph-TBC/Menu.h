#pragma once
#include "pch.h"
#include "PlayerData.h"
#include "json.hpp"

class Menu
{
public:
	bool last_game_state = false;
	bool current_game_state = false;
	bool first_inititalization = true;
	bool menu_visible = true;
	bool called_by_me = false;
	std::vector<std::string> profiles;
	uintptr_t player;
	PlayerData mog_data;
	PlayerData real_data;

	int8_t num_skincolors;
	int8_t num_faces;
	int8_t num_hairstyles;
	int8_t num_haircolors;
	int8_t num_features;

	int32_t mainhand_enchant_index = 0;
	int32_t offhand_enchant_index = 0;
	int32_t races_index = 0;
	int32_t gender_index = 0;
	int32_t skincolor_slider = 0;
	int32_t face_slider = 0;
	int32_t hairstyle_slider = 0;
	int32_t haircolor_slider = 0;
	int32_t features_slider = 0;
	int32_t title_index = 0;
	int32_t mount_index = 0;

	Menu() = default;
	void UpdateModelAndEquipment();
	void UpdateEquipment();
	void Update();
	void Initialize();
	void RenderMenu();
	[[nodiscard]] bool WriteSaveFile(const std::string&, const nlohmann::json::string_t&) const;
	std::string GetSaveString();
	[[nodiscard]] bool DeleteSaveFile(const std::string&) const;
	nlohmann::json::string_t GetSaveData();
	bool LoadSaveDataFromFile(const std::string&);
	bool LoadSaveDataFromString(const std::string&);
	[[nodiscard]] std::vector<std::string> GetSaveFiles() const;
	static bool BufferIsEmpty(const char*);
	~Menu() = default;
};

