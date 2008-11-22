// Props to ExJam for this code :D
#include "../worldserver.h"
#ifdef USENEWQUESTSYSTEM

void CWorldServer::ReadQSD(strings path, dword index){
	CRoseFile* fh = new CRoseFile(path, FM_READ | FM_BINARY);
	if(fh->IsOpen()) { // goto done;

	Log(MSG_LOAD, "Loading %s", path);

	fh->Seek(4, SEEK_CUR);
	dword BlockCount = fh->Get<dword>();
	fh->Seek(fh->Get<word>(), SEEK_CUR);
	for(dword i = 0; i < BlockCount; i++){
		dword RecordCount = fh->Get<dword>();
		fh->Seek(fh->Get<word>(), SEEK_CUR);
		for(dword j = 0; j < RecordCount; j++){
			CQuestTrigger* trigger = new CQuestTrigger();
			trigger->id=((index*0x10000)+(i*0x100)+j);
			trigger->CheckNext = fh->Get<byte>();
			trigger->ConditionCount = fh->Get<dword>();
			trigger->ActionCount = fh->Get<dword>();
			dword len = fh->Get<word>();
			trigger->TriggerName = new char[len+1];
			fh->Read(trigger->TriggerName, len, 1);
			trigger->TriggerName[len] = 0;

			if(trigger->ConditionCount > 0){
				trigger->Conditions = new CQuestTrigger::SQuestDatum*[trigger->ConditionCount];
				for(dword k = 0; k < trigger->ConditionCount; k++){
					CQuestTrigger::SQuestDatum* data = new CQuestTrigger::SQuestDatum();
					data->size = fh->Get<int>();
					data->opcode = fh->Get<int>();
					data->data = new byte[data->size - 8];
					fh->Read(data->data, data->size - 8, 1);
					trigger->Conditions[k] = data;
				}
			}else{
				trigger->Conditions = NULL;
			}

			if(trigger->ActionCount > 0){
				trigger->Actions = new CQuestTrigger::SQuestDatum*[trigger->ActionCount];
				for(dword k = 0; k < trigger->ActionCount; k++){
					CQuestTrigger::SQuestDatum* data = new CQuestTrigger::SQuestDatum();
					data->size = fh->Get<int>();
					data->opcode = fh->Get<int>() - 0x01000000;
					data->data = new byte[data->size - 8];
					fh->Read(data->data, data->size - 8, 1);
					trigger->Actions[k] = data;
				}
			}else{
				trigger->Actions = NULL;
			}

			trigger->TriggerHash = MakeStrHash(trigger->TriggerName);
			TriggerList.push_back( trigger );
		}
	}
}else
     Log( MSG_ERROR, "QSD File: '%s'", path );

    fh->Close();
	delete fh;
}


void CWorldServer::LoadQuestData()
{
    //LMA: loading Pegasus data.
    CStrStb* stbQuest=NULL;
    if(Config.is_pegasus==1)
    {
        stbQuest = new CStrStb("3DDataPeg/stb/LIST_QUESTDATA.STB");
    }
    else
    {
        stbQuest = new CStrStb("3ddata/stb/LIST_QUESTDATA.STB");
    }

	char buffer [100];
	char path[100];

	for(dword i = 1; i < stbQuest->Rows(); i++){
		if(stbQuest->Data(i, 0)){
			strcpy((char*)&buffer, stbQuest->Data(i, 0));

			for (int loop = 0; buffer[loop] !=0; loop++)
			{
				buffer[loop] = toupper(buffer[loop]);
				if (buffer[loop] == '\\')
				{
					buffer[loop] = '/';
				}

                //LMA: For Pegasus.
			    if(Config.is_pegasus==1&&loop<7)
                    path[loop]=toupper(buffer[loop]);
			}

			//LMA: Patch for Pegasus server data files:
			if(Config.is_pegasus==1)
			{
			    char temp[] = "3DDATA/";
			    if(strcmp (temp,path)==0)
			    {
			        string temps=buffer;
			        temps="3DDATAPEG/"+temps.substr(7);
                    strcpy ((char*)&buffer,temps.c_str());
                    buffer[temps.size()]=0;
			    }

			}

			GServer->ReadQSD((strings)&buffer,i);
		}
	}

	Log(MSG_INFO, "Finished loading quest data                              ");

	qstCondFunc[0] = &QUEST_COND_000;
	qstCondFunc[1] = &QUEST_COND_001;
	qstCondFunc[2] = &QUEST_COND_002;
	qstCondFunc[3] = &QUEST_COND_003;
	qstCondFunc[4] = &QUEST_COND_004;
	qstCondFunc[5] = &QUEST_COND_005;
	qstCondFunc[6] = &QUEST_COND_006;
	qstCondFunc[7] = &QUEST_COND_007;
	qstCondFunc[8] = &QUEST_COND_008;
	qstCondFunc[9] = &QUEST_COND_009;
	qstCondFunc[10] = &QUEST_COND_010;
	qstCondFunc[11] = &QUEST_COND_011;
	qstCondFunc[12] = &QUEST_COND_012;
	qstCondFunc[13] = &QUEST_COND_013;
	qstCondFunc[14] = &QUEST_COND_014;
	qstCondFunc[15] = &QUEST_COND_015;
	qstCondFunc[16] = &QUEST_COND_016;
	qstCondFunc[17] = &QUEST_COND_017;
	qstCondFunc[18] = &QUEST_COND_018;
	qstCondFunc[19] = &QUEST_COND_019;
	qstCondFunc[20] = &QUEST_COND_020;
	qstCondFunc[21] = &QUEST_COND_021;
	qstCondFunc[22] = &QUEST_COND_022;
	qstCondFunc[23] = &QUEST_COND_023;
	qstCondFunc[24] = &QUEST_COND_024;
	qstCondFunc[25] = &QUEST_COND_025;
	qstCondFunc[26] = &QUEST_COND_026;
	qstCondFunc[27] = &QUEST_COND_027;
	qstCondFunc[28] = &QUEST_COND_028;
	qstCondFunc[29] = &QUEST_COND_029;
	qstCondFunc[30] = &QUEST_COND_030;

	qstRewdFunc[0] = &QUEST_REWD_000;
	qstRewdFunc[1] = &QUEST_REWD_001;
	qstRewdFunc[2] = &QUEST_REWD_002;
	qstRewdFunc[3] = &QUEST_REWD_003;
	qstRewdFunc[4] = &QUEST_REWD_004;
	qstRewdFunc[5] = &QUEST_REWD_005;
	qstRewdFunc[6] = &QUEST_REWD_006;
	qstRewdFunc[7] = &QUEST_REWD_007;
	qstRewdFunc[8] = &QUEST_REWD_008;
	qstRewdFunc[9] = &QUEST_REWD_009;
	qstRewdFunc[10] = &QUEST_REWD_010;
	qstRewdFunc[11] = &QUEST_REWD_011;
	qstRewdFunc[12] = &QUEST_REWD_012;
	qstRewdFunc[13] = &QUEST_REWD_013;
	qstRewdFunc[14] = &QUEST_REWD_014;
	qstRewdFunc[15] = &QUEST_REWD_015;
	qstRewdFunc[16] = &QUEST_REWD_016;
	qstRewdFunc[17] = &QUEST_REWD_017;
	qstRewdFunc[18] = &QUEST_REWD_018;
	qstRewdFunc[19] = &QUEST_REWD_019;
	qstRewdFunc[20] = &QUEST_REWD_020;
	qstRewdFunc[21] = &QUEST_REWD_021;
	qstRewdFunc[22] = &QUEST_REWD_022;
	qstRewdFunc[23] = &QUEST_REWD_023;
	qstRewdFunc[24] = &QUEST_REWD_024;
	qstRewdFunc[25] = &QUEST_REWD_025;
	qstRewdFunc[26] = &QUEST_REWD_026;
	qstRewdFunc[27] = &QUEST_REWD_027;
	qstRewdFunc[28] = &QUEST_REWD_028;
	qstRewdFunc[34] = &QUEST_REWD_034;


    //LMA: AIP
	qstCondFuncC[0] = &QUEST_CONDC_000;
	qstCondFuncC[1] = &QUEST_CONDC_001;
	qstCondFuncC[2] = &QUEST_CONDC_002;
	qstCondFuncC[3] = &QUEST_CONDC_003;
	qstCondFuncC[4] = &QUEST_CONDC_004;
	qstCondFuncC[5] = &QUEST_CONDC_005;
	qstCondFuncC[6] = &QUEST_CONDC_006;
	qstCondFuncC[7] = &QUEST_CONDC_007;
	qstCondFuncC[8] = &QUEST_CONDC_008;
	qstCondFuncC[9] = &QUEST_CONDC_009;
	qstCondFuncC[10] = &QUEST_CONDC_010;
	qstCondFuncC[11] = &QUEST_CONDC_011;
	qstCondFuncC[12] = &QUEST_CONDC_012;
	qstCondFuncC[13] = &QUEST_CONDC_013;
	qstCondFuncC[14] = &QUEST_CONDC_014;
	qstCondFuncC[15] = &QUEST_CONDC_015;
	qstCondFuncC[16] = &QUEST_CONDC_016;
	qstCondFuncC[17] = &QUEST_CONDC_017;
	qstCondFuncC[18] = &QUEST_CONDC_018;
	qstCondFuncC[19] = &QUEST_CONDC_019;
	qstCondFuncC[20] = &QUEST_CONDC_020;
	qstCondFuncC[21] = &QUEST_CONDC_021;
	qstCondFuncC[22] = &QUEST_CONDC_022;
	qstCondFuncC[23] = &QUEST_CONDC_023;
	qstCondFuncC[24] = &QUEST_CONDC_024;
	qstCondFuncC[25] = &QUEST_CONDC_025;
	qstCondFuncC[26] = &QUEST_CONDC_026;
	qstCondFuncC[27] = &QUEST_CONDC_027;
	qstCondFuncC[28] = &QUEST_CONDC_028;
	qstCondFuncC[29] = &QUEST_CONDC_029;
	qstCondFuncC[30] = &QUEST_CONDC_030;

	qstRewdFuncC[0] = &QUEST_REWDC_000;
	qstRewdFuncC[1] = &QUEST_REWDC_001;
	qstRewdFuncC[2] = &QUEST_REWDC_002;
	qstRewdFuncC[3] = &QUEST_REWDC_003;
	qstRewdFuncC[4] = &QUEST_REWDC_004;
	qstRewdFuncC[5] = &QUEST_REWDC_005;
	qstRewdFuncC[6] = &QUEST_REWDC_006;
	qstRewdFuncC[7] = &QUEST_REWDC_007;
	qstRewdFuncC[8] = &QUEST_REWDC_008;
	qstRewdFuncC[9] = &QUEST_REWDC_009;
	qstRewdFuncC[10] = &QUEST_REWDC_010;
	qstRewdFuncC[11] = &QUEST_REWDC_011;
	qstRewdFuncC[12] = &QUEST_REWDC_012;
	qstRewdFuncC[13] = &QUEST_REWDC_013;
	qstRewdFuncC[14] = &QUEST_REWDC_014;
	qstRewdFuncC[15] = &QUEST_REWDC_015;
	qstRewdFuncC[16] = &QUEST_REWDC_016;
	qstRewdFuncC[17] = &QUEST_REWDC_017;
	qstRewdFuncC[18] = &QUEST_REWDC_018;
	qstRewdFuncC[19] = &QUEST_REWDC_019;
	qstRewdFuncC[20] = &QUEST_REWDC_020;
	qstRewdFuncC[21] = &QUEST_REWDC_021;
	qstRewdFuncC[22] = &QUEST_REWDC_022;
	qstRewdFuncC[23] = &QUEST_REWDC_023;
	qstRewdFuncC[24] = &QUEST_REWDC_024;
	qstRewdFuncC[25] = &QUEST_REWDC_025;
	qstRewdFuncC[26] = &QUEST_REWDC_026;
	qstRewdFuncC[27] = &QUEST_REWDC_027;
	qstRewdFuncC[28] = &QUEST_REWDC_028;
	qstRewdFuncC[34] = &QUEST_REWDC_034;


	delete stbQuest;
}
#endif
