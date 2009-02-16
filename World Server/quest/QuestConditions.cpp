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

// Props to ExJam for this code :D Ported to OSpRose by Drakia
#include "../worldserver.h"

//Check Quest
QUESTCOND(000){
	GETCONDDATA(000);
  if( client->questdebug )
    server->SendPM(client, "Check quest: %i", data->iQuestSN);
	for(dword i = 0; i < 10; i++){
		if(client->quest.quests[i].QuestID == data->iQuestSN) {
		  client->CheckQuest = i;
      if( client->questdebug )
        server->SendPM(client, "Check Quest - Found!");
			return QUEST_SUCCESS;
        }
	}
  if( client->questdebug )
    server->SendPM(client, "Check Quest - Not Found!");
	return QUEST_FAILURE;
}

//Check Quest Variable
QUESTCOND(001){
    GETCONDDATA(001);
	int retVal = 1;
	for(int i = 0; i < data->iDataCnt; i++)
	{
		dword address = i * sizeof(STR_QUEST_DATA);
		address += (dword)data;
		address += 4;
		STR_QUEST_DATA* curQst = (STR_QUEST_DATA*)address;
		word nValue = curQst->nValue;
		word tempValue = client->GetQuestVar(curQst->m_wVarTYPE, curQst->m_wVarNO);
		retVal = OperateValues<word>(curQst->btOp, &tempValue, curQst->nValue);
    if( client->questdebug )
      server->SendPM(client, "Check Quest Var[%04x][%i] - %i (Op: %i)", curQst->m_wVarTYPE, curQst->m_wVarNO, curQst->nValue, curQst->btOp);
		if(retVal == 0) return QUEST_FAILURE;
    }
	return (retVal == 0)?QUEST_FAILURE:QUEST_SUCCESS;
}

//Check Quest Variable
QUESTCOND(002){
	return QUEST_COND_001(server, client, raw);
}

//Check Stats
QUESTCOND(003){
	GETCONDDATA(003);
	for(int i = 0; i < data->iDataCnt; i++)
	{
		dword address = i * 0x0C;
		address += (dword)data;
		address += 4;
		STR_ABIL_DATA* curAbil = (STR_ABIL_DATA*)address;
        if( client->questdebug )
          server->SendPM(client, "Check Stat[%i] - %i (Op: %i)", curAbil->iType, curAbil->iValue, curAbil->btOp);
		switch( curAbil->iType )
		{
            case sGender:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->Sex, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sJob:
            {
                word tempValue = client->CharInfo->Job / 100;
                    if(!OperateValues<word>(curAbil->btOp, (word*)&tempValue, curAbil->iValue))
                    return QUEST_FAILURE;
            }
            break;

            case sUnion:
            {
                //Log(MSG_INFO,"[Union] ? QUESTCOND(003) btOp %i, value: %i",curAbil->btOp,curAbil->iValue);
                if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->unionid, curAbil->iValue))
                return QUEST_FAILURE;
                //Log(MSG_INFO,"[Union] OK QUESTCOND(003) GET union %i",curAbil->iValue);
            }
            break;
            case 81:    //LMA: Union Points (no break, it's NOT a mistake)...
            {
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->union01, curAbil->iValue))
                        return QUEST_FAILURE;
            }
            break;
            case 82:
            {
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->union02, curAbil->iValue))
                        return QUEST_FAILURE;
            }
            break;
            case 83:
            {
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->union03, curAbil->iValue))
                        return QUEST_FAILURE;
            }
            break;
            case 84:
            {
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->union04, curAbil->iValue))
                        return QUEST_FAILURE;
            }
            break;
            case 85:
            {
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->union05, curAbil->iValue))
                        return QUEST_FAILURE;
            }
            break;
            case sStrength:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->Attr->Str, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sDexterity:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->Attr->Dex, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sIntelligence:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->Attr->Int, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sConcentration:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->Attr->Con, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sCharm:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->Attr->Cha, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sSensibility:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->Attr->Sen, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sLevel:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->Stats->Level, curAbil->iValue))
                    return QUEST_FAILURE;
                break;

            case sStatPoints:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->StatPoints, curAbil->iValue))
                    return QUEST_FAILURE;
                break;
            case sMoney:
                    if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->Zulies, curAbil->iValue))
                    return QUEST_FAILURE;
                break;
        case sEXPRate:
            if(!OperateValues<int>(curAbil->btOp, (int*)&client->bonusxp, curAbil->iValue))
                        return QUEST_FAILURE;
        break;
            default:
                Log(MSG_WARNING, "QuestCond 003: Type Unknown: '%i'", curAbil->iType);
		}
	}
	return QUEST_SUCCESS;
}

//Check Items
QUESTCOND(004){
	GETCONDDATA(004);
	for(int i = 0; i < data->iDataCnt; i++){
		dword address = i * 0x10;
		address += (dword)data;
		address += 4;
		STR_ITEM_DATA* curItem = (STR_ITEM_DATA*)address;
    if( client->questdebug )
      server->SendPM(client, "Check Item - [Slot:%i][Type:%i]", curItem->iWhere, curItem->uiItemSN);
    // Check quest items for a specific amount
		if (curItem->iWhere==13)
		{
      // Ok, check the current Check'd quest.
      if (client->CheckQuest < 0) return QUEST_SUCCESS;
      unsigned int j = client->CheckQuest;
      for (unsigned int k = 0; k < 5; k++)
          if (client->quest.quests[j].Items[k].itemnum == (curItem->uiItemSN % 1000))
                {
            if( client->questdebug )
              server->SendPM(client, "Operate - btOp: %i Val1: %i Val2: %i", curItem->btOp, client->quest.quests[j].Items[k].count, curItem->iRequestCnt);
            if(!OperateValues<int>(curItem->btOp, (int*)(&client->quest.quests[j].Items[k].count), curItem->iRequestCnt))
                        	return QUEST_FAILURE;
                        else
                            return QUEST_SUCCESS;
                    }
      // Since the item doesn't exist, treat it as if there's 0 of them.
      int tempInt = 0;
      if(!OperateValues<int>(curItem->btOp, &tempInt, curItem->iRequestCnt))
        return QUEST_FAILURE;
      else
      	return QUEST_SUCCESS;
                }
    // Check equipped items for a specific item? - Drakia
		if(curItem->uiItemSN == 0 && curItem->iWhere != 0){
			int itemHead = client->items[curItem->iWhere].itemtype;
			if(!OperateValues<int>(curItem->btOp, &itemHead, curItem->uiItemSN))
				return QUEST_FAILURE;
		}
	}
	return QUEST_SUCCESS;
}

//Check Party
QUESTCOND(005){
	return QUEST_SUCCESS;
}

//Near Point
QUESTCOND(006){
	GETCONDDATA(006);
	client->UpdatePosition(false);
	if(data->iZoneSN != 0){
		if(client->Position->Map != data->iZoneSN)
			return QUEST_FAILURE;
	}

//	float dx = client->Position->current.x - (float)data->iX;
//	float dy = client->Position->current.y - (float)data->iY;
    float dx = client->Position->current.x - (float)(data->iX / 100);
    float dy = client->Position->current.y - (float)(data->iY / 100);
	float distance = sqrt((dx*dx) + (dy*dy));
	return (distance < data->iRadius)?QUEST_SUCCESS:QUEST_FAILURE;
}

//World Time
QUESTCOND(007){
    return QUEST_SUCCESS;
}

//Quest Time
QUESTCOND(008){
  GETCONDDATA(008);
  if( client->questdebug )
    server->SendPM(client, "QuestTime - ulTime: %i btOp: %i", data->ulTime, data->btOp);
  if (client->CheckQuest < 0) return QUEST_FAILURE; // Not checking a quest, don't return success
  long int Time = 0;
  if (server->STB_QUEST.rows[client->quest.quests[client->CheckQuest].QuestID][1] > 0) {
    Time += client->quest.quests[client->CheckQuest].StartTime; // Start time
    Time += server->STB_QUEST.rows[client->quest.quests[client->CheckQuest].QuestID][1] * 10; // Time to finish
    Time -= time(NULL); // Current time
    if (Time < 0) Time = 0; // Time is up
    Time /= 10; // Divide to get 10's of seconds
  }
  if (!OperateValues<dword>(data->btOp, (dword*)&Time, data->ulTime))
    return QUEST_FAILURE;
  else
    return QUEST_SUCCESS;
}

//Check Skill
QUESTCOND(009){
    GETCONDDATA(009);
	// Line not needed, never used - Drakia
	//int checkVal = (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
  if( client->questdebug )
    server->SendPM(client, "Check Skill: %i", data->iSkillSN1);
    /*
	for(dword i = 0; i < MAX_BASICSKILL; i++){
        if(client->bskills[i] == data->iSkillSN1)
        	return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
        // if(client->askill[i] == data->iSkillSN1)
        //	return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
        //if(client->pskill[i] == data->iSkillSN1)
        //	return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
    }
    */

	for (dword i = 0; i < MAX_ALL_SKILL; i++) {
        if(client->cskills[i].id == data->iSkillSN1)
        	return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
	}
	return (data->btOp)?QUEST_FAILURE:QUEST_SUCCESS;
}

//Unknown
QUESTCOND(010){
	return QUEST_SUCCESS;
}

//Object Variable
QUESTCOND(011){
/*	if(entity->_EntityType != ENTITY_NPC) return QUEST_FAILURE;
	GETCONDDATA(011);

	if(data->btWho == 0){
		CNpc* thisNpc = reinterpret_cast<CNpc*>(entity);
		thisNpc = thisNpc->SelectedNpc;
		if(thisNpc == NULL) return QUEST_FAILURE;

		short VarValue = thisNpc->ObjVar.GetVar(data->nVarNo);
		if(OperateValues(data->btOp, &VarValue, (short)data->iValue)) return QUEST_SUCCESS;
	}

	return QUEST_FAILURE;*/
	// Don't think we've implemented NPC's having quests. - Drakia
	Log(MSG_WARNING,"QSD CDT011 NOT CODED");
	return QUEST_SUCCESS;
}

//Select an IFO Object.
QUESTCOND(012)
{
    /*
    GETCONDDATA(012);

    //LMA: For now we do only this stuff for the warp gate :)
    bool is_ok=false;
    LogSp(MSG_INFO,"\t\t\t\t\t CDT %.3i: Select Object %i in map %i, IFO %i_%i.IFO (NOT CODED)",opcode,data->iEventID,data->iZone,data->iX,data->iY);
    if(GServer->WarpGate.id!=data->iEventID||GServer->WarpGate.IfoX!=data->iX||GServer->WarpGate.IfoY!=data->iY||GServer->WarpGate.mapid!=data->iZone)
    {
        return QUEST_FAILURE;
    }

    //We select as refNPC the WarpGate ^_^
    if(GServer->WarpGate.Npc==NULL)
    {
        return QUEST_FAILURE;
    }

    client->quest.selectedNpc = GServer->WarpGate.Npc;
    Log(MSG_INFO,"CDTQ 012 Warp Gate Selected");
    */
    Log(MSG_WARNING,"QSD CDT012 NOT CODED");


	return QUEST_SUCCESS;
}


//Select NPC
QUESTCOND(013){
    GETCONDDATA(013);

    /*if(entity->_EntityType != ENTITY_NPC) return QUEST_FAILURE;

    CNpc* thisNpc = reinterpret_cast<CNpc*>(entity);
    std::map<dword, CNpc*>::iterator triggerITR = server->NpcList.find(data->iNpcNo);
    if(triggerITR == server->NpcList.end()){
        thisNpc->SelectedNpc = NULL;
        return QUEST_FAILURE;
    }
    thisNpc->SelectedNpc = triggerITR->second;

    return QUEST_SUCCESS;*/
    // More NPC specific stuff
    CMap* thisMap = GServer->MapList.Index[client->Position->Map];
    CNPC* thisNpc = thisMap->GetNPCInMapQSD(data->iNpcNo);

    if (thisNpc == NULL) {
        Log (MSG_WARNING, "Questcondition 13: NPC not found");
        return QUEST_FAILURE;
    }

    client->quest.selectedNpc = thisNpc;

    return QUEST_SUCCESS;
}



//Check Quest Flag
QUESTCOND(014){
    GETCONDDATA(014);
  if( client->questdebug )
    server->SendPM(client, "Check QFlag[%i] == %i", data->nSN, data->btOp);
	bool dataOp = (data->btOp)?true:false;
	return (client->quest.GetFlag(data->nSN) == dataOp)?QUEST_SUCCESS:QUEST_FAILURE;
}

//Unknown
QUESTCOND(015){
    return QUEST_SUCCESS;
}

//Zone Time
QUESTCOND(016){
    return QUEST_SUCCESS;
}

//NPC & Obj Variables?
QUESTCOND(017){
    return QUEST_SUCCESS;
}

//Time on Date
QUESTCOND(018){
    return QUEST_SUCCESS;
}

//Time on Day
QUESTCOND(019){
    return QUEST_SUCCESS;
}

//Unknown
QUESTCOND(020){
    return QUEST_SUCCESS;
}

//Unknown
QUESTCOND(021){
    return QUEST_SUCCESS;
}

//Check Server/Channel
QUESTCOND(022){
    return QUEST_SUCCESS;
}

//In Clan
QUESTCOND(023){
    return QUEST_SUCCESS;
}

//Clan Position
QUESTCOND(024){
    return QUEST_SUCCESS;
}

//Clan Contribution
QUESTCOND(025){
    return QUEST_SUCCESS;
}

//Clan Grade
QUESTCOND(026){
    return QUEST_SUCCESS;
}

//Clan Points
QUESTCOND(027){
    GETCONDDATA(027);
  if( client->questdebug )
    server->SendPM(client, "QUEST - Clan Points");
    switch(data->btOP)
    {
        case 0x01:
             /*
             BEGINPACKET( pak, 0x7e0 );
             ADDBYTE    ( pak, 0x5C ); //action to update clan points (charserver)
	         ADDWORD    ( pak, client->Clan->clanid);
	         ADDWORD    ( pak, client->clientid );
             ADDDWORD    ( pak, client->Clan->CP );
             ADDWORD    ( pak, 0x00);
             //GServer->SendISCPacket( &pak );
             //Log(MSG_NOTICE, "implement CharServer Communication at __FILE__ _LINE__");
             */

             //LMA: temp version...
            BEGINPACKET( pak, 0x7e0 );
            ADDBYTE    ( pak, 0xfe );
            ADDWORD    ( pak, client->CharInfo->charid);  //charid
            ADDDWORD    ( pak, 0);  //Clan points (to be added)
            cryptPacket( (char*)&pak, GServer->cct );
            send( GServer->csock, (char*)&pak, pak.Size, 0 );
            //Log(MSG_NOTICE, "implement CP nb at __FILE__ _LINE__");
            break;
    }
	return QUEST_SUCCESS;
}

//Clan Funds
QUESTCOND(028){
    return QUEST_SUCCESS;
}

//Clan Members
QUESTCOND(029){
    return QUEST_SUCCESS;
}

//Clan Skills
QUESTCOND(030){
    return QUEST_SUCCESS;
}

