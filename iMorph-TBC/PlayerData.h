#pragma once
#include "Natives.h"
#include <string>
#include <map>
#include "EnumsTbc.h"

enum inv_slot
{
	ammo,
	head,
	neck,
	shoulder,
	shirt,
	chest,
	waist,
	legs,
	feet,
	wrist,
	hands,
	finger_1,
	finger_2,
	trinket_1,
	trinket_2,
	back,
	main_hand,
	off_hand,
	ranged,
	tabard
};

inline const char* Races[] = { "Human", "Orc", "Dwarf", "Night Elf", "Undead", "Tauren", "Gnome", "Troll", "Goblin", "Blood Elf", "Draenei" };
inline int32_t RaceIds[] = { 49, 51, 53, 55, 57, 59, 1563, 1478, 6894, 15476, 16125 }; //bloodelf female is -1 (wtf blizz?)
inline const char* Gender[] = { "Male", "Female" };

inline const char* Enchants[] =
{
	"No Enchant",

	//Enchants
	"Executioner",
	"Spellsurge",
	"Mongoose",
	"Battlemaster",
	"Deathfrost",
	"Crusader",
	"Demonslaying",
	"Fiery Weapon",
	"Icy Chill",
	"Lifestealing",
	"Unholy Weapon",
	"Major Spellpower",
	"Major Healing",
	"Spellpower",
	"Healing Power",
	"Sunfire",
	"Soulfrost",
	"Greater Agility",
	"Agility",
	"Major Intellect",
	"Mighty Intellect",
	"Mighty Versatility",
	"Potency",
	"Strength",
	"2h Superior Impact",
	"2h Greater Impact",
	"2h Impact",
	"2h Lesser Impact",
	"2h Savagery",
	"2h Major Agility",
	"2h Agility",
	"2h Major Intellect",
	"2h Major Versatility",
	"Major Striking",
	"Superior Striking",
	"Greater Striking",
	"Striking",
	"Lesser Beastslayer",
	"Minor Beastslayer",
	"Lesser Elemental Slayer"
};

inline const char* Titles[] =
{
	"No Title",
	"Private",
	"Corporal",
	"Sergeant",
	"Master Sergeant",
	"Sergeant Major",
	"Knight",
	"Knight-Lieutenant",
	"Knight-Captain",
	"Knight-Champion",
	"Lieutenant Commander",
	"Commander",
	"Marshal",
	"Field Marshal",
	"Grand Marshal",
	"Scout",
	"Grunt",
	"Sergeant",
	"Senior Sergeant",
	"First Sergeant",
	"Stone Guard",
	"Blood Guard",
	"Legionnaire",
	"Centurion",
	"Champion",
	"Lieutenant General",
	"General",
	"Warlord",
	"High Warlord",
	"Gladiator",
	"Duelist",
	"Rival",
	"Challenger",
	"Scarab Lord",
	"Conqueror",
	"Justicar",
	"Champion of the Naaru",
	"Merciless Gladiator",
	"of the Shattered Sun",
	"Hand of A'dal",
	"Vengeful Gladiator"
};

inline std::map<const std::string, std::pair<int32_t, int32_t>> EnchantDisplayId
{
	//{enchantName, {enchantId, index}}
	//None
	{"No Enchant", {0, 0}},

	//Enchants
	{"Executioner", {3225, 1}},
	{"Spellsurge", {2674, 2}},
	{"Mongoose", {2673, 3}},
	{"Battlemaster", {2675, 4}},
	{"Deathfrost", {3273, 5}},
	{"Crusader", {1900, 6}},
	{"Demonslaying", {912, 7}},
	{"Fiery Weapon", {803, 8}},
	{"Icy Chill", {1894, 9}},
	{"Lifestealing", {1898, 10}},
	{"Unholy Weapon", {1899, 11}},
	{"Major Spellpower", {2669, 12}},
	{"Major Healing", {3846, 13}},
	{"Spellpower", {2504, 14}},
	{"Healing Power", {2505, 15}},
	{"Sunfire", {2671, 16}},
	{"Soulfrost", {2672, 17}},
	{"Greater Agility", {3222, 18}},
	{"Agility", {2564, 19}},
	{"Major Intellect", {2666, 20}},
	{"Mighty Intellect", {2568, 21}},
	{"Mighty Versatility", {2567, 22}},
	{"Potency", {2668, 23}},
	{"Strength", {2563, 24}},
	{"2h Superior Impact", {1896, 25}},
	{"2h Greater Impact", {963, 26}},
	{"2h Impact", {1897, 27}},
	{"2h Lesser Impact", {943, 28}},
	{"2h Savagery", {2667, 29}},
	{"2h Major Agility", {2670, 30}},
	{"2h Agility", {2646, 31}},
	{"2h Major Intellect", {1904, 32}},
	{"2h Major Versatility", {1903, 33}},
	{"Major Striking", {4746, 34}},
	{"Superior Striking", {1897, 35}},
	{"Greater Striking", {805, 36}},
	{"Striking", {4745, 37}},
	{"Lesser Beastslayer", {853, 38}},
	{"Minor Beastslayer", {249, 39}},
	{"Lesser Elemental Slayer", {854, 40}},
};

inline const char* Mounts[] =
{
	//Normal Mount
	"Normal Mount",
	//End Normal Mount

	//Vanilla Mounts
	"Ancient Frostsaber",
	"Arctic Wolf",
	"Black Battlestrider",
	"Black Nightsaber",
	"Black Qiraji Battle Tank",
	"Black Ram",
	"Black Stallion",
	"Black War Kodo",
	"Black War Ram",
	"Black War Raptor",
	"Black War Steed",
	"Black War Tiger",
	"Black War Wolf",
	"Blue Mechanostrider",
	"Blue Qiraji Battle Tank",
	"Blue Skeletal Horse",
	"Brown Horse",
	"Brown Kodo",
	"Brown Ram",
	"Brown Skeletal Horse",
	"Brown Wolf",
	"Charger",
	"Chestnut Mare",
	"Dire Wolf",
	"Dreadsteed",
	"Emerald Raptor",
	"Felsteed",
	"Frost Ram",
	"Frostwolf Howler",
	"Gray Kodo",
	"Gray Ram",
	"Great Brown Kodo",
	"Great Gray Kodo",
	"Great White Kodo",
	"Green Kodo",
	"Green Mechanostrider",
	"Green Qiraji Battle Tank",
	"Green Skeletal Warhorse",
	"Icy Blue Mechanostrider Mod A",
	"Ivory Raptor",
	"Mottled Red Raptor",
	"Palomino",
	"Pinto",
	"Purple Skeletal Warhorse",
	"Red Mechanostrider",
	"Red Qiraji Battle Tank",
	"Red Skeletal Horse",
	"Red Skeletal Warhorse",
	"Red Wolf",
	"Riding Turtle",
	"Rivendare's Deathcharger",
	"Spotted Frostsaber",
	"Stormpike Battle Charger",
	"Striped Frostsaber",
	"Striped Nightsaber",
	"Swift Blue Raptor",
	"Swift Brown Ram",
	"Swift Brown Steed",
	"Swift Brown Wolf",
	"Swift Frostsaber",
	"Swift Gray Ram",
	"Swift Gray Wolf",
	"Swift Green Mechanostrider",
	"Swift Mistsaber",
	"Swift Olive Raptor",
	"Swift Orange Raptor",
	"Swift Palomino",
	"Swift Razzashi Raptor",
	"Swift Stormsaber",
	"Swift Timber Wolf",
	"Swift White Mechanostrider",
	"Swift White Ram",
	"Swift White Steed",
	"Swift Yellow Mechanostrider",
	"Swift Zulian Tiger",
	"Teal Kodo",
	"Timber Wolf",
	"Turquoise Raptor",
	"Unpainted Mechanostrider",
	"Violet Raptor",
	"Warhorse",
	"White Mechanostrider Mod B",
	"White Ram",
	"White Stallion",
	"Winterspring Frostsaber",
	"Yellow Qiraji Battle Tank",
	//End Vanilla Mounts

	//TBC Mounts
	"Amani War Bear",
	"Ashes of Al'ar",
	"Azure Netherwing Drake",
	"Big Battle Bear",
	"Black Hawkstrider",
	"Black War Elekk",
	"Blue Hawkstrider",
	"Blue Hippogryph",
	"Blue Riding Nether Ray",
	"Blue Wind Rider",
	"Brewfest Ram",
	"Brown Elekk",
	"Cenarion War Hippogryph",
	"Cobalt Netherwing Drake",
	"Cobalt Riding Talbuk",
	"Cobalt War Talbuk",
	"Dark Riding Talbuk",
	"Dark War Talbuk",
	"Ebon Gryphon",
	"Fiery Warhorse",
	"Flying Machine",
	"Golden Gryphon",
	"Gray Elekk",
	"Great Blue Elekk",
	"Great Brewfest Kodo",
	"Great Green Elekk",
	"Great Purple Elekk",
	"Green Riding Nether Ray",
	"Green Wind Rider",
	"Merciless Nether Drake",
	"Onyx Netherwing Drake",
	"Purple Elekk",
	"Purple Hawkstrider",
	"Purple Netherwing Drake",
	"Purple Riding Nether Ray",
	"Purple Twilight Drake",
	"Raven Lord",
	"Red Hawkstrider",
	"Red Riding Nether Ray",
	"Silver Riding Nether Ray",
	"Silver Riding Talbuk",
	"Silver War Talbuk",
	"Snowy Gryphon",
	"Spectral Tiger",
	"Swift Blue Gryphon",
	"Swift Brewfest Ram",
	"Swift Green Gryphon",
	"Swift Green Hawkstrider",
	"Swift Green Wind Rider",
	"Swift Nether Drake",
	"Swift Pink Hawkstrider",
	"Swift Purple Gryphon",
	"Swift Purple Hawkstrider",
	"Swift Purple Wind Rider",
	"Swift Red Gryphon",
	"Swift Red Wind Rider",
	"Swift Spectral Tiger",
	"Swift Warstrider",
	"Swift White Hawkstrider",
	"Swift Yellow Wind Rider",
	"Swift Zhevra",
	"Tan Riding Talbuk",
	"Tan War Talbuk",
	"Tawny Wind Rider",
	"Thalassian Charger",
	"Thalassian Warhorse",
	"Turbo-Charged Flying Machine",
	"Vengeful Nether Drake",
	"Veridian Netherwing Drake",
	"Violet Netherwing Drake",
	"White Riding Talbuk",
	"White War Talbuk",
	"X-51 Nether-Rocket",
	"X-51 Nether-Rocket X-TREME"
	//End TBC Mounts
};

inline std::map<const std::string, int> MountDisplayId
{
	//Normal Mount
	{"Normal Mount", 0},
	//End Normal Mount

	//Vanilla Mounts
	{"Ancient Frostsaber", 9695},
	{"Arctic Wolf", 1166},
	{"Black Battlestrider", 14372},
	{"Black Nightsaber", 9991},
	{"Black Qiraji Battle Tank", 15676},
	{"Black Ram", 2784},
	{"Black Stallion", 2402},
	{"Black War Kodo", 14348},
	{"Black War Ram", 14577},
	{"Black War Raptor", 14388},
	{"Black War Steed", 14337},
	{"Black War Tiger", 14330},
	{"Black War Wolf", 14334},
	{"Blue Mechanostrider", 6569},
	{"Blue Qiraji Battle Tank", 15672},
	{"Blue Skeletal Horse", 10671},
	{"Brown Horse", 2404},
	{"Brown Kodo", 11641},
	{"Brown Ram", 2785},
	{"Brown Skeletal Horse", 10672},
	{"Brown Wolf", 2328},
	{"Charger", 14584},
	{"Chestnut Mare", 2405},
	{"Dire Wolf", 2327},
	{"Dreadsteed", 14554},
	{"Emerald Raptor", 4806},
	{"Felsteed", 2346},
	{"Frost Ram", 2787},
	{"Frostwolf Howler", 14776},
	{"Gray Kodo", 12246},
	{"Gray Ram", 2736},
	{"Great Brown Kodo", 14578},
	{"Great Gray Kodo", 14579},
	{"Great White Kodo", 14349},
	{"Green Kodo", 12245},
	{"Green Mechanostrider", 10661},
	{"Green Qiraji Battle Tank", 15679},
	{"Green Skeletal Warhorse", 10720},
	{"Icy Blue Mechanostrider Mod A", 10666},
	{"Ivory Raptor", 6471},
	{"Mottled Red Raptor", 6469},
	{"Palomino", 2408},
	{"Pinto", 2409},
	{"Purple Skeletal Warhorse", 10721},
	{"Red Mechanostrider", 9473},
	{"Red Qiraji Battle Tank", 15681},
	{"Red Skeletal Horse", 10670},
	{"Red Skeletal Warhorse", 10719},
	{"Red Wolf", 2326},
	{"Riding Turtle", 17158},
	{"Rivendare's Deathcharger", 10718},
	{"Spotted Frostsaber", 6444},
	{"Stormpike Battle Charger", 14777},
	{"Striped Frostsaber", 6080},
	{"Striped Nightsaber", 6448},
	{"Swift Blue Raptor", 14339},
	{"Swift Brown Ram", 14347},
	{"Swift Brown Steed", 14583},
	{"Swift Brown Wolf", 14573},
	{"Swift Frostsaber", 14331},
	{"Swift Gray Ram", 14576},
	{"Swift Gray Wolf", 14574},
	{"Swift Green Mechanostrider", 14374},
	{"Swift Mistsaber", 14332},
	{"Swift Olive Raptor", 14344},
	{"Swift Orange Raptor", 14342},
	{"Swift Palomino", 14582},
	{"Swift Razzashi Raptor", 15289},
	{"Swift Stormsaber", 14632},
	{"Swift Timber Wolf", 14575},
	{"Swift White Mechanostrider", 14376},
	{"Swift White Ram", 14346},
	{"Swift White Steed", 14338},
	{"Swift Yellow Mechanostrider", 14377},
	{"Swift Zulian Tiger", 15290},
	{"Teal Kodo", 12242},
	{"Timber Wolf", 247},
	{"Turquoise Raptor", 6472},
	{"Unpainted Mechanostrider", 9476},
	{"Violet Raptor", 6473},
	{"Warhorse", 8469},
	{"White Mechanostrider Mod B", 9474},
	{"White Ram", 2786},
	{"White Stallion", 2410},
	{"Winterspring Frostsaber", 10426},
	{"Yellow Qiraji Battle Tank", 15680},
	//End Vanilla Mounts

	//TBC Mounts
	{"Amani War Bear", 22464},
	{"Ashes of Al'ar", 17890},
	{"Azure Netherwing Drake", 21521},
	{"Big Battle Bear", 25335},
	{"Black Hawkstrider", 19478},
	{"Black War Elekk", 23928},
	{"Blue Hawkstrider", 19480},
	{"Blue Hippogryph", 22472},
	{"Blue Riding Nether Ray", 21156},
	{"Blue Wind Rider", 17700},
	{"Brewfest Ram", 22265},
	{"Brown Elekk", 17063},
	{"Cenarion War Hippogryph", 22473},
	{"Cobalt Netherwing Drake", 21525},
	{"Cobalt Riding Talbuk", 21073},
	{"Cobalt War Talbuk", 19375},
	{"Dark Riding Talbuk", 21074},
	{"Dark War Talbuk", 19303},
	{"Ebon Gryphon", 17694},
	{"Fiery Warhorse", 19250},
	{"Flying Machine", 22719},
	{"Golden Gryphon", 17697},
	{"Gray Elekk", 19869},
	{"Great Blue Elekk", 19871},
	{"Great Brewfest Kodo", 24757},
	{"Great Green Elekk", 19873},
	{"Great Purple Elekk", 19872},
	{"Green Riding Nether Ray", 21152},
	{"Green Wind Rider", 17701},
	{"Merciless Nether Drake", 22620},
	{"Onyx Netherwing Drake", 21520},
	{"Purple Elekk", 19870},
	{"Purple Hawkstrider", 19479},
	{"Purple Netherwing Drake", 21523},
	{"Purple Riding Nether Ray", 21155},
	{"Purple Twilight Drake", 27796},
	{"Raven Lord", 21473},
	{"Red Hawkstrider", 18696},
	{"Red Riding Nether Ray", 21158},
	{"Silver Riding Nether Ray", 21157},
	{"Silver Riding Talbuk", 21075},
	{"Silver War Talbuk", 19378},
	{"Snowy Gryphon", 17696},
	{"Spectral Tiger", 21973},
	{"Swift Blue Gryphon", 17759},
	{"Swift Brewfest Ram", 22350},
	{"Swift Green Gryphon", 17703},
	{"Swift Green Hawkstrider", 19484},
	{"Swift Green Wind Rider", 17720},
	{"Swift Nether Drake", 20344},
	{"Swift Pink Hawkstrider", 18697},
	{"Swift Purple Gryphon", 17717},
	{"Swift Purple Hawkstrider", 19482},
	{"Swift Purple Wind Rider", 17721},
	{"Swift Red Gryphon", 17718},
	{"Swift Red Wind Rider", 17719},
	{"Swift Spectral Tiger", 21974},
	{"Swift Warstrider", 20359},
	{"Swift White Hawkstrider", 19483},
	{"Swift Yellow Wind Rider", 17722},
	{"Swift Zhevra", 24745},
	{"Tan Riding Talbuk", 21077},
	{"Tan War Talbuk", 19376},
	{"Tawny Wind Rider", 17699},
	{"Thalassian Charger", 19085},
	{"Thalassian Warhorse", 19296},
	{"Turbo-Charged Flying Machine", 22720},
	{"Vengeful Nether Drake", 24725},
	{"Veridian Netherwing Drake", 21522},
	{"Violet Netherwing Drake", 21524},
	{"White Riding Talbuk", 21076},
	{"White War Talbuk", 19377},
	{"X-51 Nether-Rocket", 23656},
	{"X-51 Nether-Rocket X-TREME", 23647}
	//End TBC Mounts
};

struct PlayerData
{
	std::string name;
	std::string name_full;

	//Item Slots
	int32_t head;
	int32_t shoulder;
	int32_t shirt;
	int32_t chest;
	int32_t waist;
	int32_t legs;
	int32_t feet;
	int32_t wrist;
	int32_t hands;
	int32_t back;
	int32_t main_hand;
	int32_t off_hand;
	int32_t ranged;
	int32_t tabard;

	//Enchant Data
	int32_t main_hand_enchant;
	int32_t off_hand_enchant;

	//Customization Data
	int8_t skin_color;
	int8_t face;
	int8_t hair_style;
	int8_t hair_color;
	int8_t features;

	//Race & Gender Data
	int8_t race_id;
	int8_t class_id;
	int8_t gender;
	int32_t display_id;
	int32_t native_display_id;
	int32_t pet_display_id;

	//Title Data
	int8_t title;
	int8_t medal;

	//Shapeshift Data
	bool stay_human;
	int32_t bear;
	int32_t aquatic;
	int32_t cat;
	int32_t travel;
	int32_t flight;
	int32_t moonkin;
	int32_t tree;
	int32_t ghost_wolf;

	//Mount Data
	int32_t mount_id;

	void SetInitialPlayerData(const uintptr_t unit)
	{
		//Equipment Data
		head = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_1_0);
		shoulder = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_3_0);
		shirt = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_4_0);
		chest = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_5_0);
		waist = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_6_0);
		legs = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_7_0);
		feet = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_8_0);
		wrist = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_9_0);
		hands = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_10_0);
		back = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_15_0);
		main_hand = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_16_0);
		off_hand = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_17_0);
		ranged = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_18_0);
		tabard = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_19_0);
		main_hand_enchant = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_16_1_ENCHANT);
		off_hand_enchant = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_17_1_ENCHANT);

		//Other Data
		const auto ptr = reinterpret_cast<byte*>(GetPointerDescriptor(unit, UNIT_FIELD_BYTES_0));
		const auto styles = reinterpret_cast<byte*>(GetPointerDescriptor(unit, PLAYER_BYTES));
		const auto styles2 = reinterpret_cast<byte*>(GetPointerDescriptor(unit, PLAYER_BYTES_2));
		skin_color = styles[0];
		face = styles[1];
		hair_style = styles[2];
		hair_color = styles[3];
		features = styles2[0];
		race_id = ptr[0];
		class_id = ptr[1];
		gender = ptr[2];
		display_id = GetDescriptor<int32_t>(unit, UNIT_FIELD_DISPLAYID);
		native_display_id = GetDescriptor<int32_t>(unit, UNIT_FIELD_NATIVEDISPLAYID);
		title = GetDescriptor<int32_t>(unit, PLAYER_CHOSEN_TITLE);
		//medal = unit->medal;
		name = ExecuteGetResult("iMorphName = UnitName('player')", "iMorphName");
		name_full = ExecuteGetResult("iMorphNameFull = UnitName('player').. ' - ' ..GetRealmName()", "iMorphNameFull");
	}

	/*bool SendItemSlotPacket(int32_t slotId, int32_t displayId)
	{
		Packet pkt;
		char bitBuffer[1000];
		pkt.Write<int32_t>(packedGuid);
		pkt.Write<char[]>(*bitBuffer | slotId);
		pkt.Write<int32_t>(displayId);
		return pkt.Recieve();
	}*/

	void UpdatePlayerData(const uintptr_t unit)
	{
		head = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_1_0);
		shoulder = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_3_0);
		shirt = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_4_0);
		chest = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_5_0);
		waist = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_6_0);
		legs = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_7_0);
		feet = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_8_0);
		wrist = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_9_0);
		hands = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_10_0);
		back = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_15_0);
		main_hand = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_16_0);
		off_hand = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_17_0);
		ranged = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_18_0);
		tabard = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_19_0);
		main_hand_enchant = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_16_1_ENCHANT);
		off_hand_enchant = GetDescriptor<int32_t>(unit, PLAYER_VISIBLE_ITEM_17_1_ENCHANT);
		title = GetDescriptor<int32_t>(unit, PLAYER_CHOSEN_TITLE);
	}

	void WriteEquipmentPlayerData(const uintptr_t unit) const
	{
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_1_0, head);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_3_0, shoulder);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_4_0, shirt);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_5_0, chest);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_6_0, waist);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_7_0, legs);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_8_0, feet);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_9_0, wrist);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_10_0, hands);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_15_0, back);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_16_0, main_hand);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_17_0, off_hand);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_18_0, ranged);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_19_0, tabard);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_16_1_ENCHANT, main_hand_enchant);
		SetDescriptor(unit, PLAYER_VISIBLE_ITEM_17_1_ENCHANT, off_hand_enchant);
	}

	void WriteModelPlayerData(const uintptr_t unit) const
	{
		const auto ptr = reinterpret_cast<byte*>(GetPointerDescriptor(unit, UNIT_FIELD_BYTES_0));
		const auto styles = reinterpret_cast<byte*>(GetPointerDescriptor(unit, PLAYER_BYTES));
		const auto styles2 = reinterpret_cast<byte*>(GetPointerDescriptor(unit, PLAYER_BYTES_2));
		//ptr[0] = race_id;
		//ptr[2] = gender;
		SetDescriptor(unit, UNIT_FIELD_DISPLAYID, display_id);
		SetDescriptor(unit, UNIT_FIELD_NATIVEDISPLAYID, native_display_id);
		styles[0] = skin_color;
		styles[1] = face;
		styles[2] = hair_style;
		styles[3] = hair_color;
		styles2[0] = features;
	}

	void ResetEquipmentTab()
	{
		head = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 1) id = ':0:' if link then id = link end", "id"), ":")[1]);
		shoulder = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 3) id = ':0:' if link then id = link end", "id"), ":")[1]);
		shirt = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 4) id = ':0:' if link then id = link end", "id"), ":")[1]);
		chest = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 5) id = ':0:' if link then id = link end", "id"), ":")[1]);
		waist = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 6) id = ':0:' if link then id = link end", "id"), ":")[1]);
		legs = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 7) id = ':0:' if link then id = link end", "id"), ":")[1]);
		feet = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 8) id = ':0:' if link then id = link end", "id"), ":")[1]);
		wrist = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 9) id = ':0:' if link then id = link end", "id"), ":")[1]);
		hands = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 10) id = ':0:' if link then id = link end", "id"), ":")[1]);
		back = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 15) id = ':0:' if link then id = link end", "id"), ":")[1]);
		main_hand = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 16) id = ':0:' if link then id = link end", "id"), ":")[1]);
		off_hand = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 17) id = ':0:' if link then id = link end", "id"), ":")[1]);
		ranged = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 18) id = ':0:' if link then id = link end", "id"), ":")[1]);
		tabard = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 19) id = ':0:' if link then id = link end", "id"), ":")[1]);
		main_hand_enchant = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 16) id = ':0:0:' if link then id = link end", "id"), ":")[2]);
		off_hand_enchant = stoi(Split(ExecuteGetResult("local link = GetInventoryItemLink('player', 17) id = ':0:0:' if link then id = link end", "id"), ":")[2]);
	}

	void ResetModelTab (PlayerData& data) const
	{
		data.race_id = race_id;
		data.gender = gender;
		data.display_id = display_id;
		data.native_display_id = native_display_id;
		data.skin_color = skin_color;
		data.face = face;
		data.hair_style = hair_style;
		data.hair_color = hair_color;
		data.features = features;
	}

	void ResetMiscTab(PlayerData& data)
	{
		title = static_cast<int8_t>(stoi(ExecuteGetResult("s_rank = UnitPVPRank('player')", "s_rank")));
		medal = 0;
		data.title = title;
		data.medal = medal;
	}

	void ResetShapeshiftTab()
	{
		stay_human = false;
		bear = 0;
		aquatic = 0;
		cat = 0;
		travel = 0;
		moonkin = 0;
		ghost_wolf = 0;
	}
};