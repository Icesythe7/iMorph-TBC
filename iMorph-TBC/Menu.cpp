#include "pch.h"
#include "Menu.h"
#include "Natives.h"
#include <iostream>
#include "Typedefs.h"
#include "base64.h"
#include <filesystem>
#include "Shlobj_core.h"
#include <sstream>
#include <fstream>


void Menu::UpdateModelAndEquipment() // Doesnt work on login?
{
	mog_data.WriteModelPlayerData(player);
	mog_data.WriteEquipmentPlayerData(player);
	called_by_me = true;
	UpdateDisplayInfo(player);
}

void Menu::UpdateEquipment()
{
}

void Menu::Update()
{
	current_game_state = *reinterpret_cast<bool*>(OfInGame);

	if (current_game_state != last_game_state)
	{
		last_game_state = current_game_state;
		if (current_game_state)
		{
			Initialize();
			UpdateModelAndEquipment();
		}
	}
}

void Menu::Initialize()
{
	player = GetBaseFromToken("player");

	if (first_inititalization)
	{
		first_inititalization = false;
		real_data.SetInitialPlayerData(player);
		for (auto& effectId : EnchantDisplayId)
			if (effectId.second.first == real_data.main_hand_enchant)
			{
				mainhand_enchant_index = effectId.second.second;
				break;
			}
		for (auto& effectId : EnchantDisplayId)
			if (effectId.second.first == real_data.off_hand_enchant)
			{
				offhand_enchant_index = effectId.second.second;
				break;
			}

		mog_data = real_data;
		races_index = mog_data.race_id - 1;
		gender_index = mog_data.gender;
		skincolor_slider = mog_data.skin_color + 1;
		face_slider = mog_data.face + 1;
		hairstyle_slider = mog_data.hair_style + 1;
		haircolor_slider = mog_data.hair_color + 1;
		features_slider = mog_data.features + 1;
		title_index = mog_data.title;

		profiles = GetSaveFiles();

		SendBlizzMsg("Icesythe7", mog_data.name, "iMorph-TBC has successfully loaded! You can toggle the UI using F5.");
	}
	else
	{
		if (mog_data.name_full != ExecuteGetResult("iMorphNameFull = UnitName('player').. ' - ' ..GetRealmName()", "iMorphNameFull")) //we switched characters
		{
			real_data.SetInitialPlayerData(player);
			mog_data = real_data;
			races_index = mog_data.race_id - 1;
			gender_index = mog_data.gender;
			skincolor_slider = mog_data.skin_color + 1;
			face_slider = mog_data.face + 1;
			hairstyle_slider = mog_data.hair_style + 1;
			haircolor_slider = mog_data.hair_color + 1;
			features_slider = mog_data.features + 1;
			title_index = mog_data.title;
		}
	}
}

void Menu::RenderMenu()
{
	if (GetAsyncKeyState(VK_F6) & 1)
	{
		/*const auto ptr = reinterpret_cast<byte*>(GetPointerDescriptor(player, UNIT_FIELD_BYTES_0));
		std::cout << std::dec << GetDescriptor<int32_t>(player, UNIT_FIELD_NATIVEDISPLAYID) << " NativeDisplayId\n";
		std::cout << std::dec << GetDescriptor<int32_t>(player, UNIT_FIELD_DISPLAYID) << " DisplayId\n";
		std::cout << static_cast<int32_t>(ptr[0]) << " Race\n";
		std::cout << static_cast<int32_t>(ptr[1]) << " Class\n";
		std::cout << static_cast<int32_t>(ptr[2]) << " Gender\n";
		std::cout << static_cast<int32_t>(ptr[3]) << " Ukn3\n";*/
	}

	if (!menu_visible || !current_game_state)
		return;

	if (!ImGui::Begin("iMorph-TBC", &menu_visible, ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
		return;
	}

	ImGui::SetWindowSize(ImVec2(360, 460), ImGuiCond_FirstUseEver);

	if (ImGui::BeginTabBar("Tabs"))
	{
		if (ImGui::BeginTabItem("Equipment"))
		{
			ImGui::Text("You can modify your enchants here.");
			ImGui::Separator();
			ImGui::PushItemWidth(130);
			if (ImGui::Combo("MH", &mainhand_enchant_index, Enchants, IM_ARRAYSIZE(Enchants)))
			{
				mog_data.main_hand_enchant = EnchantDisplayId[Enchants[mainhand_enchant_index]].first;
			}
			ImGui::SameLine(185);
			if (ImGui::Combo("OH", &offhand_enchant_index, Enchants, IM_ARRAYSIZE(Enchants)))
			{
				mog_data.off_hand_enchant = EnchantDisplayId[Enchants[offhand_enchant_index]].first;
			}
			ImGui::Separator();
			ImGui::Text("You can modify your equipment here.");
			ImGui::Separator();
			ImGui::PushItemWidth(80);
			ImGui::InputInt("Head", &mog_data.head, 0, 0, ImGuiInputTextFlags_CharsNoBlank);          ImGui::SameLine(185); ImGui::InputInt("Hands", &mog_data.hands, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputInt("Shoulders", &mog_data.shoulder, 0, 0, ImGuiInputTextFlags_CharsNoBlank); ImGui::SameLine(185); ImGui::InputInt("Belt", &mog_data.waist, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputInt("Back", &mog_data.back, 0, 0, ImGuiInputTextFlags_CharsNoBlank);          ImGui::SameLine(185); ImGui::InputInt("Legs", &mog_data.legs, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputInt("Chest", &mog_data.chest, 0, 0, ImGuiInputTextFlags_CharsNoBlank);        ImGui::SameLine(185); ImGui::InputInt("Boots", &mog_data.feet, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputInt("Shirt", &mog_data.shirt, 0, 0, ImGuiInputTextFlags_CharsNoBlank);        ImGui::SameLine(185); ImGui::InputInt("Mainhand", &mog_data.main_hand, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputInt("Tabard", &mog_data.tabard, 0, 0, ImGuiInputTextFlags_CharsNoBlank);      ImGui::SameLine(185); ImGui::InputInt("Offhand", &mog_data.off_hand, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputInt("Wrist", &mog_data.wrist, 0, 0, ImGuiInputTextFlags_CharsNoBlank);        ImGui::SameLine(185); ImGui::InputInt("Ranged", &mog_data.ranged, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::PopItemWidth();
			ImGui::Separator();
			if (ImGui::Button("Transmogrify", ImVec2(160.0f, 42.0f)))
			{
				mog_data.WriteEquipmentPlayerData(player);
				called_by_me = true;
				PlayLevelUpAnimation(player);
				UpdateDisplayInfo(player);
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset", ImVec2(160.0f, 42.0f)))
			{
				real_data.ResetEquipmentTab(); //get current values
				mog_data = real_data; //reset modified values
				for (auto& effectId : EnchantDisplayId)
					if (effectId.second.first == real_data.main_hand_enchant)
					{
						mainhand_enchant_index = effectId.second.second;
						break;
					}
				for (auto& effectId : EnchantDisplayId)
					if (effectId.second.first == real_data.off_hand_enchant)
					{
						offhand_enchant_index = effectId.second.second;
						break;
					}
				mog_data.WriteEquipmentPlayerData(player);
				called_by_me = true;
				PlayLevelUpAnimation(player);
				UpdateDisplayInfo(player);
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Model"))
		{
			ImGui::Text("You can modify your race here.");
			ImGui::Separator();
			ImGui::PushItemWidth(130);
			if (ImGui::Combo("Race", &races_index, Races, IM_ARRAYSIZE(Races)))
			{
				mog_data.race_id = races_index + 1;
				if (races_index == 9 && mog_data.gender) //bloodelf
				{
					mog_data.display_id = 15475;
					mog_data.native_display_id = 15475;
				}
				else
				{
					mog_data.display_id = RaceIds[races_index] + mog_data.gender;
					mog_data.native_display_id = RaceIds[races_index] + mog_data.gender;
				}
			}
			ImGui::SameLine(185);
			if (ImGui::Combo("Sex", &gender_index, Gender, IM_ARRAYSIZE(Gender)))
			{
				mog_data.gender = static_cast<int8_t>(gender_index);
				if (races_index == 9 && mog_data.gender) //bloodelf
				{
					mog_data.display_id = 15475;
					mog_data.native_display_id = 15475;
				}
				else
				{
					mog_data.display_id = RaceIds[races_index] + mog_data.gender;
					mog_data.native_display_id = RaceIds[races_index] + mog_data.gender;
				}
			}
			ImGui::Separator();
			ImGui::Text("You can modify your model here.");
			ImGui::Separator();
			ImGui::InputInt("Id   ", &mog_data.display_id, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::SameLine();
			ImGui::InputInt("Pet", &mog_data.pet_display_id, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::Separator();
			ImGui::Text("You can modify your appearance here.");
			ImGui::Separator();
			switch (mog_data.race_id)
			{
			case 1: //human
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 10;
					num_faces = 12;
					num_hairstyles = 12;
					num_haircolors = 10;
					num_features = 9;
					break;
				}
				num_skincolors = 10;
				num_faces = 15;
				num_hairstyles = 19;
				num_haircolors = 10;
				num_features = 7;
				break;
			}
			case 2: //orc
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 9;
					num_faces = 9;
					num_hairstyles = 7;
					num_haircolors = 8;
					num_features = 11;
					break;
				}
				num_skincolors = 9;
				num_faces = 9;
				num_hairstyles = 8;
				num_haircolors = 8;
				num_features = 7;
				break;
			}
			case 3: //dwarf
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 9;
					num_faces = 10;
					num_hairstyles = 11;
					num_haircolors = 10;
					num_features = 11;
					break;
				}
				num_skincolors = 9;
				num_faces = 10;
				num_hairstyles = 14;
				num_haircolors = 10;
				num_features = 6;
				break;
			}
			case 4: //night elf
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 9;
					num_faces = 9;
					num_hairstyles = 7;
					num_haircolors = 8;
					num_features = 6;
					break;
				}
				num_skincolors = 9;
				num_faces = 9;
				num_hairstyles = 7;
				num_haircolors = 8;
				num_features = 10;
				break;
			}
			case 5: //undead
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 6;
					num_faces = 10;
					num_hairstyles = 10;
					num_haircolors = 10;
					num_features = 17;
					break;
				}
				num_skincolors = 6;
				num_faces = 10;
				num_hairstyles = 10;
				num_haircolors = 10;
				num_features = 8;
				break;
			}
			case 6: //tauren
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 19;
					num_faces = 5;
					num_hairstyles = 8;
					num_haircolors = 3;
					num_features = 7;
					break;
				}
				num_skincolors = 11;
				num_faces = 4;
				num_hairstyles = 7;
				num_haircolors = 3;
				num_features = 5;
				break;
			}
			case 7: //gnome
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 5;
					num_faces = 7;
					num_hairstyles = 7;
					num_haircolors = 9;
					num_features = 8;
					break;
				}
				num_skincolors = 5;
				num_faces = 7;
				num_hairstyles = 7;
				num_haircolors = 9;
				num_features = 7;
				break;
			}
			case 8: //troll
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 6;
					num_faces = 5;
					num_hairstyles = 6;
					num_haircolors = 10;
					num_features = 11;
					break;
				}
				num_skincolors = 6;
				num_faces = 6;
				num_hairstyles = 5;
				num_haircolors = 10;
				num_features = 6;
				break;
			}
			case 10: //blood elf
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 10;
					num_faces = 13;
					num_hairstyles = 17;
					num_haircolors = 10;
					num_features = 10;
					break;
				}
				num_skincolors = 10;
				num_faces = 13;
				num_hairstyles = 20;
				num_haircolors = 10;
				num_features = 11;
				break;
			}
			case 11: //draenei
			{
				if (mog_data.gender == 0) //male
				{
					num_skincolors = 14;
					num_faces = 10;
					num_hairstyles = 14;
					num_haircolors = 7;
					num_features = 8;
					break;
				}
				num_skincolors = 12;
				num_faces = 10;
				num_hairstyles = 17;
				num_haircolors = 7;
				num_features = 7;
				break;
			}
			default:
				num_skincolors = 1;
				num_faces = 1;
				num_hairstyles = 1;
				num_haircolors = 1;
				num_features = 1;
				break;
			}
			if (ImGui::SliderInt("Skin Color", &skincolor_slider, 1, num_skincolors))
			{
				mog_data.skin_color = skincolor_slider - 1;
			}
			if (ImGui::SliderInt("Face", &face_slider, 1, num_faces))
			{
				mog_data.face = face_slider - 1;
			}
			if (ImGui::SliderInt("Hair Style", &hairstyle_slider, 1, num_hairstyles))
			{
				mog_data.hair_style = hairstyle_slider - 1;
			}
			if (ImGui::SliderInt("Hair Color", &haircolor_slider, 1, num_haircolors))
			{
				mog_data.hair_color = haircolor_slider - 1;
			}
			if (ImGui::SliderInt("Features", &features_slider, 1, num_features))
			{
				mog_data.features = features_slider - 1;
			}
			ImGui::Separator();
			if (ImGui::Button("Morph", ImVec2(160.0f, 36.0f)))
			{
				/*const auto pet = GetUnit("pet");
				if (pet && mog_data.pet_display_id)
				{
					if (!pet_hooked_)
					{
						pet_v_hook_ = new VmtHook(reinterpret_cast<void*>(pet));
						pet_hooked_ = pet_v_hook_->HookFunction(UpdateDisplayInfoHandler, 53);
						pet_address = pet;
					}
					else if (pet_hooked_ && pet_address != pet)
					{
						pet_hooked_ = !pet_v_hook_->UnhookFunction(53);
						delete pet_v_hook_;
						pet_v_hook_ = nullptr;
						pet_v_hook_ = new VmtHook(reinterpret_cast<void*>(pet));
						pet_hooked_ = pet_v_hook_->HookFunction(UpdateDisplayInfoHandler, 53);
						pet_address = pet;
					}

					*reinterpret_cast<int32_t*>(pet_address + 0x8C18) = mog_data.pet_display_id;
					UpdateDisplayInfo(pet);
				}*/
				mog_data.WriteModelPlayerData(player);
				called_by_me = true;
				PlayLevelUpAnimation(player);
				UpdateDisplayInfo(player);
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset", ImVec2(160.0f, 36.0f)))
			{
				real_data.ResetModelTab(mog_data);
				mog_data.WriteModelPlayerData(player);
				races_index = mog_data.race_id - 1;
				gender_index = mog_data.gender;
				skincolor_slider = mog_data.skin_color + 1;
				face_slider = mog_data.face + 1;
				hairstyle_slider = mog_data.hair_style + 1;
				haircolor_slider = mog_data.hair_color + 1;
				features_slider = mog_data.features + 1;
				called_by_me = true;
				PlayLevelUpAnimation(player);
				UpdateDisplayInfo(player);
			}
			ImGui::PopItemWidth();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::Text("You can modify your title here.");
			ImGui::Separator();
			if (ImGui::Combo("Title", &title_index, Titles, IM_ARRAYSIZE(Titles)))
			{
				mog_data.title = title_index;
				SetDescriptor(player, PLAYER_CHOSEN_TITLE, mog_data.title);
				Execute("SetCVar('UnitNameOwn', 0) SetCVar('UnitNameOwn', 1)");
			}
			ImGui::Separator();
			ImGui::Text("You can modify your mount here.");
			ImGui::Separator();
			if (ImGui::Combo("Mount", &mount_index, Mounts, IM_ARRAYSIZE(Mounts)))
			{
				const bool onTaxy = GetDescriptor<int>(player, UNIT_FIELD_FLAGS) >> 0x14 & 1;
				const auto isMounted = *reinterpret_cast<bool*>(player + 0xEC4);
				mog_data.mount_id = MountDisplayId[Mounts[mount_index]];
				if (mog_data.class_id == 11 && *reinterpret_cast<int32_t*>(0xCF21CC) == 33943) //druid in flight form
				{
					SetDescriptor(player, UNIT_FIELD_DISPLAYID, mog_data.mount_id);
					called_by_me = true;
					UpdateDisplayInfo(player);
				}
				else if (isMounted && !onTaxy)
					FpOnMountDisplayChanged(player, mog_data.mount_id);
			}
			ImGui::EndTabItem();
		}

		if (mog_data.class_id == 11 && ImGui::BeginTabItem("Druid"))
		{
			ImGui::Text("You can modify your forms here."); 
			ImGui::Separator();
			ImGui::Checkbox("Stay as human always", &mog_data.stay_human);
			ImGui::Separator();
			if (!mog_data.stay_human)
			{
				ImGui::InputInt("Bear Form", &mog_data.bear, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
				ImGui::InputInt("Aquatic Form", &mog_data.aquatic, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
				ImGui::InputInt("Cat Form", &mog_data.cat, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
				ImGui::InputInt("Travel Form", &mog_data.travel, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
				ImGui::InputInt("Moonkin Form", &mog_data.moonkin, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
				ImGui::InputInt("Tree Form", &mog_data.tree, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			}
			ImGui::Separator();
			if (ImGui::Button("Reset", ImVec2(329.0f, 42.0f)))
			{
				mog_data.ResetShapeshiftTab();
			}
			ImGui::EndTabItem();
		}

		if (mog_data.class_id == 7 && ImGui::BeginTabItem("Shaman"))
		{
			ImGui::Text("You can modify your ghost wolf here.");
			ImGui::Separator();
			ImGui::Checkbox("Stay as human always", &mog_data.stay_human);
			ImGui::Separator();
			if (!mog_data.stay_human)
			{
				ImGui::InputInt("Ghost Wolf", &mog_data.ghost_wolf, 0, 0, ImGuiInputTextFlags_CharsNoBlank);
			}
			ImGui::Separator();
			if (ImGui::Button("Reset", ImVec2(329.0f, 42.0f)))
			{
				mog_data.ResetShapeshiftTab();
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Save"))
		{
			ImGui::Text("Click a profile to load.");
			ImGui::Separator();
			ImGui::BeginChild("Profiles", ImVec2(ImGui::GetWindowContentRegionWidth(), 240), true, ImGuiWindowFlags_HorizontalScrollbar);
			for (const auto& file : profiles)
				if (ImGui::Selectable(file.c_str()))
				{
					LoadSaveDataFromFile(file);
					mog_data.main_hand_enchant = EnchantDisplayId[Enchants[mainhand_enchant_index]].first;
					mog_data.off_hand_enchant = EnchantDisplayId[Enchants[offhand_enchant_index]].first;
					mog_data.WriteEquipmentPlayerData(player);

					mog_data.race_id = races_index + 1;
					mog_data.gender = static_cast<int8_t>(gender_index);
					mog_data.display_id = RaceIds[races_index] + mog_data.gender;
					mog_data.native_display_id = RaceIds[races_index] + mog_data.gender;
					mog_data.skin_color = skincolor_slider - 1;
					mog_data.face = face_slider - 1;
					mog_data.hair_style = hairstyle_slider - 1;
					mog_data.hair_color = haircolor_slider - 1;
					mog_data.features = features_slider - 1;
					mog_data.WriteModelPlayerData(player);

					mog_data.title = title_index;
					SetDescriptor(player, PLAYER_CHOSEN_TITLE, mog_data.title);
					Execute("SetCVar('UnitNameOwn', 0) SetCVar('UnitNameOwn', 1)");

					const bool onTaxy = GetDescriptor<int>(player, UNIT_FIELD_FLAGS) >> 0x14 & 1;
					const auto isMounted = *reinterpret_cast<bool*>(player + 0xEC4);
					mog_data.mount_id = MountDisplayId[Mounts[mount_index]];
					if (mog_data.class_id == 11 && (GetValue<uint8_t>(player, UNIT_FIELD_BYTES_2, 3) == FORM_FLIGHT || GetValue<uint8_t>(player, UNIT_FIELD_BYTES_2, 3) == FORM_FLIGHT_EPIC))
					{
						SetDescriptor(player, UNIT_FIELD_DISPLAYID, mog_data.mount_id);
						called_by_me = true;
						UpdateDisplayInfo(player);
					}
					else if (isMounted && !onTaxy)
						FpOnMountDisplayChanged(player, mog_data.mount_id);

					called_by_me = true;
					UpdateDisplayInfo(player);
				}
			ImGui::EndChild();
			ImGui::Separator();

			static char fileName[128];
			ImGui::PushItemWidth(223);
			ImGui::InputTextWithHint("##dummy", "enter save/delete name here", fileName, IM_ARRAYSIZE(fileName));
			ImGui::PopItemWidth();
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				if (!BufferIsEmpty(fileName))
				{
					const auto f = std::string(fileName);
					if (WriteSaveFile(f, GetSaveData()))
					{
						memset(fileName, 0, sizeof fileName);
						profiles = GetSaveFiles();
						PrintChat("Saved " + f, "00BFFF");
					}
				}
				else
					PrintChat("Please input a file name.", "FF0000");
			}

			ImGui::SameLine();

			if (ImGui::Button("Delete"))
			{
				if (!BufferIsEmpty(fileName))
				{
					const auto f = std::string(fileName);
					if (DeleteSaveFile(f))
					{
						memset(fileName, 0, sizeof fileName);
						profiles = GetSaveFiles();
						PrintChat("Deleted " + f, "00BFFF");
					}
				}
				else
					PrintChat("Please input a file name.", "FF0000");
			}

			static char mString[768];
			ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth());
			if (ImGui::InputTextWithHint("##dummy2", "enter morph string here and press enter", mString, IM_ARRAYSIZE(mString), ImGuiInputTextFlags_EnterReturnsTrue))
			{
				if (!BufferIsEmpty(mString))
					if (LoadSaveDataFromString(std::string(mString)))
					{
						memset(mString, 0, sizeof mString);
						mog_data.main_hand_enchant = EnchantDisplayId[Enchants[mainhand_enchant_index]].first;
						mog_data.off_hand_enchant = EnchantDisplayId[Enchants[offhand_enchant_index]].first;
						mog_data.WriteEquipmentPlayerData(player);

						mog_data.race_id = races_index + 1;
						mog_data.gender = static_cast<int8_t>(gender_index);
						mog_data.display_id = RaceIds[races_index] + mog_data.gender;
						mog_data.native_display_id = RaceIds[races_index] + mog_data.gender;
						mog_data.skin_color = skincolor_slider - 1;
						mog_data.face = face_slider - 1;
						mog_data.hair_style = hairstyle_slider - 1;
						mog_data.hair_color = haircolor_slider - 1;
						mog_data.features = features_slider - 1;
						mog_data.WriteModelPlayerData(player);

						mog_data.title = title_index;
						SetDescriptor(player, PLAYER_CHOSEN_TITLE, mog_data.title);
						Execute("SetCVar('UnitNameOwn', 0) SetCVar('UnitNameOwn', 1)");

						const bool onTaxy = GetDescriptor<int>(player, UNIT_FIELD_FLAGS) >> 0x14 & 1;
						const auto isMounted = *reinterpret_cast<bool*>(player + 0xEC4);
						mog_data.mount_id = MountDisplayId[Mounts[mount_index]];
						if (mog_data.class_id == 11 && (GetValue<uint8_t>(player, UNIT_FIELD_BYTES_2, 3) == FORM_FLIGHT || GetValue<uint8_t>(player, UNIT_FIELD_BYTES_2, 3) == FORM_FLIGHT_EPIC)) //druid in flight form
						{
							SetDescriptor(player, UNIT_FIELD_DISPLAYID, mog_data.mount_id);
							called_by_me = true;
							UpdateDisplayInfo(player);
						}
						else if (isMounted && !onTaxy)
							FpOnMountDisplayChanged(player, mog_data.mount_id);

						called_by_me = true;
						UpdateDisplayInfo(player);

						PrintChat("Loaded morph string.", "00BFFF");
					}
					else
						PrintChat("Invalid morph string.", "FF0000");
				else
					PrintChat("Morph string is empty.", "FF0000");
			}

			ImGui::PopItemWidth();

			if (ImGui::Button("Get Morph String"))
			{
				ImGui::SetClipboardText(GetSaveString().c_str());
				PrintChat("Current data saved to clipboard.", "00BFFF");
			}

			ImGui::SameLine();

			if (ImGui::Button("Refresh Profiles"))
				profiles = GetSaveFiles();

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

bool Menu::WriteSaveFile(const std::string& fileName, const nlohmann::json::string_t& data) const
{
	PWSTR path;
	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, nullptr, &path) == S_OK)
	{
		std::wstringstream ss;
		ss << path << "\\iMorphTBC";
		std::filesystem::path file{ ss.str() };
		file /= fileName + ".json";
		create_directories(file.parent_path());
		std::ofstream ofs(file);
		ofs << data;
		ofs.close();
		CoTaskMemFree(path);
		std::cout << "Saved " << fileName << " to " << file << "\n";
		return true;
	}
	return false;
}

std::string Menu::GetSaveString()
{
	const auto data = GetSaveData();
	return base64_encode(data.c_str(), data.size());
}

bool Menu::DeleteSaveFile(const std::string& fileName) const
{
	auto result = false;
	PWSTR path;
	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, nullptr, &path) == S_OK)
	{
		std::wstringstream ss;
		ss << path << "\\iMorphTBC";
		std::filesystem::path file{ ss.str() };
		file /= fileName + ".json";
		if (exists(file))
		{
			std::filesystem::remove(file);
			std::cout << "Deleted " << fileName << " from " << file << "\n";
			result = true;
		}
		CoTaskMemFree(path);
	}
	return result;
}

nlohmann::json::string_t Menu::GetSaveData()
{
	nlohmann::json j;

	j["Equipment"] = {
		{"Head", mog_data.head},
		{"Shoulders", mog_data.shoulder},
		{"Back", mog_data.back},
		{"Chest", mog_data.chest},
		{"Shirt", mog_data.shirt},
		{"Tabard", mog_data.tabard},
		{"Wrist", mog_data.wrist},
		{"Hands", mog_data.hands},
		{"Belt", mog_data.waist},
		{"Legs", mog_data.legs},
		{"Boots", mog_data.feet},
		{"MainHand", mog_data.main_hand},
		{"OffHand", mog_data.off_hand},
		{"Ranged", mog_data.ranged}
	};

	j["Enchants"] = {
		{"MhEnchant", mainhand_enchant_index},
		{"OhEnchant", offhand_enchant_index}
	};

	j["Model"] = {
		{"Race", races_index},
		{"Gender", gender_index},
		{"SkinColor", skincolor_slider},
		{"Face", face_slider},
		{"HairStyle", hairstyle_slider},
		{"HairColor", haircolor_slider},
		{"Features", features_slider}
	};

	j["Title"] = {
		{"TitleId", title_index}
	};

	j["Mount"] = {
		{"MountDisplayId", mount_index}
	};

	return j.dump();
}

bool Menu::LoadSaveDataFromFile(const std::string& fileName)
{
	PWSTR path;
	std::stringstream buffer;
	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, nullptr, &path) == S_OK)
	{
		std::wstringstream ss;
		ss << path << "\\iMorphTBC";
		std::filesystem::path file{ ss.str() };
		file /= fileName;
		std::ifstream t(file);
		buffer << t.rdbuf();
		CoTaskMemFree(path);

		try
		{
			auto j = nlohmann::json::parse(buffer.str());

			mog_data.head = j["Equipment"]["Head"];
			mog_data.shoulder = j["Equipment"]["Shoulders"];
			mog_data.back = j["Equipment"]["Back"];
			mog_data.chest = j["Equipment"]["Chest"];
			mog_data.shirt = j["Equipment"]["Shirt"];
			mog_data.tabard = j["Equipment"]["Tabard"];
			mog_data.wrist = j["Equipment"]["Wrist"];
			mog_data.hands = j["Equipment"]["Hands"];
			mog_data.waist = j["Equipment"]["Belt"];
			mog_data.legs = j["Equipment"]["Legs"];
			mog_data.feet = j["Equipment"]["Boots"];
			mog_data.main_hand = j["Equipment"]["MainHand"];
			mog_data.off_hand = j["Equipment"]["OffHand"];
			mog_data.ranged = j["Equipment"]["Ranged"];

			mainhand_enchant_index = j["Enchants"]["MhEnchant"];
			offhand_enchant_index = j["Enchants"]["OhEnchant"];

			races_index = j["Model"]["Race"];
			gender_index = j["Model"]["Gender"];
			skincolor_slider = j["Model"]["SkinColor"];
			face_slider = j["Model"]["Face"];
			hairstyle_slider = j["Model"]["HairStyle"];
			haircolor_slider = j["Model"]["HairColor"];
			features_slider = j["Model"]["Features"];

			title_index = j["Title"]["TitleId"];
			mount_index = j["Mount"]["MountDisplayId"];

			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	return false;
}

bool Menu::LoadSaveDataFromString(const std::string& encodedString)
{
	try
	{
		auto j = nlohmann::json::parse(base64_decode(encodedString));

		mog_data.head = j["Equipment"]["Head"];
		mog_data.shoulder = j["Equipment"]["Shoulders"];
		mog_data.back = j["Equipment"]["Back"];
		mog_data.chest = j["Equipment"]["Chest"];
		mog_data.shirt = j["Equipment"]["Shirt"];
		mog_data.tabard = j["Equipment"]["Tabard"];
		mog_data.wrist = j["Equipment"]["Wrist"];
		mog_data.hands = j["Equipment"]["Hands"];
		mog_data.waist = j["Equipment"]["Belt"];
		mog_data.legs = j["Equipment"]["Legs"];
		mog_data.feet = j["Equipment"]["Boots"];
		mog_data.main_hand = j["Equipment"]["MainHand"];
		mog_data.off_hand = j["Equipment"]["OffHand"];
		mog_data.ranged = j["Equipment"]["Ranged"];

		mainhand_enchant_index = j["Enchants"]["MhEnchant"];
		offhand_enchant_index = j["Enchants"]["OhEnchant"];

		races_index = j["Model"]["Race"];
		gender_index = j["Model"]["Gender"];
		skincolor_slider = j["Model"]["SkinColor"];
		face_slider = j["Model"]["Face"];
		hairstyle_slider = j["Model"]["HairStyle"];
		haircolor_slider = j["Model"]["HairColor"];
		features_slider = j["Model"]["Features"];

		title_index = j["Title"]["TitleId"];
		mount_index = j["Mount"]["MountDisplayId"];

		return true;
	}
	catch (...)
	{
		return false;
	}
}

std::vector<std::string> Menu::GetSaveFiles() const
{
	std::vector<std::string> result{};
	PWSTR path;
	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, nullptr, &path) == S_OK)
	{
		std::wstringstream ss;
		ss << path << "\\iMorphTBC";
		const std::filesystem::path file{ ss.str() };
		if (exists(file))
			for (const auto& entry : std::filesystem::directory_iterator(file))
				if (entry.path().extension() == ".json")
					result.push_back(entry.path().filename().string());
		CoTaskMemFree(path);
	}
	return result;
}

bool Menu::BufferIsEmpty(const char* buf)
{
	for (std::size_t i = 0; i < sizeof buf; i++)
		if (buf[i] != '\0')
			return false;
	return true;
}
