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

// from Paul_T
bool CWorldServer::SendPM( CPlayer* thisclient, char* Format, ... )
{
    char buf[512];
    va_list ap;
    va_start( ap, Format );
    vsprintf( buf, Format, ap );
    BEGINPACKET( pak, 0x0784 );
    ADDSTRING( pak, "Server" );
    ADDBYTE( pak, 0 );
    ADDSTRING( pak, buf );
    ADDBYTE( pak, 0 );
    thisclient->client->SendPacket(&pak);
    va_end( ap );
    return true;
}

// from Paul_T
bool CWorldServer::SendGlobalMSG( CPlayer* thisclient, char msg[200] )
{
    BEGINPACKET( pak, 0x0784 );
    ADDSTRING( pak, thisclient->CharInfo->charname );
    ADDBYTE( pak, 0 );
    ADDSTRING( pak, msg );
    ADDBYTE( pak, 0 );
    SendToAll(&pak);
    return true;
}

// NPC Announce to the server
bool CWorldServer::NPCAnnounce( char* msg, char* npc, int mapid)
{
    //LMA: We only announce in the NPC's map
    //Log(MSG_INFO,"%s announces: %s",npc,msg);
    BEGINPACKET( pak, 0x702 );
    ADDSTRING( pak, npc );
	ADDSTRING( pak, "> " );
	ADDSTRING( pak, msg);
	ADDBYTE( pak, 0x00);

	if(mapid!=0)
	{
	    SendToMap  ( &pak, mapid );
	}
	else
	{
	    SendToAll( &pak );
	}


	return true;
}

// NPC Whisper to a character
bool CWorldServer::NPCWhisper( CPlayer* thisclient, CMonster* thismon, char msg[200], char npc[50] )
{
    BEGINPACKET( pak, 0x0784 );
    ADDSTRING( pak, npc );
    ADDBYTE( pak, 0 );
    ADDSTRING( pak, msg );
    ADDBYTE( pak, 0 );
    thisclient->client->SendPacket(&pak);
    return true;
}

// NPC Shout to the current map
bool CWorldServer::NPCShout( CMonster* thismon, char* msg, char* npc,int mapid)
{
    BEGINPACKET(pak, 0x0785);
	ADDSTRING  ( pak, npc );
	ADDBYTE    ( pak, 0 );
	ADDSTRING  ( pak, msg );
	ADDBYTE    ( pak, 0 );

	if(mapid!=0)
        SendToMap  ( &pak, mapid );
    else
        SendToMap  ( &pak, thismon->Position->Map );


	return true;
}


bool CWorldServer::NPCShout2( CMonster* thismon, char* msg, char* npc )
{
    BEGINPACKET(pak, 0x0785);
	ADDSTRING  ( pak, npc );
	ADDBYTE    ( pak, 0 );
	ADDSTRING  ( pak, msg );
	ADDBYTE    ( pak, 0 );
	SendToMap  ( &pak, thismon->Position->Map );
	return true;
}



// Send a PM from a specific NPC using the blue text of the shout system. Used in custom quests
bool CWorldServer::NPCMessage( CPlayer* thisclient, char msg[200], char npc[50])
{
    if (npc == "")
        strcpy(npc, "Event NPC");
    BEGINPACKET(pak, 0x0785);
    ADDSTRING  ( pak, npc );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, msg );
    ADDBYTE    ( pak, 0 );
    thisclient->client->SendPacket(&pak);
    return true;
}

// Search Quest by ID
CQuest* CWorldServer::GetQuestByID( unsigned long int id )
{
	for(unsigned j=0; j<QuestList.size(); j++)
    {
		CQuest* thisquest = (CQuest*)QuestList.at( j );
		if ( thisquest->id == id )
            return thisquest;
	}
	return 0;
}

// Search Quest by QuestID
CQuest* CWorldServer::GetQuestByQuestID( unsigned long int questid )
{
	for(unsigned j=0; j<QuestList.size(); j++)
    {
		CQuest* thisquest = (CQuest*)QuestList.at( j );
		if ( thisquest->questid == questid )
            return thisquest;
	}
	return 0;
}

// Search Quest by FinalID
CQuest* CWorldServer::GetQuestByFinalID(  unsigned long int questid )
{
	for(unsigned j=0; j<QuestList.size(); j++)
    {
		CQuest* thisquest = (CQuest*)QuestList.at( j );
		if ( thisquest->finalid == questid )
            return thisquest;
	}
	return 0;
}

bool CWorldServer::DoSkillScript( CCharacter* character, CSkills* thisskill )
{
    if(thisskill==0)
        return false;
    if(thisskill->script==0)
        return false;
    switch(thisskill->script)
    {
        case 1:
        {
            if(thisskill->svalue1==0)
                return false;

            //fPoint position = RandInCircle( character->Position->current, 5 );
            fPoint position = RandInCircle( character->Position->current, 0 );

            CMap* map = MapList.Index[character->Position->Map];
            CMonster* thismonster=map->AddMonster( thisskill->svalue1, position, character->clientid );
            if (thismonster!=NULL)
            {
               thismonster->skillid=thisskill->id;
               if (!thismonster->IsBonfire())
                  break;

               //LMA: Special for bonfire (and others) cases.
               switch (thisskill->value1[0])
               {
                      case 3:
                           {
                             thismonster->bonushp=1;
                             thismonster->bonusmp=1;
                           }
                           break;
                      case 2:
                           {
                             thismonster->bonushp=1;
                           }
                           break;
                      case 1:
                           {
                             thismonster->bonusmp=1;
                           }
                           break;
                      default:
                           {
                             //NA
                           }
                           break;
               }

                if (thismonster->bonushp==0&&thismonster->bonusmp==0)
                   break;
                thismonster->minvalue=thisskill->value1[1];
                thismonster->maxvalue=thisskill->value1[2];
                thismonster->range=thisskill->range;
            }

        }
        break;
    }
    return true;
}

// Build Drop (LMA: shouldn't be used anymore).
CDrop* CWorldServer::GetDrop( CMonster* thismon )
{
    CDrop* newdrop = new (nothrow) CDrop;
    if(newdrop==NULL)
    {
        Log(MSG_WARNING, "Error allocing memory [getdrop]" );
        return NULL;
    }
    newdrop->clientid = GetNewClientID( );
    newdrop->posMap = thismon->Position->Map;
    newdrop->pos = RandInCircle( thismon->Position->current, 3 );
    newdrop->droptime = time(NULL);
    newdrop->owner = thismon->MonsterDrop->firsthit;
    newdrop->thisparty = thismon->thisparty;
    ClearItem(newdrop->item);
    int randv = RandNumber( 1, 100);
    if(thismon->MonsterDrop->mapdrop->level_max<thismon->MonsterDrop->firstlevel) randv = 100;
    if(randv<=30)//30% zuly [zulies will count as mapdrop]
    {
        if(thismon->MonsterDrop->mapdrop->level_max>=thismon->MonsterDrop->firstlevel)
        {
            newdrop->type = 1; //Drop Zuly
            newdrop->amount = thismon->thisnpc->level*5*Config.ZULY_RATE + RandNumber( 1, 10 );
            return  newdrop;
        }
        delete newdrop;
        return NULL;
    }
    CMDrops* thisdrops;
    newdrop->type = 2; //drop item drop
    switch( Config.DROP_TYPE )
    {
        case 0://only map
            thisdrops = thismon->MonsterDrop->mobdrop;
            if(thisdrops->level_max<thismon->MonsterDrop->firstlevel)
            {
                delete newdrop;
                return NULL;
            }
        break;
        case 1://mob only
            thisdrops = thismon->MonsterDrop->mapdrop;
            if(thismon->thisnpc->level-thismon->MonsterDrop->firstlevel<-14)
            {
                delete newdrop;
                return NULL;
            }
        break;
        default://both
            randv = RandNumber(1,100);
            if(thismon->MonsterDrop->mapdrop!=NULL)
                if(thismon->MonsterDrop->mapdrop->level_max<thismon->MonsterDrop->firstlevel)
                    randv = 100;
            if(randv>60)//select wich drop will use (map or mob) //40 - 60%
            {
                thisdrops = thismon->MonsterDrop->mobdrop;
                if((int)(thismon->thisnpc->level-thismon->MonsterDrop->firstlevel) < -14)
                {
                    delete newdrop;
                    return NULL;
                }
            }
            else
            {
                thisdrops = thismon->MonsterDrop->mapdrop;
                if(thisdrops->level_max<thismon->MonsterDrop->firstlevel)
                {
                    delete newdrop;
                    return NULL;
                }
            }
        break;
    }
    if(thisdrops==NULL)
    {
        thisdrops = thismon->MonsterDrop->mobdrop;
        if(thisdrops==NULL)
        {
            thisdrops = thismon->MonsterDrop->mapdrop;
            if(thisdrops==NULL)
            {
                newdrop->type = 1; //Drop Zuly
                newdrop->amount = thismon->thisnpc->level*5*Config.ZULY_RATE - RandNumber( 1, 20 );
                return  newdrop;
            }
        }
    }
    randv = 0;
    randv = RandNumber( 1, thisdrops->probmax );
    DWORD prob = 1;
    for(UINT i=0;i<thisdrops->Drops.size();i++)
    {
        CDropInfo* dropinfo = thisdrops->Drops.at( i );
        prob += dropinfo->prob;
        if(randv<=prob)
        {
            newdrop->item.itemtype = dropinfo->type;
            newdrop->item.itemnum = dropinfo->item;
            break;
        }
    }
    if(newdrop->item.itemtype==0)
    {
        Log(MSG_WARNING, "Drop Probability Highter: %i", randv );
        delete newdrop;
        return NULL;
    }
    if(newdrop->item.itemtype>1 && newdrop->item.itemtype<10 && newdrop->item.itemtype!=JEWEL)
    {
        // Refine
        randv = RandNumber( 1, 100 );
        if( randv < 10 )        //10%
            newdrop->item.refine = 48;
        else if( randv < 25 )   //15%
            newdrop->item.refine = 32;
        else if( randv < 50 )   // 25%
            newdrop->item.refine = 16;
        else //50%
            newdrop->item.refine = 0;
        newdrop->item.lifespan = RandNumber( 30, 100 );
        newdrop->item.durability = RandNumber( 35, 70 );
        if( newdrop->item.itemtype==WEAPON || newdrop->item.itemtype==SUBWEAPON )
        {
            //socketed
            randv = RandNumber( 1, 100 );
            if( randv < 30 ) newdrop->item.socketed = true; // 30%
            else newdrop->item.socketed = false;            // 70%
        }
        else
        {
            newdrop->item.socketed = false;
        }
        randv = RandNumber( 1, 100 );
        if( randv < 30 )        // 30%
            newdrop->item.stats = rand()%300;
        newdrop->item.appraised = newdrop->item.stats==0?true:false;
    }
    else
    {
         newdrop->item.lifespan = 100;
         newdrop->item.durability = 40;
         newdrop->item.socketed = false;
         newdrop->item.stats = 0;
    }
    newdrop->item.count = 1;
    if( newdrop->item.itemtype == 10 || newdrop->item.itemtype == 12 )
    {
        newdrop->item.count = RandNumber( 1, 3 );
    }
    newdrop->item.gem = 0;
    return newdrop;
}

//hidden
// Build Drop the PY way
CDrop* CWorldServer::GetPYDrop( CMonster* thismon, UINT droptype )
{   //if droptype = 1 then it is a normal drop. if it is 2 then it is a potential side drop.
    //Log(MSG_INFO,"GetPYDrop, monster %i, droptype %i",thismon->montype,droptype);

    if(droptype == 2) // monster is still alive
    {
        // kicks it straight back if the monster is not dead
        if(thismon->thisnpc->side != 0) //perhaps we get a side drop??
        {
            if(GServer->RandNumber(0,100) < thismon->thisnpc->sidechance)
            {
                droptype = thismon->thisnpc->side;
            }
            else
            {
                return NULL;  //No drop this time
            }
        }
        else
        {
            return NULL;  //No drop this time
        }
    }

    CDrop* newdrop = new (nothrow) CDrop;
    if(newdrop==NULL)
    {
        Log(MSG_WARNING, "Error allocing memory [getdrop]" );
        return NULL;
    }
    newdrop->clientid = GetNewClientID( );
    newdrop->posMap = thismon->Position->Map;
    newdrop->pos = RandInCircle( thismon->Position->current, 3 );
    newdrop->droptime = time(NULL);
    newdrop->owner = thismon->MonsterDrop->firsthit;
    newdrop->thisparty = thismon->thisparty;
    ClearItem(newdrop->item);

    CPlayer* thisclient = GServer->GetClientByCID(thismon->MonsterDrop->firsthit);
    if(thisclient == NULL)
    {
        Log(MSG_WARNING,"GetPYDrop:: Failed to create player");
        return NULL;
    }

    // code to modify drop chance for different levels
    //float charm = 0;
    float charm = (float)thisclient->Attr->Cha / 5;
    float leveldif = (float)thismon->thisnpc->level - (float)thisclient->Stats->Level;
    float droprate = (float)GServer->Config.DROP_RATE + charm;  //basic server rate + extra for player charm
    float dropchance = (droprate + (droprate * 0.01 * leveldif));
    //Log(MSG_INFO,"charm %.2f, leveldif %.2f, droprate %.2f, dropchance %.2f",charm,leveldif,droprate,dropchance);
    if(dropchance < 10) dropchance = 10; //always a small chance of a drop even when the mob is more than 20 levels beneath your own
    //Log(MSG_INFO,"dropchance %.2f",dropchance);
    if(thismon->thisnpc->level == 1)
        dropchance = 80;
    //Log(MSG_INFO,"dropchance %.2f",dropchance);
    UINT lma_save_rand=0;
    lma_save_rand=GServer->RandNumber(0, 100);
    if (lma_save_rand>dropchance)
    {
        //Log(MSG_INFO,"no drop, %i > %.2f",lma_save_rand,dropchance);
        return NULL; // no drop here. not this time anyway.
    }

    //Log(MSG_INFO,"drop possible, %i <= %.2f",lma_save_rand,dropchance);

    CItemType prob[MDropList.size()];
    bool isdrop = false;
    int n = 0;
    int test = 0;
    long int probmax = 0;
    int itemnumber[MDropList.size()];
    int itemtype[MDropList.size()];
    int probability[MDropList.size()];
    int alternate[MDropList.size()][8];

    if( thismon->IsGhost())
    {
        // Stuff to do if the mob is a ghost of any type
        int selection = 1 + rand()%10;
        if( selection <= 3 ) //MP water
        {
            newdrop->type = 2;
            itemnumber[n] = 399;
            itemtype[n] = 12;
            probability[n] = 10;
            probmax =10;
            n++;
        }
        else if( selection <=6 ) //HP water
        {
            newdrop->type = 2;
            itemnumber[n] = 400;
            itemtype[n] = 12;
            probability[n] = 10;
            probmax =10;
            n++;
        }
        else  //skillbooks
        {
            for(int i=0; i<SkillbookList.size( ); i++)
            {
                newdrop->type = 2;
                CMDrops* thisdrop = GServer->SkillbookList.at(i);
                if(thisdrop->level_min <= thismon->thisnpc->level &&  thisdrop->level_max >= thismon->thisnpc->level)
                {
                    itemnumber[n] = thisdrop->itemnum;
                    itemtype[n] = thisdrop->itemtype;
                    probability[n] = thisdrop->prob;
                    probmax += thisdrop->prob;
                    n++;
                }
            }
        }
    }
    else
    {
        int randv = RandNumber( 1, 100);
        if(randv <= 30)//30% zuly drop instead of item drop
        {
            newdrop->type = 1; //Drop Zuly
            newdrop->amount = thismon->thisnpc->level * 5 * Config.ZULY_RATE + RandNumber( 1, 10 );
            //Log(MSG_INFO,"zuly drop %i",newdrop->amount);
            return  newdrop;
        }
        // Stuff to do if the mob isn't a ghost

        int randomdrop = GServer->RandNumber(1, 100);
        //enable the next line for debug purposes if you want to confirm a drop is working.
        //Log(MSG_INFO, "Mob type %i. Map = %i. Level = %i", thismon->montype, thismon->Position->Map,thismon->thisnpc->level);

        for(int i=0; i<MDropList.size( ); i++)
        {
            isdrop=false;
            CMDrops* thisdrop = GServer->MDropList.at(i);
            if(thisdrop->mob == thismon->montype)
            {
                //Mob drop possible.
                test = GServer->RandNumber(1, 1000);
                if(test < thisdrop->prob)
                {
                    isdrop = true;
                    //item will be added to the short list
                }
            }
            if(thisdrop->map == thismon->Position->Map)
            {
                //Map drop possible.
                test = GServer->RandNumber(1, 1000);
                if(thismon->thisnpc->level == 1)
                   test = GServer->RandNumber(1, 10000); // make it less likely to get map drops from event mobs
                if(test < thisdrop->prob)
                {
                    isdrop = true;
                    //item will be added to the short list
                }
            }
            if(thismon->thisnpc->level >= thisdrop->level_min && thismon->thisnpc->level <= thisdrop->level_max)
            {
                //Level drop possible
                test = GServer->RandNumber(1, 1000);
                if(test < thisdrop->prob)
                {
                    isdrop = true;
                    //item will be added to the short list
                }
            }
            if(isdrop == true) //Add item to the short list
            {
                if(droptype != 1) //side drops only. Skip if the item is not a match for side type
                {
                    if(itemtype[n] != droptype)continue;
                }
                //droptype 1 is a regular drop
                itemnumber[n] = thisdrop->itemnum;
                itemtype[n] = thisdrop->itemtype;
                //probability[n] = thisdrop->prob;
                alternate[n][0] = 0;
                for(int i=1;i<8;i++)
                {
                    alternate[n][i] = thisdrop->alt[i];
                }
                n++;
            }
        }
    }
    int newn = n;
    if(n == 0)
        return NULL;
    int maxitems = n;
    //maxitems is the number of items in the shortlist

    // randomize the item from the shortlist. items get equal chance
    n = GServer->RandNumber(0, maxitems);

    newdrop->item.itemnum = itemnumber[n];
    newdrop->item.itemtype = itemtype[n];
    newdrop->type = 2;

    newdrop->item.lifespan = 10 + rand()%80;
    float dmod = 0; //random number from 0 to 100 made up of 4 sub numbers to keep
    //the average value near to 50
    for(int i=0; i<4; i++)
    {
        float r1 = rand()%20;
        dmod += r1;
    }
    newdrop->item.durability = 10 + (int)dmod;
    if( newdrop->item.itemtype == 8 || newdrop->item.itemtype == 9 )
    {
        //This probability is now configurable from WorldServer.conf
        int psocked = rand()%101; //Probability of finding a socketed item
        if( psocked < Config.SlotChance) //default should be around 5% needs to be rare
        {
            newdrop->item.socketed = true;
        }
        else
        {
             newdrop->item.socketed = false;
        }
    }
    else
    {
        newdrop->item.socketed = false;
    }
    newdrop->item.appraised = false;
    newdrop->item.stats = 0;
    newdrop->item.count = 1;

    //chamod = a modifier based on the character's CHA stat. Increases the number of drops
    int chamod = (int)floor(thisclient->Attr->Cha / 20);
    if(chamod <0) chamod = 0;
    int basedrop = 6 + chamod; //Base number of items to be dropped. add CHA to increase this.
    if( newdrop->item.itemtype == 10 || newdrop->item.itemtype == 12 )
    {
        newdrop->item.count = RandNumber(0, basedrop);
        if(thismon->thisnpc->level == 1 && newdrop->item.count > 6) newdrop->item.count = 6; //limit the drop rate of items from level 1 event mobs
        if(newdrop->item.count==0)
            newdrop->item.count = 1;
        // Skillbooks & Chests
        if(newdrop->item.itemtype == 10)
        {
            if((newdrop->item.itemnum >=441 && newdrop->item.itemnum <= 888) ||
               (newdrop->item.itemnum >=247 && newdrop->item.itemnum <= 249) ||
               (newdrop->item.itemnum >=270 && newdrop->item.itemnum <= 275) ||
               (newdrop->item.itemnum >=1001 && newdrop->item.itemnum <= 1028) ||
               (newdrop->item.itemnum >=1110 && newdrop->item.itemnum <= 1178) ||
               (newdrop->item.itemnum >=1080 && newdrop->item.itemnum <= 1090) )
                newdrop->item.count = 1;   // just one skill book or chest per drop
        /*
        441-888    Skills
        247-249    Christmas Presents
        270-275    Dirty Stones
        1001-1028  Prison Chests
        1110-1178  Dispensers
        1080-1090  Event Boxes
        1200-1201  Christmas Gift - Present Box - Mileage
        1202-1203  Boy and Girl Snow Suit - Mileage
        */
        }
        // Gem Drops
        if(newdrop->item.itemtype == 11)
            newdrop->item.count = 1;   // just one gem per drop

        if(newdrop->item.itemtype == 12)
        {
            if(newdrop->item.itemnum > 300 && newdrop->item.itemnum < 360) //bullets get a lot higher count.
            {
                newdrop->item.count *= 10;
                newdrop->item.count += 10;
            }
        }
    }
    else if( newdrop->item.itemtype >1 && newdrop->item.itemtype !=7 && newdrop->item.itemtype < 10)
    {
        // check to see if the item will be refined
        int prefine = rand()%100; //Probability of finding a refined item
        if(prefine < Config.RefineChance) // default = 5%
        {
            int refinelevel = rand()%101;  //which level of refine do we actually get
            if( refinelevel < 5)        //default 5%
                newdrop->item.refine = 3 * 16;
            else if( refinelevel < 11 )   //10%
                newdrop->item.refine = 2 * 16;
            else                          // 90%
                newdrop->item.refine = 16;
        }
        else //99%
            newdrop->item.refine = 0;

        // will the item be a blue?
        int blue = 0;
        int bluechance1 = RandNumber( 1, 100);
        int bluechance2 = Config.BlueChance + chamod;


        // will the items get stats? All blue items will.
        int pstats = rand()%101; //Probability of the item having stats. default = 5%

        //This probability is now configurable from WorldServer.conf. CHA also has an effect
        if(bluechance1 < bluechance2) // some percentage of drops will be specials or blues whenever one is available.
        {
            //Log( MSG_INFO, "Selected a blue item");
            int p = 1;
            while(alternate[n][p] != 0 && p < 8)
            {
                p++;
            }
            if(p > 1) // blues available for this item
            {
                p--;
                int bluenum = RandNumber( 1, p);
                newdrop->item.itemnum = alternate[n][bluenum];
                pstats = 1; //make sure we get stats for this item
            }
            /*else
            {
                //Sorry blue item not available for this item
            }*/
        }
        //Uniques count as blues.
        if(newdrop->item.itemnum > 900)pstats = 1; //make sure we get stats for this unique item
        if( pstats < Config.StatChance)
        {   // default 5%
            //PY stats
            newdrop->item.stats = GetExtraStats( 0 );
            //newdrop->item.stats = rand()%300;
        }

    }
    newdrop->item.gem = 0;

    //Log(MSG_INFO,"drop %i* (%i:%i)",newdrop->amount,newdrop->type,newdrop->item);
    return newdrop;
}


 // PY extra stats lookup
 UINT CWorldServer::GetExtraStats( UINT modifier )
 {
    UINT stat = rand()%300 + modifier;
    if(stat > 300)stat = 300;
    return StatLookup[stat].statnumber;
 }


UINT CWorldServer::GetColorExp( UINT playerlevel,UINT moblevel, UINT exp )
{
    int dif = moblevel - playerlevel;

    if(dif>15)//purple
        exp = (UINT)floor(exp*1.5);
    else if(dif>10)
        exp = (UINT)floor(exp*1.2);
    else if(dif>4)
        exp = (UINT)floor(exp*1.1);
    else if(dif>-4)
        exp = (UINT)floor(exp*1);
    else if(dif>-9)
        exp = (UINT)floor(exp*0.7);
    else if(dif>-15)
        exp = (UINT)floor(exp*0.1);
    else if(dif>-25)
        exp = (UINT)floor(exp*0.005);
    else
        exp = 0;
    return exp;
}
bool CWorldServer::SendSysMsg( CPlayer* thisclient, string message )
{
	BEGINPACKET( pak, 0x7df );
	ADDBYTE    ( pak, 0xf1 );
	ADDSTRING  ( pak, message.c_str( ));
	ADDBYTE    ( pak, 0x00 );
	thisclient->client->SendPacket( &pak );
    return true;
}


// teleport to specificated map and position
bool CWorldServer::TeleportTo ( CPlayer* thisclient, int map, fPoint position )
{
    MapList.Index[map]->TeleportPlayer( thisclient, position, false );
    return true;
}

//LMA: checking compatible class (for skills)
bool CWorldServer::CheckCompatibleClass(UINT rclass, UINT player_job)
{
    if(rclass==player_job)
        return true;

    if(player_job>=121&&player_job<=122)
    {
        if(rclass==111)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    if(player_job>=221&&player_job<=222)
    {
        if(rclass==211)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    if(player_job>=321&&player_job<=322)
    {
        if(rclass==311)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    if(player_job>=421&&player_job<=422)
    {
        if(rclass==411)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    Log(MSG_INFO,"Class %i/%i not found?",rclass,player_job);


    return false;
}

// Learn Skill
//bool CWorldServer::LearnSkill( CPlayer* thisclient, UINT skill )
bool CWorldServer::LearnSkill( CPlayer* thisclient, UINT skill, bool takeSP)
{
    /*
    0 - already learned
    1 - he learned
    2 - not job
    3 - another skill is absent
    4 - not status points the (lvl)
    5 - it is not possible to raise of lvl the skill
    6 - incorrect number of skill
    7 - you do not have sufficient sp
    */

    int b=1;
    CSkills* thisskill = GetSkillByID( skill );
    if( thisskill==NULL )
        return false;

    //LMA: Is it an empty skill?
    if(GServer->SkillList[skill]->skill_tab==0)
    {
        Log(MSG_WARNING,"%s:: Incorrect or empty skill %i",thisclient->CharInfo->charname,skill);
        b=6;
    }

    if(takeSP&&thisclient->CharInfo->SkillPoints<thisskill->sp )
    {
        Log(MSG_WARNING,"%s:: not enough skill points (%u<%u) for skill %u",thisclient->CharInfo->charname,thisclient->CharInfo->SkillPoints,thisskill->sp,skill);
        b=7;
    }
    else if( thisskill->clevel>thisclient->Stats->Level )
    {
        Log(MSG_WARNING,"%s:: incorrect level for skill %u (%u<%u)",thisclient->CharInfo->charname,skill,thisskill->clevel,thisclient->Stats->Level);
        b=4;
    }

    if(b==1)
    {
        UINT rclass = 0;
        for(UINT i=0;i<4; i++)
        {
            if (thisskill->c_class[i] == 0)
            {
                continue;
            }

            if (thisskill->c_class[i] == 41)
            {
                rclass = 111;
            }
             else if (thisskill->c_class[i] == 42)
            {
                rclass = 211;
            }
            else if (thisskill->c_class[i] == 43)
            {
                rclass = 311;
            }
            else if (thisskill->c_class[i] == 44)
            {
                rclass = 411;
            }
            else if (thisskill->c_class[i] == 61)
            {
                rclass = 121;
            }
            else if (thisskill->c_class[i] == 62)
            {
                rclass = 122;
            }
            else if (thisskill->c_class[i] == 63)
            {
                rclass = 221;
            }
            else if (thisskill->c_class[i] == 64)
            {
                rclass = 222;
            }
            else if (thisskill->c_class[i] == 65)
            {
                rclass = 321;
            }
            else if (thisskill->c_class[i] == 66)
            {
                rclass = 322;
            }
            else if (thisskill->c_class[i] == 67)
            {
                rclass = 421;
            }
            else if (thisskill->c_class[i] == 68)
            {
                rclass = 422;
            }

            //LMA: new way, so "old" job skill can be learned...
            //if(rclass == thisclient->CharInfo->Job)
            if(CheckCompatibleClass(rclass,thisclient->CharInfo->Job))
            {
                b=1;
                break;
            }
            else
            {
                Log(MSG_WARNING,"%s:: Incompatible class for skill %u (%u)",thisclient->CharInfo->charname,skill,rclass);
                b=2;
            }
        }
    }
    if(b==1)
    {
        for(UINT i=0;i<3; i++)
        {
            if(thisskill->rskill[i] != 0)
            {
                UINT rskill = thisclient->GetPlayerSkill(thisskill->rskill[i]);
                if(rskill == 0xffff)
                {
                    Log(MSG_WARNING,"%s:: Necessary skill %u not found to learn %u",thisclient->CharInfo->charname,thisskill->rskill[i],skill);
                    b=3;
                }
                else
                {
                    if(thisskill->lskill[i] > thisclient->cskills[rskill].level)
                    {
                        Log(MSG_WARNING,"%s:: Necessary skill (%u) level incorrect (%u>%u) to learn %u",thisclient->CharInfo->charname,thisskill->rskill[i],thisskill->lskill[i],thisclient->cskills[rskill].level,skill);
                        b=5;
                    }

                }

            }

        }

    }

    if(b==1)
    {
        //LMA: Looking for good place to save it now...
        int family=thisclient->GoodSkill(skill);
        if(family==-1)
        {
            Log(MSG_WARNING,"%s:: Can't find family for skill %i",thisclient->CharInfo->charname,skill);
            b=6;
        }
        else
        {
            int index=thisclient->FindSkillOffset(family);
            if(index==-1)
            {
                Log(MSG_WARNING,"%s:: Can't find index in family %i for skill %i",thisclient->CharInfo->charname,family,skill);
                b=6;
            }
            else
            {
                thisclient->cskills[index].id=skill;
                thisclient->cskills[index].level=1;
                thisclient->cskills[index].thisskill = thisskill;

                if (takeSP)
                {
                    thisclient->CharInfo->SkillPoints -= thisskill->sp;
                }
                //in the good family now.
                //thisclient->SaveSkillInfo(family,thisclient->cur_max_skills[family],skill,1);
                thisclient->saveskills();

                BEGINPACKET( pak, 0x7b0 );
                ADDBYTE    ( pak, b);
                ADDWORD    ( pak, index);
                ADDWORD    ( pak, skill);
                ADDWORD    ( pak, thisclient->CharInfo->SkillPoints);
                thisclient->client->SendPacket( &pak);
                thisclient->SetStats( );


                return true;
                //LMA: new way end.
            }

        }

    }

    BEGINPACKET( pak, 0x7b0 );
    ADDBYTE    ( pak, b);
    ADDWORD    ( pak, thisclient->p_skills-1);
    ADDWORD    ( pak, skill);
    ADDWORD    ( pak, thisclient->CharInfo->SkillPoints);
    thisclient->client->SendPacket( &pak);

    Log(MSG_WARNING,"%s:: skill %i not learned (error %i)",thisclient->CharInfo->charname,skill,b);


    return false;
}

//add / remove a Fairy
void CWorldServer::DoFairyStuff(CPlayer* targetclient, int action)
{
    BEGINPACKET( pak, 0x7dc );
	ADDBYTE( pak, action );
	ADDWORD( pak, targetclient->clientid);
	SendToVisible( &pak, targetclient );
}

void CWorldServer::DoFairyFree( int fairy )
{
    GServer->FairyList.at(fairy)->assigned = false;
    GServer->FairyList.at(fairy)->ListIndex = 0;

    if(GServer->Config.FairyTestMode == 0)
         GServer->FairyList.at(fairy)->WaitTime = GServer->Config.FairyWait * (rand()% GServer->GetFairyRange(1)+ GServer->GetFairyRange(0));

    GServer->FairyList.at(fairy)->LastTime = clock();
}

void CWorldServer::RefreshFairy( )
{
        //fairy: The wait timer should be possibibly bigger when there is few people online.
        if (Config.FairyMode == 1 && ClientList.size() > 1){   //if fairy mode on and someone online
           for (int i=0; i<Config.FairyMax; i++)     // check all fairies
           {
                if ( FairyList.at(i)->LastTime <= ( clock() - (FairyList.at(i)->WaitTime*60*CLOCKS_PER_SEC) ) && !FairyList.at(i)->assigned )  // if fairy hour is now
	            {
                    int value = rand()%(int)(ClientList.size()-1) + 1;  //choose random value in clientlist
		            CPlayer* targetclient = (CPlayer*) ClientList.at(value)->player;

		            //LMA: Patch if fairy was attributed as the player is not actually yet IG...
		            //The Fairy is not an easy lady ^_^
		            if ((clock()-targetclient->firstlogin)>(60*CLOCKS_PER_SEC))
		            {
                        FairyList.at(i)->ListIndex = value;
    			        FairyList.at(i)->LastTime = clock();
    			        FairyList.at(i)->assigned = true;
    			        targetclient->Fairy = true;
    			        targetclient->FairyListIndex = i;                 // FairyList index number of our actual fairy
    			        DoFairyStuff(targetclient, 1);           // spawn fairy to target
    			        targetclient->SetStats();
                    }

                }
			    if ( (FairyList.at(i)->LastTime + (Config.FairyStay*60*CLOCKS_PER_SEC)) <= clock() && FairyList.at(i)->assigned)  // id time for our fairy to go away
    			{
                    CPlayer* oldclient  = (CPlayer*) ClientList.at(FairyList.at(i)->ListIndex)->player;
                    DoFairyFree(i);
                    oldclient->Fairy = false;
                    oldclient->FairyListIndex = 0;
                    DoFairyStuff(oldclient, 0);  // unspawn fairy
                    oldclient->SetStats();
                }
           }
        }
        // this close fairies after their time if GM de activate  fairy mode when some fairies are assigned.
        if (Config.FairyMode == 0 && ClientList.size() > 1){    // if serevr mode off and someone online
             for (int i=0; i<Config.FairyMax; i++)
             {
                 if ( (FairyList.at(i)->LastTime + (Config.FairyStay*60*CLOCKS_PER_SEC)) <= clock() && FairyList.at(i)->assigned)
    			{
                    CPlayer* oldclient  = (CPlayer*) ClientList.at(FairyList.at(i)->ListIndex)->player;
                    DoFairyFree(i);
                    oldclient->Fairy = 0;
                    oldclient->FairyListIndex = 0;
                    DoFairyStuff(oldclient, 0);
                    oldclient->SetStats();
                }
             }
         }
}
