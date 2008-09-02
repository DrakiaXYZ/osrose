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
#include "character.h"
#include "worldserver.h"

void CCharacter::DoAttack( )
{
     /*
     if(IsSummon())
       Log(MSG_INFO,"Someone attacks type=%i,skillid=%i",Battle->atktype,Battle->skillid);
     */

    CMap* map = GServer->MapList.Index[Position->Map];
    switch(Battle->atktype)
    {
        case NORMAL_ATTACK://normal attack
        {
            CCharacter* Enemy = GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( Enemy ) && CanAttack( ))
                NormalAttack( Enemy );
        }
        break;
        case SKILL_ATTACK://skill attack
        {
            CCharacter* Enemy = GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( Enemy, skill ) && CanAttack( ))
                SkillAttack( Enemy, skill );
        }
        break;
        case MONSTER_SKILL_ATTACK://LMA: monster skill attack
        {
            CCharacter* Enemy = GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( Enemy, skill ) && CanAttack( ))
                SkillAttack( Enemy, skill );
        }
        break;
        case SUMMON_BUFF://Summon buffs (support)
        {
            //LMA: For summon that buff player :)
            if (Battle->bufftarget==0)
               break;
            CCharacter* master = GetCharBuffTarget( );
            if(master==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( master, skill ) && CanAttack( ))
                SummonBuffSkill( master, skill );
        }
        break;
        case MONSTER_SKILL_BUFF://LMA: monster buffs
        {
            CCharacter* Enemy= GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( Enemy, skill ) && CanAttack( ))
                BuffSkill( Enemy, skill );
        }
        break;
       case SKILL_BUFF://buffs
        {

            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            } // debuff or buff? [netwolf]
            switch (skill->target)
             {
                    case 5:
                    {
                     CCharacter* Enemy = GetCharTarget( );
                     if(Enemy==NULL)
                     {
                                     ClearBattle( Battle );
                                     return;
                     }
                     if(IsTargetReached( Enemy, skill ) && CanAttack( ))
                     {
                        Log(MSG_INFO,"%i:: DeBuff time for %i",clientid,Enemy->clientid);
                        DebuffSkill( Enemy, skill );
                     }
                    }break;
                    default:
                    {
                            CCharacter* Target = GetCharTarget( );
                            if(Target==NULL)
                            {
                                     ClearBattle( Battle );
                                     return;
                            }
                            if(IsTargetReached( Target, skill ) && CanAttack( ))
                            {
                               Log(MSG_INFO,"%i:: Buff time for %i",clientid,Target->clientid);
                               BuffSkill( Target, skill );
                            }
                    }break;
            }

        }
        break;  //LMA: break was missing?
        case SKILL_AOE:
        case SKILL_SELF:
        case AOE_TARGET:
        {
            CCharacter* Enemy = NULL;
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(Battle->atktype==AOE_TARGET)
            {
                //LMA 2008/09/02: new version, the target is a zone, not a monster... so we stick with aoedestiny ;)
                /*
                Enemy = GetCharTarget( );
                if(Enemy==NULL)
                {
                    //LMA: oups, our temp monster has been killed, let's find another one if possible :)
                    Log(MSG_INFO,"[DoAttack] In AOE_TARGET (Enemy not found)");
                    CMonster* tempmonster=GServer->LookAOEMonster(this);
                    if (tempmonster==NULL)
                    {
                        Log(MSG_INFO,"[DoAttack] In AOE_TARGET (no new monsters in range)");
                        ClearBattle( Battle );
                        return;
                    }

                    Battle->skilltarget = tempmonster->clientid;
                    Battle->target = tempmonster->clientid;     //LMA: just for compatibility use...
                    Enemy = GetCharTarget( );
                    if(Enemy==NULL)
                    {
                        Log(MSG_INFO,"[DoAttack] In AOE_TARGET (Enemy2 not found)");
                        ClearBattle( Battle );
                        return;
                    }

                }

                if(IsTargetReached( Enemy, skill ) && CanAttack( ))
                {
                    Log(MSG_INFO,"[DoAttack] In AOE_TARGET time for AoeSkill");
                    AoeSkill( skill, Enemy );
                }
                else
                {
                    Log(MSG_INFO,"[DoAttack] In AOE_TARGET not reached or can't attack");
                }
                */
                float distance = GServer->distance( Position->current, Position->aoedestiny );
                if(distance<=skill->range)
                {
                    Log(MSG_INFO,"[DoAttack] In AOE_TARGET time for AoeSkill");
                    AoeSkill( skill, NULL );    //LMA: no specific Enemy in Zone.
                }
                else
                {
                    Log(MSG_INFO,"[DoAttack] In AOE_TARGET not reached or can't attack");
                }

            }
            else
            {
                if(Enemy==NULL)
                {
                   Log(MSG_INFO,"player %i: default AOE attack (%i/%i) %i for ennemy NULL ", clientid,Battle->atktype,AOE_TARGET,skill->id);
                }
                else
                {
                   Log(MSG_INFO,"player %i: default AOE attack (%i/%i) %i for ennemy %i ", clientid,Battle->atktype,AOE_TARGET,skill->id,Enemy->clientid);
                }

                AoeSkill( skill, Enemy );
            }
        }
        break;
        case BUFF_SELF:
        {
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            BuffSkill( this, skill );
        }
        break;
        case MONSTER_BUFF_SELF:    //LMA: monster selfs buffs.
        {
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            BuffSkill( this, skill );
        }
        break;
       case BUFF_AOE:
        {
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            //[netwolf]
            switch (skill->target)
             {
                    case 5:
                    {
                         CCharacter* Enemy = NULL;
                         AoeDebuff( skill, Enemy );
                    } break;
                    default:
                    {
                            AoeBuff( skill );
                    }   break;
             }
        }
        break;
    }

}

// do normal attack
void CCharacter::NormalAttack( CCharacter* Enemy )
{
    Position->destiny = Position->current;
    reduceItemsLifeSpan( false );
    Enemy->OnBeAttacked( this );
    float attack = (float)Stats->Attack_Power - ((Enemy->Stats->Magic_Defense+Enemy->Stats->Defense )/2);
    if(attack<0) attack = 5;
    attack *= 0.65;
    float d_attack = attack / 100;
    if(attack<0) attack = 5;
    attack += (float)GServer->RandNumber( 0, 7 ) - 2;
    attack += ((Stats->Level - Enemy->Stats->Level) * d_attack);
    if(attack<7) attack = 5;
    long int hitpower = (long int)floor(attack + GServer->RandNumber(0, 4));
    /*if(IsPlayer( ))
        hitpower = (long int)floor(attack * 1.2 );*/
    if(IsPlayer( )) //temp fix to find balance btw monster and player
        hitpower = (long int)floor(attack * (GServer->Config.PlayerDmg/100.00));
    if(IsMonster( )) //temp fix to find balance btw monster and player
        hitpower = (long int)floor(attack * (GServer->Config.MonsterDmg/100.00));

    //TEST
    long int hitsave=hitpower;
    hitpower+=Stats->ExtraDamage_add;
    hitpower+=((hitpower*(Stats->ExtraDamage))/100);  //LMA: ED, Devilking / Arnold
    //Log(MSG_INFO,"ED: before %i, after %i (extra *%i + %i)",hitsave,hitpower,Stats->ExtraDamage,Stats->ExtraDamage_add);


    bool critical = false;
    if(hitpower<=0)
    {
        hitpower = 0;
    }
    else
    {
        if(GServer->RandNumber(0,300)<Stats->Critical)
        {
            hitpower = (long int)floor(hitpower*1.5);
            critical = true;
        }
    }
    // dodge
    unsigned int hitvalue = (unsigned int)floor(Stats->Accury * 50 / Enemy->Stats->Dodge);
    if(hitvalue>100) hitvalue = 100;
    if(GServer->RandNumber( 0, 100 )>hitvalue)
        hitpower = 0; // dodged
    if(!Enemy->IsSummon( ) && Enemy->IsMonster( ))
    {
        Enemy->AddDamage( this, hitpower );
    }

    Enemy->Stats->HP -= hitpower;

    // actually the target was hit, if it was sleeping, set duration of
    // sleep to 0. map process will remove sleep then at next player-update
    if (Enemy->Status->Sleep != 0xff) {
        Enemy->MagicStatus[Enemy->Status->Sleep].Duration = 0;
    }

    //if (IsPlayer())
    //printf("Target suffered %i physical damage, %i HP still remain \n", hitpower, Enemy->Stats->HP);
    //else printf("Mob did %i physical damage, %i HP still remain \n", hitpower, Enemy->Stats->HP);
    Enemy->reduceItemsLifeSpan(true);
    BEGINPACKET( pak, 0x799 );
    ADDWORD    ( pak, clientid );
    ADDWORD    ( pak, Battle->atktarget );
    ADDDWORD   ( pak, hitpower );
    if(Enemy->IsDead())
    {
        //LMA: Union Wars
        if (IsPlayer()&&Enemy->IsPlayer()&&(Position->Map==8||Position->Map==9))
        {
            Log(MSG_INFO,"UWKILL begin normal atk");
            UWKill(Enemy);
            ClearBattle( Battle );
        }
        else
        {
            Log(MSG_INFO,"Not for UWKILL, killer isplayer? %i, killed? %i, map? %i",IsPlayer(),Enemy->IsPlayer(),Position->Map==MAP_UW);
        }
        //

        Log(MSG_INFO,"Someone died.");

        CDrop* thisdrop = NULL;
        ADDDWORD   ( pak, critical?28:16 );
        if(!Enemy->IsSummon( ) && !Enemy->IsPlayer( ))
        {
            thisdrop = Enemy->GetDrop( );
            if(thisdrop!=NULL)
            {
                ADDFLOAT   ( pak, thisdrop->pos.x*100 );
                ADDFLOAT   ( pak, thisdrop->pos.y*100 );
                if(thisdrop->type==1)
                {
                    ADDDWORD( pak, 0xccccccdf );
                    ADDDWORD( pak, thisdrop->amount );
                    ADDDWORD( pak, 0xcccccccc );
                    ADDWORD ( pak, 0xcccc );
                }
                else
                {
                    ADDDWORD   ( pak, GServer->BuildItemHead( thisdrop->item ) );
                    ADDDWORD   ( pak, GServer->BuildItemData( thisdrop->item ) );
                    ADDDWORD( pak, 0x00000000 );
                    ADDWORD ( pak, 0x0000 );
                }
                ADDWORD    ( pak, thisdrop->clientid );
                ADDWORD    ( pak, thisdrop->owner );
                CMap* map = GServer->MapList.Index[thisdrop->posMap];
                map->AddDrop( thisdrop );
            }
        }
        GServer->SendToVisible( &pak, Enemy, thisdrop );
        OnEnemyDie( Enemy );
    }
    else
    {
        ADDDWORD   ( pak, (hitpower>0?(critical?12:0):0) );
        GServer->SendToVisible( &pak, Enemy );
    }
    ReduceABC( );
    Battle->lastAtkTime = clock( );
}

// do skill attack
bool CCharacter::SkillAttack( CCharacter* Enemy, CSkills* skill )
{
    Position->destiny = Position->current;
    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }
    Battle->castTime = 0;
    UseAtkSkill( Enemy, skill );
    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0) Stats->MP=0;
    if(Battle->contatk)
    {
        Battle->atktype = NORMAL_ATTACK;
        Battle->skilltarget = 0;
        Battle->atktarget = Battle->target;
        Battle->skillid = 0;
    }
    else
    {
        ClearBattle( Battle );
    }
    GServer->DoSkillScript( this, skill );       //So far only used for summons
    Battle->lastAtkTime = clock( );
    return true;
}

// do buff skill
bool CCharacter::BuffSkill( CCharacter* Target, CSkills* skill )
{
    Position->destiny = Position->current;
    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        //Log(MSG_INFO,"7bb battle casttime==0");
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
        {
            //Log(MSG_INFO,"etime<SKILL_DELAY: %i<%i",etime,SKILL_DELAY);
            return true;
        }

    }

    //Log(MSG_INFO,"new stat MP %i",Stats->MP);

    Battle->castTime = 0;
    UseBuffSkill( Target, skill );
    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0)
    {
        Stats->MP=0;
    }

    ClearBattle( Battle );
    GServer->DoSkillScript( this, skill );
    Battle->lastAtkTime = clock( );
    return true;
}

// do Debuff skill [netwolf]
bool CCharacter::DebuffSkill( CCharacter* Enemy, CSkills* skill )
{
    Position->destiny = Position->current;
    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }
    Battle->castTime = 0;
    UseDebuffSkill( Enemy, skill );
    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0) Stats->MP=0;
    ClearBattle( Battle );
    GServer->DoSkillScript( this, skill );
    Battle->lastAtkTime = clock( );
    return true;
}

//LMA: A summon does a buff skill
//2do: check if master is debuffed.
bool CCharacter::SummonBuffSkill( CCharacter* Target, CSkills* skill )
{
    Position->destiny = Position->current;
    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        //Log(MSG_INFO,"0x7bb");
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }

    //LMA: For now, it seems the summon buff only one time :(
    //Log(MSG_INFO,"Real buff skill");
    Battle->castTime = 0;
    UseBuffSkill( Target, skill );
    ClearBattle( Battle );
    GServer->DoSkillScript( this, skill );
    Battle->lastAtkTime = clock( );
    return true;
}

// do AoE skill
bool CCharacter::AoeSkill( CSkills* skill, CCharacter* Enemy )
{
    Log(MSG_INFO,"In AOE Skill");
    Position->destiny = Position->current;

    //LMA: handling case of AOE_SKILLS and AOE_TARGET (the target point is not the same).
    fPoint goodtarget;
    goodtarget=Position->current;
    if (Battle->atktype==AOE_TARGET)
    {
       goodtarget=Position->aoedestiny;
    }

    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        //LMA: No delay for AOE_TARGET skill (zone)
        if (Battle->atktype!=AOE_TARGET)
        {
            clock_t etime = clock() - Battle->castTime;
            if(etime<SKILL_DELAY)
                return true;
        }

    }

    Battle->castTime = 0;
    CMap* map = GServer->MapList.Index[Position->Map];
    for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* monster = map->MonsterList.at(i);
        if(monster->clientid==clientid) continue;
        if(IsSummon( ) || IsPlayer( ))
        {
            if(monster->IsSummon( ) && (map->allowpvp==0 || monster->owner==clientid)) continue;
        }
        else
        {
            if(!monster->IsSummon( )) continue;
        }
        if(GServer->IsMonInCircle( goodtarget,monster->Position->current,(float)skill->aoeradius+1))
        {
            Log(MSG_INFO,"AOE Attack (1) monster %i",monster->montype);
            UseAtkSkill( (CCharacter*) monster, skill );
        }

    }

    if(map->allowpvp!=0 || (IsMonster( ) && !IsSummon( )))
    {
        for(UINT i=0;i<map->PlayerList.size();i++)
        {
            CPlayer* player = map->PlayerList.at(i);
            if(player->clientid==clientid) continue;
            if(GServer->IsMonInCircle( goodtarget,player->Position->current,(float)skill->aoeradius+1))
            {
                Log(MSG_INFO,"AOE Attack (2) player %s",player->CharInfo->charname);
                UseAtkSkill( (CCharacter*) player, skill );
            }

        }
    }

    if(Enemy!=NULL)
    {
        if(!Enemy->IsDead( ))
        {
            //LMA: Union Wars
            if (IsPlayer()&&Enemy->IsPlayer()&&(Position->Map==8||Position->Map==9))
            {
                Log(MSG_INFO,"UWKill begin for AOE skill");
                UWKill(Enemy);
                ClearBattle( Battle );
            }
            //

            Battle->atktarget = Battle->target;
            Battle->atktype = NORMAL_ATTACK;
            Battle->skilltarget = 0;
            Battle->skillid = 0;
        }
        else ClearBattle( Battle );
    }
    else ClearBattle( Battle );
    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0) Stats->MP=0;
    Battle->lastAtkTime = clock( );
    return true;
}

bool CCharacter::AoeBuff( CSkills* skill )
{
    Position->destiny = Position->current;

    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }
    Battle->castTime = 0;
    CMap* map = GServer->MapList.Index[Position->Map];

    //LMA: GM AOE Buff (Devilking).
    if (skill->gm_aoe!=0)
    {
         Log(MSG_INFO,"GM AOE buff");
        for(UINT i=0;i<map->PlayerList.size();i++)
        {
            CPlayer* player = map->PlayerList.at(i);
            if(GServer->IsMonInCircle( Position->current,player->Position->current,(float)skill->aoeradius+1))
            {
                 UseBuffSkill( (CCharacter*)player, skill );
                  Log(MSG_INFO,"Buffing %s ",player->CharInfo->charname);
            }

        }

    }
    else
    {
        if(skill->target==1 && GetParty( )==NULL)
        {
            UseBuffSkill( this, skill );
            ClearBattle( Battle );
            Battle->lastAtkTime = clock( );
            return true;
        }

        for(UINT i=0;i<map->PlayerList.size();i++)
        {
            CPlayer* player = map->PlayerList.at(i);
            switch(skill->target)
            {
                case 1: // party
                {
                    if(player->Party->party==GetParty( ))
                    {
                        if(GServer->IsMonInCircle( Position->current,player->Position->current,(float)skill->aoeradius+1))
                            UseBuffSkill( (CCharacter*)player, skill );
                    }
                }
            }
        }

    }

    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0) Stats->MP=0;
    ClearBattle( Battle );
    Battle->lastAtkTime = clock( );
    return true;
}

// Aoe Debuff [netwolf]
bool CCharacter::AoeDebuff( CSkills* skill, CCharacter* Enemy )
{
    Position->destiny = Position->current;

    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }
    Battle->castTime = 0;

    CMap* map = GServer->MapList.Index[Position->Map];
    for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* monster = map->MonsterList.at(i);
        if(monster->clientid==clientid) continue;
        if(IsSummon( ) || IsPlayer( ))
        {
            if(monster->IsSummon( ) && (map->allowpvp==0 || monster->owner==clientid)) continue;
        }
        else
        {
            if(!monster->IsSummon( )) continue;
        }
        if(GServer->IsMonInCircle( Position->current,monster->Position->current,(float)skill->aoeradius+1))
        {
            Log(MSG_INFO,"AOE Debuff (1) monster %i",monster->montype);
            UseDebuffSkill( (CCharacter*) monster, skill );
        }

    }

    if(map->allowpvp!=0 || (IsMonster( ) && !IsSummon( )))
    {
        for(UINT i=0;i<map->PlayerList.size();i++)
        {
            CPlayer* player = map->PlayerList.at(i);
            if(player->clientid==clientid) continue;
            if(GServer->IsMonInCircle( Position->current,player->Position->current,(float)skill->aoeradius+1))
            {
                Log(MSG_INFO,"AOE Debuff (2) player %s",player->CharInfo->charname);
                UseDebuffSkill( (CCharacter*) player, skill );
            }

        }
    }

    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0) Stats->MP=0;
    ClearBattle( Battle );
    Battle->lastAtkTime = clock( );
    return true;
}

// use skill attack
void CCharacter::UseAtkSkill( CCharacter* Enemy, CSkills* skill, bool deBuff )
{
    reduceItemsLifeSpan( false );
    Enemy->reduceItemsLifeSpan(true);
    //Skill power calculations
    long int skillpower = skill->atkpower + (long int)floor(GetInt( )/2);
    long int level_diff = Stats->Level - Enemy->Stats->Level;
    skillpower -= Enemy->Stats->Magic_Defense;
    if(Enemy->IsMonster()){
        if(level_diff >= 1){
            skillpower += Stats->Attack_Power * (level_diff / 5) + (level_diff*2);
        }else{
            skillpower += Stats->Attack_Power - (level_diff / 2);
        }
    }
    //Tell enemy he's attacked & add damage & send the dmg packet
    bool bflag = false;
    Enemy->OnBeAttacked( this );
    if(skillpower<=0) skillpower = 0;
    if(IsPlayer())
    {
        //LMA: ED, Devilking / Arnold
        skillpower+=Stats->ExtraDamage_add;
        skillpower+=((skillpower*(Stats->ExtraDamage))/100);
    }
    if(!Enemy->IsSummon( ) && Enemy->IsMonster( ))
    {
        Enemy->AddDamage( this, skillpower );
    }
    Enemy->Stats->HP -= skillpower;

    // actually the target was hit, if it was sleeping, set duration of
    // sleep to 0. map process will remove sleep then at next player-update
    if (Enemy->Status->Sleep != 0xff) {
        Enemy->MagicStatus[Enemy->Status->Sleep].Duration = 0;
    }

    BEGINPACKET( pak, 0x7b6 );
    ADDWORD    ( pak, Enemy->clientid );
    ADDWORD    ( pak, clientid );
    ADDDWORD   ( pak, 0x000007f8 );
    ADDBYTE    ( pak, 0x00 );
    ADDDWORD   ( pak, skillpower );

    //If Enemy is killed
    if(Enemy->IsDead())
    {
        //LMA: Union Wars
        if (IsPlayer()&&Enemy->IsPlayer()&&(Position->Map==8||Position->Map==9))
        {
            Log(MSG_INFO,"UWKILL begins for atkskill");
            UWKill(Enemy);
            ClearBattle( Battle );
        }
        //

        CDrop* thisdrop = NULL;
        ADDDWORD   ( pak, 16 );
        if(!Enemy->IsSummon( ) && !Enemy->IsPlayer( ))
        {
            thisdrop = Enemy->GetDrop( );
            if(thisdrop!=NULL)
            {
                ADDFLOAT   ( pak, thisdrop->pos.x*100 );
                ADDFLOAT   ( pak, thisdrop->pos.y*100 );
                if(thisdrop->type==1)
                {
                    ADDDWORD( pak, 0xccccccdf );
                    ADDDWORD( pak, thisdrop->amount );
                    ADDDWORD( pak, 0xcccccccc );
                    ADDWORD ( pak, 0xcccc );
                }
                else
                {
                    ADDDWORD   ( pak, GServer->BuildItemHead( thisdrop->item ) );
                    ADDDWORD   ( pak, GServer->BuildItemData( thisdrop->item ) );
                    ADDDWORD( pak, 0x00000000 );
                    ADDWORD ( pak, 0x0000 );
                }
                ADDWORD    ( pak, thisdrop->clientid );
                ADDWORD    ( pak, thisdrop->owner );
                CMap* map = GServer->MapList.Index[thisdrop->posMap];
                map->AddDrop( thisdrop );
            }
        }
        GServer->SendToVisible( &pak, Enemy, thisdrop );
        OnEnemyDie( Enemy );
    }

    //If enemy is still alive
    else
    {
        ADDDWORD   ( pak, 4 );
        GServer->SendToVisible( &pak, Enemy );

        if (deBuff) return;

        //GOTO debuffing section
        bflag = GServer->AddDeBuffs( skill, Enemy, GetInt( ) );

        //Send (de)buff information to the whole world
        if(skill->nbuffs>0 && bflag)
        {
            BEGINPACKET( pak, 0x7b5 );
            ADDWORD    ( pak, Battle->skilltarget );
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, Battle->skillid );
            ADDWORD    ( pak, GetInt( ) );
            ADDBYTE    ( pak, skill->nbuffs );
            GServer->SendToVisible( &pak, Enemy );
        }
    }
    if (deBuff) return;
    //Send skill animation to the world
    RESETPACKET( pak, 0x7b9);
    ADDWORD    ( pak, clientid);
    ADDWORD    ( pak, Battle->skillid);
    ADDWORD    ( pak, 1);
    GServer->SendToVisible( &pak, this );
}

// use buff skill
void CCharacter::UseBuffSkill( CCharacter* Target, CSkills* skill )
{
    bool bflag = false;
    bflag = GServer->AddBuffs( skill, Target, GetInt( ) );
    if(skill->nbuffs>0 && bflag == true)
    {
        BEGINPACKET( pak, 0x7b5 );
        ADDWORD    ( pak, Target->clientid );
        ADDWORD    ( pak, clientid );
        ADDWORD    ( pak, Battle->skillid );
        ADDWORD    ( pak, GetInt( ) );
        ADDBYTE    ( pak, skill->nbuffs );
        GServer->SendToVisible( &pak, Target );
    }
    BEGINPACKET( pak, 0x7b9);
    ADDWORD    ( pak, clientid);
    ADDWORD    ( pak, Battle->skillid);
    ADDWORD    ( pak, 1);
	GServer->SendToVisible( &pak, (CCharacter*)this );
}

// use Debuff skill
void CCharacter::UseDebuffSkill( CCharacter* Enemy, CSkills* skill )
{
    bool bflag = false;
    bflag = GServer->AddBuffs( skill, Enemy, GetInt( ) );
    if(skill->nbuffs>0 && bflag == true)
    {
        BEGINPACKET( pak, 0x7b5 );
        ADDWORD    ( pak, Enemy->clientid );
        ADDWORD    ( pak, clientid );
        ADDWORD    ( pak, Battle->skillid );
        ADDWORD    ( pak, GetInt( ) );
        ADDBYTE    ( pak, skill->nbuffs );
        GServer->SendToVisible( &pak, Enemy );
    }
    BEGINPACKET( pak, 0x7b9);
    ADDWORD    ( pak, clientid);
    ADDWORD    ( pak, Battle->skillid);
    ADDWORD    ( pak, 1);
    GServer->SendToVisible( &pak, (CCharacter*)this );
}

//LMA: Union war kill and Slaughter kill
void CCharacter::UWKill(CCharacter* Enemy)
{
    CMap* map = GServer->MapList.Index[Position->Map];
    if (!map->is_union_fired&&!map->is_uw_fired)
    {
       Log(MSG_INFO,"[UWKILL] Not in the good map %i or not union fired %i or not slaughter fired %i",Position->Map,map->is_union_fired,map->is_uw_fired);
       return;
    }

    Log(MSG_INFO,"[UWKILL] client ID killer %i, killed %i",clientid,Enemy->clientid);

    //CPlayer* plkiller=GServer->GetClientByID(clientid,Position->Map);
    //CPlayer* plkilled=GServer->GetClientByID(Enemy->clientid,Enemy->Position->Map);
    CPlayer* plkiller=(CPlayer*) this;
    CPlayer* plkilled=(CPlayer*) Enemy;

    if (plkiller==NULL||plkilled==NULL)
    {
       Log(MSG_INFO,"[UWKILL] we've not found either killer %i or killed %i",clientid,Enemy->clientid);
       return;
    }
    else
    {
        Log(MSG_INFO,"[UWKILL] it seems player %s (%i) killed player %s (%i)",plkiller->CharInfo->charname,clientid,plkilled->CharInfo->charname,Enemy->clientid);
    }

    //UW case
    if (map->is_uw_fired)
    {
        bool is_ally=false;
        switch (plkiller->CharInfo->unionid)
        {
           case 1:
           case 2:
           case 3:
                if(plkilled->CharInfo->unionid==1||plkilled->CharInfo->unionid==2||plkilled->CharInfo->unionid==3)
                  is_ally=true;
                break;

           case 4:
           case 5:
           case 6:
           case 7:
                if(plkilled->CharInfo->unionid==4||plkilled->CharInfo->unionid==5||plkilled->CharInfo->unionid==6||plkilled->CharInfo->unionid==7)
                  is_ally=true;
                break;

           default:
               break;
        }

        if (is_ally)
        {
           Log(MSG_INFO,"Too bad, players in same union or allies, %i, %i",plkiller->CharInfo->unionid,plkilled->CharInfo->unionid);
           return;
        }

        //We give money to the killer ;)
        UINT temp_fame=0;
        temp_fame=GServer->GetColorExp(plkiller->Stats->Level,plkilled->Stats->Level,100000);
        //Ok, let's send PM now :)
        char msg[200];
        sprintf(msg, "You've killed %s !",plkilled->CharInfo->charname);
        GServer->SendPM(plkiller,msg);
        sprintf(msg, "You've been killed by %s !",plkiller->CharInfo->charname);
        GServer->SendPM(plkilled, msg);
        plkiller->CharInfo->Zulies += temp_fame;
        BEGINPACKET(pak, 0x7a7);
        ADDWORD(pak, plkiller->clientid);
        ADDWORD(pak, 0);
        ADDBYTE(pak, 0);
        ADDDWORD(pak, 0xccccccdf);
        ADDDWORD(pak, temp_fame);
        ADDDWORD( pak, 0xcccccccc );
        ADDWORD ( pak, 0xcccc );
        plkiller->client->SendPacket(&pak);
        Log(MSG_INFO,"We gave %i Z to %s",temp_fame,plkiller->CharInfo->charname);


       return;
    }

    //Union Slaughter.
    //only counts if he killed someone from another side than his ;)
    if (plkiller->CharInfo->unionid!=plkilled->CharInfo->unionid)
    {
        Log(MSG_INFO,"[UWKILL] too bad,they were in same union");
        return;
    }

    UINT temp_fame=0;
    /*
    plkiller->CharInfo->union01++;  //Nb kills (total)
    plkiller->CharInfo->union02++;  //Nb kills (this session)
    plkilled->CharInfo->union03++;  //Nb beeing killed (total)
    plkilled->CharInfo->union04++;  //Nb beeing killed (this session)
    */

    //Log(MSG_INFO,"Plkiller stats: %i,%i,%i",plkiller->CharInfo->union01,plkiller->CharInfo->union02,plkiller->CharInfo->union05);

    //Fame if level difference is not far (not really cool to kill a noob).
    temp_fame=GServer->GetColorExp(plkiller->Stats->Level,plkilled->Stats->Level,100);

    //This one can't be updated :(
    //plkiller->CharInfo->unionfame=temp_fame; //fame...
    //plkiller->CharInfo->union05+=temp_fame;  //Nb kills (money?)

       int new_amount=0;
        int new_offset=80+plkiller->CharInfo->unionid;
        switch(new_offset)
        {
            case 81:
            {
                plkiller->CharInfo->union01+=20;
                new_amount=plkiller->CharInfo->union01;
            }
            break;
            case 82:
            {
                plkiller->CharInfo->union02+=20;
                new_amount=plkiller->CharInfo->union02;
            }
            break;
            case 83:
            {
                plkiller->CharInfo->union03+=20;
                new_amount=plkiller->CharInfo->union03;
            }
            break;
            case 84:
            {
                plkiller->CharInfo->union04+=20;
                new_amount=plkiller->CharInfo->union04;
            }
            break;
            case 85:
            {
                plkiller->CharInfo->union05+=20;
                new_amount=plkiller->CharInfo->union05;
            }
            break;
        }

        BEGINPACKET( pak, 0x721 );
        ADDWORD( pak, new_offset );
        ADDWORD( pak, new_amount );
        ADDWORD( pak, 0x0000 );
        plkiller->client->SendPacket( &pak );
        RESETPACKET( pak, 0x730 );
        ADDWORD    ( pak, 0x0005 );
        ADDDWORD   ( pak, 0x40b3a24d );
        plkiller->client->SendPacket( &pak );

    //let's update stats.
    /*
    int unionvalues[5];
    unionvalues[0]=plkiller->CharInfo->union01;
    unionvalues[1]=plkiller->CharInfo->union02;
    unionvalues[2]=plkiller->CharInfo->union03;
    unionvalues[3]=plkiller->CharInfo->union04;
    unionvalues[4]=plkiller->CharInfo->union05;

    for (int k=0;k<5;k++)
    {
         int key=81+k;
         //let's update values "live" ;)
        BEGINPACKET( pak, 0x721 );
        ADDWORD( pak, key );
        ADDWORD( pak, unionvalues[k] );
        ADDWORD( pak, 0x0000 );
        plkiller->client->SendPacket( &pak );
        RESETPACKET( pak, 0x730 );
        ADDWORD    ( pak, 0x0005 );
        ADDDWORD   ( pak, 0x40b3a24d );
        plkiller->client->SendPacket( &pak );
    }
    */
    /*
    unionvalues[0]=plkilled->CharInfo->union01;
    unionvalues[1]=plkilled->CharInfo->union02;
    unionvalues[2]=plkilled->CharInfo->union03;
    unionvalues[3]=plkilled->CharInfo->union04;
    unionvalues[4]=plkilled->CharInfo->union05;

    for (int k=0;k<5;k++)
    {
         int key=81+k;
         //let's update values "live" ;)
        BEGINPACKET( pak, 0x721 );
        ADDWORD( pak, key );
        ADDWORD( pak, unionvalues[k] );
        ADDWORD( pak, 0x0000 );
        plkilled->client->SendPacket( &pak );
        RESETPACKET( pak, 0x730 );
        ADDWORD    ( pak, 0x0005 );
        ADDDWORD   ( pak, 0x40b3a24d );
        plkilled->client->SendPacket( &pak );
    }
    */

    //Ok, let's send PM now :)
    char msg[200];
    sprintf(msg, "You've killed %s !",plkilled->CharInfo->charname);
    GServer->SendPM(plkiller,msg);
    sprintf(msg, "You've been killed by %s !",plkiller->CharInfo->charname);
    GServer->SendPM(plkilled, msg);

    //let's update stats for the map session :)
    map->nb_kills[plkiller->CharInfo->unionid-1]++;
    map->nb_killed[plkilled->CharInfo->unionid-1]++;

  return;
}

