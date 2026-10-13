// GameType.cpp -- the time-of-day and weather name tables (Zero Hour's
// Common/System/GameType.cpp). Native .data VA DBE958..DBE980: TimeOfDayNames
// holds six labels and a null, WeatherNames two labels and a null.
// BFME2 appends INTERPOLATE to Zero Hour's time-of-day names (retail target
// fact). Retail consumers: the INI water and time-of-day parsers (0x00200BEB,
// 0x000C4BAE), the camera-marker parsers (0x000CF873, 0x000D06C6) and the
// TimeOfDay/Weather entries of the GlobalData FieldParse table at VA BE8520.

char *TimeOfDayNames[] =
{
	"NONE",
	"MORNING",
	"AFTERNOON",
	"EVENING",
	"NIGHT",
	"INTERPOLATE",

	0
};

char *WeatherNames[] =
{
	"NORMAL",
	"SNOWY",

	0
};
