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
#include "worldmonster.h"

// called when a monster is attacked  [attack/use atk skill/use buff/run/summon]
bool CMonster::OnBeAttacked( CCharacter* Enemy )
{

    Battle->hitby = Enemy->clientid;

    if(!IsOnBattle( ))
    {
        //Some monsters do not attack and stay still (mc)
        if(!stay_still)
        {
            StartAction( Enemy, NORMAL_ATTACK, 0 );
        }
        else
        {
            StartAction( Enemy, STAY_STILL_ATTACK, 0 );
        }

    }

    return true;
}

// called when a monster die [give exp/give extra drop]
bool CMonster::OnDie( )
{
    CMap* map = GServer->MapList.Index[Position->Map];
    /*
    //AIP should do it...
    if(map->ghost!=0)
    {
     if((map->IsNight( ) || map->ghost==2) && !IsGhost( ) && !IsGhostSeed( ) && !IsSummon( ))
       {
        UINT gs = GServer->RandNumber( 0, 100 );
        if(gs<30) // 30% / 70%
            {   // spawn a ghost seed [for now will be 701 [level 1 ghost seed] ]
                map->AddMonster( 701, Position->current, 0, NULL, NULL, Position->respawn, true );
            }
        }
    }
    */

    //LMA: Union Wars :)
    //A stone has been killed?
    if (map->id==9&&(this->montype==431||this->montype==432||this->montype==433))
    {
       if (map->is_uw_fired)
       {
         if(this->montype==431)
            map->sunsetkilled=true;
         if(this->montype==432)
            map->sunrisekilled=true;
         if(this->montype==433)
            map->duskkilled=true;
       }

    }

    //UW END



    //LMA begin
    //CF mode 1
    //20070621-211100
    UINT special_exp=0;
    UINT special_lvl=0;


    if (map->is_cf==1)
    {
       //what monster is dead?
       if(this->montype==map->id_def_mon)
       {
           //oh my god, they killed a j&b !! (or the monster with exp)
           special_exp=(UINT) map->mon_exp;
           special_lvl= (UINT) map->mon_lvl;
           Log(MSG_INFO,"special_exp %i, special lvl %i",special_exp,special_lvl);
       }
       else
       {
           if (this->montype!=map->id_temp_mon)
           {
                UINT gs = GServer->RandNumber( 0, 100 );
                if(gs<map->percent)
                {
                  //we use the temporary monster as a decoy.
                  fPoint position_cf = GServer->RandInCircle( Position->current, 50 );
                  CMonster* monster2 = map->AddMonster( map->id_temp_mon, position_cf, 0, NULL, NULL, 0, true );
                }

           }

       }

    }

    GServer->GiveExp( this , special_lvl, special_exp );
    //LMA End


    return true;
}
// called when we create a new monster [attack players?]
bool CMonster::OnSpawn( bool Attack )
{
     lastSighCheck = clock();
    if(IsGhost( ) && Attack )
    {
        CPlayer* player = GetNearPlayer( );
        if(player==NULL) // no players or too far
            return true;
        StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
    }

    return true;
}

// [not]called when a monster is almost dead [run/use only skills/call a healer? :S xD]
bool CMonster::OnAlmostDie( )
{
    return true;
}

// called when a enemy is on sight
bool CMonster::OnEnemyOnSight( CPlayer* Enemy )
{
    clock_t etime = clock() - lastSighCheck;
    if(etime<5000) return true;
    if(!IsOnBattle( ))
    {
        if(thisnpc->aggresive>1)
        {
            UINT aggro = GServer->RandNumber(2,15);
            if(thisnpc->aggresive>=aggro && !IsGhostSeed( ))
            {
                Enemy->ClearObject( this->clientid );
				SpawnMonster(Enemy, this );
                StartAction( (CCharacter*) Enemy, NORMAL_ATTACK, 0 );
            }
            else
            if(IsGhostSeed( ) || thisnpc->aggresive>5)
                MoveTo( Enemy->Position->current, true );
        }
        lastSighCheck = clock();
    }
    return true;
}

// called when enemy die
bool CMonster::OnEnemyDie( CCharacter* Enemy )
{
    Log(MSG_INFO,"An enemy died, let's stop battle");
    Position->destiny = Position->source; //ON MOB DIE
    ClearBattle( Battle );
    MoveTo( Position->source );
    return true;
}

bool CMonster::OnFar( )
{
    //if Owner too far away, we kill the bonfire.
    if(IsBonfire())
    {
       UnspawnMonster( );
       return true;
    }

    Position->destiny = Position->source; //ON TARGET LOST
    ClearBattle( Battle );
    MoveTo( Position->source );
    return true;
}


//LMA: Arnold code for guardiantree
bool CMonster::Guardiantree(CMonster* monster,CMap* map)
{
     if(Stats->HP>9000)monster->hitcount=0;
     switch (monster->hitcount)
     {
         case 0:
              if(Stats->HP<9000)
              {
                  for(unsigned char i=0;i<5;i++){
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=1;
              }
              break;
         case 1:
              if(Stats->HP<8000)
              {
                  for(unsigned char i=0;i<5;i++){
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=2;
              }
              break;
         case 2:
              if(Stats->HP<7000)
              {
                  for(unsigned char i=0;i<5;i++){
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=3;
              }
              break;
         case 3:
              if(Stats->HP<6000)
              {
                  for(unsigned char i=0;i<5;i++){
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=4;
              }
              break;
         case 4:
              if(Stats->HP<5000)
              {
                  for(unsigned char i=0;i<5;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=5;
              }
              break;
         case 5:
              if(Stats->HP<4000)
              {
                  for(unsigned char i=0;i<5;i++){
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=6;
              }
              break;
         case 6:
              if(Stats->HP<3000)
              {
                  for(unsigned char i=0;i<5;i++){
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=7;
              }
              break;
         case 7:
              if(Stats->HP<2000)
              {
                  for(unsigned char i=0;i<5;i++){
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      map->AddMonster( 210, position, 0, NULL, NULL, 0, true );
                  }
                  monster->hitcount=8;
              }
              break;
         default:
                 monster->hitcount=9;

     }
}

//LMA: Handling Moonchild siblings
bool CMonster::MoonChild(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.98))
         monster->hitcount=0;

     CPlayer* player = NULL;


     switch (monster->hitcount)
     {
         case 0:
              if(Stats->HP<(Stats->MaxHP*0.98))
              {
                  Log(MSG_INFO,"case 0 for the MC");
                  for(unsigned char i=0;i<2;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 657, position, 0, NULL, NULL, 0, true );

                      if(i==0)
                         player = monster2->GetNearPlayer(20);    //getting near player.

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );

                  }
                  for(unsigned char i=0;i<3;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 658, position, 0, NULL, NULL, 0, true );

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );

                  }

                  monster->hitcount=1;
              }
              break;
         case 1:
              if(Stats->HP<(Stats->MaxHP*0.80))
              {
                  Log(MSG_INFO,"case 1 for the MC");
                  for(unsigned char i=0;i<3;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 657, position, 0, NULL, NULL, 0, true );

                      if(i==0)
                         player = monster2->GetNearPlayer(20);    //getting near player.

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
                  }
                  for(unsigned char i=0;i<4;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 658, position, 0, NULL, NULL, 0, true );

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );

                  }
                  monster->hitcount=2;
              }
              break;
         case 2:
              if(Stats->HP<(Stats->MaxHP*0.70))
              {
                  Log(MSG_INFO,"case 2 for the MC");
                  for(unsigned char i=0;i<10;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 657, position, 0, NULL, NULL, 0, true );

                      if(i==0)
                         player = monster2->GetNearPlayer(20);    //getting near player.

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );

                  }
                  for(unsigned char i=0;i<5;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 658, position, 0, NULL, NULL, 0, true );

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );

                  }
                  monster->hitcount=monster->maxhitcount;
              }
              break;

         default:
                 monster->hitcount=monster->maxhitcount;

     }


     return true;
}

//LMA: Handling Worm Dragon :)
bool CMonster::WormDragon(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.50))
         return true;

     CPlayer* player = NULL;
     int nb_worms =0;
     nb_worms=GServer->RandNumber(2,4);

      Log(MSG_INFO,"case 0 for the Worm Dragon (%i)",nb_worms);
      for(unsigned char i=0;i<nb_worms;i++)
      {
          fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
          CMonster* monster2=map->AddMonster( 202, position, 0, NULL, NULL, 0, true );

          if(i==0)
             player = monster2->GetNearPlayer(20);    //getting near player.

         if(player!=NULL)
             monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
      }

      monster->hitcount=monster->maxhitcount;


     return true;
}

//LMA: added by rl2171 Handling Cursed Ant Vagabond :)
bool CMonster::AntVagabond(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.50))
         return true;

     CPlayer* player = NULL;
     int nb_destroyers =0;
     nb_destroyers=GServer->RandNumber(1,2);

      Log(MSG_INFO,"case 0 for the Cursed Ant Vagabond (%i)",nb_destroyers);
      for(unsigned char i=0;i<nb_destroyers;i++)
      {
          fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
          CMonster* monster2=map->AddMonster( 1567, position, 0, NULL, NULL, 0, true );

          if(i==0)
             player = monster2->GetNearPlayer(20);    //getting near player.

         if(player!=NULL)
             monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
      }

      monster->hitcount=monster->maxhitcount;


     return true;
}

///LMA: added by rl2171 Handling Dragon Eggs :)
bool CMonster::DragonEgg(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.98))
         monster->hitcount=0;

     CPlayer* player = NULL;


     switch (monster->hitcount)
     {
         case 0:
              if(Stats->HP<(Stats->MaxHP*0.98))
              {
                  Log(MSG_INFO,"case 0 for the Dragon Egg");
                  for(unsigned char i=0;i<2;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 663, position, 0, NULL, NULL, 0, true );

                      if(i==0)
                         player = monster2->GetNearPlayer(20);    //getting near player.

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );

                  }

                  monster->hitcount=1;
              }
              break;
         case 1:
              if(Stats->HP<(Stats->MaxHP*0.80))
              {
                  Log(MSG_INFO,"case 1 for the Dragon Egg");
                  for(unsigned char i=0;i<3;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 663, position, 0, NULL, NULL, 0, true );

                      if(i==0)
                         player = monster2->GetNearPlayer(20);    //getting near player.

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
                  }
                  monster->hitcount=2;
              }
              break;
         case 2:
              if(Stats->HP<(Stats->MaxHP*0.70))
              {
                  Log(MSG_INFO,"case 2 for the Dragon Egg");
                  for(unsigned char i=0;i<2;i++)
                  {
                      fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
                      CMonster* monster2=map->AddMonster( 663, position, 0, NULL, NULL, 0, true );

                      if(i==0)
                         player = monster2->GetNearPlayer(20);    //getting near player.

                     if(player!=NULL)
                         monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );

                  }
                  monster->hitcount=monster->maxhitcount;
              }
              break;

         default:
                 monster->hitcount=monster->maxhitcount;

     }


     return true;
}
/*bool CMonster::DragonEgg(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.60))
         return true;

     CPlayer* player = NULL;
     int nb_egg =0;
     nb_egg=GServer->RandNumber(2,4);

      Log(MSG_INFO,"case 0 for the Dragon Eggs (%i)",nb_egg);
      for(unsigned char i=0;i<nb_egg;i++)
      {
          fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
          CMonster* monster2=map->AddMonster( 663, position, 0, NULL, NULL, 0, true );

          if(i==0)
             player = monster2->GetNearPlayer(20);    //getting near player.

         if(player!=NULL)
             monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
      }

      monster->hitcount=monster->maxhitcount;


     return true;
}
*/
///LMA: added by rl2171 Handling 1st Turak :)
bool CMonster::Turak1(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.00))
         return true;

     CPlayer* player = NULL;
     int nb_turak1 =0;
     nb_turak1=GServer->RandNumber(1,1);

      Log(MSG_INFO,"case 0 for the 1st Turak (%i)",nb_turak1);
      for(unsigned char i=0;i<nb_turak1;i++)
      {
          fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
          CMonster* monster2=map->AddMonster( 559, position, 0, NULL, NULL, 0, true );

          if(i==0)
             player = monster2->GetNearPlayer(20);    //getting near player.

         if(player!=NULL)
             monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
      }

      monster->hitcount=monster->maxhitcount;


     return true;
}

//LMA: added by rl2171 Handling 2nd Turak :)
bool CMonster::Turak2(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.00))
         return true;

     CPlayer* player = NULL;
     int nb_turak2 =0;
     nb_turak2=GServer->RandNumber(1,1);

      Log(MSG_INFO,"case 0 for the 2nd Turak (%i)",nb_turak2);
      for(unsigned char i=0;i<nb_turak2;i++)
      {
          fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
          CMonster* monster2=map->AddMonster( 560, position, 0, NULL, NULL, 0, true );

          if(i==0)
             player = monster2->GetNearPlayer(20);    //getting near player.

         if(player!=NULL)
             monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
      }

      monster->hitcount=monster->maxhitcount;


     return true;
}
/*
//LMA: added by rl2171 Handling 3rd Turak :)
bool CMonster::Turak3(CMonster* monster,CMap* map)
{
     if (monster->hitcount>=monster->maxhitcount)
        return true;

     if(Stats->HP>(Stats->MaxHP*0.50))
         return true;

     CPlayer* player = NULL;
     int nb_turak3 =0;
     nb_turak3=GServer->RandNumber(1,1);

      Log(MSG_INFO,"case 0 for the 3rd Turak (%i)",nb_turak3);
      for(unsigned char i=0;i<nb_turak3;i++)
      {
          fPoint position = GServer->RandInCircle( monster->Position->current, 5 );
          CMonster* monster2=map->AddMonster( 559, position, 0, NULL, NULL, 0, true );

          if(i==0)
             player = monster2->GetNearPlayer(20);    //getting near player.

         if(player!=NULL)
             monster2->StartAction( (CCharacter*)player, NORMAL_ATTACK, 0 );
      }

      monster->hitcount=monster->maxhitcount;


     return true;
}

*/


//LMA: AIP
void CMonster::DoAi(int ainumber,char type)//ainumber is monster->AI type is add=0 idle=1 attacking=2 attacked=3 after killing target=4 hp<1=5
{
    CAip* script = NULL;
    int AIWatch = GServer->Config.AIWatch;
    int aiindex = (ainumber*0x10000)+(type*0x100);
    if(type == 5)
    {
        Log(MSG_INFO,"Monster died. Activating AI type 5");
    }

    //LMA: halloween debug (Odelo).
    bool lma_debug=false;
    int nb_turns=0;
    if(ainumber==1116)
    {
        lma_debug=true;
    }


    for(unsigned j=0; j < GServer->AipList.size(); j++)
    {
        if (GServer->AipList.at(j)->AipID == aiindex)
        {
            nb_turns++;
            if (lma_debug)
                Log(MSG_INFO,"BEGIN CDT Turn %i",nb_turns);

            script = GServer->AipList.at(j);
            /*
            if(ainumber == AIWatch)Log(MSG_DEBUG, "Record count = %i",script->recordcount[type]);
            if(ainumber == AIWatch)Log(MSG_DEBUG, "aiCondition type: %i AI index: %i condition count %i", type, aiindex, script->ConditionCount);
            */
            if (lma_debug)
            {
                Log(MSG_DEBUG, "DoAI1116 script %i, Record count = %i",script->AipID,script->recordcount[type]);
                Log(MSG_DEBUG, "DoAI1116 aiCondition type: %i AI index: %i condition count %i", type, aiindex, script->ConditionCount);
            }

            int success = AI_SUCCESS; //needs to be AI_SUCCESS otherwise would not perform conditionless actions
            int thisaction = 0;

            for (dword i = 0; i < script->ConditionCount; i++)
            {
                int command = script->Conditions[i]->opcode;
                if (command > 30 || command < 0) continue;
                success = (*GServer->aiCondFunc[command])(GServer, this, script->Conditions[i]->data);
                if(ainumber == AIWatch)Log(MSG_DEBUG, "aiCondition %03u returned %d", command, success);

                if (success == AI_FAILURE)
                {
                    if (lma_debug)
                        Log(MSG_DEBUG, "aiCondition %03u, %i/%i Failure.",command,i,script->ConditionCount-1);
                    break;
                }
                else
                {
                    if (lma_debug)
                        Log(MSG_DEBUG, "aiCondition %03u, %i/%i Success.",command,i,script->ConditionCount-1);
                }

            }

            if (lma_debug)
                Log(MSG_INFO,"END CDT Turn %i",nb_turns);


            if (success == AI_SUCCESS)
            {
                if (lma_debug)
                    Log(MSG_INFO,"BEGIN ACT Turn %i",nb_turns);

                for (dword i = 0; i < script->ActionCount; i++)
                {
                    int command = script->Actions[i]->opcode;
                    if (command > 38 || command < 0) continue;
                    success = (*GServer->aiActFunc[command])(GServer, this, script->Actions[i]->data);
                    if(ainumber == AIWatch)Log(MSG_DEBUG, "aiAction: %03u returned %d", command, success);

                    if(lma_debug)
                        Log(MSG_DEBUG, "aiAction: %03u returned %d, %i/%i", command, success,i,script->ActionCount-1);
                }

                if(success == AI_SUCCESS)
                {
                  if(lma_debug)
                        Log(MSG_INFO,"END ACT SUCCESS Turn %i",nb_turns);
                    return; //automatically return after performing the first successful action
                }
                else
                {
                  if(lma_debug)
                        Log(MSG_INFO,"END ACT FAILURE Turn %i",nb_turns);
                }

            }

            aiindex++;
        }
        else if(GServer->AipList.at(j)->AipID > aiindex)
        {
            return;
        }

    }
    return;
}
