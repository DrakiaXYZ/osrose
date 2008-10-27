//lmame: LTB file reader.

#include "ltbhandler.h"


void LTBStoreData(char* filename, LTBData* data)
{
    long int first_data=0;
    long int cur_offset=0;
    DWORD nb_box=0;
    WORD nb_dial_box=0;
    int nb_dialogs=0;
    char templma[2];
    char tempfield[1024];


    FILE* fh = fopen( filename, "rb" );
	if (  fh== NULL )
	{
		cout << "Could not load LTB" << endl;
		return;
	}

    //How many dialogs?
    fread( &nb_box, 4, 1, fh);
	fread(&nb_dial_box,2,1,fh);
	nb_dialogs=nb_box*nb_dial_box;

    data->nb_sentence=nb_box;

    //reading location of first data.
    fseek(fh,8,SEEK_SET);
    fread(&first_data,4,1,fh);
    cur_offset=8;
    fseek(fh,cur_offset,SEEK_SET);


    //making the offset list.
    long int cpt=0;
    map <int,Dialog> list_dialog;

	while(cur_offset<first_data)
	{
	    Dialog temp_dial;

		//dialog.
		//offset is 4 bytes, lg is 2 bytes.
		temp_dial.dialognb=cpt;
		fread(&temp_dial.offsetd,4,1,fh);
		fread(&temp_dial.lengthd,2,1,fh);
		list_dialog[cpt]=temp_dial; //I know, it's faster with .insert...
		cur_offset+=6;
		cpt++;

		if(temp_dial.offsetd==0&&temp_dial.lengthd==0)
		{
		    continue;
		}

	}

    //Getting dialogs...
    int lang=0;
    int no_block=0;
    NPCLTB templtb;

	for (unsigned int k=0;k<list_dialog.size();k++)
	{
	    lang=k%nb_box;
	    no_block=int(k/nb_box);

		if(lang==LTBINDEX)
		{
            templtb.name="NoName";
            templtb.sentence="NoSentence";
		}

		if(list_dialog[k].offsetd==0)
		{
			continue;
		}

		//reading data
		//lg*2 because of unicode :)
		string temp;
		fseek(fh,list_dialog[k].offsetd,SEEK_SET);

		if(lang!=LTBENGLISH&&lang!=LTBINDEX)
		{
		    fread(&tempfield,list_dialog[k].lengthd*2,1,fh);
		    continue;
		}

		//unicode is NOT our friend :(
		for(int j=0;j<(list_dialog[k].lengthd*2);j++)
		{
		    fread(&templma,1,1,fh);
		    if (templma[0]=='\0')
                continue;
            temp+=templma[0];
		}

        if (lang==LTBENGLISH)
        {
            templtb.sentence=temp;
            data->record.push_back(templtb);
            continue;
        }

        templtb.name=temp;
	}

    //closing the file...
    fclose(fh);


    return;
}

