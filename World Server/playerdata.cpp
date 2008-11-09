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
#include "player.h"
#include "worldserver.h"


// Load this characters userdata from the database
bool CPlayer::loaddata( )
{
	MYSQL_ROW row;
	MYSQL_RES *result = GServer->DB->QStore("SELECT level,face,hairStyle,sex,classid,zuly,str,dex,_int, con,cha,sen,curHp,curMp,id,statp,skillp,exp,stamina,quickbar,basic_skills, class_skills,class_skills_level,respawnid,clanid,clan_rank,townid,rewardpoints,unionid,unionfame,union01,union02,union03,union04,union05,bonusxp,timerxp,shoptype,timershop,isGM,unique_skills,mileage_skills,driving_skills,unique_skills_level,mileage_skills_level FROM characters WHERE char_name='%s'", CharInfo->charname);
	if(result==NULL) return false;
	if(mysql_num_rows(result)!=1)
	{
        Log( MSG_WARNING, "Number of user with charname '%s' is %i", CharInfo->charname,mysql_num_rows(result));
        return false;
    }
	row = mysql_fetch_row(result);
    last_map=-1;	//LMA: maps
    last_coords=-1;	//LMA: maps
	Stats->Level = atoi(row[0]);
	CharInfo->Face = atoi(row[1]);
	CharInfo->Hair = atoi(row[2]);
	CharInfo->Sex = atoi(row[3]);
	CharInfo->Job = atoi(row[4]);
	CharInfo->Zulies = atol(row[5]);
	Attr->Str = atoi(row[6]);
	Attr->Dex = atoi(row[7]);
	Attr->Int = atoi(row[8]);
	Attr->Con = atoi(row[9]);
	Attr->Cha = atoi(row[10]);
	Attr->Sen = atoi(row[11]);
	Stats->HP = atoi(row[12]);
	Stats->MP = atoi(row[13]);
	CharInfo->charid = atoi(row[14]);
	CharInfo->StatPoints = atoi(row[15]);
	CharInfo->SkillPoints = atoi(row[16]);
	CharInfo->Exp = atoi(row[17]);
	CharInfo->stamina = atoi(row[18]);
	CharInfo->MaxStamina = 5000;
    Position->respawn = atoi(row[23]);
    Clan->clanid = atoi(row[24]);
    Clan->clanrank = atoi(row[25]);
    Position->saved = atoi(row[26]);
    CharInfo->rewardpoints=atoi(row[27]); //LMA: reward points.
    //Union
    CharInfo->unionid=atoi(row[28]);
    CharInfo->unionfame=atoi(row[29]);
    CharInfo->union01=atoi(row[30]);
    CharInfo->union02=atoi(row[31]);
    CharInfo->union03=atoi(row[32]);
    CharInfo->union04=atoi(row[33]);
    CharInfo->union05=atoi(row[34]);

    //LMA: mileage stuff
    bonusxp=atoi(row[35]);
    timerxp=atoi(row[36]);
    wait_validation=0;
    last_fuel=0;

    Shop->ShopType=atoi(row[37]);
    Shop->mil_shop_time=atoi(row[38]);

    //GM Additional Security by PurpleYouKo
    CharInfo->isGM=atoi(row[39]);   // GM Security

    //resetting some values:
    sp_hp=0;
    sp_mp=0;
    nb_hp=0;
    nb_mp=0;

    //TEST
    time_t rawtime;
    struct tm * timeinfo;
    rawtime=Shop->mil_shop_time;
    timeinfo = localtime ( &rawtime );
    Log(MSG_INFO,"Shop %i/%i/%i, %i:%i:%i",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour+1,timeinfo->tm_min+1,timeinfo->tm_sec+1);
    rawtime=timerxp;
    timeinfo = localtime ( &rawtime );
    Log(MSG_INFO,"Bonus Xp %i/%i/%i, %i:%i:%i",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour+1,timeinfo->tm_min+1,timeinfo->tm_sec+1);
    //End of test

    time_t etime=time(NULL);
    if(bonusxp<=0)
         bonusxp=1;

    if(bonusxp>1&&(etime>=timerxp))
    {
      bonusxp=1;
      timerxp=0;
    }

    if (Shop->ShopType>0&&(etime>=Shop->mil_shop_time))
    {
     Shop->ShopType=0;
     Shop->mil_shop_time=0;
    }

	p_skills = 0;
	for(BYTE i=0;i<48;i++)
    {
        char* tmp=strtok((i==0?row[19]:NULL), ",");
        if (tmp!=NULL)
            quickbar[i]=atoi(tmp);
        else
            quickbar[i]=0;
    }

    //LMA: Old way:
    /*
	for(UINT i=0;i<42;i++)
    {
        char* tmp=strtok((i==0?row[20]:NULL), ",");
        if (tmp!=NULL)
            bskills[i]=atoi(tmp);
        else
            bskills[i]=0;
    }
	for(UINT i=0;i<60;i++)
	{
        char* tmp=strtok((i==0?row[21]:NULL), ",");
        if (tmp!=NULL)
        {
            if(atoi(tmp)!=0)
                p_skills++;
            cskills[i].id=atoi(tmp);
        }
        else
            cskills[i].id=0;
    }
	for(UINT i=0;i<60;i++)
    {
        char* tmp=strtok((i==0?row[22]:NULL), ",");
        if (tmp!=NULL)
            cskills[i].level=atoi(tmp);
        else
            cskills[i].level=1;
    }
    for(int i=0;i<60;i++)
    {
        if(cskills[i].id==0)
        {
            cskills[i].thisskill = NULL;
        }
        else
        {
            cskills[i].thisskill = GServer->GetSkillByID( cskills[i].id+cskills[i].level-1 );
        }
    }
    */

    //LMA: new way BEGIN
    bool do_save=false;
    int cur_cskills[5];
    int max_skills[5];
    int coff[MAX_CLASS_SKILL];
    int uoff[MAX_UNIQUE_SKILL];
    int moff[MAX_MILEAGE_SKILL];
    char* tab_names[]={"class","driving","basic","unique","mileage"};

    int good_family=0;
    cur_cskills[0]=0;
    cur_cskills[1]=60;
    cur_cskills[2]=320;
    cur_cskills[3]=90;
    cur_cskills[4]=120;

    max_skills[0]=60;
    max_skills[1]=90;
    max_skills[2]=362;
    max_skills[3]=120;
    max_skills[4]=320;

    //Browsing supposed basic skills.
    good_family=2;
	for(UINT i=0;i<MAX_BASIC_SKILL;i++)
    {
        char* tmp=strtok((i==0?row[20]:NULL), ",");
        if (tmp==NULL)
            continue;

        int temp=atoi(tmp);
        if (temp==0)
            continue;
        int indexfamily=GoodSkill(temp);
        if (indexfamily==-1)
        {
            Log(MSG_WARNING,"Incorrect skill detected %i",temp);
            do_save=true;
            continue;
        }

        if (indexfamily!=good_family)
        {
            Log(MSG_WARNING,"Skill %i should be in family %s instead of family %s",temp,tab_names[indexfamily],tab_names[good_family]);
            do_save=true;
        }

        if(cur_cskills[indexfamily]>=max_skills[indexfamily])
        {
            Log(MSG_WARNING,"Already too much skills in family %s, no room for skill %i",tab_names[indexfamily],temp);
            do_save=true;
            continue;
        }

        cskills[cur_cskills[indexfamily]].id=temp;
        cskills[cur_cskills[indexfamily]].level=1;
        cur_cskills[indexfamily]++;
    }

    //Browsing unique skills.
    good_family=1;
	for(UINT i=0;i<MAX_DRIVING_SKILL;i++)
    {
        char* tmp=strtok((i==0?row[42]:NULL), ",");
        if (tmp==NULL)
            continue;

        int temp=atoi(tmp);
        if (temp==0)
            continue;
        int indexfamily=GoodSkill(temp);
        if (indexfamily==-1)
        {
            Log(MSG_WARNING,"Incorrect skill detected %i",temp);
            do_save=true;
            continue;
        }

        if (indexfamily!=good_family)
        {
            Log(MSG_WARNING,"Skill %i should be in family %s instead of family %s",temp,tab_names[indexfamily],tab_names[good_family]);
            do_save=true;
        }

        if(cur_cskills[indexfamily]>=max_skills[indexfamily])
        {
            Log(MSG_WARNING,"Already too much skills in family %s, no room for skill %i",tab_names[indexfamily],temp);
            do_save=true;
            continue;
        }

        cskills[cur_cskills[indexfamily]].id=temp;
        cskills[cur_cskills[indexfamily]].level=1;
        cur_cskills[indexfamily]++;
    }

    //unique skills.
    good_family=3;
	for(UINT i=0;i<MAX_UNIQUE_SKILL;i++)
    {
        uoff[i]=-1;
        char* tmp=strtok((i==0?row[40]:NULL), ",");
        if (tmp==NULL)
            continue;

        int temp=atoi(tmp);
        if (temp==0)
            continue;
        int indexfamily=GoodSkill(temp);
        if (indexfamily==-1)
        {
            Log(MSG_WARNING,"Incorrect skill detected %i",temp);
            do_save=true;
            continue;
        }

        if (indexfamily!=good_family)
        {
            Log(MSG_WARNING,"Skill %i should be in family %s instead of family %s",temp,tab_names[indexfamily],tab_names[good_family]);
            do_save=true;
        }

        if(cur_cskills[indexfamily]>=max_skills[indexfamily])
        {
            Log(MSG_WARNING,"Already too much skills in family %s, no room for skill %i",tab_names[indexfamily],temp);
            do_save=true;
            continue;
        }

        cskills[cur_cskills[indexfamily]].id=temp;
        cskills[cur_cskills[indexfamily]].level=1;
        uoff[i]=cur_cskills[indexfamily];
        cur_cskills[indexfamily]++;
    }

    //mileage skills.
    good_family=4;
	for(UINT i=0;i<MAX_MILEAGE_SKILL;i++)
    {
        moff[i]=-1;
        char* tmp=strtok((i==0?row[41]:NULL), ",");
        if (tmp==NULL)
            continue;

        int temp=atoi(tmp);
        if (temp==0)
            continue;
        int indexfamily=GoodSkill(temp);
        if (indexfamily==-1)
        {
            Log(MSG_WARNING,"Incorrect skill detected %i",temp);
            do_save=true;
            continue;
        }

        if (indexfamily!=good_family)
        {
            Log(MSG_WARNING,"Skill %i should be in family %s instead of family %s",temp,tab_names[indexfamily],tab_names[good_family]);
            do_save=true;
        }

        if(cur_cskills[indexfamily]>=max_skills[indexfamily])
        {
            Log(MSG_WARNING,"Already too much skills in family %s, no room for skill %i",tab_names[indexfamily],temp);
            do_save=true;
            continue;
        }

        cskills[cur_cskills[indexfamily]].id=temp;
        cskills[cur_cskills[indexfamily]].level=1;
        moff[i]=cur_cskills[indexfamily];
        cur_cskills[indexfamily]++;
    }

    //class skills.
    good_family=0;
	for(UINT i=0;i<MAX_CLASS_SKILL;i++)
    {
        coff[i]=-1;
        char* tmp=strtok((i==0?row[21]:NULL), ",");
        if (tmp==NULL)
            continue;

        int temp=atoi(tmp);
        if (temp==0)
            continue;
        int indexfamily=GoodSkill(temp);
        if (indexfamily==-1)
        {
            Log(MSG_WARNING,"Incorrect skill detected %i",temp);
            do_save=true;
            continue;
        }

        if (indexfamily!=good_family)
        {
            Log(MSG_WARNING,"Skill %i should be in family %s instead of family %s",temp,tab_names[indexfamily],tab_names[good_family]);
            do_save=true;
        }

        if(cur_cskills[indexfamily]>=max_skills[indexfamily])
        {
            Log(MSG_WARNING,"Already too much skills in family %s, no room for skill %i",tab_names[indexfamily],temp);
            do_save=true;
            continue;
        }

        cskills[cur_cskills[indexfamily]].id=temp;
        cskills[cur_cskills[indexfamily]].level=1;
        coff[i]=cur_cskills[indexfamily];
        cur_cskills[indexfamily]++;
    }

    //getting class levels now.
	for(UINT i=0;i<MAX_CLASS_SKILL;i++)
    {
        char* tmp=strtok((i==0?row[22]:NULL), ",");
        int temp=1;
        if (tmp!=NULL)
            temp=atoi(tmp);

        if (coff[i]==-1)
            continue;
        if (temp==0)
            temp=1;
        cskills[coff[i]].level=temp;

        if(cskills[coff[i]].id!=0)
            cskills[coff[i]].thisskill = GServer->GetSkillByID( cskills[coff[i]].id+cskills[coff[i]].level-1 );
    }

    //unique skills levels.
	for(UINT i=0;i<MAX_UNIQUE_SKILL;i++)
    {
        char* tmp=strtok((i==0?row[43]:NULL), ",");
        int temp=1;
        if (tmp!=NULL)
            temp=atoi(tmp);

        if (uoff[i]==-1)
            continue;
        if (temp==0)
            temp=1;
        cskills[uoff[i]].level=temp;

        if(cskills[uoff[i]].id!=0)
            cskills[uoff[i]].thisskill = GServer->GetSkillByID( cskills[uoff[i]].id+cskills[uoff[i]].level-1 );
    }

    //mileage skills levels.
	for(UINT i=0;i<MAX_MILEAGE_SKILL;i++)
    {
        char* tmp=strtok((i==0?row[43]:NULL), ",");
        int temp=1;
        if (tmp!=NULL)
            temp=atoi(tmp);

        if (moff[i]==-1)
            continue;
        if (temp==0)
            temp=1;
        cskills[moff[i]].level=temp;

        if(cskills[moff[i]].id!=0)
            cskills[moff[i]].thisskill = GServer->GetSkillByID( cskills[moff[i]].id+cskills[moff[i]].level-1 );
    }

    //First free offset.
    for (int i=0;i<5;i++)
        cur_max_skills[i]=cur_cskills[i];

    //reconstructing all the skills again...
    //Not needed...
    /*
    //driving skills.
    int cpt=0;
    for (int i=60;i<MAX_DRIVING_SKILL;i++)
    {
        dskills[cpt]=cskills[i].id;
        cskills[i].thisskill=NULL;
        if(dskills[cpt]!=0)
            cur_max_skills[1]++;
        cpt++;
    }

    //basic
    cpt=0;
    for (int i=320;i<MAX_BASICSKILL;i++)
    {
        bskills[cpt]=cskills[i].id;
        cskills[i].thisskill=NULL;
        if(bskills[cpt]!=0)
            cur_max_skills[2]++;
        cpt++;
    }

    //unique.
    cpt=0;
    for (int i=90;i<MAX_UNIQUE_SKILL;i++)
    {
        uskills[cpt].id=cskills[i].id;
        uskills[cpt].level=cskills[i].level;
        cskills[i].thisskill=NULL;
        if(cskills[i].id!=0)
        {
            cur_max_skills[3]++;
            cskills[i].thisskill = GServer->GetSkillByID( cskills[i].id+cskills[i].level-1 );
        }

    }

    //mileage.
    cpt=0;
    for (int i=120;i<MAX_MILEAGE_SKILL;i++)
    {
        mskills[cpt].id=cskills[i].id;
        mskills[cpt].level=cskills[i].level;
        cskills[i].thisskill=NULL;
        if(cskills[i].id!=0)
        {
            cur_max_skills[4]++;
            cskills[i].thisskill = GServer->GetSkillByID( cskills[i].id+cskills[i].level-1 );
        }

    }

    //class skills.
    cpt=0;
    for (int i=0;i<MAX_SKILL;i++)
    {
        cskills[i].thisskill=NULL;
        if(cskills[i].id!=0)
        {
            cur_max_skills[0]++;
            cskills[i].thisskill = GServer->GetSkillByID( cskills[i].id+cskills[i].level-1 );
        }

    }
    */
    //LMA: new way END


    //LMA: reset inventory.
    for(int i=0;i<MAX_INVENTORY;i++)
    {
        items[i].sig_data=-1;
        items[i].sig_head=-1;
        items[i].sig_gem=-1;
        items[i].sp_value=0;
        items[i].last_sp_value=0;
    }

	GServer->DB->QFree( );

	//LMA: Saving Skills if needed.
    if (do_save)
        saveskills();

	result = GServer->DB->QStore("SELECT itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem,sp_value FROM items WHERE owner=%i", CharInfo->charid);
    if(result==NULL) return false;
	while(row = mysql_fetch_row(result))
    {
        if(!GServer->IsValidItem( atoi(row[1]), atoi(row[0]) ) || atoi(row[6])==0)
        {
            Log(MSG_WARNING, "char %s have a invalid or empty item in inventory: %i-%i [%i], this item will be deleted", CharInfo->charname, atoi(row[1]), atoi(row[0]), atoi(row[6]) );
            continue;
        }
		UINT itemnum = atoi(row[5]);
		items[itemnum].itemnum = atoi(row[0]);
		items[itemnum].itemtype = atoi(row[1]);
		items[itemnum].refine = atoi(row[2]);
		items[itemnum].durability = atoi(row[3]);
		items[itemnum].lifespan = atoi(row[4]);
		items[itemnum].count = atoi(row[6]);
		items[itemnum].stats = atoi(row[7]);
		items[itemnum].socketed = (atoi(row[8])==1)?true:false;
		items[itemnum].appraised = (atoi(row[9])==1)?true:false;
		items[itemnum].gem = atoi(row[10])>3999?0:atoi(row[10]);
		items[itemnum].sp_value = atoi(row[11]);
		CalculateSignature(itemnum);  //Calculate signature.
	}
	GServer->DB->QFree( );
	result = GServer->DB->QStore("SELECT itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem FROM storage WHERE owner=%i", Session->userid);
	if(result==NULL) return false;
	nstorageitems = mysql_num_rows(result);
	while(row = mysql_fetch_row(result))
    {
        if(!GServer->IsValidItem( atoi(row[1]), atoi(row[0]) ) || atoi(row[6])==0)
        {
            Log(MSG_WARNING, "char %s have a invalid or empty item in storage: %i%i [%i], this item will be deleted", CharInfo->charname, atoi(row[1]), atoi(row[0]), atoi(row[6]) );
            continue;
        }
		UINT itemnum = atoi(row[5]);
		storageitems[itemnum].itemnum = atoi(row[0]);
		storageitems[itemnum].itemtype = atoi(row[1]);
		storageitems[itemnum].refine = atoi(row[2]);
		storageitems[itemnum].durability = atoi(row[3]);
		storageitems[itemnum].lifespan = atoi(row[4]);
		storageitems[itemnum].count = atoi(row[6]);
		storageitems[itemnum].stats = atoi(row[7]);
		storageitems[itemnum].socketed = (atoi(row[8])==1)?true:false;
		storageitems[itemnum].appraised = (atoi(row[9])==1)?true:false;
		storageitems[itemnum].gem = atoi(row[10]);
	}
	GServer->DB->QFree( );

	//LMA: Loading ItemMall
    RebuildItemMall();

    if(Clan->clanid!=0)
    {
    	result = GServer->DB->QStore("SELECT logo,back,name,grade FROM list_clan where id=%i", Clan->clanid);
        if(result==NULL) return false;
    	if(mysql_num_rows(result)!=1)
    	{
            Log(MSG_WARNING, "There are %i clan(s) with id %i", mysql_num_rows(result), Clan->clanid );
    	    Clan->clanid=0;
        }
    	else
    	{
    	    row = mysql_fetch_row(result);
    	    Clan->logo = atoi(row[0]);
    	    Clan->back = atoi(row[1]);
    	    strcpy(Clan->clanname,row[2]);
    	    Clan->grade = atoi(row[3]);
        }
    	GServer->DB->QFree( );
    }

    //Quest, QSD version
#ifdef USENEWQUESTSYSTEM
    memset(&quest, 0, sizeof(SQuestData));
    result = GServer->DB->QStore("SELECT quests from list_quest_new where owner=%i",CharInfo->charid );
    if(result!=NULL) //return false;
    {
        while(row = mysql_fetch_row(result))
        {
           if( row[0] != NULL ) memcpy(&quest, row[0], sizeof(SQuestData));
        }
    }
    GServer->DB->QFree( );

#else
    for (int i=0;i<25;i++)
    {
       QuestVariables[i]=0x00;
    }

     //LMA begin
     //20070621-211100
    //Patch for soul crystal quest...
     result = GServer->DB->QStore("SELECT questid, active from list_quest where owner=%i and questid>208 and questid<218",CharInfo->charid );
     if(result!=NULL)
     {
           bool tryteh_done=false;
           bool spero_time=false;

           while(row = mysql_fetch_row(result))
           {
                     switch (atoi(row[0]))
                     {
                            case 209:
                                 {
                                     QuestVariables[1]=0x06;
                                 }
                                break;
                            case 210:
                                 {
                                     QuestVariables[1]=0x07;
                                 }
                                break;
                            case 211:
                                 {
                                     QuestVariables[1]=0x08;
                                 }
                                break;
                            case 215:
                                 {
                                      spero_time=true;
                                  }
                                 break;
                            case 217:
                                 {
                                      tryteh_done=true;
                                  }
                                 break;
                            default:
                                    break;
                     }

           }

           GServer->DB->QFree( );
           if (tryteh_done||(!spero_time))
           {
              QuestVariables[1]=0x00;
           }

     }

    //LMA END

    //LMA BEGIN
    //20060623, 022000
    //Patch for Lunar Quest
    bool is_lunar=false;
    //LMA END

    speaksLuna=false;
    canUseFlyingVessel=false;

    result = GServer->DB->QStore("SELECT questid,nitems,active from list_quest where owner=%i order by active DESC",CharInfo->charid );
    if(result==NULL) return false;
	while(row = mysql_fetch_row(result))
    {
        int questid = atoi(row[0]);

        Log(MSG_INFO,"Adding quest %i for player %i",questid,CharInfo->charid);

        CQuest* thisquest = GServer->GetQuestByID( questid );
        if(thisquest==0)
            continue;

         //LMA BEGIN
        //20060623, 022000
        //Patch for Lunar Quest
        //Log( MSG_INFO, "Reading quest %u",thisquest->id);
        if (thisquest->id==808&&atoi(row[2]))
        {
           Log( MSG_INFO, "Patch Lunar part 1");
           is_lunar=true;
           continue;
        }
        //LMA END


        QUESTS* myquest = new QUESTS;
        assert(myquest);
        myquest->questid = thisquest->questid;
        myquest->thisquest = thisquest;
        for(int i=0;i<5;i++)
        {
            char* tmp = strtok((i==0?row[1]:NULL),"|");
            if(tmp!=NULL)
                myquest->items[i] = atoi(tmp);
            else
                myquest->items[i] = 0;
        }

        //LMA BEGIN
        //20070621-215100
        //Various patches for the quests...
        //Patch for Spero quest
        if (thisquest->id==2000)
        {
           myquest->items[0]=0;
           myquest->items[1]=0;
           if (myquest->items[2]==1)
           {
               myquest->items[0]=1;
           }

            if (myquest->items[2]==2)
           {
               myquest->items[0]=1;
               myquest->items[1]=1;
           }
        }

        //Patch for hunt for pomics
        if (thisquest->id==224||thisquest->id==226)
        {
           myquest->items[0]=0;
           myquest->items[1]=0;
        }

        //Patch for Ikaness
        if (thisquest->id==232)
        {
           myquest->items[0]=1;
        }

        //patch for Rosemary Doll:
        if (thisquest->id==806)
        {
           myquest->items[0]=0;
           if(myquest->items[1]>0)
           {
               myquest->items[0]=1;
           }

        }

         //patch for Sellion's memorantum
        if (thisquest->id==813)
        {
           myquest->items[0]=0;
        }

        //patch for car quest:
        if (thisquest->id==805)
        {
           myquest->items[0]=0;
           myquest->items[1]=0;
           myquest->items[2]=0;
           myquest->items[3]=0;
           UINT nb_papers= (UINT) myquest->items[4];

           if(nb_papers==3)
           {
               myquest->items[0]=1;
               myquest->items[1]=1;
               myquest->items[2]=1;
           }

           if (nb_papers==2)
           {
               myquest->items[0]=1;
               myquest->items[1]=1;
           }

           if (nb_papers==1)
           {
              myquest->items[0]=1;
           }

        }
        //LMA END

        myquest->active = atoi( row[2] );
        if( myquest->active )
            ActiveQuest++;

        //Patch soldier quest lvl 20:
        if (thisquest->id==856||thisquest->id==855)
        {
            myquest->items[0]=0;
            myquest->items[0]=0;
        }

        if (thisquest->id==855&&myquest->active&&myquest->items[0]==40)
        {
           myquest->active=false;
           ActiveQuest--;
           Log(MSG_INFO,"Patch for quest soldier lvl 20 startup");
        }

        //lvl 30 soldier quest
        if (myquest->thisquest->id==858)
        {
           int nb_ok=0;

           if (myquest->items[0]>0)
           {
             nb_ok++;
           }

           if (myquest->items[1]>0)
           {
             nb_ok++;
           }

           if (myquest->items[2]>0)
           {
             nb_ok++;
           }

           if (myquest->items[2]>=22)
           {
             nb_ok++;
           }

           if (myquest->items[1]>=12)
           {
             nb_ok++;
           }

           for (int k=0;k<5;k++)
           {
               myquest->items[k]=0;
           }

           for (int k=0;k<nb_ok;k++)
           {
               myquest->items[k]=1;
           }

        }

         //LMA BEGIN
        //20060623, 022000
        //Patch for Lunar Quest
        if (myquest->thisquest->id==807&&is_lunar)
        {
           Log( MSG_INFO, "Patch Lunar part 2");
           myquest->active = 1;
           ActiveQuest++;
        }
        //LMA END

        //LMA BEGIN
        //20060622, 211500
        //no shadow quests...
        if(myquest->thisquest->id==63&&myquest->active)
        {
           myquest->active=!myquest->active;
           ActiveQuest--;
        }
        //LMA END

        //LMA: Quest of Eucar (Est)
        if (myquest->thisquest->id==2058)
        {
                if (QuestVariables[10]<0x02)
               {
                  QuestVariables[10]=0x01;
               }
        }

        if(myquest->thisquest->id>=2060&&myquest->thisquest->id<=2086)
        {
           myquest->items[1]=0;
        }

        if (myquest->thisquest->id==1055||myquest->thisquest->id==1059||myquest->thisquest->id==1062||myquest->thisquest->id==1064||myquest->thisquest->id==1074||myquest->thisquest->id==239||myquest->thisquest->id==269)
        {
           myquest->items[1]=0;
        }

        if (myquest->thisquest->id==1068)
        {
           myquest->items[2]=0;
        }

        if (myquest->thisquest->id==1057||myquest->thisquest->id==1070)
        {
           int nb_pieces=0;
           nb_pieces=myquest->items[0]+myquest->items[1]+myquest->items[2]+myquest->items[3]+myquest->items[4];

           for (int k=0;k<5;k++)
           {
              if (k<nb_pieces)
              {
                  myquest->items[k]=1;
              }
              else
              {
                  myquest->items[k]=0;
              }

           }

        }

        if (myquest->thisquest->id==2066)
        {
                if (QuestVariables[10]<0x03)
               {
                  QuestVariables[10]=0x02;
               }
        }

        if (myquest->thisquest->id==2071)
        {
                if (QuestVariables[10]<0x04)
               {
                  QuestVariables[10]=0x03;
               }
        }

        if (myquest->thisquest->id==2076)
        {
                if (QuestVariables[10]<0x05)
               {
                  QuestVariables[10]=0x04;
               }
        }

        //LMA: Patch for Flame of Eucar Quest:
        if (myquest->thisquest->id==2079)
        {
                if (QuestVariables[11]<0x02)
               {
                  QuestVariables[11]=0x01;
               }
        }

        if (myquest->thisquest->id==2084)
        {
                if (QuestVariables[11]<0x03)
               {
                  QuestVariables[11]=0x02;
               }
        }

        if (myquest->thisquest->id==2088)
        {
                if (QuestVariables[11]<0x04)
               {
                  QuestVariables[11]=0x03;
               }
        }

        if (myquest->thisquest->id==2092)
        {
                if (QuestVariables[11]<0x05)
               {
                  QuestVariables[11]=0x04;
               }
        }

        //Patch for second jobs quests
        if (myquest->thisquest->id==1051||myquest->thisquest->id==1052||myquest->thisquest->id==1053||myquest->thisquest->id==1054)
        {
                if (QuestVariables[6]<0x02)
               {
                  QuestVariables[6]=0x01;
               }
        }

        //LMA: Main quest
        if (myquest->thisquest->id==201)
        {
           if (myquest->active)
           {
               if (QuestVariables[1]<0x02)
               {
                  QuestVariables[1]=0x01;
               }

           }
           else
           {
               if (QuestVariables[1]<0x03)
               {
                  QuestVariables[1]=0x02;
               }

           }

        }

        /*
         if (myquest->thisquest->id==234&&QuestVariables[1]<0x11)
        {
          QuestVariables[1]=0x10;
        }
         if (myquest->thisquest->id==235&&QuestVariables[1]<0x12)
        {
          QuestVariables[1]=0x11;
        }
         if (myquest->thisquest->id==236&&QuestVariables[1]<0x13)
        {
          QuestVariables[1]=0x12;
        }
         if (myquest->thisquest->id==237&&QuestVariables[1]<0x14)
        {
          QuestVariables[1]=0x13;
        }
         if (myquest->thisquest->id==238&&QuestVariables[1]<0x15)
        {
          QuestVariables[1]=0x14;
        }
         if (myquest->thisquest->id==239&&QuestVariables[1]<0x16)
        {
          QuestVariables[1]=0x15;
        }
         if (myquest->thisquest->id==240&&QuestVariables[1]<0x17)
        {
          QuestVariables[1]=0x16;
        }
         if (myquest->thisquest->id==241&&QuestVariables[1]<0x18)
        {
          QuestVariables[1]=0x17;
        }

         if (myquest->thisquest->id==242&&QuestVariables[1]<0x19)
        {
          QuestVariables[1]=0x18;
        }
        */
         if (myquest->thisquest->id>=234&&myquest->thisquest->id<=246)
        {
          UINT lma_value=0;
          lma_value=16+(myquest->thisquest->id-234);
          if (QuestVariables[1]<(lma_value+1))
          {
           QuestVariables[1]=lma_value;
          }

        }

        //TEST
        if (myquest->thisquest->id==247&&QuestVariables[1]<31)
        {
          QuestVariables[1]=30;
        }
         if (myquest->thisquest->id==248&&QuestVariables[1]<32)
        {
          QuestVariables[1]=31;
        }

        //2do: other values
         if (myquest->thisquest->id==254&&QuestVariables[1]<40)
        {
          QuestVariables[1]=40;
        }
          //2do: other values
         if (myquest->thisquest->id==261&&QuestVariables[1]<51)
        {
          QuestVariables[1]=50;
        }
         if (myquest->thisquest->id==262&&QuestVariables[1]<52)
        {
          QuestVariables[1]=51;
        }
        //2Do: other values
         if (myquest->thisquest->id==264&&QuestVariables[1]<54)
        {
          QuestVariables[1]=53;
        }
        //2do: other values
          if (myquest->thisquest->id==266&&QuestVariables[1]<54)
        {
          QuestVariables[1]=55;
        }
        //2do: other values
          if (myquest->thisquest->id==269&&QuestVariables[1]<59)
        {
          QuestVariables[1]=58;
        }
         //2do: other values
          if (myquest->thisquest->id==273&&QuestVariables[1]<65)
        {
          QuestVariables[1]=64;
        }
          //2do: other values
          if (myquest->thisquest->id==274&&QuestVariables[1]<66)
        {
          QuestVariables[1]=65;
        }


        //TEST 282 (ok)
        /*
         if (myquest->thisquest->id==282&&QuestVariables[1]<75)
        {
          QuestVariables[1]=74;
        }
        */

        //test on unactive quests.
        if( ! myquest->active )
        {
            //Main quest
            if (myquest->thisquest->id==212&&QuestVariables[1]<0x04)
            {
              QuestVariables[1]=0x03;
            }
            if (myquest->thisquest->id==213&&QuestVariables[1]<0x05)
            {
              QuestVariables[1]=0x04;
            }
            if (myquest->thisquest->id==214&&QuestVariables[1]<0x06)
            {
              QuestVariables[1]=0x05;
            }
            if (myquest->thisquest->id>=218&&myquest->thisquest->id<=220&&QuestVariables[1]<0x0A)
            {
              QuestVariables[1]=0x09;
            }
             if (myquest->thisquest->id==101&&QuestVariables[1]<0x0B)
            {
              QuestVariables[1]=0x0A;
            }
             if (myquest->thisquest->id==104&&QuestVariables[1]<0x0C)
            {
              QuestVariables[1]=0x0B;
            }
             if (myquest->thisquest->id==107&&QuestVariables[1]<0x0D)
            {
              QuestVariables[1]=0x0C;
            }
             if (myquest->thisquest->id==223&&QuestVariables[1]<0x0E)
            {
              QuestVariables[1]=0x0D;
            }
             if (myquest->thisquest->id==231&&QuestVariables[1]<0x0F)
            {
              QuestVariables[1]=0x0E;
            }
             if (myquest->thisquest->id==233&&QuestVariables[1]<0x10)
            {
              QuestVariables[1]=0x0F;
            }
             if (myquest->thisquest->id==234&&QuestVariables[1]<0x11)
            {
              QuestVariables[1]=0x10;
            }

            //second level job (Soldier/muse/hawker/dealer)
            if (myquest->thisquest->id==1061||myquest->thisquest->id==1067||myquest->thisquest->id==1073||myquest->thisquest->id==1079)
            {
                QuestVariables[6]=0x02;
            }


            if (myquest->thisquest->id==2092)
            {
                QuestVariables[11]=0x05;
            }

            if (myquest->thisquest->id==2077)
            {
                QuestVariables[10]=0x05;
            }

            //LMA: Patch for lvl 30 class quests.
            if (myquest->thisquest->id==857||myquest->thisquest->id==907||myquest->thisquest->id==956||myquest->thisquest->id==1006||myquest->thisquest->id==1007)
            {
               if (QuestVariables[5]<0x04)
               {
                  QuestVariables[5]=0x03;
               }

            }

            //lvl 30 quest are done.
            if (myquest->thisquest->id==912)
            {
               if (QuestVariables[5]<0x07)
               {
                  QuestVariables[5]=0x06;
               }
            }

            if (myquest->thisquest->id==9997||myquest->thisquest->id==858)
            {
               QuestVariables[5]=0x07;
            }

            if (myquest->thisquest->id==1008)
            {
               QuestVariables[5]=0x07;
            }

            //For Hawkers
            if (((myquest->thisquest->id==957||myquest->thisquest->id==958)&&myquest->items[4]==1)||myquest->thisquest->id==959)
            {
               QuestVariables[5]=0x07;
            }

            //Patch to end Spero Quest.
            if (myquest->thisquest->id==2011)
            {
               QuestVariables[8]=0x07;
            }

            switch (myquest->thisquest->id)
            {
                   case 814: Log(MSG_INFO, "Player: %s can use flying vessel", CharInfo->charname); canUseFlyingVessel = true; break;
                   case 9999: Log(MSG_INFO, "Player: %s can speak Luna lang", CharInfo->charname); speaksLuna = true; break;
            }
        }
        MyQuest.push_back( myquest );
    }
   	GServer->DB->QFree( );
#endif

	Session->isLoggedIn = true;
    GServer->DB->QExecute("UPDATE accounts SET online=true where id=%u", Session->userid );

    // Calculate how many fairies are available online, according to amoutn of players
	int oldFairyMax = GServer->Config.FairyMax;
    GServer->Config.FairyMax = (int)ceil((float)GServer->ClientList.size() / 50.0); //(1 fairy more every 50 player)
	if( oldFairyMax < GServer->Config.FairyMax ){
        CFairy* thisfairy = new (nothrow) CFairy;
        thisfairy->LastTime = clock();
        thisfairy->assigned = 0;
        thisfairy->ListIndex = 0;
        thisfairy->WaitTime = GServer->Config.FairyWait;
        GServer->FairyList.push_back( thisfairy );
    }


	return true;
}

//LMA: Calculating item signature
void CPlayer::CalculateSignature( int slot )
{
     long int res_head=-1;
     long int res_data=-1;
     int res=1;


     if(items[slot].itemnum==0)
     {
        items[slot].sig_head=-1;
        items[slot].sig_data=-1;
        items[slot].sig_gem=-1;
        items[slot].sp_value=-1;
        items[slot].last_sp_value=-1;
        return;
     }

     res_head=(long int)pow(2,5)*items[slot].itemnum+items[slot].itemtype;

     if( items[slot].itemtype >= 10 && items[slot].itemtype <= 13 )
     {
         res_data=items[slot].count;
     }
     else
     {
        res_data=items[slot].stats;
        if(items[slot].socketed)
        		res_data+=(long int)pow(2,26);
        if(items[slot].appraised)
		        res_data+=(long int)pow(2,27);

        res_data+=(long int)pow(2,16)*(items[slot].lifespan*10);
		res_data+=(long int)pow(2,9)*items[slot].durability;
		res_data+=(long int)pow(2,28)*items[slot].refine;
     }

     items[slot].sig_head=res_head;
     items[slot].sig_data=res_data;
     items[slot].sig_gem=items[slot].gem;

     //Special PAT case
     if(items[slot].itemtype == 14&&items[slot].sp_value<=0&&items[slot].lifespan>0)
     {
        items[slot].sp_value=10*items[slot].lifespan;
        items[slot].last_sp_value=-1;
     }
     else
     {
         items[slot].last_sp_value=items[slot].sp_value;
     }

     if(items[slot].last_sp_value>1000)
     {
        Log(MSG_INFO,"ERROR sp_value, Previous value %i",items[slot].last_sp_value);
        items[slot].last_sp_value=1000;
     }

     return;
}


//LMA: Checking item signature.
//0=delete
//1=add/update
//2=do nothing
int CPlayer::CheckSignature( int slot )
{
     long int res_head=-1;
     long int res_data=-1;
     int res=1;


     if(items[slot].itemnum==0)
     {
        items[slot].sig_head=0;
        items[slot].sig_data=0;
        items[slot].sig_gem=0;
        return 0;
     }

     res_head=(long int)pow(2,5)*items[slot].itemnum+items[slot].itemtype;

     if( items[slot].itemtype >= 10 && items[slot].itemtype <= 13 )
     {
         res_data=items[slot].count;
         //Log(MSG_INFO,"item: %i(%i*[%i:%i]), data: (%i:%i)",slot,items[slot].count,items[slot].itemtype,items[slot].itemnum,res_data,items[slot].sig_data,res_head,items[slot].sig_head);
         if ((items[slot].sig_head==res_head)&&(items[slot].sig_data==res_data))
            return 2;
     }
     else
     {
        res_data=items[slot].stats;
        if(items[slot].socketed)
        		res_data+=(long int)pow(2,26);
        if(items[slot].appraised)
		        res_data+=(long int)pow(2,27);

        res_data+=(long int)pow(2,16)*(items[slot].lifespan*10);
		res_data+=(long int)pow(2,9)*items[slot].durability;
		res_data+=(long int)pow(2,28)*items[slot].refine;
		//Log(MSG_INFO,"wep/pat: %i(%i*[%i:%i]), data: (%li:%li), head(%li:%li)",slot,items[slot].count,items[slot].itemtype,items[slot].itemnum,res_data,items[slot].sig_data,res_head,items[slot].sig_head);

        //special PAT handling
		if(items[slot].itemtype == 14)
		{
             if(items[slot].sp_value<=0&&items[slot].lifespan>0)
             {
                items[slot].sp_value=10*items[slot].lifespan;
                items[slot].last_sp_value=-1;
             }

            if ((items[slot].sig_head==res_head)&&(items[slot].sig_data==res_data)&&(items[slot].sig_gem==items[slot].gem)&&(items[slot].last_sp_value==items[slot].sp_value))
               return 2;
        }
        else
        {
            if ((items[slot].sig_head==res_head)&&(items[slot].sig_data==res_data)&&(items[slot].sig_gem==items[slot].gem))
               return 2;
        }
     }

     items[slot].sig_head=res_head;
     items[slot].sig_data=res_data;
     items[slot].sig_gem=items[slot].gem;
     items[slot].last_sp_value=items[slot].sp_value;


     return res;
}

// This is a REALLY bad way of saving the character data, but it works ^^
//LMA: should be more efficient now ;)
void CPlayer::savedata( )
{
    lastSaveTime = clock();
    if(Session->userid!=0)
    {
        CMap* map = GServer->MapList.Index[Position->Map];
    	CRespawnPoint* thisrespawn = map->GetNearRespawn( this );
    	if(thisrespawn == NULL)
    	   Position->respawn = 4;
    	else
    	   Position->respawn = thisrespawn->id;
	    char quick[1024];

	    //LMA: we save the skills elsewhere now :)
	    /*
	    char basic[1024];
	    char sclass[1024];
 	    char slevel[1024];
    	for(UINT i=0;i<MAX_SKILL;i++)
    	{
            if(i==0)
            {
    	       sprintf(&sclass[i], "%i",cskills[i].id);
    	       sprintf(&slevel[i], "%i",cskills[i].level);
            }
            else
            {
    	       sprintf(&sclass[strlen(sclass)], ",%i",cskills[i].id);
    	       sprintf(&slevel[strlen(slevel)], ",%i",cskills[i].level);
            }
        }
    	for(UINT i=0;i<42;i++)
    	{
            if(i==0)
            	sprintf(&basic[i], "%i",bskills[i]);
            else
                sprintf(&basic[strlen(basic)], ",%i",bskills[i]);
        }
        */

        for(UINT i=0;i<48;i++)
        {
            if(i==0)
            	sprintf(&quick[i], "%i",quickbar[i]);
            else
                sprintf(&quick[strlen(quick)], ",%i",quickbar[i]);
        }

        //long int hp = Stats->HP;
        long long hp = Stats->HP;
    	if(hp<=0)
    	   hp=Stats->MaxHP * 10 / 100;
	   if(Stats->MP<0)
	       Stats->MP=0;

        //LMA: bonus XP (coupon)
        int temp_xp=bonusxp;
        time_t temp_timer=timerxp;

        if(once)
        {
            temp_xp=0;
            temp_timer=0;
        }

        //LMA: adding union stuff.
        //LMA: Saving skills elsewhere now :)
        //GServer->DB->QExecute("UPDATE characters SET classid=%i,level=%i,zuly=%i,curHp=%i,curMp=%i,str=%i,con=%i,dex=%i,_int=%i,cha=%i,sen=%i,exp=%i,skillp=%i,statp=%i, stamina=%i,quickbar='%s',class_skills='%s',class_skills_level='%s',basic_skills='%s',respawnid=%i,clanid=%i,clan_rank=%i, townid=%i, rewardpoints=%i, bonusxp=%i, timerxp=%i, shoptype=%i, timershop=%i, unionid=%i, unionfame=%i, union01=%i, union02=%i, union03=%i, union04=%i, union05=%i WHERE id=%i",
        /*
        GServer->DB->QExecute("UPDATE characters SET classid=%i,level=%i,zuly=%i,curHp=%i,curMp=%i,str=%i,con=%i,dex=%i,_int=%i,cha=%i,sen=%i,exp=%i,skillp=%i,statp=%i, stamina=%i,quickbar='%s',class_skills='%s',class_skills_level='%s',basic_skills='%s',respawnid=%i,clanid=%i,clan_rank=%i, townid=%i, rewardpoints=%i, bonusxp=%i, timerxp=%i, shoptype=%i, timershop=%i, unionid=%i, unionfame=%i, union01=%i, union02=%i, union03=%i, union04=%i, union05=%i WHERE id=%i",
                    CharInfo->Job,Stats->Level, CharInfo->Zulies, (UINT) hp, (UINT) Stats->MP,
                    Attr->Str,Attr->Con,Attr->Dex,Attr->Int,Attr->Cha,Attr->Sen,
                    (UINT) CharInfo->Exp,CharInfo->SkillPoints,CharInfo->StatPoints,CharInfo->stamina,
                    quick, sclass,slevel,basic,Position->respawn,Clan->clanid,Clan->clanrank,Position->saved,CharInfo->rewardpoints,temp_xp,temp_timer,Shop->ShopType,Shop->mil_shop_time,
                    CharInfo->unionid,CharInfo->unionfame,CharInfo->union01,CharInfo->union02,CharInfo->union03,CharInfo->union04,CharInfo->union05,CharInfo->charid);
        */

        GServer->DB->QExecute("UPDATE characters SET classid=%i,level=%i,zuly=%i,curHp=%i,curMp=%i,str=%i,con=%i,dex=%i,_int=%i,cha=%i,sen=%i,exp=%i,skillp=%i,statp=%i, stamina=%i,quickbar='%s',respawnid=%i,clanid=%i,clan_rank=%i, townid=%i, rewardpoints=%i, bonusxp=%i, timerxp=%i, shoptype=%i, timershop=%i, unionid=%i, unionfame=%i, union01=%i, union02=%i, union03=%i, union04=%i, union05=%i WHERE id=%i",
                    CharInfo->Job,Stats->Level, CharInfo->Zulies, (UINT) hp, (UINT) Stats->MP,
                    Attr->Str,Attr->Con,Attr->Dex,Attr->Int,Attr->Cha,Attr->Sen,
                    (UINT) CharInfo->Exp,CharInfo->SkillPoints,CharInfo->StatPoints,CharInfo->stamina,
                    quick,Position->respawn,Clan->clanid,Clan->clanrank,Position->saved,CharInfo->rewardpoints,temp_xp,temp_timer,Shop->ShopType,Shop->mil_shop_time,
                    CharInfo->unionid,CharInfo->unionfame,CharInfo->union01,CharInfo->union02,CharInfo->union03,CharInfo->union04,CharInfo->union05,CharInfo->charid);

        //LMA: intelligent item save (?)
    	//if(!GServer->DB->QExecute("DELETE FROM items WHERE owner=%i", CharInfo->charid)) return;
    	int res_check=0;
    	int nb_saved=0;
    	int nb_delete=0;
    	int sp_item_value=0;
    	for(UINT i=0;i<MAX_INVENTORY;i++)
        {
            //Already deleted
            if ((items[i].itemnum==0)&&(items[i].sig_data==-1))
               continue;
            res_check=CheckSignature(i);
            //not changed
            if(res_check==2)
               continue;
            //2delete
            if(res_check==0)
            {
                //delete item.
                GServer->DB->QExecute("DELETE FROM items WHERE owner=%i and slotnum=%i", CharInfo->charid,i);
                items[i].sig_data=-1;
                items[i].sig_head=-1;
                items[i].sig_gem=-1;
                items[i].sp_value=-1;
                items[i].last_sp_value=-1;
                nb_delete++;
                continue;
            }

            //Add or update item (new way, mysql 4.1+)
            /*
    		GServer->DB->QExecute("INSERT INTO items (owner,itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem) VALUES(%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i)",
    								CharInfo->charid, items[i].itemnum, items[i].itemtype,items[i].refine, items[i].durability,
    								items[i].lifespan, i, items[i].count, items[i].stats, (items[i].socketed?1:0),
    								(items[i].appraised?1:0),items[i].gem );
            */
            nb_saved++;
            sp_item_value=0;
            if(items[i].itemtype==14)
              sp_item_value=items[i].sp_value;
            GServer->DB->QExecute("INSERT INTO items (owner,slotnum,itemnum,itemtype,refine,durability,lifespan,count,stats,socketed,appraised,gem,sp_value) VALUES(%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i) ON DUPLICATE KEY UPDATE owner=VALUES(owner),itemnum=VALUES(itemnum),itemtype=VALUES(itemtype),refine=VALUES(refine),durability=VALUES(durability),lifespan=VALUES(lifespan),slotnum=VALUES(slotnum),count=VALUES(count),stats=VALUES(stats),socketed=VALUES(socketed),appraised=VALUES(appraised),gem=VALUES(gem),sp_value=VALUES(sp_value)",
    								CharInfo->charid, i, items[i].itemnum, items[i].itemtype,items[i].refine, items[i].durability,
    								items[i].lifespan, items[i].count, items[i].stats, (items[i].socketed?1:0),
    								(items[i].appraised?1:0),items[i].gem,sp_item_value );
    	}

    	//Log(MSG_INFO,"We saved %i slots, deleted %i",nb_saved,nb_delete);


    	/*
    	//LMA: We're saving storage separetly now :)
    	if(!GServer->DB->QExecute("DELETE FROM storage WHERE owner=%i", Session->userid)) return;
    	for(UINT i=0;i<160;i++)
        {
    		if (storageitems[i].count > 0)
            {
    			GServer->DB->QExecute("INSERT INTO storage (owner,itemnum,itemtype,refine,durability,lifespan,slotnum,count,stats,socketed,appraised,gem) VALUES(%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i)",
    								Session->userid, storageitems[i].itemnum, storageitems[i].itemtype,storageitems[i].refine, storageitems[i].durability,
    								storageitems[i].lifespan, i, storageitems[i].count, storageitems[i].stats, (storageitems[i].socketed?1:0),
                                    (storageitems[i].appraised?1:0), storageitems[i].gem );//Gem Fix by Irulagain
    		}
    	}
    	*/

    	//We save quests elsewhere.
    	/*
    	if(!GServer->DB->QExecute( "DELETE FROM list_quest WHERE owner=%i",CharInfo->charid )) return;
    	for(int i=0;i<MyQuest.size();i++)
    	{
            QUESTS* myquest = MyQuest.at( i );
     	    char nqitem[200];
        	for( int j=0;j<5;j++ )
        	{
                if( j==0 )
                {
        	       sprintf(&nqitem[j], "%i",myquest->items[j]);
                }
                else
                {
        	       sprintf(&nqitem[strlen(nqitem)], "|%i",myquest->items[j]);
                }
            }
            GServer->DB->QExecute("INSERT INTO list_quest (owner,questid,nitems,active) VALUES (%i,%i,'%s',%i)",
            CharInfo->charid, myquest->thisquest->id, nqitem, myquest->active );
        }
        */

        //We save Zuly storage elsewhere.
		//GServer->DB->QExecute("update accounts set zulystorage = %i where id = %i", CharInfo->Storage_Zulies, Session->userid);

		//QSD Save
		//2do, save on used?
		#ifdef USENEWQUESTSYSTEM
               savequests(this);
        #endif

		Log(MSG_INFO, "Data Saved for char '%s' ", CharInfo->charname );
    }
}

//LMA: Saving skills here...
void CPlayer::saveskills( )
{
    if(Session->userid==0)
        return;
    char basic[1024];
    char drive[1024];
    char sclass[1024];
    char slevel[1024];
    char uclass[1024];
    char ulevel[1024];
    char mclass[1024];
    char mlevel[1024];

    //class skills and level.
    for(UINT i=0;i<MAX_CLASS_SKILL;i++)
    {
        if(i==0)
        {
           sprintf(&sclass[0], "%i",cskills[i].id);
           sprintf(&slevel[0], "%i",cskills[i].level);
        }
        else
        {
           sprintf(&sclass[strlen(sclass)], ",%i",cskills[i].id);
           sprintf(&slevel[strlen(slevel)], ",%i",cskills[i].level);
        }

    }

    //unique skills.
    for(UINT i=90;i<90+MAX_UNIQUE_SKILL;i++)
    {
        if(i==90)
        {
           sprintf(&uclass[0], "%i",cskills[i].id);
           sprintf(&ulevel[0], "%i",cskills[i].level);
        }
        else
        {
           sprintf(&uclass[strlen(uclass)], ",%i",cskills[i].id);
           sprintf(&ulevel[strlen(ulevel)], ",%i",cskills[i].level);
        }

    }

    //mileage skills and level.
    for(UINT i=120;i<120+MAX_MILEAGE_SKILL;i++)
    {
        if(i==120)
        {
           sprintf(&mclass[0], "%i",cskills[i].id);
           sprintf(&mlevel[0], "%i",cskills[i].level);
        }
        else
        {
           sprintf(&mclass[strlen(mclass)], ",%i",cskills[i].id);
           sprintf(&mlevel[strlen(mlevel)], ",%i",cskills[i].level);
        }

    }

    //basic skills.
    for(UINT i=320;i<320+MAX_BASIC_SKILL;i++)
    {
        if(i==320)
            sprintf(&basic[0], "%i",cskills[i].id);
        else
            sprintf(&basic[strlen(basic)], ",%i",cskills[i].id);
    }

    //driving skills.
    for(UINT i=60;i<60+MAX_DRIVING_SKILL;i++)
    {
        if(i==60)
            sprintf(&drive[0], "%i",cskills[i]);
        else
            sprintf(&drive[strlen(drive)], ",%i",cskills[i]);
    }

    //LMA: Saving Skills Data for a player.
    GServer->DB->QExecute("UPDATE characters SET class_skills='%s',class_skills_level='%s',basic_skills='%s',driving_skills='%s',unique_skills='%s',mileage_skills='%s',unique_skills_level='%s',mileage_skills_level='%s' WHERE id=%i",
                sclass,slevel,basic,drive,uclass,mclass,ulevel,mlevel,
                CharInfo->charid);

    Log(MSG_INFO, "Skill Data Saved for char '%s' ", CharInfo->charname );


    return;
}

//For QSD.
#ifdef USENEWQUESTSYSTEM
unsigned char GetCharVal( char mychar )
{
    switch( mychar )
    {
        case '0':   return 0;
        case '1':   return 1;
        case '2':   return 2;
        case '3':   return 3;
        case '4':   return 4;
        case '5':   return 5;
        case '6':   return 6;
        case '7':   return 7;
        case '8':   return 8;
        case '9':   return 9;
        case 'a':   return 10;
        case 'b':   return 11;
        case 'c':   return 12;
        case 'd':   return 13;
        case 'e':   return 14;
        case 'f':   return 15;
        case 'A':   return 10;
        case 'B':   return 11;
        case 'C':   return 12;
        case 'D':   return 13;
        case 'E':   return 14;
        case 'F':   return 15;
    }
    return 0;
}

void EncodeBinary( char* encoded, unsigned char* data, unsigned datalen )
{
    for( unsigned short i = 0, j = 0; i < datalen; i++ )
    {
        encoded[ j++ ] = "0123456789ABCDEF"[ data[ i ] >> 4 ];
        encoded[ j++ ] = "0123456789ABCDEF"[ data[ i ] & 0xf ];
    }
    encoded[ datalen * 2 ] = 0;
}

void DecodeBinary( char* encoded, unsigned char* data )
{
    unsigned curbit = 0;
    for( unsigned i = 0; i < (unsigned)strlen(encoded); i+=2 )
    {
        data[curbit] = GetCharVal( encoded[i] ) << 4;
        data[curbit] += GetCharVal( encoded[i+1] );
        curbit++;
    }
}
#endif

#ifdef USENEWQUESTSYSTEM
void CPlayer::savequests( CPlayer* thisclient )
{
    char* questBuffer = new char[sizeof(SQuestData)*3 +1];
    mysql_real_escape_string(GServer->DB->Mysql, questBuffer, (const char*)&quest, sizeof(SQuestData));
    GServer->DB->QExecute( "DELETE FROM list_quest_new WHERE owner=%i",thisclient->CharInfo->charid );
    GServer->DB->QExecute("INSERT INTO list_quest_new (owner, quests) VALUES(%i,'%s')",
        thisclient->CharInfo->charid, questBuffer);
    delete questBuffer;
}
#endif


//LMA: getting the family skill.
int CPlayer::GoodSkill(int skill_id)
{
    int type=GServer->SkillList[skill_id]->skill_tab;

    if (type==11)
        return 2;   //basic
    if (type==41)
        return 3;   //unique
    if (type==51)
        return 4;   //mileage
    if (type>=20&&type<30)
        return 0;   //class
    if (type>=30&&type<40)
        return 1;   //driving


    return -1;
}

//LMA: Find a skill offset for cskills...
int CPlayer::FindSkillOffset(int family)
{
    int begin[5];
    int end[5];

    begin[0]=0;
    begin[1]=60;
    begin[2]=320;
    begin[3]=90;
    begin[4]=120;
    end[0]=60;
    end[1]=90;
    end[2]=362;
    end[3]=120;
    end[4]=320;

    int res=cur_max_skills[family];

    if (res<end[family])
    {
        cur_max_skills[family]++;
        return res;
    }

    /*
    switch(family)
    {
        case 0:
        {
            begin=0;
            end=60;
        }
        break;
        case 1:
        {
            begin=60;
            end=90;
        }
        break;
        case 2:
        {
            begin=320;
            end=362;
        }
        break;
        case 3:
        {
            begin=90;
            end=120;
        }
        break;
        case 4:
        {
            begin=120;
            end=320;
        }
        break;
        default:
        break;
    }

    for (int i=begin;i<end;i++)
    {
        if(cskills[i].id==0)
            return i;
    }
    */


    return -1;
}

//LMA: Save some skills informations for later... (useless)
/*
void CPlayer::SaveSkillInfo(int family,int offset,int id,int level)
{
    //No need for class.
    if (family==0)
        return;

    if(family==1)
    {
        if(dskills[offset]!=0)
            Log(MSG_WARNING,"Skill overwrite");
        dskills[offset]=id;
        return;
    }

    if(family==2)
    {
        if(bskills[offset]!=0)
            Log(MSG_WARNING,"Skill overwrite");
        bskills[offset]=id;
        return;
    }

    if(family==3)
    {
        if(uskills[offset].id!=0)
            Log(MSG_WARNING,"Skill overwrite");
        uskills[offset].id=id;
        uskills[offset].level=level;
        return;
    }

    if(family==4)
    {
        if(mskills[offset].id!=0)
            Log(MSG_WARNING,"Skill overwrite");
        mskills[offset].id=id;
        mskills[offset].level=level;
        return;
    }


    return;
}
*/

//LMA: Upgrade a skill level (useless)...
/*
void CPlayer::UpgradeSkillInfo(int offset,int skillid,int nb_upgrade)
{
    //no need for class.
    int family=0;
    if (offset<60)
        return;

    //driving, useless...
    if (offset>=60&&offset<64)
        return;

    //basic, no level...
    if (offset>=64&&offset<90)
        return;

    if (offset>=90&&offset<120)
        family=3;

    if (offset>=120&&offset<320)
        family=4;


    if(family==3)
    {
        for (int i=0;i<MAX_UNIQUE_SKILL;i++)
        {

            if (uskills[i].id==0)
            {
                Log(MSG_WARNING,"Skill %i not found during upgrade unique",skillid);
                return;
            }

            if (uskills[i].id==skillid)
            {
                uskills[i].level+=nb_upgrade;
                return;
            }

        }

    }

    if(family==4)
    {
        for (int i=0;i<MAX_MILEAGE_SKILL;i++)
        {

            if (mskills[i].id==0)
            {
                Log(MSG_WARNING,"Skill %i not found during upgrade mileage",skillid);
                return;
            }

            if (mskills[i].id==skillid)
            {
                mskills[i].level+=nb_upgrade;
                return;
            }

        }

    }


    return;
}
*/
