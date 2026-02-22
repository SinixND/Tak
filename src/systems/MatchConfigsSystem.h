#ifndef IG20260222205746
#define IG20260222205746

#include "MatchConfigs.h"

/// Valid boardWidths: 3 to 8
MatchConfigs getMatchConfigs( int const boardWidth );

/// Default configuration
MatchConfigs getDefaultMatchConfigs( void );

/// Returns total reserves per player
int getTotalPlayerReserves( MatchConfigs const matchConfigs );

#endif
