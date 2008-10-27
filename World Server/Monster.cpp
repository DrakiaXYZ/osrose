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

// update attack values and destiny  position
bool CMonster::UpdateValues( )
{
    //LMA: Some special case where special monsters stay still (mc, bonfires and so on...)
    if(stay_still&&(!IsBonfire()))
       return true;

    if(IsSummon( ) && CanMove( ))
    {
        CPlayer* thisclient = GetOwner( );
        if(thisclient!=NULL)
        {
            if(!IsBonfire())
            {
                if(!IsOnBattle( ) && thisclient->IsAttacking( ))
                {
                    Battle->target = thisclient->Battle->target;
                    Battle->atktarget = Battle->target;
                    Battle->atktype = NORMAL_ATTACK;
                    Battle->contatk = true;
                    CCharacter* Enemy = GetCharTarget( );

                    //LMA: TEST monster skills.
                    int lma_rand=GServer->RandNumber(0,10);
                    if(Enemy!=NULL)
                    {

                        if(montype==663)
                        {
                           Log(MSG_INFO,"Telling to do a skill attack");
                           StartAction( Enemy, SKILL_ATTACK,3562);
                        }
                        else
                        {
                           StartAction( Enemy, NORMAL_ATTACK );
                        }

                    }


                }
                else
                if(!IsOnBattle( ))
                {
                    Position->source = thisclient->Position->current;
                    float distance = GServer->distance( Position->destiny , thisclient->Position->current );
                    if((distance>15 && !IsOnBattle()) || distance>50)
                        Move( );
                }

            }
            else
            {
                //LMA: Let's kill bonfires if owner too far away :).
                float distance = GServer->distance( Position->current , thisclient->Position->current );
                if(distance>25)
                {
                   UnspawnMonster( );
                   return false;
                }

                return true;
            }

        }
        else
        {
            UnspawnMonster( );
            return false;
        }
    }
    if(!IsMoving( ) && !IsOnBattle( ) && CanMove( ))
    {
        clock_t etime = clock() - Position->lastMoveTime;
        if(etime > 20*CLOCKS_PER_SEC)
            Move( );
    }
    if(!IsSummon( ))
    {
        CPlayer* player = GetNearPlayer( 10 );
        if(player!=NULL)
            OnEnemyOnSight( player );
    }
    return true;
}

// Spawn a monster
//LMA: added handling of skill summons.
void CMonster::SpawnMonster( CPlayer* player, CMonster* thismon )
{
    BEGINPACKET( pak, 0x792 );
	ADDWORD    ( pak, clientid );
	ADDFLOAT   ( pak, Position->current.x*100 );
	ADDFLOAT   ( pak, Position->current.y*100 );

	if((thismon->bonushp>0||thismon->bonusmp>0)&&(thismon->skillid>0))
	{
    	ADDFLOAT   ( pak, 0xcdcdcdcd );
    	ADDFLOAT   ( pak, 0xcdcdcdcd );
    }
    else
    {
     	ADDFLOAT   ( pak, Position->destiny.x*100 );
    	ADDFLOAT   ( pak, Position->destiny.y*100 );
    }

	if(IsDead( ))
	{
	   ADDWORD    ( pak, 0x0003 );
	   ADDWORD    ( pak, 0x0000 );
    }
	else if(IsOnBattle( ))
	{
       //LMA: for supportive summons (lucky ghost...)
       if(Battle->bufftarget==Battle->target)
       {
    	   ADDWORD    ( pak, 0x0002 );
    	   ADDWORD    ( pak, 0x0000 );
       }
       else
       {
    	   ADDWORD    ( pak, 0x0002 );
    	   ADDWORD    ( pak, Battle->target );
       }

    }
	else if(IsMoving( ))
	{
	   ADDWORD    ( pak, 0x0001 );
	   ADDWORD    ( pak, 0x0000 );
    }
    else
    {
    	ADDWORD    ( pak, 0x0000 );
    	ADDWORD    ( pak, 0x0000 );
    }
	ADDBYTE    ( pak, 0x00 );
	ADDDWORD   ( pak, Stats->HP );
	if(thismon->owner != player->clientid)
        {
            CMap* map = GServer->MapList.Index[Position->Map];

            //LMA: UW
            if(map->id==9)
            {
                int lma_alliance=0x07D0;
                if(montype!=433)
                {
                    if (map->attackers==1)
                    {
                        lma_alliance=0x03E8;
                    }

                }
                else
                {
                    if (map->attackers==2)
                    {
                        lma_alliance=0x03E8;
                    }

                }

                ADDDWORD(pak, lma_alliance);
                Log(MSG_INFO,"Spawn monster %i",lma_alliance);
            }
            else
            {
                if(IsSummon( ) && map->allowpvp!=0) {ADDDWORD( pak, 0x00000064 );} //Hostil
                else if (IsSummon( ) && map->allowpvp==0) {ADDDWORD ( pak, 0x00000000 );}//Friendly
                else {ADDDWORD( pak, 0x00000064 );} //Hostil
            }

        }
    else {ADDDWORD( pak, 0x00000000 );}//Friendly
    ADDDWORD( pak, GServer->BuildBuffs( this ) );
	ADDWORD   ( pak, montype );
	ADDWORD   ( pak, 0x0000 );
	if(IsSummon( ))
    {
        ADDWORD( pak, owner );

        if (thismon->skillid>0)
        {
           ADDWORD( pak, thismon->skillid ); //id del skill (si es summon de skill)
        }
        else
        {
           ADDWORD( pak, 0x0000 ); //id del skill (si es summon de skill)
        }

    }
	player->client->SendPacket( &pak );

    //LMA: supportive summons (lucky ghost)
    if(IsSummon()&&buffid>0&&(player==GetOwner()))
    {
        Log(MSG_INFO,"The summon is spawned");
        /*CPlayer* player = GetOwner( );
        if (ownplayer==NULL)
           return true;*/
        StartAction( player,SUMMON_BUFF,buffid);
        Log(MSG_INFO,"completly");
        buffid=0;  //only one buff
    }

}

// UnSpawn a Monster
bool CMonster::UnspawnMonster( )
{
    GServer->MapList.Index[Position->Map]->DeleteMonster( this, true );
    return true;
}

// Move a mob (random place)
void CMonster::Move( )
{
    Position->destiny  = GServer->RandInCircle( Position->source, 10 );
//    Position->lastMoveTime = clock();
    ClearBattle( Battle );
    BEGINPACKET( pak, 0x797 );
	ADDWORD    ( pak, clientid );
	ADDWORD    ( pak, 0x0000 );//???
	ADDWORD    ( pak, Stats->Move_Speed ); //speed
	ADDFLOAT   ( pak, Position->destiny.x*100 );
	ADDFLOAT   ( pak, Position->destiny.y*100 );
	ADDWORD    ( pak, 0xcdcd );
	//ADDBYTE    ( pak, 0x01 );
	ADDBYTE	   ( pak, thisnpc->stance );    //AIP
	GServer->SendToVisible(&pak, this);
}

// Move a mob (specified point)
void CMonster::MoveTo( fPoint nPos, bool randcircle )
{
    if(randcircle) Position->destiny  = GServer->RandInCircle( nPos, 5 );
    else Position->destiny  = nPos;
//    Position->lastMoveTime = clock();
    BEGINPACKET( pak, 0x797 );
	ADDWORD    ( pak, clientid );
	ADDWORD    ( pak, 0x0000 ); // ???
	ADDWORD    ( pak, Stats->Move_Speed );
	ADDFLOAT   ( pak, Position->destiny.x*100 );
	ADDFLOAT   ( pak, Position->destiny.y*100 );
	ADDWORD    ( pak, 0xcdcd );
	//ADDBYTE    ( pak, 0x01 );
	ADDBYTE    ( pak, thisnpc->stance); //AIP
	GServer->SendToVisible(&pak, this );
}
