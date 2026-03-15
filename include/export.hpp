#pragma once

#ifdef GEODE_IS_WINDOWS
	#ifdef NWO5_SILLY_API_EXPORTING
		#define	SILLY_API_DLL __declspec(dllexport)
	#else
		#define	SILLY_API_DLL __declspec(dllimport)
	#endif
#else
	#define	SILLY_API_DLL __attribute__((visibility("default")))
#endif