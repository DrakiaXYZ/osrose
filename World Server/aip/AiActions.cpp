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

// Props to ExJam for this code :D
#include "../WorldServer.h"

// extern CRandomMersenne rg;

//Unknown
AIACT(000)
{
	//SetCMD_Stop (Stop all actions i guess?)
    //entity->StopAll();
	return AI_SUCCESS;
}

//Do Action
AIACT(001)
{
	//byte cAction;	//Pos: 0x00
	//CObjMOB::Set_EMOTION (pak 781)
	GETAIACTDATA(001);
    BEGINPACKET( pak, 0x781 );
    ADDWORD    ( pak, data->cAction );
	ADDWORD    ( pak, 0);
	ADDWORD    ( pak, entity->clientid );
    GServer->SendToVisible(&pak, entity,NULL );
	return AI_SUCCESS;
}

//Say LTB String
AIACT(002)
{
	//Client side say text
	//Log(MSG_DEBUG, "Say LTB String");
	return AI_SUCCESS;
}

//Move (1)
AIACT(003)
{
	//dword iDistance;	//Pos: 0x00
	//byte cSpeed;	//Pos: 0x04
	//move randomly within iDistance (individual x and y so its within a square)
	GETAIACTDATA(003);
	CMonster* monster = reinterpret_cast<CMonster*>(entity);
    monster->UpdatePosition(monster->stay_still);
	int iDist = data->iDistance;// * 2;//Get it to our coord system!

    //int randDis = rg.IRandom(0, iDist << 1);
    //srand(time(NULL));
    int randDis = rand()%(iDist << 1);
	float nX = (entity->Position->current.x + randDis) - iDist;
	entity->Position->destiny.x=nX;

    //randDis = rg.IRandom(0, iDist << 1);
    //srand(time(NULL));
    randDis = rand()%(iDist << 1);
	float nY = (entity->Position->current.y + randDis) - iDist;
	entity->Position->destiny.y=nY;
	monster->thisnpc->stance = data->cSpeed;
	monster->SetStats();
    entity->Position->lastMoveTime = clock();
    //ClearBattle( entity->Battle );// this also seems to clear the attackers battle??
    //entity->Battle->atktype=0;
    BEGINPACKET( pak, 0x797 );
	ADDWORD    ( pak, entity->clientid );
	ADDWORD    ( pak, 0x0000 );
	ADDWORD    ( pak, entity->Stats->Move_Speed ); //speed
	ADDFLOAT   ( pak, entity->Position->destiny.x*100 );
	ADDFLOAT   ( pak, entity->Position->destiny.y*100 );
	ADDWORD    ( pak, 0xcdcd );
	ADDBYTE    ( pak, monster->thisnpc->stance );
	GServer->SendToVisible(&pak, entity);
    ////Log(MSG_DEBUG, "move1 monster %i, stance %i",monster->montype,data->cSpeed);
    ////Log(MSG_DEBUG, "move(1)");
	return AI_SUCCESS;
}

//Move (2)
AIACT(004)
{
	//dword iDistance;	//Pos: 0x00
	//byte cSpeed;	//Pos: 0x04
	//move randomly within iDistance of spawn position (square)	Position->source
	GETAIACTDATA(004);
	CMonster* monster = reinterpret_cast<CMonster*>(entity);
    monster->UpdatePosition(monster->stay_still);

	int iDist = data->iDistance;//Get it to our coord system!

    //int randDis = rg.IRandom(0, iDist << 1);
    int randDis = rand()%(iDist << 1);
	float nX = (entity->Position->source.x + randDis) - iDist;
	entity->Position->destiny.x=nX;

    //randDis = rg.IRandom(0, iDist << 1);
    randDis = rand()%(iDist << 1);
	float nY = (entity->Position->source.y + randDis) - iDist;
	entity->Position->destiny.y=nY;


	monster->thisnpc->stance = data->cSpeed;
	monster->SetStats();
    entity->Position->lastMoveTime = clock();
    //ClearBattle( entity->Battle );// this also seems to clear the attackers battle??
    //entity->Battle->atktype = 0;
    BEGINPACKET( pak, 0x797 );
	ADDWORD    ( pak, entity->clientid );
	ADDWORD    ( pak, 0x0000 );//???
	ADDWORD    ( pak, entity->Stats->Move_Speed ); //speed
	ADDFLOAT   ( pak, entity->Position->destiny.x*100 );
	ADDFLOAT   ( pak, entity->Position->destiny.y*100 );
	ADDWORD    ( pak, 0xcdcd );
	ADDBYTE    ( pak, monster->thisnpc->stance );
	GServer->SendToVisible(&pak, entity);
    ////Log(MSG_DEBUG, "move2 stance %i",data->cSpeed);

	return AI_SUCCESS;
}

//Move (3)
AIACT(005)
{
	//byte cSpeed;	//Pos: 0x00
	//move randomly within 200 of "m_pFindCHAR" (square)
	GETAIACTDATA(005);
	if(entity->findChar == NULL)
        return AI_FAILURE;
    CMonster* monster = reinterpret_cast<CMonster*>(entity);
    monster->UpdatePosition(monster->stay_still);
	entity->findChar->UpdatePosition(monster->stay_still);

	int iDist = 2;//Get it to our coord system!


    int randDis = rand()%(iDist << 1);
	float nX = (entity->findChar->Position->current.x + randDis) - iDist;
	entity->Position->destiny.x=nX;


    randDis = rand()%(iDist << 1);
	float nY = (entity->findChar->Position->current.y + randDis) - iDist;
	entity->Position->destiny.y=nY;
	monster->thisnpc->stance = data->cSpeed;
	monster->SetStats();
    //entity->MoveTo(nX, nY);
    //entity->Position->lastMoveTime = clock();
    //ClearBattle( entity->Battle );// this also seems to clear the attackers battle??
    //entity->Battle->atktype = 0;
    BEGINPACKET( pak, 0x797 );
	ADDWORD    ( pak, entity->clientid );
	ADDWORD    ( pak, 0x0000 );//???
	ADDWORD    ( pak, entity->Stats->Move_Speed ); //speed
	ADDFLOAT   ( pak, entity->Position->destiny.x*100 );
	ADDFLOAT   ( pak, entity->Position->destiny.y*100 );
	ADDWORD    ( pak, 0xcdcd );
	ADDBYTE    ( pak, monster->thisnpc->stance );
	GServer->SendToVisible(&pak, entity);
    //	//Log(MSG_DEBUG, "move3 stance %i",data->cSpeed);
    //	//Log(MSG_DEBUG, "move (3)");
    //    RESETPACKET(pak, 0x783);
    //    ADDWORD(pak,entity->findChar->clientid);//entity->clientid);
    //    ADDSTRING(pak,"hello there");
    //    ADDBYTE(pak,0);
    //    GServer->SendToVisible(&pak, entity);
    //		server->SendPacketToZone(entity, &pakout);

	return AI_SUCCESS;
}

//Move (?)
AIACT(006)
{
	//dword iDistance;	//Pos: 0x00
	//byte cAbType;	//Pos: 0x04
	//byte cMoreLess;	//Pos: 0x05
	//Run and Attack aiobj within iDistance that has the lowest or greatest cAbType
	//cAbType
	//0 = Level
	//1 = Attack
	//2 = Defense
	//3 = "Res"? Magic Resistance?
	//4 = HP
	//5 = Charm
	GETAIACTDATA(006);

    dword eCount = 0;
    int highestAB = -9999999;
    //	CWorldEntity* highestEntity = NULL;
    int lowestAB = 9999999;
    //	CWorldEntity* lowestEntity = NULL;
    CMonster* monster = reinterpret_cast<CMonster*>(entity);
    CMap* map= GServer->MapList.Index[entity->Position->Map];
    CCharacter* Target = NULL;
    for(UINT i=0;i<map->PlayerList.size();i++)
    {
        CPlayer* player = map->PlayerList.at(i);
        if(player == NULL)continue;
        if(GServer->IsMonInCircle( monster->Position->current, player->Position->current, data->iDistance))
        {
            switch(data->cAbType)
            {
                case 0: //level
                    if(data->cMoreLess == 0)
                    {
                        if(player->Stats->Level > lowestAB)
                        {
                            lowestAB = player->Stats->Level;
                            Target = player;
                        }else continue;
                    }else{
                        if(player->Stats->Level < highestAB)
                        {
                            highestAB = player->Stats->Level;
                            Target = player;
                        }else continue;
                    }
                break;
                case 1: //Attack power
                    if(data->cMoreLess == 0)
                    {
                        if(player->Stats->Attack_Power > lowestAB)
                        {
                            lowestAB = player->Stats->Attack_Power;
                            Target = player;
                        }else continue;
                    }else{
                        if(player->Stats->Attack_Power < highestAB)
                        {
                            highestAB = player->Stats->Attack_Power;
                            Target = player;
                        }else continue;
                    }
                break;
                case 2: //defense
                    if(data->cMoreLess == 0)
                    {
                        if(player->Stats->Defense> lowestAB)
                        {
                            lowestAB = player->Stats->Defense;
                            Target = player;
                        }else continue;
                    }else{
                        if(player->Stats->Defense < highestAB)
                        {
                            highestAB = player->Stats->Defense;
                            Target = player;
                        }else continue;
                    }
                break;
                case 3: //Magic Def
                    if(data->cMoreLess == 0)
                    {
                        if(player->Stats->Magic_Defense> lowestAB)
                        {
                            lowestAB = player->Stats->Magic_Defense;
                            Target = player;
                        }else continue;
                    }else{
                        if(player->Stats->Magic_Defense < highestAB)
                        {
                            highestAB = player->Stats->Magic_Defense;
                            Target = player;
                        }else continue;
                    }
                break;
                case 4: // HP
                    if(data->cMoreLess == 0)
                    {
                        if(player->Stats->HP> lowestAB)
                        {
                            lowestAB = player->Stats->HP;
                            Target = player;
                        }else continue;
                    }else{
                        if(player->Stats->HP < highestAB)
                        {
                            highestAB = player->Stats->HP;
                            Target = player;
                        }else continue;
                    }
                break;
                case 5: // Charm
                    if(data->cMoreLess == 0)
                    {
                        if(player->Attr->Cha > lowestAB)
                        {
                            lowestAB = player->Attr->Cha;
                            Target = player;
                        }else continue;
                    }else{
                        if(player->Attr->Cha < highestAB)
                        {
                            highestAB = player->Attr->Cha;
                            Target = player;
                        }else continue;
                    }
                break;
            }
        }
    }
    // OK we found the new Target player. now attack him.
    monster->thisnpc->stance = 1;
    monster->SetStats();
    monster->StartAction( Target, NORMAL_ATTACK, 0 );

    //	int searchDistance = data->iDistance * 100;

    //	CWorldEntity** entityList = entity->thisZone->GetEntityList();
    //	dword entityCount = entity->thisZone->GetEntityCount();
    //	for(dword i = 1; i < MAX_ZONE_CLIENTID; i++){
    //		CWorldEntity* other = entityList[i];
    //		if(eCount >= entityCount) break;
    //		if(other == NULL) continue;
    //		eCount++;
    //		if(other == entity) continue;
    //		if(other->_EntityType == ENTITY_NO_TYPE) continue;
    //		if(other->_EntityType == ENTITY_DROP) continue;

    //		int dX = (int)abs((int)other->curBlock.x - (int)entity->curBlock.x);
    //		if(dX > 1) continue;
    //		int dY = (int)abs((int)other->curBlock.y - (int)entity->curBlock.y);
    //		if(dY > 1) continue;

    //		int iDistance = other->basic.pos.distance(entity->basic.pos);
    //		if(iDistance > searchDistance) continue;

    //		int value = AI_GetAbility(other, data->cAbType);

    //		if(value < lowestAB){
    //			lowestAB = value;
    //			lowestEntity = other;
    //		}
    //		if(value > highestAB){
    //			highestAB = value;
    //			highestEntity = other;
    //		}
    //	}
    //	if(data->cMoreLess){
    //		if(lowestEntity){
			//SetCmdRUN_nATTACK
    //			entity->Attack(lowestEntity);
    //		}
    //	}else{
    //		if(highestEntity){
			//SetCmdRUN_nATTACK
    //			entity->Attack(highestEntity);
    //		}
    //	}
    //Log(MSG_DEBUG, "move (?)");
	return AI_SUCCESS;
}

//Unknown
AIACT(007)
{
	//CObjCHAR::Special_ATTACK
	//Log(MSG_DEBUG, "AIACT(007)");
	return AI_SUCCESS;
}

//Move (4)
AIACT(008)
{
	//dword iDistance;	//Pos: 0x00
	//byte cSpeed;	//Pos: 0x04
	//Some weird shit going on here
	//move within some sort of distance of target (i think possibly % iDistance of distance between target)(run away?)
	//Log(MSG_DEBUG, "AIACT(008)");
	return AI_SUCCESS;
}

//Convert Monster to new monster (1)
AIACT(009)
{
	//word wMonster;	//Pos: 0x00
	//Transform into wMonster
	GETAIACTDATA(010);
	CMap* map= GServer->MapList.Index[entity->Position->Map];
	CMonster* monster = reinterpret_cast<CMonster*>(entity);
	int oldmon = monster->montype;
	map->ConverToMonster(monster,data->wMonster,1);
	//Log(MSG_DEBUG, "AIACT(009)convert monster type %i to %i",oldmon,data->wMonster);
	return AI_SUCCESS;
}

//Spawn Monster (2)
AIACT(010)
{
	//word wMonster;	//Pos: 0x00
	//Spawn wMonster at current X,Y
	GETAIACTDATA(010);
	CMap* map = GServer->MapList.Index[entity->Position->Map];
	fPoint position;
    //CMonster* newmonster;
    position = GServer->RandInCircle( entity->Position->current, 1 );
    map->AddMonster( data->wMonster, position,0, NULL, NULL, 0,true );
    //	entity->thisZone->SpawnMonster(data->wMonster, entity->basic.pos, entity->basic.map);
    //Log(MSG_DEBUG, "AIACT(010)spawn %i",data->wMonster);
	return AI_SUCCESS;
}

//Call for backup
AIACT(011)
{
	//dword iDistance;	//Pos: 0x00
	//dword iNumOfMonster;	//Pos: 0x04
	//force iNumOfMonster of same team within iDistance to attack my target
    //CWorldEntity* target = entity->thisZone->GetEntity(entity->_TargetID);
    //if(target == NULL) return AI_FAILURE;
    //Log(MSG_DEBUG, "AIACT(011)");
    CCharacter* target = entity->GetCharTarget( );
    if(target == NULL) return AI_FAILURE;
	GETAIACTDATA(011);

	int chrCount = 0;
	dword eCount = 0;
	int searchDistance = data->iDistance;

	CMap* map = GServer->MapList.Index[entity->Position->Map];
	dword entityCount = map->MonsterList.size();
	for(UINT j=0;j<map->MonsterList.size();j++)
    {
        CMonster* other = map->MonsterList.at(j);
        if(eCount >= entityCount) break;
        if(other == NULL) continue;
        eCount++;
        if(other == entity) continue;
        if(other->CharType != 0) continue;

        //	CWorldEntity** entityList = entity->thisZone->GetEntityList();
        //	dword entityCount = entity->thisZone->GetEntityCount();
        //	for(dword i = 1; i < MAX_ZONE_CLIENTID; i++){
        //		CWorldEntity* other = entityList[i];
        //		if(eCount >= entityCount) break;
        //		if(other == NULL) continue;
        //		eCount++;
        //		if(other == entity) continue;
        //		if(other->_EntityType == ENTITY_MONSTER) continue;
        //		if(other->team != entity->team) continue;
        //		int dX = (int)abs((int)other->curBlock.x - (int)entity->curBlock.x);
        //		if(dX > 1) continue;
        //		int dY = (int)abs((int)other->curBlock.y - (int)entity->curBlock.y);
        //		if(dY > 1) continue;
        int iDistance = (int) GServer->distance( other->Position->current, entity->Position->current );
        //		int iDistance = other->basic.pos.distance(entity->basic.pos);
		if(iDistance > searchDistance) continue;
		chrCount++;
		other->Battle->target = entity->Battle->target;
		other->StartAction( (CCharacter*) target, NORMAL_ATTACK, 0 );

        //		other->Attack(target);

		if(chrCount >= data->iNumOfMonster) return AI_SUCCESS;
	}

	return AI_SUCCESS;
}

//start attack
AIACT(012)
{
    //Log(MSG_DEBUG, "AIACT(012)");
	//Run and attack "m_pNearCHAR" Nearest Character
    //	entity->Attack(entity->nearChar);
    //    //Log(MSG_DEBUG, "AIACT(012)");
    if(entity->nearChar == NULL)return AI_FAILURE;
    //entity->Battle->target=entity->nearChar->clientid;
    CMonster* monster = reinterpret_cast<CMonster*>(entity);
    monster->thisnpc->stance=1;
    monster->SetStats();
    monster->StartAction( (CCharacter*) entity->nearChar, NORMAL_ATTACK, 0 );
    //    //Log(MSG_DEBUG, "AIACT(012)%i",entity->nearChar->clientid);
	return AI_SUCCESS;
}

//start attack
AIACT(013)
{
    //Log(MSG_DEBUG, "AIACT(013)");
	//Run and attack "m_pFindCHAR" Character found from aiobj loop things
    //	entity->Attack(entity->findChar);
    if(entity->findChar == NULL)return AI_FAILURE;
    //entity->Battle->target=entity->findChar->clientid;
    CMonster* monster = reinterpret_cast<CMonster*>(entity);
    monster->thisnpc->stance = 1;
    monster->SetStats();
    monster->Battle->target = entity->findChar->clientid;
    monster->StartAction( (CCharacter*) entity->findChar, NORMAL_ATTACK, 0 );
    //    //Log(MSG_DEBUG, "AIACT(013)%i",entity->findChar->clientid);
	return AI_SUCCESS;
}

//Unknown
AIACT(014)
{
	//dword iDistance;	//Pos: 0x00
	//find aiobj within iDistance and force them to attack my target
    //	CWorldEntity* target = entity->thisZone->GetEntity(entity->_TargetID);
    //	if(target == NULL) return AI_FAILURE;
	GETAIACTDATA(014);


    //	dword eCount = 0;
    //	int searchDistance = data->iDistance * 100;

    //	CWorldEntity** entityList = entity->thisZone->GetEntityList();
    //	dword entityCount = entity->thisZone->GetEntityCount();
    //	for(dword i = 1; i < MAX_ZONE_CLIENTID; i++){
    //		CWorldEntity* other = entityList[i];
    //		if(eCount >= entityCount) break;
    //		if(other == NULL) continue;
    //		eCount++;
    //		if(other == entity) continue;
    //		if(other->_EntityType == ENTITY_NO_TYPE) continue;
    //		if(other->_EntityType == ENTITY_DROP) continue;
    //		if(other->team != entity->team) continue;

    //		int dX = (int)abs((int)other->curBlock.x - (int)entity->curBlock.x);
    //		if(dX > 1) continue;
    //		int dY = (int)abs((int)other->curBlock.y - (int)entity->curBlock.y);
    //		if(dY > 1) continue;

    //		int iDistance = other->basic.pos.distance(entity->basic.pos);
    //		if(iDistance > searchDistance) continue;

    //		other->Attack(target);
    //		return AI_SUCCESS;
    //	}
    //Log(MSG_DEBUG, "AIACT(014)");
	return AI_SUCCESS;
}

//Retaliate against the last character that hit me
AIACT(015)
{
	//Run and attack "m_pDestCHAR" Blah?
    //	//Log(MSG_DEBUG, "AIACT(015)");
    CMonster* monster = reinterpret_cast<CMonster*>(entity);
    //if(monster->Battle->hitby == monster->Battle->target)
    //    return AI_FAILURE; //no need to initiate combat. I am already fighting this player

    if(monster->IsOnBattle())
        return AI_FAILURE; //already in battle

    monster->thisnpc->stance = 1;
    monster->SetStats();
    monster->Battle->target = monster->Battle->hitby;
    CCharacter* target = entity->GetCharTarget( );
    monster->StartAction( target, NORMAL_ATTACK, 0 );
	return AI_SUCCESS;
}

//Run away
AIACT(016)
{
	//dword iDistance;
	//Run Away!
    //Log(MSG_DEBUG, "AIACT(016)");
	GETAIACTDATA(016);
	CMonster* monster = reinterpret_cast<CMonster*>(entity);
    monster->UpdatePosition(monster->stay_still);

	float radius = data->iDistance;
    float angle = rand()%(360);
    //	float angle = rg.IRandom(0,360);
    //	entity->UpdatePosition();
    //	entity->MoveTo(entity->basic.pos.x + (radius * cos(angle)), entity->basic.pos.y + (radius * sin(angle)));
	float nX = (entity->Position->source.x + (radius * cos(angle)));
	entity->Position->destiny.x=nX;
	float nY = (entity->Position->source.y + (radius * cos(angle)));
	entity->Position->destiny.y=nY;

	monster->thisnpc->stance = 1;
	monster->SetStats();

    entity->Position->lastMoveTime = clock();
    //ClearBattle( entity->Battle );// this also seems to clear the attackers battle??
    entity->Battle->atktype = 0;
    BEGINPACKET( pak, 0x797 );
	ADDWORD    ( pak, entity->clientid );
	ADDWORD    ( pak, 0x0000 );//???
	ADDWORD    ( pak, entity->Stats->Move_Speed ); //speed
	ADDFLOAT   ( pak, entity->Position->destiny.x*100 );
	ADDFLOAT   ( pak, entity->Position->destiny.y*100 );
	ADDWORD    ( pak, 0xcdcd );
	ADDBYTE    ( pak, 0x01 );
	GServer->SendToVisible(&pak, entity);


	return AI_SUCCESS;
}

//Drop Item
AIACT(017)
{
	//word item0;	//Pos: 0x00
	//word item1;	//Pos: 0x02
	//word item2;	//Pos: 0x04
	//word item3;	//Pos: 0x06
	//word item4;	//Pos: 0x08
	//dword iToOwner;	//Pos: 0x0c
	//Random drop one of item 1-5
	GETAIACTDATA(017);
	//Log(MSG_DEBUG, "AIP DROP 017");

	//srand(time(NULL));
    int itemRand = rand()%(5);
	//int itemRand = rg.IRandom(0,360);
	int nItem = data->items[itemRand];
	if (nItem == 0)return AI_FAILURE;

	//CItem dropItem;
    CDrop* newdrop = new (nothrow) CDrop;
	newdrop->clientid = GServer->GetNewClientID( );
    newdrop->posMap = entity->Position->Map;
    newdrop->pos = GServer->RandInCircle( entity->Position->current, 3 );
    newdrop->droptime = time(NULL);
    newdrop->owner = 0;//entity->MonsterDrop->firsthit;
    newdrop->thisparty = 0;//entity->thisparty;
    ClearItem(newdrop->item);
	newdrop->amount = 1;
	newdrop->type = 2;
	newdrop->item.itemnum = nItem % 1000;
	newdrop->item.itemtype = nItem / 1000;
	if(newdrop->item.IsStackable())
    {
		newdrop->item.count = 1;
	}
    else
    {
		newdrop->item.stats = 0;
		newdrop->item.durability = 40;
		newdrop->item.lifespan = 1000;
		newdrop->item.socketed = 0;
		newdrop->item.appraised = 1;
		newdrop->item.refine = 0;
	}
    //Log(MSG_DEBUG, "AIP DROP item type=  %i item num = %i", newdrop->item.itemtype, newdrop->item.itemnum);
	newdrop->item.count = 1;


	CMap* map = GServer->MapList.Index[newdrop->posMap];
		map->AddDrop( newdrop );
    //	entity->DropEntityItem(&dropItem);

	return AI_SUCCESS;
}

//Make nearby monsters attack my target
AIACT(018)
{
	//word cMonster;	//Pos: 0x00
	//word wHowMany;	//Pos: 0x02
	//dword iDistance;	//Pos: 0x04
	//make wHowMany monsters of type cMonster within iDistance attack my target
    //	CWorldEntity* target = entity->thisZone->GetEntity(entity->_TargetID);
    //	if(target == NULL) return AI_FAILURE;
	GETAIACTDATA(018);

    //	int chrCount = 0;
    //	dword eCount = 0;
    //	int nearestDistance = 9999999;
    //	int searchDistance = data->iDistance * 100;

    //	CWorldEntity** entityList = entity->thisZone->GetEntityList();
    //	dword entityCount = entity->thisZone->GetEntityCount();
    //	for(dword i = 1; i < MAX_ZONE_CLIENTID; i++){
    //		CWorldEntity* other = entityList[i];
    //		if(eCount >= entityCount) break;
    //		if(other == NULL) continue;
    //		eCount++;
    //		if(other == entity) continue;
    //		if(other->_EntityType != ENTITY_MONSTER) continue;
    //		if(other->team != entity->team) continue;
    //		if(reinterpret_cast<CMonster*>(other)->MonID != data->cMonster) continue;

    //		int dX = (int)abs((int)other->curBlock.x - (int)entity->curBlock.x);
    //		if(dX > 1) continue;
    //		int dY = (int)abs((int)other->curBlock.y - (int)entity->curBlock.y);
    //		if(dY > 1) continue;

    //		int iDistance = other->basic.pos.distance(entity->basic.pos);
    //		if(iDistance > searchDistance) continue;
    //		chrCount++;

		//Run and Attack target
    //		other->Attack(target);

    //		if(chrCount >= data->wHowMany) return AI_SUCCESS;
    //	}
    //Log(MSG_DEBUG, "AIACT(018)");
	return AI_SUCCESS;
}

//Unknown
AIACT(019)
{
	//Run and attack "m_pNearCHAR" //Identical to 012
	return F_AI_ACT_012(server, entity, raw);
}

//Spawn Monster (5)
AIACT(020)
{
	//word cMonster;	//Pos: 0x00
	//byte btPos;	//Pos: 0x02
	//dword iDistance;	//Pos: 0x04

	//Spawn cMonster within iDistance of btPos

	//btPos 0 = my pos
	//btPos 1 = "m_pDestCHAR" pos
	//btPos 2 = targets pos
	GETAIACTDATA(020);
	CMap* map = GServer->MapList.Index[entity->Position->Map];
	CMonster* monster = reinterpret_cast<CMonster*>(entity); //need this to get the spawnid of the entity
	if(monster == NULL) return AI_FAILURE;

	fPoint position;

	if(data->btPos == 0)
    {
        position = GServer->RandInCircle( entity->Position->current, data->iDistance );
        map->AddMonster( data->cMonster, position,0,NULL,NULL, monster->Status->spawnid, true);
    }
    else if(data->btPos == 1)
    {
        position = GServer->RandInCircle( entity->Position->current, data->iDistance );
        map->AddMonster( data->cMonster, position,0, NULL,NULL, monster->Status->spawnid, true );
		//dest char
	}
    else if(data->btPos == 2)
    {
        CCharacter* target = entity->GetCharTarget( );
        if(target == NULL) return AI_FAILURE;
        position = GServer->RandInCircle( target->Position->current, data->iDistance );
        map->AddMonster( data->cMonster, position,0, NULL,NULL, monster->Status->spawnid, true );
    }
    //Log(MSG_DEBUG, "AIACT(020)option spawn %i distance %i monstertype %i",data->btPos,data->iDistance,data->cMonster);
	return AI_SUCCESS;
}

//Unknown
AIACT(021)
{
	//Does absolutely nothing
	return AI_SUCCESS;
}

//Unknown
AIACT(022)
{
	//Does absolutely nothing
	return AI_SUCCESS;
}

//ghostseeds and ghosts and player summons commit suicide
AIACT(023)
{
	//Commit suicide
	//Log(MSG_DEBUG, "AIACT(023) Suicide");
    //entity->Stats->HP = 0;

    //LMA: we let him die later, it seems we never come back from DoAI in this case...
    CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);
    entity->Stats->HP = -1;
    BEGINPACKET( pak, 0x799 );
    ADDWORD    ( pak, entity->clientid );
    ADDWORD    ( pak, entity->clientid );
    ADDDWORD   ( pak, thisMonster->thisnpc->hp*thisMonster->thisnpc->level );
    ADDDWORD   ( pak, 16 );
    GServer->SendToVisible( &pak, entity );
    //thisMonster->DoAi(thisMonster->thisnpc->AI, 5);
	return AI_SUCCESS;
}

//Do Skill
AIACT(024)
{
	//byte btTarget;	//Pos: 0x00
	//word nSkill;	//Pos: 0x02
	//word nMotion;	//Pos: 0x04 //8 = SKILL_ATTACK 6 = magic

	//Use nSkill & nMotion?
	//btTarget 0 = m_pFindCHAR
	//btTarget 1 = target
	//btTarget 2 = self skill
	GETAIACTDATA(024);
    //	//Log(MSG_DEBUG, "Do Skill btTarget %i nSkill %i nMotion %i",data->btTarget,data->nSkill,data->nMotion);
    //	//Log(MSG_DEBUG, "entity %i",entity->clientid);
    //	//Log(MSG_DEBUG, "entity->findChar %i",entity->findChar->clientid);
    //	//Log(MSG_DEBUG, "entity->nearChar %i", entity->nearChar->clientid);
	CSkills* thisskill = GServer->GetSkillByID( data->nSkill );
	CCharacter* monster = entity;
	//if(monster->Battle->atktype != 0)
	//{
    //    //Log(MSG_DEBUG,"Cannot apply battle attacktype. Monster already has one");
    //    return AI_FAILURE;
    //}
    //Log(MSG_DEBUG,"AIACT(024)skill attack id: %i target: %i type: %i btTarget: %i nMotion: %i", data->nSkill, thisskill->target, thisskill->skilltype, data->btTarget, data->nMotion);
	switch (thisskill->skilltype)
	{
        case 3: //damage action
        case 6: //magic attack
        {
            CCharacter* target = entity->GetCharTarget( );
            //Log(MSG_DEBUG,"SKILL_ATTACK or DAMAGE_ACTION selected");
            if(target==NULL)
            {
                //Log(MSG_DEBUG,"No target can be found for this skill");
                return AI_FAILURE;
            }
            //Log(MSG_DEBUG,"SKILL_ATTACK selected. target: %i",target->clientid);
            monster->StartAction( (CCharacter*) target, SKILL_ATTACK, data->nSkill );
        }
        break;
        case 7: //AOE magic attack
        {
            CCharacter* target = entity->GetCharTarget( );
            //Log(MSG_DEBUG,"AOE_TARGET selected");
            if(target == NULL)
            {
                //Log(MSG_DEBUG,"No target can be found for this skill");
                return AI_FAILURE;
            }
            //Log(MSG_DEBUG,"AOE_TARGET selected. target: %i",target->clientid);
            monster->StartAction( (CCharacter*) target, AOE_TARGET, data->nSkill );
        }
        break;
        case 8: //self buff
        {
            //Log(MSG_DEBUG,"BUFF_SELF selected.");
            monster->StartAction( NULL, BUFF_SELF, data->nSkill );
        }
        break;
        case 9: //skill buff
        case 13://skill buff
        case 11: //heal
        {
            CCharacter* target = entity->GetCharTarget( );
            if(target == NULL) //some skills always return a NULL target here
            {
                if(entity->nearChar == NULL) // maybe there really is no possible target.
                {
                    //Log(MSG_DEBUG,"No target can be found for this skill");
                    return AI_FAILURE;
                }
                else //so we are going to have them select a NEW target (if possible) rather than return AI_FAILURE
                {
                    //Log(MSG_DEBUG,"SKILL_BUFF type 13 selected. NEW target: %i",entity->nearChar->clientid);
                    monster->StartAction( (CCharacter*) entity->nearChar, SKILL_BUFF, data->nSkill );
                }
            }
            else
            {
                //Log(MSG_DEBUG,"SKILL_BUFF type %i selected. target: %i",thisskill->skilltype, target->clientid);
                monster->StartAction( (CCharacter*) target, SKILL_BUFF, data->nSkill );
            }
        }
        break;
        case 10: //heal AOE centered on self
            //Log(MSG_DEBUG,"BUFF_AOE selected. Skill id %i", data->nSkill);
            monster->StartAction( NULL, BUFF_AOE, data->nSkill );
        break;
        case 17: //skill AOE centered on self
        {
            //Log(MSG_DEBUG,"SKILL_AOE selected. Skill id %i", data->nSkill);
            monster->StartAction( NULL, SKILL_AOE, data->nSkill );
        }
        break;
        default:
        {
            ////Log(MSG_WARNING,"Skill type not recognized. type: %i",thisskill->skilltype);
        }
        break;
    }
    /*
    if (data->btTarget == 0)
	{
        //CCharacter* target = entity->GetCharTarget();
        //if(target==NULL)return AI_FAILURE;
        //CCharacter* monster = entity;  //defined twice????
        //Log(MSG_DEBUG,"BUFF_AOE selected");
        monster->StartAction( NULL, BUFF_AOE, data->nSkill );
    }
	else if (data->btTarget == 1)
	{
        CCharacter* target = entity->GetCharTarget( );
        if(target==NULL)return AI_FAILURE;
        if(data->nMotion == 8)
        {
            //Log(MSG_DEBUG,"SKILL_ATTACK selected");
            monster->StartAction( (CCharacter*) target, SKILL_ATTACK, data->nSkill );
        }
        else
        {
            //Log(MSG_DEBUG,"SKILL_BUFF selected");
            monster->StartAction( (CCharacter*) target, SKILL_BUFF, data->nSkill );
        }
    }
    else if (data->btTarget == 2)
	{
        if(thisskill->target == tYourself)
        {
             //Log(MSG_DEBUG,"BUFF_SELF selected");
             monster->StartAction( entity, BUFF_SELF, data->nSkill );
        }
        else if (thisskill->target == tAlly)
        {
            //Log(MSG_DEBUG,"BUFF_AOE selected");
            monster->StartAction( NULL, BUFF_AOE, data->nSkill );
        }
        else if (thisskill->target == tHostileCharacter)
        {
             CCharacter* target = entity->GetCharTarget( );
             if(target == NULL)return AI_FAILURE;
             if(data->nMotion == 8)
             {
                 //Log(MSG_DEBUG,"SKILL_ATTACK selected");
                 monster->StartAction( (CCharacter*) target, SKILL_ATTACK, data->nSkill );
             }
             else
             {
                 monster->StartAction( (CCharacter*) target, SKILL_BUFF, data->nSkill );
             }
        }
    }*/
	return AI_SUCCESS;
}

//Set Variable (1)
AIACT(025)
{
    //	if(entity->_EntityType != ENTITY_NPC) return AI_FAILURE;
	GETAIACTDATA(025);
	//Log(MSG_DEBUG,"AIP25 BEGIN");

	CMonster* monster = reinterpret_cast<CMonster*>(entity);
	if(monster == NULL) return AI_FAILURE;
	if(data->btVarIDX > 19) return AI_FAILURE;
	short tempval = GServer->ObjVar[monster->thisnpc->refNPC][data->btVarIDX];

	//Log(MSG_DEBUG,"AIP25 Set variable NPC %i, data->btOp=%i, data->iValue=%i, data->btVarIDX=%i",monster->thisnpc->refNPC,data->btOp,data->iValue,data->btVarIDX);

	switch(data->btOp)
    {
        case 5:
            tempval = data->iValue;
            break;
        case 6:
            tempval += data->iValue;
            break;
        case 7:
            tempval -= data->iValue;
        case 9:
            tempval++;
            break;
        default:
            return AI_FAILURE;
            break;
    }
    if(tempval < 0)tempval = 0;
    GServer->ObjVar[monster->thisnpc->refNPC][data->btVarIDX] = tempval;

    //LMA: EventID changed?
    //Mainprocess will take care of it since we don't have client ID here.
    if(data->btVarIDX==0)
    {
        //Log(MSG_DEBUG,"AIACT(025) eventID has changed from %i to %i",monster->thisnpc->eventid,tempval);
        monster->thisnpc->eventid=tempval;
    }


	return AI_SUCCESS;
}

//Set Variable (2)
AIACT(026)
{
	//Set WorldVAR
	//word nVarNo;	//Pos: 0x00
	//byte btOp;	//Pos: 0x08
	//dword iValue;	//Pos: 0x04
	return AI_SUCCESS;
}

//Set Variable (3)
AIACT(027)
{
	//Set EconomyVAR
	//word nVarNo;	//Pos: 0x00
	//byte btOp;	//Pos: 0x08
	//dword iValue;	//Pos: 0x04
	return AI_SUCCESS;
}

//Shout/Ann LTB String
AIACT(028)
{
	GETAIACTDATA(028);

    dword npcId = 0;
    //if(entity->_EntityType == ENTITY_NPC)

    if(data->iStrID>=GServer->maxltbaip)
    {
        //Log(MSG_INFO,"AIACT(028) AIP LTB index error %i>=%i",data->iStrID,GServer->maxltbaip);
        return AI_SUCCESS;
    }

    CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);
    switch(data->btMsgType)
    {
        case 0: //whisper to client
            // don't think this is possible. No way to get a character to send it to??
        break;
        case 1: //shout to map
        {
            //Log(MSG_INFO,"AIP NPC %s (%i) shouts to map.",GServer->GetNPCNameByType(thisMonster->aip_npctype),thisMonster->aip_npctype);
            //GServer->NPCShout(thisMonster,GServer->Ltbstring[data->iStrID]->LTBstring,GServer->Ltbstring[data->iStrID]->NPCname);
            GServer->NPCShout(thisMonster,GServer->LtbstringQSD[data->iStrID]->LTBstring,GServer->GetNPCNameByType(thisMonster->aip_npctype));
        }
        break;
        case 2: //announce to server.
        {
            //Log(MSG_INFO,"AIP NPC %s (%i) announces to server.",GServer->GetNPCNameByType(thisMonster->aip_npctype),thisMonster->aip_npctype);
            //GServer->NPCAnnounce(GServer->Ltbstring[data->iStrID]->LTBstring,GServer->Ltbstring[data->iStrID]->NPCname);
            GServer->NPCAnnounce(GServer->Ltbstring[data->iStrID]->LTBstring,GServer->GetNPCNameByType(thisMonster->aip_npctype));
        }
        break;
    }

        //npcId = reinterpret_cast<CNpc*>(entity)->NpcID;
    //	}else if(entity->_EntityType == ENTITY_MONSTER){
    //		npcId = reinterpret_cast<CMonster*>(entity)->MonID;
    //	}else{
    //		return AI_FAILURE;
    //	}
    //	std::map<dword, char*>::iterator triggerITR = server->NpcNames.find(npcId);
    //	if(triggerITR == server->NpcNames.end()) return AI_FAILURE;

    //	char* npcName = triggerITR->second;
    //	char* sayStr = server->lngAi->Data(data->iStrID, 1);
    //	if(sayStr == NULL) return AI_FAILURE;
    //	if(data->btMsgType == 0){
		//Chat
    //		CPacket pakout(0x783);
    //		pakout.Add<dword>(entity->_ClientID);
    //		pakout.Add<string>(sayStr);
    //		server->SendPacketToZone(entity, &pakout);
    //	}else if(data->btMsgType == 1){
		//Shout
    //		CPacket pakout(0x785);
    //		pakout.Add<string>(npcName);
    //		pakout.Add<string>(sayStr);
    //		server->SendPacketToZone(entity, &pakout);
    //	}else if(data->btMsgType == 2){
		//Announce
    //		CPacket pakout(0x702);
    //		pakout.AddBytes((byte*)npcName, strlen(npcName));
    //		pakout.Add<byte>('>');
    //		pakout.Add<string>(sayStr);
    //		server->SendPacketToZone(entity, &pakout);
    //	}
    //	delete [] sayStr;
    //Log(MSG_DEBUG, "AIACT(028)");
	return AI_SUCCESS;
}

//Move to my owner's location
AIACT(029)
{
	//Move within 20% of the distance of my "CALLER"
	GETAIACTDATA(029);
    //	if(entity->_EntityType != ENTITY_MONSTER) return AI_FAILURE;
    //	CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);
    //	CWorldEntity* caller = thisMonster->thisZone->GetEntity(thisMonster->_CallerID);
    //	if(caller == NULL) return AI_FAILURE;
    //	caller->UpdatePosition();
    //	thisMonster->UpdatePosition();
    if(!entity->IsMonster( )) return AI_FAILURE;
	CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);
	CMap* map = GServer->MapList.Index[thisMonster->Position->Map];
	CCharacter* caller = map->GetCharInMap( thisMonster->owner );
	if(caller == NULL) return AI_FAILURE;
	caller->UpdatePosition(false);
	thisMonster->UpdatePosition(thisMonster->stay_still);


    //	float fMoveDistance = thisMonster->basic.pos.distance(caller->basic.pos) * 0.2;

    //	float m = float(caller->basic.pos.y - thisMonster->basic.pos.y) / float(caller->basic.pos.x - thisMonster->basic.pos.x);
    //	float c = (m * thisMonster->basic.pos.x) + thisMonster->basic.pos.y;
    //	float y = (m * fMoveDistance) + c;
    //	float x = (fMoveDistance - c) / m;
    //	thisMonster->stance = 1;
	thisMonster->thisnpc->stance = 1;
    thisMonster->SetStats();
    thisMonster->Position->source = caller->Position->current;
    thisMonster->MoveTo(caller->Position->current);
    //	thisMonster->CalculateStats();
    //	thisMonster->MoveTo(x, y);

	return AI_SUCCESS;
}

//Do Trigger
AIACT(030)
{
	//word lenszTrigger;	//Pos: 0x00
	//char* szTrigger;	//Pos: 0x02
	GETAIACTDATA(030);
	char* tempName = reinterpret_cast<char*>(&data->szTrigger) - 2;
	dword hash = MakeStrHash(tempName);
	//Log(MSG_INFO, "Execute Quest Trigger %s[%d] [%08x]", tempName, data->lenszTrigger, hash);

    //CCharacter test...
    return (entity->ExecuteQuestTrigger(hash) == QUEST_SUCCESS)?AI_SUCCESS:AI_FAILURE;
    /*
    //LMA: cast to Player...
    CPlayer* player =new CPlayer(NULL);
    //player=reinterpret_cast<CPlayer*>(entity);

    player->Position->current.x=entity->Position->current.x;
    player->Position->current.y=entity->Position->current.y;
    player->Position->current.z=entity->Position->current.z;
    player->


    player->CheckQuest=0;
    int result=(player->ExecuteQuestTrigger(hash) == QUEST_SUCCESS)?AI_SUCCESS:AI_FAILURE;
    //Log(MSG_INFO,"AIACT(030) after ExecuteQuestTrigger");
    delete player;
    //Log(MSG_INFO,"After delete");
    return result;
    */

    /*
    CPlayer* lma_player=reinterpret_cast<CPlayer*>(entity);
    lma_player->CheckQuest=0;

    return (lma_player->ExecuteQuestTrigger(hash) == QUEST_SUCCESS)?AI_SUCCESS:AI_FAILURE;
    */
}

//set monster's attack target to the same as the owner
AIACT(031)
{
    //Log(MSG_DEBUG, "AIACT(031)");
	//Attack my "CALLER"(s target) if he is not an ally (must be caller's target...)
    //	if(entity->_EntityType != ENTITY_MONSTER) return AI_FAILURE;
    //	CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);

    //	CWorldEntity* caller = thisMonster->thisZone->GetEntity(thisMonster->_CallerID);
    //	if(caller == NULL) return AI_FAILURE;

    //	CWorldEntity* target = caller->thisZone->GetEntity(caller->_TargetID);
    //	if(target == NULL) return AI_FAILURE;

    //	thisMonster->Attack(target);
    if(!entity->IsMonster( )) return AI_FAILURE;
	CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);
	CMap* map = GServer->MapList.Index[thisMonster->Position->Map];
	CCharacter* caller = map->GetCharInMap( thisMonster->owner );
	if(caller == NULL) return AI_FAILURE;
	thisMonster->Position->source=caller->Position->current;
	CCharacter* target = map->GetCharInMap(caller->Battle->target);
	if(target == NULL) return AI_FAILURE;
	thisMonster->StartAction( (CCharacter*) target, NORMAL_ATTACK, 0 );
    //Log(MSG_DEBUG, "AIACT(031 END");

	return AI_SUCCESS;
}

//Zone (1)
AIACT(032)
{
	//word nZoneNo;	//Pos: 0x00
	//byte btOnOff;	//Pos: 0x02
	//Set PK Flag (btOnOff) in nZoneNo
	GETAIACTDATA(032);
	//Log(MSG_DEBUG, "AIACT(032) zone (1)");
	return AI_SUCCESS;
}

//Zone (2)
AIACT(033)
{
	//word nZoneNo //if 0, current map
	//word nNewValue
	//if nNewValue == 2 -> toggle
	//else set regen system nNewValue (0 = off, 1 = on)
	GETAIACTDATA(033);
	//Log(MSG_DEBUG, "AIACT(033) zone (2)");
	return AI_SUCCESS;
}

//Item (?)
AIACT(034)
{
	//word nItemNum;	//Pos: 0x00
	//word nCount;	//Pos: 0x02
	//Give item to "CALLER"
	GETAIACTDATA(034);
	//Log(MSG_DEBUG, "AIACT(034) Item (?)");
	return AI_SUCCESS;
}

//Set Variable (4)
AIACT(035)
{
	//Set AiVAR
	GETAIACTDATA(035);
	CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);
	if(data->nVarIDX >19)return AI_FAILURE;
    int tempval = thisMonster->AIVar[data->nVarIDX];
    switch(data->btOp)
    {
        case 6:
            tempval += data->iValue;
            break;
        case 7:
            tempval -= data->iValue;
            if(tempval <= 0)
            {
                thisMonster->AIVar[data->nVarIDX] = 0;
                return AI_FAILURE;
            }
        case 9:
            tempval++;
            break;
        default:
            return AI_FAILURE;
            break;
    }
    thisMonster->AIVar[data->nVarIDX] = tempval;
	//thisMonster->thisnpc->Objvar->SetVar(data->btOp, data->iValue); //code not working
	return AI_SUCCESS;
}

//Monster (1)
AIACT(036)
{
	//word nMonster;	//Pos: 0x00
	//byte btMaster;	//Pos: 0x02
	//Spawn nMonster at my position (has btMaster)?
	GETAIACTDATA(036);
    //	CWorldEntity* master = NULL;
    //	if(data->btMaster) master = entity;
	CMonster* monster = reinterpret_cast<CMonster*>(entity); //need this to get the spawnid of the entity
	CMap* map = GServer->MapList.Index[entity->Position->Map];
    map->AddMonster( data->nMonster, entity->Position->current, data->btMaster, NULL,NULL,monster->Status->spawnid, 10 );
	//Log(MSG_DEBUG, "AIACT(36) monster (1) no code here");
	return AI_SUCCESS;
}

//Monster (2)
AIACT(037)
{
	//word nMonster;	//Pos: 0x00
	//word nPos;	//Pos: 0x02
	//dword iDistance;	//Pos: 0x04
	//byte btMaster;	//Pos: 0x08

	//Spawn nMonster at nPos within iDistance (has btMaster)?
	//nPos = 0 my pos
	//nPos = 1 m_pDestCHAR pos
	//nPos = 2 target pos
    GETAIACTDATA(037);
    CMap* map = GServer->MapList.Index[entity->Position->Map];
	CMonster* monster = reinterpret_cast<CMonster*>(entity); //need this to get the spawnid of the entity
	if(monster == NULL) return AI_FAILURE;

	fPoint position;

	if(data->nPos == 0) //spawn monster in a circle with radius iDistance around my current position
    {
        position = GServer->RandInCircle( entity->Position->current, data->iDistance );
        map->AddMonster( data->nMonster, position, data->btMaster,NULL,NULL, monster->Status->spawnid, 10 );
    }
    else if(data->nPos == 1) //spawn monster in a circle with radius iDistance around my destiny position
    {
        position = GServer->RandInCircle( entity->Position->destiny, data->iDistance );
        map->AddMonster( data->nMonster, position, data->btMaster,NULL,NULL, monster->Status->spawnid, 10 );
		//dest char
	}
    else if(data->nPos == 2) //spawn monster in a circle with radius iDistance around my target's current position
    {
        CCharacter* target = entity->GetCharTarget( );
        if(target == NULL) return AI_FAILURE;
        position = GServer->RandInCircle( target->Position->current, data->iDistance );
        map->AddMonster( data->nMonster, position, data->btMaster,NULL,NULL, monster->Status->spawnid, 10 );
    }
	return AI_SUCCESS;
}
