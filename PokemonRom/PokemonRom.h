/*///////////////////////////////////////////////////////////////////////////////////////////////////
	Copyright(c) Fuzzier, 2004/9/10
///////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once

/////////////////////////////////////////////
// this function is used by qsort_s() to sort skills
// pContext: CPokemonRom *, whose skill list will be used for comparison
// pElem0, pElem1: WORD, skill id
INT SortSkillProc(LPVOID pContext, LPCVOID * pElem0, LPCVOID * pElem1);

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "pshpack1.h"

/////////////////////////////////////////////////
#define SPEC_COUNT	(0x4E)	// (78)

/////////////////////////////////////////////////
#define BREED_COUNT		(412)
#define ABILITY_COUNT	(6)
#define ANNOON_COUNT	(28)

struct BreedListEntry
{
	BYTE	bHP;			// ＨＰ		// @0x00
	BYTE	bAtk;			// 攻撃
	BYTE	bDef;			// 防御
	BYTE	bDex;			// 素早さ
	BYTE	bSAtk;			// 特攻		// @0x04
	BYTE	bSDef;			// 特防
	BYTE	bType1;			// タイプ１（相性）
	BYTE	bType2;			// タイプ２（相性）
	BYTE	bCatchRatio;	// 被捕率		// @0x08, 被捕率 = (# + 1) / 256 x 100%
	BYTE	bBaseExp;		// 初期経験値
	WORD	wBattleBonuses;	// 努力値		// @0x0A, BIT[2] (LSB->MSB): ＨＰ, 攻撃, 防御, 素早さ, 特攻, 特防, 0, 0
	WORD	wDrop1;			// 道具１（５０％）// @0x0C
	WORD	wDrop2;			// 道具２（５％）
	BYTE	bFemaleRatio;	// ♀の比率		// @0x10, ♀の比率 = (# + 1) / 256 x 100%, '00'=♂のみ, 'FE'=♀のみ, 'FF'=性別不明
	BYTE	bHatchTime;		// タマゴの歩数	// @0x11, タマゴの歩数 = # x 256
	BYTE	bInitIntimate;	// 初期なつき度
	BYTE	bExpType;		// 経験値タイプ
	BYTE	bEggGroup1;		// タマゴグループ１// @0x14
	BYTE	bEggGroup2;		// タマゴグループ２
	BYTE	bSpecialty1;	// 特性１
	BYTE	bSpecialty2;	// 特性２
	BYTE	bEscapeRatio;	// 逃亡率		// @0x18, 逃亡率 = (# + 1) / 256 x 100%
	BYTE	unk0;			// ？
	WORD	wReserved;		// '00 00'
};

/////////////////////////////////////////////////
extern LPCTSTR	szTypes[];
extern DWORD	dwTypesCount;

/////////////////////////////////////////////////
extern LPCTSTR	szEggGroups[];
extern DWORD	dwEggGroupsCount;

/////////////////////////////////////////////////
#define EXP_LIST_COUNT	(8)
#define EXP_COUNT		(0x65)

/////////////////////////////////////////////////
#define EVO_LIST_COUNT	(5)

struct EvoListEntry
{
	WORD	wCondition;		// 進化の条件
	WORD	wValue;			// 条件の内容 (depends on 進化の条件)
	WORD	wBreed;			// 何のポケモンまで　進化する (index of the pokemon)
	WORD	wReserved;		// '00 00'
};

/////////////////////////////////////////////////
enum { evo_none=0, evo_level=1, evo_item=2, evo_beauty=3 };
struct EvoConditions
{
	LPCTSTR	szCondition;
	LPCTSTR	szParamDesc;
	DWORD	dwParamType;
};

extern EvoConditions	rgEvoConditions[];
extern DWORD			dwEvoConditionsCount;

/////////////////////////////////////////////////
#define ITEM_COUNT	(0x179)

struct ItemListEntry
{
	WORD	wId;
	WORD	wPrice;
	WORD	unk0;
	DWORD	dwAddressOfDescription;
	BYTE	unk1[0x14];
};

struct ItemListEntryJP
{
	BYTE			rgbCode[0x09];
	BYTE			bReserved;
	ItemListEntry	Entry;
};

struct ItemListEntryEN
{
	BYTE			rgbCode[0x0D];
	BYTE			bReserved;
	ItemListEntry	Entry;
};

/////////////////////////////////////////////////
#define SKILL_COUNT			(0x163)	// (355)
#define SKILL_EFFECT_COUNT	(0x100)
struct SkillListEntry
{
	BYTE	bEffect;		// 追加効果
	BYTE	bPower;			// パワー
	BYTE	bType;			// タイプ（相性）
	BYTE	bAccuracy;		// 命中率（# x 100%）
	BYTE	bPP;			// ポイント（ＰＰ）
	BYTE	bEffectRatio;	// 追加効果の発動率（# x 100%）
	BYTE	bTargetType;	// 対象
	CHAR	nPriority;		// 優先度
	DWORD	dwFlags;		// bits: 近身, 守护/见切, 身代, ？, ？, 王者之印, 0 ,0
};

enum SKILLFLAGSENUM
{
	skl_melee = 0x01,
	skl_protect = 0x02,
	skl_substitute = 0x04,
	skl_unk0 = 0x08,
	skl_unk1 = 0x10,
	skl_kingsrock = 0x20,
	skl_reserved0 = 0x40,
	skl_reserved1 = 0x80
};

/////////////////////////////////////////////////
struct SkillTargetType
{
	BYTE	bCode;
	LPCTSTR	szName;
};

extern SkillTargetType	rgSkillTargetTypes[];
extern DWORD			dwSkillTargetTypesCount;

DWORD GetTargetTypeIndex(BYTE bTargetType);

/////////////////////////////////////////////////
#define ENC_COUNT		(0x84 + 0x7C)
#define ENC_TYPE_COUNT	(4)
enum { enc_land=0, enc_water=1, enc_stone=2, enc_fish=3 };

struct EncAddressListEntry
{
	WORD	wAreaId;
	WORD	wReserved;			// '00 00'
	DWORD	dwLandEncAddress;	// points to dwEncCode member of EncXXXList; if not used, the value is 0
	DWORD	dwWaterEncAddress;
	DWORD	dwStoneEncAddress;
	DWORD	dwFishEncAddress;
};

#define ENC_LAND_ENTRY_COUNT	(0x0C)
#define ENC_WATER_ENTRY_COUNT	(0x05)
#define ENC_STONE_ENTRY_COUNT	(0x05)
#define ENC_FISH_ENTRY_COUNT	(0x0A)
#define ANNOON_ENC_AREA_COUNT	(7)		// area id: 0x1B02 - 0x2102 (land encounter)

struct EncEntry
{
	BYTE	bMinLevel;
	BYTE	bMaxLevel;
	WORD	wBreed;
};

struct EncLandList
{
	EncEntry	rgEntry[ENC_LAND_ENTRY_COUNT];
	DWORD		dwEncCode;	// a code affects encounters
	DWORD		dwAddressOfFirstEntry;
};

struct EncWaterList
{
	EncEntry	rgEntry[ENC_WATER_ENTRY_COUNT];
	DWORD		dwEncCode;	// a code affects encounters
	DWORD		dwAddressOfFirstEntry;
};

struct EncStoneList
{
	EncEntry	rgEntry[ENC_STONE_ENTRY_COUNT];
	DWORD		dwEncCode;	// a code affects encounters
	DWORD		dwAddressOfFirstEntry;
};

struct EncFishList
{
	EncEntry	rgEntry[ENC_FISH_ENTRY_COUNT];
	DWORD		dwEncCode;	// a code affects encounters
	DWORD		dwAddressOfFirstEntry;
};

/////////////////////////////////////////////////
// each list ends with 'FF FF'
struct LvlupLearnListEntry
{
	WORD	wSkill : 9;
	WORD	wLevel : 7;
};

/////////////////////////////////////////////////
#define MACHINE_LEARN_ENTRY_SIZE	(8)		// bytes for each block, each block is a 58-bit bit field, SM1-50 & HM1-8

/////////////////////////////////////////////////
#define MACHINE_COUNT	(58)	// there are 50 skill machines, and 8 secret machines

/////////////////////////////////////////////////
#define BERRY_COUNT		(43)
#define BERRY_NAME_SIZE	(6)
struct BerryListEntry
{
	BYTE		szName[BERRY_NAME_SIZE];	// きのみ名前 (0xFF for terminating & padding)
	BYTE		bTerminator;				// 'FF' for JP, '00' for EN
	BYTE		bFirm;						// 硬さ(00=？？？、01=とても　やわらかい、02=やわらかい、03=かたい、04=とても　かたい、05=とてつもなく　かたい)
	WORD		bSize;						// おおきさ (Size = #/10 cm)
	BYTE		bMax;						// 個数の上限
	BYTE		bMin;						// 個数の下限
	DWORD		dwAddressOfDescription0;	// Address of 説明１
	DWORD		dwAddressOfDescription1;	// Address of 説明２
	BYTE		bHoursPerStage;				// 毎段階のかかる時間 (Hour)
	BYTE		bSpicy;						// 辛さ
	BYTE		bDry;						// 渋さ
	BYTE		bSweet;						// 甘さ
	BYTE		bBitter;					// 苦さ
	BYTE		bSour;						// 酸さ
	BYTE		bFeel;						// 滑さ
	BYTE		bReserved;					// 保留 ('00')
};

/////////////////////////////////////////////////
#define SMALL_ICON_PALETTE_LIST_ENTRY_COUNT			(3)
#define SMALL_ICON_PALETTE_LIST_ENTRY_COLOR_DEPTH	(4)
#define SMALL_ICON_PALETTE_LIST_ENTRY_COLOR_COUNT	(1 << SMALL_ICON_PALETTE_LIST_ENTRY_COLOR_DEPTH)
#define SMALL_ICON_ADDRESS_LIST_ENTRY_COUNT			(440)
#define SMALL_ICON_PALETTE_INDEX_LIST_ENTRY_COUNT	(440)
#define SMALL_ICON_SUB_LIST_ENTRY_COUNT				(2)		// ディオキシス(#410(0-based)) has 4 in fire/leaf/emerald
#define SMALL_ICON_TILE_BIT_WIDTH	(8)
#define SMALL_ICON_TILE_BTYE_WIDTH	(SMALL_ICON_TILE_BIT_WIDTH * SMALL_ICON_PALETTE_LIST_ENTRY_COLOR_DEPTH / 8)
#define SMALL_ICON_TILE_BIT_HEIGHT	(8)
#define SMALL_ICON_TILES_HORIZONTAL	(4)
#define SMALL_ICON_TILES_VERTICAL	(4)
#define SMALL_ICON_BIT_WIDTH		(SMALL_ICON_TILE_BIT_WIDTH  * SMALL_ICON_TILES_HORIZONTAL)
#define SMALL_ICON_BYTE_WIDTH		(SMALL_ICON_TILE_BTYE_WIDTH * SMALL_ICON_TILES_HORIZONTAL)
#define SMALL_ICON_BIT_HEIGHT		(SMALL_ICON_TILE_BIT_HEIGHT * SMALL_ICON_TILES_VERTICAL)
#define SMALL_ICON_BIT_WIDTH2		(64)		// for stretching
#define SMALL_ICON_BYTE_WIDTH2		(SMALL_ICON_BIT_WIDTH2 / 2)
#define SMALL_ICON_BIT_HEIGHT2		(64)

struct SmallIconPaletteListEntry
{
	WORD	rgwColor[SMALL_ICON_PALETTE_LIST_ENTRY_COLOR_COUNT];
};

struct SmallIconPaletteList
{
	SmallIconPaletteListEntry	rgEntry[SMALL_ICON_PALETTE_LIST_ENTRY_COUNT];
};

struct SmallIconAddressList
{
	DWORD	rgdwAddress[SMALL_ICON_ADDRESS_LIST_ENTRY_COUNT];
};

struct SmallIconPaletteIndexList
{
	BYTE	rgbPaletteIndex[SMALL_ICON_PALETTE_INDEX_LIST_ENTRY_COUNT];
};

struct SmallIconTile
{
	BYTE	rgbPixel[SMALL_ICON_TILE_BIT_HEIGHT][SMALL_ICON_TILE_BTYE_WIDTH];
};

struct SmallIconSubListEntry
{
	SmallIconTile	rgTile[SMALL_ICON_TILES_VERTICAL][SMALL_ICON_TILES_HORIZONTAL];
};

#include "poppack.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class CPokemonRom
{
public:
	CPokemonRom(VOID);
	~CPokemonRom(VOID);

	BOOL	m_bOpened;
	BOOL	m_bIsFileReadOnly;
	DWORD	m_dwOpenFlags;

	CImageList *m_pSmallIconList;
	CImageList *m_pTinyIconList;
	HBITMAP *	m_rghbmSmallIcons;

	enum eRomVerion
	{
		rom_ruby_jp		=	0,
		rom_sapphire_jp	=	1,
		rom_ruby_en		=	2,
		rom_sapphire_en	=	3,
		rom_fire_jp		=	4,
		rom_leaf_jp		=	5,
		rom_fire_en		=	6,
		rom_leaf_en		=	7,
		rom_emerald_jp	=	8,
		rom_emerald_en	=	9,
	};

	enum eOpenFlags
	{
		rom_breed_list			= 0x00000001,
		rom_pokedex_order		= 0x00000002,
		rom_experience_list		= 0x00000004,
		rom_evolution_list		= 0x00000008,
		rom_item_list			= 0x00000010,
		rom_skill_list			= 0x00000020,
		rom_encounter_list		= 0x00000040,
		rom_lvlup_learn_list	= 0x00000080,
		rom_derive_learn_list	= 0x00000100,
		rom_machine_learn_list	= 0x00000200,
		rom_machine_skill_list	= 0x00000400,
		rom_berry_list			= 0x00000800,
		rom_tiny_image_list		= 0x00001000,
		rom_small_image_list	= 0x00002000,
	//	rom_small_bmp_array		= 0x00003000,	// 'm_rghbmSmallIcons' is always available
	};

	// 1: good, 0: bad, -1: warning (may be bad)
	// 'lpszFileName' takes precedence than 'lpVbaRam'
	// make sure 'lpVbaRam->RefreshAddressList()' is called before calling this function
	INT OpenRom(LPCTSTR lpszFileName, CVisualBoyHandler * lpVbaRam = NULL, DWORD dwOpenFlags = 0x00002FFF);
	VOID CloseRom(VOID);

	DWORD	GetRomVersion(VOID);
	LPCTSTR	GetRomName(VOID);

	/////////////////////////////////////////////
	BOOL ReadBreedList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadPokedexOrder(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadExpList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadEvoList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadItemList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadSkillList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadEncList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadLvlupLearnList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadMachineLearnList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadMachineSkillList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadDeriveLearnList(CVisualBoyHandler * lpVbaRam = NULL);
	BOOL ReadBerryList(CVisualBoyHandler * lpVbaRam = NULL);

	BOOL SaveBreedList(VOID);
	BOOL SaveExpList(VOID);
	BOOL SaveEvoList(VOID);
	BOOL SaveItemList(VOID);
	BOOL SaveSkillList(VOID);
	BOOL SaveEncList(VOID);
	BOOL SaveLvlupLearnList(VOID);
	BOOL SaveMachineLearnList(VOID);
	BOOL SaveMachineSkillList(VOID);
	BOOL SaveDeriveLearnList(VOID);
	BOOL SaveBerryList(VOID);

	VOID CalcDeriveLearnAddressList(VOID);

	/////////////////////////////////////////////
	BreedListEntry * GetBreedListEntry(WORD wBreed);

	WORD * GetDeoxysBreedAbilities();

	DWORD * GetExpList(BYTE bExpType);

	EvoListEntry * GetEvoListEntry(WORD wBreed, BYTE bIndex);

	ItemListEntry * GetItemListEntry(DWORD wItem);

	SkillListEntry * GetSkillListEntry(DWORD wSkill);

	EncLandList * GetEncLandList(DWORD dwEncIndex);
	EncWaterList* GetEncWaterList(DWORD dwEncIndex);
	EncStoneList* GetEncStoneList(DWORD dwEncIndex);
	EncFishList * GetEncFishList(DWORD dwEncIndex);
	EncEntry * GetEncList(DWORD dwEncIndex, DWORD dwEncType);
	BYTE * GetAnnoonEncList(DWORD dwEncIndex);

	// each list ends with 'FF FF'
	LvlupLearnListEntry * GetLvlupLearnList(WORD wBreed);

	// each list is a 8-byte bit field
	BYTE * GetMachineLearnList(WORD wBreed);

	// each list ends with a number larger than 20000 ('not larger than SKILL_COUNT' is enough)
	WORD * GetDeriveLearnList(WORD wBreed);

	BerryListEntry * GetBerryListEntry(DWORD dwIndex);

	/////////////////////////////////////////////
	// wBreed: 0xFFFF for egg
	DWORD GetSmallIconCount(WORD wBreed);
	DWORD GetSmallIconIndex(WORD wBreed, DWORD dwIconIndex);
	HBITMAP GetSmallIcon(WORD wBreed, DWORD dwIndex);
	HBITMAP GetSmallIcon(WORD wBreed);

	WORD GetItemCount(VOID);
	DWORD GetEncCount(VOID);
	DWORD GetEncListEntryCount(DWORD dwEncType);

	DWORD GetLvlupLearnListEntryCount(WORD wBreed);

	DWORD GetDeriveLearnListEntryCount(WORD wBreed);

protected:
	DWORD	GetSmallIconTotalCount(VOID);
	BOOL	CreateSmallIconList(CVisualBoyHandler * lpVbaRam = NULL);

	CFile *	m_pRomFile;
	DWORD	m_dwRomVersion;

public:
	BreedListEntry *		m_pBreedList;
	WORD *					m_pDeoxysBreedAblities;
	WORD *					m_pPokedexHouenOrder;
	WORD *					m_pPokedexKantoOrder;
	DWORD *					m_pExpList;
	EvoListEntry *			m_pEvoList;
	LPVOID					m_pItemList;
	SkillListEntry *		m_pSkillList;
	EncAddressListEntry *	m_pEncAddressList;
	BYTE *					m_pEncList;
	BYTE *					m_pAnnoonEncList;		// アンノーン
	DWORD *					m_pLvlupLearnAddressList;
	BYTE *					m_pLvlupLearnList;
	BYTE *					m_pMachineLearnList;
	WORD *					m_pMachineSkillList;
	BYTE *					m_pDeriveLearnList;
	DWORD *					m_pDeriveLearnAddressList;	// this is not read from rom !
	BerryListEntry *		m_pBerryList;
};
