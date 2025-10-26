#ifndef DOOMRPG_H__
#define DOOMRPG_H__

#ifndef __BYTEBOOL__
#define __BYTEBOOL__
#ifdef __aarch64__
#include <switch/types.h>
#include <switch/runtime/pad.h>
#endif
typedef enum { false_f, true_t } boolean;
typedef unsigned char byte;
#endif

#define MAXCHAR ((char)0x7f)
#define MAXSHORT ((short)0x7fff)
#define MAXINT	((int)0x7fffffff)	// max pos 32-bit int 
#define MAXLONG ((long)0x7fffffff)

#define MINCHAR ((char)0x80)
#define MINSHORT ((short)0x8000)
#define MININT 	((int)0x80000000)	// max negative 32-bit integer
#define MINLONG ((long)0x80000000)

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CLAMP(x,min,max) MIN(max, MAX(min,x))

#ifndef NULL
#define	NULL	0
#endif

#define KEYBINDS_MAX 10
#define IS_MOUSE_BUTTON			0x10000
#define IS_CONTROLLER_BUTTON	0x20000
typedef struct keyMapping_s
{
	int avk_action;
	int keyBinds[KEYBINDS_MAX];
} keyMapping_t;

extern keyMapping_t keyMapping[12];
extern keyMapping_t keyMappingTemp[12];
extern keyMapping_t keyMappingDefault[12];

enum _AVKType {
	AVK_UNDEFINED = 0,	// hex 0xE010; dec 57360
	AVK_FIRST = 1,		// hex 0xE020; dec 57376

	AVK_0,		// hex 0xE021; dec 57377
	AVK_1,		// hex 0xE022; dec 57378
	AVK_2,		// hex 0xE023; dec 57379
	AVK_3,		// hex 0xE024; dec 57380
	AVK_4,		// hex 0xE025; dec 57381
	AVK_5,		// hex 0xE026; dec 57382
	AVK_6,		// hex 0xE027; dec 57383
	AVK_7,		// hex 0xE028; dec 57384
	AVK_8,		// hex 0xE029; dec 57385
	AVK_9,		// hex 0xE02A; dec 57386
	AVK_STAR,	// hex 0xE02B; dec 57387
	AVK_POUND,	// hex 0xE02C; dec 57388

	AVK_POWER,	// hex 0xE02D; dec 57389
	AVK_END,	// hex 0xE02E; dec 57390
	AVK_SEND,	// hex 0xE02F; dec 57391
	AVK_CLR,	// hex 0xE030; dec 57392

	AVK_UP,		// hex 0xE031; dec 57393
	AVK_DOWN,	// hex 0xE032; dec 57394
	AVK_LEFT,	// hex 0xE033; dec 57395
	AVK_RIGHT,	// hex 0xE034; dec 57396
	AVK_SELECT,	// hex 0xE035; dec 57397

	AVK_SOFT1,	// hex 0xE036; dec 57398
	AVK_SOFT2,	// hex 0xE037; dec 57399

	// New Types Only on port
	AVK_MENUOPEN,
	AVK_AUTOMAP,
	AVK_MOVELEFT,
	AVK_MOVERIGHT,
	AVK_PREVWEAPON,
	AVK_NEXTWEAPON,
	AVK_PASSTURN,

	// New Flags Menu Only on port
	AVK_MENU_UP	=			0x40,
	AVK_MENU_DOWN =			0x80,
	AVK_MENU_PAGE_UP =		0x100,
	AVK_MENU_PAGE_DOWN =	0x200,
	AVK_MENU_SELECT =		0x400,
	AVK_MENU_OPEN =			0x800
};

enum _GameController {
	CONTROLLER_BUTTON_INVALID = -1,
	CONTROLLER_BUTTON_A,			// Gamepad A
	CONTROLLER_BUTTON_B,			// Gamepad B
	CONTROLLER_BUTTON_X,			// Gamepad X
	CONTROLLER_BUTTON_Y,			// Gamepad Y
	CONTROLLER_BUTTON_BACK,			// Back
	CONTROLLER_BUTTON_START,		// Start
	CONTROLLER_BUTTON_LEFT_STICK,	// Left Stick
	CONTROLLER_BUTTON_RIGHT_STICK,	// Right Stick
	CONTROLLER_BUTTON_LEFT_BUMPER,	// Left Bumper
	CONTROLLER_BUTTON_RIGHT_BUMPER,	// Right Bumper
	CONTROLLER_BUTTON_DPAD_UP,		// D-Pad Up
	CONTROLLER_BUTTON_DPAD_DOWN,	// D-Pad Down
	CONTROLLER_BUTTON_DPAD_LEFT,	// D-Pad Left
	CONTROLLER_BUTTON_DPAD_RIGHT,	// D-Pad Right
	CONTROLLER_BUTTON_LAXIS_UP,		// L-Axis Up
	CONTROLLER_BUTTON_LAXIS_DOWN,	// L-Axis Down
	CONTROLLER_BUTTON_LAXIS_LEFT,	// L-Axis Left
	CONTROLLER_BUTTON_LAXIS_RIGHT,	// L-Axis Right
	CONTROLLER_BUTTON_RAXIS_UP,		// R-Axis Up
	CONTROLLER_BUTTON_RAXIS_DOWN,	// R-Axis Down
	CONTROLLER_BUTTON_RAXIS_LEFT,	// R-Axis Left
	CONTROLLER_BUTTON_RAXIS_RIGHT,	// R-Axis Right
	CONTROLLER_BUTTON_LEFT_TRIGGER,	// Left Trigger
	CONTROLLER_BUTTON_RIGHT_TRIGGER,// Right Trigger
	CONTROLLER_BUTTON_MAX
};

enum _MOUSE {
	MOUSE_BUTTON_INVALID = -1,
	MOUSE_BUTTON_LEFT,			// Mouse Left
	MOUSE_BUTTON_MIDDLE,		// Mouse Middle
	MOUSE_BUTTON_RIGHT,			// Mouse Right
	MOUSE_BUTTON_X1,			// Mouse X1
	MOUSE_BUTTON_X2,			// Mouse X2
	MOUSE_BUTTON_WHELL_UP,		// Mouse Wheel Up
	MOUSE_BUTTON_WHELL_DOWN,	// Mouse Wheel Down
	MOUSE_BUTTON_MOTION_UP,		// Mouse Motion Up
	MOUSE_BUTTON_MOTION_DOWN,	// Mouse Motion Down
	MOUSE_BUTTON_MOTION_LEFT,	// Mouse Motion Left
	MOUSE_BUTTON_MOTION_RIGHT,	// Mouse MotionRight
	MOUSE_BUTTON_MAX
};

#define LINE_FLAG_RENDER_SPRITE_TWO_SIDED 1 // (internal) rendering both sides of the sprite
#define LINE_FLAG_RENDER_SPRITE 2 // (internal) rendering sprite as line
#define LINE_FLAG_DOORLERP 4 // Door
#define LINE_FLAG_EAST_SOUTH 8 // Shift East or South
#define LINE_FLAG_WEST_NORTH 16 // Shift West or North
#define LINE_FLAG_HIDDEN 32 // Hidden
#define LINE_FLAG_DOOROPEN 64 // (internal) door open/close
#define LINE_FLAG_AUTOMAP_VISIBLE 128  // (internal) automap visible
#define LINE_FLAG_VERTICAL 256 // Shift vertical
#define LINE_FLAG_HORIZONTAL 512 // Shift horizontal
#define LINE_FLAG_DOORLOCKED 1024 // Locked door
#define LINE_FLAG_SOUTH 2048 // South - facing wall
#define LINE_FLAG_NORTH 4096 // North - facing wall
#define LINE_FLAG_WEST 8192 // West - facing wall
#define LINE_FLAG_EAST 16384 // East - facing wall
#define LINE_FLAG_FLIP_HORIZONTAL 32768 // Flip texture horizontally

#define SPRITE_FLAG_HIDDEN 65536 // Hidden
#define SPRITE_FLAG_WALL 131072	// Wall
#define SPRITE_FLAG_TILE 262144	// Wall texture
#define SPRITE_FLAG_NORTH 524288 // North - facing
#define SPRITE_FLAG_SOUTH 1048576 // South - facing
#define SPRITE_FLAG_EAST 2097152 // East - facing
#define SPRITE_FLAG_WEST 4194304 // West - facing
#define SPRITE_FLAG_DECAL 8388608 // Wall decal
#define SPRITE_FLAG_NOENTITY 16777216 // No entity
#define SPRITE_FLAG_FLIP_WALL 33554432 // Flip wall

#define SPRITE_FLAG_FOUR_ITEMS 67108864			// (internal) draw four items
#define SPRITE_FLAG_TWO_SIDED 134217728			// (internal) wall double sided
#define SPRITE_FLAG_AUTOMAP_VISIBLE 268435456	// (internal) automap visible
#define SPRITE_FLAG_0x20000000 536870912		// (internal) 
#define SPRITE_FLAG_0x40000000 1073741824		// (internal) 
#define SPRITE_FLAG_AUTO_ANIMATE 2147483648		// (internal) automatic missile animation

#define SPRITE_FLAGS_ORIENTED (SPRITE_FLAG_NORTH | SPRITE_FLAG_SOUTH | SPRITE_FLAG_EAST | SPRITE_FLAG_WEST)
#define SPRITE_FLAGS_HORIZONTAL = (SPRITE_FLAG_NORTH| SPRITE_FLAG_SOUTH)
#define SPRITE_FLAGS_VERTICAL (SPRITE_FLAG_EAST | SPRITE_FLAG_WEST)

// Doom Canvas
#define BIT_AM_WALL 1
#define BIT_AM_SECRET 2
#define BIT_AM_ENTRANCE 4
#define BIT_AM_EVENTS 8
#define BIT_AM_VISITED 16

#define BYTE_CODE_ID 0
#define BYTE_CODE_ARG1 1
#define BYTE_CODE_ARG2 2
#define BYTE_CODE_MAX 3

#define CHANGEMAP_FADE_BIT = 128;
#define CHANGEMAP_SHOWSTAT_SHIFT 31
#define CHANGEMAP_SHOWSTATS_BIT (1 << CHANGEMAP_SHOWSTAT_SHIFT)

// Game
#define EVENT_FLAG_BLOCKINPUT 1
#define MCODE_EXEC_ENTER_NORTH 1
#define MCODE_EXEC_ENTER_EAST 2
#define MCODE_EXEC_ENTER_SOUTH 4
#define MCODE_EXEC_ENTER_WEST 8
#define MCODE_EXEC_EXIT_SOUTH 16
#define MCODE_EXEC_EXIT_WEST 32
#define MCODE_EXEC_EXIT_NORTH 64
#define MCODE_EXEC_EXIT_EAST 128
#define MCODE_EXEC_TRIGGER 256
#define MCODE_FLAG_REMOVE 512

#define	FRACBITS    16
#define	FRACUNIT    (1<<FRACBITS)
#define	FRACMASK    (FRACUNIT-1)    // Named from PsyDoom (StationDoom)

typedef int fixed_t;

#define	RANDTABLESIZE	128

typedef struct Random_s
{
	byte	randTable[RANDTABLESIZE];
	int		nextRand;
} Random_t;

struct DoomCanvas_s;
struct Render_s;
struct Player_s;
struct Game_s;
struct EntityDefManager_s;
struct Combat_s;
struct Hud_s;
struct Menu_s;
struct MenuSystem_s;
struct ParticleSystem_s;
struct Sound_s;

typedef struct DoomRPG_s
{
	int				upTimeMs;
	struct Random_s	random;
	struct DoomCanvas_s*	doomCanvas;
	struct Render_s*		render;
	struct Player_s*		player;
	struct Game_s*			game;
	struct EntityDefManager_s*		entityDef;
	struct Combat_s*		combat;
	struct Hud_s*			hud;
	struct Menu_s*			menu;
	struct MenuSystem_s*	menuSystem;
	struct ParticleSystem_s* particleSystem;
	struct Sound_s*			sound;

	boolean			graphSetCliping;
	int				memoryBeg;
	int				errorID;
	char			errorStr[64];
	boolean			closeApplet;
	int				imageMemory;
	char*			lang;
	unsigned char** sysStrings;
} DoomRPG_t;

typedef enum
{
	STRING_LOADING=0,  //Loading...
	STRING_SAVING, //Saving...
	STRING_TOOKDAMAGEDIED, //%s took %d damage! %s died!
	STRING_TOOKDAMAGE, //%s took %d damage!
	STRING_FIRECLEARED, //Fire cleared!
	STRING_TRAPPED, //Trapped!
	STRING_DOORCLEARED, //Door cleared!
	STRING_CASTSRAISE, //%s casts raise%c
	STRING_ATTACKS, //%s attacks%c
	STRING_DODGED, //Dodged!
	STRING_GAINEDARMOR, //Gained %d armor
	STRING_GAINEDHEALTH, //Gained %d health
	STRING_GAINEDXP, //Gained %d XP!
	STRING_LEVELUP, //Level up!
	STRING_N, //|
	STRING_CURLEVEL, //Level: %d|
	STRING_MAXHEALTH, //Max Health: +%d|
	STRING_MAXARMOR, //Max Armor: +%d|
	STRING_MAXDEFENSE, //Defense: +%d|
	STRING_MAXSTRENGTH, //Strength: +%d|
	STRING_MAXAGILITY, //Agility: +%d|
	STRING_MAXACCURACY, //Accuracy: +%d|
	STRING_HEALTHRESTORED, //|Health restored.
	STRING_BERSERKEREXPIRED, //Berserker expired!
	STRING_NOAMMO, //Not enough ammo!
	STRING_CRIT, //Crit!
	STRING_DOGTOOK, //Dog took
	STRING_DAMAGE, // damage!
	STRING_DOGDIED, // Dog died!
	STRING_NEARDEATH, //Near Death!
	STRING_LOWHEALTH, //Low Health!
	STRING_ARMORGONE, //Armor Gone!
	STRING_INSUHEALTH, //Insufficient health!
	STRING_INSUARMOR, //Insufficient armor!
	STRING_INSUFUNDS, //Insufficient funds!
	STRING_INSUXP, //Insufficient XP!
	STRING_NODOGRANGE, //No dog within range
	STRING_BADTARGET, //Bad target for Dog Collar
	STRING_WONTFIT, //Dog Collar won't fit %s%c
	STRING_BERSERKERACITVE, //Berserker activated!
	STRING_REVIVED, //%s is revived!
	STRING_RAISEF, //Raise failed!
	STRING_ATTACKING, //Attacking%c %s
	STRING_LASTSHOT, //(Last shot!)
	STRING_ONESHOT, //(1 shot left!)
	STRING_TWOSHOTS, //(2 shots left!)
	STRING_THREESHOTS, //(3 shots left!)
	STRING_KRONOSTELEP, //Kronos Teleported!
	STRING_MISSED, //Missed!
	STRING_NOEFFECT, //No effect!
	STRING_EMPTY, //
	STRING_DAMAGE2, //%s%d damage!
	STRING_DIED, // %s died!
	STRING_HITFORDAM, //Hit %s for %d damage!
	STRING_DESTROYED, //%s destroyed!
	STRING_MAXCREDITS, //Credits at maximum
	STRING_ARMORATMAX, //Armor at maximum
	STRING_HEALTHATMAX, //Health at maximum
	STRING_GOT, //Got %s
	STRING_CANTHOLDMORE, //Can't hold more %ss
	STRING_GOTAXE, //You got the Axe!|Zombies beware...
	STRING_GOTFIRE, //You got the Fire|Extinguisher! It|uses halon can-|isters to put out|fires.
	STRING_GOTSHOT, //You got the|Shotgun!
	STRING_GETCHAIN, //You got the|Chaingun! Precise|and deadly, but|it's an ammo hog.
	STRING_GETSUPSHOT, //You got the Super|Shotgun! Fierce!
	STRING_GOTROCKET, //You got the|Rocket Launcher!|w00t!
	STRING_GOTPLASMA, //You got the|Plasma Gun!
	STRING_GOTBFG, //You got the BFG!|We could tell you|what BFG stands|for, but this is|a family game.
	STRING_BURNS, //It burns!
	STRING_REALBURNS, //It really burns!!
	STRING_NOTES, //%s notes...
	STRING_BACK, //Back
	STRING_ITEMS, //ITEMS
	STRING_SMMED, //Sm Medkit
	STRING_LGMED, //Lg Medkit
	STRING_SPHERE, //Soul Sphere
	STRING_BERSERK, //Berserker
	STRING_AMMO, //AMMO
	STRING_CANS, //10x Hal. Cans
	STRING_BULLETS, //10x Bullets
	STRING_SHELLS, //10x Shells
	STRING_CELLS, //10x Cells
	STRING_ROCKETS, //3x Rockets
	STRING_STATS, //STATS
	STRING_PACC, //+1 Accuracy
	STRING_PAGI, //+1 Agility
	STRING_PSTR, //+1 Strength
	STRING_PDEF, //+1 Defense
	STRING_YES, //Yes
	STRING_NO, //No
	STRING_PLAYER, //PLAYER
	STRING_HEALTH, //Health:
	STRING_ARMOR, //Armor:
	STRING_CREDITS, //Credits:
	STRING_LEVEL, //Level:
	STRING_XP, //XP:
	STRING_STARTGAME, //Start Game
	STRING_OPTIONS, //Options
	STRING_HELP, //Help/About
	STRING_EXIT, //Exit
	STRING_ISEXIT, //Exit Doom RPG?
    STRING_ERASE, //Erase saved game?
	STRING_AREYOUSURE, //Are you sure?
	STRING_CONTINUE, //Continue
	STRING_NEWGAME, //New Game
	STRING_VIDEO, //Video
	STRING_INPUT, //Input
	STRING_SOUND, //Sound
	STRING_SOUNDON, //Enable sounds?
	STRING_COMPLETED, //Completed!
	STRING_PRESSOKTO, //Press OK to
	STRING_PRESSCONT, //continue
	STRING_GOTOJ, //Go To Junction
	STRING_MAINMENU, //Main Menu
	STRING_QUITTOMAIN, //Quit to Main Menu?
	STRING_QUIT, //Quit
	STRING_CANCEL, //Cancel
	STRING_NOTEBOOK, //Notebook
	STRING_RESUME, //Resume Game
	STRING_INVENTORY, //Inventory
	STRING_SAVEGAME, //Save Game
	STRING_LOADGAME, //Load Game
	STRING_AUTOMAP, //Automap
	STRING_STATUS, //Status
	STRING_NOSAVE, //Don't Save
	STRING_WEAPONS, //WEAPONS
	STRING_OTHER, //OTHER
	STRING_GKEY, //Green Key
	STRING_YKEY, //Yellow Key
	STRING_BKEY, //Blue Key
	STRING_RKEY, //Red Key
	STRING_CONFIRMUSE, //Use %s?
	STRING_HFULL, //Health full.
	STRING_HANDA, //Health and armor
	STRING_FULL, //full.
	STRING_TRYAGAIN, //Try again?
	STRING_RETRY, //Retry Sector
	STRING_TWT, //This will take
	STRING_YTJ, //you to Junction
	STRING_BT2, //before the 2nd
	STRING_IAS, //invasion. Are
	STRING_USQ, //you sure?
	STRING_WYL, //Would you like
	STRING_TMA, //to make a pur-
	STRING_CSS, //chase?
	STRING_NEC, //You do not have
	STRING_ECS, //enough credits!
	STRING_YHT, //You have too
	STRING_MAS, //many already!
	STRING_BUY, //Buy %s?
	STRING_LGS, //Load Game?
	STRING_NSG, //No Saved Game
	STRING_MORE, //More
	STRING_NTU, //Nothing to use
	STRING_TPS, //Turn passed.
	STRING_RANKM, //Master
	STRING_YHF, //You have found\nevery secret and\nkilled every mon-\nster in the game.\nThis calls for a\ncelebration!\nPlease visit:\n\ndoomrpg.com/sarge\n
	STRING_RANKB, //Baddy
	STRING_NJT, //Nice job. There\nis only a little\nmore you need to\ndo to achieve\nMaster rank. We\nhave a parade\nfor you at:\n\ndoomrpg.com/blues\n
	STRING_RANKA, //Average
	STRING_YBT, //You've beaten the\ndemons from Hell,\nbut we've seen\nbetter. Find out\nmore by visiting:\n\ndoomrpg.com/spire\n
	STRING_RANKC, //Chump
	STRING_YFS, //You've finished\nthe game, barely.\nThere's still much\nto discover. For a\nlittle inspiration\nto do better next\ntime, visit:\n\ndoomrpg.com/hound\n
	STRING_CSN, //Congratulations!\nYou've shut down\nthe portal to\nHell and stopped\nthe demonic inv-\nasion.\n\nRank: %s
	STRING_STORYA, //You have been\ndispatched in re - \nsponse to a dis - \ntress call from\nUnion Aerospace\nCorporation's re-\nsearch facility\non Mars. The base\nis under attack
	STRING_STORYB, //by an unknown\nforce and your\nmission is to ac-\nquire intelli-\ngence and neu-\ntralize the\nthreat.
	STRING_STORYC, //Insertion com-\nplete. For fur-\nther instruc-\ntions, rendezvous\nwith the other\nMarines at Junc-\ntion. Expect\nheavy resistance.\nGood luck!
	STRING_GSS, //Game Saved
	STRING_GLS, //Game Loaded
	STRING_CORRECT, //Correct code!
	STRING_INVALID, //Invalid code!
	STRING_PROCESSING, //Processing...
	STRING_JAM, //(Just a moment!)
	STRING_YOUCAPT, //You captured|the %s!|
	STRING_SORRY, //Sorry!
	STRING_FOUNDSEC, //Found Secret!
	STRING_DEFENSE, //Defense:
	STRING_STRENGTH, //Strength:
	STRING_AGIL, //Agility:
	STRING_ACCUR, //Accuracy:
	STRING_THISSEC, //THIS SECTOR
	STRING_TIME, //Time:
	STRING_SECRETS, //Secrets:
	STRING_MONSTERS, //Monsters:
	STRING_MOVES, //Moves:
	STRING_XPG, //XP Gained:
	STRING_OVERA, //OVERALL
	STRING_DEATHS, //Deaths:
	STRING_HUNKILLS, //100% KILLS
	STRING_NONE, //None
	STRING_HUNSECRETS, //%c 100%% SECRETS %c
	STRING_LOADINGJ, //Loading Junction
	STRING_LOADINGSEC, //Loading Sector
	STRING_E, //E
	STRING_W, //W
	STRING_S, //S
	STRING_N2 //N
} systemStrings;

typedef struct Image_s
{
	SDL_Texture* imgBitmap;
	int	width;
	int	height;
	boolean isTransparentMask;
} Image_t;

//extern DoomRPG_t *doomRpg;

fixed_t	DoomRPG_FixedMul(fixed_t a, fixed_t b);
fixed_t	DoomRPG_FixedDiv(fixed_t a, fixed_t b);
fixed_t	DoomRPG_FixedDiv2(fixed_t a, fixed_t b);

void DoomRPG_Error(const char* fmt, ...);
unsigned int DoomRPG_GetTimeMS(void);
unsigned int DoomRPG_GetUpTimeMS(void);
int DoomRPG_freeMemory(void);

int DoomRPG_getEventKey(int mouse_Button,
#ifdef __aarch64__
PadState pad
#else
const Uint8* state
#endif
);
void DoomRPG_setDefaultBinds(DoomRPG_t* doomrpg);
void DoomRPG_setBind(DoomRPG_t* doomrpg, int mouse_Button, const Uint8* state);


int DoomRPG_Init(void);
void DoomRPG_FreeAppData(DoomRPG_t* doomrpg);

void DoomRPG_createImage(DoomRPG_t* doomrpg, const char* resourceName, boolean isTransparentMask, Image_t* img);
void DoomRPG_createImageBerserkColor(DoomRPG_t* doomrpg, const char* resourceName, boolean isTransparentMask, Image_t* img);
void DoomRPG_freeImage(DoomRPG_t* doomrpg, Image_t* image);

byte* DoomRPG_fileOpenRead(DoomRPG_t* doomrpg, const char* resourceName);
void DoomRPG_setErrorID(DoomRPG_t* doomrpg, int ID);
int DoomRPG_getErrorID(DoomRPG_t* doomrpg);
byte DoomRPG_byteAtNext(byte* data, int* posData);
byte DoomRPG_byteAt(byte* data, int posData);
short DoomRPG_shortAtNext(byte* data, int* posData);
short DoomRPG_shortAt(byte* data, int posData);
int DoomRPG_intAtNext(byte* data, int* posData);
int DoomRPG_intAt(byte* data, int posData);
short DoomRPG_shiftCoordAt(byte* data, int* posData);

void DoomRPG_loopGame(DoomRPG_t* doomrpg);

void DoomRPG_setClipFalse(DoomRPG_t* doomrpg);
void DoomRPG_setClipTrue(DoomRPG_t* doomrpg, int x, int y, int w, int h);
void DoomRPG_setColor(DoomRPG_t* doomrpg, int color);
void DoomRPG_flushGraphics(DoomRPG_t* doomrpg);
void DoomRPG_clearGraphics(DoomRPG_t* doomrpg);
void DoomRPG_drawRect(DoomRPG_t* doomrpg, int x, int y, int w, int h);
void DoomRPG_fillRect(DoomRPG_t* doomrpg, int x, int y, int w, int h);
void DoomRPG_drawCircle(DoomRPG_t* doomrpg, int x, int y, int r);
void DoomRPG_fillCircle(DoomRPG_t* doomrpg, int x, int y, int r);
void DoomRPG_drawLine(DoomRPG_t* doomrpg, int x1, int y1, int x2, int y2);
void DoomRPG_setFontColor(DoomRPG_t* doomrpg, int color); // New

void DoomRPG_setRand(Random_t* rand);
byte DoomRPG_randNextByte(Random_t* rand);
int DoomRPG_randNextInt(Random_t* rand);

void DoomRPG_notifyDestroyed(DoomRPG_t* doomrpg);

void File_writeBoolean(SDL_RWops* rw, int i);
void File_writeByte(SDL_RWops* rw, int i);
void File_writeShort(SDL_RWops* rw, int i);
void File_writeInt(SDL_RWops* rw, int i);
void File_writeLong(SDL_RWops* rw, int i);

boolean File_readBoolean(SDL_RWops* rw);
int File_readByte(SDL_RWops* rw);
int File_readShort(SDL_RWops* rw);
int File_readInt(SDL_RWops* rw);
int File_readLong(SDL_RWops* rw);
bool file_exists(const char *path);

#endif
