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


// Parse our commands to their appropriate function
bool CWorldServer::pakGMCommand( CPlayer* thisclient, CPacket* P )
{

	char* tmp;
	char* command = strtok( (char*)&(*P).Buffer[1] , " ");
	if (command==NULL) return true;
	if (strcmp(command, "here")==0)
	{
        if(Config.Command_Here > thisclient->Session->accesslevel)
            return true;

        return pakGMTele(thisclient, thisclient->Position->Map, thisclient->Position->current.x, thisclient->Position->current.y);
    }
    else
	if (strcmp(command, "tele")==0) // **** TELEPORT TO MAX AND X Y POINTS *****
    {
        if(Config.Command_Tele > thisclient->Session->accesslevel)
	                    return true;
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned map=atoi(tmp);
		if ((tmp = strtok(NULL, " "))==NULL) return true; float x=(float)atoi(tmp);
		if ((tmp = strtok(NULL, " "))==NULL) return true; float y=(float)atoi(tmp);

        Log( MSG_GMACTION, " %s : /tele %i,%.2f,%.2f" , thisclient->CharInfo->charname, map, x, y);
        return pakGMTele(thisclient, map, x, y);
    }
   else if (strcmp(command, "allskill")==0) /* Give all Skill to a Player - By CrAshInSiDe */
   {
        if(Config.Command_AllSkill > thisclient->Session->accesslevel)
        return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
        Log( MSG_GMACTION, " %s : /allskill %s", thisclient->CharInfo->charname, name);
        return pakGMAllSkill(thisclient, name);
        }

   else if (strcmp(command, "npcltb")==0) /* LMA:npc shouts or announces with LTB string */
   {
        if(Config.Command_NpcLtb > thisclient->Session->accesslevel)
        return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* shan=tmp;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* aipqsd=tmp;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int npctype=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true; int ltbid=atoi(tmp);
        return pakGMnpcshout(thisclient,shan,aipqsd,npctype,ltbid);
        }

   else if (strcmp(command, "delskills")==0) /* Remove all Skill from a Player - modified by rl2171 */
   {
        if(Config.Command_DelSkills > thisclient->Session->accesslevel)
        return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
        Log( MSG_GMACTION, " %s : /delskills %s", thisclient->CharInfo->charname, name);
        return pakGMDelSkills(thisclient, name);
        }
/* GM List {By CrAshInSiDe} */
    else if(strcmp(command, "gmlist")==0)
    {
        if(Config.Command_GmList > thisclient->Session->accesslevel)
            return true;
        SendPM(thisclient, "The currently GM connected is:");
        int count=1;
        int hiddenam=0;
        char line0[200];
        while(count <= (ClientList.size()-1))
        {
            CPlayer* whoclient = (CPlayer*)ClientList.at(count)->player;
            if(whoclient->Session->accesslevel > 100)
            {
                sprintf(line0, "%s - GM[%i]", whoclient->CharInfo->charname, whoclient->Session->accesslevel);
            }

            if(whoclient->isInvisibleMode != true)
            {
                SendPM(thisclient, line0 );
            }
            else
            {
                hiddenam++;
            }
            count++;
        }
        sprintf(line0, "There are currently %i GM connected!", ((ClientList.size()-1)-hiddenam));
        Log( MSG_GMACTION, " %s : /gmlist" , thisclient->CharInfo->charname);
        SendPM(thisclient, line0 );
        return true;
    }

    /// geo edit for /savetown // 30 sep 07
    else if (strcmp(command, "savetown")==0)
    {
        if ((tmp = strtok(NULL, " ")) == NULL) tmp = 0; int loc=atoi(tmp);
        unsigned int spot = 0;
        switch(loc)
        {
            case 1:  //AP
            {
                spot = 54;  // 1
                break;
            }
            case 2:  //Zant
            {
                spot = 1;  // 2
                break;
            }
            case 3:  //Junon
            {
                spot = 4;  // 4
                break;
            }
            case 4:  //Eucar
            {
                spot = 105;  // 5
                break;
            }
            case 5:  //Xita
            {
                spot = 122;  //68
                break;
            }
        }
        if(spot>0)
        {
            thisclient->Position->saved = spot;
            SendPM(thisclient, "Saved in Town");
        }
        else
        {
            SendPM(thisclient, "Please input a number after the savetown command, below is a list of places and their appropriate number");
            SendPM(thisclient, "1 = Adventurers plains");
            SendPM(thisclient, "2 = The city of Zant");
            SendPM(thisclient, "3 = Junon Polis");
            SendPM(thisclient, "4 = The City of Eucar");
            SendPM(thisclient, "5 = Xita Refuge");
            SendPM(thisclient, "Example; /savetown 3");
        }

        return true;
    }
    /// end geo edit
   else if (strcmp(command, "mute")==0) //==== Mute a player ==== [by Paul_T]
   {
        if(Config.Command_Mute > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL)
                return true;
        char* id=tmp;
        if ((tmp = strtok(NULL, " "))==NULL)
                return true;
        int min=atoi(tmp);
        Log( MSG_GMACTION, " %s : /mute %s %i" , thisclient->CharInfo->charname, id, min);
        return pakGMMute(thisclient, id, min);
    }
    else if (strcmp(command, "reborn")==0) //==== Reborn ==== (By Core)
   {
         if(Config.Command_Reborn > thisclient->Session->accesslevel)
                        return true;

        Log( MSG_GMACTION, " %s : /reborn" , thisclient->CharInfo->charname);
        return pakGMReborn(thisclient);
   }
   else if (strcmp(command, "event")==0) //==== Trigger Events (credit Welson)
   {
        if(Config.Command_Event > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL)
                return true;
        int npctype=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
                return true;
        int dialog=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
                return true;
        long int type=atoi(tmp);
        Log( MSG_GMACTION, " %s : /event %i %i %i" ,thisclient->CharInfo->charname, npctype,dialog,type);
        return pakGMEventType(thisclient,npctype,dialog,type);
    }
    else if (strcmp(command, "save")==0) // *** SAVE USER DATA *****
    {
             if(Config.Command_Save > thisclient->Session->accesslevel)
	                    return true;
           thisclient->savedata();
           return true;
	}
    else if (strcmp(command, "reload")==0) // *** RELOAD CONFIG.INI ******
    {
//         if(Config.Command_Reload > thisclient->Session->accesslevel )
           if(Config.Command_Reload > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /reload NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "reload NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
         if ((tmp = strtok(NULL, " "))==NULL)return true;
         else if(strcmp(tmp, "config")==0)
//         {
             LoadConfigurations( (char*)filename.c_str()  );
//             GServer->LoadConfig( );
//         }
         else if(strcmp(tmp, "mobs")==0)
             GServer->LoadNPCData( );
         else if(strcmp(tmp, "drops")==0)
             GServer->LoadPYDropsData( );
         else if(strcmp(tmp, "cmd")==0)
             LoadConfigurations( "commands.ini" );
         else if(strcmp(tmp, "cquests")==0)
         {
             LoadCustomEvents( );
             LoadCustomTeleGate( );
         }
         else if(strcmp(tmp, "events")==0)
         {
             GServer->LoadCustomEvents( );
             GServer->LoadCustomTeleGate( );
         }
         else if(strcmp(tmp, "quests")==0)
         {
             GServer->QuestList.clear( );
             GServer->LoadQuestData( );
         }
         else if(strcmp(tmp, "spawns")==0)
         {
             GServer->LoadMonsterSpawn();
         }
         //else if(strcmp(tmp, "equip")==0)
         //{
         //    GServer->LoadEquip();
         //}
         else
         {
             Log( MSG_INFO, "Unrecognized reload command by GM %s" , thisclient->CharInfo->charname);
             return true;
         }
         Log( MSG_GMACTION, " %s : /reload %s" , thisclient->CharInfo->charname, tmp);
         char buffer2[200];
         sprintf ( buffer2, "%s data has been reloaded", tmp );
         SendPM(thisclient, buffer2);
            return true;
    }
	else if (strcmp(command, "prize")==0)
    {
         if ((tmp = strtok(NULL, " "))==NULL)return true;
         {
             UINT prizeid = atoi(tmp);
             thisclient->PrizeExchange(thisclient, prizeid);
             return true;
         }
    }
    else if (strcmp(command, "ann")==0) // *** SEND A ANNOUNCEMENT ***
    {
        if(Config.Command_Ann > thisclient->Session->accesslevel)
	       return true;
        Log( MSG_GMACTION, " %s : /ann %s" , thisclient->CharInfo->charname, &P->Buffer[5] );
		return pakGMAnn(thisclient, P);
    }
    /*else if(strcmp(command, "bodysize")==0)
    {
        if ((tmp = strtok(NULL, " ")) == NULL) return true; UINT size=atoi(tmp);
        BEGINPACKET(pak, 0x721);
        ADDWORD(pak, 36);
        ADDWORD(pak, size);
        ADDWORD(pak, 0);
        thisclient->client->SendPacket(&pak);
        RESETPACKET(pak, 0x0730);
        ADDWORD(pak, 5);
        ADDWORD(pak, 0xa24d);
        ADDWORD(pak, 0x40b3);
        thisclient->client->SendPacket(&pak);
        SendSysMsg(thisclient, "Body size changed!");
    }*/
    /*else if(strcmp(command, "headsize")==0)
    {
        if ((tmp = strtok(NULL, " ")) == NULL) return true; UINT size=atoi(tmp);
        BEGINPACKET(pak, 0x721);
        ADDWORD(pak, 35);
        ADDWORD(pak, size);
        ADDWORD(pak, 0);
        thisclient->client->SendPacket(&pak);
        RESETPACKET(pak, 0x0730);
        ADDWORD(pak, 5);
        ADDWORD(pak, 0xa24d);
        ADDWORD(pak, 0x40b3);
        thisclient->client->SendPacket(&pak);
        SendSysMsg(thisclient, "Head size changed!");
    }*/
    else if(strcmp(command, "face")==0)
    {
        if(Config.Command_Face > thisclient->Session->accesslevel)
	       return true;
        if ((tmp = strtok(NULL, " ")) == NULL) return true; UINT face=atoi(tmp);
        if (face > 12) return true;
        UINT style;
        if ((tmp = strtok(NULL, " ")) == NULL) style = 0; else style = atoi(tmp);
        if (style > 3) style = 3;
        thisclient->CharInfo->Face = ((face*7) + style + 1);
        BEGINPACKET(pak, 0x721);
        ADDWORD(pak, 8);
        ADDWORD(pak, thisclient->CharInfo->Face);
        ADDWORD(pak, 0);
        thisclient->client->SendPacket(&pak);
        RESETPACKET(pak, 0x0730);
        ADDWORD(pak, 5);
        ADDWORD(pak, 0xa24d);
        ADDWORD(pak, 0x40b3);
        thisclient->client->SendPacket(&pak);
        SendPM(thisclient, "Face changed!");
        DB->QExecute("UPDATE characters SET face=%i WHERE id=%i", thisclient->CharInfo->Face, thisclient->CharInfo->charid);
    }
    else if(strcmp(command, "hair")==0)
    {
        if(Config.Command_Hair > thisclient->Session->accesslevel)
	       return true;
        if ((tmp = strtok(NULL, " ")) == NULL) return true; UINT hair=atoi(tmp);
        if (hair > 6) return true;
        thisclient->CharInfo->Hair = (hair*5);
        BEGINPACKET(pak, 0x721);
        ADDWORD(pak, 9);
        ADDWORD(pak, thisclient->CharInfo->Hair);
        ADDWORD(pak, 0);
        thisclient->client->SendPacket(&pak);
        RESETPACKET(pak, 0x0730);
        ADDWORD(pak, 5);
        ADDWORD(pak, 0xa24d);
        ADDWORD(pak, 0x40b3);
        thisclient->client->SendPacket(&pak);
        DB->QExecute("UPDATE characters SET hairStyle=%i WHERE id=%i", thisclient->CharInfo->Hair, thisclient->CharInfo->charid);
        SendPM(thisclient, "Hair changed!");
    }
    else if(strcmp(command, "pvp")==0)
    {
        if(Config.Command_Pvp > thisclient->Session->accesslevel)
	       return true;
        CMap* map = MapList.Index[thisclient->Position->Map];
        BEGINPACKET(pak, 0x721);
        ADDWORD(pak, 34);
        if(map->allowpvp!=0)
        {
            map->allowpvp = 0;
            ADDWORD(pak, 2);
            SendSysMsg(thisclient, "PVP off");
        }
        else
        {
            map->allowpvp = 1;
            ADDWORD(pak, 51);
            SendSysMsg(thisclient, "PVP on");
        }
        ADDWORD(pak, 0);
        SendToMap(&pak, thisclient->Position->Map);
        RESETPACKET(pak, 0x0730);
        ADDWORD(pak, 5);
        ADDWORD(pak, 0xa24d);
        ADDWORD(pak, 0x40b3);
        SendToMap(&pak, thisclient->Position->Map);
    }
    else if(strcmp(command, "pvpnew")==0)
    {
        if(Config.Command_Pvp > thisclient->Session->accesslevel)
	       return true;
        if ((tmp = strtok(NULL, " ")) == NULL) tmp = 0; int testvalue=atoi(tmp);
        CMap* map = MapList.Index[thisclient->Position->Map];

        switch (testvalue)
        {
           case 0:
           {
            BEGINPACKET(pak, 0x0730);
            ADDWORD(pak, 5);
            ADDWORD(pak, 0xa24d);
            ADDWORD(pak, 0x40b3);
            SendSysMsg(thisclient, "PVP 0");
            SendToMap(&pak, thisclient->Position->Map);
            }
            break;
            case 1:
            {
                BEGINPACKET(pak, 0x0730);
                ADDWORD(pak, 0x0101);
                ADDWORD(pak, 0x0b03);
                ADDWORD(pak, 0x0000);
                 SendSysMsg(thisclient, "PVP 1");
                 SendToMap(&pak, thisclient->Position->Map);
             }
             break;
            case 2:
            {
                //0x813 - 05 00
                //0x814 - 04 00
                BEGINPACKET(pak, 0x0813);
                ADDWORD(pak, 0x0005);
                 SendToMap(&pak, thisclient->Position->Map);
                 RESETPACKET(pak, 0x0814);
                ADDWORD(pak, 0x0004);
                 SendSysMsg(thisclient, "PVP 2");
                 SendToMap(&pak, thisclient->Position->Map);
             }
             break;
            default:
            {
                    SendSysMsg(thisclient, "Wrong value");
            }
            break;
        }


    }
    else if(strcmp(command, "who")==0)
    {
        if(Config.Command_Who > thisclient->Session->accesslevel)
            return true;
        int count=1;
        int gmcount=0;
        int playercount=0;
        char line0[200];
        while(count <= (ClientList.size()-1))
        {
            CPlayer* whoclient = (CPlayer*)ClientList.at(count)->player;
            if(whoclient->isInvisibleMode != true)
            {
                    if(whoclient->Session->accesslevel > 100)
                    {
                        gmcount++;
                    }
                    else
                    {
                        playercount++;
                    }
            }
            count++;
        }
        sprintf(line0, "There are currently %i players and %i game moderators currently connected.", playercount, gmcount);
        Log( MSG_GMACTION, " %s : /who" , thisclient->CharInfo->charname);
        SendPM(thisclient, line0 );
        return true;
    }
    else if (strcmp(command, "go")==0) // AtCommandGo
    {
        if(Config.Command_go > thisclient->Session->accesslevel)
	       return true;
        if ((tmp = strtok(NULL, " ")) == NULL) tmp = 0; int loc=atoi(tmp);
        if(Config.Command_Go > thisclient->Session->accesslevel)
            return true;
        int x = 0;
        int y = 0;
        int map = 0;
        if(loc == 1) // Adventure Plains
        {
            map = 22;
            x = 5098;
            y = 5322;
        }
        else if(loc == 2) // Canyon City of Zant
        {
            map = 1;
            x = 5240;
            y = 5192;
        }
        else if (loc == 3) // Junon Polis
        {
            map = 2;
            x = 5514;
            y = 5247;
        }
        else if (loc == 4) // Magic City of Eucar - Luna
        {
             if (thisclient->Stats->Level<50)
             {
             SendPM(thisclient, "You need to be a least Level 50 to visit Eucar!");
             return true;
             }
         {
            map = 51;
            x = 5357;
            y = 5013;
         }
        }
        else if (loc == 5) // Xita Refuge - Eldeon
        {
             if (thisclient->Stats->Level<120)
             {
             SendPM(thisclient, "You need to be a least Level 120 to visit Eldeon!");
             return true;
             }
         {
            map = 61;
            x = 5434;
            y = 4569;
         }
        }
        else if (loc == 6) // Training Grounds
        {
            map = 6;
            x = 5199;
            y = 5280;
        }
        else if (loc == 7) // Lions Plains
        {
            map = 8;
            x = 5160;
            y = 5080;
        }
        else if (loc == 8) // Luna Clan Field
        {
             //if (thisclient->Stats->Level<120)
             if (thisclient->Stats->Level<120 && thisclient->Stats->Level>160)
             // Luna Clan Field actually restricted to from 120 - 160 only, will above work?
             {
             SendPM(thisclient, "You need to be between Level 120 and 160 to visit Luna Clan Field!");
             return true;
             }

        {
            map = 59;
            x = 5095;
            y = 5128;
        }
      }
        else if (loc == 9) // Desert of the Dead
        {
            map = 29;
            x = 5093;
            y = 5144;
        }
/*        else if (loc == 10) // Pyramid Tombs
        {
            map = 41;
            x = 5105; // 5165 if jRose Client
            y = 5246; // 5207 if jRose Client
        }
*/        else if (loc == 11) // Sikuku Underground Prison
        {
             if (thisclient->Stats->Level<160) // by Terr0risT
             {
                 SendPM(thisclient, "You need to be a least Level 160 to visit Sikuku Underground Prison!");
                 return true;
             }
             else
             {
                map = 65;
                x = 5485;
                y = 5285;
             }
        }
/*        else if (loc == 12) // Oro
        {
             if (thisclient->Stats->Level<160)
             {
                 SendPM(thisclient, "You need to be a least Level 160 to visit Oro!");
                 return true;
             }
             else
             {
                map = 80;
                x = 5163;
                y = 5236;
             }
        }
*/
        else
        {
            SendPM(thisclient, "Please input a number after the go command, below is a list of places and their appropriate number");
            SendPM(thisclient, "1 = Adventurers Plains");
            SendPM(thisclient, "2 = The City of Zant");
            SendPM(thisclient, "3 = Junon Polis");
            SendPM(thisclient, "4 = Magic City of Eucar");
            SendPM(thisclient, "5 = Xita Refuge");
            SendPM(thisclient, "6 = Training grounds");
            SendPM(thisclient, "7 = Lions Plains");
            SendPM(thisclient, "8 = Luna Clan Field");
            SendPM(thisclient, "9 = Desert of the Dead");
//            SendPM(thisclient, "10 = Pyramid Tombs - ElVerloon");
            SendPM(thisclient, "11 = Sikuku Underground Prison");
//            SendPM(thisclient, "12 = Oro");
            SendPM(thisclient, "Example; /go 3");
        }
        if ( thisclient->Stats->HP < (thisclient->Stats->MaxHP / 2) || thisclient->Stats->HP < 1 || thisclient->Session->inGame == false )
        {
             SendPM(thisclient, "You need at least 50% HP in order to warp");
             return true;
        }

        if( (x != 0) && (y != 0) && (map != 0) )
        {
            fPoint coord;
            coord.x = x;
            coord.y = y;
            SendPM(thisclient, "teleport to map: %i",map);
            MapList.Index[map]->TeleportPlayer( thisclient, coord, false );
            Log( MSG_GMACTION, " %s : /go %i" , thisclient->CharInfo->charname, loc);
        }
        return true;
    }
//Old spawning gm command - commented out for now
/*
    //******************************* START RESPAWN ***************************
    else if (strcmp(command, "SSPAWN")==0)
    { //STARTPOINT IDMOB CANTMIN CANTMAX RESPAWNTIME(s)  (3 points minimum)
        if(Config.Command_SSpawn > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
          {
           Log( MSG_GMACTION, " %s : /SSPAWN NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "SSPAWN NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        Log( MSG_GMACTION, " %s : /SSPAWN", thisclient->CharInfo->charname);
        thisclient->GMRespawnPoints.map = thisclient->Position->Map;
        if ((tmp = strtok(NULL, " "))==NULL)
        {
            thisclient->GMRespawnPoints.b=0;
            return true;
        }
        thisclient->GMRespawnPoints.mobID=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
        {
            thisclient->GMRespawnPoints.b=0;
            return true;
        }
        thisclient->GMRespawnPoints.min=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
        {
            thisclient->GMRespawnPoints.b=0;
            return true;
        }
        thisclient->GMRespawnPoints.max=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
        {
            thisclient->GMRespawnPoints.b=0;
            return true;
        }
        thisclient->GMRespawnPoints.n=0;
        thisclient->GMRespawnPoints.respawntime=atoi(tmp);
        thisclient->GMRespawnPoints.b=1;
		BEGINPACKET( pak, 0x702 );
		ADDSTRING( pak, "STARTPOINT" );
		ADDBYTE( pak, 0 );
		thisclient->client->SendPacket(&pak);
		thisclient->GMRespawnPoints.d=0;
        return true;
    }
    else if (strcmp(command, "SET")==0)
    {
        if(Config.Command_Set > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /SET NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "SET NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        Log( MSG_GMACTION, " %s : /SET" , thisclient->CharInfo->charname);
        if(thisclient->GMRespawnPoints.b==1 && thisclient->GMRespawnPoints.n<50)
        {
            int n=thisclient->GMRespawnPoints.n;
            thisclient->GMRespawnPoints.points[n].x=floor(thisclient->Position->destiny.x);
            thisclient->GMRespawnPoints.points[n].y=floor(thisclient->Position->destiny.y);
            thisclient->GMRespawnPoints.n++;
            char text[10];
            sprintf(text,"--POINT #%i",thisclient->GMRespawnPoints.n);
		    BEGINPACKET( pak, 0x702 );
		    ADDSTRING( pak,text );
		    ADDBYTE( pak, 0 );
		    thisclient->client->SendPacket(&pak);
            return true;
        }
        return true;
    }
    else if (strcmp(command, "ESPAWN")==0)
    {
        if(Config.Command_ESpawn > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /ESPAWN NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "ESPAWN NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        Log( MSG_GMACTION, " %s : /ESPAWN" , thisclient->CharInfo->charname);
        if(thisclient->GMRespawnPoints.n>3 && thisclient->GMRespawnPoints.b==1)
        {
            if ((tmp = strtok(NULL, " "))==NULL)
                return true;
            int id=atoi(tmp);
            if ((tmp = strtok(NULL, " "))==NULL)
                return true;
            int agressive=atoi(tmp);
            int n=thisclient->GMRespawnPoints.n;
            char points[1000] = "";
            sprintf(&points[0],"%i",n);
            for(int i=0;i<n;i++)
            {
                sprintf(&points[strlen(points)],"|%.0f,%.0f",thisclient->GMRespawnPoints.points[i].x,thisclient->GMRespawnPoints.points[i].y);
            }
            DB->QExecute("INSERT into list_spawnareas (id,map,montype,respawntime,points,min,max,agressive) values (%i,%i,%i,%i,'%s',%i,%i,%i)",
            id,thisclient->GMRespawnPoints.map, thisclient->GMRespawnPoints.mobID,thisclient->GMRespawnPoints.respawntime,
            points,thisclient->GMRespawnPoints.min,thisclient->GMRespawnPoints.max,agressive);
            thisclient->GMRespawnPoints.b=0;
            thisclient->GMRespawnPoints.d=1;
		    BEGINPACKET( pak, 0x702 );
		    ADDSTRING( pak,"ENDSPAWN" );
		    ADDBYTE( pak, 0 );
		    thisclient->client->SendPacket(&pak);
		    ReloadMobSpawn(thisclient, id );
            return true;
        }
        return true;
    }
    else if (strcmp(command, "DSPAWN")==0)
      {
        if(Config.Command_DSpawn > thisclient->Session->accesslevel)
//        if(Config.Command_DSpawn > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /DSPAWN NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "SSPAWN NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        Log( MSG_GMACTION, " %s : /DSPAWN" , thisclient->CharInfo->charname);
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        int id=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        thisclient->GMRespawnPoints.mobID=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        thisclient->GMRespawnPoints.min=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        thisclient->GMRespawnPoints.max=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        thisclient->GMRespawnPoints.respawntime=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        int agressive = atoi(tmp);
        if(thisclient->GMRespawnPoints.n>3 && thisclient->GMRespawnPoints.d==1)
        {
            int n=thisclient->GMRespawnPoints.n;
            char points[1000] = "";
            sprintf(&points[0],"%i",n);
            for(int i=0;i<n;i++)
            {
                sprintf(&points[strlen(points)],"|%.0f,%.0f",thisclient->GMRespawnPoints.points[i].x,thisclient->GMRespawnPoints.points[i].y);
            }
            DB->QExecute("INSERT into list_spawnareas (id,map,montype,respawntime,points,min,max,agressive) values (%i,%i,%i,%i,'%s',%i,%i,%i)",
            id,thisclient->GMRespawnPoints.map,
            thisclient->GMRespawnPoints.mobID,thisclient->GMRespawnPoints.respawntime,
            points,thisclient->GMRespawnPoints.min,thisclient->GMRespawnPoints.max,agressive);
            thisclient->GMRespawnPoints.b=0;
		    BEGINPACKET( pak, 0x702 );
		    ADDSTRING( pak, "DUPESPAWN" );
		    ADDBYTE( pak, 0 );
		    thisclient->client->SendPacket(&pak);
		    ReloadMobSpawn(thisclient, id );
            return true;
        }
        return true;
    }
*/
    else if(strcmp(command, "DELETESPAWN")==0)
    {
         if(Config.Command_DelSpawn > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /DELETESPAWN NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "DELETESPAWN NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        if ((tmp = strtok(NULL, " "))==NULL)
             return true;
        int id=atoi(tmp);
        DB->QExecute("DELETE from list_spawnareas where id=%i",id);
//		BEGINPACKET( pak, 0x702 );
        char buffer[200];
        sprintf( buffer, "DELETESPAWN %i", id);
        BEGINPACKET ( pak, 0x702 );
        ADDSTRING( pak, buffer );
//		ADDSTRING( pak, "DELETESPAWN" );
		ADDBYTE( pak, 0 );
        thisclient->client->SendPacket(&pak);
        CSpawnArea* thisspawn = GetSpawnArea( id );
        if(thisspawn==NULL)
            return true;
        CMap* map = MapList.Index[thisspawn->map];
        for(UINT i=0;i<map->MonsterList.size();i++)
        {
            CMonster* thismon = map->MonsterList.at(i);
            BEGINPACKET( pak, 0x794 );
            ADDWORD    ( pak, thismon->clientid );
            SendToVisible( &pak, thismon );
            MapList.Index[thisspawn->map]->DeleteMonster( thismon );
        }
        DeleteSpawn( thisspawn );
        Log( MSG_GMACTION, " %s : /deletespawn %i" , thisclient->CharInfo->charname, id);
    }//******************************** FINISH RESPAWN ***************************
    else if(strcmp(command, "p")==0)  //*** READ THE PACKET.TXT AND SEND IT
    {
         if(Config.Command_Pak > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /p NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "p NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
         if ((tmp = strtok(NULL, " "))==NULL)
             return true;
            char buffer;
            std::string filename = "packet/packet";
            filename += tmp;
            filename += ".txt";
            FILE *packet1 = fopen(filename.c_str(),"r");
            if(packet1==NULL)
            {
                printf("Error opening packet.txt!\n");
                return true;
            }
            unsigned int command = 0;
            fread( &command, 1, 2, packet1 );
            BEGINPACKET(pak,command);
            while((fscanf(packet1,"%c",&buffer))!=EOF)
                    ADDBYTE(pak,buffer);
    		thisclient->client->SendPacket( &pak );
            fclose(packet1);
    }
    else if (strcmp(command, "level")==0)
    {
         if(Config.Command_Level > thisclient->Session->accesslevel)
                        return true;
        char* name;
        if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned level=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) name = thisclient->CharInfo->charname; else name = tmp;
        Log( MSG_GMACTION, " %s : /level %i %s" , thisclient->CharInfo->charname, level, name);
        return pakGMLevel( thisclient, level, name );
    }
    else if (strcmp(command, "info")==0)
    {
            if(Config.Command_Info > thisclient->Session->accesslevel)
	                    return true;
            Log( MSG_GMACTION, " %s : /info" , thisclient->CharInfo->charname);
            thisclient->GetPlayerInfo( );
            return true;
	}
    else if (strcmp(command, "exp")==0)
    {
         if(Config.Command_Exp > thisclient->Session->accesslevel)
                        return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned exp=atoi(tmp);
        char* name;
        if ((tmp = strtok(NULL, " "))==NULL)
            name = thisclient->CharInfo->charname;
        else
            name = tmp;
        CPlayer* otherclient = GetClientByCharName( name );
        if (otherclient == NULL)
            return true;
        otherclient->CharInfo->Exp += exp;
        BEGINPACKET( pak, 0x79b );
        ADDDWORD   ( pak, otherclient->CharInfo->Exp );
        ADDWORD    ( pak, otherclient->CharInfo->stamina );
        ADDWORD    ( pak, 0 );
        otherclient->client->SendPacket( &pak );
        Log( MSG_GMACTION, " %s : /exp %i %s" , thisclient->CharInfo->charname, exp, name);
    }
    else if (strcmp(command, "mon")==0) {
         if(Config.Command_Mon > thisclient->Session->accesslevel)
	                    return true;
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned montype=atoi(tmp);
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned moncount=atoi(tmp);
		Log( MSG_GMACTION, " %s : /mon %i,%i" , thisclient->CharInfo->charname, montype, moncount);
		return pakGMMon( thisclient, montype, moncount );
	}
    else if (strcmp(command, "mon2")==0)
    {    //Spawn "x" monsters
         if(Config.Command_Mon2 > thisclient->Session->accesslevel)
	                    return true;
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned montype=atoi(tmp);
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned moncount=atoi(tmp);

		for (int k=0;k<moncount;k++)
	    {
             Log( MSG_GMACTION, " %s : /mon2 %i,%i" , thisclient->CharInfo->charname, montype+k, moncount);
             pakGMMon( thisclient, montype+k, 1 );
        }

		return true;
	}
    else if (strcmp(command, "kick")==0)
    {
        if(Config.Command_Kick > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /kick NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "kick NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
        Log( MSG_GMACTION, " %s : /kick %s" , thisclient->CharInfo->charname, name);
        return pakGMKick( thisclient, name );
    }
    else if (strcmp(command, "job")==0) // *** Change Job *****
    {
         if(Config.Command_Job > thisclient->Session->accesslevel)
	       return true;
               char* tmp;
               if ((tmp = strtok(NULL, " "))==NULL) return true; char* job=tmp;
               Log( MSG_GMACTION, " %s : /job %s" , thisclient->CharInfo->charname, job);
               if(thisclient->CharInfo->Job != 0 || thisclient->Stats->Level<10)
                    return true;
               if(strcmp(job,"soldier")==0)
               {
                    BEGINPACKET(pak, 0x721);
                    ADDWORD    (pak, 0x0004);
                    ADDWORD    (pak, 0x006f);
                    ADDWORD    (pak, 0x0000);
                    thisclient->client->SendPacket(&pak);

                    RESETPACKET( pak, 0x730);
                    ADDBYTE(pak, 0x05);
                    ADDBYTE(pak, 0x00);
                    ADDWORD(pak, 0xf52f);
                    ADDWORD(pak, 0x2964);
                	thisclient->client->SendPacket( &pak );
                    thisclient->CharInfo->Job=111;
               }
               else
               if(strcmp(job,"muse")==0)
               {
                    BEGINPACKET(pak, 0x721);
                    ADDWORD    (pak, 0x0004);
                    ADDWORD    (pak, 0x00D3);
                    ADDWORD    (pak, 0x0000);
                    thisclient->client->SendPacket(&pak);

                    RESETPACKET( pak, 0x730);
                    ADDBYTE(pak, 0x05);
                    ADDBYTE(pak, 0x00);
                    ADDWORD(pak, 0xdc3b);
                    ADDWORD(pak, 0x20cd);
                	thisclient->client->SendPacket( &pak );
                    thisclient->CharInfo->Job=211;
               }
               else
               if(strcmp(job,"hawker")==0)
               {
                     BEGINPACKET(pak, 0x721);
                     ADDWORD    (pak, 0x0004);
                     ADDWORD    (pak, 0x0137);
                     ADDWORD    (pak, 0x0000);
                     thisclient->client->SendPacket(&pak);

                     RESETPACKET( pak, 0x730);
                     ADDBYTE(pak, 0x05);
                     ADDBYTE(pak, 0x00);
                     ADDWORD(pak, 0x1104);
                     ADDWORD(pak, 0x5150);
                	 thisclient->client->SendPacket( &pak );
                     thisclient->CharInfo->Job=311;
               }
               else
               if(strcmp(job,"dealer")==0)
               {
                    BEGINPACKET(pak, 0x721);
                    ADDWORD    (pak, 0x0004);
                    ADDWORD    (pak, 0x019b);
                    ADDWORD    (pak, 0x0000);
                    thisclient->client->SendPacket(&pak);

                    RESETPACKET( pak, 0x730);
                    ADDBYTE(pak, 0x05);
                    ADDBYTE(pak, 0x00);
                    ADDWORD(pak, 0x4c1c);
                    ADDWORD(pak, 0xef69);
                	thisclient->client->SendPacket( &pak );
                    thisclient->CharInfo->Job=411;
          }
     }
     else if (strcmp(command, "set")==0)
     {
        if(Config.Command_Set > thisclient->Session->accesslevel)
                    return true;
        int refine;
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        int id=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            refine = 0;
        else
            refine=atoi(tmp);
        //LMA: why *=16???
        //refine *= 16;
        BEGINPACKET( pak, 0);
        if(EquipList[2].Index[id]!=NULL)
        {
            thisclient->items[2].itemnum = id;
    		thisclient->items[2].itemtype = 2;
    		thisclient->items[2].refine =refine;
    		thisclient->items[2].durability = 50;
    		thisclient->items[2].lifespan = 100;
    		thisclient->items[2].count = 1;
    		thisclient->items[2].stats = 0;
    		thisclient->items[2].socketed = false;
    		thisclient->items[2].appraised = true;
        	thisclient->items[2].gem = 0;
        	thisclient->items[2].sp_value=0;
        	thisclient->items[2].last_sp_value=0;
            thisclient->UpdateInventory( 2 );

    	    RESETPACKET( pak, 0x7a5);
    	    ADDWORD( pak, thisclient->clientid );
    	    ADDWORD( pak, 0x0002);
    	    ADDWORD( pak, id);	// ITEM NUM
    	    ADDWORD( pak, BuildItemRefine( thisclient->items[2] ) );	// REFINE
    	    ADDWORD( pak, thisclient->Stats->Move_Speed );	// REFINE
    	    SendToVisible( &pak,thisclient );
        }
    	if(EquipList[3].Index[id]!=NULL)
    	{
    		thisclient->items[3].itemnum = id;
    		thisclient->items[3].itemtype = 3;
    		thisclient->items[3].refine =refine;
    		thisclient->items[3].durability = 50;
    		thisclient->items[3].lifespan = 100;
    		thisclient->items[3].count = 1;
    		thisclient->items[3].stats = 0;
    		thisclient->items[3].socketed = false;
    		thisclient->items[3].appraised = true;
        	thisclient->items[3].gem = 0;
        	thisclient->items[3].sp_value=0;
        	thisclient->items[3].last_sp_value=0;
            thisclient->UpdateInventory( 3 );

	        RESETPACKET( pak, 0x7a5);
    	    ADDWORD( pak, thisclient->clientid );
    	    ADDWORD( pak, 0x0003);
    	    ADDWORD( pak, id);	// ITEM NUM
    	    ADDWORD( pak, BuildItemRefine( thisclient->items[3] ));	// REFINE
    	    ADDWORD( pak, thisclient->Stats->Move_Speed );	// REFINE
    	    SendToVisible( &pak,thisclient );
        }
        if(EquipList[4].Index[id]!=NULL)
        {
    		thisclient->items[5].itemnum = id;
    		thisclient->items[5].itemtype = 4;
    		thisclient->items[5].refine =refine;
    		thisclient->items[5].durability = 50;
    		thisclient->items[5].lifespan = 100;
    		thisclient->items[5].count = 1;
    		thisclient->items[5].stats = 0;
    		thisclient->items[5].socketed = false;
    		thisclient->items[5].appraised = true;
        	thisclient->items[5].gem = 0;
        	thisclient->items[5].sp_value=0;
        	thisclient->items[5].last_sp_value=0;

            thisclient->UpdateInventory( 4 );

    	    RESETPACKET( pak, 0x7a5);
     	    ADDWORD( pak, thisclient->clientid );
	        ADDWORD( pak, 5);
    	    ADDWORD( pak, id);	// ITEM NUM
    	    ADDWORD( pak, BuildItemRefine( thisclient->items[5] ));	// REFINE
    	    ADDWORD( pak, thisclient->Stats->Move_Speed );	// REFINE 2602
    	    SendToVisible( &pak,thisclient );
        }
        if(EquipList[5].Index[id]!=NULL)
        {
    		thisclient->items[6].itemnum = id;
    		thisclient->items[6].itemtype = 5;
    		thisclient->items[6].refine =refine;
    		thisclient->items[6].durability = 50;
    		thisclient->items[6].lifespan = 100;
    		thisclient->items[6].count = 1;
      		thisclient->items[6].stats = 0;
    		thisclient->items[6].socketed = false;
    		thisclient->items[6].appraised = true;
        	thisclient->items[6].gem = 0;
        	thisclient->items[6].sp_value=0;
        	thisclient->items[6].last_sp_value=0;

            thisclient->UpdateInventory( 6 );

    	    RESETPACKET( pak, 0x7a5);
    	    ADDWORD( pak, thisclient->clientid );
    	    ADDWORD( pak, 6);
    	    ADDWORD( pak, id);	// ITEM NUM
    	    ADDWORD( pak, BuildItemRefine( thisclient->items[6] ));	// REFINE
    	    ADDWORD( pak, thisclient->Stats->Move_Speed);	// REFINE
    	    SendToVisible( &pak,thisclient );
        }
        thisclient->SetStats( );
    }
    else if (strcmp(command, "cha")==0)
    {
         if(Config.Command_Cha > thisclient->Session->accesslevel)
	                    return true;
        int slot;
        int tipo;
        int id;
        int stats;
        int socket;
        int refine;
        if ((tmp = strtok(NULL, " "))==NULL)return true;
        if(strcmp(tmp, "mask")==0)
        {
            slot=1;
            tipo=1;
        }
        else
        if(strcmp(tmp, "cap")==0)
        {
            slot=2;
            tipo=2;
        }
        else
        if(strcmp(tmp, "suit")==0)
        {
            slot=3;
            tipo=3;
        }
        else
        if(strcmp(tmp, "back")==0)
        {
            slot=4;
            tipo=6;
        }
        else
        if(strcmp(tmp, "glov")==0)
        {
            slot=5;
            tipo=4;
        }
        else
        if(strcmp(tmp, "shoe")==0)
        {
            slot=6;
            tipo=5;
        }
        else
        if(strcmp(tmp, "weap")==0)
        {
            slot=7;
            tipo=8;
        }
        else
        if(strcmp(tmp, "shield")==0)
        {
            slot=8;
            tipo=9;
        }
        else
            return true;
        if ((tmp = strtok(NULL, " "))==NULL)return true;
            id=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            stats=0;
        else
            stats=atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            socket=0;
        else
            socket=1;
        if ((tmp = strtok(NULL, " "))==NULL)
            refine=0;
        else
            refine=atoi(tmp);
	   thisclient->items[slot].itemnum = id;
	   thisclient->items[slot].itemtype = tipo;
	   thisclient->items[slot].refine = refine;
	   thisclient->items[slot].durability = 50;
	   thisclient->items[slot].lifespan = 100;
	   thisclient->items[slot].count = 1;
	   thisclient->items[slot].stats = stats;
	   thisclient->items[slot].socketed = socket;
	   thisclient->items[slot].appraised = true;
	   thisclient->items[slot].gem = 0;
	   thisclient->items[slot].sp_value=0;
	   BEGINPACKET( pak, 0x7a5);
	   ADDWORD( pak, thisclient->clientid );
	   ADDWORD( pak, slot);
	   ADDWORD( pak, id);	// ITEM NUM
	   ADDWORD( pak, BuildItemRefine(  thisclient->items[slot] ));	// REFINE
	   ADDWORD( pak, thisclient->Stats->Move_Speed );	// REFINE 2602
	   SendToVisible( &pak,thisclient );

      thisclient->UpdateInventory( slot );
       thisclient->SetStats( );
		return true;
    }
    else if (strcmp(command, "item")==0)//Modified by Hiei (added refine/socket/stats)
    {
         if(Config.Command_Item > thisclient->Session->accesslevel)
	                    return true;
        UINT itemrefine, itemstats, itemls, itemsocket;
        if ((tmp = strtok(NULL, " "))==NULL) return true; UINT itemid =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true; UINT itemtype =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true; UINT itemamount =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            itemrefine =0;
        else
            itemrefine = atoi(tmp)<10?atoi(tmp)*16:9*16;
        if ((tmp = strtok(NULL, " "))==NULL)
            itemls =100;
        else
            itemls = atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            itemsocket =0;
        else
            itemsocket =atoi(tmp)==0?false:true;
        if ((tmp = strtok(NULL, " "))==NULL)
            itemstats =0;
        else
            itemstats =atoi(tmp);
        Log( MSG_GMACTION, " %s : /item %i,%i,%i,%i,%i,%i" , thisclient->CharInfo->charname, itemid, itemtype, itemamount , itemrefine , itemsocket ,itemstats);
        return pakGMItem( thisclient , itemid , itemtype , itemamount , itemrefine , itemls, itemstats , itemsocket );
    }
    else if (strcmp(command, "levelup")==0)
    {
         if(Config.Command_LevelUp > thisclient->Session->accesslevel)
	            return true;
        Log( MSG_GMACTION, " %s : /levelup" , thisclient->CharInfo->charname);
		thisclient->CharInfo->Exp += thisclient->GetLevelEXP();
	}
    else if (strcmp(command, "drop")==0)
    {
         if(Config.Command_Drop > thisclient->Session->accesslevel)
	             return true;
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned itemtype=atoi(tmp);
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned itemid=atoi(tmp);
        Log( MSG_GMACTION, " %s : /drop %i,%i" , thisclient->CharInfo->charname, itemtype, itemid);

		CDrop* thisdrop = new CDrop;
		assert(thisdrop);
		thisdrop->clientid = GetNewClientID();
		thisdrop->type = 2;
		thisdrop->pos.x = thisclient->Position->current.x;
		thisdrop->pos.y = thisclient->Position->current.y;
		thisdrop->posMap = thisclient->Position->Map;
		thisdrop->droptime = time(NULL);

		ClearItem(thisdrop->item);
		thisdrop->item.itemnum = itemid;
		thisdrop->item.itemtype = itemtype;
		thisdrop->item.count = 1;
		thisdrop->item.refine = 0;
		thisdrop->item.durability = 35;
		thisdrop->item.lifespan = 100;
		thisdrop->item.appraised = true;
		thisdrop->item.socketed = false;
		thisdrop->item.stats = 0;
		thisdrop->item.gem = 0;

		thisdrop->amount = 1;
		thisdrop->owner = 0;
		CMap* map = MapList.Index[thisdrop->posMap];
		map->AddDrop( thisdrop );
	}
    else if(strcmp(command, "givezuly")==0)
    {
         if(Config.Command_GiveZuly > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
		if((tmp = strtok(NULL, " "))==NULL) return true; int zuly=atoi(tmp);
        Log( MSG_GMACTION, " %s : /givezuly %s, %i" , thisclient->CharInfo->charname, name, zuly);
		  return pakGMZulygive(thisclient, name, zuly);
	}
    else if(strcmp(command, "npc")==0)
    {
         if(Config.Command_Npc > thisclient->Session->accesslevel)
	                    return true;
		if((tmp = strtok(NULL, " "))==NULL) return true; unsigned npcid=atoi(tmp);
		unsigned npcdialog = 0;
		unsigned eventid=0;
		if((tmp = strtok(NULL, " "))!=NULL)
            npcdialog=atoi(tmp);
		if((tmp = strtok(NULL, " "))!=NULL)
            eventid=atoi(tmp);
        Log( MSG_GMACTION, " %s : /npc %i, %i" , thisclient->CharInfo->charname, npcid, npcdialog);
        return pakGMNpc(thisclient, npcid, npcdialog,eventid);
	}
    else if(strcmp(command, "giveclanrp")==0)
    {
         if(Config.Command_GiveClanRp > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
	    if((tmp = strtok(NULL, " "))==NULL) return true; int points=atoi(tmp);
	    Log( MSG_GMACTION, " %s : /giveclanrp %s, %i" , thisclient->CharInfo->charname, name, points);
	    return pakGMClanRewardPoints(thisclient, name, points);
	}
    else if(strcmp(command, "giveclanp")==0)
    {
         if(Config.Command_GiveClanp > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
	    if((tmp = strtok(NULL, " "))==NULL) return true; int points=atoi(tmp);
	    Log( MSG_GMACTION, " %s : /giveclanp %s, %i" , thisclient->CharInfo->charname, name, points);
	    return pakGMClanPoints(thisclient, name, points);
	}
    else if(strcmp(command, "givefairy")==0)
    {
         if(Config.Command_GiveFairy > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned mode=atoi(tmp);
	    Log( MSG_GMACTION, " %s : /givefairy %s, %i" , thisclient->CharInfo->charname, name, mode);
	    return pakGMFairyto(thisclient, name, mode);
	}
    else if(strcmp(command, "hurthim")==0)
    {
         if(Config.Command_HurtHim > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
	    Log( MSG_GMACTION, " %s : /hurthim %s" , thisclient->CharInfo->charname, name);
	    return pakGMHurtHim(thisclient, name);
	}
	else if(strcmp(command, "fairymode")==0)
    {
        if(Config.Command_ManageFairy > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned mode=atoi(tmp);
	    Log( MSG_GMACTION, " %s : /fairymode mode: %i" , thisclient->CharInfo->charname, mode);
	    return pakGMManageFairy(thisclient, mode);
	}
	else if(strcmp(command, "fairywait")==0)
    {
        if(Config.Command_ChangeFairyWait > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned value=atoi(tmp);
	    Log( MSG_GMACTION, " %s : /fairywait value: %i" , thisclient->CharInfo->charname, value);
	    return pakGMChangeFairyWait(thisclient, value);
	}
	else if(strcmp(command, "fairystay")==0)
    {
        if(Config.Command_ChangeFairyStay > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned value=atoi(tmp);
	    Log( MSG_GMACTION, " %s : /fairystay value: %i" , thisclient->CharInfo->charname, value);
	    return pakGMChangeFairyStay(thisclient, value);
	}
	else if(strcmp(command, "fairytestmode")==0)
    {
        if(Config.Command_ChangeFairyTestMode > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned mode=atoi(tmp);
	    Log( MSG_GMACTION, " %s : /fairytestmode mode: %i" , thisclient->CharInfo->charname, mode);
	    return pakGMChangeFairyTestMode(thisclient, mode);
	}
    else if (strcmp(command, "move")==0)
    {
         if(Config.Command_Move > thisclient->Session->accesslevel)
	                    return true;
		if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
		if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned map=atoi(tmp);
		if ((tmp = strtok(NULL, " "))==NULL) return true; float x=(float)atoi(tmp);
		if ((tmp = strtok(NULL, " "))==NULL) return true; float y=(float)atoi(tmp);
		Log( MSG_GMACTION, " %s : /move %s,%i,%i,%i" , thisclient->CharInfo->charname, name, map, x, y);
		return pakGMTeleOtherPlayer(thisclient, name, map, x, y);
	}
    else if (strcmp(command, "goto")==0)
    {
         if(Config.Command_Goto > thisclient->Session->accesslevel)
	                    return true;
		if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
// added to prevent map changes with less hp than 1/2
        if ( thisclient->Stats->HP < (thisclient->Stats->MaxHP / 2) || thisclient->Session->inGame == false )
        {
             SendPM(thisclient, "You need at least 50% HP in order to warp");
             return true;
        }
		Log( MSG_GMACTION, " %s : /goto %s" , thisclient->CharInfo->charname, name);
		return pakGMTeleToPlayer(thisclient, name);
	}
    else if (strcmp(command, "teletome")==0)
    {
         if(Config.Command_TeleToMe > thisclient->Session->accesslevel)
	                    return true;
		if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
		Log( MSG_GMACTION, " %s : /teletome %s" , thisclient->CharInfo->charname, name);
        if(strcmp(name,"all")==0)
        {
            return pakGMTeleAllHere(thisclient);
        }
		return pakGMTelePlayerHere(thisclient, name);
    }
    else if(strcmp(command, "CharInfo")==0)
    {
         if(Config.Command_Item > thisclient->Session->accesslevel)
	                    return true;
			if((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
			Log( MSG_GMACTION, " %s : /CharInfo %s" , thisclient->CharInfo->charname, name);
			return pakGMInfo(thisclient, name);
	}
else if (strcmp(command, "give2")==0)
{
             if(Config.Command_Item > thisclient->Session->accesslevel)
                      return true;
        UINT itemrefine, itemstats, itemls, itemsocket;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
        if ((tmp = strtok(NULL, " "))==NULL) return true; UINT itemid =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true; UINT itemtype =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true; UINT itemamount =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            itemrefine =0;
        else
            itemrefine = atoi(tmp)<10?atoi(tmp)*16:9*16;
        if ((tmp = strtok(NULL, " "))==NULL)
            itemls =100;
        else
            itemls = atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL)
            itemsocket =0;
        else
            itemsocket =atoi(tmp)==0?false:true;
        if ((tmp = strtok(NULL, " "))==NULL)
            itemstats =0;
        else
            itemstats =atoi(tmp);
        Log( MSG_GMACTION, " %s : /give2 %s,%i,%i,%i,%i,%i,%i,%i" , thisclient->CharInfo->charname, name, itemid , itemtype , itemamount , itemrefine , itemls, itemstats , itemsocket);
        return pakGMItemtoplayer( thisclient , name , itemid , itemtype , itemamount , itemrefine , itemls, itemstats , itemsocket );
}
    else if (strcmp(command, "ban")==0)
    {
         if(Config.Command_Ban > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /ban NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "ban NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
        Log( MSG_GMACTION, " %s : /ban %s" , thisclient->CharInfo->charname, name);
        return pakGMBan( thisclient, name );
	}
    else if (strcmp(command, "ani")==0)
    {
         if(Config.Command_Ani > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned anid =atoi(tmp);
            Log( MSG_GMACTION, " %s : /ani %i" , thisclient->CharInfo->charname, anid);
            pakGMDoEmote( thisclient, anid );
    }
    else if (strcmp(command, "fskill")==0)
    {
         //forcing a skill (for test)
         if(Config.Command_fskill > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned monstertype =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned skilltype =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned skillvalue =atoi(tmp);
        fmmonstertype=monstertype;         //montype
        ftypeskill=skilltype;              //1=attack, 2=debuff, 3=self buff
        fskill=skillvalue;                 //skill value.
        Log( MSG_GMACTION, " %s : /fskill monter %i type %i skill %i" , thisclient->CharInfo->charname, monstertype,skilltype,skillvalue);
        return true;
    }
    else if(strcmp(command,"summon")==0)
    {
        if(Config.Command_Summon > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        unsigned int summon = atoi(tmp);
        Log( MSG_GMACTION, " %s : /summon %i" , thisclient->CharInfo->charname, summon);
        fPoint position = RandInCircle( thisclient->Position->current, 5 );
        CMap* map = MapList.Index[thisclient->Position->Map];
        map->AddMonster( summon, position, thisclient->clientid );
        //Start Animation
        BEGINPACKET( pak, 0x7b2 );
        ADDWORD    ( pak, thisclient->clientid );
        ADDWORD    ( pak, 2802 );
        SendToVisible( &pak, thisclient );
        //Finish Animation
        RESETPACKET( pak, 0x7bb );
        ADDWORD    ( pak, thisclient->clientid );
        SendToVisible( &pak, thisclient );
        //????
        RESETPACKET( pak, 0x7b9);
        ADDWORD    ( pak, thisclient->clientid);
        ADDWORD    ( pak, 1286 );
	    SendToVisible( &pak, thisclient );
	    // Add our Mob to the mobs list
    }
    else if (strcmp(command, "reloadquest")==0)
    {
         if(Config.Command_ReloadQuest > thisclient->Session->accesslevel)
	                    return true;
        QuestList.clear( );
        LoadQuestData( );
        Log( MSG_GMACTION, " %s : /reloadquest" , thisclient->CharInfo->charname);
        return true;
    }
	else if (strcmp(command, "shutdown")==0)
	{
             if(Config.Command_Shutdown > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /showdown NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "shutdown NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned int minutes =atoi(tmp);
        char text[200];
        sprintf( text, "Server will shutdown in %i minutes, Please logout NOW to be sure your information is saved correctly.",
           minutes );
        BEGINPACKET( pak, 0x702 );
	    ADDSTRING  ( pak, thisclient->CharInfo->charname );
    	ADDSTRING  ( pak, "> " );
    	ADDSTRING  ( pak, text );
    	ADDBYTE    ( pak, 0x00 );
    	SendToAll  ( &pak );
        pthread_create( &WorldThread[SHUTDOWN_THREAD], NULL, ShutdownServer, (PVOID)minutes);
        Log( MSG_GMACTION, " %s : /shutdown %u" , thisclient->CharInfo->charname, shutdown);
    }
    else if(strcmp(command, "dquest")==0)
    {
         if(Config.Command_DQuest > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /dquest NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "dquest NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        char line0[200];

        if( thisclient->questdebug )
        {
            Log(MSG_INFO,"Quest Debug deactivated");
            sprintf(line0, "Quest Debug deactivated");
            thisclient->questdebug = false;
        }
        else
        {
            Log(MSG_INFO,"Quest Debug activated");
            sprintf(line0, "Quest Debug activated");
            thisclient->questdebug = true;
        }

        SendPM(thisclient, line0 );
    }
    else if(strcmp(command, "debugmode")==0)
    {
        if(thisclient->Session->accesslevel <= 100)
	                    return true;
        char buffer2[200];
        if( thisclient->Session->codedebug )
        {
            thisclient->Session->codedebug = false;

            sprintf ( buffer2, "Debug Mode disabled" );
            SendPM(thisclient, buffer2);
        }
        else
        {
            thisclient->Session->codedebug = true;
            sprintf ( buffer2, "Debug Mode enabled" );
            SendPM(thisclient, buffer2);
        }
        return true;
    }
    else if(strcmp(command, "iquest")==0)
    {
         if(Config.Command_IQuest > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /iquest NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "iquest NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        int n=1;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        unsigned int itemquest =atoi(tmp);
        if ((tmp = strtok(NULL, " "))!=NULL)
            n=atoi(tmp);
        if( thisclient->questdebug )
        {
            for(int i=0;i<n;i++)
            {
                BEGINPACKET( pak, 0x731 )
                ADDWORD    ( pak, itemquest );
                thisclient->client->SendPacket( &pak );
            }
        }
    }
    else if(strcmp(command, "addquest")==0)
    {

        if(Config.Command_Addquest > thisclient->Session->accesslevel)
	         return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        unsigned int questnum =atoi(tmp);
                Log( MSG_GMACTION, "add quest %i" , questnum);
        for(int i=0;i<10;i++)
            {
                if (thisclient->quest.quests[i].QuestID != 0) continue;
                    thisclient->quest.quests[i].QuestID = questnum;
                    thisclient->quest.quests[i].StartTime = clock_t();
                Log( MSG_GMACTION, "quest added %i" , thisclient->quest.quests[i].QuestID);
                break;
            }
    }
    else if(strcmp(command, "listquest")==0)
    {

        if(Config.Command_Listquest > thisclient->Session->accesslevel)
	         return true;
        SendPM( thisclient, "Current Quests:" );
        for(int i=0;i<10;i++)
            {
              if (thisclient->quest.quests[i].QuestID == 0) continue;
                SendPM( thisclient, "Quest[%i]: %i[%i] %i[%i] %i[%i] %i[%i] %i[%i]" , thisclient->quest.quests[i].QuestID, thisclient->quest.quests[i].Items[0].itemnum, thisclient->quest.quests[i].Items[0].count, thisclient->quest.quests[i].Items[1].itemnum, thisclient->quest.quests[i].Items[1].count, thisclient->quest.quests[i].Items[2].itemnum,thisclient->quest.quests[i].Items[2].count,thisclient->quest.quests[i].Items[3].itemnum,thisclient->quest.quests[i].Items[3].count,thisclient->quest.quests[i].Items[4].itemnum,thisclient->quest.quests[i].Items[4].count);
            }
    }
    else if(strcmp(command, "listqflag")==0)
    {
      if(Config.Command_Listqflag > thisclient->Session->accesslevel)
        return true;
      SendPM(thisclient, "Quest Flags");
      string buffer = "";
      for (dword i = 0; i < 0x40; i++) {
        char buf2[5];
        sprintf(buf2, "%i ", thisclient->quest.flags[i]);
        buffer.append(buf2);
//        if (i > 0 && i%10 == 0) {
        if ((i + 1) % 10 == 0) {
          SendPM(thisclient, (char*)buffer.c_str());
          buffer = "";
        }
      }
      SendPM(thisclient, (char*)buffer.c_str());
    }
    else if(strcmp(command, "Setqflag")==0)
    {
      if(Config.Command_Setqflag > thisclient->Session->accesslevel)
        return true;
      if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned int var = atoi(tmp);
      if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned int val = atoi(tmp);
      if (var >= (0x40 * 8)) return true;
      thisclient->quest.SetFlag(var, (val > 0) ? true : false);
      SendPM( thisclient, "Set Flag[%i] = %i", var, val);
    }
    else if(strcmp(command, "listqvar")==0)
    {
      if(Config.Command_Listqvar > thisclient->Session->accesslevel)
        return true;
        SendPM( thisclient, "Quest Variables");

        string buffer = "Episode: ";
        for(dword i = 0; i < 5; i++) {
          char buf2[5];
          sprintf(buf2, "%02x ", thisclient->quest.EpisodeVar[i]);
          buffer.append(buf2);
        }
        SendPM( thisclient, (char*)buffer.c_str() );

        buffer = "Job: ";
        for(dword i = 0; i < 3; i++) {
          char buf2[5];
          sprintf(buf2, "%02x ", thisclient->quest.JobVar[i]);
          buffer.append(buf2);
        }
        SendPM( thisclient, (char*)buffer.c_str());

        buffer = "Planet: ";
        for(dword i = 0; i < 7; i++) {
          char buf2[5];
          sprintf(buf2, "%02x ", thisclient->quest.PlanetVar[i]);
          buffer.append(buf2);
        }
        SendPM( thisclient, (char*)buffer.c_str());

        buffer = "Union: ";
        for(dword i = 0; i < 10; i++) {
          char buf2[5];
          sprintf(buf2, "%02x ", thisclient->quest.UnionVar[i]);
          buffer.append(buf2);
            }
        SendPM( thisclient, (char*)buffer.c_str());

        for (dword j = 0; j < 10; j++) {
        if (thisclient->quest.quests[j].QuestID == 0) continue;
        buffer = "Quest: ";
          for(dword i = 0; i < 10; i++) {
            char buf2[5];
            sprintf(buf2, "%02x ", thisclient->quest.quests[j].Variables[i]);
            buffer.append(buf2);
          }
          SendPM( thisclient, (char*)buffer.c_str());
        }
    }
    else if(strcmp(command, "setqvar")==0)
    {
      if(Config.Command_Setqvar > thisclient->Session->accesslevel)
        return true;
      if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned int vartype = atoi(tmp);
      if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned int var = atoi(tmp);
      if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned int val = atoi(tmp);
      if (vartype > 3) return true;
      switch (vartype) {
        case 0:
          if (var >= 5) return true;
          thisclient->quest.EpisodeVar[var] = val;
        break;
        case 1:
          if (var >= 3) return true;
          thisclient->quest.JobVar[var] = val;
        break;
        case 2:
          if (var >= 7) return true;
          thisclient->quest.PlanetVar[var] = val;
        break;
        case 3:
          if (var >= 10) return true;
          thisclient->quest.UnionVar[var] = val;
        break;
      }
      SendPM( thisclient, "Set Var[%i][%i] = %i", vartype, var, val);
    }
	else if (strcmp(command, "shoptype")==0)
	{
         if(Config.Command_ShopType > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
            unsigned int shoptype =atoi(tmp);
        thisclient->Shop->ShopType = shoptype;
        Log( MSG_GMACTION, " %s : /shoptype %i" , thisclient->CharInfo->charname, shoptype);
    }
	else if (strcmp(command, "bonusxp")==0)
	{
         if(Config.Command_BonusXp > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        char* name = tmp;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        unsigned int bonus =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        unsigned int time_min =atoi(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        unsigned int to_save =atoi(tmp);

        CPlayer* otherclient = GetClientByCharName(name);
        if (otherclient == NULL)
            return true;

        char buffer2[200];
        if (bonus==0)
        {
           otherclient->bonusxp=1;
           otherclient->timerxp=0;
           otherclient->wait_validation=0;
           otherclient->Saved=false;
            sprintf ( buffer2, "Your Bonus Xp has been deactivated.");
            SendPM(otherclient, buffer2);
        }
        else
        {
           otherclient->bonusxp=bonus;
           otherclient->wait_validation=0;
           //otherclient->timerxp=clock()+time_min*60*1000;
           otherclient->timerxp=time(NULL)+time_min*60;
           otherclient->Saved=false;
           if (to_save!=0)
              otherclient->Saved=true;
            sprintf ( buffer2, "You have a bonus xp (*%i) for %i minutes.",bonus,time_min);
            SendPM(otherclient, buffer2);
        }

        Log( MSG_GMACTION, " %s : /bonusxp %s %i %i %i" ,thisclient->CharInfo->charname, otherclient->CharInfo->charname,bonus,time_min,to_save );
        return true;
    }
    else if (strcmp(command, "stat")==0) /// Code By Minoc
    {
         if(Config.Command_Stat > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* statname =(char*)tmp;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int statvalue    = atoi(tmp);
        if (statvalue > Config.MaxStat)  /// code by PurpleYouko for setting max stat to 300
            statvalue = Config.MaxStat;  /// extra code to match setting in worldserver.conf by Atomsk
        Log( MSG_GMACTION, " %s : /stat %s %i" , thisclient->CharInfo->charname, statname, statvalue);
        return pakGMStat( thisclient , statname , statvalue);
    }
    else if (strcmp(command, "statp")==0)
    {
        if (Config.Command_Stat > thisclient->Session->accesslevel)
            return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int statvalue = atoi(tmp);
        char* name;
        if ((tmp = strtok(NULL, " "))==NULL)
            name = thisclient->CharInfo->charname;
        else
            name = tmp;
        CPlayer* otherclient = GetClientByCharName(name);
        if (otherclient == NULL)
            return true;
        if ((int)otherclient->CharInfo->StatPoints + statvalue < 0)
            otherclient->CharInfo->StatPoints = 0;
        else
            otherclient->CharInfo->StatPoints += statvalue;
        BEGINPACKET( pak, 0x720 );
        ADDWORD( pak, 32 );
        ADDWORD( pak, statvalue );
        ADDWORD( pak, 0 );
        otherclient->client->SendPacket( &pak );
        RESETPACKET( pak, 0x0730 );
        ADDWORD( pak, 5 );
        ADDWORD( pak, 0xa24d );
        ADDWORD( pak, 0x40b3 );
        otherclient->client->SendPacket( &pak );
        Log(MSG_GMACTION, " %s : /stats %i %s", thisclient->CharInfo->charname, statvalue, name);
        return true;
    }
    else if (strcmp(command, "skillp")==0)
    {
        if (Config.Command_Stat > thisclient->Session->accesslevel)
            return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int skillp = atoi(tmp);
        char* name;
        if ((tmp = strtok(NULL, " "))==NULL)
            name = thisclient->CharInfo->charname;
        else
            name = tmp;
        CPlayer* otherclient = GetClientByCharName(name);
        if (otherclient == NULL)
            return true;
        if ((int)otherclient->CharInfo->SkillPoints + skillp < 0)
            otherclient->CharInfo->SkillPoints = 0;
        else
            otherclient->CharInfo->SkillPoints += skillp;
        BEGINPACKET( pak, 0x720 );
        ADDWORD( pak, 37 );
        ADDWORD( pak, skillp );
        ADDWORD( pak, 0 );
        otherclient->client->SendPacket( &pak );
        RESETPACKET( pak, 0x0730 );
        ADDWORD( pak, 5 );
        ADDWORD( pak, 0xa24d );
        ADDWORD( pak, 0x40b3 );
        otherclient->client->SendPacket( &pak );
        Log(MSG_GMACTION, " %s : /skillp %i %s", thisclient->CharInfo->charname, skillp, name);
        return true;
    }
    else if (strcmp(command, "killinrange")==0)
    {
        if(Config.Command_KillInRange > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned range=atoi(tmp);
        Log( MSG_GMACTION, " %s : /killinrange %i" , thisclient->CharInfo->charname, range);
        return pakGMKillInRange( thisclient, range );
    }
    else if (strcmp(command, "gotomap")==0) // *** TELEPORT WITH MAP ID *****
	{	 // credits to Blackie
	   if(Config.Command_GoToMap > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; unsigned map=atoi(tmp);
// added to prevent map changes with less hp than 1/2
        if ( thisclient->Stats->HP < (thisclient->Stats->MaxHP / 2) || thisclient->Session->inGame == false )
        {
             SendPM(thisclient, "You need at least 50% HP in order to warp");
             return true;
        }
        SendPM(thisclient, "Go to map: %i",map);
        Log( MSG_GMACTION, " %s : /gotomap %i" , thisclient->CharInfo->charname, map);
		return pakGMGotomap(thisclient, map);
    }
    else if(strcmp(command, "heal")==0)
    {
        if(Config.Command_Heal > thisclient->Session->accesslevel)
	                    return true;
        Log( MSG_GMACTION, " %s : /heal", thisclient->CharInfo->charname );
        return pakGMHeal( thisclient );
    }
    else if(strcmp(command, "serverinfo")==0)
    {
         if(Config.Command_ServerInfo > thisclient->Session->accesslevel)
	                    return true;
        Log( MSG_GMACTION, " %s : /serverinfo" , thisclient->CharInfo->charname);
		return pakGMServerInfo( thisclient );
    }
    else if(strcmp(command, "targetinfo")==0)
    {
         if(Config.Command_TargetInfo > thisclient->Session->accesslevel)
	                    return true;
        return GMShowTargetInfo( thisclient );
    }
    else if (strcmp(command, "hide")==0)
    {
         if(Config.Command_Hide > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        int mode= atoi( tmp );
        return pakGMHide( thisclient, mode );
    }
    else if (strcmp(command, "class")==0)
    {
         if(Config.Command_Class > thisclient->Session->accesslevel)
	                    return true;
        if ((tmp = strtok(NULL, " "))==NULL)
            return true;
        char* classid=(char*)tmp;
        Log( MSG_GMACTION, " %s : /class %s" , thisclient->CharInfo->charname, classid);
        return pakGMClass( thisclient, classid );
    }
    else if(strcmp(command, "convert")==0)
    {
        if(Config.Command_Convert > thisclient->Session->accesslevel)
	       return true;
	    if(thisclient->Battle->target==0) return true;
        if ((tmp = strtok(NULL, " " ))==NULL)
            return true;
        UINT newmon = atoi(tmp);
        if(newmon==0) return true;
        CMonster* thismon = GetMonsterByID( thisclient->Battle->target, thisclient->Position->Map );
        if(thismon==NULL)
        {
            CNPC* thisnpc = GetNPCByID( thisclient->Battle->target, thisclient->Position->Map );
            if(thisnpc==NULL) return true;
            MapList.Index[thisclient->Position->Map]->ConverToMonster( thisnpc, newmon );
        }
        else
        {
            MapList.Index[thisclient->Position->Map]->ConverToMonster( thismon, newmon );
        }
        return true;
    }
    else if (strcmp(command, "b")==0)
    {
        if(Config.Command_Broadcast > thisclient->Session->accesslevel)
            return true;
        time_t seconds;
        seconds = time (NULL);
        if((thisclient->CharInfo->LastGlobal+Config.Command_GlobalTime) <= seconds)
        {
            thisclient->CharInfo->LastGlobal = time (NULL);
            char outputmsg[200];
            sprintf( outputmsg, "%s %s", Config.Command_GlobalPrefix, &P->Buffer[3] );
            Log( MSG_INFO, "%s> %s %s", thisclient->CharInfo->charname, Config.Command_GlobalPrefix, &P->Buffer[3]);
            SendGlobalMSG(thisclient, outputmsg);
        }
        else
        {
            long int remaining = (Config.Command_GlobalTime-(seconds-thisclient->CharInfo->LastGlobal));
            char buffer2[200];
            sprintf ( buffer2, "Please wait %i seconds before sending another global message.", remaining );
            SendPM(thisclient, buffer2);
        }
        return true;
    }
    else if(strcmp(command, "who2")==0)
    {
        if(Config.Command_Who2 > thisclient->Session->accesslevel)
            return true;
        SendPM(thisclient, "The following players are currently connected;");
        int count=1;
        int hiddenam=0;
        char line0[200];
        while(count <= (ClientList.size()-1))
        {
            CPlayer* whoclient = (CPlayer*)ClientList.at(count)->player;
            if(whoclient->Session->accesslevel > 100)
            {
//                sprintf(line0, "%s - GM[%i]", whoclient->CharInfo->charname, whoclient->Session->accesslevel);
                sprintf(line0, "%s - (GM %i, lvl %u), map %u[%.2f,%.2f]", whoclient->CharInfo->charname, whoclient->Session->accesslevel,
                whoclient->Stats->Level,
                whoclient->Position->Map,
                whoclient->Position->current.x,
                whoclient->Position->current.y);

            }
            else
            {
//                sprintf(line0, "%s", whoclient->CharInfo->charname);

        sprintf(line0, "%s (job %u, lvl %u), map %u[%.2f,%.2f]", whoclient->CharInfo->charname,
        whoclient->CharInfo->Job,
        whoclient->Stats->Level,
        whoclient->Position->Map,
        whoclient->Position->current.x,
        whoclient->Position->current.y);

            }
            if(!whoclient->isInvisibleMode || thisclient->Session->accesslevel >= whoclient->Session->accesslevel)
            {
                SendPM(thisclient, line0 );
            }
            else
            {
                hiddenam++;
            }
            count++;
        }
        sprintf(line0, "There are currently %i players connected!", ((ClientList.size()-1)-hiddenam));
        Log( MSG_GMACTION, " %s : /who2" , thisclient->CharInfo->charname);


        return true;
    }
    else if(strcmp(command, "rate")==0) //incomplete
    {
        if(Config.Command_Rate > thisclient->Session->accesslevel)
           return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        char* type = tmp;
        if(strcmp(type,"drop")==0)
        {
            if ((tmp = strtok(NULL, " "))==NULL) return true;
            Config.DROP_RATE = atoi(tmp);
        }
        else
        if(strcmp(type,"exp")==0)
        {
            if ((tmp = strtok(NULL, " "))==NULL) return true;
            Config.EXP_RATE = atoi(tmp);
        }
    }
    else if(strcmp(command, "moveto")==0)
    {
        if(Config.Command_Moveto > thisclient->Session->accesslevel)
            return true;
        fPoint position;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        position.x = atof(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        position.y = atof(tmp);
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        position.z = atof(tmp);
        pakGMMoveTo( thisclient, position );
    }
    else if (strcmp(command, "refine")==0)
    {
        if(Config.Command_Refine > thisclient->Session->accesslevel)
            return true;
        if ((tmp = strtok(NULL, " "))==NULL)return true;
        int slot = 7; //defaults to weapon
        int tipo;
        int itemrefine;
        if(strcmp(tmp, "mask")==0)
        {
            slot=1;
        }
        else
        if(strcmp(tmp, "cap")==0)
        {
            slot=2;
        }
        else
        if(strcmp(tmp, "suit")==0)
        {
            slot=3;
        }
        else
        if(strcmp(tmp, "back")==0)
        {
            slot=4;
        }
        else
        if(strcmp(tmp, "glov")==0)
        {
            slot=5;
        }
        else
        if(strcmp(tmp, "shoe")==0)
        {
            slot=6;
        }
        else
        if(strcmp(tmp, "weap")==0)
        {
            slot=7;
        }
        else
        if(strcmp(tmp, "shield")==0)
        {
            slot=8;
        }
        if ((tmp = strtok(NULL, " "))==NULL)
            itemrefine =0;
        else
            itemrefine = atoi(tmp)<10?atoi(tmp)*16:9*16;
        thisclient->items[slot].refine = itemrefine;

        BEGINPACKET( pak, 0x7a5);
	    ADDWORD( pak, thisclient->clientid );
	    ADDWORD( pak, slot);
	    ADDWORD( pak, thisclient->items[slot].itemnum);	// ITEM NUM
	    ADDWORD( pak, BuildItemRefine(  thisclient->items[slot] ));	// REFINE
	    ADDWORD( pak, thisclient->Stats->Move_Speed );	// REFINE 2602
	    SendToVisible( &pak,thisclient );

        thisclient->UpdateInventory( slot );
        thisclient->SetStats( );
		return true;
    }
    else if(strcmp(command, "settime")==0)
    {
        if(Config.Command_Settime > thisclient->Session->accesslevel)
            return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true;
        unsigned int time = atoi(tmp);
        if(MapList.Index[thisclient->Position->Map]!=NULL)
        {
            switch(time)
            {
                case MORNING:
                    MapList.Index[thisclient->Position->Map]->MapTime = MapList.Index[thisclient->Position->Map]->morningtime;
                    SendSysMsg( thisclient, "Time changed!, rejoin to see change [MORNING]" );
                break;
                case DAY:
                    MapList.Index[thisclient->Position->Map]->MapTime = MapList.Index[thisclient->Position->Map]->daytime;
                    SendSysMsg( thisclient, "Time changed!, rejoin to see change [DAY]" );
                break;
                case EVENING:
                    MapList.Index[thisclient->Position->Map]->MapTime = MapList.Index[thisclient->Position->Map]->eveningtime;
                    SendSysMsg( thisclient, "Time changed!, rejoin to see change [EVENING]" );
                break;
                case NIGHT:
                    MapList.Index[thisclient->Position->Map]->MapTime = MapList.Index[thisclient->Position->Map]->nighttime;
                    SendSysMsg( thisclient, "Time changed!, rejoin to see change [NIGHT]" );
                break;
                default:
                    SendSysMsg( thisclient, "Time: 0=MORNING | 1=DAY | 2=EVENING | 3=NIGHT" );
            }
        }
    }
    else if(strcmp(command, "transx")==0)
    {
        if(Config.Command_Transx > thisclient->Session->accesslevel)
            return true;
        thisclient->CharInfo->Sex = thisclient->CharInfo->Sex==0?1:0;
        BEGINPACKET( pak, 0x720 );
        ADDWORD( pak, 2 );
        ADDWORD( pak, thisclient->CharInfo->Sex );
        ADDWORD( pak, 0 );
        thisclient->client->SendPacket( &pak );
        RESETPACKET( pak, 0x0730 );
        ADDWORD( pak, 5 );
        ADDWORD( pak, 0xa24d );
        ADDWORD( pak, 0x40b3 );
        thisclient->client->SendPacket( &pak );
    }
    /*
    else if (strcmp(command, "killunion")==0)
    {
        if(Config.Command_Partylvl > thisclient->Session->accesslevel)
	       return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int type_union= atoi( tmp );
        if ((tmp = strtok(NULL, " "))==NULL) return true; int kill_union= atoi( tmp );
        if ((tmp = strtok(NULL, " "))==NULL) return true; int test_union= atoi( tmp );

        Log( MSG_GMACTION, "killUnion type %i, value %i, loop or key %i by %s" ,type_union,kill_union, test_union, thisclient->CharInfo->charname);

        //LMA: changing union kill :)
        //28 00 d0 8a ff ff
        if (type_union==1)
        {
            BEGINPACKET( pak, 0x720 );
            ADDWORD( pak, test_union );
            ADDWORD( pak, kill_union );
            //ADDWORD( pak, 0xFFFF );
            ADDWORD( pak, 0x0 );
            thisclient->client->SendPacket( &pak );
            RESETPACKET( pak, 0x0730 );
            ADDWORD( pak, 5 );
            ADDWORD( pak, 0xa24d );
            ADDWORD( pak, 0x40b3 );
            thisclient->client->SendPacket( &pak );
            char buffer[200];
            sprintf ( buffer, "killUnion 720 set to %i, test %i by %s" , kill_union, test_union, thisclient->CharInfo->charname);
            SendPM(thisclient, buffer);

            return true;
        }

        if (type_union==101)
        {

            Log(MSG_INFO,"721, test_union %i, value %i",test_union,kill_union);
            for (int k=10;k<test_union;k++)
            {
                BEGINPACKET( pak, 0x721 );
                RESETPACKET( pak, 0x721 );
                ADDWORD( pak, k );
                ADDWORD( pak, kill_union );
                ADDWORD( pak, 0x0000 );
                thisclient->client->SendPacket( &pak );
            	RESETPACKET( pak, 0x730 );
                ADDWORD    ( pak, 0x0005 );
                ADDDWORD   ( pak, 0x40b3a24d );
                thisclient->client->SendPacket( &pak );
                Log(MSG_INFO,"killUnion 721 set to %i, key %i by %s" , kill_union, k, thisclient->CharInfo->charname);
                //char buffer[200];
                //sprintf ( buffer, "killUnion 721 set to %i, test %i by %s" , kill_union, k, thisclient->CharInfo->charname);
                //SendPM(thisclient, buffer);
            }

            return true;
        }

        if (type_union==102)
        {

            for (int k=10;k<test_union;k++)
            {
                BEGINPACKET( pak, 0x720 );
                ADDWORD( pak, k );
                ADDWORD( pak, kill_union );
                //ADDWORD( pak, 0xFFFF );
                ADDWORD( pak, 0x0 );
                thisclient->client->SendPacket( &pak );
                RESETPACKET( pak, 0x0730 );
                ADDWORD( pak, 5 );
                ADDWORD( pak, 0xa24d );
                ADDWORD( pak, 0x40b3 );
                thisclient->client->SendPacket( &pak );
                Log(MSG_INFO,"killUnion 720 set to %i, key %i by %s" , kill_union, k, thisclient->CharInfo->charname);
                //char buffer[200];
                //sprintf ( buffer, "killUnion 720 set to %i, test %i by %s" , kill_union, k, thisclient->CharInfo->charname);
                //SendPM(thisclient, buffer);
            }

            return true;
        }

        BEGINPACKET( pak, 0x721 );
        ADDWORD( pak, test_union );
        ADDWORD( pak, kill_union );
        ADDWORD( pak, 0x0000 );
        thisclient->client->SendPacket( &pak );
    	RESETPACKET( pak, 0x730 );
        ADDWORD    ( pak, 0x0005 );
        ADDDWORD   ( pak, 0x40b3a24d );
        thisclient->client->SendPacket( &pak );

       char buffer[200];
       sprintf ( buffer, "killUnion 721 set to %i, test %i by %s" , kill_union, test_union, thisclient->CharInfo->charname);
       SendPM(thisclient, buffer);


        return true;
    }*/
    else if (strcmp(command, "union")==0)
    {
        if(Config.Command_Union > thisclient->Session->accesslevel)
	       return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; char* name=tmp;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int which_union= atoi( tmp );
        return pakGMUnion(thisclient,name,which_union);
    }
    else if (strcmp(command, "partylvl")==0)
    {
        if(Config.Command_Partylvl > thisclient->Session->accesslevel)
	       return true;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int level= atoi( tmp );
        return pakGMPartylvl( thisclient, level );
    }
    else if(strcmp(command, "pdmg")==0)
    {
        if(Config.Command_Pdmg > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /pdmg NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "pdmg NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned rate=atoi(tmp);
	    Log( MSG_GMACTION, " Rate for Player Dmg is now set at %i by %s" , rate, thisclient->CharInfo->charname);
	    return pakGMChangePlayerDmg(thisclient, rate);
	}
	else if(strcmp(command, "mdmg")==0)
    {
        if(Config.Command_Mdmg > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /mdmg NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "mdmg NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned rate=atoi(tmp);
	    Log( MSG_GMACTION, " Rate for Monster Dmg is now set at %i by %s" , rate, thisclient->CharInfo->charname);
	    return pakGMChangeMonsterDmg(thisclient, rate);
	}
	else if(strcmp(command, "grid")==0)
    {
        if(Config.Command_grid > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
           {
           Log( MSG_GMACTION, " %s : /grid NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "grid NOT ALLOWED");
           SendPM(thisclient, buffer);
	                    return true;
           }
        if((tmp = strtok(NULL, " "))!=NULL)
        {
            if (Config.testgrid==0)
               SendPM(thisclient,"[Info] We are in Range Mode.");
            else
               SendPM(thisclient,"[Info] We are in Grid Mode.");

            return true;
        }
        if (Config.testgrid!=0)
        {
           Config.testgrid=0;
           SendPM(thisclient,"We are in Range Mode.");
        }
        else
        {
           Config.testgrid=1;
           SendPM(thisclient,"We are in Grid Mode.");
        }

	    Log( MSG_GMACTION, " Test Grid set at %i by %s" , Config.testgrid, thisclient->CharInfo->charname);
	    return true;
	}
	else if(strcmp(command, "unionmode")==0)
    {
        if(Config.Command_UnionMode > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
       {
           Log( MSG_GMACTION, " %s : /unionmode NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "unionmode NOT ALLOWED");
           SendPM(thisclient, buffer);
           return true;
       }

        if ((tmp = strtok(NULL, " "))==NULL)
        {
            char line0[200];
            sprintf(line0,"UW %i, dur %i min, loop? %i, loopdelay=%i, min players %i.",Config.unionwar,Config.unionwarduration,Config.unionwarloop,Config.unionwardelay_loop,Config.unionwarmin);
            SendPM(thisclient,line0);
            sprintf(line0,"Us %i, dur %i min, loop? %i, loopdelay=%i, min players %i.",Config.unionslaughter,Config.unionduration,Config.unionslaughterloop,Config.unionslaughterdelay_loop,Config.unionmin);
            SendPM(thisclient,line0);

            return true;
        }

        char* namemode=tmp;
         int value_loop_delay=0;
         int value_begin=0;
         int value_duration=0;
         int value_nb_players=0;
         int value_loop=0;

        if ((tmp = strtok(NULL, " "))==NULL)
        {
            return true;
        }
        int value_on_off= atoi( tmp );

        if ((tmp = strtok(NULL, " "))!=NULL)
        {
            value_begin= atoi( tmp );
        }

        if ((tmp = strtok(NULL, " "))!=NULL)
        {
            value_duration= atoi( tmp );
        }

        if ((tmp = strtok(NULL, " "))!=NULL)
        {
            value_nb_players= atoi( tmp );
        }

        if ((tmp = strtok(NULL, " "))!=NULL)
        {
            value_loop= atoi( tmp );
        }

        if ((tmp = strtok(NULL, " "))!=NULL)
        {
            value_loop_delay= atoi( tmp );
        }


        return pakGMUnionMode(thisclient,namemode,value_on_off,value_begin,value_duration,value_nb_players,value_loop,value_loop_delay);
	}
	else if(strcmp(command, "unionpoints")==0)
    {
        if(Config.Command_UnionPoints > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
       {
           Log( MSG_GMACTION, " %s : /unionpoints NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "unionpoints NOT ALLOWED");
           SendPM(thisclient, buffer);
           return true;
       }

        if ((tmp = strtok(NULL, " "))==NULL) return true; char* namemode=tmp;
        if ((tmp = strtok(NULL, " "))==NULL) return true; int value= atoi( tmp );

        return pakGMUnionPoints(thisclient, namemode, value);
	}
	else if(strcmp(command, "tquest")==0)
    {
        if(Config.Command_UnionPoints > thisclient->Session->accesslevel || thisclient->CharInfo->isGM == false)
       {
           Log( MSG_GMACTION, " %s : /unionpoints NOT ALLOWED" , thisclient->CharInfo->charname);
           char buffer[200];
           sprintf ( buffer, "unionpoints NOT ALLOWED");
           SendPM(thisclient, buffer);
           return true;
       }

        if ((tmp = strtok(NULL, " "))==NULL) return true; int action= atoi( tmp );
        if ((tmp = strtok(NULL, " "))==NULL) return true; int headerid= atoi( tmp );

       //810-01 00 00 00 fd 1a 00 00 66 00 d0 07
        BEGINPACKET( pak, 0x810);
        ADDBYTE    (pak, headerid);
        ADDBYTE    (pak, 0x00);
        ADDBYTE    (pak, 0x00);
        ADDBYTE    (pak, 0x00);
        ADDBYTE    (pak, thisclient->CharInfo->unionid);
        ADDBYTE    (pak, 0x00);
        ADDBYTE    (pak, 0x00);
        ADDBYTE    (pak, 0x00);
        ADDBYTE    (pak, 0x9);  //Map
        ADDBYTE    (pak, 0x00);
        if (action==1)
        {
            ADDBYTE    (pak, 0xd0);
            ADDBYTE    (pak, 0x07);
        }
        else
        {
            ADDBYTE    (pak, 0xE8);
            ADDBYTE    (pak, 0x03);
        }
        thisclient->client->SendPacket( &pak );
        return true;

       /*
       if ((tmp = strtok(NULL, " "))==NULL) return true; int action= atoi( tmp );
       if ((tmp = strtok(NULL, " "))==NULL) return true; int questpart= atoi( tmp );
       if ((tmp = strtok(NULL, " "))==NULL) return true; int questid= atoi( tmp );
       //DWORD questid=3628754895;

       //03 01 23 0b 00 00
        BEGINPACKET( pak, 0x730);
        ADDBYTE    (pak, action);
        ADDBYTE    (pak, questpart);
        //03 01 00 00 0b 23
        //ADDDWORD   (pak, 0x00000b23);
        ADDWORD   (pak, questid);
        ADDWORD   (pak, 0x0000);
    	thisclient->client->SendPacket( &pak );
        */

        return true;
	}
    else if(strcmp(command, "skill")==0)
    {
      if (Config.Command_KillInRange > thisclient->Session->accesslevel)
        return true;

      if ((tmp = strtok(NULL, " "))==NULL) return true;
      unsigned skillid = atoi(tmp);
      Log(MSG_GMACTION, "%s cast skill %i", thisclient->CharInfo->charname, skillid);
      SendPM(thisclient, "Casting skill %i", skillid);
      CCharacter* Target = thisclient->GetCharTarget( );
      CSkills* thisskill = GetSkillByID(skillid);
      thisclient->UseSkill(thisskill, Target);
    }
    else if(strcmp(command, "rules")==0)  // Rules Command by Matt
    {
        if(Config.Command_Rules > thisclient->Session->accesslevel)
	                    return true;
            SendPM(thisclient, "Please follow the following rules to ensure you have a fun time on this server!");
            SendPM(thisclient, "Rule 1: No hacking");
            SendPM(thisclient, "Rule 2: Do not abuse any bugs in the game");
            SendPM(thisclient, "Rule 3: Be respectful to all players and GMs");
            SendPM(thisclient, "Rule 4: Do not beg for items");
            SendPM(thisclient, "Rule 5: Do not harass any players or GM's");
            SendPM(thisclient, "Rule 6: Do not abuse any bugs in the game");
    }
    else if(strcmp(command, "cfmode")==0)
    {
        if(Config.Command_Cfmode > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned mode=atoi(tmp);
	    Log( MSG_GMACTION, " Clan field mode changed to %i by %s" , mode, thisclient->CharInfo->charname);
	    return pakGMChangeCfmode(thisclient, mode);
	}
	else if(strcmp(command, "whoattacksme")==0)
	{
	    return pakGMWhoAttacksMe(thisclient);
    }
    else if(strcmp(command, "atkModif")==0)
    {
        if(Config.Command_AtkModif > thisclient->Session->accesslevel)
//        if(300 > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned attkSpeedModif=atoi(tmp);
	    Log( MSG_GMACTION, " AttkSpeedModif changed to %i by %s" , attkSpeedModif, thisclient->CharInfo->charname);
	    return pakGMChangeAtkSpeedModif(thisclient, attkSpeedModif);
	}
	else if(strcmp(command, "hitModif")==0)
    {
        if(Config.Command_HitModif > thisclient->Session->accesslevel)
//        if(300 > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned hitDelayModif=atoi(tmp);
	    Log( MSG_GMACTION, " HitDelayModif changed to %i by %s" , hitDelayModif, thisclient->CharInfo->charname);
	    return pakGMChangeHitDelayModif(thisclient, hitDelayModif);
	}
	else if(strcmp(command, "SpeedModif")==0)
    {
        if(Config.Command_SpeedModif > thisclient->Session->accesslevel)
//        if(300 > thisclient->Session->accesslevel)
	                    return true;
	    if((tmp = strtok(NULL, " "))==NULL) return true; unsigned mSpeedModif=atoi(tmp);
	    Log( MSG_GMACTION, " mSpeedModif changed to %i by %s" , mSpeedModif, thisclient->CharInfo->charname);
	    return pakGMChangeMSpeedModif(thisclient, mSpeedModif);
	}
	// buff - debuff by Drakia
    else if (strcmp(command, "buff")==0)
    {
        if(Config.Command_Buff > thisclient->Session->accesslevel)
//        if (thisclient->Session->accesslevel < 300)
            return true;
        UINT strength;
        if ((tmp = strtok(NULL, " ")) == NULL) strength = 0; else strength = atoi(tmp);
        if (strength < 15) strength = 15;
        if (strength > 999999) strength = 999999;  // Max strength to use

        Log( MSG_GMACTION, "buff : character [ %s ] Strength [ %d ]", thisclient->CharInfo->charname, strength);
        pakGMBuff(thisclient, strength);
        return true;
     }
     else if ( strcmp(command, "debuff")==0)
     {
        if(Config.Command_Debuff > thisclient->Session->accesslevel)
//        if (thisclient->Session->accesslevel < 300)
            return true;
        Log(MSG_GMACTION, "debuff : character [ %s ]", thisclient->CharInfo->charname);
        pakGMDebuff(thisclient);
        return true;
     }
    // MaxStats - by rl2171
    else if(strcmp(command, "maxstats")==0)
    {
        if(Config.Command_MaxStats > thisclient->Session->accesslevel)
            return true;
        Log( MSG_GMACTION, " %s : /MaxStats", thisclient->CharInfo->charname );
        return pakGMMaxStats( thisclient );
    }
    // Dev - by rl2171
    else if (strcmp(command, "dev")==0)
     {
        if(Config.Command_Dev > thisclient->Session->accesslevel)
            return true;
         char buffer[200];
             sprintf ( buffer, "osRose Version %s", Config.osRoseVer);
             SendPM(thisclient, buffer);
      }

    // myloc - by PurpleYouko
    else if (strcmp(command, "myloc")==0)
    {
         char buffer[200];
         sprintf ( buffer, "My location. Map = %i X = %f Y = %f", thisclient->Position->Map, thisclient->Position->current.x, thisclient->Position->current.y);
         SendPM(thisclient, buffer);
    }

    // mystat - by PurpleYouko
    else if(strcmp(command, "mystat")==0)
    {
         if ((tmp = strtok(NULL, " "))==NULL)
        {
            SendPM(thisclient, "Please input after the mystat command, below is a list of commands");
            SendPM(thisclient, "ap = Attack Power");
            SendPM(thisclient, "acc = Accuracy");
            SendPM(thisclient, "dodge = Dodge");
            SendPM(thisclient, "def = Defense");
            SendPM(thisclient, "crit = Critical");
            SendPM(thisclient, "mspd = Movement Speed");
            SendPM(thisclient, "Example; /mystat ap");
         return true;
        }

         char buffer[200];
         if(strcmp(tmp, "ap")==0)
         {
             sprintf ( buffer, "My Attack Power is %i", thisclient->Stats->Attack_Power );
             SendPM(thisclient, buffer);
         }
         else if(strcmp(tmp, "acc")==0)
         {
             sprintf ( buffer, "My Accuracy is %i", thisclient->Stats->Accury );
             SendPM(thisclient, buffer);
         }
         else if(strcmp(tmp, "dodge")==0)
         {
             sprintf ( buffer, "My dodge is %i", thisclient->Stats->Dodge);
             SendPM(thisclient, buffer);
         }
         else if(strcmp(tmp, "def")==0)
         {
             sprintf ( buffer, "My defense is %i", thisclient->Stats->Defense);
             SendPM(thisclient, buffer);
         }
         else if(strcmp(tmp, "crit")==0)
         {
             sprintf ( buffer, "My critical is %i", thisclient->Stats->Critical);
             SendPM(thisclient, buffer);
         }
         else if(strcmp(tmp, "mspd")==0)
         {
             sprintf ( buffer, "My move speed is %i", thisclient->Stats->Move_Speed);
             SendPM(thisclient, buffer);
         }
    }
    // mystat2 - by PurpleYouko - from osprose to test
	else if(strcmp(command, "mystat2")==0)
    {
         if ((tmp = strtok(NULL, " "))==NULL)return true;
         if(strcmp(tmp, "ap")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My Attack Power is %i", thisclient->Stats->Attack_Power );
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "acc")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My Accuracy is %i", thisclient->Stats->Accury );
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "hp")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My current HP is %i", thisclient->Stats->HP );
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "mp")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My current MP is %i", thisclient->Stats->MP );
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "maxhp")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My Maximum HP is %i", thisclient->GetMaxHP());
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "maxmp")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My maximum MP is %i", thisclient->GetMaxMP());
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "dodge")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My dodge is %i", thisclient->Stats->Dodge);
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "def")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My defense is %i", thisclient->Stats->Defense);
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "mdef")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My Magic defense is %i", thisclient->Stats->Magic_Defense);
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "crit")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My critical is %i", thisclient->Stats->Critical);
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "mspd")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My move speed is %i", thisclient->Stats->Move_Speed);
             SendPM(thisclient, buffer2);
         }
         else if(strcmp(tmp, "aspd")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My attack speed is %i", thisclient->Stats->Attack_Speed);
             SendPM(thisclient, buffer2);
         }
//         else if(strcmp(tmp, "xprate")==0)
//         {
//             char buffer2[200];
//             sprintf ( buffer2, "My xp rate is %i", thisclient->Stats->xprate);
//             SendPM(thisclient, buffer2);
//         }
         else if(strcmp(tmp, "stamina")==0)
         {
             char buffer2[200];
             sprintf ( buffer2, "My Stamina is %i", thisclient->CharInfo->stamina);
             SendPM(thisclient, buffer2);
         }
//         else if(strcmp(tmp, "weight")==0)
//         {
//             int weight = thisclient->GetCurrentWeight();
//             int maxweight = thisclient->GetMaxWeight();
//             char buffer2[200];
//             sprintf ( buffer2, "My current weight is %i. max weight = %i", weight,maxweight);
//             SendPM(thisclient, buffer2);
//         }
         else if(strcmp(tmp, "clan")==0)
         {
             SendPM(thisclient, "My clan id is: %i My clan rank is: %i", thisclient->Clan->clanid, thisclient->Clan->clanrank);
         }
         else if(strcmp(tmp, "map")==0)
         {
             SendPM(thisclient, "My current map is: %i ", thisclient->Position->Map);
         }
    }

    // configreset - by PurpleYouko
    else if (strcmp(command, "configreset")==0) // *** RELOAD DATA FILES ******
    {
         //if(thisclient->Session->accesslevel < 900)
         if(Config.Command_ConfigReset > thisclient->Session->accesslevel)
                        return true;
         char* action;
         bool is_ok=false;
         UINT newval=0;
         //char* buffer;
         char buffer[200];
         if ((tmp = strtok(NULL, " ")) == NULL)return true; action = tmp;
         if(strcmp(action, "maxlevel")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.MaxLevel = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET maxlevel=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "xprate")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.EXP_RATE = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET exp_rate=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "droprate")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.DROP_RATE = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET drop_rate=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "droptype")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.DROP_TYPE = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET drop_type=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "zulyrate")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.ZULY_RATE = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET zuly_rate=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "savetime")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.SaveTime = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET savetime=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "partygap")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.Partygap = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET Partygap=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "maxstat")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.MaxStat = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET MaxStat=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "playerdmg")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.PlayerDmg = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET player_damage=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "monsterdmg")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.MonsterDmg = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET monster_damage=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "cfmode")==0)
         {
            if ((tmp = strtok(NULL, " ")) == NULL) return true; newval = atoi(tmp);
            {
                Config.Cfmode = newval;
                char* confname = "default";
                GServer->DB->QExecute("UPDATE list_config SET cfmode=%i WHERE conf='%s'",newval,confname);
                is_ok=true;
            }
         }
         if(strcmp(action, "cmd")==0)
         {
            LoadConfigurations( "commands.ini" );
            is_ok=true;
         }

         if(!is_ok)
         {
             Log( MSG_INFO, "Unrecognized configreset command by GM %s" , thisclient->CharInfo->charname);
             //sprintf ( buffer, "/configreset %s is not a valid command", tmp );
             sprintf ( buffer, "configreset %s is not a valid command", action );
             SendPM(thisclient, buffer);
             return true;
         }

         Log( MSG_GMACTION, " %s : /configreset %s" , thisclient->CharInfo->charname, action);
         sprintf ( buffer, "configreset %s %i data has been reloaded", action, newval  );
         SendPM(thisclient, buffer);
         return true;
    }


     // get all castlegear parts
    else if (strcmp(command, "cg")==0)
     {
        if(Config.Command_cg > thisclient->Session->accesslevel)
                    return true;
        int refine;
        if ((tmp = strtok(NULL, " "))==NULL) refine = 0;
        else
            refine=atoi(tmp);
        refine *= 16;
        BEGINPACKET( pak, 0);
        {
            //Wodden Stock Core
            thisclient->items[124].itemnum = 31;
            thisclient->items[124].itemtype = 14;
            thisclient->items[124].refine = 0;
            thisclient->items[124].durability = 40;
            thisclient->items[124].lifespan = 100;
            thisclient->items[124].count = 1;
            thisclient->items[124].stats = 0;
            thisclient->items[124].socketed = false;
            thisclient->items[124].appraised = true;
            thisclient->items[124].gem = 0;
            thisclient->UpdateInventory( 124 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 124);
            ADDWORD( pak, 31);  // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[124] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Fornef Engine
            thisclient->items[125].itemnum = 131;
            thisclient->items[125].itemtype = 14;
            thisclient->items[125].refine = 0;
            thisclient->items[125].durability = 40;
            thisclient->items[125].lifespan = 100;
            thisclient->items[125].count = 1;
            thisclient->items[125].stats = 0;
            thisclient->items[125].socketed = false;
            thisclient->items[125].appraised = true;
            thisclient->items[125].gem = 0;
            thisclient->UpdateInventory( 125 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 125);
            ADDWORD( pak, 131); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[125] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Stand Leg
            thisclient->items[126].itemnum = 231;
            thisclient->items[126].itemtype = 14;
            thisclient->items[126].refine = 0;
            thisclient->items[126].durability = 40;
            thisclient->items[126].lifespan = 100;
            thisclient->items[126].count = 1;
            thisclient->items[126].stats = 0;
            thisclient->items[126].socketed = false;
            thisclient->items[126].appraised = true;
            thisclient->items[126].gem = 0;
            thisclient->UpdateInventory( 126 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 126);
            ADDWORD( pak, 231); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[126] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            // Punch Arms
            thisclient->items[127].itemnum = 331;
            thisclient->items[127].itemtype = 14;
            thisclient->items[127].refine = 0;
            thisclient->items[127].durability = 40;
            thisclient->items[127].lifespan = 100;
            thisclient->items[127].count = 1;
            thisclient->items[127].stats = 0;
            thisclient->items[127].socketed = false;
            thisclient->items[127].appraised = true;
            thisclient->items[127].gem = 0;
            thisclient->UpdateInventory( 127 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 127);
            ADDWORD( pak, 331); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[127] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Drill Arms
            thisclient->items[128].itemnum = 332;
            thisclient->items[128].itemtype = 14;
            thisclient->items[128].refine = 0;
            thisclient->items[128].durability = 40;
            thisclient->items[128].lifespan = 100;
            thisclient->items[128].count = 1;
            thisclient->items[128].stats = 0;
            thisclient->items[128].socketed = false;
            thisclient->items[128].appraised = true;
            thisclient->items[128].gem = 0;
            thisclient->UpdateInventory( 128 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 128);
            ADDWORD( pak, 332); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[128] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Sword Wheel Arms
            thisclient->items[129].itemnum = 333;
            thisclient->items[129].itemtype = 14;
            thisclient->items[129].refine = 0;
            thisclient->items[129].durability = 40;
            thisclient->items[129].lifespan = 100;
            thisclient->items[129].count = 1;
            thisclient->items[129].stats = 0;
            thisclient->items[129].socketed = false;
            thisclient->items[129].appraised = true;
            thisclient->items[129].gem = 0;
            thisclient->UpdateInventory( 129 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 129);
            ADDWORD( pak, 333); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[129] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Cannon Arms
            thisclient->items[130].itemnum = 334;
            thisclient->items[130].itemtype = 14;
            thisclient->items[130].refine = 0;
            thisclient->items[130].durability = 40;
            thisclient->items[130].lifespan = 100;
            thisclient->items[130].count = 1;
            thisclient->items[130].stats = 0;
            thisclient->items[130].socketed = false;
            thisclient->items[130].appraised = true;
            thisclient->items[130].gem = 0;
            thisclient->UpdateInventory( 130 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 130); // SLOT NUM
            ADDWORD( pak, 334); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[131] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Spear Arms
            thisclient->items[131].itemnum = 335;
            thisclient->items[131].itemtype = 14;
            thisclient->items[131].refine = 0;
            thisclient->items[131].durability = 40;
            thisclient->items[131].lifespan = 100;
            thisclient->items[131].count = 1;
            thisclient->items[131].stats = 0;
            thisclient->items[131].socketed = false;
            thisclient->items[131].appraised = true;
            thisclient->items[131].gem = 0;
            thisclient->UpdateInventory( 131 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 131);
            ADDWORD( pak, 335); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[131] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );
            SendPM(thisclient, "get all CastleGear Parts!");
        }
        thisclient->SetStats( );
              return true;
     }

// get cart parts
    else if (strcmp(command, "cart")==0)
     {
        if(Config.Command_cart > thisclient->Session->accesslevel)
                    return true;
        int refine;
        if ((tmp = strtok(NULL, " "))==NULL) refine = 0;
        else
            refine=atoi(tmp);
        refine *= 16;
        BEGINPACKET( pak, 0);
        {
            //Sporty Frame
            thisclient->items[123].itemnum = 5;
            thisclient->items[123].itemtype = 14;
            thisclient->items[123].refine = 0;
            thisclient->items[123].durability = 40;
            thisclient->items[123].lifespan = 100;
            thisclient->items[123].count = 1;
            thisclient->items[123].stats = 0;
            thisclient->items[123].socketed = false;
            thisclient->items[123].appraised = true;
            thisclient->items[123].gem = 0;
            thisclient->UpdateInventory( 123 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 123);
            ADDWORD( pak, 5);   // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[123] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Sporty R Frame
            thisclient->items[122].itemnum = 6;
            thisclient->items[122].itemtype = 14;
            thisclient->items[122].refine = 0;
            thisclient->items[122].durability = 40;
            thisclient->items[122].lifespan = 100;
            thisclient->items[122].count = 1;
            thisclient->items[122].stats = 0;
            thisclient->items[122].socketed = false;
            thisclient->items[122].appraised = true;
            thisclient->items[122].gem = 0;
            thisclient->UpdateInventory( 122 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 122);
            ADDWORD( pak, 6);   // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[122] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Dural Engines
            thisclient->items[121].itemnum = 103;
            thisclient->items[121].itemtype = 14;
            thisclient->items[121].refine = 0;
            thisclient->items[121].durability = 40;
            thisclient->items[121].lifespan = 100;
            thisclient->items[121].count = 1;
            thisclient->items[121].stats = 0;
            thisclient->items[121].socketed = false;
            thisclient->items[121].appraised = true;
            thisclient->items[121].gem = 0;
            thisclient->UpdateInventory( 121 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 121);
            ADDWORD( pak, 103); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[121] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            // Rapid Wheels
            thisclient->items[120].itemnum = 203;
            thisclient->items[120].itemtype = 14;
            thisclient->items[120].refine = 0;
            thisclient->items[120].durability = 40;
            thisclient->items[120].lifespan = 100;
            thisclient->items[120].count = 1;
            thisclient->items[120].stats = 0;
            thisclient->items[120].socketed = false;
            thisclient->items[120].appraised = true;
            thisclient->items[120].gem = 0;
            thisclient->UpdateInventory( 120 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 120);
            ADDWORD( pak, 203); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[120] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Spike Wheel
            thisclient->items[119].itemnum = 401;
            thisclient->items[119].itemtype = 14;
            thisclient->items[119].refine = 0;
            thisclient->items[119].durability = 40;
            thisclient->items[119].lifespan = 100;
            thisclient->items[119].count = 1;
            thisclient->items[119].stats = 0;
            thisclient->items[119].socketed = false;
            thisclient->items[119].appraised = true;
            thisclient->items[119].gem = 0;
            thisclient->UpdateInventory( 119 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 119);
            ADDWORD( pak, 401); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[119] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Speed Wing
            thisclient->items[118].itemnum = 402;
            thisclient->items[118].itemtype = 14;
            thisclient->items[118].refine = 0;
            thisclient->items[118].durability = 40;
            thisclient->items[118].lifespan = 100;
            thisclient->items[118].count = 1;
            thisclient->items[118].stats = 0;
            thisclient->items[118].socketed = false;
            thisclient->items[118].appraised = true;
            thisclient->items[118].gem = 0;
            thisclient->UpdateInventory( 118 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 118);
            ADDWORD( pak, 402); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[118] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Wind Booster
            thisclient->items[117].itemnum = 403;
            thisclient->items[117].itemtype = 14;
            thisclient->items[117].refine = 0;
            thisclient->items[117].durability = 40;
            thisclient->items[117].lifespan = 100;
            thisclient->items[117].count = 1;
            thisclient->items[117].stats = 0;
            thisclient->items[117].socketed = false;
            thisclient->items[117].appraised = true;
            thisclient->items[117].gem = 0;
            thisclient->UpdateInventory( 117 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 117); // SLOT NUM
            ADDWORD( pak, 403); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[117] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Jet Booster
            thisclient->items[116].itemnum = 404;
            thisclient->items[116].itemtype = 14;
            thisclient->items[116].refine = 0;
            thisclient->items[116].durability = 40;
            thisclient->items[116].lifespan = 100;
            thisclient->items[116].count = 1;
            thisclient->items[116].stats = 0;
            thisclient->items[116].socketed = false;
            thisclient->items[116].appraised = true;
            thisclient->items[116].gem = 0;
            thisclient->UpdateInventory( 116 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 116);
            ADDWORD( pak, 404); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[116] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Sun Roof
            thisclient->items[115].itemnum = 405;
            thisclient->items[115].itemtype = 14;
            thisclient->items[115].refine = 0;
            thisclient->items[115].durability = 40;
            thisclient->items[115].lifespan = 100;
            thisclient->items[115].count = 1;
            thisclient->items[115].stats = 0;
            thisclient->items[115].socketed = false;
            thisclient->items[115].appraised = true;
            thisclient->items[115].gem = 0;
            thisclient->UpdateInventory( 115 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 115); // SLOT NUM
            ADDWORD( pak, 405); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[115] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Meister W Frame
            thisclient->items[114].itemnum = 421;
            thisclient->items[114].itemtype = 14;
            thisclient->items[114].refine = 0;
            thisclient->items[114].durability = 40;
            thisclient->items[114].lifespan = 100;
            thisclient->items[114].count = 1;
            thisclient->items[114].stats = 0;
            thisclient->items[114].socketed = false;
            thisclient->items[114].appraised = true;
            thisclient->items[114].gem = 0;
            thisclient->UpdateInventory( 114 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 114); // SLOT NUM
            ADDWORD( pak, 421); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[114] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Meister R Frame
            thisclient->items[113].itemnum = 422;
            thisclient->items[113].itemtype = 14;
            thisclient->items[113].refine = 0;
            thisclient->items[113].durability = 40;
            thisclient->items[113].lifespan = 100;
            thisclient->items[113].count = 1;
            thisclient->items[113].stats = 0;
            thisclient->items[113].socketed = false;
            thisclient->items[113].appraised = true;
            thisclient->items[113].gem = 0;
            thisclient->UpdateInventory( 113 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 113); // SLOT NUM
            ADDWORD( pak, 422); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[113] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Meister B Frame
            thisclient->items[112].itemnum = 423;
            thisclient->items[112].itemtype = 14;
            thisclient->items[112].refine = 0;
            thisclient->items[112].durability = 40;
            thisclient->items[112].lifespan = 100;
            thisclient->items[112].count = 1;
            thisclient->items[112].stats = 0;
            thisclient->items[112].socketed = false;
            thisclient->items[112].appraised = true;
            thisclient->items[112].gem = 0;
            thisclient->UpdateInventory( 112 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 112); // SLOT NUM
            ADDWORD( pak, 423); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[112] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Meister Y Frame
            thisclient->items[111].itemnum = 424;
            thisclient->items[111].itemtype = 14;
            thisclient->items[111].refine = 0;
            thisclient->items[111].durability = 40;
            thisclient->items[111].lifespan = 100;
            thisclient->items[111].count = 1;
            thisclient->items[111].stats = 0;
            thisclient->items[111].socketed = false;
            thisclient->items[111].appraised = true;
            thisclient->items[111].gem = 0;
            thisclient->UpdateInventory( 111 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 111); // SLOT NUM
            ADDWORD( pak, 424); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[111] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Meister Pink Frame
            thisclient->items[110].itemnum = 425;
            thisclient->items[110].itemtype = 14;
            thisclient->items[110].refine = 0;
            thisclient->items[110].durability = 40;
            thisclient->items[110].lifespan = 100;
            thisclient->items[110].count = 1;
            thisclient->items[110].stats = 0;
            thisclient->items[110].socketed = false;
            thisclient->items[110].appraised = true;
            thisclient->items[110].gem = 0;
            thisclient->UpdateInventory( 110 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 110); // SLOT NUM
            ADDWORD( pak, 425); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[110] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );


            //Chaser Engine
            thisclient->items[109].itemnum = 451;
            thisclient->items[109].itemtype = 14;
            thisclient->items[109].refine = 0;
            thisclient->items[109].durability = 40;
            thisclient->items[109].lifespan = 100;
            thisclient->items[109].count = 1;
            thisclient->items[109].stats = 0;
            thisclient->items[109].socketed = false;
            thisclient->items[109].appraised = true;
            thisclient->items[109].gem = 0;
            thisclient->UpdateInventory( 109 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 109); // SLOT NUM
            ADDWORD( pak, 451); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[109] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Meister Wheels
            thisclient->items[108].itemnum = 471;
            thisclient->items[108].itemtype = 14;
            thisclient->items[108].refine = 0;
            thisclient->items[108].durability = 40;
            thisclient->items[108].lifespan = 100;
            thisclient->items[108].count = 1;
            thisclient->items[108].stats = 0;
            thisclient->items[108].socketed = false;
            thisclient->items[108].appraised = true;
            thisclient->items[108].gem = 0;
            thisclient->UpdateInventory( 108 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 108); // SLOT NUM
            ADDWORD( pak, 471); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[108] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //P.I.G. Frame
            thisclient->items[107].itemnum = 21;
            thisclient->items[107].itemtype = 14;
            thisclient->items[107].refine = 0;
            thisclient->items[107].durability = 40;
            thisclient->items[107].lifespan = 100;
            thisclient->items[107].count = 1;
            thisclient->items[107].stats = 0;
            thisclient->items[107].socketed = false;
            thisclient->items[107].appraised = true;
            thisclient->items[107].gem = 0;
            thisclient->UpdateInventory( 107 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 107); // SLOT NUM
            ADDWORD( pak, 21);  // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[107] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //P.I.G. Engine
            thisclient->items[106].itemnum = 121;
            thisclient->items[106].itemtype = 14;
            thisclient->items[106].refine = 0;
            thisclient->items[106].durability = 40;
            thisclient->items[106].lifespan = 100;
            thisclient->items[106].count = 1;
            thisclient->items[106].stats = 0;
            thisclient->items[106].socketed = false;
            thisclient->items[106].appraised = true;
            thisclient->items[106].gem = 0;
            thisclient->UpdateInventory( 106 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 106); // SLOT NUM
            ADDWORD( pak, 121); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[106] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //P.I.G. Wheels
            thisclient->items[105].itemnum = 221;
            thisclient->items[105].itemtype = 14;
            thisclient->items[105].refine = 0;
            thisclient->items[105].durability = 40;
            thisclient->items[105].lifespan = 100;
            thisclient->items[105].count = 1;
            thisclient->items[105].stats = 0;
            thisclient->items[105].socketed = false;
            thisclient->items[105].appraised = true;
            thisclient->items[105].gem = 0;
            thisclient->UpdateInventory( 105 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 105); // SLOT NUM
            ADDWORD( pak, 221); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[105] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //P.I.G Balloon
            thisclient->items[104].itemnum = 321;
            thisclient->items[104].itemtype = 14;
            thisclient->items[104].refine = 0;
            thisclient->items[104].durability = 40;
            thisclient->items[104].lifespan = 100;
            thisclient->items[104].count = 1;
            thisclient->items[104].stats = 0;
            thisclient->items[104].socketed = false;
            thisclient->items[104].appraised = true;
            thisclient->items[104].gem = 0;
            thisclient->UpdateInventory( 104 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 104); // SLOT NUM
            ADDWORD( pak, 321); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[104] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Wooden Backseat
            thisclient->items[103].itemnum = 600;
            thisclient->items[103].itemtype = 14;
            thisclient->items[103].refine = 0;
            thisclient->items[103].durability = 40;
            thisclient->items[103].lifespan = 100;
            thisclient->items[103].count = 1;
            thisclient->items[103].stats = 0;
            thisclient->items[103].socketed = false;
            thisclient->items[103].appraised = true;
            thisclient->items[103].gem = 0;
            thisclient->UpdateInventory( 103 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 103); // SLOT NUM
            ADDWORD( pak, 600); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[103] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );

            //Steel Backseat
            thisclient->items[102].itemnum = 601;
            thisclient->items[102].itemtype = 14;
            thisclient->items[102].refine = 0;
            thisclient->items[102].durability = 40;
            thisclient->items[102].lifespan = 100;
            thisclient->items[102].count = 1;
            thisclient->items[102].stats = 0;
            thisclient->items[102].socketed = false;
            thisclient->items[102].appraised = true;
            thisclient->items[102].gem = 0;
            thisclient->UpdateInventory( 102 );
            RESETPACKET( pak, 0x7a5);
            ADDWORD( pak, thisclient->clientid );
            ADDWORD( pak, 102); // SLOT NUM
            ADDWORD( pak, 601); // ITEM NUM
            ADDWORD( pak, BuildItemRefine( thisclient->items[102] ));   // REFINE
            ADDWORD( pak, thisclient->Stats->Move_Speed );  // REFINE 2602
            SendToVisible( &pak,thisclient );
            SendPM(thisclient, "get cart parts with sporty frames jet booster and more!");
        }
        thisclient->SetStats( );
              return true;
    }


    else
    {
		Log( MSG_WARNING, "Invalid GM Command '%s' by '%s'", command, thisclient->CharInfo->charname);
		//Wrong Command Alert {By CrAshInSiDe}
        SendPM(thisclient, "Invalid Command");
	}
	return true;
}

// GM: Announcment
bool CWorldServer::pakGMAnn( CPlayer* thisclient, CPacket *P )
{
	BEGINPACKET( pak, 0x702 );
	ADDSTRING( pak, thisclient->CharInfo->charname );
	ADDSTRING( pak, "> " );
	ADDSTRING( pak, (&P->Buffer[5]));
	ADDBYTE( pak, 0x00);
	SendToAll( &pak );

	return true;
}

// GM: Spawn x mobs
bool CWorldServer::pakGMMon( CPlayer* thisclient, int montype, int moncount )
{
	for (int i=0; i<moncount; i++)
    {
        fPoint position = RandInCircle( thisclient->Position->current, 10 );
        CMap* map = MapList.Index[thisclient->Position->Map];
        map->AddMonster( montype, position, 0, NULL, NULL, 0 , true );
        SendPM(thisclient,"%i monsters of type %i summoned at position %f %f Map: %i",moncount,montype,position.x, position.y,map->id);

	}
	return true;
}

// GM: Teleport somewhere
bool CWorldServer::pakGMTele( CPlayer* thisclient, int map, float x, float y )
{
    fPoint coord;
    coord.x = x;
    coord.y = y;
    MapList.Index[map]->TeleportPlayer( thisclient, coord, false );
	return true;
}

// [by Paul_T] [Thanks to AridTag for the packet :D]
bool CWorldServer::pakGMMute( CPlayer* thisclient, char* name, int time)
{
    CPlayer* otherclient = GetClientByCharName ( name );
    BEGINPACKET( pak, 0x70d );
    ADDBYTE    ( pak, 0 );
    ADDWORD    ( pak, time );
    ADDSTRING  ( pak, thisclient->CharInfo->charname );
    ADDBYTE    ( pak, 0 );
    otherclient->client->SendPacket( &pak );
    return true;
}

// GM: Item   - Modified by Hiei (added refine/socket/stats)
bool CWorldServer::pakGMItem( CPlayer* thisclient, UINT itemid, UINT itemtype, UINT itemamount, UINT itemrefine, UINT itemls, UINT itemstats, UINT itemsocket )
{
    CItem item;
    item.count            = itemamount;
    item.durability        = 40;
    item.itemnum        = itemid;
    item.itemtype        = itemtype;
    item.lifespan        = 100;  // changed from itemls to 100, no need for lifespan on a item that is spawned - rl2171
    item.refine            = itemrefine;
    item.stats            = itemstats;
    item.socketed        = itemsocket;
    item.appraised        = 1;
    item.gem = 0;
    item.sp_value=0;
    item.last_sp_value=0;
    unsigned newslot = thisclient->GetNewItemSlot( item );

    //LMA: PAT:
    if (newslot>=135&&newslot<=136)
    {
        item.sp_value=item.lifespan*10;
    }

    if (newslot != 0xffff)
    {
        thisclient->items[newslot] = item;
        thisclient->UpdateInventory( newslot );
        char buffer[200];
        sprintf( buffer, "Item added! (ID: %i) (Type: %i) (Refine: %i) (Socket: %i)", item.itemnum, item.itemtype, item.refine, item.socketed );
        BEGINPACKET ( pak, 0x702 );
        ADDSTRING( pak, buffer );
        ADDBYTE( pak, 0 );
        thisclient->client->SendPacket( &pak );

    }else{
        BEGINPACKET( pak, 0x7a7 );
        ADDWORD( pak, thisclient->clientid );
        ADDBYTE( pak, 5 );
        thisclient->client->SendPacket( &pak );

        RESETPACKET ( pak, 0x702 );
        ADDSTRING( pak, "No free slot !" );
        ADDBYTE( pak, 0 );
        thisclient->client->SendPacket( &pak );
    }
    return true;
}

// LMA: We give an item from a Quest...
bool CWorldServer::pakGMItemQuest( CPlayer* thisclient, UINT itemid, UINT itemtype, UINT itemamount, UINT itemrefine, UINT itemls, UINT itemstats, UINT itemsocket, char buffer2[200] )
{
    CItem item;
    item.count            = itemamount;
    item.durability        = 40;
    item.itemnum        = itemid;
    item.itemtype        = itemtype;
    item.lifespan        = 100;  // changed from itemls to 100, no need for lifespan on a item that is spawned - rl2171
    item.refine            = itemrefine;
    item.stats            = itemstats;
    item.socketed        = itemsocket;
    item.appraised        = 1;
    item.gem = 0;
    unsigned newslot = thisclient->GetNewItemSlot( item );
    if (newslot != 0xffff)
    {
        thisclient->items[newslot] = item;
        thisclient->UpdateInventory( newslot );
        char buffer[200];
        sprintf( buffer, "%s", buffer2);
        BEGINPACKET ( pak, 0x702 );
        ADDSTRING( pak, buffer );
        ADDBYTE( pak, 0 );
        thisclient->client->SendPacket( &pak );

    }else{
        BEGINPACKET( pak, 0x7a7 );
        ADDWORD( pak, thisclient->clientid );
        ADDBYTE( pak, 5 );
        thisclient->client->SendPacket( &pak );

        RESETPACKET ( pak, 0x702 );
        ADDSTRING( pak, "No slot available in inventory!" );
        ADDBYTE( pak, 0 );
        thisclient->client->SendPacket( &pak );
    }
    return true;
}

// GM: Kick
bool CWorldServer::pakGMKick( CPlayer* thisclient, char* name )
{
    CPlayer* otherclient = GetClientByCharName( name );
    if(otherclient==NULL)
        return true;
    BEGINPACKET( pak, 0x702 );
    ADDSTRING( pak, "You were disconnected from the server !" );
    ADDBYTE( pak, 0 );
    otherclient->client->SendPacket( &pak );

    RESETPACKET( pak, 0x707 );
    ADDWORD( pak, 0 );
    otherclient->client->SendPacket( &pak );

    otherclient->client->isActive = false;

    return true;
}

// GM: Ban
bool CWorldServer::pakGMBan( CPlayer* thisclient, char* name )
{
    CPlayer* otherclient = GetClientByCharName( name );
    if(otherclient==NULL)
        return true;
    otherclient->Session->accesslevel = -1;
    DB->QExecute( "UPDATE accounts SET accesslevel='0' WHERE id=%i", otherclient->Session->userid);
    BEGINPACKET( pak, 0x702 );
    ADDSTRING( pak, "You were banned from the server !" );
    ADDBYTE( pak, 0 );
    otherclient->client->SendPacket( &pak );

    RESETPACKET( pak, 0x707 );
    ADDWORD( pak, 0 );
    otherclient->client->SendPacket( &pak );

    otherclient->client->isActive = false;

    return true;
}

// Reborn command credits Core
bool CWorldServer::pakGMReborn(CPlayer* thisclient)
{
     if(thisclient->Stats->Level < 250) //Level 250 can be changed to any level you want
     {
        GServer->SendPM(thisclient, "You have to be lvl 250 to reborn !");
     }

     else
     {

        //LMA: We remove all but basic skills.
        for(int i=0;i<320;i++)  //For keeping the skills, remove this line
        {  //For keeping the skills, remove this line
            thisclient->cskills[i].id = 0;  //For keeping the skills, remove this line
            thisclient->cskills[i].level = 1;  //For keeping the skills, remove this line
            thisclient->cskills[i].thisskill=NULL;
        }  //For keeping the skills, remove this line

        for(int i=0;i<MAX_QUICKBAR;i++)
            thisclient->quickbar[i] = 0;

         thisclient->p_skills = 0;  //For keeping the skills, remove
         thisclient->CharInfo->SkillPoints = 0;
         thisclient->CharInfo->StatPoints = 0;
         thisclient->CharInfo->Job = 0;

         thisclient->Stats->Level = 1;
         thisclient->CharInfo->Exp = 0;

         thisclient->ActiveQuest = 0;
#ifndef USENEWQUESTSYSTEM
         thisclient->MyQuest.clear();
#endif

        /*Update Reborn Command {By CrAshInSiDe*/
        int x = 5098;
        int y = 5322;
        int map = 22;
        if( (x != 0) && (y != 0) && (map != 0) )
        {
            fPoint coord;
            coord.x = x;
            coord.y = y;
            MapList.Index[map]->TeleportPlayer( thisclient, coord, false );
        }


         // Uncomment below if you want to use the Nobles part
         /*
                 char newcharname[65];
                 strcpy (newcharname,"[Nobles]");
                 strcat (newcharname, thisclient->CharInfo->charname);
                 GServer->DB->QExecute(" UPDATE characters SET char_name = '%s' WHERE id = '%i' ",newcharname, thisclient->CharInfo->charid);
        */

         BEGINPACKET( pak, 0x702 );
         ADDSTRING( pak, "You were disconnected from the server !" );
         ADDBYTE( pak, 0 );
         thisclient->client->SendPacket( &pak );

         RESETPACKET( pak, 0x707 );
         ADDWORD( pak, 0 );
         thisclient->client->SendPacket( &pak );

         //saving skills.
         thisclient->saveskills();
         thisclient->client->isActive = false;
      }


     return true;
}

//Event function credits Welson
bool CWorldServer::pakGMEventType(CPlayer* thisclient, int npctype, int dialog, long int type)
{
    CNPC* thisnpc = GetNPCByType(npctype);
    if(thisnpc == NULL)
    {
        delete thisnpc;
        return true;
    }
    if(type<0) type = 0;
    char buffer[200];

    sprintf( buffer, "Event %i for NPC: %i, Dialog: %i (if dialog has changed, type /here to force refresh)", type, npctype, dialog);
    thisnpc->dialog = dialog;
    thisnpc->event = type;

    BEGINPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[Server]" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE    ( pak, 0 );
    thisclient->client->SendPacket(&pak);

    RESETPACKET( pak, 0x790 );
    ADDWORD    ( pak, thisnpc->clientid );
    ADDWORD    ( pak, thisnpc->event );	  //LMA: Welcome in the real Word ^_^
    thisclient->client->SendPacket(&pak);

    //changing objvar as well.
    GServer->ObjVar[npctype][0]=thisnpc->event;

    //Saving in database
    //DB->QExecute("UPDATE npc_data SET dialog=%i, eventid=%i WHERE id=%i", dialog, type,npctype);
    //New way.
    DB->QExecute("UPDATE list_npcs SET tempdialogid=%i, eventid=%i WHERE type=%i", dialog, type,npctype);


	return true;
}

// GM: Add/Remove/Drop/Set zuly
bool CWorldServer::pakGMZuly( CPlayer* thisclient, int mode, int amount, char* charname )
{
	CPlayer* otherclient = GetClientByCharName(charname);
	if(otherclient==NULL)
	   return true;
	if (mode == 1)
	{
		//ADD
		otherclient->CharInfo->Zulies += amount;
		BEGINPACKET( pak, 0x71d );
		ADDQWORD( pak, otherclient->CharInfo->Zulies );
		otherclient->client->SendPacket( &pak );
	}
	if (mode == 2)
	{
		//REMOVE
		otherclient->CharInfo->Zulies -= amount;
		BEGINPACKET( pak, 0x71d );
		ADDQWORD( pak, otherclient->CharInfo->Zulies );
		otherclient->client->SendPacket( &pak );
	}
	if (mode == 3)
	{
		//DROP
		CDrop* thisdrop = new CDrop;
		assert(thisdrop);
		thisdrop->clientid = GetNewClientID();
		thisdrop->type = 1; // ZULY
		thisdrop->pos.x = otherclient->Position->current.x;
		thisdrop->pos.y = otherclient->Position->current.y;
		thisdrop->posMap = otherclient->Position->Map;
		thisdrop->droptime = time(NULL);
		thisdrop->amount = amount;
		thisdrop->owner = 0;
		CMap* map = MapList.Index[thisdrop->posMap];
		map->AddDrop( thisdrop );
	}
	if (mode == 4)
	{
		//SET
		otherclient->CharInfo->Zulies = amount;
		BEGINPACKET( pak, 0x71d );
		ADDQWORD( pak, otherclient->CharInfo->Zulies );
		otherclient->client->SendPacket( &pak );
	}
	return true;
}

// Change player Level
bool CWorldServer::pakGMLevel( CPlayer* thisclient, int level, char* name )
{
    CPlayer* otherclient = GetClientByCharName( name );
    if (otherclient == NULL)
        return true;
    if (((int)otherclient->Stats->Level + level) > 0)
        otherclient->Stats->Level += level;
    else
        otherclient->Stats->Level = 1;
    if (otherclient->Stats->Level > Config.MaxLevel)
        otherclient->Stats->Level = Config.MaxLevel;
    if (otherclient->Stats->Level > 250)
    //    otherclient->Stats->Level = 250;
          SendPM (thisclient, "Relogin For Get new Level");
    otherclient->CharInfo->Exp = 0;
    if (level < 0) {
        otherclient->CharInfo->StatPoints = 0;
        otherclient->CharInfo->SkillPoints = 0;
        if(otherclient->Stats->Level > 1)
        {
            for(int s = 2; s <= otherclient->Stats->Level; s++)
            {
                otherclient->CharInfo->StatPoints += 10;
                otherclient->CharInfo->StatPoints += s / 2;
                if (s >= 10)
                    otherclient->CharInfo->SkillPoints++;
            }
        }
        pakGMStat(otherclient, "str", 15);
        pakGMStat(otherclient, "dex", 15);
        pakGMStat(otherclient, "con", 15);
        pakGMStat(otherclient, "int", 15);
        pakGMStat(otherclient, "cha", 10);
        pakGMStat(otherclient, "sen", 10);
    } else {
        for(int s = (otherclient->Stats->Level - level + 1); s <= otherclient->Stats->Level; s++)
        {
            otherclient->CharInfo->StatPoints += 10;
            otherclient->CharInfo->StatPoints += s / 2;
            if (s >= 10)
                otherclient->CharInfo->SkillPoints++;
        }
    }
    BEGINPACKET( pak, 0x79e );
    ADDWORD( pak, otherclient->clientid );
    ADDWORD( pak, otherclient->Stats->Level );
    ADDDWORD( pak, otherclient->CharInfo->Exp );
    ADDWORD( pak, otherclient->CharInfo->StatPoints );
    ADDWORD( pak, otherclient->CharInfo->SkillPoints );
    otherclient->client->SendPacket( &pak );

    RESETPACKET( pak, 0x79e );
    ADDWORD( pak, otherclient->clientid );
    SendToVisible( &pak, otherclient, false );

    otherclient->SetStats( );
    otherclient->Stats->HP = otherclient->Stats->MaxHP;
    otherclient->Stats->MP = otherclient->Stats->MaxMP;
    return true;
}


// Reload Mob Spawn
bool CWorldServer::ReloadMobSpawn( CPlayer* thisclient, int id )
{
	CSpawnArea* thisspawn = new (nothrow) CSpawnArea;
	if(thisspawn==NULL)
	{
        Log(MSG_WARNING, "Error allocing memory" );
        return true;
    }
    thisspawn->thisnpc = GetNPCDataByID( thisclient->GMRespawnPoints.mobID );
    if(thisspawn->thisnpc==NULL)
    {
        SendSysMsg( thisclient, "Invalid Respawn" );
        return true;
    }
	thisspawn->id = id;
	thisspawn->map = thisclient->GMRespawnPoints.map;
	thisspawn->montype = thisclient->GMRespawnPoints.mobID;
	thisspawn->min = thisclient->GMRespawnPoints.min;
	thisspawn->max = thisclient->GMRespawnPoints.max;
	thisspawn->respawntime = thisclient->GMRespawnPoints.respawntime;
	thisspawn->pcount = thisclient->GMRespawnPoints.n;
	thisspawn->points = thisclient->GMRespawnPoints.points;
    CMap* map = MapList.Index[thisspawn->map];
	for(int j=0; j<thisspawn->max; j++)
    {
        fPoint position = RandInPoly( thisspawn->points, thisspawn->pcount );
        map->AddMonster( thisspawn->montype, position, 0, thisspawn->mobdrop, thisspawn->mapdrop, thisspawn->id, true );
	}
	thisspawn->lastRespawnTime=clock();
    return true;
}

// Teleport To player to other place
bool CWorldServer::pakGMTeleOtherPlayer( CPlayer *thisclient, char* name, int map, float x, float y )
{
	CPlayer* otherclient = GetClientByCharName( name );
	if (otherclient != NULL)
	{
        fPoint coord;
        coord.x = x;
        coord.y = y;
        MapList.Index[map]->TeleportPlayer( otherclient, coord, false );
	}
    else
	{
        SendSysMsg( thisclient, "User does not exist or is not online!" );
	}
	return true;
}

// Teleport Me to player
bool CWorldServer::pakGMTeleToPlayer( CPlayer* thisclient, char* name )
{
	CPlayer* otherclient = GetClientByCharName( name );
	if (otherclient != NULL)
	{
        MapList.Index[otherclient->Position->Map]->TeleportPlayer( thisclient, otherclient->Position->current, false );
	}
    else
	{
        SendSysMsg( thisclient, "User does not exist or is not online!" );
	}
	return true;
}

// Teleport Player Here
bool CWorldServer::pakGMTelePlayerHere( CPlayer* thisclient, char* name )
{
	CPlayer* otherclient = GetClientByCharName( name );
	if (otherclient != NULL)
	{
        CMap* map = MapList.Index[thisclient->Position->Map];
        map->TeleportPlayer( otherclient, thisclient->Position->current, false );
	}
    else
	{
        SendSysMsg( thisclient, "User does not exist or is not online!");
	}
	return true;
}

// Show Player info
bool CWorldServer::pakGMInfo(CPlayer* thisclient, char* name)
{
	CPlayer* otherclient = GetClientByCharName(name);
    if(otherclient==NULL)
        return true;
	char  buffer[200];
	char* jobname;

	if(otherclient != 0) {
		if((otherclient->CharInfo->Job - 0) == 0) { jobname = "Visitor"; }
		else if((otherclient->CharInfo->Job - 0) == 111) { jobname = "Soldier"; }
		else if((otherclient->CharInfo->Job - 0) == 121) { jobname = "Knight"; }
		else if((otherclient->CharInfo->Job - 0) == 122) { jobname = "Champion"; }
		else if((otherclient->CharInfo->Job - 0) == 211) { jobname = "Muse"; }
		else if((otherclient->CharInfo->Job - 0) == 221) { jobname = "Mage"; }
		else if((otherclient->CharInfo->Job - 0) == 222) { jobname = "Cleric"; }
		else if((otherclient->CharInfo->Job - 0) == 311) { jobname = "Hawker"; }
		else if((otherclient->CharInfo->Job - 0) == 321) { jobname = "Raider"; }
		else if((otherclient->CharInfo->Job - 0) == 322) { jobname = "Scout"; }
		else if((otherclient->CharInfo->Job - 0) == 411) { jobname = "Dealer"; }
		else if((otherclient->CharInfo->Job - 0) == 421) { jobname = "Bourgeois"; }
		else if((otherclient->CharInfo->Job - 0) == 422) { jobname = "Artisan"; }
		else { jobname = "Unknown"; }

		BEGINPACKET(pak, 0x702);

		sprintf(buffer, "Info about <%s>" , otherclient->CharInfo->charname);
		ADDSTRING(pak, buffer);
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);

		RESETPACKET(pak, 0x702);
		sprintf(buffer, "Account: %s | ID: %i" , otherclient->Session->username, otherclient->Session->userid);
		ADDSTRING(pak, buffer);
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);

		RESETPACKET(pak, 0x702);
		sprintf(buffer, "Level: %i | Job: %s" , (otherclient->Stats->Level-0) , jobname);
		ADDSTRING(pak, buffer);
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);

		RESETPACKET(pak, 0x702);
		sprintf(buffer,"Map: %i , X: %i , Y: %i", (otherclient->Position->Map-0), (int)otherclient->Position->current.x, (int)otherclient->Position->current.y);
		ADDSTRING(pak, buffer);
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
	}
	else {
		BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User does not exist or is not online!");
		ADDBYTE(pak, 0)
		thisclient->client->SendPacket(&pak);
	}
	return true;
}

//LMA: Give reward clan points to somebody
//also used when clan shopping.
bool CWorldServer::pakGMClanRewardPoints(CPlayer* thisclient, char* name, int points)
{
  	CPlayer* otherclient = GetClientByCharName (name);
	if(otherclient==NULL){
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User does not exist or is not online.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
    }

     if (otherclient->Clan->clanid==0)
     {
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User does not have a clan.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
     }

     //adding points if needed
     //Asking CharServer to refresh the player's informations.
    if (points>0)
    {
        thisclient->CharInfo->rewardpoints+=points;
        char buffer[200];
        sprintf( buffer, "You received %i Clan Reward Points !!", points);
        BEGINPACKET ( pak, 0x702 );
        ADDSTRING( pak, buffer );
        ADDBYTE( pak, 0 );
        otherclient->client->SendPacket( &pak );

        RESETPACKET( pak, 0x7e0 );
     	ADDBYTE    ( pak, 0xff );
    	ADDWORD    ( pak, otherclient->CharInfo->charid);  //charid
    	ADDDWORD    ( pak, thisclient->CharInfo->rewardpoints);  //reward points (TOTAL)
    	cryptPacket( (char*)&pak, GServer->cct );
    	send( csock, (char*)&pak, pak.Size, 0 );
    }
    else
    {
        BEGINPACKET( pak, 0x7e0 );
 	    ADDBYTE    ( pak, 0xff );
    	ADDWORD    ( pak, otherclient->CharInfo->charid);  //charid
    	ADDDWORD    ( pak, thisclient->CharInfo->rewardpoints);  //reward points (TOTAL)
    	cryptPacket( (char*)&pak, GServer->cct );
    	send( csock, (char*)&pak, pak.Size, 0 );
    }


     return true;
}

//LMA: Give clan points to somebody
bool CWorldServer::pakGMClanPoints(CPlayer* thisclient, char* name, int points)
{
  	CPlayer* otherclient = GetClientByCharName (name);
	if(otherclient==NULL){
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User does not exist or is not online.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
    }

     if (otherclient->Clan->clanid==0)
     {
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User does not have a clan.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
     }

     //adding points if needed
     //Asking CharServer to refresh the player's informations.
    if (points>0)
    {
        char buffer[200];
        sprintf( buffer, "You received %i Clan Points !!", points);
        BEGINPACKET ( pak, 0x702 );
        ADDSTRING( pak, buffer );
        ADDBYTE( pak, 0 );
        otherclient->client->SendPacket( &pak );

        RESETPACKET( pak, 0x7e0 );
     	ADDBYTE    ( pak, 0xfe );
    	ADDWORD    ( pak, otherclient->CharInfo->charid);  //charid
    	ADDDWORD    ( pak, points);  //Clan points (to be added)
    	cryptPacket( (char*)&pak, GServer->cct );
    	send( csock, (char*)&pak, pak.Size, 0 );
    }
    else
    {
        BEGINPACKET( pak, 0x7e0 );
 	    ADDBYTE    ( pak, 0xfe );
    	ADDWORD    ( pak, otherclient->CharInfo->charid);  //charid
    	ADDDWORD    ( pak, points);  //Clan points (to be added)
    	cryptPacket( (char*)&pak, GServer->cct );
    	send( csock, (char*)&pak, pak.Size, 0 );
    }

    //2do:
    //Add the last packet needed?
    BEGINPACKET( pak, 0x7e0 );
    ADDBYTE    ( pak, 0x35 );
    ADDWORD    ( pak, otherclient->clientid );
    ADDWORD    ( pak, otherclient->Clan->clanid );
    ADDWORD    ( pak, 0x0000 );
    ADDWORD    ( pak, otherclient->Clan->back );
    ADDWORD    ( pak, otherclient->Clan->logo );
    ADDBYTE    ( pak, otherclient->Clan->grade );
    ADDBYTE    ( pak, otherclient->Clan->clanrank);
    ADDSTRING  ( pak, otherclient->Clan->clanname );
    ADDBYTE    ( pak, 0x00 );
    otherclient->client->SendPacket(&pak);


     return true;
}

// Add Fairy
bool CWorldServer::pakGMFairyto(CPlayer* thisclient, char* name, int mode)
{
	if (GServer->Config.FairyMode== 0){
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "Fairy feature is de-activated.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
    }
	CPlayer* otherclient = GetClientByCharName (name);
	if(otherclient==NULL){
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User does not exist or is not online.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
    }
    if(mode == 0 && otherclient->Fairy == false){
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User already not fairied.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
    }
    if(mode == 1 && otherclient->Fairy == true){
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User already fairied.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
    }
    if(!otherclient->Fairy && mode == 1){
          int FairyIndex=100;
          for (int i=0; i<GServer->Config.FairyMax; i++){
               if (GServer->FairyList.at(i)->assigned == false){
                   FairyIndex=i;
                   i=GServer->Config.FairyMax;
               }
          }
          if (FairyIndex == 100){
              BEGINPACKET(pak, 0x702);
		      ADDSTRING(pak, "No free Fairy.");
		      ADDBYTE(pak, 0);
		      thisclient->client->SendPacket(&pak);
		      return true;
          }
          BEGINPACKET(pak, 0x702);
		  ADDSTRING(pak, "User fairied.");
		  ADDBYTE(pak, 0);
		  thisclient->client->SendPacket(&pak);
          int ListIndex;
          for (int i=0; i<ClientList.size(); i++){
              if (GServer->ClientList.at(i)->player == otherclient){
                 ListIndex = i;
                 i = GServer->ClientList.size();
              }
          }
          otherclient->Fairy = true;
          otherclient->FairyListIndex = FairyIndex;
          GServer->FairyList.at(FairyIndex)->ListIndex = ListIndex;
          GServer->FairyList.at(FairyIndex)->assigned = true;
          GServer->FairyList.at(FairyIndex)->LastTime = clock();
          GServer->FairyList.at(FairyIndex)->WaitTime = GServer->Config.FairyWait;
          GServer->DoFairyStuff( otherclient, mode );
          otherclient->SetStats();
          Log( MSG_INFO, "HP: %i  MP: %i  ATK: %i   DEF: %i   CRI: %i  MSPD: %i", otherclient->Stats->MaxHP, otherclient->Stats->MaxMP, otherclient->Stats->Attack_Power, otherclient->Stats->Defense, otherclient->Stats->Critical, otherclient->Stats->Move_Speed);
    }
    if(otherclient->Fairy && mode == 0){
          GServer->DoFairyFree(otherclient->FairyListIndex);
          GServer->FairyList.at(otherclient->FairyListIndex)->WaitTime = GServer->Config.FairyWait;
          otherclient->Fairy = false;
          otherclient->FairyListIndex = 0;
          GServer->DoFairyStuff( otherclient, mode );
          BEGINPACKET(pak, 0x702);
		  ADDSTRING(pak, "User unfairied.");
		  ADDBYTE(pak, 0);
		  otherclient->client->SendPacket(&pak);
          otherclient->SetStats();
          Log( MSG_INFO, "HP: %i  MP: %i  ATK: %i   DEF: %i   CRI: %i  MSPD: %i", otherclient->Stats->MaxHP, otherclient->Stats->MaxMP, otherclient->Stats->Attack_Power, otherclient->Stats->Defense, otherclient->Stats->Critical, otherclient->Stats->Move_Speed);
    }
    otherclient->SetStats();
	return true;
}

//LMA: let's hurt some people :)
//takes away 90% of HP and MP of a player
bool CWorldServer::pakGMHurtHim(CPlayer* thisclient, char* name)
{
	CPlayer* otherclient = GetClientByCharName (name);
	if(otherclient==NULL){
        BEGINPACKET(pak, 0x702);
		ADDSTRING(pak, "User does not exist or is not online.");
		ADDBYTE(pak, 0);
		thisclient->client->SendPacket(&pak);
        return true;
    }

    otherclient->Stats->HP=(long int) 10*otherclient->Stats->MaxHP/100;
    otherclient->Stats->MP=(long int) 10*otherclient->Stats->MaxMP/100;
    otherclient->SetStats();
	return true;
}

// Activate de-activate Fairy mode in game
bool CWorldServer::pakGMManageFairy(CPlayer* thisclient, int mode)
{
    BEGINPACKET (pak, 0x702);
	if(mode == 0){
        if (GServer->Config.FairyMode != mode){
	        GServer->Config.FairyMode = 0;
            ADDSTRING(pak, "You have de-activated the Fairy mode ingame.");
        }else{
            ADDSTRING(pak, "The Fairy mode is already de-activated.");
        }
    }else{
      	if (GServer->Config.FairyMode != mode){
	        GServer->Config.FairyMode = 1;
            for (int i=0; i<GServer->Config.FairyMax; i++)
            {
                GServer->DoFairyFree(i);
                GServer->FairyList.at(i)->WaitTime = GServer->Config.FairyWait;
            }
            ADDSTRING(pak, "You have activated the Fairy mode ingame.");
        }else{
            ADDSTRING(pak, "The Fairy mode is already activated.");
        }
    }
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);

	return true;
}

// Change FairyWait
bool CWorldServer::pakGMChangeFairyWait(CPlayer* thisclient, int newvalue)
{
    GServer->Config.FairyWait = newvalue;
    for (int i=0; i<GServer->FairyList.size(); i++){
        GServer->FairyList.at(i)->WaitTime = newvalue;
    }
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "You have changed the time between each Fairies");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}

// Change FairyStay
bool CWorldServer::pakGMChangeFairyStay(CPlayer* thisclient, int newvalue)
{
    GServer->Config.FairyStay = newvalue;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "You have changed the time of Fairies for Buffing ");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}

// Change Fairy Test mode.
// 0 -> normal random x * Fairywait
// 1 -> Test mode activated: 1 * Fairywait only
bool CWorldServer::pakGMChangeFairyTestMode(CPlayer* thisclient, int mode)
{
    GServer->Config.FairyTestMode = mode;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "You have changed the Fairy test mode.");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}

// Give Zuly
bool CWorldServer::pakGMZulygive(CPlayer* thisclient, char* name, int zuly)
{
    CPlayer* otherclient = GetClientByCharName (name);
    if(otherclient==NULL)
        return true;
	otherclient->CharInfo->Zulies += zuly;
	BEGINPACKET(pak, 0x7a7);
	ADDWORD(pak, otherclient->clientid);
	ADDWORD(pak, 0);
	ADDBYTE(pak, 0);
	ADDDWORD(pak, 0xccccccdf);
	ADDDWORD(pak, zuly);
    ADDDWORD( pak, 0xcccccccc );
    ADDWORD ( pak, 0xcccc );
	otherclient->client->SendPacket(&pak);

	return true;
}


//LMA: setting an union for a player
bool CWorldServer::pakGMUnion(CPlayer* thisclient, char* name, int which_union)
{
    CPlayer* otherclient = GetClientByCharName (name);
    if(otherclient==NULL)
        return true;
    if(which_union<0||which_union>7)
      return true;

    if(which_union==0)
    {
       //leaving union.
       //05 00 00 00 00 00
        BEGINPACKET( pak, 0x721 );
        ADDWORD( pak, 0x05 );
        ADDWORD( pak, 0x0000 );
        ADDWORD( pak, 0x0000 );
        otherclient->client->SendPacket( &pak );

    	RESETPACKET( pak, 0x730 );
        ADDWORD    ( pak, 0x0005 );
        ADDDWORD   ( pak, 0x40b3a24d );
        otherclient->client->SendPacket( &pak );

       char buffer[200];
       sprintf ( buffer, "GM %s made you left the Union.",thisclient->CharInfo->charname);
       SendPM(otherclient, buffer);

       Log( MSG_GMACTION, "Union set to %i for %s by %s" , which_union,name,thisclient->CharInfo->charname);

       thisclient->CharInfo->unionid=0;
       return true;
    }

    //LMA: changing union :)
    BEGINPACKET( pak, 0x721 );
    ADDWORD( pak, 0x05 );
    ADDWORD( pak, which_union );
    ADDWORD( pak, 0x0000 );
    otherclient->client->SendPacket( &pak );
	RESETPACKET( pak, 0x730 );
    ADDWORD    ( pak, 0x0005 );
    ADDDWORD   ( pak, 0x40b3a24d );
    otherclient->client->SendPacket( &pak );

   char buffer[200];
   sprintf ( buffer, "Welcome to union %i, %s",which_union,otherclient->CharInfo->charname);
   SendPM(otherclient, buffer);
   thisclient->CharInfo->unionid=which_union;
   Log( MSG_GMACTION, "Union set to %i for %s by %s" , which_union,name,thisclient->CharInfo->charname);


     return true;
}

//LMA: Giving union points to a player.
bool CWorldServer::pakGMUnionPoints(CPlayer* thisclient, char* name, int nb_points)
{
    CPlayer* otherclient = GetClientByCharName (name);
    if(otherclient==NULL)
    {
        return true;
    }

    if(nb_points<=0||thisclient->CharInfo->unionid==0)
    {
      return true;
    }

    int new_amount=0;
    int new_offset=80+thisclient->CharInfo->unionid;
    switch(new_offset)
    {
        case 81:
        {
            thisclient->CharInfo->union01+=nb_points;
            new_amount=thisclient->CharInfo->union01;
        }
        break;
        case 82:
        {
            thisclient->CharInfo->union02+=nb_points;
            new_amount=thisclient->CharInfo->union02;
        }
        break;
        case 83:
        {
            thisclient->CharInfo->union03+=nb_points;
            new_amount=thisclient->CharInfo->union03;
        }
        break;
        case 84:
        {
            thisclient->CharInfo->union04+=nb_points;
            new_amount=thisclient->CharInfo->union04;
        }
        break;
        case 85:
        {
            thisclient->CharInfo->union05+=nb_points;
            new_amount=thisclient->CharInfo->union05;
        }
        break;
    }

    //otherclient->CharInfo->union05+=nb_points;
    BEGINPACKET( pak, 0x721 );
    ADDWORD( pak, new_offset );
    ADDWORD( pak, new_amount );
    ADDWORD( pak, 0x0000 );
    otherclient->client->SendPacket( &pak );
    RESETPACKET( pak, 0x730 );
    ADDWORD    ( pak, 0x0005 );
    ADDDWORD   ( pak, 0x40b3a24d );
    otherclient->client->SendPacket( &pak );

   char buffer[200];
   sprintf ( buffer, "You have been given %i Faction Points by %s",nb_points,thisclient->CharInfo->charname);
   SendPM(otherclient, buffer);
   Log( MSG_GMACTION, "%i Faction points given to %s by %s" , nb_points,name,thisclient->CharInfo->charname);


     return true;
}


//LMA: setting union war or union slaughter
bool CWorldServer::pakGMUnionMode(CPlayer* thisclient, char* namemode, int value_on_off, int value_begin, int value_duration,int value_nb_players, int value_loop, int value_loop_delay)
{
   int value=0;


    value=value_on_off;

   if (strcmp(namemode, "uw")==0)
   {
       if (value<0||value>1)
          value=0;

       CMap* map = MapList.Index[9];
       if(value==0)
       {
         if (map->is_uw_fired)
         {
            SendPM(thisclient,"You can't cancel Union War now, a session is running...");
            return true;
         }

       }
       else
       {
         if (map->announce_done)
         {
            SendPM(thisclient,"You can't enable Union War now, it is already on...");
            return true;
         }

        }

        if(value==0)
        {
           GServer->UWNPCdialogs(0);
           map->uw_end=0;
           map->is_uw_fired=false;
           map->uw_begin=0;
           map->announce_done=false;
           map->uw_loop=false;
           map->uw_delay_loop=0;
           map->uw_duration=0;
           Config.unionwar=value;
           Config.unionwarloop=0;
           Config.unionwardelay_loop=0;
           Config.unionwarduration=0;
           Config.unionwarmin=0;
           char line0[200];
           sprintf(line0,"We set Union War to OFF .");
            SendPM(thisclient,line0);
            Log( MSG_GMACTION, " Union War set to OFF by %s" ,thisclient->CharInfo->charname);
            return true;
        }

        //We want to set it on :)
        if(value_duration==0||(value_loop!=0&&value_loop_delay==0)||value_begin==0||value_nb_players<=0)
        {
             char line0[200];
           sprintf(line0,"Uncorrect values for Union wars, duration is 0 or delay loop is 0 when loop is enabled...");
            SendPM(thisclient,line0);
            return true;
        }

       time_t etime=time(NULL);
       GServer->UWNPCdialogs(0);
       map->uw_end=0;
       map->is_uw_fired=false;
       map->uw_begin=etime+(60*value_begin);
       map->announce_done=false;
       map->uw_loop=value_loop;
       map->uw_delay_loop=value_loop_delay;
       map->uw_duration=value_duration;
       Config.unionwar=value;
       Config.unionwarloop=value_loop;
       Config.unionwardelay_loop=value_loop_delay;
       Config.unionwarduration=value_duration;
       Config.unionwarmin=value_nb_players;
       char line0[200];
       sprintf(line0,"UW ON in %i min, dur %i min, nb players %i, loop? %i, loopdelay=%i.",value_begin,value_duration,value_nb_players,value_loop,value_loop_delay);
        SendPM(thisclient,line0);
        Log( MSG_GMACTION, "UW ON in %i min, dur %i min, nb players %i, loop? %i, loopdelay=%i by %s.",value_begin,value_duration,value_nb_players,value_loop,value_loop_delay,thisclient->CharInfo->charname);


        return true;
   }

   //Union Slaughter
   if (value<0||value>1)
      value=0;

   CMap* map = MapList.Index[8];
   if(value==0)
   {
     if (map->is_union_fired)
     {
        SendPM(thisclient,"You can't cancel Union Slaughter now, a session is running...");
        return true;
     }

   }

    if(value==0)
    {
        map->utime_begin=0;
        Config.unionslaughter=value;
        char line0[200];
        sprintf(line0,"We set Union slaughter to OFF .");
        SendPM(thisclient,line0);
        Log( MSG_GMACTION, " Union slaughter set OFF by %s" , thisclient->CharInfo->charname);
        return true;
    }

        //We want to set it on :)
        if(value_duration==0||(value_loop!=0&&value_loop_delay==0)||value_begin==0||value_nb_players<=0)
        {
             char line0[200];
           sprintf(line0,"Uncorrect values for Union Slaughter, duration is 0 or delay loop is 0 when loop is enabled...");
            SendPM(thisclient,line0);
            return true;
        }

       time_t etime=time(NULL);
       map->utime_end=0;
       map->utime_begin=etime+(60*value_begin);
       map->us_loop=value_loop;
       map->us_delay_loop=value_loop_delay;
       map->us_duration=value_duration;
       Config.unionslaughter=value;
       Config.unionslaughterloop=value_loop;
       Config.unionslaughterdelay_loop=value_loop_delay;
       Config.unionduration=value_duration;
       Config.unionmin=value_nb_players;
       char line0[200];
       sprintf(line0,"US ON in %i min, dur %i min, nb players %i, loop? %i, loopdelay=%i.",value_begin,value_duration,value_nb_players,value_loop,value_loop_delay);
        SendPM(thisclient,line0);
        Log( MSG_GMACTION, "US ON in %i min, dur %i min, nb players %i, loop? %i, loopdelay=%i by %s.",value_begin,value_duration,value_nb_players,value_loop,value_loop_delay,thisclient->CharInfo->charname);


     return true;
}

// Spawn a NPC
bool CWorldServer::pakGMNpc(CPlayer* thisclient, int npcid,int dialogid,int eventid)
{
	CNPC* thisnpc = new CNPC;
	assert(thisnpc);
	thisnpc->clientid = GetNewClientID();
	thisnpc->dir = 0;
	thisnpc->npctype = npcid;
	thisnpc->pos = thisclient->Position->current;
	thisnpc->posMap = thisclient->Position->Map;
	thisnpc->thisnpc = GetNPCDataByID( npcid );
	thisnpc->thisnpc->dialogid = dialogid;
	thisnpc->event=eventid;
	if( thisnpc->thisnpc==NULL ) return true;
	CMap* map = MapList.Index[thisclient->Position->Map];
	thisnpc->lastAiUpdate=clock();
	map->AddNPC( thisnpc );
    char buffer[200];
    sprintf( buffer, "NPC Spawned! (NPC: %i) (Dialog: %i) (Event: %i)", npcid, dialogid,eventid );
    BEGINPACKET ( pak, 0x702 );
    ADDSTRING( pak, buffer );
    ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
	return true;
}

// Give Item to Player
bool CWorldServer::pakGMItemtoplayer(CPlayer* thisclient, char* name , UINT itemid, UINT itemtype, UINT itemamount, UINT itemrefine, UINT itemls, UINT itemstats, UINT itemsocket)
{
    CItem item;
    item.count            = itemamount;
    item.durability        = 40;
    item.itemnum        = itemid;
    item.itemtype        = itemtype;
    item.lifespan        = 100; //itemls Set lifespan to 100
    item.refine            = itemrefine;
    item.stats            = itemstats;
    item.socketed        = itemsocket;
    item.appraised        = 1;
    item.gem = 0;
    item.last_sp_value=0;
    item.sp_value=0;

    //LMA: Fuel for PAT.
    if (item.itemnum>=135&&item.itemnum<=136)
    {
        item.sp_value=item.lifespan*10;
    }

   CPlayer* otherclient = GetClientByCharName ( name );

   if(otherclient != NULL) {
      unsigned newslot = otherclient->GetNewItemSlot( item );
      if(newslot != 0xffff) {
         otherclient->items[newslot] = item;
         otherclient->UpdateInventory( newslot );

         BEGINPACKET (pak, 0x702);
         ADDSTRING(pak, "You have recieved an item from a GM !");
         ADDBYTE(pak, 0);
         otherclient->client->SendPacket(&pak);

         RESETPACKET (pak, 0x702);
         ADDSTRING(pak, "Item has been given!");
         ADDBYTE(pak, 0);
         thisclient->client->SendPacket(&pak);
      }
      else {
         BEGINPACKET (pak, 0x702);
         ADDSTRING(pak, "No free slot !");
         ADDBYTE(pak, 0);
         thisclient->client->SendPacket(&pak);
      }
   }

   return true;
}

// Do Emotion
bool CWorldServer::pakGMDoEmote( CPlayer* thisclient, int emotionid )
{
    ClearBattle( thisclient->Battle );
	BEGINPACKET( pak, 0x781 );
	ADDDWORD( pak, emotionid );
	ADDWORD( pak, thisclient->clientid );
	SendToVisible( &pak, thisclient );
	return true;
}

// Change GM Stats (Coded by Minoc)
bool CWorldServer::pakGMStat( CPlayer* thisclient, char* statname, int statvalue )
{
    int statid;
    if (strcmp( statname, "Str" )==0 || strcmp( statname, "str" )==0)
    {
        thisclient->Attr->Str = statvalue;
        statid = 0;
    }
    else if (strcmp( statname, "Dex" )==0 || strcmp( statname, "dex" )==0)
    {
        thisclient->Attr->Dex = statvalue;
        statid = 1;
    }
    else if (strcmp( statname, "Int" )==0 || strcmp( statname, "int" )==0)
    {
        thisclient->Attr->Int = statvalue;
        statid = 2;
    }
    else if (strcmp( statname, "Con" )==0 || strcmp( statname, "con" )==0)
    {
        thisclient->Attr->Con = statvalue;
        statid = 3;
    }
    else if (strcmp( statname, "Cha" )==0 || strcmp( statname, "cha" )==0)
    {
        thisclient->Attr->Cha = statvalue;
        statid = 4;
    }
    else if (strcmp( statname, "Sen" )==0 || strcmp( statname, "sen" )==0)
    {
        thisclient->Attr->Sen = statvalue;
        statid = 5;
    }
    else
    {
        return true;
    }
    BEGINPACKET( pak, 0x7a9 );
    ADDBYTE( pak, statid );
    ADDWORD( pak, (unsigned short)statvalue );
    thisclient->client->SendPacket( &pak );
    thisclient->SetStats( );
    return true;
}

// GM: Teleport using map id  credits to Blackie
bool CWorldServer::pakGMGotomap( CPlayer* thisclient, int map )
{
    CRespawnPoint* thisrespawn = MapList.Index[map]->GetFirstRespawn( );
    if(thisrespawn==NULL)
    {
        SendSysMsg( thisclient, "This map have no respawn" );
        return true;
    }
    MapList.Index[map]->TeleportPlayer( thisclient, thisrespawn->dest, false );
	return true;
}

// Heal a player ( by rl2171 )
// need to double check function - no errors compiling, but not healing MP and stamina
// playerdata.cpp has this value - CharInfo->MaxStamina = 5000;
// chartype.h has this value -  unsigned int MaxStamina;
bool CWorldServer::pakGMHeal( CPlayer* thisclient )
{
	thisclient->Stats->HP = thisclient->Stats->MaxHP;
	thisclient->Stats->MP = thisclient->Stats->MaxMP;
	thisclient->CharInfo->stamina = thisclient->CharInfo->MaxStamina;
	BEGINPACKET( pak, 0x7ec );
	ADDWORD( pak, thisclient->Stats->HP );
	ADDWORD( pak, thisclient->Stats->MP );
	ADDWORD( pak, thisclient->CharInfo->stamina );
	thisclient->client->SendPacket( &pak );
	return true;
}

// GM: Server Information ( by rl2171 ) modified by me
bool CWorldServer::pakGMServerInfo( CPlayer* thisclient )
{
    char buffer[200];
    // Players Online
	BEGINPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[SYS]ServerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, "SERVER INFORMATION" );
	ADDBYTE( pak, 0 );
	thisclient->client->SendPacket( &pak );
	sprintf( buffer, "Online Players: %i", (int)ClientList.size()-1 );// -1 (we don't count charserver)
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[SYS]ServerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, buffer );
	ADDBYTE( pak, 0 );
	thisclient->client->SendPacket( &pak );
    // Exp / Zulies / Drop rates
	sprintf( buffer, "Exp %i | Zulies %i | Drops %i", Config.EXP_RATE, Config.ZULY_RATE, Config.DROP_RATE );
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[SYS]ServerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, buffer );
	ADDBYTE( pak, 0 );
	thisclient->client->SendPacket( &pak );
	// Send map time
	if(MapList.Index[thisclient->Position->Map]!=NULL)
	{
    	RESETPACKET( pak, 0x0784 );
    	ADDSTRING( pak, "[SYS]ServerInfo" );
    	ADDBYTE( pak, 0 );
    	switch(MapList.Index[thisclient->Position->Map]->CurrentTime)
    	{
            case MORNING:
                sprintf( buffer, "The Time is: Morning[%i]", MapList.Index[thisclient->Position->Map]->MapTime%MapList.Index[thisclient->Position->Map]->dayperiod );
                ADDSTRING( pak, buffer );
            break;
            case DAY:
                sprintf( buffer, "The Time is: Day[%i]", MapList.Index[thisclient->Position->Map]->MapTime%MapList.Index[thisclient->Position->Map]->dayperiod );
                ADDSTRING( pak, buffer );
            break;
            case EVENING:
                sprintf( buffer, "The Time is: Evening[%i]", MapList.Index[thisclient->Position->Map]->MapTime%MapList.Index[thisclient->Position->Map]->dayperiod );
                ADDSTRING( pak, buffer );
            break;
            case NIGHT:
                sprintf( buffer, "The Time is: Night[%i]", MapList.Index[thisclient->Position->Map]->MapTime%MapList.Index[thisclient->Position->Map]->dayperiod );
                ADDSTRING( pak, buffer );
            break;
            default:
                sprintf( buffer, "Invalid Time is the End of world [%i]", MapList.Index[thisclient->Position->Map]->MapTime );
                ADDSTRING( pak, buffer );
        }
    	ADDBYTE( pak, 0 );
    	thisclient->client->SendPacket( &pak );
    }
	return true;
}

// Show Target Info
bool CWorldServer::GMShowTargetInfo( CPlayer* thisclient )
{
    if(thisclient->Battle->target==0) return true;
    char buffer[200];
    CMonster* monster = GetMonsterByID( thisclient->Battle->target, thisclient->Position->Map );
    if(monster==NULL) return true;
    float dist = distance( thisclient->Position->current, monster->Position->current );
    sprintf( buffer, "Target Position: %.4f, %.4f", monster->Position->current.x, monster->Position->current.y );
    BEGINPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Distance: %.0f",	dist );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Target Defense: %i", monster->Stats->Defense );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Target Level: %i", monster->thisnpc->level );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Target Attack Power: %i", monster->Stats->Attack_Power );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Target Attack Speed: %.0f", monster->Stats->Attack_Speed );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Target Move Speed: %i", monster->Stats->Move_Speed );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Target HP/MAXHP: %i/%i", monster->Stats->HP, monster->Stats->MaxHP );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
	ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
// added Database & Monster ID by rl2171 with help from lmame
    sprintf( buffer, "Target Database ID: %i", monster->Position->respawn );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
    ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    sprintf( buffer, "Target Monster ID: %i", monster->montype );
    RESETPACKET( pak, 0x784 );
    ADDSTRING  ( pak, "[SYS]TargetInfo" );
    ADDBYTE    ( pak, 0 );
    ADDSTRING  ( pak, buffer );
    ADDBYTE( pak, 0 );
    thisclient->client->SendPacket( &pak );
    return true;
}

// GM: Make yourself invisible from tomiz
bool CWorldServer::pakGMHide( CPlayer* thisclient, int mode )
{
    BEGINPACKET( pak, 0x702 );
    if ( mode == 1 )
    {
        thisclient -> isInvisibleMode = true;
        ADDSTRING( pak, "You are now invisible !" );
        Log( MSG_GMACTION, " %s : /hide invisible" , thisclient->CharInfo->charname);
    }
    else
    {
        thisclient -> isInvisibleMode = false;
        ADDSTRING( pak, "You are now visible !" );
        Log( MSG_GMACTION, " %s : /hide visible" , thisclient->CharInfo->charname);
    }
    ADDBYTE( pak, 0 );
    thisclient->client->SendPacket ( &pak );
    return true;
}
// GM : Change the party lvl
bool CWorldServer::pakGMPartylvl( CPlayer* partyclient, int level )
{
    if (partyclient->Party->party == NULL) return true;
    if (level < 0 || level >50) return true;
    partyclient->Party->party->PartyLevel = level;
    if( partyclient->Party->party->PartyLevel == 50)
          partyclient->Party->party->Exp = 0;
          //Send Party Level and Party Exp
          BEGINPACKET( pak, 0x7d4 ); //
          ADDBYTE    ( pak, partyclient->Party->party->PartyLevel);
          ADDDWORD   ( pak, partyclient->Party->party->Exp );
          partyclient->Party->party->SendToMembers( &pak );
    return true;
}

// GM: Kill all mobs in a range of x-Fields
bool CWorldServer::pakGMKillInRange( CPlayer* thisclient, int range )
{
    for(UINT j = 0; j < MapList.Index[thisclient->Position->Map]->MonsterList.size(); j++)
    {
        CMonster* thismon = MapList.Index[thisclient->Position->Map]->MonsterList.at(j);
        if( IsMonInCircle( thisclient, thismon, (float)range ))
        {
            //Kill the mob
            thismon->Stats->HP = -1;
            BEGINPACKET( pak, 0x799 );
            ADDWORD    ( pak, thismon->clientid );
            ADDWORD    ( pak, thismon->clientid );
            ADDDWORD   ( pak, thismon->thisnpc->hp*thismon->thisnpc->level );
            ADDDWORD   ( pak, 16 );
            SendToVisible( &pak, thismon );
        	CMap* map = MapList.Index[thisclient->Position->Map];
            map->DeleteMonster( thismon );
        }
    }
    return true;
}


//LMA: NPC shouts or announces with LTB.
bool CWorldServer::pakGMnpcshout( CPlayer* thisclient, char* shan, char* aipqsd, int npctype, int ltbid )
{
    if ( strcmp ( shan , "shout" ) != 0 && strcmp ( shan , "ann" ) != 0)
    {
        return true;
    }

    if ( strcmp ( aipqsd , "aip" ) != 0 && strcmp ( aipqsd , "qsd" ) != 0)
    {
        return true;
    }

    if (strcmp ( aipqsd , "aip" )==0)
    {
        if(ltbid>=maxltbaip)
        {
            return true;
        }

    }

    if (strcmp ( aipqsd , "qsd" )==0)
    {
        if(ltbid>=maxltbqsd)
        {
            return true;
        }

    }

    //checking NPC
    CNPC* thisnpc = GetNPCByType(npctype);
    if(thisnpc==NULL)
    {
        return true;
    }

	if(strcmp ( shan , "shout" ) == 0)
	{
	    if ( strcmp ( aipqsd , "aip" )==0)
	    {
	        GServer->NPCShout(NULL,GServer->Ltbstring[ltbid]->LTBstring,GServer->GetNPCNameByType(thisnpc->npctype),thisnpc->posMap);
	    }
	    else
	    {
	        GServer->NPCShout(NULL,GServer->LtbstringQSD[ltbid]->LTBstring,GServer->GetNPCNameByType(thisnpc->npctype),thisnpc->posMap);
	    }

	}
	else
	{
	    if ( strcmp ( aipqsd , "aip" )==0)
	    {
	        GServer->NPCAnnounce(GServer->Ltbstring[ltbid]->LTBstring,GServer->GetNPCNameByType(thisnpc->npctype));
	    }
	    else
	    {
	        GServer->NPCAnnounce(GServer->LtbstringQSD[ltbid]->LTBstring,GServer->GetNPCNameByType(thisnpc->npctype));
	    }

	}

	Log( MSG_GMACTION, " %s : /npcltb %s %s %i %i", thisclient->CharInfo->charname,shan,aipqsd,npctype,ltbid);


    return true;
}

// GM: Change Class (from Crash)
// Block Multiclass, except for GMs  (from MonkeyRose)
bool CWorldServer::pakGMClass( CPlayer* thisclient, char* classid )
{
    int classid_new = thisclient->CharInfo->Job;
    // allow GMs to multiclass
    bool GM = ( thisclient->Session->accesslevel == 300 );
    if ( strcmp ( classid , "Visitor" ) == 0 || strcmp ( classid , "visitor" ) == 0)
    {
        if (GM)
           classid_new = 0;
    }
    else if ( strcmp ( classid , "Soldier" ) == 0 || strcmp ( classid , "soldier" ) == 0)
    {
         if ( GM || ((thisclient->Stats->Level >= 10) && (classid_new == 0 ))) // visitor
             classid_new = 111;
    }
    else if ( strcmp ( classid , "Knight" ) == 0 || strcmp ( classid , "knight" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 111)))  // solder
             classid_new = 121;
    }
    else if ( strcmp ( classid , "Champion" ) == 0 || strcmp ( classid , "champion" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 111)))  // solder
                classid_new = 122;
    }
    else if ( strcmp ( classid , "Muse" ) == 0 || strcmp ( classid , "muse" ) == 0)
    {
         if ( GM || ((thisclient->Stats->Level >= 10) && (classid_new == 0 ))) // visitor
                classid_new = 211;
    }
    else if ( strcmp ( classid , "Mage" ) == 0 || strcmp ( classid , "mage" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 211)))  // muse
                classid_new = 221;
    }
    else if ( strcmp ( classid , "Cleric" ) == 0 || strcmp ( classid , "cleric" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 211)))  // muse
                classid_new = 222;
    }
    else if ( strcmp ( classid , "Hawker" ) == 0 || strcmp ( classid , "hawker" ) == 0)
    {
         if ( GM || ((thisclient->Stats->Level >= 10) && (classid_new == 0 ))) // visitor
                classid_new = 311;
    }
    else if ( strcmp ( classid , "Raider" ) == 0 || strcmp ( classid , "raider" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 311)))  // hawker
                classid_new = 321;
    }
    else if ( strcmp ( classid , "Scout" ) == 0 || strcmp ( classid , "scout" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 311)))  // hawker
                classid_new = 322;
    }
    else if ( strcmp ( classid , "Dealer" ) == 0 || strcmp ( classid , "dealer" ) == 0)
    {
         if ( GM || ((thisclient->Stats->Level >= 10) && (classid_new == 0 ))) // visitor
               classid_new = 411;
    }
    else if ( strcmp ( classid , "Bourgeois" ) == 0 || strcmp ( classid , "bourgeois" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 411)))  // dealer
                classid_new = 421;
    }
    else if ( strcmp ( classid , "Artisan" ) == 0 || strcmp ( classid , "artisan" ) == 0)
    {
        if ( GM || ((thisclient->Stats->Level >= 100) && (classid_new == 411)))  // dealer
                classid_new = 422;
    }
    else
    {
        return true;
    }
/*   add this section?
    // Set the quest vars for the new class by Drakia
    dword jVarSw = classid_new % 10;
    thisclient->quest.JobVar[0] = 0;
    thisclient->quest.JobVar[1] = 0;
    if (jVarSw == 1) {
      thisclient->quest.JobVar[0] = 1;
    } else if (jVarSw == 2) {
      thisclient->quest.JobVar[0] = 1;
      thisclient->quest.JobVar[1] = 2;
    }
*/
    bool changed = true;
    if ( thisclient->CharInfo->Job == classid_new )
       changed = false;
    thisclient->CharInfo->Job = classid_new;
    BEGINPACKET(pak, 0x0721);
    ADDWORD(pak,4);
    ADDWORD(pak, thisclient->CharInfo->Job);
    ADDWORD(pak,0);
    thisclient->client->SendPacket(&pak);
    RESETPACKET(pak, 0x0730);
    ADDWORD(pak, 5);
    ADDWORD(pak, 0xa24d);
    ADDWORD(pak, 0x40b3);
    thisclient->client->SendPacket(&pak);

    if ( changed )
    {
       SendPM(thisclient, "Class changed!" );
    }
    else
    {
       if ( thisclient->Stats->Level < 10 )
          SendPM(thisclient, "Class change failed! You must be at least lvl 10 to change your job." );
       else if (classid_new == 0) // visitor
          SendPM(thisclient, "Class change failed! Pick a first job, muse, dealer, hawker, or solder" );
       else
          SendPM(thisclient, "Class change failed!" );
    }

    return true;
}



bool CWorldServer::pakGMTeleAllHere( CPlayer* thisclient )
{
    int count=1;
    while(count <= (ClientList.size()-1))
    {
        CPlayer* otherclient = (CPlayer*)ClientList.at(count)->player;
        if ((otherclient != NULL) && (otherclient != thisclient))
        {
            CMap* map = MapList.Index[thisclient->Position->Map];
            map->TeleportPlayer( otherclient, thisclient->Position->current, false );
        }
        count++;
    }
    return true;
}

bool CWorldServer::pakGMMoveTo( CPlayer* thisclient, fPoint position )
{
    if( thisclient->Shop->open || (!thisclient->Ride->Drive && thisclient->Ride->Ride) || !thisclient->Status->CanMove )
        return true;
    if( thisclient->Status->Stance==1 )
        thisclient->Status->Stance=3;
    thisclient->Position->destiny = position; // PAKGMMOVETO
    ClearBattle( thisclient->Battle );
	BEGINPACKET( pak, 0x79a );
	ADDWORD    ( pak, thisclient->clientid );
	ADDWORD    ( pak, thisclient->Battle->target );
	ADDWORD    ( pak, thisclient->Stats->Move_Speed );
	ADDFLOAT   ( pak, thisclient->Position->destiny.x*100 );
	ADDFLOAT   ( pak, thisclient->Position->destiny.y*100 );
	ADDFLOAT   ( pak, thisclient->Position->destiny.z*100 );
    SendToVisible( &pak, thisclient );
    return true;
}

//change the player dmg rate
bool CWorldServer::pakGMChangePlayerDmg(CPlayer* thisclient, int rate)
{
    GServer->Config.PlayerDmg = rate;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "You have changed the player dmg rate.");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}
//change the monster dmg rate
bool CWorldServer::pakGMChangeMonsterDmg(CPlayer* thisclient, int rate)
{
    GServer->Config.MonsterDmg = rate;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "You have changed the Monster dmg rate.");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}
//change the Cfmode
bool CWorldServer::pakGMChangeCfmode(CPlayer* thisclient, int mode)
{
    if(mode<0) mode = 0;
    if(mode>1) mode = 1;
    GServer->Config.Cfmode = mode;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "You have changed the Clan Field Mode.");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}

bool CWorldServer::pakGMWhoAttacksMe(CPlayer* thisclient)
{
     std::cout << "You are attacked by these Mobs: ";
     CMap* map = GServer->MapList.Index[thisclient->Position->Map];
     for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* thismon = map->MonsterList.at( i );
		float distance = GServer->distance ( thisclient->Position->current, thismon->Position->current );
		if (thismon->Battle->target == thisclient->clientid)
           std::cout <<"ID: "<<thismon->clientid<< "  / " <<thismon->montype<<" I "<< (GServer->IsVisible(thisclient, thismon) ? "Visible\n":"Invisible\n");
	}
	return true;
}

//change the AtkSpeedModif || For test only
bool CWorldServer::pakGMChangeAtkSpeedModif(CPlayer* thisclient, int modif)
{
    GServer->ATTK_SPEED_MODIF = modif;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "AttkSpeedModif Changed.");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}

//change the HitDelayModif || For test only
bool CWorldServer::pakGMChangeHitDelayModif(CPlayer* thisclient, int modif)
{
    GServer->HIT_DELAY_MODIF = modif;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "HitDelayModif Changed.");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}

//change the mSpeedModif || For test only
bool CWorldServer::pakGMChangeMSpeedModif(CPlayer* thisclient, int modif)
{
    GServer->MOVE_SPEED_MODIF = modif;
    BEGINPACKET (pak, 0x702);
    ADDSTRING(pak, "mSpeedModif Changed.");
    ADDBYTE(pak, 0);
    thisclient->client->SendPacket(&pak);
	return true;
}

// GM Debuff players in sight. by Drakia
bool CWorldServer::pakGMDebuff(CPlayer* thisClient)
{
    for(int i = 0; i < 30; i++)
    {
        thisClient->MagicStatus[i].Duration = 0;
        thisClient->MagicStatus[i].BuffTime = 0;
    }
    thisClient->RefreshBuff();
    for (int i = 0; i < thisClient->VisiblePlayers.size(); i++)
    {
        CPlayer* targetClient = thisClient->VisiblePlayers[i];
        if (targetClient->Session->isLoggedIn == false) continue;
        if (targetClient->Stats->HP <= 0) continue;
        for(int j = 0; j < 30; j++)
        {
            targetClient->MagicStatus[j].Duration = 0;
            targetClient->MagicStatus[j].BuffTime = 0;
        }
        targetClient->RefreshBuff();
    }
    return true;
}

// GM Buff players in sight. by Drakia
bool CWorldServer::pakGMBuff( CPlayer* thisClient, int strength )
{
    // Buff the GM
    pakGMDebuff(thisClient);

    pakGMGiveBuff( thisClient, thisClient, 3906, strength); // Attack   (300s) (18)
    pakGMGiveBuff( thisClient, thisClient, 3905, strength); // Defense  (300s) (19)
    pakGMGiveBuff( thisClient, thisClient, 3908, strength); // Accuracy (420s) (20)
    pakGMGiveBuff( thisClient, thisClient, 3907, strength); // MResist  (420s) (21)
    pakGMGiveBuff( thisClient, thisClient, 3909, strength); // Dodge    (420s) (22)
    pakGMGiveBuff( thisClient, thisClient, 3904, strength); // Dash     (300s) (23)
    pakGMGiveBuff( thisClient, thisClient, 3910, strength); // Haste    (420s) (24)
    pakGMGiveBuff( thisClient, thisClient, 3911, strength); // Critical (420s) (26)
    pakGMGiveBuff( thisClient, thisClient, 3900, strength); // Max HP   (420s) (38)
    pakGMGiveBuff( thisClient, thisClient, 3901, strength); // Max MP   (420s) (39)
    pakGMGiveBuff( thisClient, thisClient, 3912, strength); //additional damage (420s) (36)
    // Buff all players visible
//    for (int i = 0; i < thisClient->VisiblePlayers.size(); i++)
//    {
//        CPlayer* target = thisClient->VisiblePlayers[i];
//        if ( target->Session->isLoggedIn == false ) continue;
//        if ( target->Stats->HP <= 0 ) continue;
    for(UINT j=0;j<ClientList.size();j++)
    {
        CPlayer* target = (CPlayer*) ClientList.at( j )->player;
        if ( target == NULL) continue;
        if ( target->Session->isLoggedIn == false ) continue;
        if ( target->Stats->HP <= 0 ) continue;
        if ( IsVisible(thisClient, target))
        {
        pakGMGiveBuff( thisClient, target, 3906, strength); // Attack   (300s) (18)
        pakGMGiveBuff( thisClient, target, 3905, strength); // Defense  (300s) (19)
        pakGMGiveBuff( thisClient, target, 3908, strength); // Accuracy (420s) (20)
        pakGMGiveBuff( thisClient, target, 3907, strength); // MResist  (420s) (21)
        pakGMGiveBuff( thisClient, target, 3909, strength); // Dodge    (420s) (22)
        pakGMGiveBuff( thisClient, target, 3904, strength); // Dash     (300s) (23)
        pakGMGiveBuff( thisClient, target, 3910, strength); // Haste    (420s) (24)
        pakGMGiveBuff( thisClient, target, 3911, strength); // Critical (420s) (26)
        pakGMGiveBuff( thisClient, target, 3900, strength); // Max HP   (420s) (38)
        pakGMGiveBuff( thisClient, target, 3901, strength); // Max MP   (420s) (39)
        pakGMGiveBuff( thisClient, target, 3912, strength); //additional damage (420s) (36)
        }
    }
    return true;
}

// Find the skill, add the buff, and send the packet. This is where the magic happens
// And what took me so freakin long to figure out x.x
bool CWorldServer::pakGMGiveBuff(CPlayer* thisClient, CPlayer* targetClient, int skillID, int strength)
{
    CSkills* skill = GServer->GetSkillByID(skillID);

    GServer->AddBuffs( skill, targetClient, strength );
    BEGINPACKET( pak, 0x7b5 );
    ADDWORD    ( pak, targetClient->clientid );
    ADDWORD    ( pak, thisClient->clientid );
    ADDWORD    ( pak, skillID );
    ADDWORD    ( pak, strength );
    ADDBYTE    ( pak, skill->nbuffs );
    GServer->SendToVisible( &pak, targetClient );
    return true;
}

// GM Give yourself all stats maxed
bool CWorldServer::pakGMMaxStats( CPlayer* thisclient )
{

        pakGMStat(thisclient, "str", Config.MaxStat);
        pakGMStat(thisclient, "dex", Config.MaxStat);
        pakGMStat(thisclient, "con", Config.MaxStat);
        pakGMStat(thisclient, "int", Config.MaxStat);
        pakGMStat(thisclient, "cha", Config.MaxStat);
        pakGMStat(thisclient, "sen", Config.MaxStat);

//changed from fixed 300 to Config.MaxStat controlled from list_config db  - rl2171

    return true;
}


//GM: All Skills {By CrAshInSiDe} - Skills and levels updated by rl2171 & Devilking
bool CWorldServer::pakGMAllSkill(CPlayer* thisclient, char* name)
{
    int classid = thisclient->CharInfo->Job;
    bool is_ok=true;
    CPlayer* otherclient = GetClientByCharName( name );
    if(otherclient==NULL)
    return true;

    //LMA: We delete previous skills to avoir errors (only the class ones)...
    //They will be sorted correctly (if needed) at next startup...
    for (int k=0;k<60;k++)
    {
        otherclient->cskills[k].id = 0;
        otherclient->cskills[k].level = 0;
        otherclient->cskills[k].thisskill=NULL;
    }

    if ( classid == 121 ) //Knight
    {
        otherclient->cskills[0].id = 201;//Physical Training
        otherclient->cskills[0].level = 9;
        otherclient->cskills[1].id = 211;//Repose
        otherclient->cskills[1].level = 9;
        otherclient->cskills[2].id = 221;//Defense Training
        otherclient->cskills[2].level = 9;
        otherclient->cskills[3].id = 231;//Power Owerflow
        otherclient->cskills[3].level = 5;
        otherclient->cskills[4].id = 236;//howl
        otherclient->cskills[4].level = 5;
        otherclient->cskills[5].id = 241;//staminal assist
        otherclient->cskills[5].level = 9;
        otherclient->cskills[6].id = 251;//Melee Weapon Mastery
        otherclient->cskills[6].level = 9;
        otherclient->cskills[7].id = 261;//Melee Double Attack
        otherclient->cskills[7].level = 9;
        otherclient->cskills[8].id = 271;//One Handed Weapon Mastery
        otherclient->cskills[8].level = 9;
        otherclient->cskills[9].id = 281;//Shield Mastery
        otherclient->cskills[9].level = 9;
        otherclient->cskills[10].id = 291;//Fatal Thrust
        otherclient->cskills[10].level = 9;
        otherclient->cskills[11].id = 301;//durability assist
        otherclient->cskills[11].level = 5;
        otherclient->cskills[12].id = 306;//Shield Stun
        otherclient->cskills[12].level = 5;
        otherclient->cskills[13].id = 311;//soul wreck
        otherclient->cskills[13].level = 4;
        otherclient->cskills[14].id = 416;//taunt
        otherclient->cskills[14].level = 5;
        otherclient->cskills[15].id = 421;//soundles vacuum
        otherclient->cskills[15].level = 4;
        otherclient->cskills[16].id = 431;//Advanced Defense Training
        otherclient->cskills[16].level = 9;
        otherclient->cskills[17].id = 441;//One-Handed Combat Mastery
        otherclient->cskills[17].level = 9;
        otherclient->cskills[18].id = 451;//Actual Battle Training
        otherclient->cskills[18].level = 9;
        otherclient->cskills[19].id = 461;//Advanced Shield Mastery
        otherclient->cskills[19].level = 18;
        otherclient->cskills[20].id = 481;//Triple Strike
        otherclient->cskills[20].level = 9;
        otherclient->cskills[21].id = 491;//safe guard
        otherclient->cskills[21].level = 5;
        otherclient->cskills[22].id = 496;//Shield Reflect
        otherclient->cskills[22].level = 5;
        otherclient->cskills[23].id = 501;//battle alertniss
        otherclient->cskills[23].level = 4;
        otherclient->cskills[24].id = 506;//Staminal Training
        otherclient->cskills[24].level = 9;
        otherclient->cskills[25].id = 516;//Refreshment
        otherclient->cskills[25].level = 9;
        otherclient->cskills[26].id = 721;//Quick Step
        otherclient->cskills[26].level = 5;
        otherclient->cskills[27].id = 726;//Battle March
        otherclient->cskills[27].level = 5;
        otherclient->cskills[28].id = 731;//Sword Force
        otherclient->cskills[28].level = 9;
        // Mileage Items - knight - 1 handed
        otherclient->cskills[29].id = 5601; // 847
        otherclient->cskills[29].level = 1;
        otherclient->cskills[30].id = 5602; // 848
        otherclient->cskills[30].level = 1;
        // Unique Items - knight - 1 handed
        otherclient->cskills[31].id = 4211; // 569
        otherclient->cskills[31].level = 4;
        //Immortal Form
        //otherclient->cskills[32].id = 426;
        //otherclient->cskills[32].level = 1;
        SendPM (thisclient, "Relogin For Get All Skills");
    }
    else if ( classid == 122 ) //Champion
    {
        otherclient->cskills[0].id = 201;//Physical Training
        otherclient->cskills[0].level = 9;
        otherclient->cskills[1].id = 211;//Repose
        otherclient->cskills[1].level = 9;
        otherclient->cskills[2].id = 221;//Defense Training
        otherclient->cskills[2].level = 9;
        otherclient->cskills[3].id = 231;//Power Owerflow
        otherclient->cskills[3].level = 5;
        otherclient->cskills[4].id = 236;//howl
        otherclient->cskills[4].level = 5;
        otherclient->cskills[5].id = 241;//staminal assist
        otherclient->cskills[5].level = 9;
        otherclient->cskills[6].id = 251;//Melee Weapon Mastery
        otherclient->cskills[6].level = 9;
        otherclient->cskills[7].id = 261;//Melee Double Attack
        otherclient->cskills[7].level = 9;
        otherclient->cskills[8].id = 311;//soul wreck
        otherclient->cskills[8].level = 4;
        otherclient->cskills[9].id = 316;//Two-Handed Weapon Mastery
        otherclient->cskills[9].level = 9;
        otherclient->cskills[10].id = 326;//Two-Handed Sword Mastery
        otherclient->cskills[10].level = 9;
        otherclient->cskills[11].id = 336;//Piercing Lunge
        otherclient->cskills[11].level = 9;
        otherclient->cskills[12].id = 346;//Battle howl
        otherclient->cskills[12].level = 4;
        otherclient->cskills[13].id = 351;//Voltage Crash
        otherclient->cskills[13].level = 4;
        otherclient->cskills[14].id = 356;//Spear Mastery
        otherclient->cskills[14].level = 9;
        otherclient->cskills[15].id = 366;//Raging Spear Strike
        otherclient->cskills[15].level = 9;
        otherclient->cskills[16].id = 376;//battle scream
        otherclient->cskills[16].level = 4;
        otherclient->cskills[17].id = 381;//spear screw
        otherclient->cskills[17].level = 4;
        otherclient->cskills[18].id = 386;//Axe Mastery
        otherclient->cskills[18].level = 9;
        otherclient->cskills[19].id = 396;//Leaping Axe Strike
        otherclient->cskills[19].level = 9;
        otherclient->cskills[20].id = 406;//Battle cry
        otherclient->cskills[20].level = 4;
        otherclient->cskills[21].id = 411;//Axe Launcher
        otherclient->cskills[21].level = 4;
        otherclient->cskills[22].id = 416;//taunt
        otherclient->cskills[22].level = 5;
        otherclient->cskills[23].id = 421;//soundles vacuum
        otherclient->cskills[23].level = 4;
        otherclient->cskills[24].id = 501;//battle alertniss
        otherclient->cskills[24].level = 4;
        otherclient->cskills[25].id = 506;//Staminal Training
        otherclient->cskills[25].level = 9;
        otherclient->cskills[26].id = 516;//Refreshment
        otherclient->cskills[26].level = 9;
        otherclient->cskills[27].id = 531;//Melee Combat Mastery
        otherclient->cskills[27].level = 9;
        otherclient->cskills[28].id = 541;//Two-Handed Battle Mastery
        otherclient->cskills[28].level = 9;
        otherclient->cskills[29].id = 551;//Battle Sense Mastery
        otherclient->cskills[29].level = 9;
        otherclient->cskills[30].id = 561;//Advanced Two-Handed Sword Mastery
        otherclient->cskills[30].level = 18;
        otherclient->cskills[31].id = 581;//Geon Archangel Crumpler
        otherclient->cskills[31].level = 9;
        otherclient->cskills[32].id = 591;//combat howl
        otherclient->cskills[32].level = 4;
        otherclient->cskills[33].id = 596;//War howl
        otherclient->cskills[33].level = 4;
        otherclient->cskills[34].id = 601;//Seismic Impact
        otherclient->cskills[34].level = 9;
        otherclient->cskills[35].id = 611;//Advanced Spear Mastery
        otherclient->cskills[35].level = 18;
        otherclient->cskills[36].id = 631;//Longinus's Spear
        otherclient->cskills[36].level = 9;
        otherclient->cskills[37].id = 641;//combat scream
        otherclient->cskills[37].level = 4;
        otherclient->cskills[38].id = 646;//war scream
        otherclient->cskills[38].level = 4;
        otherclient->cskills[39].id = 651;//Achilles's Heel Strike
        otherclient->cskills[39].level = 9;
        otherclient->cskills[40].id = 661;//Advanced Axe Mastery
        otherclient->cskills[40].level = 18;
        otherclient->cskills[41].id = 681;//Vaulting Axe Smash
        otherclient->cskills[41].level = 9;
        otherclient->cskills[42].id = 691;//combat cry
        otherclient->cskills[42].level = 4;
        otherclient->cskills[43].id = 696;//war cry
        otherclient->cskills[43].level = 4;
        otherclient->cskills[44].id = 701;//Axe Slugger
        otherclient->cskills[44].level = 9;
        otherclient->cskills[45].id = 711;//motion sensing
        otherclient->cskills[45].level = 5;
        otherclient->cskills[46].id = 716;//beserk
        otherclient->cskills[46].level = 5;
        // Mileage Items - 2 hand swor6
        otherclient->cskills[47].id = 5603; // 849
        otherclient->cskills[47].level = 1;
        otherclient->cskills[48].id = 5604; // 850
        otherclient->cskills[48].level = 1;
        // Mileage Items - spear
        otherclient->cskills[49].id = 5605; // 851
        otherclient->cskills[49].level = 1;
        otherclient->cskills[50].id = 5606; // 852
        otherclient->cskills[50].level = 1;
        // Mileage Items - axe
        otherclient->cskills[51].id = 5607; // 853
        otherclient->cskills[51].level = 1;
        otherclient->cskills[52].id = 5608; // 854
        otherclient->cskills[52].level = 1;
        // Unique Items -
        otherclient->cskills[53].id = 4211; // 569
        otherclient->cskills[53].level = 4;
        //Sword Master Form
        //otherclient->cskills[54].id = 526;
        //otherclient->cskills[54].level = 1;

        SendPM (thisclient, "Relogin For Get All Skills");
    }

    else if ( classid == 221 ) //Mage
    {
        otherclient->cskills[0].id = 851;//Mana Bolt
        otherclient->cskills[0].level = 9;
        otherclient->cskills[1].id = 831;//Frostbiter
        otherclient->cskills[1].level = 18;
        otherclient->cskills[2].id = 891;//Spell Mastery
        otherclient->cskills[2].level = 9;
        otherclient->cskills[3].id = 861;//Mana Spear
        otherclient->cskills[3].level = 9;
        otherclient->cskills[4].id = 881;//Fire Ring
        otherclient->cskills[4].level = 4;
        otherclient->cskills[5].id = 871;//Voltage Jolt
        otherclient->cskills[5].level = 4;
        otherclient->cskills[6].id = 831;//Frostbiter
        otherclient->cskills[6].level = 9;
        otherclient->cskills[7].id = 821;//Ice Bolt
        otherclient->cskills[7].level = 9;
        otherclient->cskills[8].id = 841;//Wind Storm
        otherclient->cskills[8].level = 4;
        otherclient->cskills[9].id = 846;//Tornado
        otherclient->cskills[9].level = 4;
        otherclient->cskills[10].id = 876;//Icy Hailstorm
        otherclient->cskills[10].level = 4;
        otherclient->cskills[11].id = 886;//Meteorite Strike
        otherclient->cskills[11].level = 4;
        otherclient->cskills[12].id = 901;//Spirit Boost
        otherclient->cskills[12].level = 9;
        otherclient->cskills[13].id = 1046;//Sorceror Form
        otherclient->cskills[13].level = 1;
        otherclient->cskills[14].id = 1051;//Staff Combat Mastery
        otherclient->cskills[14].level = 18;
        otherclient->cskills[15].id = 1316;//Lucid Soul
        otherclient->cskills[15].level = 9;
        otherclient->cskills[16].id = 1136;//Mystic Eye
        otherclient->cskills[16].level = 4;
        otherclient->cskills[17].id = 1071;//Freezing Chill
        otherclient->cskills[17].level = 9;
        otherclient->cskills[18].id = 1101;//Soul Shock
        otherclient->cskills[18].level = 5;
        otherclient->cskills[19].id = 1121;//Hellfire
        otherclient->cskills[19].level = 5;
        otherclient->cskills[20].id = 1141;//Elemental Bolt
        otherclient->cskills[20].level = 9;
        otherclient->cskills[21].id = 1106;//Fierce Cudgeling
        otherclient->cskills[21].level = 5;
        otherclient->cskills[22].id = 1126;//Staff Stun
        otherclient->cskills[22].level = 5;
        otherclient->cskills[23].id = 1081;//Tempest
        otherclient->cskills[23].level = 4;
        otherclient->cskills[24].id = 1096;//Hurricane
        otherclient->cskills[24].level = 5;
        otherclient->cskills[25].id = 1151;//Aural Pierce
        otherclient->cskills[25].level = 9;
        otherclient->cskills[26].id = 1086;//Glaciating Chill
        otherclient->cskills[26].level = 9;
        otherclient->cskills[27].id = 1111;//Soul Electric
        otherclient->cskills[27].level = 5;
        otherclient->cskills[28].id = 1131;//Mana Burn
        otherclient->cskills[28].level = 5;
        otherclient->cskills[29].id = 1116;//Permafrost Chill
        otherclient->cskills[29].level = 5;
        otherclient->cskills[30].id = 1171;//Meteorite Flow
        otherclient->cskills[30].level = 5;
        otherclient->cskills[31].id = 1176;//Soul Doubt
        otherclient->cskills[31].level = 5;
        otherclient->cskills[32].id = 1161;//Elemental Spike
        otherclient->cskills[32].level = 9;
        otherclient->cskills[33].id = 801;//Staff Mastery
        otherclient->cskills[33].level = 18;
        otherclient->cskills[34].id = 911;//Meditation
        otherclient->cskills[34].level = 9;
        otherclient->cskills[35].id = 921;//Cure
        otherclient->cskills[35].level = 5;
        // Mileage Items - mage
        otherclient->cskills[36].id = 5702; // 855
        otherclient->cskills[36].level = 1;
        otherclient->cskills[37].id = 5703; // 856
        otherclient->cskills[37].level = 1;
        // Mileage Item - Soul Recall
        otherclient->cskills[38].id = 5701; // 592
        otherclient->cskills[38].level = 1;
        // Unique Item - Soul Recall
        //otherclient->cskills[39].id = 4401; // 560
        //otherclient->cskills[39].level = 3;

        SendPM (thisclient, "Relogin For Get All Skills");
    }
    else if ( classid == 222 ) //Cleric
    {
        otherclient->cskills[0].id = 931;//Wand Mastery
        otherclient->cskills[0].level = 18;
        otherclient->cskills[1].id = 911;//Meditation
        otherclient->cskills[1].level = 9;
        otherclient->cskills[2].id = 921;//Cure
        otherclient->cskills[2].level = 5;
        otherclient->cskills[3].id = 926;//Hustle Charm
        otherclient->cskills[3].level = 5;
        otherclient->cskills[4].id = 951;//Mana Drop
        otherclient->cskills[4].level = 9;
        otherclient->cskills[5].id = 986;//Wallop Charm
        otherclient->cskills[5].level = 9;
        otherclient->cskills[6].id = 1021;//Bonfire
        otherclient->cskills[6].level = 9;
        otherclient->cskills[7].id = 1031;//Party Heal
        otherclient->cskills[7].level = 5;
        otherclient->cskills[8].id = 976;//Soul Revive
        otherclient->cskills[8].level = 5;
        otherclient->cskills[9].id = 996;//Resilience Charm
        otherclient->cskills[9].level = 9;
        otherclient->cskills[10].id = 1006;//Purify
        otherclient->cskills[10].level = 4;
        otherclient->cskills[11].id = 1036;//Blessed Mind
        otherclient->cskills[11].level = 4;
        otherclient->cskills[12].id = 1041;//Integrity
        otherclient->cskills[12].level = 5;
        otherclient->cskills[13].id = 961;//Voltage Shock
        otherclient->cskills[13].level = 9;
        otherclient->cskills[14].id = 971;//Summon Phantom Sword
        otherclient->cskills[14].level = 5;
        otherclient->cskills[15].id = 981;//Recovery
        otherclient->cskills[15].level = 5;
        otherclient->cskills[16].id = 1011;//Precision Charm
        otherclient->cskills[16].level = 9;
        otherclient->cskills[17].id = 1181;//Untouchable Aura
        otherclient->cskills[17].level = 1;
        otherclient->cskills[18].id = 1186;//Magic Battle Mastery
        otherclient->cskills[18].level = 18;
        otherclient->cskills[19].id = 1296;//Dragon Skin
        otherclient->cskills[19].level = 9;
        otherclient->cskills[20].id = 1306;//Chant Focusing
        otherclient->cskills[20].level = 9;
        otherclient->cskills[21].id = 1241;//Heavenly Grace
        otherclient->cskills[21].level = 5;
        otherclient->cskills[22].id = 1211;//Mana Wave
        otherclient->cskills[22].level = 9;
        otherclient->cskills[23].id = 1206;//Summon Mastery
        otherclient->cskills[23].level = 4;
        otherclient->cskills[24].id = 1246;//Battle Charm
        otherclient->cskills[24].level = 9;
        otherclient->cskills[26].id = 1256;//Salamander Flame
        otherclient->cskills[26].level = 3;
        otherclient->cskills[27].id = 1266;//Clobber Charm
        otherclient->cskills[27].level = 5;
        otherclient->cskills[28].id = 1276;//Critical Charm
        otherclient->cskills[28].level = 9;
        otherclient->cskills[29].id = 1271;//Evasive Charm
        otherclient->cskills[29].level = 5;
        otherclient->cskills[30].id = 1226;//Voltage Storm
        otherclient->cskills[30].level = 9;
        otherclient->cskills[31].id = 1236;//Summon Firegon
        otherclient->cskills[31].level = 5;
        otherclient->cskills[32].id = 1261;//Mana Flame
        otherclient->cskills[32].level = 3;
        otherclient->cskills[33].id = 1176;//Soul Doubt
        otherclient->cskills[33].level = 5;
        otherclient->cskills[34].id = 1286;//Valkyrie Charm
        otherclient->cskills[34].level = 9;
        otherclient->cskills[35].id = 1221;//Summon Elemental
        otherclient->cskills[35].level = 5;
        // Mileage Items - cleric
        otherclient->cskills[36].id = 5704; // 857
        otherclient->cskills[36].level = 1;
        otherclient->cskills[37].id = 5705; // 858
        otherclient->cskills[37].level = 1;
        // Mileage Item - Soul Recall
        otherclient->cskills[38].id = 5701; // 592
        otherclient->cskills[38].level = 1;
        // Unique Item - Soul Recall
        otherclient->cskills[39].id = 4401; // 560
        otherclient->cskills[39].level = 3;

        SendPM (thisclient, "Relogin For Get All Skills");
    }
    else if ( classid == 321 ) //Raider
    {
        otherclient->cskills[0].id = 1401;//Combat Mastery
        otherclient->cskills[0].level = 9;
        otherclient->cskills[1].id = 1521;//Knuckle Mastery
        otherclient->cskills[1].level = 18;
        otherclient->cskills[2].id = 1541;//Double Slash
        otherclient->cskills[2].level = 9;
        otherclient->cskills[3].id = 1551;//Focused Impact
        otherclient->cskills[3].level = 9;
        otherclient->cskills[4].id = 1561;//pison knife
        otherclient->cskills[4].level = 9;
        otherclient->cskills[5].id = 1571;//triple slash
        otherclient->cskills[5].level = 9;
        otherclient->cskills[6].id = 1581;//katar upper
        otherclient->cskills[6].level = 9;
        otherclient->cskills[7].id = 1591;//dividing cleave
        otherclient->cskills[7].level = 9;
        otherclient->cskills[8].id = 1601;//venom knife
        otherclient->cskills[8].level = 5;
        otherclient->cskills[9].id = 1606;//Katar Mastery
        otherclient->cskills[9].level = 9;
        otherclient->cskills[10].id = 1616;//Dual Weapon Mastery
        otherclient->cskills[10].level = 9;
        otherclient->cskills[11].id = 1626;//stealth
        otherclient->cskills[11].level = 4;
        otherclient->cskills[12].id = 1631;//ferocity accordance
        otherclient->cskills[12].level = 4;
        otherclient->cskills[13].id = 1636;//weaken
        otherclient->cskills[13].level = 4;
        otherclient->cskills[14].id = 1641;//morror phantasim
        otherclient->cskills[14].level = 4;
        otherclient->cskills[15].id = 1646;//flame hawk
        otherclient->cskills[15].level = 4;
        otherclient->cskills[16].id = 1651;//spiral kick
        otherclient->cskills[16].level = 4;
        otherclient->cskills[17].id = 1776;//Assassin Form
        otherclient->cskills[17].level = 1;
        otherclient->cskills[18].id = 1781;//Combat Weapon Mastery
        otherclient->cskills[18].level = 18;
        otherclient->cskills[19].id = 1801;//Combo Slash
        otherclient->cskills[19].level = 9;
        otherclient->cskills[20].id = 1811;//mystic knife
        otherclient->cskills[20].level = 4;
        otherclient->cskills[21].id = 1946;//plasma falcon
        otherclient->cskills[21].level = 4;
        otherclient->cskills[22].id = 1816;//Crazy-Style Slash
        otherclient->cskills[22].level = 9;
        otherclient->cskills[23].id = 1826;//Quick-Style Assualt
        otherclient->cskills[23].level = 9;
        otherclient->cskills[24].id = 1951;//circle break
        otherclient->cskills[24].level = 4;
        otherclient->cskills[25].id = 1836;//screw slash
        otherclient->cskills[25].level = 4;
        otherclient->cskills[26].id = 1841;//
        otherclient->cskills[26].level = 9;
        otherclient->cskills[27].id = 1851;//cloaking
        otherclient->cskills[27].level = 4;
        otherclient->cskills[28].id = 1856;//evasion guard
        otherclient->cskills[28].level = 4;
        otherclient->cskills[29].id = 1861;//Advanced Katar Mastery
        otherclient->cskills[29].level = 9;
        otherclient->cskills[30].id = 1871;//bloody assault
        otherclient->cskills[30].level = 4;
        otherclient->cskills[31].id = 1881;//critical accordance
        otherclient->cskills[31].level = 4;
        otherclient->cskills[32].id = 1886;//mental storm
        otherclient->cskills[32].level = 4;
        otherclient->cskills[33].id = 1891;//enfeeblement
        otherclient->cskills[33].level = 4;
        otherclient->cskills[34].id = 1896;//Phoenix Slash
        otherclient->cskills[34].level = 9;
        otherclient->cskills[35].id = 1906;//Flame Slash
        otherclient->cskills[35].level = 9;
        otherclient->cskills[36].id = 1916;//Freezing Assualt
        otherclient->cskills[36].level = 9;
        otherclient->cskills[37].id = 1926;//Precision Slash
        otherclient->cskills[37].level = 9;
        otherclient->cskills[38].id = 1936;//Precision Assualt
        otherclient->cskills[38].level = 9;
        otherclient->cskills[39].id = 1876;//vicious accordance
        otherclient->cskills[39].level = 4;
        otherclient->cskills[40].id = 1811;//Mystic Knife
        otherclient->cskills[40].level = 4;
        otherclient->cskills[41].id = 1506;//sprint
        otherclient->cskills[41].level = 5;
        otherclient->cskills[42].id = 1511;//velocity accordance
        otherclient->cskills[42].level = 5;
        otherclient->cskills[43].id = 1766;//rapid twitch
        otherclient->cskills[43].level = 5;
        otherclient->cskills[44].id = 1761;//hawker accordance
        otherclient->cskills[44].level = 5;
        otherclient->cskills[45].id = 1516;//secound sight
        otherclient->cskills[45].level = 4;
        otherclient->cskills[46].id = 1771;//requiem
        otherclient->cskills[46].level = 4;
        // Mileage Items - raider - katar
        otherclient->cskills[47].id = 5803; // 861
        otherclient->cskills[47].level = 1;
        otherclient->cskills[48].id = 5804; // 862
        otherclient->cskills[48].level = 1;
        // Mileage Items - raider - dual
        otherclient->cskills[49].id = 5805; // 863
        otherclient->cskills[49].level = 1;
        otherclient->cskills[50].id = 5806; // 864
        otherclient->cskills[50].level = 1;

        SendPM (thisclient, "Relogin For Get All Skills");
    }
    else if ( classid == 322 ) //Scout
    {
        otherclient->cskills[0].id = 1401;//Combat Mastery
        otherclient->cskills[0].level = 9;
        otherclient->cskills[1].id = 1411;//Bow Mastery
        otherclient->cskills[1].level = 18;
        otherclient->cskills[2].id = 1431;//Clamp Arrow
        otherclient->cskills[2].level = 9;
        otherclient->cskills[3].id = 1441;//Double Arrow
        otherclient->cskills[3].level = 9;
        otherclient->cskills[4].id = 1451;//Backpack Proficiency
        otherclient->cskills[4].level = 9;
        otherclient->cskills[5].id = 1461;//Mana Profut
        otherclient->cskills[5].level = 9;
        otherclient->cskills[6].id = 1471;//offensive focus
        otherclient->cskills[6].level = 5;
        otherclient->cskills[7].id = 1496;//soul disciplin
        otherclient->cskills[7].level = 5;
        otherclient->cskills[8].id = 1476;//Shackle Arrow
        otherclient->cskills[8].level = 9;
        otherclient->cskills[9].id = 1486;//Triple Arrow
        otherclient->cskills[9].level = 9;
        otherclient->cskills[10].id = 1501;//stun arrow
        otherclient->cskills[10].level = 4;
        otherclient->cskills[11].id = 1656;//Flame Hawk
        otherclient->cskills[11].level = 1;
        otherclient->cskills[12].id = 1661;//Advanced Bow Mastery
        otherclient->cskills[12].level = 18;
        otherclient->cskills[13].id = 1681;//Call Hawk
        otherclient->cskills[13].level = 9;
        otherclient->cskills[14].id = 1691;//Trap Arrow
        otherclient->cskills[14].level = 9;
        otherclient->cskills[15].id = 1701;//Aimed Triple Arrow
        otherclient->cskills[15].level = 9;
        otherclient->cskills[16].id = 1711;//camoflage
        otherclient->cskills[16].level = 5;
        otherclient->cskills[17].id = 1716;//longinus`s Incoration
        otherclient->cskills[17].level = 5;
        otherclient->cskills[18].id = 1721;//mana flow
        otherclient->cskills[18].level = 9;
        otherclient->cskills[19].id = 1731;//point black arrow
        otherclient->cskills[19].level = 5;
        otherclient->cskills[20].id = 1736;//Entangling Arrow
        otherclient->cskills[20].level = 9;
        otherclient->cskills[21].id = 1746;//Phoenix Arrow
        otherclient->cskills[21].level = 9;
        otherclient->cskills[22].id = 1756;//soul gurrent
        otherclient->cskills[22].level = 5;
        otherclient->cskills[23].id = 1506;//sprint
        otherclient->cskills[23].level = 5;
        otherclient->cskills[24].id = 1766;//rapid twitch
        otherclient->cskills[24].level = 5;
        otherclient->cskills[25].id = 1511;//Velocity accourdance
        otherclient->cskills[25].level = 5;
        otherclient->cskills[26].id = 1761;//Hawker accordance
        otherclient->cskills[26].level = 5;
        otherclient->cskills[27].id = 1516;//secound sight
        otherclient->cskills[27].level = 4;
        otherclient->cskills[28].id = 1771;//requiem
        otherclient->cskills[28].level = 4;
        otherclient->cskills[29].id = 1956;//impact arrow
        otherclient->cskills[29].level = 6;
        // Mileage Items - scout
        otherclient->cskills[30].id = 5801; // 859
        otherclient->cskills[30].level = 1;
        otherclient->cskills[31].id = 5802; // 860
        otherclient->cskills[31].level = 1;
        // Unique Items - hawker
        otherclient->cskills[32].id = 4601; // call beast // 565
        otherclient->cskills[32].level = 9;

        SendPM (thisclient, "Relogin For Get All Skills");
    }

    else if ( classid == 421 ) //Bourgeois
    {
        otherclient->cskills[0].id = 2001;//Trigger Finger
        otherclient->cskills[0].level = 9;
        otherclient->cskills[1].id = 2011;//Tough Gunner
        otherclient->cskills[1].level = 18;
        otherclient->cskills[2].id = 2036;//Twin Shot
        otherclient->cskills[2].level = 9;
        otherclient->cskills[3].id = 2031;//Intesify
        otherclient->cskills[3].level = 5;
        otherclient->cskills[4].id = 2056;//selsam gaint
        otherclient->cskills[4].level = 5;
        otherclient->cskills[5].id = 2046;//craftsman talent
        otherclient->cskills[5].level = 5;
        otherclient->cskills[6].id = 2051;//Discount
        otherclient->cskills[6].level = 5;
        otherclient->cskills[7].id = 2061;//Sniping
        otherclient->cskills[7].level = 9;
        otherclient->cskills[8].id = 2071;//master twin shot
        otherclient->cskills[8].level = 5;
        otherclient->cskills[9].id = 2076;//Demolition Expertise
        otherclient->cskills[9].level = 9;
        otherclient->cskills[10].id = 2086;//backpack mastery
        otherclient->cskills[10].level = 5;
        otherclient->cskills[11].id = 2091;//illusion
        otherclient->cskills[11].level = 5;
        otherclient->cskills[12].id = 2096;//mercenery employment
        otherclient->cskills[12].level = 4;
        otherclient->cskills[13].id = 2111;//weapon expertise
        otherclient->cskills[13].level = 5;
        otherclient->cskills[14].id = 2101;//employ warrior
        otherclient->cskills[14].level = 5;
        otherclient->cskills[15].id = 2106;//employ hunter
        otherclient->cskills[15].level = 5;
        otherclient->cskills[16].id = 2256;//Veteran Sniper
        otherclient->cskills[16].level = 9;
        otherclient->cskills[17].id = 2266;//Ace Gunner
        otherclient->cskills[17].level = 18;
        otherclient->cskills[18].id = 2286;//Merchandising
        otherclient->cskills[18].level = 9;
        otherclient->cskills[19].id = 2296;//Third Eye
        otherclient->cskills[19].level = 1;
        otherclient->cskills[20].id = 2301;//triple shot
        otherclient->cskills[20].level = 5;
        otherclient->cskills[21].id = 2316;//Zulie Bolt
        otherclient->cskills[21].level = 9;
        otherclient->cskills[22].id = 2306;//Venemous Shot
        otherclient->cskills[22].level = 9;
        otherclient->cskills[23].id = 2401;//master triple shot
        otherclient->cskills[23].level = 5;
        otherclient->cskills[24].id = 2326;//Shrapnel Burst
        otherclient->cskills[24].level = 9;
        otherclient->cskills[25].id = 2336;//Chaotic Burst
        otherclient->cskills[25].level = 9;
        otherclient->cskills[26].id = 2346;//windstep
        otherclient->cskills[26].level = 5;
        otherclient->cskills[27].id = 2356;//stockpile
        otherclient->cskills[27].level = 9;
        otherclient->cskills[28].id = 2366;//weapon agument
        otherclient->cskills[28].level = 5;
        otherclient->cskills[29].id = 2351;//light step
        otherclient->cskills[29].level = 5;
        otherclient->cskills[30].id = 2376;//summon dreag knight
        otherclient->cskills[30].level = 5;
        otherclient->cskills[31].id = 2371;//jury rigging
        otherclient->cskills[31].level = 5;
        otherclient->cskills[32].id = 2381;//Toxic Shot
        otherclient->cskills[32].level = 9;
        otherclient->cskills[33].id = 2391;//Zulie Stun
        otherclient->cskills[33].level = 9;
        otherclient->cskills[34].id = 2406;//Cannon Splash Burst
        otherclient->cskills[34].level = 9;
        otherclient->cskills[35].id = 2416;//Flame Stun Burst
        otherclient->cskills[35].level = 9;
        otherclient->cskills[36].id = 2426;//reflect aura
        otherclient->cskills[36].level = 5;
        otherclient->cskills[37].id = 2431;//dual layer
        otherclient->cskills[37].level = 5;
        // Mileage Items - Borg - Launcher
        otherclient->cskills[38].id = 5904; // 867
        otherclient->cskills[38].level = 1;
        otherclient->cskills[39].id = 5905; // 868
        otherclient->cskills[39].level = 1;
        //added for ver 144
        otherclient->cskills[40].id = 2461;//aimed triple shot
        otherclient->cskills[40].level = 5;
        SendPM (thisclient, "Relogin For Get All Skills");
    }

    else if ( classid == 422 ) //Artisan
    {
        //Common Tab
        otherclient->cskills[0].id = 2031;//Intensify Weapon
        otherclient->cskills[0].level = 5;
        otherclient->cskills[1].id = 2036;//Twin Shot
        otherclient->cskills[1].level = 9;
        otherclient->cskills[2].id = 2046;//Craftsman's Talent
        otherclient->cskills[2].level = 5;
        otherclient->cskills[3].id = 2051;//Discount
        otherclient->cskills[3].level = 5;
        otherclient->cskills[4].id = 2056;//Salesman Gait
        otherclient->cskills[4].level = 5;
        otherclient->cskills[5].id = 2086;//Backpack Mastery
        otherclient->cskills[5].level = 5;
        otherclient->cskills[6].id = 2301;//Triple Shot
        otherclient->cskills[6].level = 5;
        otherclient->cskills[7].id = 2461;//Aimed Triple Shot
        otherclient->cskills[7].level = 5;
        //Crafting Tab
        otherclient->cskills[8].id = 2116;//Weapon Research
        otherclient->cskills[8].level = 9;
        otherclient->cskills[9].id = 2126;//Armor Research
        otherclient->cskills[9].level = 9;
        otherclient->cskills[10].id = 2136;//SubItem Research
        otherclient->cskills[10].level = 9;
        otherclient->cskills[11].id = 2146;//Alchemy Research
        otherclient->cskills[11].level = 9;
        otherclient->cskills[12].id = 2156;//Weapon Craft
        otherclient->cskills[12].level = 9;
        otherclient->cskills[13].id = 2166;//Dark Blade Research
        otherclient->cskills[13].level = 9;
        otherclient->cskills[14].id = 2176;//Beam Blade Research
        otherclient->cskills[14].level = 9;
        otherclient->cskills[15].id = 2186;//Metal Blade Research
        otherclient->cskills[15].level = 9;
        otherclient->cskills[16].id = 2196;//Timber Blade Research
        otherclient->cskills[16].level = 9;
        otherclient->cskills[17].id = 2206;//Armor Craft
        otherclient->cskills[17].level = 9;
        otherclient->cskills[18].id = 2216;//Earth Blade Research
        otherclient->cskills[18].level = 9;
        otherclient->cskills[19].id = 2226;//Ocean Blade Research
        otherclient->cskills[19].level = 9;
        otherclient->cskills[20].id = 2236;//SubItem Craft
        otherclient->cskills[20].level = 9;
        otherclient->cskills[21].id = 2246;//Alchemy Craft
        otherclient->cskills[21].level = 9;
        otherclient->cskills[22].id = 2666;//Weapon Darkening
        otherclient->cskills[22].level = 9;
        otherclient->cskills[23].id = 2676;//Weapon Hardening
        otherclient->cskills[23].level = 9;
        otherclient->cskills[24].id = 2686;//Weapon Balancing
        otherclient->cskills[24].level = 9;
        otherclient->cskills[25].id = 2696;//Weapon Enchanting
        otherclient->cskills[25].level = 9;
        otherclient->cskills[26].id = 2706;//Armor Reinforcement
        otherclient->cskills[26].level = 9;
        otherclient->cskills[27].id = 2716;//Armor Endowment
        otherclient->cskills[27].level = 9;
        //Artizan Tab
        otherclient->cskills[28].id = 2441;//Top Gunner
        otherclient->cskills[28].level = 18;
        otherclient->cskills[29].id = 2466;//Poison Shot
        otherclient->cskills[29].level = 9;
        otherclient->cskills[30].id = 2476;//Hypno Shot
        otherclient->cskills[30].level = 5;
        otherclient->cskills[31].id = 2481;//Summon Terror Knight
        otherclient->cskills[31].level = 5;
        otherclient->cskills[32].id = 2486;//Advanced Weapon Research
        otherclient->cskills[32].level = 9;
        otherclient->cskills[33].id = 2496;//Advanced Armor Research
        otherclient->cskills[33].level = 9;
        otherclient->cskills[34].id = 2506;//Advanced Subitem Research
        otherclient->cskills[34].level = 9;
        otherclient->cskills[35].id = 2516;//Advanced Alchemy Research
        otherclient->cskills[35].level = 9;
        otherclient->cskills[36].id = 2526;//Advanced Weapon Craft
        otherclient->cskills[36].level = 9;
        otherclient->cskills[37].id = 2536;//Advanced Dark Blade Research
        otherclient->cskills[37].level = 9;
        otherclient->cskills[38].id = 2546;//Advanced Beam Blade Research
        otherclient->cskills[38].level = 9;
        otherclient->cskills[39].id = 2556;//Advanced Metal Blade Research
        otherclient->cskills[39].level = 9;
        otherclient->cskills[40].id = 2566;//Advanced Timber Blade Research
        otherclient->cskills[40].level = 9;
        otherclient->cskills[41].id = 2576;//Advanced Armor Craft
        otherclient->cskills[41].level = 9;
        otherclient->cskills[42].id = 2586;//Advanced Earth Blade Research
        otherclient->cskills[42].level = 9;
        otherclient->cskills[43].id = 2596;//Advanced Ocean Blade Research
        otherclient->cskills[43].level = 9;
        otherclient->cskills[44].id = 2606;//Advanced SubItem Craft
        otherclient->cskills[44].level = 9;
        otherclient->cskills[45].id = 2616;//Advanced Alchemy Craft
        otherclient->cskills[45].level = 9;
        otherclient->cskills[46].id = 2626;//PAT Research
        otherclient->cskills[46].level = 9;
        otherclient->cskills[47].id = 2636;//PAT Craft
        otherclient->cskills[47].level = 9;
        otherclient->cskills[48].id = 2646;//Gem Cutting Research
        otherclient->cskills[48].level = 9;
        otherclient->cskills[49].id = 2656;//Gem Cutting
        otherclient->cskills[49].level = 9;
        otherclient->cskills[50].id = 2726;//Advanced Weapon Darkening
        otherclient->cskills[50].level = 9;
        otherclient->cskills[51].id = 2736;//Advanced Weapon Hardening
        otherclient->cskills[51].level = 9;
        otherclient->cskills[52].id = 2746;//Advanced Weapon Balancing
        otherclient->cskills[52].level = 9;
        otherclient->cskills[53].id = 2756;//Advanced Weapon Enchanting
        otherclient->cskills[53].level = 9;
        otherclient->cskills[54].id = 2766;//Advanced Armor Reinforcement
        otherclient->cskills[54].level = 9;
        otherclient->cskills[55].id = 2776;//Advanced Armor Endowment
        otherclient->cskills[55].level = 9;
        // Mileage Items - artisan
        otherclient->cskills[56].id = 5902; // 865
        otherclient->cskills[56].level = 1;
        otherclient->cskills[57].id = 5903; // 866
        otherclient->cskills[57].level = 1;
        // Unique Items - artisan
        otherclient->cskills[58].id = 4801; // 561
        otherclient->cskills[58].level = 9;
        otherclient->cskills[59].id = 4811; // 562
        otherclient->cskills[59].level = 9;

        SendPM (thisclient, "Relogin For Get All Skills");
    }
    else
    {
        /*
        // Mileage Items - For which jobs?
        otherclient->cskills[xx].id = 5501; // 590 - all
        otherclient->cskills[xx].level = 1;
        otherclient->cskills[xx].id = 5502; // 591 - all
        otherclient->cskills[xx].level = 1;
        otherclient->cskills[xx].id = 5901; // 593  (can learn, but not showing)
        otherclient->cskills[xx].level = 1;
        // Unique Items - For which jobs?
        otherclient->cskills[xx].id = 4401; // 567 - all
        otherclient->cskills[xx].level = 1;
        otherclient->cskills[xx].id = 4402; // 568 - all
        otherclient->cskills[xx].level = 1;
        otherclient->cskills[xx].id = xxxx; // 563 - all
        otherclient->cskills[xx].level = x;
        otherclient->cskills[xx].id = xxxx; // 564 - all
        otherclient->cskills[xx].level = x;
        otherclient->cskills[xx].id = xxxx; // 566 - dealer
        otherclient->cskills[xx].level = x;
        */
        is_ok=false;
        SendPM(thisclient, "Can't add skills for this class");
    }

    if(is_ok)
    {
        thisclient->saveskills();
    }


    return true;
}

//GM: DeleteSkills {modified from allskill command - rl2171}
    bool CWorldServer::pakGMDelSkills(CPlayer* thisclient, char* name)
{

    CPlayer* otherclient = GetClientByCharName( name );
    if(otherclient==NULL)
    return true;

{
otherclient->cskills[0].id = 0;
otherclient->cskills[0].level = 1;
otherclient->cskills[1].id = 0;
otherclient->cskills[1].level = 1;
otherclient->cskills[2].id = 0;
otherclient->cskills[2].level = 1;
otherclient->cskills[3].id = 0;
otherclient->cskills[3].level = 1;
otherclient->cskills[4].id = 0;
otherclient->cskills[4].level = 1;
otherclient->cskills[5].id = 0;
otherclient->cskills[5].level = 1;
otherclient->cskills[6].id = 0;
otherclient->cskills[6].level = 1;
otherclient->cskills[7].id = 0;
otherclient->cskills[7].level = 1;
otherclient->cskills[8].id = 0;
otherclient->cskills[8].level = 1;
otherclient->cskills[9].id = 0;
otherclient->cskills[9].level = 1;
otherclient->cskills[10].id = 0;
otherclient->cskills[10].level = 1;
otherclient->cskills[11].id = 0;
otherclient->cskills[11].level = 1;
otherclient->cskills[12].id = 0;
otherclient->cskills[12].level = 1;
otherclient->cskills[13].id = 0;
otherclient->cskills[13].level = 1;
otherclient->cskills[14].id = 0;
otherclient->cskills[14].level = 1;
otherclient->cskills[15].id = 0;
otherclient->cskills[15].level = 1;
otherclient->cskills[16].id = 0;
otherclient->cskills[16].level = 1;
otherclient->cskills[17].id = 0;
otherclient->cskills[17].level = 1;
otherclient->cskills[18].id = 0;
otherclient->cskills[18].level = 1;
otherclient->cskills[19].id = 0;
otherclient->cskills[19].level = 1;
otherclient->cskills[20].id = 0;
otherclient->cskills[20].level = 1;
otherclient->cskills[21].id = 0;
otherclient->cskills[21].level = 1;
otherclient->cskills[22].id = 0;
otherclient->cskills[22].level = 1;
otherclient->cskills[23].id = 0;
otherclient->cskills[23].level = 1;
otherclient->cskills[24].id = 0;
otherclient->cskills[24].level = 1;
otherclient->cskills[25].id = 0;
otherclient->cskills[25].level = 1;
otherclient->cskills[26].id = 0;
otherclient->cskills[26].level = 1;
otherclient->cskills[27].id = 0;
otherclient->cskills[27].level = 1;
otherclient->cskills[28].id = 0;
otherclient->cskills[28].level = 1;
otherclient->cskills[29].id = 0;
otherclient->cskills[29].level = 1;
otherclient->cskills[30].id = 0;
otherclient->cskills[30].level = 1;
otherclient->cskills[31].id = 0;
otherclient->cskills[31].level = 1;
otherclient->cskills[32].id = 0;
otherclient->cskills[32].level = 1;
otherclient->cskills[33].id = 0;
otherclient->cskills[33].level = 1;
otherclient->cskills[34].id = 0;
otherclient->cskills[34].level = 1;
otherclient->cskills[35].id = 0;
otherclient->cskills[35].level = 1;
otherclient->cskills[36].id = 0;
otherclient->cskills[36].level = 1;
otherclient->cskills[37].id = 0;
otherclient->cskills[37].level = 1;
otherclient->cskills[38].id = 0;
otherclient->cskills[38].level = 1;
otherclient->cskills[39].id = 0;
otherclient->cskills[39].level = 1;
otherclient->cskills[40].id = 0;
otherclient->cskills[40].level = 1;
otherclient->cskills[41].id = 0;
otherclient->cskills[41].level = 1;
otherclient->cskills[42].id = 0;
otherclient->cskills[42].level = 1;
otherclient->cskills[43].id = 0;
otherclient->cskills[43].level = 1;
otherclient->cskills[44].id = 0;
otherclient->cskills[44].level = 1;
otherclient->cskills[45].id = 0;
otherclient->cskills[45].level = 1;
otherclient->cskills[46].id = 0;
otherclient->cskills[46].level = 1;
otherclient->cskills[47].id = 0;
otherclient->cskills[47].level = 1;
otherclient->cskills[48].id = 0;
otherclient->cskills[48].level = 1;
otherclient->cskills[49].id = 0;
otherclient->cskills[49].level = 1;
otherclient->cskills[50].id = 0;
otherclient->cskills[50].level = 1;
otherclient->cskills[51].id = 0;
otherclient->cskills[51].level = 1;
otherclient->cskills[52].id = 0;
otherclient->cskills[52].level = 1;
otherclient->cskills[53].id = 0;
otherclient->cskills[53].level = 1;
otherclient->cskills[54].id = 0;
otherclient->cskills[54].level = 1;
otherclient->cskills[55].id = 0;
otherclient->cskills[55].level = 1;
//added for ver 144
otherclient->cskills[56].id = 0;
otherclient->cskills[56].level = 1;
otherclient->cskills[57].id = 0;
otherclient->cskills[57].level = 1;
//added for ver.160
otherclient->cskills[58].id = 0;
otherclient->cskills[58].level = 1;
otherclient->cskills[59].id = 0;
otherclient->cskills[59].level = 1;

SendPM (thisclient, "Relogin to remove All Skills");
}
    return true;
}

