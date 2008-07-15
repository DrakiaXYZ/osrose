/*
    Rose Online Server Emulator
    Copyright (C) 2006,2007 OSRose Team http://www.dev-osrose.com

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

    depeloped with Main erose/hrose source server + some change from the original eich source
*/
#ifndef __ROSE_MAP__
#define __ROSE_MAP__
#include "worldserver.h"
#include "player.h"
#include "character.h"
#include "worldmonster.h"
#include "datatypes.h"

//LMATEST
class CMonster;

class CMap
{
    public:
        CMap( );
        ~CMap( );

        bool AddPlayer( CPlayer* player );
        bool RemovePlayer( CPlayer* player, bool clearobject=true );

    CMonster* AddMonster( UINT montype, fPoint position,  UINT owner=0, CMDrops* MonsterDrop=NULL, CMDrops* MapDrop=NULL, UINT spawnid=0, bool GetDropData=false );
    bool DeleteMonster( CMonster*, bool clearobject=false, UINT i=0 );
    bool AddDrop( CDrop* drop );
    bool DeleteDrop( CDrop* drop );
    bool AddNPC( CNPC* npc );
    bool DeleteNPC( CNPC* npc );

    CMonster* ConverToMonster( CMonster* monster, UINT newmonttype, bool heal=true );
    CMonster* ConverToMonster( CNPC* npc, UINT newmonttype );

    bool TeleportPlayer( CPlayer* player, fPoint coord, bool TelePassenger=true );

    CRespawnPoint* GetNearRespawn( CPlayer* player );
    CRespawnPoint* GetFirstRespawn( );

    CCharacter* GetCharInMap( unsigned int id );
    CPlayer* GetPlayerInMap( UINT id );
    CMonster* GetMonsterInMap( UINT id );
    CPlayer* GetCharIDInMap( UINT id );
    CDrop* GetDropInMap( UINT id );
    CNPC* GetNPCInMap( UINT id );
    CNPC* CMap::GetNPCInMapQSD( UINT id );
    void UpdateTime( );
    void CleanDrops( );
    void RespawnMonster( );
    bool IsNight( );

    UINT id;           // id from map
    UINT dayperiod;    // duration of 1 day
    UINT morningtime;  // morning start time
    UINT daytime;      // day start time
    UINT eveningtime;  // evening start time
    UINT nighttime;    // nighttime start time
    UINT ghost;        // ghosttime?
    BYTE allowpvp;     // pvp allowed?
    bool allowpat;     // pat allowed?

    //LMA: Union slaughter (map 8)
    bool is_union_fired;  //LMA: is union slaughter on?
    time_t utime_end;   //LMA: When ends Union Slaughter?
    time_t utime_begin;  //LMA: when begins Union Slaughter?
    int nb_kills[8];     //LMA: nb killed by this union
    int nb_killed[8];     //LMA: how many times this union has been killed
    bool us_loop;   //LMA: does the US loop?
    int us_duration;    //LMA: duration of US (minutes)
    int us_delay_loop;  //LMA: delay between 2 US (minutes)

    //LMA: Union War (map 9)
    bool is_uw_fired;     //LMA: UW started?
    bool sunsetkilled;    //LMA: UW
    bool sunrisekilled;   //LMA: UW
    bool sunsetspawned;   //LMA: UW
    bool duskkilled;      //LMA: UW
    time_t uw_end;   //LMA: When ends Union war?
    time_t uw_begin;  //LMA: when begins Union war?
    bool uw_loop;   //LMA: does the UW loop?
    int uw_duration;    //LMA: duration of UW (minutes)
    int uw_delay_loop;  //LMA: delay between 2 UW (minutes)
    int announce_done;  //LMA: Announce done?
    UINT npc_id;      //LMA: NPC client ID for UW.
    int defenders;    //LMA: who attacks?
    int attackers;    //LMA: who defends?


    //LMA BEGIN
    //20070621-211100
    //For CF Mode 1
    UINT is_cf;        //is this a cf map (for jelly beans)...
    UINT id_temp_mon;        //id of the temporary monster (before the jelly bean or another one)
    UINT id_def_mon;        //id of the mon with great Xp
    UINT min_lvl;        //minimum lvl for cf
    UINT mon_lvl;        //lvl of the mob (used for exp calculation according to player's level)
    UINT mon_exp;        //exp of the mob
    UINT percent;        //% of luck summoning a monster
    //LMA END

    // Time values
    UINT MapTime;      // Past time in this map
    clock_t LastUpdate;// Last time update in the map
    UINT CurrentTime;  // 0 = morning | 1 = day  | 2 = evening | 3 = night | 4+ = invalid

    vector<CRespawnPoint*>	    RespawnList;	  // RespawnZones List
    vector<CSpawnArea*>	        MonsterSpawnList; // Monster spawn in this map
#ifdef USEIFO
    vector<CMobGroup*>          MobGroupList; // Spawn "Zones"
#endif
    vector<CMonster*>           MonsterList;      // Monster List in this map
  	vector<CDrop*>			    DropsList;				// Droped Items
    vector<CPlayer*>            PlayerList;       // Client list in this map;
    vector<CNPC*>               NPCList;          // NPC in this map
    vector<CTeleGate*>		    TeleGateList;	  // Telegates from this map
    vector<CCustomGate*>        CustomGateList;   //Custom telegate list
    vector<CCustomEvent*>       CustomEventList;  //Custom events list

    pthread_mutex_t MonsterMutex, DropMutex;
};

#endif
