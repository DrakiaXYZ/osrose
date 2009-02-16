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

//LMA: This file if specifically for CCharacter QSD (NPC, monsters...)
#include "../worldserver.h"
dword GetRewardValueC(dword function, dword amount, CCharacter* client, word nDupCNT){
	switch(function){
		case 0:
		{
			dword tempVal = amount + 0x1E;
            //tempVal *= client->Attr->Cha + 0x0a; // We need to add a way to get all stats totals (Including buff, E, etc) - Drakia
            tempVal *= 1 + 0x0a; // We need to add a way to get all stats totals (Including buff, E, etc) - Drakia
			tempVal *= (100 & 0xFFFF);//World Rate
			tempVal *= 0x14;//Fame + 0x14
			tempVal = ((tempVal / (client->Stats->Level + 0x46)) / 0x7530) + amount;
			return tempVal;
		}
		break;
		case 1:
		{
			dword tempVal = (client->Stats->Level + 3) * amount;
			//tempVal *= (client->Attr->Cha >> 1) + client->Stats->Level + 0x28;
			tempVal *= 1 + client->Stats->Level + 0x28;
			tempVal *= (100 & 0xFFFF);//World Rate
			return tempVal / 0x2710;
		}
		break;
		case 2:
			return (amount * nDupCNT);
		break;
		case 3:
		case 5:
		{
			dword tempVal = amount + 0x14;
			//tempVal *= client->Attr->Cha + 0x0a;
			tempVal *= 1 + 0x0a;
			tempVal *= (100 & 0xFFFF);//World Rate
			tempVal *= 0x14;//Fame + 0x14
			tempVal = ((tempVal / (client->Stats->Level + 0x46)) / 0x7530) + amount;
			return tempVal;
		}
		break;
		case 4:
		{
			dword tempVal = amount + 0x2;
			//tempVal *= (client->Attr->Cha + client->Stats->Level + 0x28);
			tempVal *= (1 + client->Stats->Level + 0x28);
			tempVal *= 0x28;//Fame + 0x28
			tempVal *= (100 & 0xFFFF);//World Rate
			return tempVal / 0x222E0;
		}
		break;
		case 6:
		{
			dword tempVal = amount + 0x14;
			//tempVal *= client->Attr->Cha + client->Stats->Level;
			tempVal *= 1 + client->Stats->Level;
			tempVal *= 0x14;//Fame + 0x14
			tempVal *= (100 & 0xFFFF);//World Rate
			return (tempVal / 0x2DC6C0) + amount;
		}
		break;
	}
	return amount;
}

//Update Quest
QUESTREWDC(000){
    /*
	GETREWDDATA(000);

	switch(data->btOp){//0 remove, 1 start, 2 replace quest keep items, 3 replace quest delete items, 4 select
		case 0:
		{
      if (client->ActiveQuest == data->iQuestSN) client->ActiveQuest = 0;
			for(dword i = 0; i < 10; i++){
				if(client->quest.quests[i].QuestID != data->iQuestSN) continue;

    				memset(&client->quest.quests[i], 0, sizeof(SQuest));
    				break;
    			}
            }
		break;
		case 1:
		{
			for(dword i = 0; i < 10; i++){
			  if(client->quest.quests[i].QuestID == data->iQuestSN) return QUEST_SUCCESS;
				if(client->quest.quests[i].QuestID != 0) continue;
				memset(&client->quest.quests[i], 0, sizeof(SQuest));
				client->quest.quests[i].QuestID = data->iQuestSN;
				client->quest.quests[i].StartTime = time(NULL);
				break;
			}
			client->ActiveQuest = data->iQuestSN;
		}
		break;
		case 2:
		{
			for(dword i = 0; i < 10; i++){
				if(client->quest.quests[i].QuestID != client->ActiveQuest) continue;
				client->quest.quests[i].QuestID = data->iQuestSN;
				client->quest.quests[i].StartTime = time(NULL);
				break;
            }
			client->ActiveQuest = data->iQuestSN;
		}
		break;
		case 3:
		{
			for(dword i = 0; i < 10; i++){
				if(client->quest.quests[i].QuestID != client->ActiveQuest) continue;
				memset(&client->quest.quests[i], 0, sizeof(SQuest));
				client->quest.quests[i].QuestID = data->iQuestSN;
				client->quest.quests[i].StartTime = time(NULL);
				break;
            }
			client->ActiveQuest = data->iQuestSN;
		}
		break;
		case 4:
		{
			client->ActiveQuest = data->iQuestSN;
		}
		break;
	}
	*/

	//Log(MSG_WARNING,"Monster/NPC using QuestAction 000");

	return QUEST_SUCCESS;
}

//Update Quest Items
QUESTREWDC(001){
    GETREWDDATA(001);
    /*
	CItem tmpItem;
	tmpItem.itemtype = data->uiItemSN / 1000;
	tmpItem.itemnum = data->uiItemSN % 1000;
	tmpItem.count = data->nDupCNT;

	SQuest* curQuest = client->GetActiveQuest();
	if(curQuest == NULL) {
	  //Log(MSG_DEBUG, "Couldn't find active quest, wtf? Id %u", client->ActiveQuest);
	  return QUEST_FAILURE;
                         }
	curQuest->AddItem(&tmpItem, data->btOp);
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 001");
    return QUEST_SUCCESS;
}

//Set Quest Variable
QUESTREWDC(002){
    /*
    GETREWDDATA(002);
	for(dword i = 0; i < data->iDataCnt; i++){
		dword address = i * sizeof(STR_QUEST_DATA);
		address += (dword)data;
		address += 4;
		STR_QUEST_DATA* curQst = (STR_QUEST_DATA*)address;

		word nValue = curQst->nValue;
		word tempValue = client->GetQuestVar(curQst->m_wVarTYPE, curQst->m_wVarNO);
		OperateValues<word>(curQst->btOp, &tempValue, curQst->nValue);
		client->SetQuestVar(curQst->m_wVarTYPE, curQst->m_wVarNO, tempValue);
    }
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 002");
	return QUEST_SUCCESS;
}

//Update Stats
QUESTREWDC(003){
    /*
	GETREWDDATA(003);
	for(dword i = 0; i < data->iDataCnt; i++){
		dword address = i * 0x0C;
		address += (dword)data;
		address += 4;
		STR_ABIL_DATA* curAbil = (STR_ABIL_DATA*)address;

		switch( curAbil->iType )
		{
		case sGender:
			if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->Sex, curAbil->iValue))
				return QUEST_FAILURE;
			break;

		case sJob:
		{
			if(!OperateValues<int>(curAbil->btOp, (int*)&client->CharInfo->Job, curAbil->iValue))
				return QUEST_FAILURE;
			BEGINPACKET(pak, 0x721 );
			ADDWORD(pak, curAbil->iType );
			ADDDWORD(pak, curAbil->iValue );
			client->client->SendPacket( &pak );
		}
			break;

		case sUnion:
			//if(!OperateValues<word>(curAbil->btOp, &client->Attr->u, curAbil->iValue))
			//	return QUEST_FAILURE;
			// We actually don't have union code.
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
			// Send zuly update packet
            BEGINPACKET( pak, 0x71d );
            ADDQWORD( pak, client->CharInfo->Zulies );
            client->client->SendPacket( &pak );
            break;
		default:
			//Log(MSG_WARNING, "Type Unknown: '%i'", curAbil->iType);
			break;
		}
	}
	*/
	//Log(MSG_WARNING,"Monster/NPC using QuestAction 003");
	return QUEST_SUCCESS;
}

//Set Quest Variable
QUESTREWDC(004){
	//return QUEST_REWDC_002(server, client, raw);
	//Log(MSG_WARNING,"Monster/NPC using QuestAction 004");
	return QUEST_SUCCESS;
}

//Give Reward
QUESTREWDC(005){
    /*
	GETREWDDATA(005);
	switch(data->btTarget){
		case 0://EXP
		{
			client->CharInfo->Exp += GetRewardValueC(data->btEquation, data->iValue, client, 0);
			BEGINPACKET(pak, 0x79b);
			ADDDWORD(pak, client->CharInfo->Exp);
			ADDDWORD(pak, client->CharInfo->stamina);
			ADDWORD (pak, 0);
    			client->client->SendPacket(&pak);
              }
		break;
		case 1://Zuly
		{
			client->CharInfo->Zulies += GetRewardValueC(data->btEquation, data->iValue, client, 1);//dunno nDupCount for this one!
			BEGINPACKET(pak, 0x71D);
			ADDQWORD(pak, client->CharInfo->Zulies);
			client->client->SendPacket(&pak);
		}
		break;

        case 2://Item
        {
            CItem nItem;
            nItem.itemtype = data->iItemSN / 1000;
            nItem.itemnum = data->iItemSN % 1000;
            if(nItem.IsStackable()){
                nItem.count = GetRewardValueC(data->btEquation, data->iValue, client, 0);
            } else
                nItem.count = 1;

            //Maxxon: How is durability done in Evo?
            //nItem.durability = GServer->EquipList[nItem.itemtype].Index[nItem.itemnum]->d;
            nItem.durability = 50;
            nItem.gem = 0;
            nItem.stats = 0;
            nItem.refine = 0;
            nItem.socketed = 0;
            nItem.lifespan = 100;
            nItem.appraised = 1;
            dword slot = client->AddItem(nItem);
            if (slot == 0xffff) { // Fail
                BEGINPACKET( pak, 0x7a7);
                ADDWORD(pak, 0x00);
                ADDBYTE(pak, 0x03);
                ADDBYTE(pak, 0x00);
                client->client->SendPacket(&pak);
            } else { // Success
                BEGINPACKET( pak, 0x71f);
                ADDBYTE(pak, 0x01);
                ADDBYTE(pak, slot);
                ADDDWORD(pak, GServer->BuildItemHead ( client->items[slot]) );
                ADDDWORD(pak, GServer->BuildItemData ( client->items[slot]) );
                ADDDWORD( pak, 0x00000000 );
                ADDWORD ( pak, 0x0000 );
                client->client->SendPacket(&pak);
            }
        }
        break;

	}
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 005");
	return QUEST_SUCCESS;
}

//Restore HP/MP
QUESTREWDC(006){
    /*
	GETREWDDATA(006);
  client->Stats->HP = (long int)((float)client->Stats->MaxHP / 100.0f) * data->iPercentOfHP;
	client->Stats->MP = (long int)((float)client->Stats->MaxHP / 100.0f) * data->iPercentOfMP;
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 006");
	return QUEST_SUCCESS;
}

//Teleport
QUESTREWDC(007){
    /*
	GETREWDDATA(007);
	fPoint thispoint;
	thispoint.x = floor(((float)data->iX)/100);
	thispoint.y = floor(((float)data->iY)/100);
	GServer->TeleportTo(client, data->iZoneSN, thispoint);
	*/
	//Log(MSG_WARNING,"Monster/NPC using QuestAction 007");
	return QUEST_SUCCESS;
}

//Spawn Monster
QUESTREWDC(008){
    GETREWDDATA(008);

    //Log(MSG_DEBUG,"BEGIN QUESTREWDC(008)");
    fPoint position;
    dword mapId;
    if(data->iX == 0 || data->iY == 0 || data->iZoneSN == 0)
    {
        position.x = client->Position->current.x;
        position.y = client->Position->current.y;
        mapId = client->Position->Map;
    }
    else
    {
        position.x = data->iX / 100;
        position.y = data->iY / 100;
        mapId = data->iZoneSN;
    }

    for(dword i = 0; i < data->iHowMany; i++)
    {
        fPoint pos = GServer->RandInCircle( position, data->iRange );
        CMap* map = GServer->MapList.Index[mapId];

        //monster
        //Log(MSG_INFO, "Spawn mob[%i] @ map %i (%f,%f)", data->iMonsterSN, mapId,pos.x, pos.y);
        CMonster* mon = map->AddMonster( data->iMonsterSN, pos, 0, NULL, NULL, 0 , true );
        // ghost rackies = non aggresive, same for Xmas trees.
        if((data->iMonsterSN > 750 && data->iMonsterSN < 755) || (data->iMonsterSN >= 1474 && data->iMonsterSN <= 1489))
        {
            mon->thisnpc->aggresive = 0;
        }
        else
        {
            mon->thisnpc->aggresive = 999; // Force the mob to be agressive.
        }

        mon->lastSighCheck = 0; // Force sight check instantly.

        /*
        if((data->iMonsterSN >= 1474 && data->iMonsterSN <= 1489))
        {
            Log(MSG_DEBUG,"GETREWDDATA(008) Xmas tree[%i] @ map %i (%f,%f)", data->iMonsterSN, mapId,pos.x, pos.y);
        }

        if((data->iMonsterSN >= 3050 && data->iMonsterSN <= 3090))
        {
            Log(MSG_INFO, "GETREWDDATA(008) Xmas Box[%i] @ map %i (%f,%f)", data->iMonsterSN, mapId,pos.x, pos.y);
        }
        */

    }

    //Log(MSG_DEBUG,"END QUESTREWDC(008)");
    return QUEST_SUCCESS;
}

//Execute Quest Trigger
QUESTREWDC(009){
	GETREWDDATA(009);
	char* tempName = reinterpret_cast<char*>(&data->szNextTriggerSN) - 2;
	dword hash = MakeStrHash(tempName);
	return client->ExecuteQuestTrigger(hash);
    return QUEST_SUCCESS;
}

//Reset Stats
QUESTREWDC(010){
    /*
	client->CharInfo->StatPoints = 0;

	client->Attr->Str = 15;
	client->Attr->Dex = 15;
	client->Attr->Int = 15;
	client->Attr->Con = 15;
	client->Attr->Cha = 10;
	client->Attr->Sen = 10;

	for(int i = 2; i <= client->Stats->Level; i++) {
		client->CharInfo->StatPoints += 10;
		client->CharInfo->StatPoints += i / 2;
	}
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 010");
	return QUEST_SUCCESS;
}

//Update Object Var
QUESTREWDC(011)
{
	GETREWDDATA(011);
	if(data->btWho == 0)
	{
	    //Npc
        CMonster* monster = reinterpret_cast<CMonster*>(client);
        if(monster == NULL)
        {
            //Log(MSG_DEBUG,"QUESTREWDC(011) failed (monster null)");
            return QUEST_FAILURE;
        }


        short tempval = 0;

        //LMA: WarpGate or standard NPC?
        bool is_gate=false;

        if(monster->thisnpc->refNPC>1000&&monster->thisnpc->refNPC==GServer->WarpGate.virtualNpctypeID)
        {
            //WarpGate.
            if(data->nVarNo>19)
                return QUEST_FAILURE;
            tempval = GServer->WarpGate.IfoObjVar[data->nVarNo];
            is_gate=true;
        }
        else
        {
            tempval = GServer->ObjVar[monster->thisnpc->refNPC][data->nVarNo];
        }

        //Log(MSG_DEBUG,"QSD Set variable NPC %i, data->btOp=%i, data->iValue=%i, data->nVarNo=%i",monster->thisnpc->refNPC,data->btOp,data->iValue,data->nVarNo);

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

        /*
        if(monster->thisnpc->refNPC==1201)
        {
            Log(MSG_INFO,"Judy changes [%i] to %i",data->nVarNo,tempval);
        }
        */

        //WarpGate?
        if(is_gate)
        {
            short previous_val=GServer->WarpGate.IfoObjVar[data->nVarNo];
            GServer->WarpGate.IfoObjVar[data->nVarNo]=tempval;
            if(data->nVarNo==0&&previous_val!=tempval)
            {
                if(tempval==0)
                {
                    GServer->WarpGate.hidden=true;
                }
                else
                {
                    GServer->WarpGate.hidden=false;
                }

                //LMA: 2 do, check if really needed....
                //Forcing refresh.
                //GServer->pakSpawnIfoObject(NULL,GServer->WarpGate.virtualNpctypeID,true);
                BEGINPACKET( pak, 0x790 );
                ADDWORD    ( pak, GServer->WarpGate.clientID);
                ADDWORD    ( pak, tempval);
                GServer->SendToAllInMap(&pak,GServer->WarpGate.mapid);
            }

        }
        else
        {
            GServer->ObjVar[monster->thisnpc->refNPC][data->nVarNo] = tempval;
        }

		if(data->nVarNo==0)
		{
		    //LMA: event, we have to update, not here because we need the clientID :(
		    //mainprocess will do it for us ;)
		    monster->thisnpc->eventid=tempval;
		    /*
            BEGINPACKET( pak, 0x790 );
            ADDWORD    ( pak, monster->thisnpc->clientid );
            ADDWORD    ( pak, tempval );
            //GServer->SendToVisible(&pak,client);
            GServer->SendToAllInMap(&pak,monster->Position->Map);
            */
            //Log(MSG_INFO,"QUESTREWDC(011) Changing event for npc %i to %i, map %i",monster->thisnpc->refNPC,tempval,monster->Position->Map);
		}

	}
	else if	(data->btWho == 1)
	{
	    //Event
	    /*
		short VarValue = server->EventVar.GetVar(data->nVarNo);
		OperateValues(data->btOp, &VarValue, (short)data->iValue);
		server->EventVar.SetVar(data->nVarNo, VarValue);
		*/
        //Log(MSG_WARNING,"SERVER EVENT IN QUESTREWDC(011)");
        //return QUEST_SUCCESS;
	}


	return QUEST_SUCCESS;
}

//NPC Speak
QUESTREWDC(012){
	/*if(entity->_EntityType != ENTITY_NPC) return QUEST_FAILURE;
	GETREWDDATA(012);

	CNpc* thisNpc = reinterpret_cast<CNpc*>(entity);
	if(thisNpc->SelectedNpc == NULL) return QUEST_FAILURE;
	std::map<dword, char*>::iterator triggerITR = server->NpcNames.find(thisNpc->SelectedNpc->NpcID);
	if(triggerITR == server->NpcNames.end()) return QUEST_FAILURE;

	char* npcName = triggerITR->second;
	char* sayStr = server->lngQst->GetLTBStr(data->iStrID);
	if(sayStr == NULL) return QUEST_FAILURE;
	if(data->btMsgType == 1){
		//Shout
		CPacket pakout(0x785);
		pakout.Add<string>(npcName);
		pakout.Add<string>(sayStr);
		server->SendPacketToZone(thisNpc, &pakout);
	}else if(data->btMsgType == 2){
		//Announce
		CPacket pakout(0x702);
		pakout.AddBytes((byte*)npcName, strlen(npcName));
		pakout.Add<byte>('>');
		pakout.Add<string>(sayStr);
		server->SendPacketToZone(thisNpc, &pakout);
	}
	delete [] sayStr;

	return QUEST_SUCCESS;*/

	GETREWDDATA(012);
	//2do: check length + check msg ID...
    if(data->iStrID>=GServer->maxltbqsd)
    {
        //Log(MSG_INFO,"QUESTREWDC(012) QSD LTB index error %i>=%i",data->iStrID,GServer->maxltbqsd);
        return QUEST_SUCCESS;
    }

	CMonster* thisMonster = reinterpret_cast<CMonster*>(client);
	if(data->btMsgType == 1)
	{
	    ////Log(MSG_DEBUG,"%s shouts Nb %i::%s",GServer->LtbstringQSD[data->iStrID]->NPCname,data->iStrID,GServer->LtbstringQSD[data->iStrID]->LTBstring);
        //GServer->NPCShout(thisMonster,GServer->LtbstringQSD[data->iStrID]->LTBstring,GServer->LtbstringQSD[data->iStrID]->NPCname);
        //Log(MSG_DEBUG,"%s (%i) shouts Nb %i::%s",GServer->GetNPCNameByType(thisMonster->aip_npctype),thisMonster->aip_npctype,data->iStrID,GServer->LtbstringQSD[data->iStrID]->LTBstring);
        GServer->NPCShout(thisMonster,GServer->LtbstringQSD[data->iStrID]->LTBstring,GServer->GetNPCNameByType(thisMonster->aip_npctype));
	}
	else if(data->btMsgType == 2)
	{
	    //Log(MSG_DEBUG,"%s (%i) announces Nb %i::%s",GServer->GetNPCNameByType(thisMonster->aip_npctype),thisMonster->aip_npctype,data->iStrID,GServer->LtbstringQSD[data->iStrID]->LTBstring);
	    GServer->NPCAnnounce(GServer->LtbstringQSD[data->iStrID]->LTBstring,GServer->GetNPCNameByType(thisMonster->aip_npctype));
	}


	return QUEST_SUCCESS;
}

//Unknown
QUESTREWDC(013){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 013");
	return QUEST_SUCCESS;
}

//Learn Skill
QUESTREWDC(014){
    /*
    GETREWDDATA(014);
    GServer->LearnSkill(client, data->iSkillNo, false);
//	GServer->LearnSkill(client, data->iSkillNo);
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 014");
	return QUEST_SUCCESS;
}

//Set Quest Flag
QUESTREWDC(015){
    /*
	GETREWDDATA(015);
	client->quest.SetFlag(data->nSN, (data->btOp == 1)?true:false);
	*/
	//Log(MSG_WARNING,"Monster/NPC using QuestAction 015");
	return QUEST_SUCCESS;
}

//Unknown
QUESTREWDC(016){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 016");
	return QUEST_SUCCESS;
}

//Reset All Quest Flags
QUESTREWDC(017){
    /*
  memset(&client->quest.flags, 0, 64);
  */
  //Log(MSG_WARNING,"Monster/NPC using QuestAction 017");
	return QUEST_SUCCESS;
}

//Send Announcement
QUESTREWDC(018){
    /*
    GETREWDDATA(018);
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 018 (annoucment?)");
	return QUEST_SUCCESS;
}

//Execute Quest Trigger in Other Map
QUESTREWDC(019){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 019");
	return QUEST_SUCCESS;
}

//PvP Status
QUESTREWDC(020){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 020");
	return QUEST_SUCCESS;
}

//Set Respawn Position
QUESTREWDC(021){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 021");
	return QUEST_SUCCESS;
}

//Unknown
QUESTREWDC(022){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 022");
	return QUEST_SUCCESS;
}

//Raise Clan Grade - This is not the least bit efficient - Drakia
QUESTREWDC(023){
    /*
    GETREWDDATA(023);
    for(UINT i=0;i<GServer->MapList.Map.size();i++)
    {
        CMap* map = GServer->MapList.Map.at(i);
        if( map->PlayerList.size()<1 )
            continue;
        for(UINT j=0;j<map->PlayerList.size();j++)
        {
        CPlayer* player = map->PlayerList.at(j);
        if( player->Clan->clanid != client->Clan->clanid ) continue;
        player->Clan->grade++;

        //load clan info in char server
	    BEGINPACKET( pak, 0x7e0 );
	    ADDBYTE    ( pak, 0xfb ); //action to update clan informacion (charserver)
	    ADDWORD    ( pak, player->Clan->clanid );
	    ADDWORD    ( pak, player->Clan->grade );
        //GServer->SendISCPacket( &pak );
		Log (MSG_NOTICE, "implement CharServer communication in __FILE__ line __LINE__");

        //Send to other players
        RESETPACKET( pak, 0x7e0 );
        ADDBYTE    ( pak, 0x35 );
        ADDWORD    ( pak, player->clientid );
        ADDWORD    ( pak, player->Clan->clanid);
        ADDWORD    ( pak, 0x0000 );//???
        ADDWORD    ( pak, player->Clan->back );
        ADDWORD    ( pak, player->Clan->logo );
        ADDBYTE    ( pak, player->Clan->grade );//clan grade
        ADDBYTE    ( pak, 0x06 );//clan rank
        ADDSTRING  ( pak, player->Clan->clanname );
        ADDBYTE    ( pak, 0x00 );
        GServer->SendToVisible( &pak, player );
        }
    }
    GServer->DB->QExecute("UPDATE list_clan SET grade=%i WHERE id=%i", client->Clan->grade, client->Clan->clanid);
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 023");
	return QUEST_SUCCESS;
}

//Clan Money
QUESTREWDC(024){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 024");
	return QUEST_SUCCESS;
}

//Clan Points
QUESTREWDC(025){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 025");
	return QUEST_SUCCESS;
}

//Clan Skill
QUESTREWDC(026){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 026");
	return QUEST_SUCCESS;
}

//Clan Contribution
QUESTREWDC(027){
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 027");
	return QUEST_SUCCESS;
}

//Clan Teleportation - Again, not efficient. Maybe keep a list of pointers to clan members? - Drakia
QUESTREWDC(028){
    /*
    GETREWDDATA(028);
    fPoint telepos;
    fPoint newPos;
    telepos.x = data->iX/100;
    telepos.y = data->iY/100;
    for(UINT i=0;i<GServer->MapList.Map.size();i++)
    {
        CMap* map = GServer->MapList.Map.at(i);
        if( map->PlayerList.size()<1 )
            continue;
        for(UINT j=0;j<map->PlayerList.size();j++)
        {
            CPlayer* player = map->PlayerList.at(j);
            if( player->Clan->clanid != client->Clan->clanid ) continue;
            newPos = GServer->RandInCircle(telepos, data->iRange);
            GServer->TeleportTo(player, data->nZoneNo, newPos );
        }
    }
    */
    //Log(MSG_WARNING,"Monster/NPC using QuestAction 028");
	return QUEST_SUCCESS;
}

//Unspawn a NPC
QUESTREWDC(034){
    /*
    GETREWDDATA(034);

    if (client->quest.selectedNpc == NULL) {
        // WTF?
        return QUEST_FAILURE;
    }

    for (int i = 0; i < client->VisibleNPCs.size(); i++) {
        CNPC* curNpc = client->VisibleNPCs.at(i);
        if (curNpc == client->quest.selectedNpc) {
            // found!
            //client->VisibleNPCs.erase(client->VisibleNPCs.begin()+i);
            client->ClearObject(client->quest.selectedNpc->clientid);
            client->quest.selectedNpc = NULL;
            return QUEST_SUCCESS;
        }
    }
    return QUEST_FAILURE;
    */

    //Log(MSG_WARNING,"Monster/NPC using QuestAction 034");
    return QUEST_SUCCESS;
}


