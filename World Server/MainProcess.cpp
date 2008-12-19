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
    bool only_npc=false;    //LMA: AIP is done by NPC even when no player in map.

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

            //LMA: test for Union.
            only_npc=false;
            if( map->PlayerList.size()<1 )
            {
                only_npc=true;    //LMA: AIP is done by NPC even when no player in map.
                //continue;
            }

            if (!only_npc)
            {
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

                     //Log(MSG_INFO,"Player %s in map %i, position->map %i",player->CharInfo->charname,map->id,player->Position->Map);

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

                    if(monster->Stats->HP<0)
                    {
                        Log(MSG_INFO,"A monster %i is dead in map %i (position->Map %i)",monster->montype,map->id,monster->Position->Map);
                    }

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


                        /*LMA: should be done by AIP now.
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
                        //if((monster->montype==560)&&(monster->hitcount<monster->maxhitcount))
                           // monster->Turak3(monster,map);      //rl2171: 3rd Turak under attack (LMA)
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

                    //osprose
                    if (monster->IsSummon())
                    {
                        monster->SummonUpdate(monster,map, j);
                        continue;
                    }

                }

            }

            if(only_npc)
                pthread_mutex_lock( &map->MonsterMutex );

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

                         int lma_previous_eventID=npc->thisnpc->eventid;
                         //Log(MSG_INFO,"DoAI for NPC %i",npc->npctype);
                         monster->DoAi(monster->thisnpc->AI, 1);

                         //LMA: check if eventID changed, if we do it in AIP conditions / actions, it just fails...
                         if (lma_previous_eventID!=monster->thisnpc->eventid)
                         {
                            Log(MSG_WARNING,"(1)Event ID not the same NPC %i from %i to %i in map %i, npc->thisnpc->eventid=%i !",npc->npctype,lma_previous_eventID,monster->thisnpc->eventid,map->id,npc->thisnpc->eventid);
                            npc->thisnpc->eventid=monster->thisnpc->eventid;
                            npc->event=npc->thisnpc->eventid;
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

                //LMA: Sometimes another NPC does the job for you.
                if(npc->thisnpc->eventid!=GServer->ObjVar[npc->npctype][0])
                {
                    int new_event_id=GServer->ObjVar[npc->npctype][0];
                    Log(MSG_WARNING,"(2)Event ID not the same NPC %i from %i to %i in map %i, npc->thisnpc->eventid=%i !",npc->npctype,npc->thisnpc->eventid,new_event_id,map->id,npc->thisnpc->eventid);
                    npc->thisnpc->eventid=new_event_id;
                    npc->event=new_event_id;
                    //LMA: We have to change the event ID here since we didn't send the clientID :(
                    BEGINPACKET( pak, 0x790 );
                    ADDWORD    ( pak, npc->clientid );
                    ADDWORD    ( pak, npc->thisnpc->eventid );
                    GServer->SendToAllInMap(&pak,map->id);
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
                if(!player->Session->inGame)
                {
                    continue;
                }
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
