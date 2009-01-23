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

    //LMA: loading Pegasus data.
    if(Config.is_pegasus==1)
    {
        STBStoreData( "3DDataPeg\\STB\\LIST_NPC.STB", &STB_NPC );
        STBStoreData( "3DDataPeg\\STB\\LIST_SKILL.STB", &STB_SKILL );
        STBStoreData( "3DDataPeg\\STB\\LIST_STATUS.STB", &STB_STATUS );
        STBStoreData( "3DDataPeg\\STB\\LIST_FACEITEM.STB", &STB_ITEM[0] );
        STBStoreData( "3DDataPeg\\STB\\LIST_CAP.STB", &STB_ITEM[1] );
        STBStoreData( "3DDataPeg\\STB\\LIST_BODY.STB", &STB_ITEM[2] );
        STBStoreData( "3DDataPeg\\STB\\LIST_ARMS.STB", &STB_ITEM[3] );
        STBStoreData( "3DDataPeg\\STB\\LIST_FOOT.STB", &STB_ITEM[4] );
        STBStoreData( "3DDataPeg\\STB\\LIST_BACK.STB", &STB_ITEM[5] );
        STBStoreData( "3DDataPeg\\STB\\LIST_JEWEL.STB", &STB_ITEM[6] );
        STBStoreData( "3DDataPeg\\STB\\LIST_WEAPON.STB", &STB_ITEM[7] );
        STBStoreData( "3DDataPeg\\STB\\LIST_SUBWPN.STB", &STB_ITEM[8] );
        STBStoreData( "3DDataPeg\\STB\\LIST_USEITEM.STB", &STB_ITEM[9] );
        STBStoreData( "3DDataPeg\\STB\\LIST_JEMITEM.STB", &STB_ITEM[10] );
        STBStoreData( "3DDataPeg\\STB\\LIST_NATURAL.STB", &STB_ITEM[11] );
        STBStoreData( "3DDataPeg\\STB\\LIST_QUESTITEM.STB", &STB_ITEM[12] );
        STBStoreData( "3DDataPeg\\STB\\LIST_PAT.STB", &STB_ITEM[13] );
        STBStoreData( "3DDataPeg\\STB\\LIST_PRODUCT.STB", &STB_PRODUCT );
        STBStoreData( "3DDataPeg\\STB\\LIST_SELL.STB", &STB_SELL );
        STBStoreData( "3DDataPeg\\STB\\LIST_ZONE.STB", &STB_ZONE );
        STBStoreData( "3DDataPeg\\STB\\ITEM_DROP.STB", &STB_DROP );
        STBStoreData("3DDataPeg\\STB\\LIST_UPGRADE.STB", &upgradeData);
        STBStoreData("3DDataPeg\\STB\\LIST_BREAK.STB", &BreakData);    //LMA: for break and chest and blue break.
    }
    else
    {
        STBStoreData( "3DData\\STB\\LIST_NPC.STB", &STB_NPC );
        STBStoreData( "3DData\\STB\\LIST_SKILL.STB", &STB_SKILL );
        STBStoreData( "3DData\\STB\\LIST_STATUS.STB", &STB_STATUS );
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
        STBStoreData("3DData\\STB\\LIST_UPGRADE.STB", &upgradeData);
        STBStoreData("3DData\\STB\\LIST_BREAK.STB", &BreakData);    //LMA: for break and chest and blue break.
    }


}

//LMA: loading LTB (for AIP)
bool CWorldServer::LoadLTB( )
{
    maxltbaip=0;
    maxltbqsd=0;
    Log(MSG_INFO, "Loading LTB strings");

    //LMA: loading Pegasus data.
    if(Config.is_pegasus==1)
    {
        LTBStoreData("3DDataPeg\\AI\\ULNGTB_AI.LTB",&MyLTB);
        LTBStoreData("3DDataPeg\\QUESTDATA\\ULNGTB_QST.LTB",&MyLTBQSD);
    }
    else
    {
        LTBStoreData("3DData\\AI\\ULNGTB_AI.LTB",&MyLTB);
        LTBStoreData("3DData\\QUESTDATA\\ULNGTB_QST.LTB",&MyLTBQSD);
    }

    if (MyLTB.record.size()==0||MyLTBQSD.record.size()==0)
    {
        return true;
    }

    //LTB for AIP
    maxltbaip=MyLTB.record.size();
    Ltbstring = new CLTBstring*[MyLTB.record.size()];
    for (unsigned int k=0;k<MyLTB.record.size();k++)
    {
        //cout << "IndexMyLTB " << k << " NPC: " << MyLTB.record.at(k).name.c_str() << ", sentence: " << MyLTB.record.at(k).sentence.c_str() << endl;
        CLTBstring* tempLTB = new CLTBstring;
        tempLTB->NPCname=new char[MyLTB.record.at(k).name.size()+1];
        strcpy (tempLTB->NPCname, MyLTB.record.at(k).name.c_str());
        tempLTB->LTBstring=new char[MyLTB.record.at(k).sentence.size()+1];
        strcpy (tempLTB->LTBstring, MyLTB.record.at(k).sentence.c_str());
        GServer->Ltbstring[k]=tempLTB;
    }

    //LTB for QSD
    maxltbqsd=MyLTBQSD.record.size();
    LtbstringQSD = new CLTBstring*[MyLTBQSD.record.size()];
    for (unsigned int k=0;k<MyLTBQSD.record.size();k++)
    {
        //cout << "IndexMyLTBQSD " << k << " NPC: " << MyLTBQSD.record.at(k).name.c_str() << ", sentence: " << MyLTBQSD.record.at(k).sentence.c_str() << endl;
        CLTBstring* tempLTB = new CLTBstring;
        tempLTB->NPCname=new char[2];
        strcpy (tempLTB->NPCname, " ");
        tempLTB->LTBstring=new char[MyLTBQSD.record.at(k).sentence.size()+1];
        strcpy (tempLTB->LTBstring, MyLTBQSD.record.at(k).sentence.c_str());
        GServer->LtbstringQSD[k]=tempLTB;
    }

    Log( MSG_INFO, "LTB Data Loaded" );

    return true;
}

//LMA: we init default values for some lists.
bool CWorldServer::InitDefaultValues()
{
    //Creating indexes
    for(int j=0;j<9;j++)
    {
        EquipList[j+1].Index = new CEquip*[STB_ITEM[j].rowcount];
        EquipList[j+1].max=STB_ITEM[j].rowcount;
    }

    JemList.Index = new CJemData*[STB_ITEM[10].rowcount];
    JemList.max=STB_ITEM[10].rowcount;
    NaturalList.Index = new CNaturalData*[STB_ITEM[11].rowcount];
    NaturalList.max=STB_ITEM[11].rowcount;
    PatList.Index = new CPatData*[STB_ITEM[13].rowcount];
    PatList.max=STB_ITEM[13].rowcount;
    ProductList.Index = new CProductData*[STB_PRODUCT.rowcount];
    ProductList.max=STB_PRODUCT.rowcount;
    SellList.Index = new CCSellData*[STB_SELL.rowcount];
    SellList.max=STB_SELL.rowcount;
    UseList.Index = new CUseData*[STB_ITEM[9].rowcount];
    UseList.max=STB_ITEM[9].rowcount;

    //LMA: hard for now...
    MapList.Index = new CMap*[300];
    MapList.max=300;

    //stats.
    StatusList=new CStatus*[STB_STATUS.rowcount];
    maxStatus=STB_STATUS.rowcount;

    //Skills and NPC as static array too, but no init for this one.
    SkillList=new CSkills*[STB_SKILL.rowcount];
    maxSkills=STB_SKILL.rowcount;
    NPCData=new CNPCData*[STB_NPC.rowcount];
    maxNPC=STB_NPC.rowcount;

    //Item stats.
    StatsList=new CItemStas*[STB_ITEM[10].rowcount];
    maxStats=STB_ITEM[10].rowcount;

    //Equip null init
    CEquip* nullequip = new CEquip;
    nullequip->id = 0;
    nullequip->equiptype = 0;
    nullequip->type = 0;
    nullequip->price = 0;
    nullequip->pricerate = 0;
    nullequip->weight = 0;
    nullequip->quality = 0;
    nullequip->level = 0;
    nullequip->material = 0;
    nullequip->defense = 0;
    nullequip->magicresistence = 0;
    nullequip->attackdistance = 0;
    nullequip->movespeed = 0;
    nullequip->attackpower = 0;
    nullequip->attackspeed =0;
    nullequip->itemgrade = 0;
    for(int i=0;i<3;i++)
    {
        nullequip->occupation[i] = 0;
        nullequip->condition1[i] = 0;
        nullequip->condition2[i] = 0;
    }
    for(int i=0;i<2;i++)
    {
        nullequip->stat1[i] = 0;
        nullequip->stat2[i] = 0;
    }
    for(int i=0;i<10;i++)
    {
        EquipList[i].nullequip = nullequip;
        for(UINT j=0;j<EquipList[i].max;j++)
            EquipList[i].Index[j] = nullequip;
    }

    //natural null init
    CNaturalData* nullnatural = new CNaturalData;
    nullnatural->id = 0;
    nullnatural->type = 0;
    nullnatural->price = 0;
    nullnatural->pricerate = 0;
    nullnatural->weight = 0;
    nullnatural->quality = 0;
    nullnatural->pricevalue = 0;
    NaturalList.nullnatural = nullnatural;

    for(UINT i=0;i<NaturalList.max;i++)
    {
        NaturalList.Index[i] = nullnatural;
    }

    //pat null init
    CPatData* nullpat = new CPatData;
    nullpat->id = 0;
    nullpat->type = 0;
    nullpat->price = 0;
    nullpat->pricerate = 0;
    nullpat->weight = 0;
    nullpat->quality = 0;
    nullpat->material = 0;
    nullpat->partversion = 0;
    nullpat->maxfuel = 0;
    nullpat->fuelcons = 0;
    nullpat->speed = 0;
    nullpat->attackdistance = 0;
    nullpat->attackpower = 0;
    nullpat->attackspeed = 0;
    PatList.nullpat = nullpat;
    for(UINT i=0;i<PatList.max;i++)
    {
        PatList.Index[i] = nullpat;
    }

    //sell null init
    CCSellData* nullsell = new CCSellData;
    nullsell->id = 0;
    for(UINT i=0;i<48;i++)
        nullsell->item[i] = 0;
    SellList.nullsell = nullsell ;

    for(UINT i=0;i<SellList.max;i++)
    {
        SellList.Index[i] = nullsell;
    }

    //map null init
    CMap* nullzone = new CMap( );
    nullzone->id =0;
    nullzone->dayperiod = 1;
    nullzone->morningtime = 0;
    nullzone->daytime = 0;
    nullzone->eveningtime = 0;
    nullzone->nighttime = 0;
    nullzone->allowpvp = 0;
    nullzone->allowpat = 0;
    nullzone->MapTime = 0;
    nullzone->LastUpdate = 0;
    nullzone->CurrentTime = 0;
    for(UINT i=0;i<MapList.max;i++)
    {
        MapList.Index[i] = nullzone;
    }

    MapList.nullzone = nullzone;

    //Use null init
    CUseData* nulluse = new CUseData;
    nulluse->id = 0;
    nulluse->restriction = 0;
    nulluse->type = 0;
    nulluse->price = 0;
    nulluse->pricerate = 0;
    nulluse->weight = 0;
    nulluse->quality = 0;
    nulluse->pricevalue = 0;
    for(int i=0;i<2;i++)
    {
        nulluse->usecondition[i] = 0;
        nulluse->useeffect[i] = 0;
    }
    UseList.nulluse = nulluse;
    for(UINT i=0;i<UseList.max;i++)
    {
        UseList.Index[i] = nulluse;
    }

    //product null init
    CProductData* nullproduct = new CProductData;
    nullproduct->id = 0;
    for(UINT i=0;i<50;i++)
    {
        nullproduct->item[i];
        nullproduct->amount[i];
    }
    ProductList.nullproduct = nullproduct;
    for(UINT i=0;i<ProductList.max;i++)
    {
        ProductList.Index[i] = nullproduct;
    }

    //jem null init
    CJemData* nulljem = new CJemData;
    nulljem->id = 0;
    nulljem->type = 0;
    nulljem->price = 0;
    nulljem->pricerate = 0;
    nulljem->weight = 0;
    nulljem->quality = 0;
    nulljem->material = 0;
    for(int i=0;i<2;i++)
    {
        nulljem->stat1[i] = 0;
        nulljem->stat2[i] = 0;
    }
    JemList.nulljem = nulljem ;
    for(UINT i=0;i<JemList.max;i++)
    {
        JemList.Index[i] = nulljem;
    }


    return true;
}

//LMA: npc_data, STB version.
bool CWorldServer::LoadNPCData( )
{
	Log( MSG_LOAD, "NPC Data - STB               " );
    for (UINT i = 0; i<STB_NPC.rowcount; i++)
    {
        CNPCData* newnpc = new (nothrow) CNPCData;
        if(newnpc==NULL)
        {
            Log( MSG_ERROR, "Error allocing memory" );
            continue;
        }

        newnpc->id = i;
        newnpc->life = 0;    //LMA: non sense, it's the name lol
        newnpc->stance = mRUNNING;  //AIP
        newnpc->wspeed = STB_NPC.rows[i][2];
        newnpc->rspeed = STB_NPC.rows[i][3];
        newnpc->dspeed = STB_NPC.rows[i][4];
        newnpc->weapon = STB_NPC.rows[i][5];
        newnpc->subweapon = STB_NPC.rows[i][6];
        newnpc->level = STB_NPC.rows[i][7];
        newnpc->hp = STB_NPC.rows[i][8];
        newnpc->atkpower = STB_NPC.rows[i][9];
        newnpc->hitrate = STB_NPC.rows[i][10];
        newnpc->defense = STB_NPC.rows[i][11];
        newnpc->magicdefense = STB_NPC.rows[i][12];
        newnpc->dodge = STB_NPC.rows[i][13];
        newnpc->atkspeed = STB_NPC.rows[i][14];
        newnpc->AI = STB_NPC.rows[i][16];
        newnpc->exp = STB_NPC.rows[i][17];

        newnpc->dropid = STB_NPC.rows[i][18];
        newnpc->money = STB_NPC.rows[i][19];
        newnpc->item = STB_NPC.rows[i][20];
        newnpc->tab1 = STB_NPC.rows[i][21];
        newnpc->tab2 = STB_NPC.rows[i][22];
        newnpc->tab3 = STB_NPC.rows[i][23];
        newnpc->specialtab = STB_NPC.rows[i][24];

        newnpc->atkdistance = STB_NPC.rows[i][26]/100;
        newnpc->aggresive = STB_NPC.rows[i][27];
        newnpc->helpless=0;
        newnpc->shp = STB_NPC.rows[i][42];
        newnpc->dialogid = 0;   //handled in list_npc now
        newnpc->eventid = 0;   //handled in list_npc now
        newnpc->side=0; //hidden
        newnpc->sidechance=0;   //hidden

        //LMA: Various skills for monsters (won't be used anymore, will be done by AIP, for now left for compatibility).
        for(int i=0;i<4;i++)
        {
          newnpc->askills[i]=0;
          newnpc->bskills[i]=0;
          newnpc->dskills[i]=0;
        }

        newnpc->lastskill=0;
        newnpc->sigskill=0;
        newnpc->delayskill=0;

        NPCData[newnpc->id]=newnpc;
    }

    STBFreeData(&STB_NPC);
    Log( MSG_LOAD, "NPC Data loaded          STB" );


    return true;
}

//old version (sql).
bool CWorldServer::LoadSkillDataOld( )
{
    //test stuff.

    return true;
}

//LMA: Stuff... Used for tests :)
bool CWorldServer::LMACheckStuff()
{
    //test test :)

    return true;
}


//LMA: We compare STB and SQL "skills" to check differences (for debug purpose only!!!).
bool CWorldServer::LMACheckSkills()
{
    //test.

    return true;
}

//loading status.
bool CWorldServer::LoadStatusData( )
{
  Log( MSG_LOAD, "Stats Data             " );
  for (unsigned int i = 0; i < STB_STATUS.rowcount; i++)
  {
    CStatus* newstatus = new (nothrow) CStatus;
    if (newstatus == NULL)
    {
      Log(MSG_WARNING, "\nError allocing memory: status_data");
      return false;
    }
    newstatus->id = i;
    newstatus->type = STB_STATUS.rows[i][1];  // Unk
    newstatus->duplication = STB_STATUS.rows[i][2]; // Unk
    newstatus->dir = STB_STATUS.rows[i][3]; // 0: Up 1: Down 2: ?
    newstatus->repeat = STB_STATUS.rows[i][4]; // 1: Repeat (Heal) 2: Once (Buff Stat) 3: Status Effect (Poison, etc)
    newstatus->ability[0] = STB_STATUS.rows[i][5]; // Status # to call?
    newstatus->amount[0] = STB_STATUS.rows[i][6]; // Amount
    newstatus->ability[1] = STB_STATUS.rows[i][7];
    newstatus->amount[1] = STB_STATUS.rows[i][8];
    newstatus->decrease = STB_STATUS.rows[i][17]; // 0: Increase 1: Decrease
    StatusList[i]=newstatus;
  }

  Log( MSG_LOAD, "Stats Data loaded       " );
  return true;
}


//News version (STB)
bool CWorldServer::LoadSkillData( )
{
	Log( MSG_LOAD, "Skills data - STB        " );
    for (unsigned int i = 0; i<STB_SKILL.rowcount;i++)
    {
        CSkills* newskill = new (nothrow) CSkills;
        if(newskill==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: skills_data" );
            return false;
        }
        char *tmp;
        newskill->id=i;

        newskill->level = STB_SKILL.rows[i][2];  // Skills Level
        newskill->sp = STB_SKILL.rows[i][3];     // Cost to get skill
        newskill->type = STB_SKILL.rows[i][4];   //tab type.
        newskill->skill_tab=STB_SKILL.rows[i][4];   //tab type.
        newskill->skilltype = STB_SKILL.rows[i][5]; // Type of skill
        newskill->range = STB_SKILL.rows[i][6]/100; // Range of skill
        newskill->target = STB_SKILL.rows[i][7];    // Skill Target
        newskill->aoerange = STB_SKILL.rows[i][8]/100; // AOE Range
        newskill->atkpower = STB_SKILL.rows[i][9];     // Attack Power
        newskill->gm_aoe=0; //LMA: GM AOE buff

        //LMA: Patch for osRose.
        //For us type is skilltype...
        newskill->type=newskill->skilltype;

        //LMA: Not the same IDs in ospRose and osRose...
        /*
        newskill->status[0] = STB_SKILL.rows[i][11];  // status
        newskill->status[1] = STB_SKILL.rows[i][12];  // status
        */
        newskill->status[0] = STB_SKILL.rows[i][88];  // status
        newskill->status[1] = STB_SKILL.rows[i][92];  // status
        newskill->status[2] = STB_SKILL.rows[i][96];  // status

        newskill->success = STB_SKILL.rows[i][13];    // Success Rate
        if(newskill->success == 0)
        {
            newskill->success = 100;                //success rate is stored as NULL where it is 100%. eg dual scratch
        }

        newskill->duration = STB_SKILL.rows[i][14];   // Duration
        newskill->costtype[0] = STB_SKILL.rows[i][16];   //not all costs are in MP
        newskill->costamount[0] = STB_SKILL.rows[i][17]; //some are in HP or Stamina
        newskill->mp = STB_SKILL.rows[i][17];
        newskill->costtype[1] = STB_SKILL.rows[i][18]; // All driveby skills have 2 costs
        newskill->costamount[1] = STB_SKILL.rows[i][19]; // The second is normally cart gauge
        newskill->cooldown = STB_SKILL.rows[i][20];   // The time it takes to be able to use the skill again.
        //newskill->success=STB_SKILL.rows[i][69];    //Dunno what this field is really but it sure isn't success rate <_<

        newskill->weapon[0] = STB_SKILL.rows[i][30];    // Item Type must be equipped (Only 1)
        newskill->weapon[1] = STB_SKILL.rows[i][31];    // Item Type must be equipped
        newskill->weapon[2] = STB_SKILL.rows[i][32];    // Item Type must be equipped
        newskill->weapon[3] = STB_SKILL.rows[i][33];    // Item Type must be equipped
        newskill->weapon[4] = STB_SKILL.rows[i][34];    // Item Type must be equipped
        newskill->c_class[0] = STB_SKILL.rows[i][35];   // Required Class (Only One)
        newskill->c_class[1] = STB_SKILL.rows[i][36];   // Required Class
        newskill->c_class[2] = STB_SKILL.rows[i][37];   // Required Class
        newskill->c_class[3] = STB_SKILL.rows[i][38];   // Required Class
        newskill->c_class[4] = 0;
        newskill->rskill[0] = STB_SKILL.rows[i][39];    // Required Skill
        newskill->rskill[1] = STB_SKILL.rows[i][41];    // Required Skill
        newskill->rskill[2] = STB_SKILL.rows[i][43];    // Required Skill
        newskill->lskill[0] = STB_SKILL.rows[i][40];    // Required Skill Level
        newskill->lskill[1] = STB_SKILL.rows[i][42];    // Required Skill Level
        newskill->lskill[2] = STB_SKILL.rows[i][44];    // Required Skill Level

        //LMA: Not the same IDs in ospRose and osRose...
        //and we add the skill status (like poisoned...)
        /*
        newskill->buff[0] = STB_SKILL.rows[i][21];      // Stat
        newskill->value1[0] = STB_SKILL.rows[i][22];    // Int Value
        newskill->value2[0] = STB_SKILL.rows[i][23];    // % Value
        newskill->buff[1] = STB_SKILL.rows[i][24];      // Stat
        newskill->value1[1] = STB_SKILL.rows[i][25];    // Int Value
        newskill->value2[1] = STB_SKILL.rows[i][26];    // % Value
        */

        newskill->buff[0] = STB_SKILL.rows[i][89];      // Stat
        newskill->value1[0] = STB_SKILL.rows[i][90];    // Int Value
        newskill->value2[0] = STB_SKILL.rows[i][91];    // % Value
        newskill->buff[1] = STB_SKILL.rows[i][93];      // Stat
        newskill->value1[1] = STB_SKILL.rows[i][94];    // Int Value
        newskill->value2[1] = STB_SKILL.rows[i][95];    // % Value
        newskill->buff[2] = STB_SKILL.rows[i][97];      // Stat
        newskill->value1[2] = STB_SKILL.rows[i][98];    // Int Value
        newskill->value2[2] = STB_SKILL.rows[i][99];    // % Value

        newskill->req[0] = STB_SKILL.rows[i][45];    //the requirement type (usually 31 = level)
        newskill->clevel = STB_SKILL.rows[i][46];    //requirement amount
        newskill->reqam[0] = STB_SKILL.rows[i][46];  //this need no always be level but is usually
        newskill->req[1] = STB_SKILL.rows[i][47];    //the requirement type (in most cases blank)
        newskill->reqam[1] = STB_SKILL.rows[i][48];  //requirement amount
        newskill->zuly = (STB_SKILL.rows[i][85] * 100);    // Required zuly

        if ((STB_SKILL.rows[i][8])>0)
        {
            newskill->aoe = 1;
            newskill->aoeradius = STB_SKILL.rows[i][8]/100;
        }
        else
        {
            newskill->aoe = 0;
            newskill->aoeradius = 0;
        }
        if ((STB_SKILL.rows[i][28])>0)
        {
            newskill->script = 1;
            newskill->svalue1 = STB_SKILL.rows[i][28];
        }
        else
        {
            newskill->script=0;
            newskill->svalue1=0;
        }

        //LMA: Patch for some skills (?)
        if(newskill->status[0]==35||newskill->status[0]==54||newskill->status[0]==83)
        {
            if(newskill->buff[0]==0&&newskill->value1[0]==0)
            {
                newskill->buff[0]=newskill->status[0];
                newskill->value1[0]=newskill->atkpower;
                //Log(MSG_INFO,"Skill (%i) status0=%i, buff0=%i, value=%i",i,newskill->status[0],newskill->buff[0],newskill->value1[0]);
            }

        }
        //end of patch.

        newskill->nbuffs = 0;
        if(newskill->buff[0] != 0 || newskill->status[0] != 0)
        {
            newskill->nbuffs += 1;
        }

        if(newskill->buff[1]!= 0 || newskill->status[1] != 0)
        {
            newskill->nbuffs += 2;
        }

        //LMA: add the [2]?
        if(newskill->buff[2]!= 0 || newskill->status[2] != 0)
        {
            newskill->nbuffs += 4;
        }

        SkillList[i]=newskill;
	}

	Log( MSG_LOAD, "Skills Data - STB loaded" );


    return true;
}


bool CWorldServer::LoadTeleGateData( )
{
	Log( MSG_LOAD, "Telegates data              " );
	MYSQL_ROW row;

    //LMA: Pegasus
    MYSQL_RES *result=NULL;
    if(Config.is_pegasus==1)
    {
        result = DB->QStore("SELECT id, srcx, srcy, srcmap, destx, desty, destmap FROM list_telegates_p");
    }
    else
    {
        result = DB->QStore("SELECT id, srcx, srcy, srcmap, destx, desty, destmap FROM list_telegates");
    }

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
        //thisgate->dest.x = (float)atof(row[1]);
        //thisgate->dest.y = (float)atof(row[2]);
        //thisgate->destMap = atoi(row[3]);
		TeleGateList.push_back( thisgate );
	}
	DB->QFree( );
	Log( MSG_LOAD, "Telegates Data loaded" );
	return true;
}

//Loading Quests
bool CWorldServer::LoadQuestSTB()
{
    //LMA: loading Pegasus data.
    if(Config.is_pegasus==1)
    {
        STBStoreData( "3DDataPeg/stb/LIST_QUEST.STB", &STB_QUEST );
    }
    else
    {
        STBStoreData( "3ddata/stb/LIST_QUEST.STB", &STB_QUEST );
    }

    Log(MSG_INFO,"STB Loaded for QSD Version !!!");
    return true;
}


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
        if (thisrespawnpoint->destMap>=MapList.max)
        {
           Log(MSG_WARNING,"RespawnZones, index overflow trapped %i>%i (increase MAX_MAP_DATA)",thisrespawnpoint->destMap,MapList.max);
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

bool CWorldServer::LoadMobGroups()
{
  Log(MSG_LOAD, "MobGroups data    " );
  //vector<CMobGroup*> mobGroups;
  MYSQL_ROW row;
  bool flag = true;
  char* tmp = NULL;

  //LMA: Day and night (for Halloween)
  //For pegasus too
  MYSQL_RES *result=NULL;
    if(Config.is_pegasus==1)
    {
        result = DB->QStore("SELECT `id`, `map`, `x`, `y`, `range`, `respawntime`, `limit`, `tacticalpoints`, `moblist`,`daynight`,`isactive`  FROM `list_mobgroups_p`");
    }
    else
    {
        result = DB->QStore("SELECT `id`, `map`, `x`, `y`, `range`, `respawntime`, `limit`, `tacticalpoints`, `moblist`,`daynight`,`isactive`  FROM `list_mobgroups`");
    }

  if (result == NULL) return false;
  while (row = mysql_fetch_row(result))
  {
    //LMA: Active spawn?
    int is_active=atoi(row[10]);
    if(is_active==0)
        continue;

    CMobGroup* thisgroup = new (nothrow) CMobGroup;
    if (thisgroup == NULL)
    {
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

    //LMA: Day and night (for Halloween) 0=day and night, 1=day, 2=night
    thisgroup->daynight=atoi(row[9]);

    thisgroup->lastRespawnTime = clock();
    thisgroup->active = 0;
    thisgroup->basicKills = 0;
    thisgroup->curTac = 0;
    thisgroup->curBasic = 0;


    thisgroup->basicMobs.clear();
    thisgroup->tacMobs.clear();

    //LMA: resetting the error flag
    flag=true;

    // Fill in basic/tac mobs
    tmp = strtok(mobList, ",|");
    while (tmp != NULL)
    {

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

      //LMA: We check here and delete the whole group.
      if (thismob->thisnpc == NULL)
      {
        Log(MSG_WARNING, "Group %i:: Invalid monster %i",thisgroup->id,thismob->mobId);
        flag=false;
        break;
      }

    //LMA: shouldn't be PY'drop used in those ones?
      thismob->mapdrop=NULL;
      thismob->mobdrop=NULL;

    /*
    //Org code
      thismob->mapdrop = GetDropData( thisgroup->map );
      thismob->mobdrop= GetDropData( thismob->thisnpc->dropid );
      */

      if (thismob->tactical)
        thisgroup->tacMobs.push_back(thismob);
      else
        thisgroup->basicMobs.push_back(thismob);
      tmp = strtok(NULL, ",|");
     }

        if (!flag)
        {
          delete thisgroup;
          continue;
        }

        MapList.Index[thisgroup->map]->MobGroupList.push_back(thisgroup);
        //mobGroups.push_back(thisgroup);
    }

    DB->QFree( );


    return true;
}

//LMA: Special Spawns (like Halloween or whatever...)
bool CWorldServer::LoadMobGroupsSpecial()
{
  Log(MSG_LOAD, "MobGroupsSpecial data    " );
  //vector<CMobGroup*> mobGroups;
  MYSQL_ROW row;
  bool flag = true;
  char* tmp = NULL;
  //LMA: Day and night (for Halloween)
  MYSQL_RES *result = DB->QStore("SELECT `id`, `map`, `x`, `y`, `range`, `respawntime`, `limit`, `tacticalpoints`, `moblist`,`daynight`,`isactive`  FROM `list_mobgroups_special`");
  if (result == NULL) return false;
  while (row = mysql_fetch_row(result))
  {

    //LMA: Active spawn?
    int is_active=atoi(row[10]);
    if(is_active==0)
        continue;

    CMobGroup* thisgroup = new (nothrow) CMobGroup;
    if (thisgroup == NULL)
    {
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

    //LMA: Day and night (for Halloween) 0=day and night, 1=day, 2=night
    thisgroup->daynight=atoi(row[9]);

    thisgroup->lastRespawnTime = clock();
    thisgroup->active = 0;
    thisgroup->basicKills = 0;
    thisgroup->curTac = 0;
    thisgroup->curBasic = 0;


    thisgroup->basicMobs.clear();
    thisgroup->tacMobs.clear();

    //LMA: resetting the error flag
    flag=true;

    // Fill in basic/tac mobs
    tmp = strtok(mobList, ",|");
    while (tmp != NULL)
    {

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

      //LMA: We check here and delete the whole group.
      if (thismob->thisnpc == NULL)
      {
        Log(MSG_WARNING, "Group %i:: Invalid monster %i",thisgroup->id,thismob->mobId);
        flag=false;
        break;
      }

    //LMA: shouldn't be PY'drop used in those ones?
      thismob->mapdrop=NULL;
      thismob->mobdrop=NULL;

    /*
    //Org code
      thismob->mapdrop = GetDropData( thisgroup->map );
      thismob->mobdrop= GetDropData( thismob->thisnpc->dropid );
      */

      if (thismob->tactical)
        thisgroup->tacMobs.push_back(thismob);
      else
        thisgroup->basicMobs.push_back(thismob);
      tmp = strtok(NULL, ",|");
     }

        if (!flag)
        {
          delete thisgroup;
          continue;
        }

        MapList.Index[thisgroup->map]->MobGroupList.push_back(thisgroup);
        //mobGroups.push_back(thisgroup);
    }

    DB->QFree( );


    return true;
}


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
            if (thisspawn->map>=MapList.max)
            {
               Log(MSG_WARNING,"Spawn, index overflow trapped %i>%i (increase MAX_MAP_DATA)",thisspawn->map,MapList.max);
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
	NpcNameList.clear();

    //LMA: Pegasus
    MYSQL_RES *result=NULL;
    if(Config.is_pegasus==1)
    {
        result = DB->QStore("SELECT type,map,dir,x,y,dialogid,eventid,tempdialogid,name FROM list_npcs_p");
    }
    else
    {
        result = DB->QStore("SELECT type,map,dir,x,y,dialogid,eventid,tempdialogid,name FROM list_npcs");
    }

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

        NpcNameList[thisnpc->npctype]=strdup(row[8]);    //LMA: NPC Name list.

        thisnpc->thisnpc->dialogid = atoi(row[5]); //This is global to NPC type (original dialog)
        //thisnpc->dialog=thisnpc->thisnpc->dialogid;
        //thisnpc->event=thisnpc->thisnpc->eventid; //LMA Event.
        thisnpc->event=atoi(row[6]);                //LMA Event.
        thisnpc->thisnpc->eventid=thisnpc->event;            //LMA Event (left for compatibility).
        ObjVar[thisnpc->npctype][0]=thisnpc->thisnpc->eventid;  //LMA: eventid for AIP / QSD.

        thisnpc->dialog=atoi(row[7]);               //LMA tempdialog ID, used for events for example

        //LMA: check if out of memory.
        if (thisnpc->posMap>=MapList.max)
        {
           Log(MSG_WARNING,"NPC, index overflow trapped %i>%i (increase MAX_MAP_DATA)",thisnpc->posMap,MapList.max);
           delete thisnpc;
           continue;
        }

        thisnpc->lastAiUpdate=clock();
		MapList.Index[thisnpc->posMap]->AddNPC( thisnpc );
	}
	DB->QFree( );
	Log( MSG_LOAD, "NPC spawn Data loaded" );
	return true;
}


//LMA: Special NPCs (Events or whatever...)
bool CWorldServer::LoadNPCsSpecial( )
{
    Log( MSG_LOAD, "NPC Special spawn           " );
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT type,map,dir,x,y,dialogid,eventid,tempdialogid,name,isactive FROM list_npcs_special");
    if(result==NULL) return false;
    while(row = mysql_fetch_row(result))
    {
        //LMA: Active NPC?
        int is_active=atoi(row[9]);
        if(is_active==0)
            continue;

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

        NpcNameList[thisnpc->npctype]=strdup(row[8]);    //LMA: NPC Name list.

        thisnpc->thisnpc->dialogid = atoi(row[5]); //This is global to NPC type (original dialog)
        //thisnpc->dialog=thisnpc->thisnpc->dialogid;
        //thisnpc->event=thisnpc->thisnpc->eventid; //LMA Event.
        thisnpc->event=atoi(row[6]);                //LMA Event.
        thisnpc->thisnpc->eventid=thisnpc->event;            //LMA Event (left for compatibility).
        thisnpc->dialog=atoi(row[7]);               //LMA tempdialog ID, used for events for example

        //LMA: check if out of memory.
        if (thisnpc->posMap>=MapList.max)
        {
           Log(MSG_WARNING,"NPC, index overflow trapped %i>%i (increase MAX_MAP_DATA)",thisnpc->posMap,MapList.max);
           delete thisnpc;
           continue;
        }

        thisnpc->lastAiUpdate=clock();
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


	return true;
}

bool CWorldServer::LoadUpgrade( )
{

    Log( MSG_LOAD, "Refine Data - STB      " );
    for (UINT i = 0; i<upgradeData.rowcount; i++) {
        // weapons
        if (upgradeData.rows[i][0] != 0)
        {
            upgrade[0][upgradeData.rows[i][0]] = upgradeData.rows[i][1];
        }

        // gear
        if (upgradeData.rows[i][2] != 0)
        {
            upgrade[1][upgradeData.rows[i][2]] = upgradeData.rows[i][3];
        }
    }

    STBFreeData(&upgradeData);

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
    //STB version
    Log( MSG_LOAD, "Equip Data - STB         " );
    for(int j=0;j<9;j++)
    {
        for(unsigned int i=0;i<STB_ITEM[j].rowcount;i++)
        {
            CEquip* newequip = new (nothrow) CEquip;
            if(newequip==NULL)
            {
                Log(MSG_WARNING, "\nError allocing memory: equip" );
                return false;
            }

            newequip->id = i;
            newequip->equiptype = (j+1);
            newequip->type = STB_ITEM[j].rows[i][4];
            newequip->price = STB_ITEM[j].rows[i][5];
            newequip->pricerate = STB_ITEM[j].rows[i][6];
            newequip->weight = STB_ITEM[j].rows[i][7];
            newequip->quality = STB_ITEM[j].rows[i][8];
            newequip->level = STB_ITEM[j].rows[i][13];
            newequip->material = STB_ITEM[j].rows[i][14];
            newequip->defense = STB_ITEM[j].rows[i][31];
            newequip->magicresistence = STB_ITEM[j].rows[i][32];
            newequip->attackdistance = STB_ITEM[j].rows[i][33];//Speed of travel/Range

            if(newequip->equiptype==SHOE)
            {
                newequip->movespeed = newequip->attackdistance;
            }
            else
            {
                newequip->movespeed = 0;
            }

            //All files from itemtype 1 to 10 are loaded here, it's a test for weapons I guess.
            if (STB_ITEM[j].fieldcount>35)
            {
                newequip->attackpower = STB_ITEM[j].rows[i][35];
                newequip->attackspeed = STB_ITEM[j].rows[i][36];
                //LMA: magicattack not handled !!
                /*
                newequip->magicattack = STB_ITEM[j].rows[i][37];      //new. Staffs and wands are designated as magic weapons.
                if(newequip->magicattack > 1)newequip->magicattack = 0; //all the blue named spears have weird numbers here. Maybe why NA had a massive damage glitch with them.
                */
            }
            else
            {
                newequip->attackpower = 0;
                newequip->attackspeed = 0;
                //LMA: magicattack not handled !!
                //newequip->magicattack = 0;
            }

            //job1 to job3
            for(int k=0;k<3;k++)
                newequip->occupation[k] = STB_ITEM[j].rows[i][(16+k)];
            for(int k=0;k<2;k++)
                newequip->condition1[k] = STB_ITEM[j].rows[i][(19+k)];
            for(int k=0;k<2;k++)
                newequip->condition2[k] = STB_ITEM[j].rows[i][(21+k)];
            for(int k=0;k<2;k++)
                newequip->stat1[k] = STB_ITEM[j].rows[i][(24+k)];
            for(int k=0;k<2;k++)
                newequip->stat2[k] = STB_ITEM[j].rows[i][(27+k)];
            newequip->itemgrade = STB_ITEM[j].rows[i][46];

            //LMA: raretype not handled !!
            //newequip->raretype = STB_ITEM[j].rows[i][47];
            //EquipList[newequip->equiptype].Data.push_back( newequip );
            EquipList[newequip->equiptype].Index[newequip->id] = newequip; // Index to read more quickly the data
        }
    }

    Log( MSG_LOAD, "Equip Data loaded" );


    return true;
}

bool CWorldServer::LoadJemItem( )
{
    Log( MSG_LOAD, "Jem Data - STB        " );
    for(unsigned int i=0;i<STB_ITEM[10].rowcount;i++)
    {
        CJemData* thisjem = new (nothrow) CJemData;
        if(thisjem==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: jemitem" );
            continue;
        }
        thisjem->id = i;
        thisjem->type = STB_ITEM[10].rows[i][4];
        thisjem->price = STB_ITEM[10].rows[i][5];
        thisjem->pricerate = STB_ITEM[10].rows[i][6];
        thisjem->weight = STB_ITEM[10].rows[i][7];
        thisjem->quality = STB_ITEM[10].rows[i][8];
        thisjem->material = STB_ITEM[10].rows[i][14];
        thisjem->stat1[0] = STB_ITEM[10].rows[i][16];
        thisjem->stat1[1] = STB_ITEM[10].rows[i][17];
        thisjem->stat2[0] = STB_ITEM[10].rows[i][18];
        thisjem->stat2[1] = STB_ITEM[10].rows[i][19];
        //JemList.Data.push_back( thisjem );
        JemList.Index[thisjem->id] = thisjem;

        //LMA: testing maps :) Don't need to test keys since it's ++
        //JemList.DataMap[i]=thisjem;
    }
    Log( MSG_LOAD, "Jem Data loaded" );
    return true;
}

bool CWorldServer::LoadNaturalItem( )
{
    Log( MSG_LOAD, "Natural Data - STB        " );
    for(unsigned int i=0;i<STB_ITEM[11].rowcount;i++)
    {
        CNaturalData* thisnatural = new (nothrow) CNaturalData;
        if(thisnatural==NULL)
        {
            Log(MSG_WARNING, "\nError allocing memory: natural" );
            return false;
        }
        thisnatural->id = i;
        thisnatural->type = STB_ITEM[11].rows[i][4];
        thisnatural->price = STB_ITEM[11].rows[i][5];
        thisnatural->pricerate = STB_ITEM[11].rows[i][6];
        thisnatural->weight = STB_ITEM[11].rows[i][7];
        thisnatural->quality = STB_ITEM[11].rows[i][8];
        thisnatural->pricevalue = STB_ITEM[11].rows[i][16];
        //NaturalList.Data.push_back( thisnatural );
        NaturalList.Index[thisnatural->id] = thisnatural;
    }

    Log( MSG_LOAD, "Natural Data loaded" );
    return true;
}

bool CWorldServer::LoadPatItem( )
{
    Log( MSG_LOAD, "PAT Data - STB         " );
    for(unsigned int i=0;i<STB_ITEM[13].rowcount;i++)
    {
        CPatData* newpat = new (nothrow) CPatData;
        if(newpat==NULL)
        {
            Log(MSG_WARNING, "Error allocing memory: pat\n" );
            return false;
        }
        newpat->id = i;
        newpat->type = STB_ITEM[13].rows[i][4];
        newpat->price = STB_ITEM[13].rows[i][5];
        newpat->pricerate = STB_ITEM[13].rows[i][6];
        newpat->weight = STB_ITEM[13].rows[i][7];
        newpat->quality = STB_ITEM[13].rows[i][8];
        newpat->material = STB_ITEM[13].rows[i][14];
        newpat->partversion = STB_ITEM[13].rows[i][17];
        //newpat->level = STB_ITEM[13].rows[i][22];             // extra field added rev 70
        //newpat->condition[1] = STB_ITEM[13].rows[i][24];      // extra field added rev 70
        //newpat->modifier[1] = STB_ITEM[13].rows[i][25];       // extra field added rev 70
        //newpat->condition[2] = STB_ITEM[13].rows[i][27];      // extra field added rev 70
        //newpat->modifier[2] = STB_ITEM[13].rows[i][28];       // extra field added rev 70
        newpat->modifier = STB_ITEM[13].rows[i][25];       // extra field added rev 70
        newpat->maxfuel = STB_ITEM[13].rows[i][31];
        newpat->fuelcons = STB_ITEM[13].rows[i][32];
        newpat->speed = STB_ITEM[13].rows[i][33];
        newpat->attackdistance = STB_ITEM[13].rows[i][35];
        newpat->attackpower = STB_ITEM[13].rows[i][36];
        newpat->attackspeed = STB_ITEM[13].rows[i][37];
        //PatList.Data.push_back( newpat );
        PatList.Index[newpat->id] = newpat;
    }
    Log( MSG_LOAD, "PAT Data loaded" );
    return true;
}

bool CWorldServer::LoadProductItem( )
{
    Log( MSG_LOAD, "Product Data - STB        " );
    for(unsigned int i=0;i<STB_PRODUCT.rowcount;i++)
    {
        CProductData* newproduct = new (nothrow) CProductData;
        if(newproduct==NULL)
        {
            Log(MSG_WARNING, "Error allocing memory: product\n" );
            return false;
        }
        newproduct->id = i;
        newproduct->item[0]=STB_PRODUCT.rows[i][2];
        newproduct->amount[0]=STB_PRODUCT.rows[i][3];
        newproduct->item[1]=STB_PRODUCT.rows[i][4];
        newproduct->amount[1]=STB_PRODUCT.rows[i][5];
        newproduct->item[2]=STB_PRODUCT.rows[i][6];
        newproduct->amount[2]=STB_PRODUCT.rows[i][7];
        newproduct->item[3]=STB_PRODUCT.rows[i][8];
        newproduct->amount[3]=STB_PRODUCT.rows[i][9];
        //ProductList.Data.push_back( newproduct );
        ProductList.Index[newproduct->id] = newproduct;
    }
    Log( MSG_LOAD, "Product Data loaded" );
    return true;
}

bool CWorldServer::LoadSellData( )
{
    Log( MSG_LOAD, "Sell Data - STB        " );
    for(unsigned int i=0;i<STB_SELL.rowcount;i++)
    {

        CCSellData* newsell = new (nothrow) CCSellData;
        if(newsell==NULL)
        {
            Log(MSG_WARNING, "\nError Allocing memory: sell" );
            return false;
        }
        newsell->id = i;

        for(unsigned int j=2;j<STB_SELL.fieldcount;j++)
        {
            if (j>=50)
            {
                Log(MSG_WARNING,"Loading SELL DATA, Too much Items for %i! %i>48",i,STB_SELL.fieldcount);
                break;
            }

            newsell->item[j-2] = STB_SELL.rows[i][j];
        }
        //SellList.Data.push_back( newsell );
        SellList.Index[newsell->id] = newsell;
    }
    Log( MSG_LOAD, "Sell Data loaded" );
    return true;
}

bool CWorldServer::LoadConsItem( )
{
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
        newuse->material= STB_ITEM[9].rows[i][14];
        newuse->pricevalue = STB_ITEM[9].rows[i][16];
        newuse->usecondition[0]= STB_ITEM[9].rows[i][17];
        newuse->usecondition[1]= STB_ITEM[9].rows[i][18];
        newuse->useeffect[0]= STB_ITEM[9].rows[i][19];
        newuse->useeffect[1]= STB_ITEM[9].rows[i][20];
        newuse->is_mileage=0;

        //LMA: mileage box?
        if(newuse->restriction==6&&newuse->quality==100)
            newuse->is_mileage=1;

        //UseList.Data.push_back( newuse );
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
        if (newzone->id>=MapList.max)
        {
           Log(MSG_WARNING,"zone_data.csv, index overflow trapped %i>%i (increase MAX_MAP_DATA)",newzone->id,MapList.max);
           delete newzone;
           continue;
        }
        //#endif

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
        newzone->MobGroupList.clear();
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
    Log( MSG_LOAD, "Item Stats - STB   " );
    for(unsigned int i=0;i<STB_ITEM[10].rowcount;i++)
    {
        CItemStas* tempstats=new (nothrow) CItemStas;
        StatsList[i]=tempstats;
        StatsList[i]->stat[0] = STB_ITEM[10].rows[i][16];
        StatsList[i]->value[0] = STB_ITEM[10].rows[i][17];
        StatsList[i]->stat[1] = STB_ITEM[10].rows[i][18];
        StatsList[i]->value[1] = STB_ITEM[10].rows[i][19];
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


//LMA: Loading breaks, chests and blue crafts from list_break.stb
bool CWorldServer::LoadBreakChestBlueList()
{
    Log( MSG_LOAD, "Break / Chest / Blue Craft - STB" );
    int nb_craft=0;
    int nb_chest=0;
    int nb_break=0;
    int choice=0;
    UINT itemtype=0;
    UINT itemnum=0;

    for(unsigned int i=0;i<BreakData.rowcount;i++)
    {
        //let's check if we have a break, a chest or a blue craft stuff...
        if(BreakData.rows[i][1]==0)
        {
            continue;
        }

        choice=0;
        itemtype= int(BreakData.rows[i][1]/1000);
        if (itemtype>0&&itemtype<10)
        {
            //break
            choice=1;
            itemnum=BreakData.rows[i][1] % 1000;
        }

        if(choice==0&&itemtype==10)
        {
            //chest.
            choice=2;
            itemnum=BreakData.rows[i][1] % 1000;
        }

        if (choice==0)
        {
            itemtype= int(BreakData.rows[i][1]/100000);
            if (itemtype>1&&itemtype<10)
            {
                //blue craft
                //In fact they are breaks?
                //choice=3;
                choice=1;
                itemnum=BreakData.rows[i][1] % 100000;
            }

        }

        if (choice==0)
        {
            //LMA: who wants to be a milionnaire? ^_^
            itemtype= int(BreakData.rows[i][1]/1000000);
             if (itemtype==10)
            {
                //chest or dispensers
                choice=2;
                itemnum=BreakData.rows[i][1] % 1000000;
            }

        }

        //time to make the right choice :)
        switch (choice)
        {
                case 1:
                {
                    //Break, should be easy.
                    CBreakList* newbreak = new (nothrow) CBreakList;
                    if(newbreak==NULL)
                    {
                        Log(MSG_WARNING, "Error allocing memory: break list\n" );
                        return false;
                    }

                    newbreak->itemnum=itemnum;
                    newbreak->itemtype=itemtype;
                    //We read the 20 items.
                    for(int j=0;j<20;j++)
                    {
                        newbreak->product[j]=BreakData.rows[i][2+j*3];
                        newbreak->amount[j]=BreakData.rows[i][3+j*3];
                        newbreak->prob[j]=BreakData.rows[i][4+j*3];
                    }

                    newbreak->numToGive = BreakData.rows[i][62];
                    newbreak->total = BreakData.rows[i][63];
                    nb_break++;
                    BreakList.push_back( newbreak );
                    //Log(MSG_INFO,"Break added: (%i:%i), numtogive %i, total %i",newbreak->itemtype,newbreak->itemnum,newbreak->numToGive,newbreak->total);
                    break;
                }
                case 2:
                {
                    //chest... Well let's adapt Drakia's code.
                    CChest* newchest = new (nothrow) CChest;
                    if(newchest==NULL)
                    {
                        Log( MSG_WARNING, "Error allocing memory for chest\n" );
                        return false;
                    }

                    //Patch for Xmas gift boxes...
                    newchest->chestid = itemnum;
/*                     if (itemnum>=245&&itemnum<=247)
                    {
                        newchest->chestid+=2;
                    }
*/
                   //We read the 20 items.
                   int nb_rewards=0;
                   UINT rewtype=0;
                   UINT rewnum=0;
                   bool isok=true;
                   newchest->probmax = 0;

                    for(int j=0;j<20;j++)
                    {
                        if (BreakData.rows[i][2+j*3]==0)
                        {
                            //No more rewards to be read.
                            break;
                        }

                        isok=true;
                        rewtype=int(BreakData.rows[i][2+j*3]/1000);
                        rewnum=BreakData.rows[i][2+j*3]%1000;

                        if(rewnum==0||rewtype>14||rewtype==0)
                        {
                            //Log(MSG_WARNING,"Problem getting item from Break STB (line %i): %i error %i::%i",i,BreakData.rows[i][2+j*3],rewtype,rewnum);
                            isok=false;
                        }

                        //other chance (halloween candle ghost, itemnum>1000)
                        if(!isok)
                        {
                            isok=true;
                            rewtype=int(BreakData.rows[i][2+j*3]/1000000);
                            rewnum=BreakData.rows[i][2+j*3]%1000000;

                            if(rewnum==0||rewtype>14||rewtype==0)
                            {
                                Log(MSG_WARNING,"Problem getting item from Break STB (line %i): %i",i,BreakData.rows[i][2+j*3]);
                                isok=false;
                            }
                            else
                            {
                                //Log(MSG_WARNING,"Item from Break STB retrieved (line %i): %i item (%i::%i)",i,BreakData.rows[i][2+j*3],rewtype,rewnum);
                            }

                        }

                        if(!isok)
                        {
                            continue;
                        }

                        nb_rewards++;
                        CReward* Reward = new (nothrow) CReward;
                        if(Reward==NULL)
                        {
                            Log(MSG_WARNING, "Error allocing memory Reward" );
                            return false;
                        }

                        Reward->id = rewnum;
                        Reward->type=rewtype;
                        Reward->rewardamount=BreakData.rows[i][3+j*3];
                        Reward->prob=BreakData.rows[i][4+j*3];
                        newchest->probmax+=BreakData.rows[i][4+j*3];
                        newchest->Rewards.push_back( Reward );
                    }

                    newchest->rewardposs = BreakData.rows[i][62];
                    nb_chest++;
                    ChestList.push_back( newchest );
                    //Log(MSG_INFO,"Chest added: (%i:%i), numtogive %i",10,newchest->chestid,newchest->rewardposs);
                    break;
                }
                case 3:
                {
                    //blue craft... Not yet handled...
                    //ChestList.push_back( newbreak );
                    nb_craft++;
                    break;
                }
                case 0:
                {
                    Log(MSG_WARNING,"Can't interpret itemid %i in list_break.stb",BreakData.rows[i][1]);
                    break;
                }

        }


    }

    Log(MSG_INFO,"We parsed %i Breaks, %i chests, %i blue craft",nb_break,nb_chest,nb_craft);
    Log( MSG_LOAD, "Break / Chest / Blue Craft - STB - Done" );


    return true;
}

// From osprose

bool CWorldServer::LoadConfig( )
{
    Log( MSG_INFO, "Loading database config" );
    MYSQL_ROW row;
    MYSQL_RES *result = DB->QStore("SELECT exp_rate, drop_rate, zuly_rate, blue_chance, stat_chance, slot_chance, \
        refine_chance, rare_refine, kill_on_fail, player_damage, monster_damage, player_acc, monster_acc, \
        pvp_acc, skill_damage, maxlevel, drop_type, savetime, partygap, maxstat, cfmode, autosave, mapdelay, \
        visualdelay, worlddelay, fairymode, fairystay, fairywait, fairytestmode, osrosever, testgrid, jrose, \
        is_pegasus, monmax FROM list_config");

    if(result==NULL)
    {
        DB->QFree( );
        return false;
    }
    if (mysql_num_rows(result) == 0)
    {
        DB->QFree( );
        return false;
    }

    while( row = mysql_fetch_row(result) )
    {
       GServer->Config.EXP_RATE = atoi(row[0]);
       GServer->Config.DROP_RATE = atoi(row[1]);
       GServer->Config.ZULY_RATE = atoi(row[2]);
       GServer->Config.BlueChance = atoi(row[3]);
       GServer->Config.StatChance = atoi(row[4]);
       GServer->Config.SlotChance = atoi(row[5]);
       GServer->Config.RefineChance = atoi(row[6]);
       GServer->Config.Rare_Refine = atoi(row[7]);
       GServer->Config.KillOnFail = atoi(row[8]);
       GServer->Config.PlayerDmg = atoi(row[9]);
       GServer->Config.MonsterDmg = atoi(row[10]);
       // Not implemented in server yet - Drakia
       //GServer->Config.PlayerAcc = atoi(row[11]);
       //GServer->Config.MonsterAcc = atoi(row[12]);
       //GServer->Config.PvpAcc = atoi(row[13]);
       //GServer->Config.SkillDmg = atoi(row[14]);
        // new update - from PurpleYouko
       GServer->Config.MaxLevel = atoi(row[15]);
       GServer->Config.DROP_TYPE = atoi(row[16]);
       GServer->Config.SAVETIME = atoi(row[17]);
       GServer->Config.Partygap = atoi(row[18]);
       GServer->Config.MaxStat = atoi(row[19]);
       GServer->Config.Cfmode = atoi(row[20]);
        // added to remove from worldserver.conf
        //need to remove old from worldserver.cpp
       GServer->Config.AutoSave = atoi(row[21]);
       //LMA: in osRose we are using: AUTOSAVE...
       GServer->Config.AUTOSAVE = atoi(row[21]);
       GServer->Config.MapDelay = atoi(row[22]);
       GServer->Config.VisualDelay = atoi(row[23]);
       GServer->Config.WorldDelay = atoi(row[24]);
       GServer->Config.FairyMode = atoi(row[25]);
       GServer->Config.FairyStay = atoi(row[26]);
       GServer->Config.FairyWait = atoi(row[27]);
       GServer->Config.FairyTestMode = atoi(row[28]);
       GServer->Config.osRoseVer = strdup(row[29]);
       GServer->Config.testgrid = atoi(row[30]);
       GServer->Config.jrose = atoi(row[31]);
       GServer->Config.is_pegasus = atoi(row[32]);
       GServer->Config.monmax = atoi(row[33]);
    }

    //LMA: jRose.
    if(Config.jrose==1)
       Log (MSG_INFO, "Handling ONLY jRose client.");
    else
       Log (MSG_INFO, "Handling ONLY RoseNA client.");

    //LMA: Pegasus
    if(Config.is_pegasus==1)
       Log (MSG_INFO, "Handling Pegasus STB, AIP, QSD, database.");
    else
       Log (MSG_INFO, "Handling naRose STB, AIP, QSD, database.");

    DB->QFree( );
    Log( MSG_INFO, "Config Data Loaded" );


    return true;
}
