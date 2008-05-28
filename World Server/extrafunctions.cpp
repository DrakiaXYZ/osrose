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
#include "worldserver.h"

// Build Item Head
unsigned CWorldServer::BuildItemHead( CItem thisitem )
{
	if (thisitem.count==0) return 0;
    return ( ( thisitem.itemnum & 0x7ffffff ) << 5 ) | ( thisitem.itemtype & 0x1f );
}

// Build Item Data
unsigned CWorldServer::BuildItemData( CItem thisitem )
{
	if (thisitem.count==0) return 0;
	if ( thisitem.itemtype >= 10 && thisitem.itemtype <= 13 )
    {
		return thisitem.count;
	}
    else
    {
		unsigned part1 = (thisitem.refine>>4) << 28;
		unsigned part2 = (thisitem.appraised?1:0) << 27;
		unsigned part3 = (thisitem.socketed?1:0) << 26;
		unsigned part4 = (thisitem.lifespan*10) << 16;
		unsigned part5 = thisitem.durability << 9;
		unsigned part6 = thisitem.stats;
		unsigned part7 = thisitem.gem;
		return part1 | part2 | part3 | part4 | part5 | part6 | part7;
	}
}

// Get Item By Head and Data (Coded by Caali)
CItem CWorldServer::GetItemByHeadAndData( unsigned head, unsigned data )
{
    CItem thisitem;

    //Get info from ItemHead
    thisitem.itemnum = (head >> 5) & 0x7ffffff;
    head ^= (thisitem.itemtype & 0x7ffffff) << 5;
    thisitem.itemtype = head & 0x1f;

    //Get info from ItemData
    if( thisitem.itemtype >= 10 && thisitem.itemtype <= 13 ) //Stackable
    {
        thisitem.refine        = 0;
        thisitem.appraised    = 0;
        thisitem.socketed    = 0;
        thisitem.lifespan    = 100;
        thisitem.durability    = 40;
        thisitem.gem        = 0;
        thisitem.stats        = 0;
        thisitem.count        = (int)data;
    }
    else //Non-stackable
    {
        thisitem.refine = (data >> 28) << 4;
        data-=(thisitem.refine>>4) << 28;
        thisitem.appraised = ((data >> 27)==1)?true:false;
        data-=(thisitem.appraised?1:0) << 27;
        thisitem.socketed = ((data >> 26)==1)?true:false;
        data-=(thisitem.socketed?1:0) << 26;
        thisitem.lifespan = (data >> 16) / 10;
        data-=(thisitem.lifespan*10) << 16;
        thisitem.durability = data >> 9;
        data-=thisitem.durability << 9;
        thisitem.gem = data;
        data-=thisitem.gem;
        thisitem.count = 1;
    }
    return thisitem;
}


//----Build Item refine
unsigned CWorldServer::BuildItemRefine(CItem thisitem)
{
	if (thisitem.gem == 0)
		return ((thisitem.refine)*256);
	else
	{
		return (0xd00+(thisitem.gem-320)*4)+((thisitem.refine)*256);
	}
}

// Send a packet too all connected clients
void CWorldServer::SendToAll( CPacket* pak )
{
    for(UINT i=0;i<ClientList.size();i++)
    {
        CPlayer* otherclient = (CPlayer*) ClientList.at( i )->player;
        if (otherclient->client == NULL) continue;
        if (!otherclient->client->isActive) continue;

        if (otherclient->Session->inGame)
            otherclient->client->SendPacket( pak );
    }
}

void CWorldServer::SendToVisible( CPacket* pak, CPlayer* thisclient, bool dothisclient )
{
    for(UINT j=0;j<ClientList.size();j++)
    {
        CPlayer* otherclient = (CPlayer*) ClientList.at( j )->player;
        if(otherclient == NULL) continue;
        if(otherclient->client==NULL) continue;
        if(!otherclient->client->isActive) continue;
        if(!otherclient->Session->inGame) continue;

        if( IsVisible(thisclient, otherclient))
            otherclient->client->SendPacket( pak );
    }
    if(dothisclient && thisclient->client!=NULL && thisclient->client->isActive)
        thisclient->client->SendPacket( pak );
}

void CWorldServer::SendToVisible( CPacket* pak, CPlayer* thisclient, CPlayer* xotherclient )
{
    for(UINT j=0;j<ClientList.size();j++)
    {
		CPlayer* otherclient = (CPlayer*) ClientList.at( j )->player;
		if(otherclient == NULL) continue;
        if(otherclient==xotherclient) continue;
        if(otherclient->client==NULL) continue;
        if(!otherclient->client->isActive) continue;
        if(!otherclient->Session->inGame) continue;

        if( IsVisible(thisclient, otherclient))
            otherclient->client->SendPacket( pak );
    }
}

// -- MONSTER --
void CWorldServer::SendToVisible( CPacket* pak, CMonster* thismon, CDrop* thisdrop )
{
    CMap* map = MapList.Index[thismon->Position->Map];
    for(UINT i=0;i<map->PlayerList.size();i++)
    {
        CPlayer* otherclient = map->PlayerList.at(i);
        if(otherclient == NULL) continue;
        if(otherclient->client==NULL) continue;
        if(!otherclient->client->isActive) continue;
        if(!otherclient->Session->inGame) continue;

        if(IsVisible(otherclient,thismon))
            otherclient->client->SendPacket( pak );
        if(thisdrop!=NULL)
        {
            otherclient->VisibleDrops.push_back( thisdrop );
        }
    }
}

// -- CHARACTER --
void CWorldServer::SendToVisible( CPacket* pak, CCharacter* character, CDrop* thisdrop )
{
    if(character->IsPlayer( ))
    {
        SendToVisible( pak, (CPlayer*)character );
    }
    else
    if(character->IsMonster( ))
    {
        SendToVisible( pak, (CMonster*)character, thisdrop );
    }
}

// -- DROP --
void CWorldServer::SendToVisible( CPacket* pak, CDrop* thisdrop )
{
    CMap* map = MapList.Index[thisdrop->posMap];
    if(map == NULL) return;
    for(UINT i=0;i<map->PlayerList.size();i++)
    {
        CPlayer* otherclient = map->PlayerList.at(i);
        if (thisdrop == NULL || otherclient->client==NULL || !otherclient->client->isActive)
            continue;
        if( IsVisible(otherclient, thisdrop) )
            otherclient->client->SendPacket( pak );
    }
}

// Send a packet too all clients on the specified map
void CWorldServer::SendToMap( CPacket* pak, int mapid )
{
    CMap* map = MapList.Index[mapid];
    if(map==NULL) return;
    for(UINT i=0;i<map->PlayerList.size();i++)
    {
        CPlayer* otherclient = map->PlayerList.at(i);
        if (otherclient->client == NULL) continue;
        if (!otherclient->client->isActive) continue;
        if( otherclient->Session->inGame )
            otherclient->client->SendPacket( pak );
    }
}

// -----------------------------------------------------------------------------------------
// Check if an object is visible to a client
// -----------------------------------------------------------------------------------------
// -- CLIENT --
bool CWorldServer::IsVisible( CPlayer* thisclient, CPlayer* otherclient )
{
	for(unsigned j=0; j<thisclient->VisiblePlayers.size(); j++)
    {
		if (otherclient==thisclient->VisiblePlayers.at(j))
            return true;
	}
	return false;
}

// -- MOB --
bool CWorldServer::IsVisible( CPlayer* thisclient, CMonster* thismon )
{
	for(unsigned j=0; j<thisclient->VisibleMonsters.size(); j++)
    {
        //LMATEST
		//if (thismon==thisclient->VisibleMonsters.at(j)) return true;
		if (thismon->clientid==thisclient->VisibleMonsters.at(j)) return true;
	}
	return false;
}

// -- DROP --
bool CWorldServer::IsVisible( CPlayer* thisclient, CDrop* thisdrop )
{
	for(unsigned j=0; j<thisclient->VisibleDrops.size(); j++) {
		if (thisdrop==thisclient->VisibleDrops.at(j)) return true;
	}
	return false;
}

// -- NPC --
bool CWorldServer::IsVisible( CPlayer* thisclient, CNPC* thisnpc )
{
	for(unsigned j=0; j<thisclient->VisibleNPCs.size(); j++) {
		if (thisnpc==thisclient->VisibleNPCs.at(j)) return true;
	}
	return false;
}

// This function gets a new clientID for a npc, monster or mob
unsigned CWorldServer::GetNewClientID( )
{
	for (unsigned i=1; i<0xffff; i++)
    {
		if (ClientIDList[i]!=0 && time(NULL)-ClientIDList[i]>10)
        {
			ClientIDList[i] = 0;
			return i;
		}
	}

	return 0;
}

// This function will free our clientID
void CWorldServer::ClearClientID( unsigned int id )
{
	ClientIDList[id] = (unsigned)time(NULL);
}

// Search a drop by ID
CDrop* CWorldServer::GetDropByID( UINT id, UINT map )
{
    if(map!=0)
        return MapList.Index[map]->GetDropInMap( id );
	for(unsigned j=0; j<MapList.Map.size(); j++)
    {
		CDrop* thisdrop = MapList.Map.at(j)->GetDropInMap( id );
		if(thisdrop!=NULL)
		  return thisdrop;
	}
	return NULL;
}

// Search a Chest by ChestID
CChest* CWorldServer::GetChestByID( UINT id )
{
    for(UINT i=0;i<ChestList.size();i++)
    {
        CChest* chest = (CChest*) ChestList.at(i);
    if (chest->chestid == id)
            return chest;
    }
    return NULL;
}

// Search a Monster by ID
CMonster* CWorldServer::GetMonsterByID( UINT id, UINT map )
{
    if(map!=0)
        return MapList.Index[map]->GetMonsterInMap( id );
    for(UINT i=0;i<MapList.Map.size();i++)
    {
        CMonster* thismon = MapList.Map.at(i)->GetMonsterInMap( id );
        if(thismon!=NULL)
            return thismon;
    }
	return NULL;
}

// Search a Client by Username
CPlayer* CWorldServer::GetClientByUserName( char *username )
{
    for(UINT i=0;i<ClientList.size();i++)
    {
        CPlayer* thisclient = (CPlayer*) ClientList.at(i)->player;
		if (strcmp(thisclient->Session->username,username)==0)
            return thisclient;
	}
	return NULL;
}

// Get Client By ID
CPlayer* CWorldServer::GetClientByID( UINT id, UINT map )
{
    if(map!=0)
        return MapList.Index[map]->GetPlayerInMap( id );
    for(UINT i=0;i<ClientList.size();i++)
    {
        CPlayer* thisclient = (CPlayer*) ClientList.at(i)->player;
		if (thisclient->clientid==id)
            return thisclient;
	}
	return NULL;
}

// Search a Client by CharID
CPlayer* CWorldServer::GetClientByCID( UINT id, UINT map )
{
    if(map!=0)
        return MapList.Index[map]->GetCharIDInMap( id );
    for(UINT i=0;i<ClientList.size();i++)
    {
        CPlayer* thisclient = (CPlayer*) ClientList.at(i)->player;
		if (thisclient->CharInfo->charid==id)
            return thisclient;
	}
	return NULL;
}

// Seach a client by Charname
CPlayer* CWorldServer::GetClientByCharName( char* name  )
{
    for(UINT i=0;i<ClientList.size();i++)
    {
        CPlayer* thisclient = (CPlayer*) ClientList.at(i)->player;
        if (strncmp(thisclient->CharInfo->charname,name, 16)==0)
            return thisclient;
	}
	return NULL;
}

// Get Spawn Area by ID
CSpawnArea* CWorldServer::GetSpawnArea( UINT id, UINT map )
{
    if(map!=0)
    {
    	for(unsigned j=0; j<MapList.Index[map]->MonsterSpawnList.size(); j++)
        {
    		CSpawnArea* thisspawn = MapList.Index[map]->MonsterSpawnList.at(j);
    		if (thisspawn->id==id)
                return thisspawn;
    	}
    }
    else
    {
        for(map=0;map<MapList.Map.size();map++)
        {
        	for(unsigned j=0; j<MapList.Index[map]->MonsterSpawnList.size(); j++)
            {
        		CSpawnArea* thisspawn = MapList.Index[map]->MonsterSpawnList.at(j);
        		if (thisspawn->id==id)
                    return thisspawn;
        	}
        }
    }
	return NULL;
}

#ifdef USEIFO
CMobGroup* CWorldServer::GetMobGroup(UINT id, UINT map ) {
  if (map != 0) {
    for (unsigned j = 0; j < MapList.Index[map]->MobGroupList.size(); j++) {
      CMobGroup* thisgroup = MapList.Index[map]->MobGroupList.at(j);
      if (thisgroup->id == id)
        return thisgroup;
    }
  } else {
    for (map = 0; map < MapList.Map.size(); map++) {
      for (unsigned j = 0; j < MapList.Index[map]->MobGroupList.size(); j++) {
        CMobGroup* thisgroup = MapList.Index[map]->MobGroupList.at(j);
        if (thisgroup->id == id)
          return thisgroup;
      }
    }
  }
  return NULL;
}
#endif


// delete a spawn
bool CWorldServer::DeleteSpawn( CSpawnArea* spawn )
{
    if(spawn==NULL)
        return false;
    for(UINT i=0;i<MapList.Index[spawn->map]->MonsterSpawnList.size();i++)
    {
        if(MapList.Index[spawn->map]->MonsterSpawnList.at(i)==spawn)
        {
            MapList.Index[spawn->map]->MonsterSpawnList.erase( MapList.Index[spawn->map]->MonsterSpawnList.begin()+i );
            delete spawn;
            return true;
        }
    }
    return false;
}


// Search NPC by Type
CNPC* CWorldServer::GetNPCByType( UINT npctype )
{
	for(UINT i=0;i<MapList.Map.size();i++)
    {
        CMap* map = GServer->MapList.Map.at(i);
        for(UINT j=0;j<map->NPCList.size();j++)
        {
            CNPC* npc = map->NPCList.at(j);
            if(npc->npctype == npctype)
                return npc;
        }
	}
	return NULL;
}

// Search NPC by ID
CNPC* CWorldServer::GetNPCByID( UINT id, UINT map )
{
    if(map!=0)
        return MapList.Index[map]->GetNPCInMap( id );
	for(unsigned j=0; j<MapList.Map.size(); j++)
    {
		CNPC* thisnpc = MapList.Map.at( j )->GetNPCInMap( id );
		if (thisnpc!=0)
            return thisnpc;
	}
	return NULL;
}

// Get Telegate by ID
CTeleGate* CWorldServer::GetTeleGateByID( unsigned int id )
{
	for(unsigned j=0; j<TeleGateList.size(); j++)
    {
		CTeleGate* thisgate = TeleGateList.at(j);
		if (thisgate->id==id) return thisgate;
	}
	// Hmm, shit, couldent find it
	return NULL;
}

// Get Triangle Area
float CWorldServer::AreaOfTriangle( fPoint p1, fPoint p2, fPoint p3 )
{
	return abs((int)((p2.x * p1.y - p1.x * p2.y) + (p3.x * p2.y - p2.x * p3.y) + (p1.x * p3.y - p2.x * p1.y))) / 2;
}

// Get a random point in triangle area
fPoint CWorldServer::RandInTriangle( fPoint p1, fPoint p2, fPoint p3 )
{
	fPoint thispoint;
	float a = 1.0;
	float b = 1.0;
	while (a+b>1) { a=(float)(rand()*1.0/RAND_MAX); b=(float)(rand()*1.0/RAND_MAX); }
	float c = 1 - a - b;
	thispoint.x = (p1.x*a)+(p2.x*b)+(p3.x*c);
	thispoint.y = (p1.y*a)+(p2.y*b)+(p3.y*c);
	return thispoint;
}

// Get random point in poly
fPoint CWorldServer::RandInPoly( fPoint p[], int pcount )
{
	int tnum = 0;
	float tval = 0;
	float totalarea = 0;
	float* areas = new float[pcount-1];

	for(int i=0; i<pcount-2; i++) {
		totalarea += AreaOfTriangle(p[0], p[i+1], p[i+2]);
		areas[i+1] = totalarea;
	}
	tval = rand() * totalarea / RAND_MAX;
	for (tnum=1; tnum<pcount-1; tnum++) { if(tval<=areas[tnum]&&tval>areas[tnum-1]) break; }

	return RandInTriangle(p[0], p[tnum], p[tnum+1]);
}

// Get Random point in circle
fPoint CWorldServer::RandInCircle( fPoint center, float radius )
{
	fPoint thispoint;
	float angle = (float)(rand() * ( pi * 2 ) / RAND_MAX);
	float distance = (float)sqrt( rand() * 1.0 / RAND_MAX ) * radius;
	thispoint.x = cos(angle) * distance + center.x;
	thispoint.y = sin(angle) * distance + center.y;
	return thispoint;
}

// Check if a Monster is in a Circle around a Client with a specific range
bool CWorldServer::IsMonInCircle( CPlayer* thisclient, CMonster* thismon, float radius )
{
    if ( thisclient->Position->Map!=thismon->Position->Map ) return false;

    float dx = ( thisclient->Position->current.x - thismon->Position->current.x );
    float dy = ( thisclient->Position->current.y - thismon->Position->current.y );

    if ( sqrt( (dx * dx) + (dy * dy) ) <= radius )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if a Monster is in a Circle around a point with a specific radius
bool CWorldServer::IsMonInCircle( fPoint center, fPoint position, float radius )
{
    float dx = ( center.x - position.x );
    float dy = ( center.y - position.y );

    if ( sqrt( (dx * dx) + (dy * dy) ) <= radius )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if a Player is in a Circle around a Client with a specific range
bool CWorldServer::IsPlayerInCircle( CPlayer* thisclient, CPlayer* otherclient, float radius )
{
    if ( thisclient->Position->Map!=otherclient->Position->Map ) return false;

    float dx = ( thisclient->Position->current.x - otherclient->Position->current.x );
    float dy = ( thisclient->Position->current.y - otherclient->Position->current.y );

    if ( sqrt( (dx * dx) + (dy * dy) ) <= radius )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Search Respawn by ID
CRespawnPoint* CWorldServer::GetRespawnByID( unsigned id )
{
    for(UINT i=0;i<MapList.Map.size();i++)
    {
        CMap* thismap = MapList.Map.at(i);
        for(UINT j=0;j<thismap->RespawnList.size();j++)
        {
            CRespawnPoint* thisrespawn = thismap->RespawnList.at(j);
            if(thisrespawn->id==id)
                return thisrespawn;
        }
    }
	return NULL;
}

// Search Respawn by Map
CRespawnPoint* CWorldServer::GetRespawnByMap( int map )
{
    for(UINT j=0;j<MapList.Index[map]->RespawnList.size();j++)
    {
        if(MapList.Index[map]->RespawnList.at(j)->destMap==map)
            return MapList.Index[map]->RespawnList.at(j);
    }
	return NULL;
}

// Search Skill By ID
CSkills* CWorldServer::GetSkillByID( unsigned int id )
{
    unsigned int A=0,B=0,C=0;
    for(A=0,B=SkillList.size()-1;A<=B;)
    {
        if(A==B)
        {
            CSkills* thisskill = (CSkills*) SkillList.at( A );
			//LMA: bugs?
			/*
            if( id = thisskill->id );
            return thisskill;
			*/
            if( id == thisskill->id )
				return thisskill;
         }
        C = (A+B)/2;
        CSkills* thisskill = (CSkills*) SkillList.at( C );
        if(thisskill->id == id)
        {
            return thisskill;
        }
        if(thisskill->id > id)
        {
            B=C-1;
        }
        else
        {
            A=C+1;
        }
    }
    Log( MSG_WARNING,"SKILL NOT FOUNDED! %i", id );
    return NULL;
}

// Get Monster Drop By ID
CMDrops* CWorldServer::GetDropData( unsigned int id )
{
    unsigned int A=0,B=0,C=0;
    for(A=0,B=MDropList.size()-1;A<=B;)
    {
        if(A==B)
        {
           CMDrops* thismdrop = (CMDrops*) MDropList.at( A );
           id = thismdrop->id;
           return thismdrop;
        }
        C = (A+B)/2;
        CMDrops* thismdrop = (CMDrops*) MDropList.at( C );
        if(thismdrop->id == id){return thismdrop;}
        if(thismdrop->id > id){B=C-1;}
        else{A=C+1;}
    }
    Log(MSG_WARNING,"DROP NOT FOUNDED! %i", id );
    return NULL;
}

// Get NPC Data by ID
CNPCData* CWorldServer::GetNPCDataByID( unsigned int id )
{
    unsigned int A=0,B=0,C=0;
    for(A=0,B=NPCData.size()-1;A<=B;)
    {
        if(A==B)
        {
            CNPCData* thisnpc = (CNPCData*) NPCData.at( A );
            id = thisnpc->id;
            return thisnpc;

        }
        C = (A+B)/2;
        CNPCData* thisnpc = (CNPCData*) NPCData.at( C );
        if(thisnpc->id == id){return thisnpc;}
        if(thisnpc->id > id){B=C-1;}
        else{A=C+1;}
    }
    Log(MSG_WARNING,"NPC NOT FOUNDED! %i", id );
    return NULL;
}

// Get Consumible Item Info
CUseInfo* CWorldServer::GetUseItemInfo(CPlayer* thisclient, unsigned int slot )
{
    if(thisclient->items[slot].count<1)
        return NULL;
    CUseInfo* useitem = new (nothrow) CUseInfo;
    if(useitem==NULL)
    {
        Log(MSG_WARNING, "Error allocing memory GetUseItemInfo");
        return useitem;
    }
    useitem->itemnum = 0;
    useitem->itemtype = 0;
    useitem->usescript = 0;
    useitem->usetype = 0;
    useitem->usevalue = 0;
    useitem->use_buff=0;
    unsigned int type = 0;
    useitem->itemnum = thisclient->items[slot].itemnum;
    useitem->itemtype = thisclient->items[slot].itemtype;
    type = UseList.Index[useitem->itemnum]->type;

    Log(MSG_INFO,"Using item %i:%i, type %i",useitem->itemtype,useitem->itemnum,type);

    switch(type)
    {
        case 311://Medicine
        case 312://Food
        {
            useitem->usescript = 1;
            useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
            useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
        }
        break;
        case 313://Magic Item [scrolls/summons/fireworks/etc]
        {
            // scrolls [maxhp,attackpower up, ... ]
            if((useitem->itemnum>79 && useitem->itemnum<93) || (useitem->itemnum=145) ||(useitem->itemnum>300 && useitem->itemnum<320) || (useitem->itemnum>960 && useitem->itemnum<965))
            {
                useitem->usescript = 7;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[1];
                useitem->usevalue = 0;
            }

            else // cherry berrys
            if((useitem->itemnum >= 981 && useitem->itemnum <= 988) || (useitem->itemnum >= 1035 && useitem->itemnum <= 1039))
            {
                useitem->usescript = 0;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0]; // don't really need this as it is zero
                useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
            }

            else //Return Scrolls
            if( (useitem->itemnum>349 && useitem->itemnum<355) ||
                (useitem->itemnum>359 && useitem->itemnum<365) ||
                (useitem->itemnum==945 )  ||
                (useitem->itemnum>1029 && useitem->itemnum<1035) )
            {
                if( thisclient->Stats->MP < 33 )
                {
                    delete useitem;
                    return NULL;
                }
                thisclient->Stats->MP -= 32;
                useitem->usescript = 2;
                switch( useitem->itemnum )
                {
                    //Adventure's Plains - Drop only - [credits to tomiz]
                    case 350:
                        useitem->usetype = 22;
                        useitem->usevalue = 51105310;
                    break;
                    //Zant
                    case 351:
                        useitem->usetype = 1;
                        useitem->usevalue = 52405192;
                    break;
                    //Junon Polis
                    case 352:
                        useitem->usetype = 2;
                        useitem->usevalue = 55095283;
                    break;
                    //Eucar
                    case 353:
                        useitem->usetype = 51;
                        useitem->usevalue = 53665099;
                    break;
                    //Xita Refuge
                    case 354:
                        useitem->usetype = 61;
                        useitem->usevalue = 54344607;
                    break;
                    //Goblin Cave - Mileage Scroll
                    case 360:
                    case 1030:
                        useitem->usetype = 22; //31 Value Before - rl2171
                        useitem->usevalue = 54105040; //55185444 Value Before - rl2171
                    break;
                    //Desert of the Dead - Mileage Scroll
                    case 361:
                    case 1031:
                        useitem->usetype = 29;
                        useitem->usevalue = 51405160; //50825013 Value Before - rl2171
                    break;
                    //El Verloon - Mileage Scroll
                    case 362:
                    case 1032:
                        useitem->usetype = 24;
                        useitem->usevalue = 55205370;
                    break;
                    //George of Silence - Mileage Scroll
                    case 363:
                    case 1033:
                        useitem->usetype = 28;
                        useitem->usevalue = 53005100; //54674783 Value before - rl2171
                    break;
                    //Shady Jungle - Mileage Scroll
                    case 364:
                    case 1034:
                        useitem->usetype = 62;
                        useitem->usevalue = 58405170; //57515196 Value before - rl2171
                    break;
                    //Sikuku Underground Prison - Mileage Scroll - added by rl2171
                    case 365:
                        useitem->usetype = 63;
                        useitem->usevalue = 54004440;
                    break;
                    //Marsh of Ghosts - Mileage Scroll - added by rl2171
                    case 366:
                        useitem->usetype = 64;
                        useitem->usevalue = 50395326; // Temp value until actual value is found
                    break;
                    //Forgotten Temple B2 - Mileage Scroll - added by rl2171
                    case 367:
                        useitem->usetype = 57;
                        useitem->usevalue = 55395155; // Temp value until actual value is found
                    break;                    
                    //Junon's Order Return Scroll - Quest Scroll - added by rl2171
                    case 945:
                        useitem->usetype = 2;
                        useitem->usevalue = 53225100;
                    break;
                }
            }
            else //Charm Scrolls - 381-383 Charm Scrolls
            if (useitem->itemnum>380 && useitem->itemnum<384)
            {
                useitem->usescript = 3;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[1];
            }
            else //Artisan 210-227 Bombs
            if (useitem->itemnum>209 && useitem->itemnum<228)
            {
                useitem->usescript = 0; //not correct script ?
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[1]; // not correct ?
            }

            else //Dance Scroll
            if( (useitem->itemnum>370 && useitem->itemnum<377) ||
                (useitem->itemnum>389 && useitem->itemnum<398) )
            {
                useitem->usescript = 4;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
                useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
            }
            else // Firecrackers
            if( useitem->itemnum==913 ||
                (useitem->itemnum>920 && useitem->itemnum<935) ||
                (useitem->itemnum>990 && useitem->itemnum<996) )
            {
                useitem->usescript = 4;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
                useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
            }
            else // Emotions
            if( (useitem->itemnum>970 && useitem->itemnum<979) ||
                (useitem->itemnum>917 && useitem->itemnum<920) ||
                (useitem->itemnum>599 && useitem->itemnum<608) )  //918 - Love Chocolate  919 - Kiss Scroll
            {
                useitem->usescript = 4;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
                useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
            }
            else // Summons
            if( (useitem->itemnum>400 && useitem->itemnum<440) || (useitem->itemnum==496) || (useitem->itemnum==594) || (useitem->itemnum>915 && useitem->itemnum<918) || (useitem->itemnum>939 && useitem->itemnum<943) )
            {
                if( thisclient->CharInfo->stamina<101 )
                    return NULL;
                thisclient->CharInfo->stamina -= 100;
                useitem->usescript = 5;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[1];
                if(useitem->itemnum==439){useitem->usevalue = 965;} // Metal Moldie
                else if(useitem->itemnum==916){useitem->usevalue = 294;} //Firecracker Penguin
                else if(useitem->itemnum==917){useitem->usevalue = 297;} // Ice Spirit
                else if(useitem->itemnum==940){useitem->usevalue = 994;} // Easter Bunny
                else if(useitem->itemnum==941){useitem->usevalue = 995;} // Easter Egg
                else if(useitem->itemnum==942){useitem->usevalue = 1472;} // Soccer Ball Pet
                else if(useitem->itemnum==594)
                {
                     // Lucky Ghost
                     useitem->usevalue = 941;
                     useitem->use_buff = UseList.Index[useitem->itemnum]->useeffect[0];
                }
                else if(useitem->itemnum==496) {useitem->usevalue = 992;} // Christmas Tree
//                else if(useitem->itemnum==943) {useitem->usevalue;} // Event Scroll
//                else if(useitem->itemnum==944){useitem->usevalue = 172;} // Arua's Blessing
                else{ useitem->usevalue = useitem->itemnum + 500; }
            }
            else // Snowball
            if( useitem->itemnum==326 )
            {
                useitem->usescript = 6;
                useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
                useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
            }
            else
            {
                Log( MSG_WARNING, "Unknown Item %i - Type %i",useitem->itemnum,type);
                delete useitem;
                return NULL;
            }
        }
        break;
        case 314://Skill Book
        {
            useitem->usescript = 10;
            useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
            useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];

            //LMA: Anti hack protection, those skills (plastic surgeon, reset skills) will be
            //deleted in the quest itself, it'll avoid packets injections ;) .
//            if (useitem->itemnum>=451&&useitem->itemnum<=453)
//               useitem->usescript = 11;
        }
        break;
        case 315://Repair Tool
            delete useitem;
            return NULL;
        break;
        case 316://Quest Scroll
           delete useitem;
           return NULL;
        break;
        case 317://Engine Fuel - items 293-295, LMA / DRose
        {
            useitem->usescript = 12;
            useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
            useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
        }
        break;

            delete useitem;
            return NULL;
        break;
        case 320://Automatic Consumption - HP, MP, Stamina, Clan Point
            if (useitem->itemnum>150 && useitem->itemnum<192)
        {
            useitem->usescript = 1;
            useitem->usetype = UseList.Index[useitem->itemnum]->useeffect[0];
            useitem->usevalue = UseList.Index[useitem->itemnum]->useeffect[1];
        }
            else
            {
                Log( MSG_WARNING, "Unknown Item %i - Type %i",useitem->itemnum,type);

            delete useitem;
            return NULL;
            }
        break;
        case 321://Time Coupon - items 201-203, 948, 952-957
        {
              //LMA: Mileage shop change
              if (useitem->itemnum>=954 && useitem->itemnum<=957)
              {
                 Log(MSG_INFO,"Shop changed to %i",UseList.Index[useitem->itemnum]->quality);
                 thisclient->Shop->ShopType=UseList.Index[useitem->itemnum]->quality;
                 //thisclient->Shop->mil_shop_time=clock()+10*86400*1000; //10 days
                 thisclient->Shop->mil_shop_time=time(NULL)+10*86400; //10 days
                 BEGINPACKET( pak, 0x702 );
                 ADDSTRING( pak, "[Mileage] Your Shop look has changed." );
                 ADDBYTE( pak, 0 );
                 thisclient->client->SendPacket(&pak);

                 useitem->usescript = 1;
                 useitem->usetype =0;
                 useitem->usevalue =UseList.Index[useitem->itemnum]->quality;
              }

              //LMA / Dream Rose: Medal Exp
            if(((useitem->itemnum==948)||(useitem->itemnum>=201 && useitem->itemnum<=203))&&(thisclient->timerxp == 0))
            {
                useitem->usescript = 1;
                useitem->usetype =0;
                useitem->usevalue =UseList.Index[useitem->itemnum]->quality/100;
                thisclient->bonusxp=1;
                thisclient->wait_validation=UseList.Index[useitem->itemnum]->quality/100;

                //Good version?
                if(useitem->itemnum==948||(useitem->itemnum>=202 && useitem->itemnum<=203))
                 {
                   //valid until logout (limit to one hour)
                    thisclient->once=true;
                    //thisclient->timerxp=clock()+60*60*1000;  //1 hour
                    thisclient->timerxp=time(NULL)+60*60;  //1 hour
                    Log(MSG_INFO,"Bonus XP to %i",thisclient->bonusxp);
                    BEGINPACKET( pak, 0x702 );
                    ADDSTRING( pak, "The effect will hold until you log off or you play for one hour." );
                    ADDBYTE( pak, 0 );
                    thisclient->client->SendPacket(&pak);
                 }
                else
                {
                   //1 day, will "resist" to logout ;)
                   //thisclient->timerxp=clock()+86400*1000;
                   thisclient->timerxp=time(NULL)+86400;
                   thisclient->once=false;
                    Log(MSG_INFO,"Bonus XP to %i",thisclient->bonusxp);
                    BEGINPACKET( pak, 0x702 );
                    ADDSTRING( pak, "The effect will hold 24 hours." );
                    ADDBYTE( pak, 0 );
                    thisclient->client->SendPacket(&pak);
                }

            }

        }
        break;
        case 323://Job Skill, Unique Kill, Mileage Skill and All Skill Reset Books

            delete useitem;
            return NULL;
        break;
        default:
            Log( MSG_WARNING, "Unknown use item type: %i",type);
            return NULL;
        break;

    }
    useitem->itemtype -= 1;
    return useitem;
}

// Look if a skill target is friendly
bool CWorldServer::isSkillTargetFriendly( CSkills* thisskill )
{
	switch(thisskill->target)
    {   //Non-Hostile Target
        case 0://yourself
        case 1://party member
        case 2://clan member
        case 3://ally
        case 8://all members
        case 9://Fainted
            return true;
        break; //Hostile Target
        case 4: //monster
        case 5: //hostile character
        case 6: //hostile team member
        case 10: //hostile monster
            return false;
        break;
        default:
            Log(MSG_WARNING,"Unknown skill target %i", thisskill->target);
    }
    return false;
}

// calc distance
float CWorldServer::distance( fPoint pos1, fPoint pos2 )
{
    float distance = 0;
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	distance = sqrt( (dx*dx) + (dy*dy) );
    return distance;
}

// Search client by userid
CPlayer* CWorldServer::GetClientByUserID( UINT userid )
{
    for(UINT i=0;i<ClientList.size();i++)
	{
        CPlayer* thisclient = (CPlayer*)ClientList.at(i)->player;
        if(thisclient->Session->userid==userid && thisclient->Session->accesslevel != 0xffff)
            return thisclient;
	};
    return NULL;
}

// Check if a slot is valid (to prevent crash)
bool CWorldServer::CheckInventorySlot( CPlayer* thisclient, int slot )
{
    if(slot>=MAX_INVENTORY || slot<0)
    {
        Log(MSG_HACK, "Invalid Inventory slot %i from %s", slot, thisclient->Session->username );
        return false;
    }
    return true;
}

// Return a pseudo random number
UINT CWorldServer::RandNumber( UINT init, UINT range, UINT seed )
{
    if(seed!=0)
        srand(seed);
    if(range>RAND_MAX)
    {
        UINT max = (UINT)round(sqrt(range));
        UINT num1 = init+int(max*rand()/(RAND_MAX + 1.0));
        UINT num2 = init+int(max*rand()/(RAND_MAX + 1.0));
        UINT num3 = init+int(max*rand()/(RAND_MAX + 1.0));
        UINT res = (num1 * num2)+num3;
        return res>range?range:res;
    }
    else
    {
        UINT ranum = init+int(range*rand()/(RAND_MAX + 1.0));
        return ranum;
    }

}

// Check if is a valid item
bool CWorldServer::IsValidItem(UINT type, UINT id )
{
    if(type==0 || id==0 )
        return false;
    if(type<10)
    {
        if(id>4999)
            return false;
        if(EquipList[type].Index[id]->id==0)
            return false;
    }
    else
    {
        switch(type)
        {
            case 10:
                if(id>1999)
                    return false;
                if(UseList.Index[id]->id==0)
                    return false;
            break;
            case 11:
                if(id>3999)
                    return false;
                if(JemList.Index[id]->id==0)
                    return false;
            break;
            case 12:
                if(id>999)
                    return false;
                if(NaturalList.Index[id]->id==00)
                    return false;
            break;
            case 14:
                if(id>999)
                    return false;
                if(PatList.Index[id]->id==00)
                    return false;
            break;
            default:
                return false;
        }
    }
    return true;
}

int CWorldServer::GetIntValue( const char* s , void* var )
{
    char *tmp = strtok( (char*)var, (const char*)s );
    return atoi(tmp==NULL?0:tmp);
}

UINT CWorldServer::GetUIntValue( const char* s , void* var )
{
    char *tmp = strtok( (char*)var, (const char*)s );
    return atoi(tmp==NULL?0:tmp);
}

char* CWorldServer::GetStrValue( const char* s , void* var )
{
    char *tmp = strtok( (char*)var, (const char*)s );
    return tmp;
}

bool CWorldServer::AddParty( CParty* thisparty )
{
    PartyList.push_back( thisparty );
    return true;
}

bool CWorldServer::RemoveParty( CParty* thisparty )
{
    for(UINT i=0;i<PartyList.size( );i++)
    {
        if(PartyList.at(i)==thisparty)
        {
            PartyList.erase(PartyList.begin( )+i );
            return true;
        }
    }
    return false;
}

UINT CWorldServer::GetLevelGhost( UINT map, UINT level)
{
    UINT montype = 0;
    montype = (UINT)floor((level - 19) / 4) + 711;
    if(map >=1 && map <=50) { if(level<20) return 711;if (montype> 731) return 731;}
    if(map >=51 && map <=60) { if(montype<732) return 732; if(montype>750) return 750;}
    if(map >=61 && map <= 65) { montype -= 64; if(montype<680) return 680; if(montype>692) return 692; }
    if(map > 65) { return 692;}
    return montype;
}
// return fairy range for waiting time random
UINT CWorldServer::GetFairyRange( UINT part )
{
	UINT Range1[] = { 5, 5, 4, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    UINT Range2[] = { 10, 7, 7, 6, 6, 6, 6, 5, 4, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1 };
	if (part == 0) return Range1[GServer->FairyList.size()];
	if (part == 1) return Range2[GServer->FairyList.size()];
}

//LMA Grid
//Calculates the grid number using player or monster position
UINT CWorldServer::GetGridNumber(int mapid, int posx, int posy)
{
   UINT res=0;
   int grid_id=0;


   grid_id=allmaps[mapid].grid_id;
   if (grid_id==-1||allmaps[mapid].always_on==true)
       return 0;

   //we're on a 8*8 grid basis, we're translating to 10*10 grid basis.
   //In fact the 8*8 is into 10*10, a 1 border around 8*8, helps with calculations, explains the +1
   //Log(MSG_INFO,"map %i, O(%i,%i), A(%i,%i),W=%i,L=%i",mapid,gridmaps[grid_id].org_x,gridmaps[grid_id].org_y,posx,posy,gridmaps[grid_id].width,gridmaps[grid_id].length);
   /*res=(UINT) floor((posy-gridmaps[grid_id].org_y)*8/gridmaps[grid_id].width)+1;
   res=(UINT) (floor((posx-gridmaps[grid_id].org_x)*8/gridmaps[grid_id].length)+1)+res*10;*/
   //Log(MSG_INFO,"res: %u",res);

   //New way...
   res=(UINT) floor((posy-gridmaps[grid_id].org_y)/MINVISUALRANGE)+1;
   res=(UINT) (floor((posx-gridmaps[grid_id].org_x)/MINVISUALRANGE)+1)+res*(allmaps[mapid].nb_col+2);


   return res;
}

//LMA: saving all storage
bool CWorldServer::SaveAllStorage( CPlayer* thisclient)
{

    if(!GServer->DB->QExecute("DELETE FROM storage WHERE owner=%i", thisclient->Session->userid)) return true;
    for(UINT i=0;i<160;i++)
    {
    	if (thisclient->storageitems[i].count > 0)
        {
    		GServer->DB->QExecute("INSERT INTO storage (owner,itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem) VALUES(%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i)",
    							thisclient->Session->userid, thisclient->storageitems[i].itemnum, thisclient->storageitems[i].itemtype,thisclient->storageitems[i].refine, thisclient->storageitems[i].durability,
    							thisclient->storageitems[i].lifespan, i, thisclient->storageitems[i].count, thisclient->storageitems[i].stats, (thisclient->storageitems[i].socketed?1:0),
                                (thisclient->storageitems[i].appraised?1:0), thisclient->storageitems[i].gem );//Gem Fix by Irulagain
    	}
    }

    return true;
}

//LMA: getting all storage.
bool CWorldServer::GetAllStorage( CPlayer* thisclient)
{
    //resetting array
    for(int k=0;k<160;k++)
    {
        thisclient->storageitems[k].itemnum = 0;
        thisclient->storageitems[k].itemtype = 0;
        thisclient->storageitems[k].refine = 0;
        thisclient->storageitems[k].durability = 0;
        thisclient->storageitems[k].lifespan = 0;
        thisclient->storageitems[k].count = 0;
        thisclient->storageitems[k].stats = 0;
        thisclient->storageitems[k].socketed = false;
        thisclient->storageitems[k].appraised = false;
        thisclient->storageitems[k].gem = 0;
    }

	MYSQL_ROW row;
	MYSQL_RES *result = GServer->DB->QStore("SELECT itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem FROM storage WHERE owner=%i", thisclient->Session->userid);
    if(result==NULL) return false;
    thisclient->nstorageitems = mysql_num_rows(result);
    while(row = mysql_fetch_row(result))
    {
        if(!GServer->IsValidItem( atoi(row[1]), atoi(row[0]) ) || atoi(row[6])==0)
        {
            Log(MSG_WARNING, "char %s have a invalid or empty item in storage: %i%i [%i], this item will be deleted", thisclient->CharInfo->charname, atoi(row[1]), atoi(row[0]), atoi(row[6]) );
            continue;
        }
        UINT itemnum = atoi(row[5]);
        thisclient->storageitems[itemnum].itemnum = atoi(row[0]);
        thisclient->storageitems[itemnum].itemtype = atoi(row[1]);
        thisclient->storageitems[itemnum].refine = atoi(row[2]);
        thisclient->storageitems[itemnum].durability = atoi(row[3]);
        thisclient->storageitems[itemnum].lifespan = atoi(row[4]);
        thisclient->storageitems[itemnum].count = atoi(row[6]);
        thisclient->storageitems[itemnum].stats = atoi(row[7]);
        thisclient->storageitems[itemnum].socketed = (atoi(row[8])==1)?true:false;
        thisclient->storageitems[itemnum].appraised = (atoi(row[9])==1)?true:false;
        thisclient->storageitems[itemnum].gem = atoi(row[10]);
    }
    GServer->DB->QFree( );


     return true;
}

//LMA: Get Zuly from Storage (from MySQL)
bool CWorldServer::GetZulyStorage( CPlayer* thisclient)
{
	MYSQL_ROW row;
	MYSQL_RES *result = DB->QStore("SELECT zulystorage FROM accounts WHERE id=%i", thisclient->Session->userid);
    if(result==NULL) return false;
	row = mysql_fetch_row(result);
	thisclient->CharInfo->Storage_Zulies = atoi( row[0] );
	DB->QFree( );


     return true;
}


//LMA: Save Zuly to Storage (to MySQL)
bool CWorldServer::SaveZulyStorage( CPlayer* thisclient)
{
     GServer->DB->QExecute("update accounts set zulystorage = %i where id = %i", thisclient->CharInfo->Storage_Zulies, thisclient->Session->userid);


     return true;
}

//LMA: Get a slot storage (Mysql)
bool CWorldServer::GetSlotStorage( CPlayer* thisclient,UINT slotnum)
{
	MYSQL_ROW row;
	MYSQL_RES *result = GServer->DB->QStore("SELECT itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem FROM storage WHERE owner=%i AND slotnum=%i", thisclient->Session->userid,slotnum);
     if(result==NULL)
     {
         Log(MSG_INFO,"in GetSlotStorage False");
         return false;
     }

    //row = mysql_fetch_row(result);
    while(row = mysql_fetch_row(result))
    {
        //we refresh only the item storage we need.
        thisclient->storageitems[slotnum].itemnum = atoi(row[0]);
        thisclient->storageitems[slotnum].itemtype = atoi(row[1]);
        thisclient->storageitems[slotnum].refine = atoi(row[2]);
        thisclient->storageitems[slotnum].durability = atoi(row[3]);
        thisclient->storageitems[slotnum].lifespan = atoi(row[4]);
        thisclient->storageitems[slotnum].count = atoi(row[6]);
        thisclient->storageitems[slotnum].stats = atoi(row[7]);
        thisclient->storageitems[slotnum].socketed = (atoi(row[8])==1)?true:false;
        thisclient->storageitems[slotnum].appraised = (atoi(row[9])==1)?true:false;
        thisclient->storageitems[slotnum].gem = atoi(row[10]);
    }
    GServer->DB->QFree( );


     return true;
}

//LMA: Saving one slot in storage
bool CWorldServer::SaveSlotStorage( CPlayer* thisclient,UINT slotnum)
{
    UINT i=0;
    i=slotnum;

    /*previous version
    if(!GServer->DB->QExecute("DELETE FROM storage WHERE owner=%i AND slotnum=%i", thisclient->Session->userid,i))
       return false;

    if (thisclient->storageitems[i].count > 0)
    {
    	GServer->DB->QExecute("INSERT INTO storage (owner,itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem) VALUES(%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i)",
    						thisclient->Session->userid, thisclient->storageitems[i].itemnum, thisclient->storageitems[i].itemtype,thisclient->storageitems[i].refine, thisclient->storageitems[i].durability,
    						thisclient->storageitems[i].lifespan, i, thisclient->storageitems[i].count, thisclient->storageitems[i].stats, (thisclient->storageitems[i].socketed?1:0),
                            (thisclient->storageitems[i].appraised?1:0), thisclient->storageitems[i].gem );//Gem Fix by Irulagain
    }
    */

    //New version (MySQL 4.1+)
    if (thisclient->storageitems[i].count > 0)
    {
        GServer->DB->QExecute("INSERT INTO storage (owner,slotnum,itemnum,itemtype,refine,durability,lifespan,count,stats,socketed,appraised,gem) VALUES(%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i) ON DUPLICATE KEY UPDATE owner=VALUES(owner),slotnum=VALUES(slotnum),itemnum=VALUES(itemnum),itemtype=VALUES(itemtype),refine=VALUES(refine),durability=VALUES(durability),lifespan=VALUES(lifespan),count=VALUES(count),stats=VALUES(stats),socketed=VALUES(socketed),appraised=VALUES(appraised),gem=VALUES(gem)",
    						thisclient->Session->userid, i, thisclient->storageitems[i].itemnum, thisclient->storageitems[i].itemtype,thisclient->storageitems[i].refine, thisclient->storageitems[i].durability,
    						thisclient->storageitems[i].lifespan, thisclient->storageitems[i].count, thisclient->storageitems[i].stats, (thisclient->storageitems[i].socketed?1:0),
                            (thisclient->storageitems[i].appraised?1:0), thisclient->storageitems[i].gem );
    }
    else
    {
        GServer->DB->QExecute("DELETE FROM storage WHERE owner=%i AND slotnum=%i", thisclient->Session->userid,i);
    }


    return true;
}

//LMA: Saving a slot in ItemMall.
bool CWorldServer::SaveSlotMall( CPlayer* thisclient,UINT slotnum)
{
    UINT i=0;
    i=slotnum;


    if (thisclient->itemmallitems[i].count > 0)
    {
        GServer->DB->QExecute("INSERT INTO mileage (owner,slotnum,itemnum,itemtype,refine,durability,lifespan,count,stats,socketed,appraised,gem) VALUES(%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i) ON DUPLICATE KEY UPDATE owner=VALUES(owner),slotnum=VALUES(slotnum),itemnum=VALUES(itemnum),itemtype=VALUES(itemtype),refine=VALUES(refine),durability=VALUES(durability),lifespan=VALUES(lifespan),count=VALUES(count),stats=VALUES(stats),socketed=VALUES(socketed),appraised=VALUES(appraised),gem=VALUES(gem)",
    						thisclient->Session->userid, i, thisclient->itemmallitems[i].itemnum, thisclient->itemmallitems[i].itemtype,thisclient->itemmallitems[i].refine, thisclient->itemmallitems[i].durability,
    						thisclient->itemmallitems[i].lifespan, thisclient->itemmallitems[i].count, thisclient->itemmallitems[i].stats, (thisclient->itemmallitems[i].socketed?1:0),
                            (thisclient->itemmallitems[i].appraised?1:0), thisclient->itemmallitems[i].gem );
    }
    else
    {
        GServer->DB->QExecute("DELETE FROM mileage WHERE owner=%i AND slotnum=%i", thisclient->Session->userid,i);
    }


    return true;
}

//LMA: Trying to get a monster from a location (for AOE_TARGET packet mainly).
CMonster* CWorldServer::LookAOEMonster(CPlayer* thisclient)
{
    CMap* map = MapList.Index[thisclient->Position->Map];
    for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* monster = map->MonsterList.at(i);
        if(monster->clientid==thisclient->clientid) continue;
        if(thisclient->IsSummon( ) || thisclient->IsPlayer( ))
        {
            if(monster->IsSummon( ) && (map->allowpvp==0 || monster->owner==thisclient->clientid)) continue;
        }
        else
        {
            if(!monster->IsSummon( )) continue;
        }

        //Looking for a monsters in the aera (1 meter from position sent by client)
        if(GServer->IsMonInCircle( thisclient->Position->aoedestiny,monster->Position->current,(float) 1))
        {
            return monster;
        }

    }


    return NULL;
}

//LMA: Character version
CMonster* CWorldServer::LookAOEMonster(CCharacter* character)
{
    CMap* map = MapList.Index[character->Position->Map];
    for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* monster = map->MonsterList.at(i);
        if(monster->clientid==character->clientid) continue;
        if(character->IsSummon( ) || character->IsPlayer( ))
        {
            if(monster->IsSummon( ) && (map->allowpvp==0 || monster->owner==character->clientid)) continue;
        }
        else
        {
            if(!monster->IsSummon( )) continue;
        }

        //Looking for a monsters in the aera (1 meter from position sent by client)
        if(GServer->IsMonInCircle( character->Position->aoedestiny,monster->Position->current,(float) 1))
        {
            return monster;
        }

    }


    return NULL;
}


//LMA: returns the Item Mall list (with packet)
void CWorldServer::ReturnItemMallList(CPlayer* thisclient)
{
     thisclient->CPlayer::RebuildItemMall();

     if (thisclient->nsitemmallitems==0)
        return;

    //First signature.
    BEGINPACKET( pak, 0x7d9 );
    ADDWORD    ( pak, 0x0008);
    ADDWORD    ( pak, 0x0000 );
    ADDBYTE    ( pak, 0x44 );
    ADDBYTE    ( pak, 0x04  );
    ADDBYTE    ( pak, 0x20  );
    ADDBYTE    ( pak, 0x8b  );
    ADDBYTE    ( pak, 0x11  );
    ADDBYTE    ( pak, 0x49  );
    ADDBYTE    ( pak, 0xc0  );
    ADDBYTE    ( pak, 0x3c  );
    ADDBYTE    ( pak, 0xf9  );
    ADDBYTE    ( pak, 0x48  );
    ADDBYTE    ( pak, 0x00  );
    ADDBYTE    ( pak, 0x00  );
    ADDBYTE    ( pak, 0x01  );
    thisclient->client->SendPacket( &pak );


     //list
     RESETPACKET(pak,0x7d9);
     ADDBYTE    ( pak, 0x09 );
     ADDBYTE    ( pak, thisclient->nsitemmallitems);

     //signature
     ADDWORD    ( pak, 0x0000 );
     ADDBYTE    ( pak, 0x2f );
     ADDBYTE    ( pak, 0x02 );
     ADDBYTE    ( pak, 0xc4 );
     ADDBYTE    ( pak, 0x28 );
     ADDBYTE    ( pak, 0x10 );
     ADDBYTE    ( pak, 0x49 );
     ADDBYTE    ( pak, 0x91 );
     ADDBYTE    ( pak, 0xbd );
     ADDBYTE    ( pak, 0x06 );
     ADDBYTE    ( pak, 0x49 );
     ADDBYTE    ( pak, 0x4f );
     ADDBYTE    ( pak, 0x2c );
     ADDBYTE    ( pak, 0x00);

     //there's no void between two objects ;)
     for(int i=0;i<thisclient->nsitemmallitems;i++)
     {
         ADDDWORD   ( pak, BuildItemHead( thisclient->itemmallitems[i] ) );
         ADDDWORD   ( pak, BuildItemData( thisclient->itemmallitems[i] ) );
         ADDWORD    ( pak, 0x0000 );
         ADDWORD    ( pak, 0x0000 );
         ADDWORD    ( pak, 0x0000 );
         ADDBYTE    ( pak, 0x00);

         Log(MSG_INFO,"We send item in slot %i/%i: %i * %i:%i",i,thisclient->nsitemmallitems,thisclient->itemmallitems[i].count,thisclient->itemmallitems[i].itemtype,thisclient->itemmallitems[i].itemnum);
     }

     thisclient->client->SendPacket( &pak );

    //Signature end
    RESETPACKET( pak, 0x7d9 );
    ADDWORD    ( pak, 0x000a);
    ADDWORD    ( pak, 0x0000 );
    ADDBYTE    ( pak, 0xca);
    ADDBYTE    ( pak, 0x01  );
    ADDBYTE    ( pak, 0x3c  );
    ADDBYTE    ( pak, 0x84  );
    ADDBYTE    ( pak, 0x08  );
    ADDBYTE    ( pak, 0x49  );
    ADDBYTE    ( pak, 0xbd  );
    ADDBYTE    ( pak, 0x8e  );
    ADDBYTE    ( pak, 0xda  );
    ADDBYTE    ( pak, 0x48  );
    ADDBYTE    ( pak, 0xcb  );
    ADDBYTE    ( pak, 0x03  );
    ADDBYTE    ( pak, 0x00  );
    thisclient->client->SendPacket( &pak );

     return;
}

//LMA: takes an item from item mall to player's inventory
void CWorldServer::TakeItemMallList(CPlayer* thisclient,int qty,int slot)
{
 	MYSQL_ROW row;
	MYSQL_RES *result = GServer->DB->QStore("SELECT itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem FROM mileage WHERE owner=%i AND slotnum=%i", thisclient->Session->userid,slot);
	if(result==NULL)
    {
       Log(MSG_HACK,"%s tried to get %i items from slot %i from mileage and there is nothing there !",thisclient->CharInfo->charname, qty, slot);
       return;
    }

    if(mysql_num_rows(result)!=1)
    {
      Log(MSG_HACK,"%s tried to get %i items from slot %i from mileage and there is nothing there !",thisclient->CharInfo->charname, qty, slot);
      return;
    }

    row = mysql_fetch_row(result);
    //little refresh :)
	thisclient->itemmallitems[slot].itemnum = atoi(row[0]);
	thisclient->itemmallitems[slot].itemtype = atoi(row[1]);
	thisclient->itemmallitems[slot].refine = atoi(row[2]);
	thisclient->itemmallitems[slot].durability = atoi(row[3]);
	thisclient->itemmallitems[slot].lifespan = atoi(row[4]);
	thisclient->itemmallitems[slot].count = atoi(row[6]);
	thisclient->itemmallitems[slot].stats = atoi(row[7]);
	thisclient->itemmallitems[slot].socketed = (atoi(row[8])==1)?true:false;
	thisclient->itemmallitems[slot].appraised = (atoi(row[9])==1)?true:false;
	thisclient->itemmallitems[slot].gem = atoi(row[10]);

    Log(MSG_INFO,"%s takes %i * %i:%i from item mall",thisclient->CharInfo->charname,qty,thisclient->itemmallitems[slot].itemtype,thisclient->itemmallitems[slot].itemnum);

    GServer->DB->QFree( );
    if(qty>thisclient->itemmallitems[slot].count)
    {
       Log(MSG_HACK,"%s tried to get %i items from slot %i from mileage, had only %i !",thisclient->CharInfo->charname, qty, slot,thisclient->itemmallitems[slot].count);
       return;
    }

    //Is there a free slot into inventory for this item?
    CItem newitem = thisclient->itemmallitems[slot];
    if(newitem.itemtype>9 && newitem.itemtype<14)
    {
        int count = qty;
        if( count>thisclient->itemmallitems[slot].count )
            count = thisclient->itemmallitems[slot].count;
        newitem.count = count;
        thisclient->itemmallitems[slot].count -= count;

        if(thisclient->itemmallitems[slot].count<=0)
            ClearItem(thisclient->itemmallitems[slot]);
    }
    else
    {
        ClearItem(thisclient->itemmallitems[slot]);
    }

    int newslot= thisclient->GetNewItemSlot ( newitem );
    //no place in player's inventory, so back to itemall.
    if(newslot==0xffff)
    {
        thisclient->itemmallitems[slot] = newitem;
        return ;
    }

    int amount = 0;
    if(thisclient->items[newslot].count>0)
    {
      int amount = thisclient->items[newslot].count;
	  newitem.count+=amount;
    }
    if( newitem.count > 999 )
    {
        amount = 999 - newitem.count;
        newitem.count = 999;
    }
    thisclient->items[newslot] = newitem;
    if( amount > 0 )
    {
        newitem.count = amount;
        unsigned int newslot2 = thisclient->GetNewItemSlot( newitem );
        if( newslot2 == 0xffff )
        {
            thisclient->itemmallitems[slot] = thisclient->items[newslot];
            thisclient->items[newslot].count = amount;
            return ;
        }
        thisclient->items[newslot2] = newitem;
        thisclient->UpdateInventory( newslot2 );
    }

    if (thisclient->items[newslot].itemnum>0)
       Log(MSG_INFO,"Slot in inventory: %i, exist already: %i * %i:%i",newslot,thisclient->items[newslot].count,thisclient->items[newslot].itemtype,thisclient->items[newslot].itemnum);
    else
        Log(MSG_INFO,"Slot in inventory: %i, does not exist already.",newslot);

    //Packet time :)
    BEGINPACKET( pak, 0x7d9 );
    ADDBYTE    ( pak, 0x04 );
    ADDBYTE    ( pak, slot );
    ADDBYTE    ( pak, newslot );
   	ADDDWORD   ( pak, BuildItemHead( thisclient->items[newslot] ) );
	ADDDWORD   ( pak, BuildItemData( thisclient->items[newslot] ) );
	//signature
    ADDBYTE    (pak,0xbb);
    ADDBYTE    (pak,0xfb);
    ADDBYTE    (pak,0xb0);
    ADDBYTE    (pak,0x01);
    ADDWORD    (pak,0x0000);
    //End of item signature.
    ADDBYTE    ( pak, slot );
    ADDDWORD   ( pak, BuildItemHead( thisclient->itemmallitems[slot] ) );
    ADDDWORD   ( pak, BuildItemData( thisclient->itemmallitems[slot] ) );
	//signature
    ADDBYTE    (pak,0x00);
    ADDBYTE    (pak,0x00);
    ADDBYTE    (pak,0x00);
    ADDBYTE    (pak,0x00);
    ADDWORD    (pak,0x0000);
    //End of item signature.
    //last signature
    ADDWORD    (pak,0xcccc );
    ADDBYTE    (pak,0x4f );
    ADDBYTE    (pak,0x0c );
    ADDBYTE    (pak,0x36 );
    ADDBYTE    (pak,0xf4 );
    ADDBYTE    (pak,0x00 );
    ADDWORD    (pak,0x0000 );
    ADDWORD    (pak,0x0000 );
    ADDWORD    (pak,0x0000 );
    ADDWORD    (pak,0x0000);
    //end of last signature...

    thisclient->client->SendPacket( &pak );
    //should be ok now :)
    if(thisclient->itemmallitems[slot].itemnum==0)
       thisclient->nsitemmallitems--;

    //Saving :)
    SaveSlotMall(thisclient,slot);
    thisclient->SaveSlot41(newslot);


    return;
}

//LMA: Check if it's ok for Union Slaughter.
bool CWorldServer::CheckOkUnion()
{
     //We look through player list to see if we have enough people for each union.
     int nb_union[8];
     int nb_union_ok[8];


     for (int k=0;k<8;k++)
     {
          nb_union[k]=0;
          nb_union_ok[k]=0;
     }

     Log(MSG_INFO,"In CheckOkUnion");
     //We're in map 2 (Junon Polis), mayor is at 5200,5200
    CMap* map = MapList.Index[2];
    if (map->PlayerList.size()<Config.unionmin)
       return false;

    vector<CPlayer*>  PlayerListToWarp;
    PlayerListToWarp.clear();

    for(UINT i=0;i<map->PlayerList.size();i++)
    {
       //checking radius (player near mayor).
        CPlayer* otherclient = map->PlayerList.at(i);
        if(otherclient == NULL) continue;
        if (otherclient->CharInfo->unionid==0||otherclient->Shop->open)
        {
           Log(MSG_INFO,"%s has no union id %i or is in shop %i.",otherclient->CharInfo->charname,otherclient->CharInfo->unionid==0,otherclient->Shop->open);
           continue;
        }

        float dx = ( otherclient->Position->current.x - 5515 );
        float dy = ( otherclient->Position->current.y - 5215 );

        if ( sqrt( (dx * dx) + (dy * dy) ) >= 50 )
        {
           Log(MSG_INFO,"%s is too far away.",otherclient->CharInfo->charname);
           continue;
        }

        Log(MSG_INFO,"%s is near enough.",otherclient->CharInfo->charname);
        PlayerListToWarp.push_back(otherclient);
        nb_union[otherclient->CharInfo->unionid-1]++;
        if(nb_union[otherclient->CharInfo->unionid-1]>=Config.unionmin&&nb_union_ok[otherclient->CharInfo->unionid-1]==0)
            nb_union_ok[otherclient->CharInfo->unionid-1]++;
    }

    //enough players around to fire union war? (more than one group)
    if ((nb_union_ok[0]+nb_union_ok[1]+nb_union_ok[2]+nb_union_ok[3]+nb_union_ok[4]+nb_union_ok[5]+nb_union_ok[6]+nb_union_ok[7])>1)
    {
       Log(MSG_INFO,"Let's go Warp !!");
       GoUnionWar(PlayerListToWarp);
       PlayerListToWarp.clear();
       return true;
    }

    PlayerListToWarp.clear();


     return false;
}


//LMA: let's warp all those gentlemen for Union slaughter :)
bool CWorldServer::GoUnionWar(vector<CPlayer*>  PlayerListToWarp)
{
     //We look through player list to see if we have enough people for each union.
     //We're in map 2 (Junon Polis), mayor is at 5515,5215
     fPoint list_tele[8];

     //union wars emplacement (each union has his own emplacement)
     list_tele[0].x=5507;
     list_tele[0].y=5346;
     list_tele[1].x=5150;
     list_tele[1].y=5085;
     list_tele[2].x=5435;
     list_tele[2].y=5070;
     list_tele[3].x=5459;
     list_tele[3].y=4732;
     list_tele[4].x=5289;
     list_tele[4].y=4940;
     list_tele[5].x=5182;
     list_tele[5].y=4766;
     list_tele[6].x=5271;
     list_tele[6].y=4790;
     list_tele[7].x=5410;
     list_tele[7].y=4931;

    char text[200];
    sprintf( text, "Union War has Begun !!!");

    if (PlayerListToWarp.size()<Config.unionmin)
       return false;


    for(UINT i=0;i<PlayerListToWarp.size();i++)
    {
       //checking radius (player near mayor).
        CPlayer* otherclient = PlayerListToWarp.at(i);
        if(otherclient == NULL) continue;
        if (otherclient->CharInfo->unionid==0||otherclient->Shop->open)
        {
           Log(MSG_INFO,"%s has no union id %i or is in shop %i.",otherclient->CharInfo->charname,otherclient->CharInfo->unionid==0,otherclient->Shop->open);
           continue;
        }

        float dx = ( otherclient->Position->current.x - 5515 );
        float dy = ( otherclient->Position->current.y - 5215 );

        if ( sqrt( (dx * dx) + (dy * dy) ) >= 50 )
        {
           Log(MSG_INFO,"%s is too far away to be warped.",otherclient->CharInfo->charname);
           continue;
        }

        otherclient->CharInfo->union02=0;
        otherclient->CharInfo->union04=0;

         //let's update values "live" ;)
        BEGINPACKET( pak, 0x721 );
        ADDWORD( pak, 82 );
        ADDWORD( pak, 0 );
        ADDWORD( pak, 0x0000 );
        otherclient->client->SendPacket( &pak );
        RESETPACKET( pak, 0x730 );
        ADDWORD    ( pak, 0x0005 );
        ADDDWORD   ( pak, 0x40b3a24d );
        otherclient->client->SendPacket( &pak );
        RESETPACKET( pak, 0x721 );
        ADDWORD( pak, 84 );
        ADDWORD( pak, 0 );
        ADDWORD( pak, 0x0000 );
        otherclient->client->SendPacket( &pak );
        RESETPACKET( pak, 0x730 );
        ADDWORD    ( pak, 0x0005 );
        ADDDWORD   ( pak, 0x40b3a24d );
        otherclient->client->SendPacket( &pak );

        RESETPACKET( pak, 0x702 );
        ADDSTRING  ( pak, "Mighty Lord" );
    	ADDSTRING  ( pak, "> " );
    	ADDSTRING  ( pak, text );
    	ADDBYTE    ( pak, 0x00 );
    	otherclient->client->SendPacket( &pak );
    	//SendToAllInMap  ( &pak,8 );

        //Warp time.
        fPoint temp_point=GServer->RandInCircle(list_tele[otherclient->CharInfo->unionid-1],20);
        Log(MSG_INFO,"Warping %s",otherclient->CharInfo->charname);
        GServer->pakGMTele(otherclient,8,temp_point.x,temp_point.y);
    }


     return true;
}

//LMA: Union Slaughter is over lads, let's come back to Junon :)
bool CWorldServer::WarIsOver()
{
     //Come back in JP
     fPoint list_tele;
     list_tele.x=5540;
     list_tele.y=5240;

    int nb_players=0;
    CMap* map = MapList.Index[8];

    int umax=0;
    int keymax=0;
    int uless=0;
    int keyless=0;
    for (int k=0;k<8;k++)
    {
        //Who killed most people?
        if (map->nb_kills[k]>umax)
        {
           keymax=k;
           umax=map->nb_kills[k];
        }

        //Hum... the innocent lamb :)
        if(map->nb_killed[k]>uless)
        {
           keyless=k;
           uless=map->nb_killed[k];
        }

        Log(MSG_INFO,"Union %i: Kills %i, killed: %i",k,map->nb_kills[k],map->nb_killed[k]);
    }

    char text[200];
    if (keymax==0)
       sprintf( text, "Union Slaughter has been won by %s !!!","Junon Order");
    if (keymax==1)
       sprintf( text, "Union Slaughter has been won by %s !!!","Akram Kingdom");
    if (keymax==2)
       sprintf( text, "Union Slaughter has been won by %s !!!","Righteous Crusader");
    if (keymax==3)
       sprintf( text, "Union Slaughter has been won by %s !!!","Arumic");
    if (keymax==4)
       sprintf( text, "Union Slaughter has been won by %s !!!","Ferrel Guild");
    if (keymax==5)
       sprintf( text, "Union Slaughter has been won by %s !!!","Gypsies");
    if (keymax==6)
       sprintf( text, "Union Slaughter has been won by %s !!!","Ikaness");

       Log(MSG_INFO,"keymax: %i, text %s",keymax,text);

    keymax++;

    nb_players=map->PlayerList.size();
    for(UINT i=0;i<nb_players;i++)
    {
        CPlayer* otherclient = map->PlayerList.at(map->PlayerList.size()-1);
        if(otherclient == NULL) continue;
        //Warp time, after reward ;)

        //extra points :)
        if (otherclient->CharInfo->unionid==keymax)
        {
           otherclient->CharInfo->union05+=200;
            BEGINPACKET( pak, 0x721 );
            ADDWORD( pak, 85 );
            ADDWORD( pak, otherclient->CharInfo->union05 );
            ADDWORD( pak, 0x0000 );
            otherclient->client->SendPacket( &pak );
            RESETPACKET( pak, 0x730 );
            ADDWORD    ( pak, 0x0005 );
            ADDDWORD   ( pak, 0x40b3a24d );
            otherclient->client->SendPacket( &pak );
        }

        //let's send the message to the right people only :)
        BEGINPACKET( pak, 0x702 );
        ADDSTRING  ( pak, "Mighty Lord" );
    	ADDSTRING  ( pak, "> " );
    	ADDSTRING  ( pak, text );
    	ADDBYTE    ( pak, 0x00 );
    	otherclient->client->SendPacket(&pak);
    	//SendToAll  ( &pak );

        fPoint temp_point=GServer->RandInCircle(list_tele,20);
        GServer->pakGMTele(otherclient,2,temp_point.x,temp_point.y);
    }

     return true;
}

//LMA: Send a packet too all connected clients in a map.
void CWorldServer::SendToAllInMap( CPacket* pak, int mapid)
{
    CMap* map = MapList.Index[mapid];

    for(UINT i=0;i<map->PlayerList.size();i++)
    {
        CPlayer* otherclient = map->PlayerList.at(i);
        if (otherclient->client == NULL) continue;
        if (!otherclient->client->isActive) continue;

        if (otherclient->Session->inGame)
            otherclient->client->SendPacket( pak );
    }

}

//LMA: Union War, let's summon the stones...
void CWorldServer::UWstones(int type)
{
     //2 sunrise at the middle of map, then one sunset appears when a sunrise is killed.     
    CMap* map = MapList.Index[9];
    fPoint position;
    
    //let's summon the stones ;)
    //sunrise.
    if (type==1)
    {        
        position.x=5180;
        position.y=5100;
        position.z=0;
        map->AddMonster( 432, position, 0, NULL, NULL, 0 , true );     
        position.x=5220;
        position.y=5100;
        position.z=0;
        map->AddMonster( 432, position, 0, NULL, NULL, 0 , true );     
        return;
    }
    
    //Dusk killed :)
    if (type==2)
    {        
        position.x=5200;
        position.y=5050;
        position.z=0;
        map->AddMonster( 433, position, 0, NULL, NULL, 0 , true );          
        map->duskkilled=false;
        
        //We must warp attackers to their respawn point in map 9
        UWWarpAttackers();
        return;
    }  

    //sunset    
    position.x=5200;
    position.y=5120;
    position.z=0;
    map->AddMonster( 431, position, 0, NULL, NULL, 0 , true );     
    
     
     return;
}

//LMA: UW, warp attackers to their respawn point in map 9
void CWorldServer::UWWarpAttackers()
{
    fPoint list_tele;
    list_tele.x=5200;
    list_tele.y=4868;     
    CMap* map = MapList.Index[9];
    int nb_players=0;
    nb_players=map->PlayerList.size();
    
    //temp list.    
    vector<CPlayer*>  PlayerListToWarp;
    PlayerListToWarp.clear();

    for(UINT i=0;i<map->PlayerList.size();i++)
    {
       //checking radius (player near mayor).
        CPlayer* otherclient = map->PlayerList.at(i);
        if(otherclient == NULL) continue;
        //attackers 1 means Junon Order (1) and Arumic (4)
        //attackers 2 means Righteous Crusaders (3) and Ferrell Guide (5)
        if (map->attackers==1&&!(otherclient->CharInfo->unionid==1||otherclient->CharInfo->unionid==4))
           continue;
        if (map->attackers==2&&!(otherclient->CharInfo->unionid==3||otherclient->CharInfo->unionid==5))
           continue;
        PlayerListToWarp.push_back(otherclient);
    }
    
    for(UINT i=0;i<PlayerListToWarp.size();i++)
    {
        CPlayer* otherclient = PlayerListToWarp.at(i);
        if(otherclient == NULL) continue;

        //let's send the message to the right people only :)
        char text[200];
        BEGINPACKET( pak, 0x702 );
        ADDSTRING  ( pak, "Mighty Lord" );
    	ADDSTRING  ( pak, "> Your Dusk Crystal has been killed, you've been sent to your respawn point!" );
    	ADDSTRING  ( pak, text );
    	ADDBYTE    ( pak, 0x00 );
    	otherclient->client->SendPacket(&pak);

        fPoint temp_point=GServer->RandInCircle(list_tele,20);
        GServer->pakGMTele(otherclient,2,temp_point.x,temp_point.y);
    }
    
    PlayerListToWarp.clear();
    

     return ;    
}

//LMA: UW, we kill the stones.
void CWorldServer::KillStones()
{
    CMap* map = MapList.Index[9];
    int nb_killed=0;
    
    for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* thismon=map->MonsterList.at(i);
        if (thismon->montype!=432&&thismon->montype!=431&&thismon->montype!=433)
           continue;

        thismon->Stats->HP = -1;
        BEGINPACKET( pak, 0x799 );
        ADDWORD    ( pak, thismon->clientid );
        ADDWORD    ( pak, thismon->clientid );
        ADDDWORD   ( pak, thismon->thisnpc->hp*thismon->thisnpc->level );
        ADDDWORD   ( pak, 16 );
        SendToVisible( &pak, thismon );
        map->DeleteMonster( thismon );
                                                                         
       nb_killed++;
       if (nb_killed==3)
          return;
    }   
         
     
     return;     
}
 
 
 //LMA: Enough players for Union War? Don't forget there are alliances...
 bool CWorldServer::CheckEnoughUW()
 {
    //attackers 1 means Junon Order (1) and Arumic (4)
    //attackers 2 means Righteous Crusaders (3) and Ferrell Guide (5)             
      CMap* map = MapList.Index[9];
      int quest_attack[2];
      int quest_defend[2];
      int nb_attackers=0;
      int nb_defenders=0;
      
      quest_attack[0]=2853;
      quest_attack[1]=2857;
      quest_defend[0]=2582;
      quest_defend[1]=2586;
      
      if (map->attackers==1)
      {
        quest_attack[0]=2851;
        quest_attack[1]=2855;                          
        quest_defend[0]=2584;
        quest_defend[1]=2588;        
      }
      
    //let's do some SQL :)
    MYSQL_ROW row;
    MYSQL_RES *result = GServer->DB->QStore("SELECT COUNT(questid) FROM list_quest WHERE questid=%i OR questid=%i",quest_attack[0],quest_attack[1]);
    if(result==NULL) return false;
    row = mysql_fetch_row(result);
    nb_attackers=atoi(row[0]);
    GServer->DB->QFree( );
    MYSQL_RES *result2 = GServer->DB->QStore("SELECT COUNT(questid) FROM list_quest WHERE questid=%i OR questid=%i",quest_defend[0],quest_defend[1]);
    if(result2==NULL) return false;
    row = mysql_fetch_row(result2);
    nb_defenders=atoi(row[0]);
    GServer->DB->QFree( );    
      
      //not enough people :(
      if (nb_defenders<=Config.unionwarmin||nb_attackers<Config.unionwarmin)
         return false;      
      
      map->sunrisekilled=false;
      map->sunsetkilled=false;
      map->sunsetspawned=false;
      map->duskkilled=false;
      
      
      return true;    
 }

//LMA: Summon NPC for UW :)
UINT CWorldServer::SummonNPCUW(bool kill)
 {

    	CMap* map = MapList.Index[2];	
     
         if (kill)
         {
            CNPC* goodbye=map->GetNPCInMap(map->npc_id);
            map->DeleteNPC(goodbye);
            return 0;                
         }
         
        //2do: complete it...
        fPoint position;
        position.x=5470;
        position.y=5248;
        position.z=0;
        
        UINT npcid=1189;
        UINT dialogid=28;
        UINT eventid=0;
        
     	CNPC* thisnpc = new CNPC;
    	thisnpc->clientid = GetNewClientID();
    	thisnpc->dir = 0;
    	thisnpc->npctype = npcid;
    	thisnpc->pos = position;
    	thisnpc->posMap = 2;
    	thisnpc->thisnpc = GetNPCDataByID( npcid );
    	thisnpc->thisnpc->dialogid = dialogid;
    	thisnpc->event=eventid;
    	if( thisnpc->thisnpc==NULL ) return 0;
    	map->AddNPC( thisnpc );      
    
       Log(MSG_INFO,"Summoning UW NPC %i, id: %i",npcid,thisnpc->clientid);
       
      
      return thisnpc->clientid;
 }

//LMA: UW is over, let's warp the lads back ;)
void CWorldServer::UWOver()
{
     //We delete the NPC in Junon
     SummonNPCUW(true);
     
     //we kill the stones.
     KillStones();
     
     //Ok, timeout or someone won?
     CMap* map = MapList.Index[9];
     int winner[4];
     
     //defenders or attackers won?
     //remember, there is always an alliance...
     //2do: put alliance in 'map'?
   winner[0]=4;
   winner[1]=5;               
   winner[2]=6;       
   winner[3]=7;
     
     char text[200];
     if (!map->sunrisekilled&&!map->sunsetkilled)
     {
       sprintf( text, "Union War has been won by %s !!!","the defenders");
       if (map->defenders==1)
       {
           winner[0]=1;
           winner[1]=2;
           winner[2]=3;
           winner[3]=0;           
       }
       
     }
     else
     {
         //attackers won.
       sprintf( text, "Union War has been won by %s !!!","the attackers");
       if (map->attackers==1)
       {
           winner[0]=1;
           winner[1]=2;
           winner[2]=3;
           winner[3]=0;           
       }
               
     }
     
     //let's warp everyone back.     
     //Come back in JP
     fPoint list_tele;
     list_tele.x=5540;
     list_tele.y=5240;

    int nb_players=0;
    nb_players=map->PlayerList.size();
    for(UINT i=0;i<nb_players;i++)
    {
        CPlayer* otherclient = map->PlayerList.at(map->PlayerList.size()-1);
        if(otherclient == NULL) continue;
        //Warp time, after reward ;)

        //extra points :)
        if (otherclient->CharInfo->unionid==winner[0]||otherclient->CharInfo->unionid==winner[1]||otherclient->CharInfo->unionid==winner[2]||otherclient->CharInfo->unionid==winner[3])
        {
           otherclient->CharInfo->union05+=1000;
            BEGINPACKET( pak, 0x721 );
            ADDWORD( pak, 85 );
            ADDWORD( pak, otherclient->CharInfo->union05 );
            ADDWORD( pak, 0x0000 );
            otherclient->client->SendPacket( &pak );
            RESETPACKET( pak, 0x730 );
            ADDWORD    ( pak, 0x0005 );
            ADDDWORD   ( pak, 0x40b3a24d );
            otherclient->client->SendPacket( &pak );
        }

        //let's send the message to the right people only :)
        BEGINPACKET( pak, 0x702 );
        ADDSTRING  ( pak, "Mighty Lord" );
    	ADDSTRING  ( pak, "> " );
    	ADDSTRING  ( pak, text );
    	ADDBYTE    ( pak, 0x00 );
    	otherclient->client->SendPacket(&pak);
    	//SendToAll  ( &pak );

        fPoint temp_point=GServer->RandInCircle(list_tele,20);
        GServer->pakGMTele(otherclient,2,temp_point.x,temp_point.y);
    }


     return;     
}

//LMA: we change the status dialog from some NPC for UW
void CWorldServer::UWNPCdialogs(int status)
{
     int eventid=0;
     
     
     switch (status)
     {
         case 0:
               //usual dialog
               eventid=0;
              break;
         case 1:
              //quest 1 (defend the stones for JO and Arumic, attack for Ferrel and RC)
              eventid=1;
              break;
         case 2:
         case 6:              
              //Enough participants
              eventid=2;
              break;
         case 3:
         case 7:              
              //UW underway
              eventid=3;
              break;
         case 4:
              //UW Canceled
              eventid=4;
              break;
         case 5:
              //quest 2 (attack the stones for JO and Arumic, defend for Ferrel and RC)
              eventid=5;
              break;
         default:
                 eventid=0;
                 break;
     }
     
     int list_npc[4];
     for (int k=0;k<4;k++)
         list_npc[k]=0;
         
     //2do: complete the other NPC as well...
     list_npc[0]=1089; //Arothel, Ferrel Guild
     list_npc[1]=1090; //Gawain, Righteous crusader
     list_npc[2]=1091; //Chelsie, Arumic
     list_npc[3]=1088; //Raw, Junon order
     
     for (int k=0;k<4;k++)
     {
         if (list_npc[k]==0)
            continue;
            
        CNPC* thisnpc = GetNPCByType(list_npc[k]);
        if(thisnpc == NULL)
            continue;
        thisnpc->event = eventid;
        BEGINPACKET( pak, 0x790 );
        ADDWORD    ( pak, thisnpc->clientid );
        ADDWORD    ( pak, thisnpc->event );        
        //thisclient->client->SendPacket(&pak);
        GServer->SendToAllInMap  ( &pak,2);
        
        Log(MSG_INFO,"Changing dialog UW NPC %i, eventid: %i",list_npc[k],thisnpc->event);
        
        //Saving in database
        DB->QExecute("UPDATE npc_data SET eventid=%i WHERE id=%i", eventid,list_npc[k]);                           
     }
     
          
   return;
}

//LMA: UW, who attacks, who defends?
void CWorldServer::UWDecide()
{
       //Who teams with who?       
       CMap* map = MapList.Index[9];
        //attackers 1 means Junon Order (1) and Arumic (4)
        //attackers 2 means Righteous Crusaders (3) and Ferrell Guild (5)       
     int no_attacker=2;
     int no_defender=1;
                     
       if (GServer->RandNumber(1,2)==1)
       {
         no_attacker=1;
         no_defender=2;
       }
       
       map->attackers=no_attacker;
       map->defenders=no_defender;
       
       char text[200];
       if (map->defenders!=1)
          sprintf( text, "UW will begin soon, Unions %s will defend, fetch the quest at your Union Master !!!","Junon Order and Arumic");
       else
           sprintf( text, "UW will begin soon, Unions %s will defend, fetch the quest at your Union Master !!!","Righteous Crusaders and Ferrell Guild");
    
    BEGINPACKET( pak, 0x702 );
    ADDSTRING  ( pak, "Mighty Lord" );
    ADDSTRING  ( pak, "> " );
    ADDSTRING  ( pak, text );
    ADDBYTE    ( pak, 0x00 );
    GServer->SendToAllInMap  ( &pak,2);

       if (map->attackers!=1)
          sprintf( text, "UW will begin soon, Unions %s will attack, fetch the quest at your Union Master !!!","Junon Order and Arumic");
       else
           sprintf( text, "UW will begin soon, Unions %s will attack, fetch the quest at your Union Master !!!","Righteous Crusaders and Ferrell Guild");
           
    RESETPACKET( pak, 0x702 );
    ADDSTRING  ( pak, "Mighty Lord" );
    ADDSTRING  ( pak, "> " );
    ADDSTRING  ( pak, text );
    ADDBYTE    ( pak, 0x00 );
    GServer->SendToAllInMap  ( &pak,2);     
     
     
     return;     
}
