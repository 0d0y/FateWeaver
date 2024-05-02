#pragma once

#define SIZE(ENUM) (static_cast<size_t>(ENUM))

namespace McCol
{
    class StateIcon;
    class Panel;
}

// 모든 상태이상은 적용되는 시점부터 발현됨
enum class State
{
	NONE,
	QUICK,			// 재빠름	: 모든 받는 데미지 -3				비고) 여러 공격 횟수가 있는 공격에 피격시 매 공격마다 적용.
	DISRUPTION,		// 흐트러짐	: 모든 플레이 카드 주도력 +1		비고) 이미 미래 영역에 놓인 카드도 주도력 증가로 인한 카드 처리 순서 실시간으로 반영.
	CONFUSION,		// 혼란		: 카드 데미지 30% 감소
	ENCHANTMENT,	// 마력 충전	: 주는 데미지 +3
	STUNNED,		// 기절		: 가장 빠른 주도력의 카드를 버린 카드 더미로 옮긴다.
	IMPENDING_RUIN, // 파멸의 예언 : 카드 데미지 +2 다음 전투 때의 광신도 카드도 강화를 받은 상태
	WILL_OF_RUIN,	// 파멸의 의지 : 자신 체력 +10  다음 전투 때의 광신도가 강화를 받은 상태
	ENGINE_OVERLOAD,// 엔진과부하 : 카드 데미지 +2 버프 영구 제공(파멸의 예언의 보스 버전)
	DEFENSE,
	END
};

enum class Attribute
{
	NONE,
	INITIATIVE,		// 주도력
	DAMAGE,			// 데미지
	HEALTH,			// 체력
	DEFENSE,		// 방어도
	ATTACK_COUNT,	// 공격 횟수
	FATE_ENERGY,	// 운명 에너지
	DRAW_NUMBER,    // 드로우 수
	BUFF_DURATION,  // 버프 지속시간
	VALUE,			// 수치
	END,
};

enum class Keyword
{
	NONE,
	MOMENT,			// 찰나
	OVERLOAD,		// 과부하
};

enum class Target
{
	ATTRIBUTE,
	ENEMY_CHARACTER,
	PLAYER_PLAY_CARD,
	PLAYER_FATE_CARD,
	ENEMY_PLAY_CARD,
};

enum class CardType
{
	NONE,
	PLAYER_PLAY_CARD,
	PLAYER_FATE_CARD,
	ENEMY_PLAY_CARD,
	PLAY_CARD,
};

enum class Destination
{
	NONE,
	PLAYER,
	SELF,
	NEAREST_ENEMY,
	FARTHEST_ENEMY,
	ALL_ENEMIES
};

enum class Operation
{
	NONE,
	ADD,
	SUB,
	MUL,
	DIV,
	SET
};

enum class Rarity
{
	DEFAULT,
	COMMON,
	UNCOMMON,
	RARE,
	PARADOX_COMMON,
	PARADOX_UNCOMMON,
	PARADOX_RARE,
};

struct CardInfo
{
	int Attributes[SIZE(Attribute::END)];
	int States[SIZE(State::END)];
};

enum class DeckType
{
	NONE,
	PLAYER_PLAY_CARD,
	PLAYER_FATE_CARD,
	ENEMY_PLAY_CARD,
};

enum class CharacterType
{
	NONE,
	PLAYER,
	ZOMBIE,
	WEREWOLF,
	STALKER,
	FANATIC,
	GOLEM,
};

enum class CharacterIndex
{
	NONE = -1,
	PLAYER,
	ENEMY1,
	ENEMY2,
	ENEMY3,
	ENEMY4,
	END,
};

enum class EffectType {
	Damaged,
	SLASH_1,
	//SLASH_2,
	재빠름시작,
	재빠름종료,

	마력충전시작,
	마력충전종료,

	혼란시작,
	혼란종료,

	흐트러짐시작,
	흐트러짐종료,

	파멸의예언시작,

	파멸의의지시작,

	엔진과부하시작,

	방어도아이콘,

	즉시발동,
	행동카드제거,

	전투개시,
	행동개시,
	차례시작,
	대상없음,
	에너지부족,
	패배,

	Effect_GetCard,
	Effect_DisCard,
	Effect_DrawCard,
	Effect_Shuffle,

	Effect_Heal_Screen,
	GainLife_15,
	GainLife_25,

	Effect_End,


	END,
};

struct EffectInfo {
	EffectType Type;
	float X = 0, Y = 0;		// 효과를 표시할 화면상 위치
	int Value = -1;			// 이펙트와 동시에 뜨는 텍스트
};

struct PanelInfo {
	McCol::Panel* Panel;	// 패널 정보,  패널 타입 분리가 어려워서 우선 Panel*로 넣어둠
	float OffsetX, OffsetY;	// 패널이 띄워질 위치
};

struct IconInfo {
	McCol::StateIcon* StateIcon;		// 아이콘 정보, 아이콘 타입 분리가 어려워서 우선 Icon*로 넣어둠
	State PlayerState;      // 아이콘의 State
	float OffsetX;			// 아이콘이 띄워질 위치(Y는 고정되어있음)
	int RepeatCount;		// 아이콘이 유지될 횟수
};

namespace DefaultPlayCard
{
	enum class PlayerCard
	{
		//기본
		사격,
		회피,
		다리걸기,
		난사,

		//커먼
		저격,

		//언커먼
		플래쉬뱅,
		피버타임,
		빈틈포착,

		//레어
		마탄의사수,
		아케인블래스트,

	};

	enum class MonsterCard
	{
		차가운포옹,
		깨물기,
		야성해방,
		무자비,
		저돌맹진,
		필연적인공포,
		끝없는추적,
		저격,
		다리걸기,
		플래쉬뱅,
		멸망을부르는노래,
		공허의가호,
		징벌,
		시공의파동,
		엔진과부하,
		말살,
		기어체인지,
	};
};

namespace DefaultFateCard
{
	enum class PlayerCard
	{
		//기본
		간파,
		치명,
		치명_패러독스,
		시간가속,
		숨을수없는숙명,

		//커먼
		도플갱어,
		공간팽창,
		스펠브레이크,

		//언커먼
		초침멈추기,
		운명절단,
		미래예지,
		양자얽힘,
		차원격리,
		야바위,
		시간선붕괴,
		세계속이기,
		가능성개화,
		효율증가,

		//레어
		고대의회중시계,
		체크메이트,
		파멸의예언,
		존재확률수정,
		대혼란,
		데자뷰,
		평행세계,

		//커먼
		도플갱어_패러독스,
		공간팽창_패러독스,
		스펠브레이크_패러독스,

		//언커먼
		초침멈추기_패러독스,
		운명절단_패러독스,
		미래예지_패러독스,
		양자얽힘_패러독스,
		차원격리_패러독스,
		야바위_패러독스,
		시간선붕괴_패러독스,
		세계속이기_패러독스,
		가능성개화_패러독스,

		//레어
		체크메이트_패러독스,
		파멸의예언_패러독스,
		존재확률수정_패러독스,
		대혼란_패러독스,
		데자뷰_패러독스,
		평행세계_패러독스,
	};
}

enum class ArchivePlayCard
{
	사격,
	회피,
	다리걸기,
	난사,
	저격,
	플래쉬뱅,
	피버타임,
	빈틈포착,
	마탄의사수,
	아케인블래스트,
	차가운포옹,
	깨물기,
	야성해방,
	무자비,
	저돌맹진,
	필연적인공포,
	끝없는추적,
	멸망을부르는노래,
	공허의가호,
	징벌,
	시공의파동,
	엔진과부하,
	말살,
	기어체인지,
};

enum class ArchiveFateCard
{
	간파,
	치명,
	시간가속,
	숨을수없는숙명,
	도플갱어,
	공간팽창,
	스펠브레이크,
	초침멈추기,
	운명절단,
	미래예지,
	양자얽힘,
	차원격리,
	야바위,
	시간선붕괴,
	세계속이기,
	가능성개화,
	효율증가,
	고대의회중시계,
	체크메이트,
	파멸의예언,
	존재확률수정,
	대혼란,
	데자뷰,
	평행세계
};