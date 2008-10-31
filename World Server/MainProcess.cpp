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

// Map Process
PVOID MapProcess( PVOID TS )
{
    bool ok_cont=false;
    UINT loopcount=0;
    clock_t time_skill=0;
    time_t next_time=0;
    time_t next_timeuw=0;
    int no_dial[2]={5,1};


    while(GServer->ServerOnline)
    {
        loopcount++;            //geobot: refresh only every 100 cycles
        if (loopcount<100)
           continue;
        loopcount=0;

        pthread_mutex_lock( &GServer->PlayerMutex );
        pthread_mutex_lock( &GServer->MapMutex );

        for(UINT i=0;i<GServer->MapList.Map.size();i++)
        {
            CMap* map = GServer->MapList.Map.at(i);

            //LMA: Special for Union Wars and Union Slaughter.
            time_t etime=time(NULL);
            //LMA: Union War
            if(map->id==9&&GServer->Config.unionwar==1)
            {
                /*
               if(map->uw_begin==0)
               {
                  //2do: use the time from Command
                  map->uw_end=0;
                  map->is_uw_fired=false;
                  map->uw_begin=etime+5*60; //In 5 minutes...
                  next_timeuw=etime+60;
                  GServer->UWDecide();
                  GServer->UWNPCdialogs(no_dial[map->attackers-1]);
               }
               */

               if(!map->announce_done)
               {
                   next_timeuw=1;
               }

               if (!map->is_uw_fired)
               {
                   if(etime>map->uw_begin)
                   {
                     if(GServer->CheckEnoughUW())
                     {
                        GServer->UWNPCdialogs(3);
                        map->is_uw_fired=true;
                        //let's summon the Stones and NPC
                        GServer->UWstones(1);
                        map->npc_id=GServer->SummonNPCUW();

                        map->uw_end=etime+(GServer->Config.unionwarduration*60);
                        next_timeuw=etime+60;

                        Log(MSG_INFO,"Union War has begun...");
                     }
                     else
                     {
                        GServer->UWNPCdialogs(4);
                        Log(MSG_INFO,"UW canceled...");
                        char text[200];
                        sprintf( text, "Union War has been canceled since not enough players were there...");
                        BEGINPACKET( pak, 0x702 );
                	    ADDSTRING  ( pak, "Mighty Fairy" );
                    	ADDSTRING  ( pak, "> " );
                    	ADDSTRING  ( pak, text );
                    	ADDBYTE    ( pak, 0x00 );
                    	GServer->SendToAllInMap  ( &pak,2);
                    	map->uw_begin=0;
                    	map->announce_done=false;
                    	GServer->Config.unionwar=0;

                    	if(GServer->Config.unionwarloop)
                    	{
                            map->uw_begin=etime+(GServer->Config.unionwardelay_loop*60);
                            next_timeuw=etime+60;;
                            GServer->Config.unionwar=1;
                            Log(MSG_INFO,"We loop after cancel, it'll be in %i",GServer->Config.unionwardelay_loop);
                    	}

                     }

                   }
                   else
                   {
                       //let's warn users :)
                       if(next_timeuw>0&&etime>=next_timeuw)
                       {
                          UINT remaining_time=0;
                          remaining_time=(UINT) ((map->uw_begin-etime)/60);
                          next_timeuw=0;
                          if(remaining_time>0)
                          {
                                //We change the NPC dialog.
                                if (!map->announce_done)
                                {
                                    GServer->UWDecide();
                                    GServer->UWNPCdialogs(no_dial[map->attackers-1]);
                                    char text[200];
                                    sprintf( text, "UW will begin in %i minutes, fetch the quest at your Union Master and wait near me !!!",remaining_time);

                                    BEGINPACKET( pak, 0x702 );
                                    ADDSTRING  ( pak, "Mighty Fairy" );
                                    ADDSTRING  ( pak, "> " );
                                    ADDSTRING  ( pak, text );
                                    ADDBYTE    ( pak, 0x00 );
                                    GServer->SendToAllInMap  ( &pak,2);
                                    Log(MSG_INFO,"Message time for USW (annouce): %i",remaining_time);
                                }
                                else
                                {
                                   Log(MSG_INFO,"Message time for USW: %i",remaining_time);
                                    char text[200];
                                    sprintf( text, "Union War will begin in %i minutes, Please wait near Mayor !!",remaining_time);
                                    BEGINPACKET( pak, 0x702 );
                                    ADDSTRING  ( pak, "Mighty Fairy" );
                                    ADDSTRING  ( pak, "> " );
                                    ADDSTRING  ( pak, text );
                                    ADDBYTE    ( pak, 0x00 );
                                    GServer->SendToAllInMap  ( &pak,2);
                                }

                            	//next_timeuw=etime+60;
                                next_timeuw=etime+GServer->UWNextTime(remaining_time);
                          }

                       }

                   }

               }
                else
                {
                    //is it ended?
                    if (etime>map->uw_end||map->sunsetkilled)
                    {
                       GServer->UWOver();
                       Log(MSG_INFO,"UW is over...");
                        map->is_uw_fired=false;
                        map->uw_end=0;
                        map->uw_begin=0;
                        GServer->Config.unionwar=0;
                        next_timeuw=0;
                        map->announce_done=false;

                        if (map->uw_loop)
                        {
                            map->uw_begin=etime+(GServer->Config.unionwardelay_loop*60);
                            next_timeuw=etime+60;
                            GServer->Config.unionwar=1;
                            Log(MSG_INFO,"UW: Looping %i",GServer->Config.unionwardelay_loop);
                        }

                    }
                    else
                    {
                        //sunrise killed? let's spawn sunset then :)
                        if (map->sunrisekilled&&!map->sunsetspawned)
                        {
                           GServer->UWstones();
                        }

                        if(map->duskkilled)
                        {
                           GServer->UWstones(2);
                        }

                       if(next_timeuw>0&&etime>=next_timeuw)
                       {
                          UINT remaining_time=0;
                          remaining_time=(UINT) ((map->uw_end-etime)/60);
                          Log(MSG_INFO,"Message time for UW end: %i",remaining_time);
                          next_timeuw=0;
                          if (remaining_time>0)
                          {
                              char text[200];
                                sprintf( text, "Make Haste, Union War will end in %i minutes !!!",remaining_time);
                                BEGINPACKET( pak, 0x702 );
                        	    ADDSTRING  ( pak, "Mighty Fairy" );
                            	ADDSTRING  ( pak, "> " );
                            	ADDSTRING  ( pak, text );
                            	ADDBYTE    ( pak, 0x00 );
                            	GServer->SendToAllInMap  ( &pak,9);
                            	//next_timeuw=etime+60;
                            	next_timeuw=etime+GServer->UWNextTime(remaining_time);
                          }

                       }

                    }

                }

            }


            //LMA: Union Slaughter...
            if (map->id==8&&GServer->Config.unionslaughter==1)
            {
                /*
               if(map->utime_begin==0)
               {
                  //2do: use the time from Command
                  map->utime_begin=etime+5*60; //In 5 minutes...
                  next_time=etime+60;
               }
                */

               if (!map->is_union_fired)
               {
                   if(etime>map->utime_begin)
                   {
                     if(GServer->CheckOkUnion())
                     {
                        map->is_union_fired=true;
                        for (int kmap=0;kmap<8;kmap++)
                        {
                            map->nb_killed[kmap]=0;
                            map->nb_kills[kmap]=0;
                        }

                        map->utime_end=etime+(GServer->Config.unionduration*60);
                        next_time=etime+60;
                        Log(MSG_INFO,"Union Slaughter has begun...");
                     }
                     else
                     {
                        Log(MSG_INFO,"US canceled...");
                        char text[200];
                        sprintf( text, "Union Slaughter has been canceled since not enough players were there...");
                        BEGINPACKET( pak, 0x702 );
                	    ADDSTRING  ( pak, "Mighty Fairy" );
                    	ADDSTRING  ( pak, "> " );
                    	ADDSTRING  ( pak, text );
                    	ADDBYTE    ( pak, 0x00 );
                    	GServer->SendToAllInMap  ( &pak,2);
                         map->utime_begin=0;
                         map->utime_end=0;
                         next_time=0;
                    	GServer->Config.unionslaughter=0;

                        if(GServer->Config.unionslaughterloop)
                        {
                             map->utime_begin=etime+(GServer->Config.unionslaughterdelay_loop*60);
                             next_time=etime+60;
                            GServer->Config.unionslaughter=1;
                        }

                     }

                   }
                   else
                   {
                       //let's warn users :)
                       if(next_time>0&&etime>=next_time)
                       {
                          UINT remaining_time=0;
                          remaining_time=(UINT) ((map->utime_begin-etime)/60);
                          next_time=0;
                          if(remaining_time>0)
                          {
                               Log(MSG_INFO,"Message time for US: %i",remaining_time);
                                char text[200];
                                sprintf( text, "Union Slaughter will begin in %i minutes, Please join mayor of Junon Polis to protect your Emblem !!",remaining_time);
                                BEGINPACKET( pak, 0x702 );
                        	    ADDSTRING  ( pak, "Mighty Fairy" );
                            	ADDSTRING  ( pak, "> " );
                            	ADDSTRING  ( pak, text );
                            	ADDBYTE    ( pak, 0x00 );
                            	GServer->SendToAllInMap  ( &pak,2);
                            	//next_time=etime+60;
                            	next_time=etime+GServer->UWNextTime(remaining_time);
                          }

                       }

                   }

               }
                else
                {
                    //is it ended?
                    if (etime>map->utime_end)
                    {
                       GServer->WarIsOver();
                       Log(MSG_INFO,"US is over...");
                        map->is_union_fired=false;
                         map->utime_begin=0;
                         map->utime_end=0;
                         next_time=0;
                    	GServer->Config.unionslaughter=0;

                        if(GServer->Config.unionslaughterloop)
                        {
                             map->utime_begin=etime+(GServer->Config.unionslaughterdelay_loop*60);
                             next_time=etime+60;
                            GServer->Config.unionslaughter=1;
                        }

                    }
                    else
                    {
                       if(next_time>0&&etime>=next_time)
                       {
                          UINT remaining_time=0;
                          remaining_time=(UINT) ((map->utime_end-etime)/60);
                          Log(MSG_INFO,"Message time for US end: %i",remaining_time);
                          next_time=0;
                          if (remaining_time>0)
                          {
                              char text[200];
                                sprintf( text, "Make Haste, Union Slaughter will end in %i minutes !!!",remaining_time);
                                BEGINPACKET( pak, 0x702 );
                        	    ADDSTRING  ( pak, "Mighty Fairy" );
                            	ADDSTRING  ( pak, "> " );
                            	ADDSTRING  ( pak, text );
                            	ADDBYTE    ( pak, 0x00 );
                            	GServer->SendToAllInMap  ( &pak,8);
                            	//next_time=etime+60;
                            	next_time=etime+GServer->UWNextTime(remaining_time);
                          }

                       }

                    }

                }

            }
            //END UW and US Code

            if( map->PlayerList.size()<1 )
                continue;

            // Player update //------------------------
            for(UINT j=0;j<map->PlayerList.size();j++)
            {
                CPlayer* player = map->PlayerList.at(j);
                if(!player->Session->inGame) continue;

                if(player->IsDead( ))
                {
                      player->lastRegenTime=0;
                      player->lastShowTime=0;
                      continue;
                 }

                 player->RefreshHPMP();         //LMA HP / MP Jumping
                if(player->UpdateValues( )) //Does nothing except for rides... equals to true if player isn't on the back seat
                    player->UpdatePosition(false);
                if(player->IsOnBattle( ))
                    player->DoAttack( );
                player->CheckItems( );
                player->RefreshBuff( );
                player->PlayerHeal( );
                player->Regeneration( );
                player->CheckPlayerLevelUP( );
                player->CheckPortal( );  //Custom Events
                player->CheckEvents( );  //Custom Events

                player->CheckDoubleEquip(); //LMA: Core fix for double weapon and shield
                player->CheckZulies( );

                //Fuel handling.
                if (player->Status->Stance==DRIVING&&(player->last_fuel>0)&&(clock()-player->last_fuel>60000))
                {
                  //We kill some fuel every now and then :)
                  player->TakeFuel();
                  player->last_fuel=clock();
                }

                //LMA: mileage coupon checks.
                time_t etime=time(NULL);
                if(player->bonusxp>1&&(etime>=player->timerxp))
                {
                  BEGINPACKET( pak, 0x702 );
                  ADDSTRING( pak, "[Mileage] Bonus Xp vanished.");
                  ADDBYTE( pak, 0 );
                  player->client->SendPacket(&pak);
                  player->bonusxp=1;
                  player->timerxp=0;
                  player->wait_validation=0;
                }

                if(player->Shop->ShopType>0&&(etime>=player->Shop->mil_shop_time))
                {
                  BEGINPACKET( pak, 0x702 );
                  ADDSTRING( pak, "[Mileage] Mileage shop expired !");
                  ADDBYTE( pak, 0 );
                  player->client->SendPacket(&pak);
                  player->Shop->ShopType=0;
                  player->Shop->mil_shop_time=0;
                }

            }
            // Monster update //------------------------
            pthread_mutex_lock( &map->MonsterMutex );

            for(UINT j=0;j<map->MonsterList.size();j++)
            {
                CMonster* monster = map->MonsterList.at(j);

                //LMA: AIP CODE
				if(monster->hitcount == 0xFF)//this is a delay for new monster spawns this might olso fix invisible monsters(if they attack directly on spawning the client dosn't get the attack packet(its not in it's visible list yet))
                {
                    if(1000 < (UINT)GServer->round((clock( ) - monster->lastAiUpdate)))
                    {
                        //Log(MSG_DEBUG,"DoAIP mainprocess monster loop %i",monster->thisnpc->AI);
                        monster->hitcount = 0;
                        monster->DoAi(monster->thisnpc->AI, 0);
                        monster->lastAiUpdate=clock();
                    }
                }
                //END AIP CODE

                //LMA: maps (using grid now?)
                 ok_cont=false;
                 if (GServer->Config.testgrid!=0)
                     ok_cont=monster->PlayerInGrid( );
                 else
                     ok_cont=monster->PlayerInRange( );

                if (!ok_cont)
                    continue;

                //LMA: daynight stuff :) kinda vampire code for spawns ^_^
                if((monster->daynight!=0)&&((monster->daynight==2&&!map->IsNight())||(monster->daynight==1&&map->IsNight())))
                {
                    //Bye bye little monster...
                    map->DeleteMonster( monster, true, j );
                    continue;
                }

               //LMA begin
               //20070621-211100
                //Beans for CF...
                if(map->is_cf==1&&monster->montype==map->id_temp_mon)
                {
                  //we use butterflies (temporary monster) as decoys ;)
                   UINT etime = (UINT)round((clock( ) - monster->SpawnTime));
                   if(etime<20000)
                   {
                     //if(!monster->PlayerInRange( )) continue;
                     if(!monster->UpdateValues( )) continue;
                     monster->UpdatePosition(monster->stay_still);
                   }
                   else if(etime>20000 && etime<120000) // convert temporary monster to definitive 20 seconds after the temporary was spawned
                   {
                    //if(!monster->PlayerInRange( )) continue;
                    if(!monster->UpdateValues( )) continue;
                        monster->UpdatePosition(monster->stay_still);
                      CPlayer* player = monster->GetNearPlayer( );
                      if(player==NULL) continue;
                      //time for j&b (definitive monster) to come :)
                      UINT montype = map->id_def_mon;

                      //We kill the temporary and summon the new one.
                      fPoint position_cf = GServer->RandInCircle( player->Position->current,20 );
                      Log( MSG_WARNING, "deleting butterfly for J&B, ID %u",monster->clientid);
                      map->DeleteMonster( monster, true, j );
                      CMonster* monster2=map->AddMonster( montype, position_cf, 0, NULL, NULL, 0, true );
                      //just appear and do nothing :)
                      monster2->StartAction( (CCharacter*)player, 9, 0 );
                      continue;

                      //other way
                      /*
                      map->ConverToMonster( monster, montype , true );
                      monster->StartAction( (CCharacter*)player, 9, 0 );
                      */
                    }
                    else if (etime>120000) // delete sweet butterfly (temporary monster)...
                    {
                      map->DeleteMonster( monster, true, j ); continue;
                    }

                  }

                  //if the monster is not killed soon enough, let's destroy it.
                  if(map->is_cf!=0&&monster->montype==map->id_def_mon)
                  {
                       UINT etime = (UINT)round((clock( ) - monster->SpawnTime));
                       if(etime>180000)
                       {
                            map->DeleteMonster( monster, true, j ); continue;
                       }

                        //if(!monster->PlayerInRange( )) continue;
                        if(!monster->UpdateValues( )) continue;
                        monster->UpdatePosition(monster->stay_still);
                  }
                //LMA END


                //LMA BEGIN
                //20070621-211100
                //patch for quest 2010, purified rackies
                //They have to disepear in time...
                /*LMA: handled by AIP?
                if (monster->montype==95)
                {
                       UINT etime = (UINT)round((clock( ) - monster->SpawnTime));
                       if(etime>20000)
                       {
                         //20 seconds should be enough :)
                         map->DeleteMonster( monster, true, j );
                         continue;
                       }

                        //if(!monster->PlayerInRange( )) continue;
                        if(!monster->UpdateValues( )) continue;
                        monster->UpdatePosition(monster->stay_still);
                }
                //LMA END
                */

               //Let's kill the bonfires after 2 minutes.. by Terr0risT
                if (monster->IsBonfire( ))
                    {
                        UINT etime = (UINT)round((clock( ) - monster->SpawnTime));
                        if (etime>120000) // delete our bonfire...
                        {
                           map->DeleteMonster( monster, true, j ); continue;
                        }
                    }


                /*LMA: handled by AIP?
                //A lot of code only for ghosts ======================================================================
                if((map->IsNight( ) || map->ghost==2))
                {
                    if (monster->IsGhostSeed( ))
                    {
                        UINT etime = (UINT)round((clock( ) - monster->SpawnTime));
                        if(etime<20000) {if(!monster->PlayerInRange( )) continue; if(!monster->UpdateValues( )) continue; monster->UpdatePosition(monster->stay_still);}
                        else if(etime>20000 && etime<120000) // convert seed to ghost btw 20 and 120sec after the seed was spawned
                        {
                            //if(!monster->PlayerInRange( )) continue;
                            if(!monster->UpdateValues( )) continue;
                                monster->UpdatePosition(monster->stay_still);
                            CPlayer* player = monster->GetNearPlayer( );
                            if(player==NULL) continue;
                            UINT montype = GServer->GetLevelGhost( player->Position->Map, player->Stats->Level );
                            map->ConverToMonster( monster, montype , true );
                            monster->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
                        }
                        else if (etime>120000) // delete seed after 120 seconde after the seed was spawned
                        {
                            map->DeleteMonster( monster, true, j ); continue;
                        }
                    }
                    if (monster->IsGhost( ))
                    {
                        UINT etime = (UINT)round((clock( ) - monster->SpawnTime));
                        if (etime>180000 && !monster->IsOnBattle( ) && !monster->IsMoving( )) // delete ghost after 180 sec after the ghost was spawned if not in battle
                        {
                            map->DeleteMonster( monster, true, j ); continue;
                        }
                    }
                }
                else
                if((!map->IsNight( ) && map->ghost!=2) && (monster->IsGhostSeed( ) || monster->IsGhost( ))) // if day, delete seed/ghost
                {
                    map->DeleteMonster( monster, true, j );
                    continue;
                }
                */


                //General monsters===============================================================
                //LMA: moved to beginning...
                //if(!monster->PlayerInRange( )) continue;
                if(!monster->UpdateValues( )) continue;
                    monster->UpdatePosition(monster->stay_still);
                if(monster->IsOnBattle( ))
                {
                    //monster->DoAttack( );
                    if(2000<(UINT)GServer->round((clock( ) - monster->lastAiUpdate)))
                    {
                        //Log(MSG_DEBUG,"DoAIP mainprocess monster on battle %i,2",monster->thisnpc->AI);
                         monster->DoAi(monster->thisnpc->AI, 2);
                         monster->lastAiUpdate = clock();
                         //Log(MSG_INFO,"Monster type: %i current HP: %i",monster->montype, monster->Stats->HP);
                    }
                    else
                    {
                         //Log(MSG_INFO,"Monster doing attack");
                         monster->DoAttack( );
                    }

                      //LMA: TEST for monsters attack skills...
                    if (fmmonstertype>0&&fmmonstertype==monster->montype&&fskill>0&&(ftypeskill>=1&&ftypeskill<=3))
                    {
                       if (time_skill==0)
                          time_skill=clock();
                       UINT etime = (UINT)round((clock( ) - time_skill));
                       //Skill every 10 seconds.
                       if(etime>10000)
                       {
                           int skill_value=fskill;
                           time_skill=clock();

                           switch (ftypeskill)
                           {
                                  case 1:
                                       {
                                              //attack skill.
                                       }
                                       break;

                                  case 3:
                                       {
                                             //self buff.
                                       }
                                       break;
                                  case 2:
                                       {
                                           //debuff
                                           /*
                                            [Thu Oct 11 04:03:05 2007 ][world]IN  0x7b3 -
                                            d5 aa
                                            a2 a9
                                            eb 0d
                                            8d 04
                                            b8 3c f8 48
                                            cb ed 01 49
                                            06
                                            */
                                            Log(MSG_INFO,"trying this one, skill value: %i",skill_value);
                                            CPlayer* player = monster->GetNearPlayer( );

                                            BEGINPACKET (pak,0x7b3);
                                            ADDWORD (pak,monster->clientid);
                                            ADDWORD (pak,player->clientid);
                                            ADDWORD (pak,skill_value);

                                            if (skill_value==2969)
                                            {
                                               ADDWORD (pak,1113);
                                            }
                                            else
                                            {
                                               ADDWORD (pak,1165);
                                            }

                                            ADDFLOAT (pak,player->Position->current.x);
                                            ADDFLOAT (pak,player->Position->current.y);
                                            ADDBYTE (pak,0x06);
                                            player->client->SendPacket(&pak);

                                            /*
                                            [Thu Oct 11 04:03:05 2007 ][world]IN  0x7bb -
                                            d5 aa
                                            */
                                            RESETPACKET (pak,0x7bb);
                                            ADDWORD (pak,monster->clientid);
                                            player->client->SendPacket(&pak);
                                            /*
                                            [Thu Oct 11 04:03:06 2007 ][world]IN  0x7b5 -
                                            a2 a9
                                            d5 aa
                                            eb 0d
                                            64 00
                                            01
                                            */
                                            RESETPACKET (pak,0x7b5);
                                            ADDWORD (pak,player->clientid);
                                            ADDWORD (pak,monster->clientid);
                                            ADDWORD (pak,skill_value);

                                            if (skill_value==2969)
                                            {
                                               ADDWORD (pak,35);
                                            }
                                            else
                                            {
                                               ADDWORD (pak,100);
                                            }

                                            ADDBYTE (pak,0x01);
                                            player->client->SendPacket(&pak);

                                            /*
                                            [Thu Oct 11 04:03:06 2007 ][world]IN  0x7b9 -
                                            d5 aa
                                            eb 0d
                                            */
                                            RESETPACKET (pak,0x7b9);
                                            ADDWORD (pak,monster->clientid);
                                            ADDWORD (pak,skill_value);
                                            player->client->SendPacket(&pak);
                                       }
                                       break;
                                  }

                        }

                    }

                    if(monster->montype==208)
                        monster->Guardiantree(monster,map);      //LMA: guardiantree 208 (Arnold)
                    if((monster->montype==659)&&(monster->hitcount<monster->maxhitcount))
                        monster->MoonChild(monster,map);      //LMA: Moonchild under attack
                    if((monster->montype==201)&&(monster->hitcount<monster->maxhitcount))
                        monster->WormDragon(monster,map);      //LMA: Worm Dragon under attack
                    if((monster->montype==1572)&&(monster->hitcount<monster->maxhitcount))
                        monster->AntVagabond(monster,map);      //rl2171: Cursed Ant Vagabond under attack (LMA)
                    if((monster->montype==662)&&(monster->hitcount<monster->maxhitcount))
                        monster->DragonEgg(monster,map);      //rl2171: Dragon Egg under attack (LMA)
                    if((monster->montype==558)&&(monster->hitcount<monster->maxhitcount))
                        monster->Turak1(monster,map);      //rl2171: 1st Turak under attack (LMA)
                    if((monster->montype==559)&&(monster->hitcount<monster->maxhitcount))
                        monster->Turak2(monster,map);      //rl2171: 2nd Turak under attack (LMA)
/*                    if((monster->montype==560)&&(monster->hitcount<monster->maxhitcount))
                        monster->Turak3(monster,map);      //rl2171: 3rd Turak under attack (LMA)
*/
                }
                else if(!monster->IsOnBattle() && !monster->IsDead( ))
                {
                    if(2000<(UINT)GServer->round((clock( ) - monster->lastAiUpdate)))
                    {
                        //Log(MSG_DEBUG,"DoAIP mainprocess monster iddle? %i,1",monster->thisnpc->AI);
                        monster->DoAi(monster->thisnpc->AI, 1);
                        monster->lastAiUpdate = clock();
                    }
                }
				else
				{
					if(monster->IsSummon( ))
					{// if is summon and is not attacking we reduce his life 1%
						time_t elapsedTime = time(NULL) - monster->lastLifeUpdate;
						if(elapsedTime>=5) // every 5 seconds
						{
							monster->Stats->HP -= (long int)ceil(monster->GetMaxHP( )/100);
							monster->lastLifeUpdate = time(NULL);
							if(monster->Stats->HP<=0)
							{
								map->DeleteMonster( monster, true, j ); continue;
							}
						}
					}
				}

                monster->RefreshBuff( );
                if(monster->IsDead( ))
                {
                    Log(MSG_DEBUG,"DoAIP mainprocess monster is dead %i",monster->thisnpc->AI);
                    monster->DoAi(monster->thisnpc->AI, 5);
                    monster->OnDie( );
                }

            }

            //LMA: AIP for NPC.
            for(UINT j=0;j<map->NPCList.size();j++)
            {
                CNPC* npc = map->NPCList.at(j);
                if(npc->thisnpc->AI != 0)
                {
                     if(60000<(UINT)GServer->round((clock( ) - npc->lastAiUpdate))) //check every minute. Conditions seem to be based on 6 minute segments
                     {
                         CNPCData* thisnpc = GServer->GetNPCDataByID( npc->npctype );
                         if(thisnpc == NULL)
                         {
                             Log( MSG_WARNING, "Invalid montype %i", npc->npctype );
                             continue;
                         }
                         CMonster* monster = new (nothrow) CMonster( npc->pos, npc->npctype, map->id, 0, 0  );
                         monster->aip_npctype=npc->npctype;
                         monster->aip_clientid=npc->clientid;
                         monster->thisnpc = thisnpc;

                         if (monster->thisnpc->AI==1116)
                            Log(MSG_DEBUG,"DoAIP mainprocess NPC %i,1",monster->thisnpc->AI);

                         int lma_previous_eventID=npc->thisnpc->eventid;
                         monster->DoAi(monster->thisnpc->AI, 1);

                         //LMA: check if eventID changed, if we do it in AIP conditions / actions, it just fails...
                         if (lma_previous_eventID!=monster->thisnpc->eventid)
                         {
                            Log(MSG_WARNING,"Event ID not the same NPC %i from %i to %i in map %i, npc->thisnpc->eventid=%i !",npc->npctype,lma_previous_eventID,monster->thisnpc->eventid,map->id,npc->thisnpc->eventid);
                            npc->thisnpc->eventid=monster->thisnpc->eventid;
                            //LMA: We have to change the event ID here since we didn't send the clientID :(
                            BEGINPACKET( pak, 0x790 );
                            ADDWORD    ( pak, npc->clientid );
                            ADDWORD    ( pak, npc->thisnpc->eventid );
                            GServer->SendToAllInMap(&pak,map->id);
                         }

                         delete monster;
                         npc->lastAiUpdate = clock();
                     }
                }
            }

            pthread_mutex_unlock( &map->MonsterMutex );
        }
        pthread_mutex_unlock( &GServer->MapMutex );
        pthread_mutex_unlock( &GServer->PlayerMutex );

        #ifdef _WIN32
        Sleep(GServer->Config.MapDelay);
        #else
        usleep(GServer->Config.MapDelay);
        #endif
    }
    pthread_exit( NULL );
}


// Visibility Process
PVOID VisibilityProcess(PVOID TS)
{
    while(GServer->ServerOnline)
    {
        pthread_mutex_lock( &GServer->PlayerMutex );
        pthread_mutex_lock( &GServer->MapMutex );
        for(UINT i=0;i<GServer->MapList.Map.size();i++)
        {
            CMap* map = GServer->MapList.Map.at(i);
            if( map->PlayerList.size()<1 )
                continue;
            for(UINT j=0;j<map->PlayerList.size();j++)
            {
                CPlayer* player = map->PlayerList.at(j);
                if(!player->Session->inGame) continue;
                if(!player->VisiblityList()) Log(MSG_WARNING, "Visibility False: %u", player->clientid );
                if( GServer->Config.AUTOSAVE == 1 )
                {
                    clock_t etime = clock() - player->lastSaveTime;
                    if( etime >= GServer->Config.SAVETIME*1000 )
                    {
                        player->savedata( );
                        player->lastSaveTime = clock();
                    }
                }
            }
        }
        pthread_mutex_unlock( &GServer->MapMutex );
        pthread_mutex_unlock( &GServer->PlayerMutex );
        #ifdef _WIN32
        Sleep(GServer->Config.VisualDelay);
        #else
        usleep(GServer->Config.VisualDelay);
        #endif
    }
    pthread_exit(NULL);
}

// World Process
PVOID WorldProcess( PVOID TS )
{
    while( GServer->ServerOnline )
    {
        pthread_mutex_lock( &GServer->MapMutex );
        for(UINT i=0;i<GServer->MapList.Map.size();i++)
        {
            CMap* map = GServer->MapList.Map.at(i);
            if( map->PlayerList.size()<1 )
                continue;
            map->UpdateTime( );
            pthread_mutex_lock( &map->DropMutex );
            map->CleanDrops( );
            pthread_mutex_unlock( &map->DropMutex );
            pthread_mutex_lock( &map->MonsterMutex );
            map->RespawnMonster( );
            pthread_mutex_unlock( &map->MonsterMutex );
        }
        pthread_mutex_unlock( &GServer->MapMutex );
        GServer->RefreshFairy( );
        #ifdef _WIN32
        Sleep(GServer->Config.WorldDelay);
        #else
        usleep(GServer->Config.WorldDelay);
        #endif
    }
    pthread_exit(NULL);
}

// Shutdown Server Process
PVOID ShutdownServer(PVOID TS)
{
    int minutes = (int)TS;
    #ifdef _WIN32
    Sleep(minutes*60000);
    #else
    usleep(minutes*60000);
    #endif
    Log( MSG_INFO, "Saving User Information... " );
    GServer->DisconnectAll();
    Log( MSG_INFO, "Waiting Process to ShutDown... " );
    GServer->ServerOnline = false;
    int status,res;
    res = pthread_join( GServer->WorldThread[0], (PVOID*)&status );
    if(res)
    {
        Log( MSG_WARNING, "World thread can't be joined" );
    }
    else
    {
        Log( MSG_INFO, "World thread closed." );
    }
    res = pthread_join( GServer->WorldThread[1], (PVOID*)&status );
    if(res)
    {
        Log( MSG_WARNING, "Visibility thread can't be joined" );
    }
    else
    {
        Log( MSG_INFO, "Visibility thread closed." );
    }
    res = pthread_join( GServer->MapThread[0], (PVOID*)&status );
    if(res)
    {
        Log( MSG_WARNING, "Map thread can't be joined" );
    }
    else
    {
        Log( MSG_INFO, "Map thread closed." );
    }
    Log( MSG_INFO, "All Threads Closed." );
    GServer->isActive = false;
    pthread_exit(NULL);
}
