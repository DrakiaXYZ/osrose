/*
    Rose Online Server Emulator
    Copyright (C) 2006,2007,2008 OSRose Team http://www.dev-osrose.com

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
bool CWorldServer::LoadSTBData( )
{
    Log( MSG_LOAD, "STB Data             " );  // all of the stb loading was from osiRose and ospRose
    STBStoreData( "3DData\\STB\\LIST_NPC.STB", &STB_NPC );
    STBStoreData( "3DData\\STB\\LIST_SKILL.STB", &STB_SKILL );
    STBStoreData( "3DData\\STB\\LIST_STATUS.STB", &STB_STATUS );
//    STBStoreData( "3DData\\STB\\LIST_QUEST.STB", &STB_QUEST ); //declared already in line 304
    STBStoreData( "3DData\\STB\\LIST_FACEITEM.STB", &STB_ITEM[0] );
	STBStoreData( "3DData\\STB\\LIST_CAP.STB", &STB_ITEM[1] );
	STBStoreData( "3DData\\STB\\LIST_BODY.STB", &STB_ITEM[2] );
	STBStoreData( "3DData\\STB\\LIST_ARMS.STB", &STB_ITEM[3] );
	STBStoreData( "3DData\\STB\\LIST_FOOT.STB", &STB_ITEM[4] );
	STBStoreData( "3DData\\STB\\LIST_BACK.STB", &STB_ITEM[5] );
	STBStoreData( "3DData\\STB\\LIST_JEWEL.STB", &STB_ITEM[6] );
	STBStoreData( "3DData\\STB\\LIST_WEAPON.STB", &STB_ITEM[7] );
	STBStoreData( "3DData\\STB\\LIST_SUBWPN.STB", &STB_ITEM[8] );
	STBStoreData( "3DData\\STB\\LIST_USEITEM.STB", &STB_ITEM[9] );
	STBStoreData( "3DData\\STB\\LIST_JEMITEM.STB", &STB_ITEM[10] );
	STBStoreData( "3DData\\STB\\LIST_NATURAL.STB", &STB_ITEM[11] );
	STBStoreData( "3DData\\STB\\LIST_QUESTITEM.STB", &STB_ITEM[12] );
	STBStoreData( "3DData\\STB\\LIST_PAT.STB", &STB_ITEM[13] );
	STBStoreData( "3DData\\STB\\LIST_PRODUCT.STB", &STB_PRODUCT );
	STBStoreData( "3DData\\STB\\LIST_SELL.STB", &STB_SELL );
	STBStoreData( "3DData\\STB\\LIST_ZONE.STB", &STB_ZONE );
	STBStoreData( "3DData\\STB\\ITEM_DROP.STB", &STB_DROP );
}

bool CWorldServer::LoadNPCData( )
{
//	Change MSG_LOAD to MSG_INFO for more details on the screen
	Log( MSG_LOAD, "NPC Data                    " );
	MYSQL_ROW row;
	MYSQL_RES *result = DB->QStore("SELECT id,life,walkspeed,runspeed,drivespeed,weapon, subweapon,level,hp,attackpower,hitpower,defense,strength,evasion,attackspeed,AI,exp,dropid,money,item,tab1,tab2,tab3,specialtab,attackdistance,aggresive,shp,dialog,eventid,askills,bskills,dskills,sigskill,delayskill FROM npc_data order by id");
    if(result==NULL) return false;
	while( row = mysql_fetch_row(result) )
    {
        CNPCData* newnpc = new (nothrow) CNPCData;
        if(newnpc==NULL)
        {
            Log( MSG_ERROR, "Error allocing memory" );
            continue;
        }


        newnpc->id = atoi(row[0]);
        newnpc->life = atoi(row[1]);
        newnpc->wspeed = atoi(row[2]);
        newnpc->rspeed = atoi(row[3]);
        newnpc->dspeed = atoi(row[4]);
        newnpc->weapon = atoi(row[5]);
        newnpc->subweapon = atoi(row[6]);
        newnpc->level = atoi(row[7]);
        newnpc->hp = atoi(row[8]);
        newnpc->atkpower = atoi(row[9]);
        newnpc->hitrate = atoi(row[10]);
        newnpc->defense = atoi(row[11]);
        newnpc->magicdefense = atoi(row[12]);
        newnpc->dodge = atoi(row[13]);
        newnpc->atkspeed = atof(row[14]);
        newnpc->AI = atoi(row[15]);
        newnpc->exp = atoi(row[16]);
        newnpc->dropid = atoi(row[17]);
        newnpc->money = atoi(row[18]);
        newnpc->item = atoi(row[19]);
        newnpc->tab1 = atoi(row[20]);
        newnpc->tab2 = atoi(row[21]);
        newnpc->tab3 = atoi(row[22]);
        newnpc->specialtab = atoi(row[23]);
        newnpc->atkdistance = atof(row[24])/100;
        newnpc->aggresive = atoi(row[25]);
        newnpc->shp = atoi(row[26]);
        newnpc->dialogid = atoi(row[27]);
        newnpc->eventid = atoi(row[28]);
        newnpc->side=0; //hidden
        newnpc->sidechance=0;   //hidden

        //LMA: Various skills for monsters
        for(int i=0;i<4;i++)
        {
          newnpc->askills[i]=0;
          newnpc->bskills[i]=0;
          newnpc->dskills[i]=0;
        }

        newnpc->lastskill=0;
        newnpc->sigskill=0;
        newnpc->delayskill=0;

        char *tmp;
        if((tmp = strtok( row[29] , "|"))!=NULL)
        {
            newnpc->askills[0]=atoi(tmp);
            for(int i=1;i<4; i++)
            {
                if((tmp = strtok( NULL , "|"))==NULL)
                    newnpc->askills[i]=newnpc->askills[0];
                else
                    newnpc->askills[i]=atoi(tmp);
            }

        }

        if((tmp = strtok( row[30] , "|"))!=NULL)
        {
            newnpc->bskills[0]=atoi(tmp);
            for(int i=1;i<4; i++)
            {
                if((tmp = strtok( NULL , "|"))==NULL)
                    newnpc->bskills[i]=newnpc->bskills[0];
                else
                    newnpc->bskills[i]=atoi(tmp);
            }

        }

        if((tmp = strtok( row[31] , "|"))!=NULL)
        {
            newnpc->dskills[0]=atoi(tmp);
            for(int i=1;i<4; i++)
            {
                if((tmp = strtok( NULL , "|"))==NULL)
                    newnpc->dskills[i]=newnpc->dskills[0];
                else
                    newnpc->dskills[i]=atoi(tmp);
            }

        }

        newnpc->sigskill=atoi(row[32]);
        newnpc->sigskill=atoi(row[33]);

        NPCData.push_back( newnpc );
    }
	DB->QFree( );
	Log( MSG_LOAD, "NPC Data loaded" );
	return true;
}

bool CWorldServer::LoadSkillData( )
{
	Log( MSG_LOAD, "Skills data                 " );
	MYSQL_ROW row;
	MYSQL_RES *result = DB->QStore("SELECT id,level,sp,type,range,target,power,duration,mp, success,weapon,class,rskills,lskills,buff1,buffv11,buffv12, buff2,buffv21,buffv22,buff3,buffv31,buffv32,clevel,aoe,aoeradius,script,value1,gm_aoe FROM skills_data order by id");
    if(result==NULL) return false;
	while( row = mysql_fetch_row(result) )
    {
        CSkills* newskill = new (nothrow) CSkills;
        if(newskill==NULL)
        {
            Log(MSG_ERROR, "Error allocing memory" );
            DB->QFree( );
            return false;
        }
        newskill->id=atoi(row[0]);
        newskill->level=atoi(row[1]);
        newskill->sp=atoi(row[2]);
        newskill->type=atoi(row[3]);
        newskill->range=atoi(row[4])/100;
        newskill->target=atoi(row[5]);
        newskill->atkpower=atoi(row[6]);
        newskill->duration=atoi(row[7]);
        newskill->mp=atoi(row[8]);
        newskill->success=atoi(row[9]);
        // Buffs get loaded
        newskill->buff[0]=atoi(row[14]);
        newskill->value1[0]=atoi(row[15]);
        newskill->value2[0]=atoi(row[16]);
        newskill->buff[1]=atoi(row[17]);
        newskill->value1[1]=atoi(row[18]);
        newskill->value2[1]=atoi(row[19]);
        newskill->buff[2]=atoi(row[20]);
        newskill->value1[2]=atoi(row[21]);
        newskill->value2[2]=atoi(row[22]);


        newskill->clevel=atoi(row[23]);
        newskill->aoe=atoi(row[24]);
        newskill->aoeradius=atoi(row[25])/100;
        newskill->script=atoi(row[26]);
        newskill->svalue1=atoi(row[27]);
        newskill->gm_aoe=atoi(row[28]); //LMA: GM AOE buff
        newskill->nbuffs = 0;
        if(newskill->buff[0]!=0)
            newskill->nbuffs += 1;
        if(newskill->buff[1]!=0)
            newskill->nbuffs += 2;
        if(newskill->buff[2]!=0)
            newskill->nbuffs += 4;
        char *tmp;
        //weapon list
        if((tmp = strtok( row[10] , "|"))==NULL)
            newskill->weapon[0]=0;
        else
            newskill->weapon[0]=atoi(tmp);
        for(unsigned int i=1;i<5; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                newskill->weapon[i]=0;
            else
                newskill->weapon[i]=atoi(tmp);
        }
        //class list
        if((tmp = strtok( row[11] , "|"))==NULL)
            newskill->c_class[0]=0;
        else
            newskill->c_class[0]=atoi(tmp);
        for(unsigned int i=1;i<4; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                newskill->c_class[i]=0;
            else
                newskill->c_class[i]=atoi(tmp);
        }
        //rskill list
        if((tmp = strtok( row[12] , "|"))==NULL)
            newskill->rskill[0]=0;
        else
            newskill->rskill[0]=atoi(tmp);
        for(unsigned int i=1;i<3; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                newskill->rskill[i]=0;
            else
                newskill->rskill[i]=atoi(tmp);
        }

        //rskill level list
        if((tmp = strtok( row[13] , "|"))==NULL)
            newskill->lskill[0]=0;
        else
            newskill->lskill[0]=atoi(tmp);
        for(unsigned int i=1;i<3; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                newskill->lskill[i]=0;
            else
                newskill->lskill[i]=atoi(tmp);
        }
        SkillList.push_back( newskill );
	}
	DB->QFree( );
	Log( MSG_LOAD, "Skills Data loaded" );
	return true;
}

bool CWorldServer::LoadTeleGateData( )
{
	Log( MSG_LOAD, "Telegates data              " );
	MYSQL_ROW row;
//	MYSQL_RES *result = DB->QStore("SELECT id,x,y,map FROM list_telegates");
	MYSQL_RES *result = DB->QStore("SELECT id, srcx, srcy, srcmap, destx, desty, destmap FROM list_telegates");
	if(result==NULL) return false;
	while( row = mysql_fetch_row(result) )
    {
		CTeleGate* thisgate = new (nothrow) CTeleGate;
        if(thisgate==NULL)
        {
            Log(MSG_ERROR, "Error allocing memory       " );
            DB->QFree( );
            return false;
        }
		thisgate->id = atoi(row[0]);
		thisgate->src.x = (float)atof(row[1]);
		thisgate->src.y = (float)atof(row[2]);
		thisgate->srcMap = atoi(row[3]);
		thisgate->dest.x = (float)atof(row[4]);
		thisgate->dest.y = (float)atof(row[5]);
		thisgate->destMap = atoi(row[6]);
//		thisgate->dest.x = (float)atof(row[1]);
//		thisgate->dest.y = (float)atof(row[2]);
//		thisgate->destMap = atoi(row[3]);
		TeleGateList.push_back( thisgate );
	}
	DB->QFree( );
	Log( MSG_LOAD, "Telegates Data loaded" );
	return true;
}

//Loading Quests
#ifdef USENEWQUESTSYSTEM
bool CWorldServer::LoadQuestSTB()
{
    STBStoreData( "3ddata/stb/LIST_QUEST.STB", &STB_QUEST );
    Log(MSG_INFO,"STB Loaded for QSD Version !!!");
    return true;
}
#endif

#ifndef USENEWQUESTSYSTEM
bool CWorldServer::LoadQuestData( )
{
    Log( MSG_LOAD, "Quest data                  " );
	MYSQL_ROW row;
	MYSQL_RES *result = DB->QStore("SELECT id,questid,mobs,items,itemsreward,exp,zulie,itemid,numitems,finalid,nitems, citems,script,value1,value2,value3,startItems FROM quest_data order by id");
    if(result==NULL) return false;
	while( row = mysql_fetch_row(result) )
    {
		CQuest* thisquest = new (nothrow) CQuest;
        if(thisquest==NULL)
        {
            Log(MSG_ERROR, "Error allocing memory" );
            DB->QFree( );
            return false;
        }
        thisquest->id = atoi(row[0]);
        thisquest->questid = atoi(row[1]);
        if( thisquest->questid == 0 )
        {
            delete thisquest;
            continue;
        }
        char *tmp;
        //load quest mobs
        if((tmp = strtok( row[2] , "|"))==NULL)
            thisquest->mobs[0]=0;
        else
            thisquest->mobs[0]=atoi(tmp);
        for(int i=1;i<10; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                thisquest->mobs[i]=0;
            else
                thisquest->mobs[i]=atoi(tmp);
        }
        //load quest items
        if((tmp = strtok( row[3] , "|"))==NULL)
            thisquest->items[0]=0;
        else
            thisquest->items[0]=atoi(tmp);
        for(int i=1;i<10; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                thisquest->items[i]=0;
            else
                thisquest->items[i]=atoi(tmp);
        }
        //load quest start items
        if((tmp = strtok( row[16] , "|"))==NULL)
            thisquest->startItems[0]=0;
        else
            thisquest->startItems[0]=atoi(tmp);
        for(int i=1;i<10; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                thisquest->startItems[i]=0;
            else
                thisquest->startItems[i]=atoi(tmp);
        }

         //load quests variables
        tmp = strtok( row[16] , "#");
        if((tmp = strtok( NULL , "#"))==NULL)
            thisquest->QVoffset=0;
        else
            thisquest->QVoffset=atoi(tmp);
        if((tmp = strtok( NULL , "#"))==NULL)
            thisquest->QVvalue=0;
        else
            thisquest->QVvalue=atoi(tmp);
        //load reward items
        if((tmp = strtok( row[4] , "|"))==NULL)
        {
            thisquest->Itemreward[0] = 0;
            thisquest->ItemType[0] = 0;
        }
        else
        {
            thisquest->Itemreward[0] = atoi(tmp)%1000;
            thisquest->ItemType[0] = atoi(tmp)/1000;
            if(atoi(tmp)>0&&thisquest->ItemType[0]==0)
            {
                Log(MSG_WARNING,"quest %i:: problem reward object %s(%i:%i) ",thisquest->id,tmp,thisquest->ItemType[0],thisquest->Itemreward[0]);
            }


        }
        for(int i=1;i<10; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
            {
                thisquest->Itemreward[i]=0;
                thisquest->ItemType[i]=0;
            }
            else
            {
                thisquest->Itemreward[i] = atoi(tmp)%1000;
                thisquest->ItemType[i] = atoi(tmp)/1000;

                if(atoi(tmp)>0&&thisquest->ItemType[i]==0)
                {
                    Log(MSG_WARNING,"quest %i:: problem reward object %s(%i:%i) ",thisquest->id,tmp,thisquest->ItemType[i],thisquest->Itemreward[i]);
                }

            }
        }
       //Load our items
        if((tmp = strtok( row[7] , "|"))==NULL)
            thisquest->itemid[0]=0;
        else
            thisquest->itemid[0]=atoi(tmp);
        for(int i=1;i<10; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                thisquest->itemid[i]=0;
            else
                thisquest->itemid[i]=atoi(tmp);
        }
        //Load our items count
        if((tmp = strtok( row[8] , "|"))==NULL)
            thisquest->numitems[0]=0;
        else
            thisquest->numitems[0]=atoi(tmp);
        for(int i=1;i<10; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                thisquest->numitems[i]=0;
            else
                thisquest->numitems[i]=atoi(tmp);
        }
        //Load our items reward count
        if((tmp = strtok( row[10] , "|"))==NULL)
            thisquest->CountItem[0]=0;
        else
            thisquest->CountItem[0]=atoi(tmp);
        for(int i=1;i<10; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                thisquest->CountItem[i]=0;
            else
                thisquest->CountItem[i]=atoi(tmp);
        }
        //Load our quest items
        if((tmp = strtok( row[11] , "|"))==NULL)
            thisquest->CItem[0]=0;
        else
            thisquest->CItem[0]=atoi(tmp);
        for(int i=1;i<5; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                thisquest->CItem[i]=0;
            else
                thisquest->CItem[i]=atoi(tmp);
        }
        thisquest->ExpReward = atoi( row[5] );
        thisquest->ZulieReward = atoi( row[6] );
        thisquest->finalid = atoi( row[9] );
        thisquest->script = atoi( row[12] );
        thisquest->value1 = atoi( row[13] );
        thisquest->value2 = atoi( row[14] );
        thisquest->value3 = atoi( row[15] );
		QuestList.push_back( thisquest );
	}
	DB->QFree( );
	Log( MSG_LOAD, "Quest Data loaded" );
	return true;
}
#endif

bool CWorldServer::LoadRespawnData( )
{
	Log( MSG_LOAD, "RespawnZones data           " );
	MYSQL_ROW row;
	MYSQL_RES *result = DB->QStore("SELECT id,x,y,map,radius,type FROM list_respawnzones");
    if(result==NULL) return false;
	while( row = mysql_fetch_row(result) )
    {
		CRespawnPoint* thisrespawnpoint = new (nothrow) CRespawnPoint;
        if(thisrespawnpoint==NULL)
        {
            Log(MSG_ERROR, "Error allocing memory" );
            DB->QFree( );
            return false;
        }
		thisrespawnpoint->id = atoi(row[0]);
		thisrespawnpoint->dest.x = (float)atof(row[1]);
		thisrespawnpoint->dest.y = (float)atof(row[2]);
		thisrespawnpoint->destMap = atoi(row[3]);
		thisrespawnpoint->radius = atoi(row[4]);
		thisrespawnpoint->masterdest = (atoi(row[5]) == 1);

        //LMA: check if out of memory.
        if (thisrespawnpoint->destMap>=MAX_MAP_DATA)
        {
           Log(MSG_WARNING,"RespawnZones, index overflow trapped %i>%i (increase MAX_MAP_DATA)",thisrespawnpoint->destMap,MAX_MAP_DATA);
           delete thisrespawnpoint;
           continue;
        }

		MapList.Index[thisrespawnpoint->destMap]->RespawnList.push_back( thisrespawnpoint );
	}
	DB->QFree( );
	Log( MSG_LOAD, "RespawnZones Data loaded" );
	return true;
}

bool CWorldServer::LoadChestData( )
{
    Log(MSG_LOAD, "Chest Data                   ");
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT chestid,reward,rewardtype,prob,maxamount,maxpossible FROM chest_data order by id");
    if(result==NULL) return false;
    while( row = mysql_fetch_row(result) )
    {
        CChest* newchest = new (nothrow) CChest;
        if(newchest==NULL)
        {
            Log( MSG_ERROR, "Error allocing memory" );
            continue;
        }
        newchest->chestid = atoi(row[0]);

        UINT value = 0;
        bool First = true;
        // items
        while((value=atoi(strtok(First?row[1]:NULL, "|")))!=0)
        {
            First = false;
            CReward* Reward = new (nothrow) CReward;
            if(Reward==NULL)
            {
                Log(MSG_WARNING, "\nError allocing memory [chestdata]" );
                continue;
            }
            Reward->id = value;
            newchest->Rewards.push_back( Reward );
        }

        value = 0;
        // Reward Type
        for(UINT j=0;j<newchest->Rewards.size();j++)
        {
            value = atoi(strtok((j==0?row[2]:NULL), "|"));
            if(value==0)
            {
                newchest->Rewards.erase(newchest->Rewards.begin() + j);
                Log(MSG_WARNING, "reward type not set! chestid: %i - reward id: %i - reward deleted", newchest->chestid, newchest->Rewards.at(j)->id );
            }
            else
            {
                newchest->Rewards.at(j)->type = value;
            }
        }

        newchest->rewardamount = 0;
        value = 0;
        // Reward Amount
        for(UINT j=0;j<newchest->Rewards.size();j++)
        {
            value = atoi(strtok((j==0?row[4]:NULL), "|"));
            if(value==0)
            {
                newchest->Rewards.erase(newchest->Rewards.begin() + j);
                Log(MSG_WARNING, "reward amount not set! chestid: %i - reward id: %i - reward deleted", newchest->chestid, newchest->Rewards.at(j)->id );
            }
            else
            {
            newchest->Rewards.at(j)->rewardamount = value;
            }
        }
        // Reward Total
        for(UINT j=0;j<newchest->Rewards.size();j++)
        {
            value = atoi(row[5]);
            {
            newchest->rewardposs = value;
//            newchest->Rewards.at(j)->rewardposs = value;
            }
        }

        newchest->probmax = 0;
        value = 0;
        // probability
        for(UINT j=0;j<newchest->Rewards.size();j++)
        {
            value = atoi(strtok((j==0?row[3]:NULL), "|"));
            if(value==0)
            {
                newchest->Rewards.at(j)->prob = 1;
                Log(MSG_WARNING, "Probability is not complete, chestid: %i - probability set to 1", newchest->chestid );
            }
            else
            {
                newchest->Rewards.at(j)->prob = value;
            }
            newchest->probmax += newchest->Rewards.at(j)->prob;
        }

        ChestList.push_back( newchest );
    }
    DB->QFree( );
    Log( MSG_LOAD, "Chest Data loaded" );
   	return true;
}

#ifdef USEIFO
bool CWorldServer::LoadMobGroups() {
  Log(MSG_LOAD, "MobGroups data    " );
  vector<CMobGroup*> mobGroups;
  MYSQL_ROW row;
  bool flag = true;
  char* tmp = NULL;
//  MYSQL_RES *result = DB->QStore("SELECT id, map, x, y, range, respawntime, `limit`, tacticalpoints, moblist FROM list_mobgroups");
  MYSQL_RES *result = DB->QStore("SELECT `id`, `map`, `x`, `y`, `range`, `respawntime`, `limit`, `tacticalpoints`, `moblist` FROM `list_mobgroups`");
  if (result == NULL) return false;
  while (row = mysql_fetch_row(result)) {
    CMobGroup* thisgroup = new (nothrow) CMobGroup;
    if (thisgroup == NULL) {
      Log(MSG_ERROR, "Error allocating memory");
      DB->QFree();
      return false;
    }
    thisgroup->id = atoi(row[0]);
    thisgroup->map = atoi(row[1]);
    thisgroup->point.x = atof(row[2]);
    thisgroup->point.y = atof(row[3]);
    thisgroup->range = atoi(row[4]);
    thisgroup->respawntime = atoi(row[5]);
    thisgroup->limit = atoi(row[6]);
    thisgroup->tacticalpoints = atoi(row[7]);
    char* mobList = row[8];

    thisgroup->lastRespawnTime = clock();
    thisgroup->active = 0;
    thisgroup->basicKills = 0;
    thisgroup->curTac = 0;
    thisgroup->curBasic = 0;


    thisgroup->basicMobs.clear();
    thisgroup->tacMobs.clear();

    // Fill in basic/tac mobs
    tmp = strtok(mobList, ",|");
    while (tmp != NULL) {
      int mobId = atoi(tmp);
      tmp = strtok(NULL, ",|");
      if (tmp == NULL) {
        Log(MSG_ERROR, "MobGroup %i is invalid", thisgroup->id);
        flag = false;
        break;
      }
      int amount = atoi(tmp);
      tmp = strtok(NULL, ",|");
      if (tmp == NULL) {
        Log(MSG_ERROR, "MobGroup %i is invalid", thisgroup->id);
        flag = false;
        break;
      }
      int tactical = atoi(tmp);
      CMob *thismob = new (nothrow) CMob;
      if (thismob == NULL) {
        Log(MSG_ERROR, "Error allocating memory");
        DB->QFree();
        return false;
      }
      thismob->amount = amount;
      thismob->tactical = tactical;
      thismob->mobId = mobId;
      thismob->thisnpc = GetNPCDataByID( thismob->mobId );
      thismob->mapdrop = GetDropData( thisgroup->map );
      thismob->mobdrop = GetDropData( thismob->thisnpc->dropid );
      if (thismob->thisnpc == NULL) {
        Log(MSG_WARNING, "Invalid mobId - Mob %i will not be added", atoi(row[0]));
        delete thismob;
        continue;
      }
      if (thismob->tactical)
        thisgroup->tacMobs.push_back(thismob);
      else
        thisgroup->basicMobs.push_back(thismob);
      tmp = strtok(NULL, ",|");
    }
    if (!flag) {
      delete thisgroup;
      continue;
    }
    MapList.Index[thisgroup->map]->MobGroupList.push_back(thisgroup);
    mobGroups.push_back(thisgroup);
    }
    DB->QFree( );
    return true;
}
#endif


bool CWorldServer::LoadMonsterSpawn( )
{
	Log( MSG_LOAD, "SpawnZones data             " );
    //clear the respawns data first

    for(int i=0;i<MapList.Map.size();i++)
    {
        MapList.Index[i]->MonsterSpawnList.clear();
    }

	MYSQL_ROW row;
	MYSQL_RES *result = DB->QStore("SELECT id,map,montype,min,max,respawntime,points,triggeramount,bossid FROM list_spawnareas");
//    MYSQL_RES *result = DB->QStore("SELECT id, map, montype, min, max, respawntime, points, spawntype, triggermontype, triggerammount, agressive, areatrigger, lim, spawnk FROM list_spawnareas");
	if(result==NULL) return false;
	while(row = mysql_fetch_row(result))
    {
        bool flag = true;
		char* tmp;
		CSpawnArea* thisspawn = new (nothrow) CSpawnArea;
        if(thisspawn==NULL)
        {
            Log(MSG_ERROR, "Error allocing memory" );
            DB->QFree( );
            return false;
        }
		thisspawn->id=atoi(row[0]);
		thisspawn->map=atoi(row[1]);
		thisspawn->montype=atoi(row[2]);
		thisspawn->min=atoi(row[3]);
		thisspawn->max=atoi(row[4]);
		thisspawn->respawntime=atoi(row[5]);
        //log(MSG_LOAD, "line 1 OK");
		//LMA: Adding support for spawn 'boss' (by Rob)
		thisspawn->nb_trigger=atoi(row[7]);
		thisspawn->bossid=atoi(row[8]);
		thisspawn->cu_trigger=0;
		thisspawn->bossdropID=0;

		if (thisspawn->nb_trigger==0||thisspawn->bossid==0)
		{
    		thisspawn->nb_trigger=0;
    		thisspawn->bossid=0;
        }
        else
        {
            CNPCData* tempnpc;
            tempnpc=GetNPCDataByID( thisspawn->bossid );
            if(tempnpc==NULL)
            {
                Log( MSG_WARNING, "Invalid montype %i for boss ID in spawn ID",thisspawn->bossid,thisspawn->id );
                thisspawn->bossdropID=0;
            }
            else
            {
                thisspawn->bossdropID=tempnpc->dropid;
            }

        }

		thisspawn->amon = 0;
		char* points;
		points = row[6];
		thisspawn->pcount = atoi(strtok( points , ",|"));
		thisspawn->points = new (nothrow) fPoint[thisspawn->pcount];
		if(thisspawn->points==NULL)
        {
            Log(MSG_ERROR, "Error allocing memory       " );
            delete thisspawn;
            DB->QFree( );
            return false;
        }
		thisspawn->lastRespawnTime = clock();
		for(int i=0; i<thisspawn->pcount; i++)
        {
			if ((tmp = strtok(NULL, ",|"))==NULL)
            {
				Log( MSG_ERROR, "Spawn area %i have invalid points",thisspawn->id );
				flag = false;
				break;
			}
			float x=(float)atof(tmp);
			if ((tmp = strtok(NULL, ",|"))==NULL)
            {
				Log( MSG_ERROR, "Spawn area %i have invalid points",thisspawn->id );
				flag = false;
				break;
			}
			float y=(float)atof(tmp);
			thisspawn->points[i].x = x;
			thisspawn->points[i].y = y;
		}
        if(flag)
        {
            thisspawn->thisnpc = GetNPCDataByID( thisspawn->montype );
            if(thisspawn->thisnpc==NULL)
            {
                Log( MSG_WARNING, "Invalid montype - Spawn %i will not be added", thisspawn->id );
                delete thisspawn;
                continue;
            }

            //LMA: check if out of memory.
            if (thisspawn->map>=MAX_MAP_DATA)
            {
               Log(MSG_WARNING,"Spawn, index overflow trapped %i>%i (increase MAX_MAP_DATA)",thisspawn->map,MAX_MAP_DATA);
               delete thisspawn;
               continue;
            }

    		MapList.Index[thisspawn->map]->MonsterSpawnList.push_back( thisspawn );
        }
	}
	DB->QFree( );
	Log( MSG_LOAD, "SpawnZones Data loaded" );
	return true;
}

bool CWorldServer::LoadNPCs( )
{
	Log( MSG_LOAD, "NPC spawn                   " );
	MYSQL_ROW row;
	MYSQL_RES *result = DB->QStore("SELECT type,map,dir,x,y,dialogid,eventid,tempdialogid FROM list_npcs");
	if(result==NULL) return false;
	while(row = mysql_fetch_row(result))
    {
		CNPC* thisnpc = new (nothrow) CNPC;
        if(thisnpc==NULL)
        {
            Log(MSG_ERROR, "Error allocing memory" );
            DB->QFree( );
            return false;
        }

		thisnpc->clientid = GetNewClientID();
		thisnpc->npctype = atoi(row[0]);
		thisnpc->posMap = atoi(row[1]);
		thisnpc->dir = (float)atof(row[2]);
		thisnpc->pos.x = (float)atof(row[3]);
		thisnpc->pos.y = (float)atof(row[4]);
		thisnpc->thisnpc = GetNPCDataByID( thisnpc->npctype );
		if( thisnpc->thisnpc == NULL)
		{
           Log(MSG_LOAD,"The NPC %i has not been found!, it won't be displayed",thisnpc->npctype);
            delete thisnpc;
            continue;
        }

        thisnpc->thisnpc->dialogid = atoi(row[5]); //This is global to NPC type (original dialog)
        //thisnpc->dialog=thisnpc->thisnpc->dialogid;
        //thisnpc->event=thisnpc->thisnpc->eventid; //LMA Event.        
        thisnpc->event=atoi(row[6]);                //LMA Event.
        thisnpc->dialog=atoi(row[7]);               //LMA tempdialog ID, used for events for example

        //LMA: check if out of memory.
        if (thisnpc->posMap>=MAX_MAP_DATA)
        {
           Log(MSG_WARNING,"NPC, index overflow trapped %i>%i (increase MAX_MAP_DATA)",thisnpc->posMap,MAX_MAP_DATA);
           delete thisnpc;
           continue;
        }

		MapList.Index[thisnpc->posMap]->AddNPC( thisnpc );
	}
	DB->QFree( );
	Log( MSG_LOAD, "NPC spawn Data loaded" );
	return true;
}

bool CWorldServer::LoadDropsData( )
{
	Log( MSG_LOAD, "Drops Data                  " );
    FILE* fh = NULL;
    fh = fopen("data/drops_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/drops_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CMDrops* newdrop = new (nothrow) CMDrops;
        if(newdrop==NULL)
        {
            fclose(fh);
            continue;
        }
        newdrop->id = GetUIntValue(",", &line);
        char* items = GetStrValue(",");
        char* prob = GetStrValue(",");
        newdrop->level_min = GetUIntValue(",");
        newdrop->level_max = GetUIntValue(",");
        newdrop->level_boss = GetUIntValue(",");
        UINT value = 0;
        bool First = true;

        // items
        while((value=GetUIntValue("|", First?items:NULL))!=0)
        {
            First = false;
            CDropInfo* DropInfo = new (nothrow) CDropInfo;
            if(DropInfo==NULL)
            {
                Log(MSG_WARNING, "\nError allocing memory [dropinfo]" );
                continue;
            }
            if(value<20000)
            {
                DropInfo->type = value/1000;
                DropInfo->item = value%1000;
            }
            else
            {
                DropInfo->type = value/1000000;
                DropInfo->item = value%1000000;
            }
            newdrop->Drops.push_back( DropInfo );
        }
        newdrop->probmax = 0;
        value = 0;
        // probability
        for(UINT j=0;j<newdrop->Drops.size();j++)
        {
            value = GetUIntValue("|",(j==0?prob:NULL));
            if(value==0)
            {
                newdrop->Drops.at(j)->prob = 1;
                if(newdrop->Drops.at(j)->type<10 || newdrop->Drops.at(j)->type==14)
                    newdrop->Drops.at(j)->prob *= Config.DROP_RATE;
                Log(MSG_WARNING, "Probability is not complete, dropid: %i - temporal probability will be 1 * rate", newdrop->id );
            }
            else
            {
                newdrop->Drops.at(j)->prob = value;
                if(newdrop->Drops.at(j)->type<10 || newdrop->Drops.at(j)->type==14)
                    newdrop->Drops.at(j)->prob *= Config.DROP_RATE;
            }
            newdrop->probmax += newdrop->Drops.at(j)->prob;
        }
        // sort time
        for(UINT j=0;j<newdrop->Drops.size();j++)
        {
            for(UINT k=j;k<newdrop->Drops.size();k++)
            {
                if(newdrop->Drops.at(j)>newdrop->Drops.at(k))
                {
                    CDropInfo* DropInfo = newdrop->Drops.at(j);
                    newdrop->Drops.at(j) = newdrop->Drops.at(k);
                    newdrop->Drops.at(k) = DropInfo;
                }
            }
        }
        MDropList.push_back( newdrop );
	}
	fclose(fh);
	Log( MSG_LOAD, "Drops Data loaded" );
	return true;
}

//hidden
bool CWorldServer::LoadPYDropsData( )
{
   	Log( MSG_LOAD, "PYDrops Data                " );
    MDropList.clear();
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT id,type,min_level,max_level,prob,mob,map,alt FROM item_drops");
    if(result==NULL)
    {
        DB->QFree( );
        return false;
    }
    while(row = mysql_fetch_row(result))
    {
        CMDrops* newdrop = new (nothrow) CMDrops;
        assert(newdrop);
        newdrop->itemnum = atoi(row[0]);
        newdrop->itemtype = atoi(row[1]);
        newdrop->level_min = atoi(row[2]);
        newdrop->level_max = atoi(row[3]);
        newdrop->prob = atoi(row[4]);
        newdrop->mob = atoi(row[5]);
        newdrop->map = atoi(row[6]);
        char *tmp;
        if((tmp = strtok( row[7] , "|"))==NULL)
            newdrop->alt[0]=0;
        else
            newdrop->alt[0]=atoi(tmp);
        for(unsigned int i=1;i<8; i++)
        {
            if((tmp = strtok( NULL , "|"))==NULL)
                newdrop->alt[i]=0;
            else
                newdrop->alt[i]=atoi(tmp);
        }
        MDropList.push_back( newdrop );
    }
    DB->QFree( );
    Log( MSG_LOAD, "PYDrops Data loaded" );
    return true;
}

//hidden

bool CWorldServer::LoadSkillBookDropsData( )
{
    Log( MSG_INFO, "Loading Skillbook data" );
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT id,itemtype,min,max,prob FROM list_skillbooks");
    if(result==NULL)
    {
        DB->QFree( );
        return false;
    }
    int c = 0;
    while(row = mysql_fetch_row(result))
    {

        c++;
        CMDrops* newdrop = new (nothrow) CMDrops;
        assert(newdrop);
        newdrop->itemnum = atoi(row[0]);
        newdrop->itemtype = atoi(row[1]);
        newdrop->level_min = atoi(row[2]);
        newdrop->level_max = atoi(row[3]);
        newdrop->prob = atoi(row[4]);
        SkillbookList.push_back( newdrop );
    }
    DB->QFree( );
    Log( MSG_INFO, "Skillbook Data loaded" );
    return true;
}


bool CWorldServer::LoadMonsters( )
{
	Log( MSG_LOAD, "Monsters Spawn              " );
	// Do our monster spawning
	#ifndef USEIFO
    for(UINT i=0;i<MapList.Map.size();i++)
    {
        CMap* thismap = MapList.Map.at(i);
        for(UINT j=0;j<thismap->MonsterSpawnList.size();j++)
        {
            CSpawnArea* thisspawn = thismap->MonsterSpawnList.at(j);
    		thisspawn->mapdrop = GetDropData( thisspawn->map );
            thisspawn->mobdrop = GetDropData( thisspawn->thisnpc->dropid );

            //LMA: Adding boss spawn handling
            if (thisspawn->bossid>0)
            {
               if (thisspawn->bossdropID>0)
               {
                  thisspawn->bossdrop=GetDropData( thisspawn->bossdropID);
               }
               else
               {
                   thisspawn->bossdrop=NULL;
               }

            }

            for(UINT k=0;k<thisspawn->max;k++)
            {
                fPoint position = RandInPoly( thisspawn->points, thisspawn->pcount );
                thismap->AddMonster(  thisspawn->montype, position, 0, thisspawn->mobdrop, thisspawn->mapdrop, thisspawn->id );
            }
        }
    }
   	Log( MSG_LOAD, "Monsters Spawn loaded" );
#else
       for (UINT i = 0; i < MapList.Map.size(); i++) {
      CMap *thismap = MapList.Map.at(i);
      for (UINT j = 0; j < thismap->MobGroupList.size(); j++) {
        bool GroupFull = false;
        CMobGroup* thisgroup = thismap->MobGroupList.at(j);
        // Load some basic mobs onto map
        for (UINT k = 0; k < thisgroup->limit; k++) {
          CMob* thismob = thisgroup->basicMobs.at(thisgroup->curBasic);
          thisgroup->curBasic++;
          if (thisgroup->curBasic >= thisgroup->basicMobs.size()) thisgroup->curBasic = 0;
          for (UINT l = 0; l < thismob->amount; l++) {
            fPoint position = RandInCircle( thisgroup->point, thisgroup->range );
            thismap->AddMonster( thismob->mobId, position, 0, thismob->mobdrop, thismob->mapdrop, thisgroup->id );
            if (thisgroup->active > thisgroup->limit) {
              GroupFull = true;
              break;
            }
          }
          if (GroupFull) break;
        }
      }
    }

#endif
	return true;
}

bool CWorldServer::LoadUpgrade( )
{
	Log( MSG_LOAD, "Refine Data                 " );
    FILE* fh = NULL;
    fh = fopen("data/refine_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/refine_data.csv" );
        return false;
    }
    char line[50];
    fgets( line, 50, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 50 );
        fgets( line, 50, fh );
        upgrade[GetUIntValue(",",&line)] = GetUIntValue(",");
    }
    fclose(fh);
   	Log( MSG_LOAD, "Refine Data loaded" );
	return true;
}

bool CWorldServer::CleanConnectedList( )
{
    Log( MSG_LOAD, "Cleaning Connected Clients         " );
    DB->QExecute("UPDATE accounts set online=false");
    Log( MSG_LOAD, "Cleaning Connected loaded" );
    return true;
}

bool CWorldServer::LoadEquip( )
{
    Log( MSG_LOAD, "Equip Data                  " );
    FILE* fh = NULL;
    fh = fopen("data/equip_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/equip_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CEquip* newequip = new (nothrow) CEquip;
        if(newequip==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: equip" );
            fclose(fh);
            return false;
        }
        newequip->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (newequip->id>=MAX_EQUIP_DATA)
        {
           Log(MSG_WARNING,"equip_data.csv, index overflow trapped %i>%i (increase MAX_EQUIP_DATA)",newequip->id,MAX_EQUIP_DATA);
           delete newequip;
           continue;
        }

        newequip->equiptype = GetUIntValue(",");
        newequip->type = GetUIntValue(",");
        newequip->price = GetUIntValue(",");
        newequip->pricerate = GetUIntValue(",");
        newequip->weight = GetUIntValue(",");
        newequip->quality = GetUIntValue(",");
        newequip->level = GetUIntValue(",");
        newequip->material = GetUIntValue(",");
        char* occupation = GetStrValue(",");
        char* condition1 = GetStrValue(",");
        char* condition2 = GetStrValue(",");
        char* stat1 = GetStrValue(",");
        char* stat2 = GetStrValue(",");
        newequip->defense = GetUIntValue(",");
        newequip->magicresistence = GetUIntValue(",");
        newequip->attackdistance = GetUIntValue(",");
        if(newequip->equiptype==SHOE)
        {
            newequip->movespeed = newequip->attackdistance;
        }
        else
        {
            newequip->movespeed = 0;
        }
        newequip->attackpower = GetUIntValue(",");
        newequip->attackspeed =GetUIntValue(",");
        newequip->itemgrade = GetUIntValue(",");
        for(int i=0;i<3;i++)
            newequip->occupation[i] = GetUIntValue("|", i==0?occupation:NULL);
        for(int i=0;i<3;i++)
            newequip->condition1[i] = GetUIntValue("|", i==0?condition1:NULL);
        for(int i=0;i<3;i++)
            newequip->condition2[i] = GetUIntValue("|", i==0?condition2:NULL);
        for(int i=0;i<2;i++)
            newequip->stat1[i] = GetUIntValue("|", i==0?stat1:NULL);
        for(int i=0;i<2;i++)
            newequip->stat2[i] = GetUIntValue("|", i==0?stat2:NULL);
        EquipList[newequip->equiptype].Data.push_back( newequip );
        EquipList[newequip->equiptype].Index[newequip->id] = newequip; // Index to read more quickly the data
    }
    fclose(fh);
    Log( MSG_LOAD, "Equip Data loaded" );
    return true;
}

bool CWorldServer::LoadJemItem( )
{
    Log( MSG_LOAD, "Jem Data                    " );
    FILE* fh = NULL;
    fh = fopen("data/jemitem_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/jemitem_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CJemData* thisjem = new (nothrow) CJemData;
        if(thisjem==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: jemitem" );
            fclose(fh);
            continue;
        }
        thisjem->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (thisjem->id>=MAX_JEM_DATA)
        {
           Log(MSG_WARNING,"jemitem_data.csv, index overflow trapped %i>%i (increase MAX_JEM_DATA)",thisjem->id,MAX_JEM_DATA);
           delete thisjem;
           continue;
        }

        thisjem->type = GetUIntValue(",");
        thisjem->price = GetUIntValue(",");
        thisjem->pricerate = GetUIntValue(",");
        thisjem->weight = GetUIntValue(",");
        thisjem->quality = GetUIntValue(",");
        thisjem->material = GetUIntValue(",");
        char* stat1 = GetStrValue(",");
        char* stat2 = GetStrValue(",");
        for(int i=0;i<2;i++)
            thisjem->stat1[i] = GetUIntValue("|",i==0?stat1:NULL);
        for(int i=0;i<2;i++)
            thisjem->stat2[i] = GetUIntValue("|",i==0?stat2:NULL);
        JemList.Data.push_back( thisjem );
        JemList.Index[thisjem->id] = thisjem;
    }
    fclose(fh);
    Log( MSG_LOAD, "Jem Data loaded" );
    return true;
}

bool CWorldServer::LoadNaturalItem( )
{
    Log( MSG_LOAD, "Natural Data                " );
    FILE* fh = NULL;
    fh = fopen("data/natural_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/natural_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CNaturalData* thisnatural = new (nothrow) CNaturalData;
        if(thisnatural==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: natural" );
            fclose(fh);
            return false;
        }
        thisnatural->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (thisnatural->id>=MAX_NATURAL_DATA)
        {
           Log(MSG_WARNING,"natural_data.csv, index overflow trapped %i>%i (increase MAX_NATURAL_DATA)",thisnatural->id,MAX_NATURAL_DATA);
           delete thisnatural;
           continue;
        }

        thisnatural->type = GetUIntValue(",");
        thisnatural->price = GetUIntValue(",");
        thisnatural->pricerate = GetUIntValue(",");
        thisnatural->weight = GetUIntValue(",");
        thisnatural->quality = GetUIntValue(",");
        thisnatural->pricevalue = GetUIntValue(",");
        NaturalList.Data.push_back( thisnatural );
        NaturalList.Index[thisnatural->id] = thisnatural;
    }
    fclose(fh);
    Log( MSG_LOAD, "Natural Data loaded" );
    return true;
}

bool CWorldServer::LoadPatItem( )
{
    Log( MSG_LOAD, "PAT Data                    " );
    FILE* fh = NULL;
    fh = fopen("data/pat_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/pat_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CPatData* newpat = new (nothrow) CPatData;
        if(newpat==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: pat" );
            fclose(fh);
            return false;
        }
        newpat->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (newpat->id>=MAX_PAT_DATA)
        {
           Log(MSG_WARNING,"natural_data.csv, index overflow trapped %i>%i (increase MAX_PAT_DATA)",newpat->id,MAX_PAT_DATA);
           delete newpat;
           continue;
        }

        newpat->type = GetUIntValue(",");
        newpat->price = GetUIntValue(",");
        newpat->pricerate = GetUIntValue(",");
        newpat->weight = GetUIntValue(",");
        newpat->quality = GetUIntValue(",");
        newpat->material = GetUIntValue(",");
        newpat->partversion = GetUIntValue(",");
        newpat->maxfuel = GetUIntValue(",");
        newpat->fuelcons = GetUIntValue(",");
        newpat->speed = GetUIntValue(",");
        newpat->attackdistance = GetUIntValue(",");
        newpat->attackpower = GetUIntValue(",");
        newpat->attackspeed = GetUIntValue(",");
        PatList.Data.push_back( newpat );
        PatList.Index[newpat->id] = newpat;
    }
    fclose(fh);
    Log( MSG_LOAD, "PAT Data loaded" );
    return true;
}

bool CWorldServer::LoadProductItem( )
{
    Log( MSG_LOAD, "Product Data                " );
    FILE* fh = NULL;
    fh = fopen("data/product_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/product_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name

    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CProductData* newproduct = new (nothrow) CProductData;
        if(newproduct==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: product" );
            fclose(fh);
            return false;
        }
        newproduct->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (newproduct->id>=MAX_PRODUCT_DATA)
        {
           Log(MSG_WARNING,"Product_data.csv, index overflow trapped %i>%i (increase MAX_PRODUCT_DATA)",newproduct->id,MAX_PRODUCT_DATA);
           delete newproduct;
           continue;
        }

        char* items = GetStrValue(",");
        char* amount = GetStrValue(",");
        for(int i=0;i<50;i++)
            newproduct->item[i] = GetUIntValue("|",i==0?items:NULL);
        for(int i=0;i<50;i++)
            newproduct->amount[i] = GetUIntValue("|",i==0?amount:NULL);
        ProductList.Data.push_back( newproduct );
        ProductList.Index[newproduct->id] = newproduct;
    }
    fclose(fh);
    Log( MSG_LOAD, "Product Data loaded" );
    return true;
}

bool CWorldServer::LoadSellData( )
{
    Log( MSG_LOAD, "Sell Data                   " );
    FILE* fh = NULL;
    fh = fopen("data/sell_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/sell_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CCSellData* newsell = new (nothrow) CCSellData;
        if(newsell==NULL)
        {
            Log(MSG_WARNING, "\nError Allocing memory: sell" );
            fclose(fh);
            return false;
        }
        newsell->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (newsell->id>=MAX_SELL_DATA)
        {
           Log(MSG_WARNING,"sell_data.csv, index overflow trapped %i>%i (increase MAX_SELL_DATA)",newsell->id,MAX_SELL_DATA);
           delete newsell;
           continue;
        }

        char *items = GetStrValue(",");
        for(int i=0;i<48;i++)
            newsell->item[i] = GetUIntValue("|",i==0?items:NULL);
        SellList.Data.push_back( newsell );
        SellList.Index[newsell->id] = newsell;
    }
    fclose(fh);
    Log( MSG_LOAD, "Sell Data loaded" );
    return true;
}

bool CWorldServer::LoadConsItem( )
{
/*    Log( MSG_LOAD, "Consumable Data             " );
    FILE* fh = NULL;
    fh = fopen("data/useitem_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/useitem_data.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CUseData* newuse = new (nothrow) CUseData;
        if(newuse==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: use" );
            fclose(fh);
            return false;
        }
        newuse->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (newuse->id>=MAX_USE_DATA)
        {
           Log(MSG_WARNING,"useitem_data.csv, index overflow trapped %i>%i (increase MAX_USE_DATA)",newuse->id,MAX_USE_DATA);
           delete newuse;
           continue;
        }

        newuse->restriction = GetUIntValue(",");
        newuse->type = GetUIntValue(",");
        newuse->price = GetUIntValue(",");
        newuse->pricerate = GetUIntValue(",");
        newuse->weight = GetUIntValue(",");
        newuse->quality = GetUIntValue(",");
        newuse->material = GetUIntValue(","); //core
        newuse->pricevalue = GetUIntValue(",");
        char* usecondition = GetStrValue(",");
        char* useeffect = GetStrValue(",");
        for(int i=0;i<2;i++)
            newuse->usecondition[i] = GetUIntValue("|",i==0?usecondition:NULL);
        for(int i=0;i<2;i++)
            newuse->useeffect[i] = GetUIntValue("|",i==0?useeffect:NULL);
        UseList.Data.push_back( newuse );
        UseList.Index[newuse->id] = newuse;
    }
    fclose(fh);
*/

    Log( MSG_LOAD, "Consumable Data - STB   " );
    for(unsigned int i=0;i<STB_ITEM[9].rowcount;i++)
    {
        CUseData* newuse = new (nothrow) CUseData;
        if(newuse==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: use" );
            return false;
        }
        newuse->id = i;
        newuse->restriction = STB_ITEM[9].rows[i][3];
        newuse->type = STB_ITEM[9].rows[i][4];
        newuse->price = STB_ITEM[9].rows[i][5];
        newuse->pricerate = STB_ITEM[9].rows[i][6];
        newuse->weight = STB_ITEM[9].rows[i][7];
        newuse->quality = STB_ITEM[9].rows[i][8];
        newuse->pricevalue = STB_ITEM[9].rows[i][16];
        newuse->usecondition[0]= STB_ITEM[9].rows[i][17];
        newuse->usecondition[1]= STB_ITEM[9].rows[i][18];
        newuse->useeffect[0]= STB_ITEM[9].rows[i][19];
        newuse->useeffect[1]= STB_ITEM[9].rows[i][20];
        UseList.Data.push_back( newuse );
        UseList.Index[newuse->id] = newuse;
    }    
    Log( MSG_LOAD, "Consumable Data Loaded" );
    return true;
}

bool CWorldServer::LoadZoneData( )
{
    Log( MSG_LOAD, "Zone Data                   " );
    FILE* fh = fopen( "data/zone_data.csv", "r" );
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/zone_data.csv" );
        return false;
    }

    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        CMap* newzone = new (nothrow) CMap( );
        if(newzone==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: CMap" );
            fclose(fh);
            return false;
        }
        newzone->id = GetUIntValue(",", &line);

        //LMA: check if out of memory.
        if (newzone->id>=MAX_MAP_DATA)
        {
           Log(MSG_WARNING,"zone_data.csv, index overflow trapped %i>%i (increase MAX_MAP_DATA)",newzone->id,MAX_MAP_DATA);
           delete newzone;
           continue;
        }

        newzone->dayperiod = GetUIntValue(",");
        newzone->morningtime = GetUIntValue(",");
        newzone->daytime = GetUIntValue(",");
        newzone->eveningtime = GetUIntValue(",");
        newzone->nighttime = GetUIntValue(",");
        newzone->allowpvp = GetUIntValue(",");
        newzone->allowpat = GetUIntValue(",")==0?true:false;
        newzone->ghost = GetUIntValue(",");

        //LMA begin
        //CF Mode
        //20070621-211100
        //map is cf (for jelly bean)
       newzone->is_cf=GetUIntValue(",");
       newzone->id_temp_mon = 0;
       newzone->id_def_mon = 0;
       newzone->min_lvl = 0;
       newzone->mon_lvl = 0;
       newzone->mon_exp = 0;
       newzone->percent=0;

       //LMA: Union Wars and union slaughter:
       newzone->utime_begin=0;
       newzone->utime_end=0;
       newzone->is_union_fired=false;
       newzone->us_loop=false;
        newzone->us_duration=0;
        newzone->us_delay_loop=0;
        newzone->is_uw_fired=false;
        newzone->sunsetkilled=false;
        newzone->sunrisekilled=false;
        newzone->sunsetspawned=false;
        newzone->duskkilled=false;
        newzone->uw_end=0;
        newzone->uw_begin=0;
        newzone->uw_loop=false;
        newzone->uw_duration=0;
        newzone->uw_delay_loop=0;
        newzone->announce_done=false;
        newzone->npc_id=0;
        newzone->defenders=0;
        newzone->attackers=0;

        if (newzone->id==8)
        {
            newzone->us_loop=GServer->Config.unionslaughterloop;
            newzone->us_duration=GServer->Config.unionduration;
            newzone->us_delay_loop=GServer->Config.unionslaughterdelay_loop;
        }

        if(newzone->id==9)
        {
            newzone->uw_loop=GServer->Config.unionwarloop;
            newzone->uw_duration=GServer->Config.unionwarduration;
            newzone->uw_delay_loop=GServer->Config.unionwardelay_loop;
        }

       //mode 1: one monster temporarily, then the "real" one :)
        if (newzone->is_cf==1)
        {
           Log( MSG_LOAD, "Map %u is CF mode 1 !",newzone->id);
           newzone->min_lvl = GetUIntValue(",");
           newzone->id_temp_mon = GetUIntValue(",");
           newzone->id_def_mon = GetUIntValue(",");
           newzone->mon_lvl = GetUIntValue(",");
           newzone->mon_exp = GetUIntValue(",");
           newzone->percent = GetUIntValue(",");
        }
        else
        {
            newzone->is_cf=0;
        }
        //LMA end

        newzone->MapTime = 0;
        newzone->LastUpdate = clock( );
        newzone->CurrentTime = 0;
        newzone->MonsterSpawnList.clear();
        #ifdef USEIFO
        newzone->MobGroupList.clear();
        #endif
        MapList.Map.push_back(newzone);
        MapList.Index[newzone->id] = newzone;
    }
    fclose(fh);
    Log( MSG_LOAD, "Zone Data Loaded" );
    return true;
}

//LMA: Grid Maps
bool CWorldServer::LoadGrids( )
{
    Log( MSG_LOAD, "Grid Data                   " );
    FILE* fh = fopen( "data/map_grid.csv", "r" );
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/map_grid.csv" );
        return false;
    }

    //LMA maps
    int k=0;
    int j=0;
    for(k=0;k<NB_MAPS;k++)
    {
        allmaps[k].grid_id=-1;
        allmaps[j].always_on=false;
    }
    k=0;
    //LMA END
    int lx=0;
    int ly=0;
    int rx=0;
    int ry=0;

    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );

        j = GetUIntValue(",", &line);
        if (j==0)
           continue;

        lx = GetUIntValue(",");
        ly = GetUIntValue(",");
        rx = GetUIntValue(",");
        ry = GetUIntValue(",");

        //Map info
        allmaps[j].grid_id=k;         //Id of map in gridmaps
        allmaps[j].always_on=GetUIntValue(",")==0?false:true;

        //Grid now
        gridmaps[k].always_on=allmaps[j].always_on;
        gridmaps[k].length=rx-lx;
        gridmaps[k].width=ly-ry;
        gridmaps[k].org_x=lx;
        gridmaps[k].org_y=ry;

        //getting nb of columns...
        allmaps[j].nb_col=(int) ceil(gridmaps[k].length/MINVISUALRANGE);
        allmaps[j].nb_row=(int) ceil(gridmaps[k].width/MINVISUALRANGE);

        //Log(MSG_LOAD,"map %i, row=%i, col=%i",j,allmaps[j].nb_row,allmaps[j].nb_col);

        if (gridmaps[k].width==0)
           gridmaps[k].width=1;

        if (gridmaps[k].length==0)
           gridmaps[k].length=1;

         //resetting values...
         for (j=0;j<NB_CELL_MAX;j++)
         {
             gridmaps[k].coords[j]=0;
         }

       k++;
    }
    fclose(fh);


    Log( MSG_LOAD, "Grid reseted.");
    return true;
}

bool CWorldServer::LoadItemStats( )
{
/*    Log( MSG_LOAD, "Item Stats                  " );
    FILE* fh = NULL;
    fh = fopen("data/stat.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/stat.csv" );
        return false;
    }
    char line[500];
    fgets( line, 500, fh );// this is the column name
    while(!feof(fh))
    {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        UINT id = GetUIntValue(",", &line );
        if(id>499) continue;
        StatsList[id].stat[0] = GetUIntValue(",");
        StatsList[id].value[0] = GetUIntValue(",");
        StatsList[id].stat[1] = GetUIntValue(",");
        StatsList[id].value[1] = GetUIntValue(",");
    }
    fclose(fh);
*/
{
    Log( MSG_LOAD, "Item Stats - STB   " );
    for(unsigned int i=0;i<STB_ITEM[10].rowcount;i++)
    {
        StatsList[i].stat[0] = STB_ITEM[10].rows[i][16];
        StatsList[i].value[0] = STB_ITEM[10].rows[i][17];
        StatsList[i].stat[1] = STB_ITEM[10].rows[i][18];
        StatsList[i].value[1] = STB_ITEM[10].rows[i][19];
    }
    return true;
}
    Log( MSG_LOAD, "Item Stats Loaded" );
    return true;
}


//PY stat lookup table
bool CWorldServer::LoadStatLookup( )
{
    Log( MSG_INFO, "Loading Stats Lookup Table" );
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT id, stat_number FROM list_extra_stats");
    if(result==NULL)
    {
        DB->QFree( );
        return false;
    }
    UINT counter = 1;

    while( row = mysql_fetch_row(result) )
    {
        StatLookup[counter].id = atoi(row[0]);
        StatLookup[counter].statnumber = atoi(row[1]);
        counter++;
    }

    DB->QFree( );
    Log( MSG_INFO, "Stats Lookup Data Loaded" );
    return true;
}
//PY end


// geo edit for disassemble // 22 oct 07
bool CWorldServer::LoadBreakList()
{
    Log( MSG_LOAD, "Disassembly List            " );
    FILE* fh = NULL;
    fh = fopen("data/break_data.csv", "r");
    if(fh==NULL)
    {
        Log(MSG_ERROR, "\nError loading file data/break_data.csv" );
        return false;
    }
    char line[500];
    char* temp;
    fgets( line, 500, fh );// this is the column name
    int i=0;
    while(!feof(fh))
    {
      if(i<3000)
// make sure above line is set higher than actual amount
// In WorldServer.h change this one CBreakList BreakList[3000] to match above
      {
        memset( &line, '\0', 500 );
        fgets( line, 500, fh );
        UINT itemid = GetUIntValue(",",&line);
        BreakList[i].itemtype = int(itemid / 1000);
        BreakList[i].itemnum = itemid % 1000;
        for(int j=0;j<15;j++)
        {
            BreakList[i].product[j] = GetUIntValue(",");
            BreakList[i].amount[j] = GetUIntValue(",");
            BreakList[i].prob[j] = GetUIntValue(",");
        }
        BreakList[i].numToGive = GetUIntValue(",");
        BreakList[i].total = GetUIntValue(",");
        i++;
      }
    }
    BreakListSize = i-1;
    fclose(fh);
    Log( MSG_LOAD, "Disassembly List Loaded" );
    return true;
}


bool CWorldServer::LoadCustomTeleGate()
{
    Log( MSG_LOAD, "Loading Custom Telegate data" );
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT id,sourcex,sourcey,sourcemap,destx,desty,destmap,radius,active FROM list_customgates");
    CustomGateList.clear();
    if(result==NULL)
    {
        DB->QFree( );
        return false;
    }
    while( row = mysql_fetch_row(result) )
    {
        CCustomGate* thisgate = new (nothrow) CCustomGate;
        if(thisgate == NULL)
        {
            Log(MSG_ERROR, "Error allocing memory       " );
            DB->QFree( );
            return false;
        }
        thisgate->id = atoi(row[0]);
        thisgate->source.x = (float)atof(row[1]);
        thisgate->source.y = (float)atof(row[2]);
        thisgate->sourcemap = atoi(row[3]);
        thisgate->dest.x = (float)atof(row[4]);
        thisgate->dest.y = (float)atof(row[5]);
        thisgate->destmap = atoi(row[6]);
        thisgate->radius = atoi(row[7]);
        thisgate->active = atoi(row[8]);
        CustomGateList.push_back(thisgate);
    }
    DB->QFree( );
    Log( MSG_LOAD, "Custom Telegate Data Loaded" );
    return true;
}


bool CWorldServer::LoadCustomEvents( )
{
    Log( MSG_LOAD, "Custom Events data          " );
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT id,eventtype,npcname,x,y,map,radius,active,pc1,pc2,pc3,pc4,pc5,pc6,pc7,pc8,pc9,pc10,pt1,pt2,pt3,pt4,pt5,pt6,pt7,pt8,pt9,pt10,pi1,pi2,pi3,pi4,pi5,pi6,pi7,pi8,pi9,pi10,pn1,pn2,pn3,pn4,pn5,pn6,pn7,pn8,pn9,pn10,script1,script2,script3,script4,itemname,collecttype,collectnum,level FROM list_customevents");
    CustomEventList.clear();
    if(result==NULL)
    {
        DB->QFree( );
        return false;
    }
    int i;
    while( row = mysql_fetch_row(result) )
    {
        CCustomEvent* thisevent = new (nothrow) CCustomEvent;
        if(thisevent == NULL)
        {
            Log(MSG_ERROR, "Error allocing memory" );
            DB->QFree( );
            return false;
        }
        thisevent->id = atoi(row[0]);
        thisevent->eventtype = atoi(row[1]);
        strcpy(thisevent->npcname,row[2]);
        thisevent->location.x = (float)atof(row[3]);
        thisevent->location.y = (float)atof(row[4]);
        thisevent->map = atoi(row[5]);
        thisevent->radius = atoi(row[6]);
        thisevent->active = atoi(row[7]);
        for(i=1;i<11;i++)
        {
            thisevent->prizecost[i] = atoi(row[7+i]);
        }
        for(i=1;i<11;i++)
        {
            thisevent->prizetype[i] = atoi(row[17+i]);
        }
        for(i=1;i<11;i++)
        {
            thisevent->prizeid[i] = atoi(row[27+i]);
        }
        for(i=1;i<11;i++)
        {
            strcpy(thisevent->prizename[i].prizename ,row[37+i]);
        }
        strcpy(thisevent->script1,row[48]);
        strcpy(thisevent->script2,row[49]);
        strcpy(thisevent->script3,row[50]);
        strcpy(thisevent->script4,row[51]);
        strcpy(thisevent->itemname,row[52]);
        thisevent->collecttype = atoi(row[53]);
        thisevent->collectid = atoi(row[54]);
        thisevent->level = atoi(row[55]);
        CustomEventList.push_back(thisevent);
    }
    DB->QFree( );
    Log( MSG_LOAD, "Custom Events data loaded" );
    return true;
}
