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
#ifndef _ROSE_CHARACTER_
#define _ROSE_CHARACTER_
#include "chartype.h"

class CCharacter
{
    public:
        CCharacter( );
        ~CCharacter( );

        unsigned int clientid;
        unsigned int char_montype;  //LMA: montype ID for CCharacter
        BYTE CharType; // 0 = undefined | 1 = player | 2 = monster | 3 = summon

        //LMA: maps grids
        int last_map;
        int last_coords;
        STATS *Stats;
        POSITION *Position;
        BATTLE* Battle;
        STATUS* Status;
        MAGICSTATUS MagicStatus[30];
        
       // Battle Functions
        void DoAttack( );
        void NormalAttack( CCharacter* Enemy );
        bool SkillAttack( CCharacter* Enemy, CSkills* skill );
        bool BuffSkill( CCharacter* Target, CSkills* skill );
        bool DebuffSkill ( CCharacter* Enemy, CSkills* skill );//netwolf
        bool SummonBuffSkill( CCharacter* Target, CSkills* skill );  //LMA: Special for supportive summons :)
        bool AoeSkill( CSkills* skill, CCharacter* Enemy=NULL );
        bool AoeBuff( CSkills* skill );
        bool AoeDebuff ( CSkills* skill, CCharacter* Enemy=NULL ); //netwolf
        void UseDebuffSkill ( CCharacter* Enemy, CSkills* skill );//netwolf
        void UseBuffSkill( CCharacter* Target, CSkills* skill );
        void UseAtkSkill( CCharacter* Enemy, CSkills* skill, bool deBuff= false );

        //functions
        bool IsMonster( );
        bool IsPlayer( );
        bool IsDead( );
        bool IsSummon( );
        bool IsOnBattle( );
        void StartAction( CCharacter* Target, BYTE action, UINT skillid=0, bool restart=false, CCharacter* receiver=NULL);
        bool IsTargetReached( CCharacter* , CSkills* skill=NULL );
        bool CanAttack( );
        bool IsMoving( ); 
        bool stopMoving( );       
        CCharacter* GetCharTarget( );
        CCharacter* GetCharBuffTarget( );           //LMA: Used for some summons.
        bool IsAttacking( );
                        
        // virtual functions
            // Events
            virtual bool OnBeAttacked( CCharacter* );
            virtual bool OnDie( );
            virtual bool OnEnemyDie( CCharacter* );
            virtual bool OnEnemyOnSight( void* );
            virtual bool OnSpawn( bool );
            virtual bool OnAlmostDie( );
            virtual bool OnFar( );
            
            // Functions
            virtual CDrop* GetDrop( );
            virtual void AddDamage( CCharacter* enemy, long int hitpower);
            virtual void UpdatePosition( bool monster_stay_still );       //LMA: changed for some monsters.
            virtual bool UpdateValues( );
            virtual void ReduceABC( );
            virtual int GetEVBuff( );
            void RefreshBuff( );
            virtual CParty* GetParty( );
            virtual void reduceItemsLifeSpan( bool);
            
            // stats
            virtual unsigned int GetAttackPower( );
            virtual unsigned int GetDefense( );
            virtual unsigned int GetDodge( );
            virtual unsigned int GetAccury( );
            virtual unsigned int GetMagicDefense( );
            virtual unsigned int GetCritical( );
            virtual unsigned int GetAttackSpeed( );
            virtual unsigned int GetMoveSpeed( );   
            virtual unsigned int GetMaxHP( );       
            virtual unsigned int GetMaxMP( ); 
            virtual float GetAttackDistance( );        
            virtual unsigned int GetInt( );
            virtual unsigned getWeaponType( );
            virtual bool AddClanPoints(unsigned int count);
            virtual CClientSocket* getClient();
};

#endif
