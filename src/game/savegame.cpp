//   ___________		     _________		      _____  __
//   \_	  _____/______   ____   ____ \_   ___ \____________ _/ ____\/  |_
//    |    __) \_  __ \_/ __ \_/ __ \/    \  \/\_  __ \__  \\   __\\   __\ 
//    |     \   |  | \/\  ___/\  ___/\     \____|  | \// __ \|  |   |  |
//    \___  /   |__|    \___  >\___  >\______  /|__|  (____  /__|   |__|
//	  \/		    \/	   \/	     \/		   \/
//  ______________________                           ______________________
//			  T H E   W A R   B E G I N S
//	   FreeCraft - A free fantasy real time strategy game engine
//
/**@name savegame.c	-	Save game. */
//
//	(c) Copyright 2001 by Lutz Sammer, Andreas Arens
//
//	FreeCraft is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published
//	by the Free Software Foundation; either version 2 of the License,
//	or (at your option) any later version.
//
//	FreeCraft is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	$Id$

//@{

/*----------------------------------------------------------------------------
--	Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <time.h>

#include "freecraft.h"

#include "icons.h"
#include "ui.h"
#include "construct.h"
#include "unittype.h"
#include "unit.h"
#include "upgrade.h"
#include "depend.h"
#include "interface.h"
#include "missile.h"
#include "tileset.h"
#include "map.h"
#include "player.h"

#include "ccl.h"

/*----------------------------------------------------------------------------
--	Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
--	Functions
----------------------------------------------------------------------------*/

/**
**	Save a game to file.
**
**	@param filename	File name to be stored.
**
**	@note	Later we want to store in a more compact binary format.
*/
global void SaveGame(const char* filename)
{
    time_t now;
    FILE* file;

    file=fopen(filename,"wb");
    if( !file ) {
	fprintf(stderr,"Can't save to `%s'\n",filename);
	return;
    }

    fprintf(file,";;; -----------------------------------------\n");
    fprintf(file,";;; Save file generated by FreeCraft Version " VERSION "\n");
    fprintf(file,";;;\thttp://FreeCraft.Org\n");
    time(&now);
    fprintf(file,";;;\tDate: %s",ctime(&now));
    fprintf(file,";;;\tMap: %s\n",TheMap.Description);
    fprintf(file,";;; -----------------------------------------\n\n");

    SaveIcons(file);
    SaveCursors(file);
    // SaveUI(file);
    SaveConstructions(file);
    SaveUnitTypes(file);
    SaveUpgrades(file);
    SaveDependencies(file);
    SaveButtons(file);
    SaveMissileTypes(file);
    SaveTileset(file);
    SavePlayers(file);
    SaveMap(file);
    SaveUnits(file);
    SaveSelections(file);
    SaveGroups(file);
    SaveMissiles(file);

    // FIXME: find all state information which must be saved.

    fclose(file);
}

/**
**	Test function for the later save functions.
*/
global void SaveAll(void)
{
    SaveGame("save_file_of_freecraft.ccl");
}

//@}
