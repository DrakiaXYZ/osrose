// Props to ExJam for this code :D Ported to OSpRose by Drakia

//LMA: This file if specifically for CCharacter QSD (NPC, monsters...)
#include "../worldserver.h"
#ifdef USENEWQUESTSYSTEM

//Check Quest
QUESTCONDC(000){
    /*
	GETCONDDATA(000);
	for(dword i = 0; i < 10; i++){
		if(client->quest.quests[i].QuestID == data->iQuestSN) {
		  client->CheckQuest = i;
			return QUEST_SUCCESS;
        }
	}
	return QUEST_FAILURE;
	*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 000");
	return QUEST_SUCCESS;
}

//Check Quest Variable
QUESTCONDC(001){
    /*
    GETCONDDATA(001);
	int retVal = 1;
	for(int i = 0; i < data->iDataCnt; i++) {
		dword address = i * sizeof(STR_QUEST_DATA);
		address += (dword)data;
		address += 4;
		STR_QUEST_DATA* curQst = (STR_QUEST_DATA*)address;
		word nValue = curQst->nValue;
		word tempValue = client->GetQuestVar(curQst->m_wVarTYPE, curQst->m_wVarNO);
		retVal = OperateValues<word>(curQst->btOp, &tempValue, curQst->nValue);
		if(retVal == 0) return QUEST_FAILURE;
    }
	return (retVal == 0)?QUEST_FAILURE:QUEST_SUCCESS;
	*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 001");
	return QUEST_SUCCESS;
}

//Check Quest Variable
QUESTCONDC(002){
	//return QUEST_CONDC_001(server, client, raw);
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 002");
	return QUEST_SUCCESS;
}

//Check Stats
QUESTCONDC(003){
    /*
	GETCONDDATA(003);
	for(int i = 0; i < data->iDataCnt; i++){
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
            word tempValue = client->CharInfo->Job / 100;
                if(!OperateValues<word>(curAbil->btOp, (word*)&tempValue, curAbil->iValue))
                return QUEST_FAILURE;
            break;
        }*/

			/*case sUnion: // Unions aren't implemented? - Drakia
				if(!OperateValues<int>(curAbil->btOp, (int*)&client->Union], curAbil->iValue))
				return QUEST_FAILURE;
			break;*/
        /*
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
			Log(MSG_WARNING, "QUESTCONDC 003: Type Unknown: '%i'", curAbil->iType);
		}
	}
	return QUEST_SUCCESS;
	*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 003");
	return QUEST_SUCCESS;
}

//Check Items
QUESTCONDC(004){
    /*
	GETCONDDATA(004);
	for(int i = 0; i < data->iDataCnt; i++){
		dword address = i * 0x10;
		address += (dword)data;
		address += 4;
		STR_ITEM_DATA* curItem = (STR_ITEM_DATA*)address;
    // Check quest items for a specific amount
		if (curItem->iWhere==13)
		{
      // Ok, check the current Check'd quest.
      if (client->CheckQuest < 0) return QUEST_SUCCESS;
      unsigned int j = client->CheckQuest;
      for (unsigned int k = 0; k < 5; k++)
          if (client->quest.quests[j].Items[k].itemnum == (curItem->uiItemSN % 1000))
                {
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
	*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 004");
	return QUEST_SUCCESS;
}

//Check Party
QUESTCONDC(005){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 005");
	return QUEST_SUCCESS;
}

//Near Point
QUESTCONDC(006){
    /*
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
	*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 006");
	return QUEST_SUCCESS;
}

//World Time
QUESTCONDC(007){
    //return QUEST_SUCCESS;
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 007");
	return QUEST_SUCCESS;
}

//Quest Time
QUESTCONDC(008){
    /*
  GETCONDDATA(008);
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
    */
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 008");
	return QUEST_SUCCESS;
}

//Check Skill
QUESTCONDC(009){
    /*
    GETCONDDATA(009);
	// Line not needed, never used - Drakia
	//int checkVal = (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
	for(dword i = 0; i < MAX_BASICSKILL; i++){
        if(client->bskills[i] == data->iSkillSN1)
        	return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
         //if(client->askill[i] == data->iSkillSN1)
        	//return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
        //if(client->pskill[i] == data->iSkillSN1)
        	//return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
    }
	for (dword i = 0; i < MAX_SKILL; i++) {
        if(client->cskills[i].id == data->iSkillSN1)
        	return (data->btOp)?QUEST_SUCCESS:QUEST_FAILURE;
	}
	return (data->btOp)?QUEST_FAILURE:QUEST_SUCCESS;*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 009");
	return QUEST_SUCCESS;
}

//Unknown
QUESTCONDC(010){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 010");
	return QUEST_SUCCESS;
}

//Object Variable
QUESTCONDC(011){
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

    GETCONDDATA(011);
	Log(MSG_DEBUG,"QSDC(011) nVarNo = %i, iValue = %i, btOp = %i",data->nVarNo, data->iValue,data->btOp);
	CMonster* monster = reinterpret_cast<CMonster*>(client);
	if(monster == NULL)
	{
	    Log(MSG_DEBUG,"QUESTCONDC(011) FAILED, monster NULL");
	    return QUEST_FAILURE;
	}

	int refNPC = monster->thisnpc->refNPC;
	int ObjvarIndex = data->nVarNo;

	int tempval = GServer->ObjVar[refNPC][ObjvarIndex];
	Log(MSG_DEBUG,"QSDC(011) Retrieved ObjVar[%i]=%i successfully NPC %i",ObjvarIndex,tempval,monster->thisnpc->refNPC);
	switch(data->btOp)
	{
        case 0:
             if(tempval == data->iValue)
                 return QUEST_SUCCESS;
             break;
        case 1:
             if(tempval > data->iValue)
                 return QUEST_SUCCESS;
             break;
        case 2:
             if(tempval >= data->iValue)
                 return QUEST_SUCCESS;
             break;
        case 3:
             if(tempval < data->iValue)
                 return QUEST_SUCCESS;
             break;
        case 4:
             if(tempval <= data->iValue)
                 return QUEST_SUCCESS;
             break;
        case 10:
             if(tempval != data->iValue)
                 return QUEST_SUCCESS;
             break;
        default:
        {
            Log(MSG_DEBUG,"QUESTCONDC(011) FAILED, switch default");
             return QUEST_FAILURE;
        }
             break;
    }

    Log(MSG_DEBUG,"QUESTCONDC(011) FAILED, compare false");
	return QUEST_FAILURE;
}

//Execute Trigger in Zone
QUESTCONDC(012){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 012");
	return QUEST_SUCCESS;
}


//Select NPC
QUESTCONDC(013){
    GETCONDDATA(013);

	Log(MSG_DEBUG,"Setting NPC ref number QUESTCONDC(013)");
	CMonster* monster = reinterpret_cast<CMonster*>(client);
	if(monster == NULL)
	{
	    Log(MSG_WARNING,"QUESTCONDC(013) FAILED, monster NULL");
	    return QUEST_FAILURE;
    }
	monster->thisnpc->refNPC = data->iNpcNo; // sets the reference variable for the correct ObjVar
    //Log(MSG_DEBUG,"Set NPC ref number %i successfully", monster->thisnpc->refNPC);


    return QUEST_SUCCESS;
}



//Check Quest Flag
QUESTCONDC(014){
    /*
    GETCONDDATA(014);
	bool dataOp = (data->btOp)?true:false;
	return (client->quest.GetFlag(data->nSN) == dataOp)?QUEST_SUCCESS:QUEST_FAILURE;
	*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 014");
	return QUEST_SUCCESS;
}

//Unknown
QUESTCONDC(015){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 015");
	return QUEST_SUCCESS;
}

//Zone Time
QUESTCONDC(016){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 016");
	return QUEST_SUCCESS;
}

//NPC & Obj Variables?
QUESTCONDC(017){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 017");
	return QUEST_SUCCESS;
}

//Time on Date
QUESTCONDC(018){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 018");
	return QUEST_SUCCESS;
}

//Time on Day
QUESTCONDC(019){
     Log(MSG_WARNING,"Monster/NPC using QuestCondition 019");
	return QUEST_SUCCESS;
}

//Unknown
QUESTCONDC(020){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 020");
	return QUEST_SUCCESS;
}

//Unknown
QUESTCONDC(021){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 021");
	return QUEST_SUCCESS;
}

//Check Server/Channel
QUESTCONDC(022){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 022");
	return QUEST_SUCCESS;
}

//In Clan
QUESTCONDC(023){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 023");
	return QUEST_SUCCESS;
}

//Clan Position
QUESTCONDC(024){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 024");
    return QUEST_SUCCESS;
}

//Clan Contribution
QUESTCONDC(025){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 025");
    return QUEST_SUCCESS;
}

//Clan Grade
QUESTCONDC(026){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 026");
    return QUEST_SUCCESS;
}

//Clan Points
QUESTCONDC(027){
    /*
    GETCONDDATA(027);
    switch(data->btOP)
    {
        case 0x01:

             //LMA: temp version...
            BEGINPACKET( pak, 0x7e0 );
            ADDBYTE    ( pak, 0xfe );
            ADDWORD    ( pak, client->CharInfo->charid);  //charid
            ADDDWORD    ( pak, 0);  //Clan points (to be added)
            cryptPacket( (char*)&pak, GServer->cct );
            send( GServer->csock, (char*)&pak, pak.Size, 0 );
            Log(MSG_NOTICE, "implement CP nb at __FILE__ _LINE__");
            break;
    }
	return QUEST_SUCCESS;
	*/
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 027");
	return QUEST_SUCCESS;
}

//Clan Funds
QUESTCONDC(028){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 028");
	return QUEST_SUCCESS;
}

//Clan Members
QUESTCONDC(029){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 029");
	return QUEST_SUCCESS;
}


//Clan Skills
QUESTCONDC(030){
    Log(MSG_WARNING,"Monster/NPC using QuestCondition 030");
	return QUEST_SUCCESS;
}

#endif

