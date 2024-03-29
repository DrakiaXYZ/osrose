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
#include "charserver.h"

// Do player identification
bool CCharServer::pakDoIdentify( CCharClient* thisclient, CPacket* P )
{
	if (thisclient->isLoggedIn) return false;
	MYSQL_RES *result;
	MYSQL_ROW row;
	thisclient->userid = GETDWORD((*P), 0x00);
	memcpy( thisclient->password, &P->Buffer[4], 32 );
	result = DB->QStore("SELECT username,lastsvr,accesslevel,platinum FROM accounts WHERE id=%i AND password='%s'", thisclient->userid, thisclient->password);
	if(result==NULL) return false;
	if (mysql_num_rows( result ) != 1)
    {
		Log( MSG_HACK, "Someone tried to connect to char server with an invalid account" );
		DB->QFree( );
		return false;
	}
    else
    {
		row = mysql_fetch_row(result);
		strncpy(thisclient->username, row[0],16);
		thisclient->channel = atoi(row[1]);
		thisclient->accesslevel = atoi(row[2]);
		thisclient->platinum = atoi(row[3]);
		DB->QFree( );
	}

	Log( MSG_INFO,"User '%s'(#%i) logged in", thisclient->username, thisclient->userid );

	BEGINPACKET( pak, 0x070c );
	ADDBYTE    ( pak, 0 );
	ADDDWORD   ( pak, 0x87654321);
	ADDDWORD   ( pak, 0x00000000 );
	thisclient->SendPacket( &pak );
	result = DB->QStore( "SELECT online FROM accounts WHERE username='%s'", thisclient->username );
    if(result==NULL) return false;
    row = mysql_fetch_row(result);
    bool online = atoi(row[0]);
    DB->QFree( );
    if(online)
        return false;
    if(!DB->QExecute( "UPDATE accounts SET online=1 WHERE username='%s'", thisclient->username ))
        return false;
	thisclient->isLoggedIn = true;
    return true;
}

// Get this clients character list
bool CCharServer::pakGetCharacters( CCharClient* thisclient, CPacket* P )
{
	if (!thisclient->isLoggedIn) return false;
    if(!DB->QExecute( "DELETE FROM characters WHERE deletetime>0 AND deletetime<=%i",GetServerTime( ) ))
        return false;
	MYSQL_RES *result;
	MYSQL_ROW row;
	CItem items[10];
	unsigned int charnum=0;
	CCharacter chars[5];
	            //        0       1      2    3      4      5     6      7
	result = DB->QStore("SELECT char_name,level,face,hairStyle,sex,classid,id,deletetime FROM characters WHERE account_name='%s'", thisclient->username);
	if(result==NULL) return false;
	while (row = mysql_fetch_row(result))
    {
        memset( &chars[charnum].char_name, '\0', 17 );
		strcpy( chars[charnum].char_name , row[0] );
		chars[charnum].level = atoi(row[1]);
		chars[charnum].face = atoi(row[2]);
		chars[charnum].hairStyle = atoi(row[3]);
		chars[charnum].sex = atoi(row[4]);
		chars[charnum].classid = atoi(row[5]);
		chars[charnum].id = atoi(row[6]);
        chars[charnum].DeleteTime = atoi(row[7]);
		if(chars[charnum].DeleteTime > 0)
		{
            chars[charnum].DeleteTime = chars[charnum].DeleteTime - GetServerTime( );
        }
		charnum++;
	}
	DB->QFree( );
	BEGINPACKET( pak, 0x0712 );
	ADDBYTE    ( pak, charnum );
	for (unsigned k=0;k<charnum;k++)
    {
		for(unsigned j=0; j<10; j++)
            ClearItem( items[j] );
                    //       0       1      2         3         4        5
		result = DB->QStore("SELECT itemnum,itemtype,refine,durability,lifespan,slotnum FROM items WHERE owner=%i AND slotnum<10", chars[k].id);
		if(result==NULL) return false;
		while(row = mysql_fetch_row(result))
        {
			unsigned itemnum = atoi(row[5]);
			items[itemnum].itemnum = atoi(row[0]);
			items[itemnum].itemtype = atoi(row[1]);
			items[itemnum].refine = atoi(row[2]);
			items[itemnum].durability = atoi(row[3]);
			items[itemnum].lifespan = atoi(row[4]);

            //LMA: little check, refine from 1 to 9 are not valid...
            if(items[itemnum].refine>0&&items[itemnum].refine<=9)
            {
                Log(MSG_WARNING,"Invalid refine %i for item (%i:%i) for %s",items[itemnum].refine,items[itemnum].itemtype,items[itemnum].itemnum,thisclient->username);
                items[itemnum].refine*=16;
            }

		}
		DB->QFree( );

		ADDSTRING ( pak, chars[k].char_name );
		ADDBYTE   ( pak, 0x00 );
		ADDBYTE   ( pak, chars[k].sex );			// SEX
		ADDWORD   ( pak, chars[k].level );		// LEVEL
		ADDWORD   ( pak, chars[k].classid );		// CLASSID
		ADDDWORD  ( pak, chars[k].DeleteTime );			// DELETE TIME
		ADDBYTE   ( pak, 0x00 );//thisclient->platinum?0x01:0x00 );					// IS PLATINUM?  00-NO;01-YES;02-YES BUT USER IS NOT
		ADDDWORD  ( pak, chars[k].face );		// FACE
		ADDDWORD  ( pak, chars[k].hairStyle );	// HAIR
		ADDWORD   ( pak, items[2].itemnum );		// CAP
		ADDWORD   ( pak, items[2].refine );		// CAP REFINE
		ADDWORD   ( pak, items[3].itemnum );		// BODY
		ADDWORD   ( pak, items[3].refine );		// BODY REFINE
		ADDWORD   ( pak, items[5].itemnum );		// GLOVES
		ADDWORD   ( pak, items[5].refine );		// GLOVES REFINE
		ADDWORD   ( pak, items[6].itemnum );		// BOOTS
		ADDWORD   ( pak, items[6].refine );		// BOOTS REFINE
		ADDWORD   ( pak, items[1].itemnum );		// FACE
		ADDWORD   ( pak, items[1].refine );		// FACE REFINE
		ADDWORD   ( pak, items[4].itemnum );		// BACK
		ADDWORD   ( pak, items[4].refine );		// BACK REFINE
		ADDWORD   ( pak, items[7].itemnum );		// WEAPON
		ADDWORD   ( pak, items[7].refine );		// WEAPON REFINE
		ADDWORD   ( pak, items[8].itemnum );		// SUBWEAPON
		ADDWORD   ( pak, items[8].refine );		// SUBWEAPON REFINE
	}
	thisclient->SendPacket( &pak );
	return true;
}

// Send away the world IP
bool CCharServer::pakRequestWorld( CCharClient* thisclient, CPacket* P )
{
	if (!thisclient->isLoggedIn) return false;
	MYSQL_ROW row;
	MYSQL_RES *result;
	memset( &thisclient->charname, '\0', 17 );
	memcpy( thisclient->charname, &P->Buffer[3], (P->Size-6-4)>16?16:(P->Size-6-4) );
	Log( MSG_INFO,"User %s(%i) selected char '%s'", thisclient->username, thisclient->userid, thisclient->charname);
	if(!DB->QExecute("UPDATE accounts SET lastchar='%s' WHERE id=%i", thisclient->charname, thisclient->userid))
	   return false;
	result = DB->QStore("SELECT host,port,lanip,lansubmask FROM channels WHERE id=%u and owner=%u and type=2", thisclient->channel, Config.ServerID);
	if(result==NULL) return false;
	if(mysql_num_rows( result )!=1 )
	{
        Log( MSG_WARNING, "Invalid Server: %i", thisclient->channel );
        DB->QFree( );
	    return false;
    }
	row = mysql_fetch_row( result );
	BEGINPACKET( pak, 0x711 );
	ADDWORD    ( pak, atoi(row[1]) );                // PORT
	ADDDWORD   ( pak, thisclient->userid );
	ADDDWORD   ( pak, 0x87654321 );

	if(strcmp(thisclient->ClientSubNet,row[3])==0)//from lan
	{
        ADDSTRING( pak, row[2] );
       	Log(MSG_INFO, "Sending LanIP" );
    }
    else if(strcmp( thisclient->ClientSubNet ,"127.0.0")==0)//same computer
    {
        ADDSTRING( pak, "127.0.0.1" );
       	Log(MSG_INFO, "Sending Localhost IP" );
    }
    else
    {
        ADDSTRING( pak, row[0] );
       	Log(MSG_INFO, "Sending InetIP");
    }
	ADDBYTE    ( pak, 0 );
	thisclient->SendPacket( &pak );
	DB->QFree( );
//CHAR INFORMATION        0       1    2    3      4
	result = DB->QStore("SELECT clanid,clan_rank,id,level,classid,rewardpoints FROM characters WHERE char_name='%s'", thisclient->charname);
	if(result==NULL) return false;
	if(mysql_num_rows(result)!=1)
	{
        Log( MSG_WARNING, "Number of user with charname '%s' is %i", thisclient->charname,mysql_num_rows(result));
        DB->QFree( );
        return false;
    }
	row = mysql_fetch_row( result );
	thisclient->clanid =  atoi( row[0] );
	thisclient->clan_rank = atoi( row[1] );
	thisclient->charid = atoi( row[2] );
	thisclient->level = atoi( row[3] );
	thisclient->job = atoi( row[4] );
    thisclient->reward_points=atoi( row[5] );  //LMA: reward points:
	DB->QFree( );
//MESSENGER INFORMATION
//              //          0        1
	result = DB->QStore("SELECT idfriend,namefriend FROM list_friend WHERE id=%i", thisclient->charid);
	if(result==NULL) return false;
	BYTE nfriends = mysql_num_rows(result) & 0xff;

	RESETPACKET( pak, 0x7e1 );// Friend list command
    ADDBYTE    ( pak, 0x06 );// Sending Friend List
    ADDBYTE    ( pak, nfriends );// # friends
	while(row = mysql_fetch_row( result ))
	{
        CFriendList * newfriend = new CFriendList;
        assert(newfriend);
        newfriend->id = atoi(row[0]); //friendid
        strcpy(newfriend->name, row[1]); //friend name
        thisclient->FriendList.push_back( newfriend );
        ADDWORD    (pak, newfriend->id);// friend id
        ADDWORD    (pak, 0x0000 );
        CCharClient* otherclient = (CCharClient*) GetClientByID( newfriend->id );
        if(otherclient!=NULL) //is online??
        {
            ADDBYTE    (pak, 0x07 );   //online
            ChangeMessengerStatus ( thisclient, otherclient, 0x07);
        }
        else
        {
            ADDBYTE    (pak, 0x08 );//offline
        }
        ADDSTRING  (pak, newfriend->name); //friend name
        ADDBYTE    (pak, 0x00 );
    }
    thisclient->SendPacket( &pak );
	DB->QFree( );
    thisclient->logout = false;

    //SEND CLAN INFORMATION
    SendClanInfo (thisclient);

    return true;
}

// Create a character
bool CCharServer::pakCreateChar( CCharClient* thisclient, CPacket* P )
{
	if (!thisclient->isLoggedIn) return false;

	// Get info from packet
	BYTE sex   = GETBYTE((*P), 0 ) % 2;
	BYTE hairstyle  = GETBYTE((*P), 2 );
	BYTE face  = GETBYTE((*P), 3 );
	string newname = (char*)&P->Buffer[7];
	MYSQL_RES *result;
	result = DB->QStore("SELECT id FROM characters WHERE account_name='%s'", thisclient->username);
	if(result==NULL) return false;
	if ( mysql_num_rows( result ) == 5 )
    {
        BEGINPACKET( pak, 0x713 );
        ADDWORD    ( pak, 4 );
		thisclient->SendPacket( &pak );
		DB->QFree( );
		return true;
	}
	DB->QFree( );
	result = DB->QStore("SELECT id FROM characters WHERE char_name='%s'", newname.c_str());
    if(result==NULL) return false;
	if ( mysql_num_rows( result ) > 0 )
    {
		BEGINPACKET( pak, 0x713);
		ADDWORD    ( pak, 2 );
		thisclient->SendPacket( &pak );
		DB->QFree( );
		return true;
	}
	DB->QFree( );

	if(!DB->QExecute("INSERT INTO characters (account_name, char_name, face, hairStyle, sex) VALUES('%s','%s',%i,%i,%i)", thisclient->username, newname.c_str(), face, hairstyle, sex))
	   return false;
	unsigned int mid = (unsigned)mysql_insert_id( DB->Mysql );
    MYSQL_ROW row;
	if(!DB->QExecute("INSERT INTO items VALUES(%i,29,3,0,40,100,3,1,0,0,0,0,0)", mid))
		return false;
	if(!DB->QExecute("INSERT INTO items VALUES(%i,29,5,0,40,100,6,1,0,0,0,0,0)", mid))
		return false;
	if(!DB->QExecute("INSERT INTO items VALUES(%i,1,8,0,40,100,7,1,0,0,0,0,0)", mid))
		return false;

    if(sex==0)
    {
        if(!DB->QExecute("INSERT INTO items VALUES(%i,222,2,0,40,100,12,1,0,0,0,0,0)", mid))
            return false;
     }
    else
    {
        if(!DB->QExecute("INSERT INTO items VALUES(%i,221,2,0,40,100,12,1,0,0,0,0,0)", mid))
            return false;
    }

	BEGINPACKET( pak, 0x713 );
	ADDWORD    ( pak,  0 );
	thisclient->SendPacket( &pak );

	return true;
}

// Connect WorldServer
bool CCharServer::pakWSReady ( CCharClient* thisclient, CPacket* P )
{
	if(thisclient->isLoggedIn) return false;
	if(GETDWORD((*P),0) != Config.CharPass )
    {
        Log( MSG_HACK, "WorldServer Tried to connect CharServer with wrong password ");
        return true;
    }
    thisclient->userid = GETDWORD((*P), 4); //our channelid
    thisclient->accesslevel = 0xffff; //this will identify thisclient as channel

    // add channel
    CChanels* newchannel = new (nothrow) CChanels;
    if(newchannel==NULL)
        return false;

    newchannel->id = GETDWORD((*P), 4);
    newchannel->ip = inet_ntoa( thisclient->clientinfo.sin_addr );
    newchannel->port = GETWORD((*P),8 );
    Log( MSG_INFO, "Channel #%i connected from ip %s", newchannel->id, newchannel->ip );

    // Connect to charserver
	newchannel->sock = socket( AF_INET, SOCK_STREAM, 0 );
	if (newchannel->sock == INVALID_SOCKET)
    {
		Log( MSG_WARNING, "Could not access worldserver IP: %s , Port: %i", newchannel->ip, newchannel->port );
		delete newchannel;
		return false;
	}
	struct sockaddr_in ain;
	ain.sin_family		= AF_INET;
   	ain.sin_addr.s_addr	= thisclient->clientinfo.sin_addr.s_addr;
	ain.sin_port		= htons( newchannel->port );
	memset(&(ain.sin_zero), '\0', 8);
	if ( connect( newchannel->sock , (SOCKADDR*) &ain, sizeof(ain) ) == SOCKET_ERROR)
    {
		Log( MSG_WARNING, "Could not access worldserver IP: %s , Port: %i", newchannel->ip , newchannel->port );
		delete newchannel;
		return false;
	}
    ChannelList.push_back( newchannel );

	thisclient->isLoggedIn = true;
	BEGINPACKET( pak, 0x500 );
    ADDDWORD   ( pak, Config.WorldPass );
	cryptPacket( (char*)&pak, NULL );
	send( newchannel->sock, (char*)&pak, pak.Size, 0 );
	return true;
}

// Login Connected
bool CCharServer::pakLoginConnected( CCharClient* thisclient, CPacket* P )
{
	if(thisclient->isLoggedIn) return false;
	if(GETDWORD((*P),0) != Config.CharPass )
    {
         Log( MSG_HACK, "LoginServer Tried to connect CharServer with wrong password ");
         return true;
    }
	thisclient->isLoggedIn = true;
    return true;
}

// Return to char select
bool CCharServer::pakWSCharSelect ( CCharClient* thisclient, CPacket* P )
{
	if(!thisclient->isLoggedIn) return false;
	Log( MSG_INFO, "World server requested char select" );

	DWORD userid = GETDWORD( (*P), 0 );
	CCharClient* otherclient = GetClientByUserID( userid );
	if(otherclient==NULL)
	{
        Log(MSG_WARNING, "Invalid userid: %i", userid );
	    return true;
    }
	BEGINPACKET( pak, 0x71c );
	ADDBYTE    ( pak, 0x00 );
	otherclient->SendPacket( &pak );
    Log( MSG_INFO, "Client returning to char select" );
    RESETPACKET( pak, 0x505 );
    ADDDWORD( pak, thisclient->userid );
    cryptPacket( (char*)&pak, NULL );
    CChanels* thischannel = GetChannelByID( thisclient->channel );
    if(thischannel!=NULL)
        send( thischannel->sock, (char*)&pak, pak.Size, 0 );
	return true;
}

// ???
bool CCharServer::pak7e5 ( CCharClient* thisclient, CPacket* P )
{
	if(!thisclient->isLoggedIn) return false;
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 0x03:
                BEGINPACKET( pak, 0x7e5 );
                ADDBYTE    ( pak, 0x01 );
                ADDWORD    ( pak, 0x0000 );
                thisclient->SendPacket( &pak );
        break;
        default:
            Log( MSG_WARNING,"Unknown 7e5 action %i",action);
    }
    return true;
}

// Create a chatroom?
bool CCharServer::pakChatrooms ( CCharClient* thisclient, CPacket* P )
{
	if(!thisclient->isLoggedIn) return false;
    return true;
}

// delete/resurect character
bool CCharServer::pakDeleteChar( CCharClient* thisclient, CPacket* P )
{
	if(!thisclient->isLoggedIn) return false;
	char* name = (char*)&P->Buffer[2];
    MYSQL_RES *result;
	MYSQL_ROW row;
	result = DB->QStore("SELECT account_name FROM characters WHERE char_name='%s' LIMIT 1", name);
	if(result==NULL) return false;
	row = mysql_fetch_row(result);

	//LMA: no case.
	//if (strcmp(row[0], thisclient->username)!=0)
	if (stricmp(row[0], thisclient->username)!=0)
	{
	    Log(MSG_HACK, "User %s tried deleting another users (%s) character.", thisclient->username, name);
	    DB->QFree( );
	    return false;
	}
	DB->QFree( );
    short int action = GETBYTE((*P), 1 );
    unsigned long int DeleteTime = 0;
    switch(action)
    {
        case 0x00://Resurect
        {
            DeleteTime = 0;
            if(!DB->QExecute(" UPDATE characters SET deletetime=0 WHERE char_name='%s'",
                    (char*)&P->Buffer[2] ))
                return false;
        }
        break;
        case 0x01://Delete
        {
            DeleteTime = GetServerTime( ) + Config.DeleteTime;
            if(!DB->QExecute(" UPDATE characters SET deletetime=%i WHERE char_name='%s'",
                    DeleteTime, (char*)&P->Buffer[2] ))
                return false;

        }
        break;
    }
    BEGINPACKET( pak, 0x714 );
    if(DeleteTime > 0 )
    {
        ADDDWORD   ( pak, Config.DeleteTime );
    }
    else
    {
        ADDDWORD   ( pak, 0x00000000 );
    }
    ADDSTRING  ( pak, (char*)&P->Buffer[2] );
    ADDBYTE    ( pak, 0x00 );
    thisclient->SendPacket( &pak );
    return true;
}

bool CCharServer::pakUpdateLevel( CCharClient* thisclient, CPacket* P )
{
    if(!thisclient->isLoggedIn) return false;
    WORD charid = GETWORD((*P),0);
    WORD level = GETWORD((*P),2);
    for(UINT i=0;i<ClientList.size();i++)
    {
        CCharClient* player = (CCharClient*) ClientList.at(i);
        if(player->charid==charid)
        {
            player->level = level;
            break;
        }
    }
    return true;
}

// Disconnect client from char/world server
bool CCharServer::pakLoginDSClient( CCharClient* thisclient, CPacket* P )
{
    unsigned int userid = GETDWORD((*P), 1 );
    CCharClient* otherclient = GetClientByUserID( userid );
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 1:
        {
            if(otherclient==NULL)
            {
                Log( MSG_WARNING, "Userid '%u' is not online", userid );
                return true;
            }
            otherclient->isLoggedIn = false;
            otherclient->isActive = false;
            BEGINPACKET( pak, 0x502 );
            ADDBYTE    ( pak, 1 );
            ADDDWORD   ( pak, userid );
            //ADDBYTE    ( pak, 0x00 );
            cryptPacket( (char*)&pak, NULL );
            CChanels* thischannel = GetChannelByID( otherclient->channel );
            if(thischannel!=NULL)
                send( thischannel->sock, (char*)&pak, pak.Size, 0 );
        }
        break;
    }
    return true;
}

