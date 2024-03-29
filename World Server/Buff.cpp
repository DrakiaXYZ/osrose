/*
    Rose Online Server Emulator
    Copyright (C) 2006,2007,2008,2009 OSRose Team http://www.dev-osrose.com

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

    developed with Main erose/hrose source server + some change from the original eich source
*/
#include "worldserver.h"

// Add Player buffs
bool CWorldServer::AddBuffs( CSkills* thisskill, CCharacter* character, int Evalue )
{
    //Log(MSG_INFO, "called addbuffs." );
    bool bflag = false;
    for(unsigned int i=0;i<3;i++)
    {
        if(thisskill->status[i] != 0) // sets status flags in magicstatus array
        {
            bflag = CheckABuffs( thisskill, character, Evalue, i );
        }
        else // some skills are instant effects without status changes e.g. healing.
        {
            if(thisskill->buff[i] != 0)
            {
                bflag = InstantBuff( thisskill, character, Evalue, i );
            }
        }
    }
    return bflag;
}

// handle instant effect skills without status changes
bool CWorldServer::InstantBuff( CSkills* thisskill, CCharacter* character, int Evalue, int i )
{
    //Log( MSG_INFO, "Instant skill cast: Status (should be zero):%i buff: %i", thisskill->status[i], thisskill->buff[i] );
    switch( thisskill->buff[i])
    {
        case 16: // HP
        {
            if(thisskill->duration <= 0 )//is heal
            {
                if(character->Stats->HP <= 0) //character is dead
                    return true;
                //Log(MSG_INFO,"Character %i HP is initially %I64i", character->clientid, character->Stats->HP);
                character->Stats->HP += (long int)thisskill->value1[i]; //apparently there is no buff here. // + Evalue - 8;
                //Log(MSG_INFO,"Character %i healed by %i points",character->clientid, thisskill->value1[i]);
                if(character->Stats->HP > character->Stats->MaxHP )
                    character->Stats->HP = character->Stats->MaxHP;
                //Log(MSG_INFO,"Character %i HP is now %I64i", character->clientid, character->Stats->HP);
                return true;
            }
        }
        break;
        case 17: // MP
        {
            if(thisskill->duration <= 0 )// recover MP
            {
                //Log(MSG_INFO,"Character %i MP was %I64i", character->clientid, character->Stats->MP);
                character->Stats->MP += (long int)thisskill->value1[i];
                if(character->Stats->MP > character->Stats->MaxMP)
                    character->Stats->MP = character->Stats->MaxMP;
                //Log(MSG_INFO,"Character %i MP is now %I64i", character->clientid, character->Stats->MP);
                return true;
            }
        }
        break;
        case 76: // Stamina
        {
            if(character->IsPlayer()) //monsters do not have stamina it would seem
            {
                if(thisskill->duration <= 0 )// recover Stamina
                {
                    CPlayer* thisclient = GServer->GetClientByID(character->clientid);
                    if(thisclient == NULL)return false;
                    thisclient->CharInfo->stamina += (long int)thisskill->value1[i];
                    if(thisclient->CharInfo->stamina > 5000)
                        thisclient->CharInfo->stamina = 5000;
                    //Log(MSG_INFO,"Character %i Stamina is now %i", character->clientid, thisclient->CharInfo->stamina);
                    return true;
                }
            }
            else
                return false;
        }
        break;
    }
    return false;
}

// Add DeBuffs
bool CWorldServer::CheckABuffs( CSkills* thisskill, CCharacter* character, int Evalue ,int i)
{
    //Log( MSG_INFO, "checkabuffs status: %i buff: %i",( thisskill->status[i], thisskill->buff[i] ));
    bool bflag = false;
    if(thisskill->status[i] != 0)
    {
        switch( thisskill->status[i])
        {
            case 7: case 8: case 9: case 10: case 11: //poisoned
            {
                //Log( MSG_INFO, "checkabuffs: Poisoned Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i, 0xff, character->Status->Poisoned, character->Status->Poisoned,true, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j>14)
                    {
                        character->Status->Poisoned = j;
                        character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Poisoned Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case 30: // muted
            {
                //Log( MSG_INFO, "checkabuffs: Mute Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i, 0xff, character->Status->Muted, character->Status->Muted, true, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j>14)
                    {
                        character->Status->Muted = j;
                        character->Status->CanCastSkill = false;
                        character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Muted Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case 31: // sleep
            {
                //Log( MSG_INFO, "checkabuffs: Sleep Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i, 0xff, character->Status->Sleep, character->Status->Sleep, true, true );
                Log( MSG_INFO, "Sleep Status attempted. position = %i", BuffValue.Position);
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j>14)
                    {
                        character->Status->Sleep = j;
                        character->Status->CanAttack = false;
                        character->Status->CanMove = false;
                        character->Status->CanCastSkill = false;
                        character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Sleep Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case 32: // faint
            {
                //Log( MSG_INFO, "checkabuffs: Fainted Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i, 0xff, character->Status->Faint, character->Status->Faint, true, true );
                //Log( MSG_INFO, "Stun Status attempted. position = %i", BuffValue.Position);
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j>14)
                    {
                        character->Status->Faint = j;
                        character->Status->CanAttack = false;
                        character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Fainted Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case 39: // Dispell. removes all buff and debuff effects
            {
                //Log( MSG_INFO, "checkabuffs: Dispell Status detected %i", thisskill->status[i] );
                // some dispell skills have duration of 2 seconds. Others have zero.
                // for now we will treat them all as instants so we don't need a buff slot
                float randv = GServer->RandNumber(0, 100);
                if(randv <= thisskill->successrate)
                {
                    for(int j=0;j<30;j++)
                    {
                        character->MagicStatus[j].Buff = 0;
                        character->MagicStatus[j].BuffTime = 0;
                        character->MagicStatus[j].Duration = 0;
                        character->MagicStatus[j].Value = 0;
                        character->MagicStatus[j].Status = 0;
                    }
                    //Log( MSG_INFO, "Dispell Status applied successfully");
                    // the rest will be taken care of in RefreshBuffs()
                }
                bflag = false;
            }
            break;
            case 36: //A_Extra_Damage:
            case 54: //A_GMExtra_Damage:    // this isn't going to work at all the way it is written. the buff is in skill power, not buffs
            case 83: //Valkyrie Charm:
            {
                /*
                 CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->ExtraDamage_up,
                                                character->Status->ExtraDamage_down,
                                                character->Stats->ExtraDamage, true );
                */
                //LMA: fix by sickb0y
                 CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->ExtraDamage_up,
                                                character->Status->ExtraDamage_down,true);

                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //LMA: fix by sickb0y
                    //character->Stats->ExtraDamage = thisskill->atkpower;

                    if(j<15)
                        character->Status->ExtraDamage_up = j;
                    else
                        character->Status->ExtraDamage_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;  // wrongO . Additional damage uses skill power not buff value. Fix later
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 35: // shield damage
            {
                 CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->ShieldDamage_up,
                                                character->Status->ShieldDamage_down,true);
//                                                character->Stats->ShieldDamage, true );
                 if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
//                    character->Stats->ShieldDamage = thisskill->atkpower;
                    if(j<15)
                        character->Status->ShieldDamage_up = j;
                    else
                        character->Status->ShieldDamage_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;  // wrongO . shield damage uses skill power not buff value. Fix later
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 18: // attack power up
            case 19: // attack power down
            case 48: // attack power up
            {
                //Log( MSG_INFO, "checkabuffs: Attack buff detected %i", thisskill->buff[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Attack_up,
                                                character->Status->Attack_down,
                                                character->Stats->Attack_Power, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->Attack_Power = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Attack_up = j;
                    else
                        character->Status->Attack_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 20: // def up
            case 21: // def down
            case 49: // def up
            {
                //Log( MSG_INFO, "checkabuffs: Defense buff detected %i", thisskill->buff[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Defense_up,
                                                character->Status->Defense_down,
                                                character->Stats->Defense, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->Defense = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Defense_up = j;
                    else
                        character->Status->Defense_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 24: //accuracy up
            case 25: //accuracy down
            case 51: //attack accuracy up.
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Accury_up,
                                                character->Status->Accury_down,
                                                character->Stats->Accury, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->Accury = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Accury_up = j;
                    else
                        character->Status->Accury_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 22: // macic resistance up
            case 23: // magic resistance down
            case 50: // magic resistance up
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Magic_Defense_up,
                                                character->Status->Magic_Defense_down,
                                                character->Stats->Magic_Defense, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->Magic_Defense = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Magic_Defense_up = j;
                    else
                        character->Status->Magic_Defense_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 28: //dodge up
            case 29: //dodge down
            case 53: //dodge rate up
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Dodge_up,
                                                character->Status->Dodge_down,
                                                character->Stats->Dodge, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->Dodge = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Dodge_up = j;
                    else
                        character->Status->Dodge_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 14: //dash
            case 15: //slow
            case 46: //movement speed increased
            {
                Log( MSG_INFO, "checkabuffs: move speed buff detected %i", thisskill->buff[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Dash_up,
                                                character->Status->Dash_down,
                                                character->Stats->Move_Speed, true );

                //LMA: >=0 because some skills are really efficient...
                if(BuffValue.NewValue>=0)
                {
                    UINT j = BuffValue.Position;

                    //LMA: for debug
                    UINT prev_value=character->Stats->Move_Speed;

                    character->Stats->Move_Speed = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Dash_up = j;
                    else
                        character->Status->Dash_down = j;
                    Log( MSG_INFO, "Move speed buff position %i. move speed(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 16: // haste attack
            case 17: // slow attack
            case 47: // attack speed up
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Haste_up,
                                                character->Status->Haste_down,
                                                (UINT)character->Stats->Attack_Speed, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->Attack_Speed = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Haste_up = j;
                    else
                        character->Status->Haste_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 26: // crit up
            case 27: // crit down
            case 52: // crit up
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->Critical_up,
                                                character->Status->Critical_down,
                                                character->Stats->Critical, true );
                if(BuffValue.NewValue != 0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->Critical = BuffValue.NewValue;
                    if(j<15)
                        character->Status->Critical_up = j;
                    else
                        character->Status->Critical_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 12: // max HP up
            case 44: // max HP up
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->HP_up,
                                                character->Status->HP_down,
                                                character->Stats->MaxHP, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->MaxHP = BuffValue.NewValue;
                    if(j<15)
                        character->Status->HP_up = j;
                    else
                        character->Status->HP_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 13: // max MP up
            case 45: // max MP up
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i,
                                                character->Status->MP_up,
                                                character->Status->MP_down,
                                                character->Stats->MaxMP, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->MaxMP = BuffValue.NewValue;
                    if(j<15)
                        character->Status->MP_up = j;
                    else
                        character->Status->MP_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case 58: case 61: case 71: case 77:  case 78: case 79: case 80: //Flame
            {
                Log( MSG_INFO, "checkabuffs: Flamed Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i, 0xff, character->Status->Flamed, character->Status->Flamed,true, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j>14)
                    {
                        character->Status->Flamed = j;
                        character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        Log( MSG_INFO, "Flamed Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case 33: //Stealth
            {
                //Log( MSG_INFO, "checkabuffs: Stealth Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i, 0xff,
                                                    character->Status->Stealth, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j>14)
                    {
                        character->Status->Stealth = j;
                        character->MagicStatus[j].Buff = thisskill->buff[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = BuffValue.Value;
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Stealth Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case 34: //Cloak
            {
                //Log( MSG_INFO, "checkabuffs: Cloak Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, Evalue, i, 0xff,
                                                    character->Status->Cloaking, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j>14)
                    {
                        character->Status->Cloaking = j;
                        character->MagicStatus[j].Buff = thisskill->buff[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = BuffValue.Value;
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Cloak Status applied");
                        bflag = true;
                    }
                }
            }
            break;
        }
    }
    return bflag;
}

// Get the new buffs values (character)
CBValue CWorldServer::GetBuffValue( CSkills* thisskill, CCharacter* character, UINT Evalue, UINT i, UINT up, UINT down, UINT CurrentValue, bool Buff, bool Status )
{
    CBValue NewValue;
    NewValue.Position = 0xff;
    NewValue.NewValue = 0;
    NewValue.Value = 0;
    UINT Value = 0;
    UINT NormalValue = 0;
    UINT UpValue = 0;
    UINT DownValue = 0;
    bool BuffFlag = false;
    // not currently detecting debuffs properly so let's bring in some new code :)
    //PY buff mod based on thiskill->status[i]

    //LMA: removing 13 (max mp) from debuff to buff
    switch(thisskill->status[i])
    {
        case 12: case 13: case 14: case 16: case 18: case 20: case 22: case 24: case 26: case 28: case 35: case 36: case 53:
        case 54: case 83:
             Buff = true;
        break;
        case 7: case 8: case 9: case 10: case 15: case 17: case 19: case 21: case 23: case 25: case 27: case 29:
        case 30: case 31: case 32: case 59: case 60:
        case 58: case 61: case 71: case 77:  case 78: case 79: case 80: case 33: case 34:
             Buff = false;
        break;
        default:
             Buff = true;
        break;
    }
    //Log(MSG_INFO, "Current Buff boolean status %i Skill status = %i up: %i down: %i", Buff,thisskill->status[i],up,down);
    //PY end
    if(Buff) //skill is a buff
    {
        //find whether character already has buffs for this stat
        for(UINT z=0;z<15;z++) // 0 to 14 are upward
        {
            if(character->MagicStatus[z].Status == thisskill->status[i])
            {
                NewValue.Position = z;
                //Log(MSG_INFO, "Existing Buff position = %i",z);
                NormalValue = CurrentValue - character->MagicStatus[z].Value;
                UpValue = character->MagicStatus[z].Value;
                BuffFlag = true;
                break;
            }
        }
        if(BuffFlag == false) // no active buffs so find a new slot
        {
            for(UINT z=0;z<15;z++) // 0 to 14 are upward
            {
                if(character->MagicStatus[z].Status == 0)
                {
                    NewValue.Position = z;
                    //Log(MSG_INFO, "New Buff position = %i",z);
                    NormalValue = CurrentValue;
                    BuffFlag = true;
                    break;
                }
            }
        }
    }
    else
    {
        //find whether character already has debuffs for this stat
        for(UINT z=15;z<32;z++) // 15 to 32 are downward
        {
            if(character->MagicStatus[z].Status == thisskill->status[i])
            {
                NewValue.Position = z;
                //Log(MSG_INFO, "Existing De-Buff position = %i",z);
                NormalValue = CurrentValue + character->MagicStatus[z].Value;
                DownValue = character->MagicStatus[z].Value;
                BuffFlag = true;
                break;
            }
        }
        if(BuffFlag == false) // no active debuffs so find a new slot
        {
            for(UINT z=15;z<32;z++) // 15 to 32 are downward
            {
                if(character->MagicStatus[z].Status == 0)
                {
                    NewValue.Position = z;
                    //Log(MSG_INFO, "New De-Buff position = %i",z);
                    NormalValue = CurrentValue;
                    BuffFlag = true;
                    break;
                }
            }
        }
    }
    if(BuffFlag == false) // no available spaces found
        return NewValue;

    //else // don't currently have a buff
    if(NewValue.Position == 0xff)
    {
        //Log(MSG_INFO, "No buff currently active");
        if(Buff) //is this skill a buff?
        {
            for(UINT z=0;z<15;z++) // 0 to 14 are upward
            {
                if(character->MagicStatus[z].Status == 0)
                {
                    NewValue.Position = z; //z is the new index in the magicstatus array where the buff will be placed
                    //Log(MSG_INFO, "Buff position = %i",z);
                    break;
                }
            }
            if(NewValue.Position == 0xff) //no spaces found ??
                return NewValue;
            NormalValue = CurrentValue; // no buffs currently active so set normalvalue to currentvalue
        }
        else //debuff
        {
            for(UINT z=15;z<30;z++) // 15 to 29 are downward
            {
                if(character->MagicStatus[z].Status == 0)
                {
                    NewValue.Position = z; //z is the new index in the magicstatus array where the buff will be placed
                    Log(MSG_INFO, "DeBuff position = %i",z);
                    break;
                }
            }
            if(NewValue.Position == 0xff) //no spaces found ??
                return NewValue;
            NormalValue = CurrentValue; // no buffs currently active so set normalvalue to currentvalue
        }
    }

    //Log(MSG_INFO, "Newvalue.position = %i",NewValue.Position);
    if( thisskill->value2[i] > 0 )
    {
        Value = NormalValue * thisskill->value2[i] / 100;
        //Log(MSG_INFO, "Percentage buff = %i",Value);
    }
    if( thisskill->value1[i] > 0 )
    {
        Value += thisskill->value1[i];
        if(thisskill->buff[i] == A_DASH || thisskill->buff[i] == MOV_SPEED) Value += (Evalue - 15) / 10;
        else Value += (Evalue-15)/32;
        //Log(MSG_INFO, "Number buff = %i",Value);
    }
    if(Buff)
    {
        if( Value + CurrentValue - DownValue >= CurrentValue )
        {
            CurrentValue = NormalValue - DownValue + Value;
        }
        else
        {
            CurrentValue = 0;
        }
    }
    else
    {
        CurrentValue = NormalValue + UpValue - Value;
    }
    NewValue.NewValue = CurrentValue;
    NewValue.Value = Value;
    return NewValue;
}

// Build Buffs to Show
unsigned int CWorldServer::BuildBuffs( CCharacter* character )
{
    BYTE buff1 = 0;
    BYTE buff2 = 0;
    BYTE buff3 = 0;
    BYTE buff4 = 0;
    //Build Debuffs and Buffs
        //Up
    if(character->Status->Attack_up != 0xff)//A_ATTACK:
                buff2 += ATTACK_UP;
    if(character->Status->Defense_up != 0xff)//A_DEFENSE:
                buff2 += DEFENSE_UP;
    if(character->Status->Magic_Defense_up != 0xff)//A_MDEFENSE_UP
                buff2 += MDEFENSE_UP;
    if(character->Status->Accury_up != 0xff)//A_ACCUR:
                buff3 += HITRATE_UP;
    if(character->Status->Dash_up != 0xff)//A_DASH:
                buff1 += DASH_UP;
    if(character->Status->Haste_up != 0xff)//A_HASTE:
                buff2 += HASTE_UP;
    if(character->Status->HP_up != 0xff)//A_HP:
                buff1 += HP_UP;
    if(character->Status->MP_up != 0xff)//A_MP:
                buff1 += MP_UP;
    if(character->Status->Critical_up != 0xff)//A_CRITICAL:
                buff3 += CRITICAL_UP;
    if(character->Status->Dodge_up != 0xff)//A_DODGE:
                buff1 += DODGE_UP;
    if(character->Status->ExtraDamage_up != 0xff)//A_Extra_Damage:
                buff4 += DAMAGE_UP;
    if(character->Status->ShieldDamage_up != 0xff)//A_Shield_Damage:
                buff4 += SHIELD_DAMAGE;
        //Down
    if(character->Status->Attack_down != 0xff) // A_ATTACK:
                buff2 += ATTACK_DOWN;
    if(character->Status->Defense_down != 0xff)//A_DEFENSE:
                buff2 += DEFENSE_DOWN;
    if(character->Status->Magic_Defense_down != 0xff)
                buff2 += MDEFENSE_DOWN;
    if(character->Status->Accury_down != 0xff)//A_ACCUR:
                buff3 += HITRATE_DOWN;
    if(character->Status->Dash_down != 0xff)//A_DASH:
                buff1 += DASH_DOWN;
    if(character->Status->Haste_down != 0xff)//A_HASTE:
                buff2 += HASTE_DOWN;
    if(character->Status->HP_down != 0xff)//A_HP:
                buff1 += 0;
    if(character->Status->MP_down != 0xff)//A_MP:
                buff1 += 0;
    if(character->Status->Critical_down != 0xff)//A_CRITICAL:
                buff3 += CRITICAL_DOWN;
    if(character->IsSummon( ))
                buff4 += SUMMON;
    if(character->Status->Stuned != 0xff)//A_STUN
                buff4+= STUN;
    if(character->Status->Poisoned != 0xff)//A_POISON
                buff1+= POISONED;
    if(character->Status->Muted != 0xff)//A_MUTE
                buff3+= MUTED;
    if(character->Status->Flamed != 0xff)//A_FLAME
                buff1+= FLAMED;
    if(character->Status->Stealth != 0xff)//A_STEALTH
                buff4 += STEALTH;
    if(character->Status->Cloaking != 0xff)//A_CLOAKING
                buff4 += CLOAKING;

    return (buff1 * 0x01) + (buff2 * 0x100 ) + (buff3 * 0x10000) + (buff4 * 0x1000000);
}

// Build Buffs to Show
unsigned int CWorldServer::BuildUpBuffs( CCharacter* character )
{
    BYTE buff1 = 0;
    BYTE buff2 = 0;
    BYTE buff3 = 0;
    BYTE buff4 = 0;
    // Buffs
        //Up
    if(character->Status->Attack_up != 0xff)//A_ATTACK:
                buff2 += ATTACK_UP;
    if(character->Status->Defense_up != 0xff)//A_DEFENSE:
                buff2 += DEFENSE_UP;
    if(character->Status->Magic_Defense_up != 0xff)//A_MDEFENSE_UP
                buff2 += MDEFENSE_UP;
    if(character->Status->Accury_up != 0xff)//A_ACCUR:
                buff3 += HITRATE_UP;
    if(character->Status->Dash_up != 0xff)//A_DASH:
                buff1 += DASH_UP;
    if(character->Status->Haste_up != 0xff)//A_HASTE:
                buff2 += HASTE_UP;
    if(character->Status->HP_up != 0xff)//A_HP:
                buff1 += HP_UP;
    if(character->Status->MP_up != 0xff)//A_MP:
                buff1 += MP_UP;
    if(character->Status->Critical_up != 0xff)//A_CRITICAL:
                buff3 += CRITICAL_UP;
    if(character->Status->Dodge_up != 0xff)//A_DODGE:
                buff1 += DODGE_UP;
    if(character->Status->ExtraDamage_up != 0xff)//A_Extra_Damage:
                buff4 += DAMAGE_UP;
    if(character->Status->ShieldDamage_up != 0xff)//A_Shield_Damage:
                buff4 += SHIELD_DAMAGE;
    return (buff1 * 0x01) + (buff2 * 0x100 ) + (buff3 * 0x10000) + (buff4 * 0x1000000);
}
// Build Buffs to Show
unsigned int CWorldServer::BuildDeBuffs( CCharacter* character )
{
    BYTE buff1 = 0;
    BYTE buff2 = 0;
    BYTE buff3 = 0;
    BYTE buff4 = 0;
    //Build Debuffs
        //Down
    if(character->Status->Attack_down != 0xff) // A_ATTACK:
                buff2 += ATTACK_DOWN;
    if(character->Status->Defense_down != 0xff)//A_DEFENSE:
                buff2 += DEFENSE_DOWN;
    if(character->Status->Magic_Defense_down != 0xff)
                buff2 += MDEFENSE_DOWN;
    if(character->Status->Accury_down != 0xff)//A_ACCUR:
                buff3 += HITRATE_DOWN;
    if(character->Status->Dash_down != 0xff)//A_DASH:
                buff1 += DASH_DOWN;
    if(character->Status->Haste_down != 0xff)//A_HASTE:
                buff2 += HASTE_DOWN;
    if(character->Status->HP_down != 0xff)//A_HP:
                buff1 += 0;
    if(character->Status->MP_down != 0xff)//A_MP:
                buff1 += 0;
    if(character->Status->Critical_down != 0xff)//A_CRITICAL:
                buff3 += CRITICAL_DOWN;
    if(character->IsSummon( ))
                buff4 += SUMMON;
    if(character->Status->Stuned != 0xff)//A_STUN
                buff4+= STUN;
    if(character->Status->Poisoned != 0xff)//A_POISON
                buff1+= POISONED;
    if(character->Status->Muted != 0xff)//A_MUTE
                buff3+= MUTED;
    if(character->Status->Flamed != 0xff)//A_FLAME
                buff1+= FLAMED;
    if(character->Status->Stealth != 0xff)//A_STEALTH
                buff4 += STEALTH;
    if(character->Status->Cloaking != 0xff)//A_CLOAKING
                buff4 += CLOAKING;

    return (buff1 * 0x01) + (buff2 * 0x100 ) + (buff3 * 0x10000) + (buff4 * 0x1000000);
}
