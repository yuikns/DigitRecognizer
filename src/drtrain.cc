#include "perceptron.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void ParseCSV(const string& csvSource, vector<vector<string> >& lines);


void ParseCSV(const string& csvSource, vector<vector<string> >& lines)
{
	bool inQuote(false);
	bool newLine(false);
	string field;
	lines.clear();
	vector<string> line;

	string::const_iterator aChar = csvSource.begin();
	while (aChar != csvSource.end())
	{
		switch (*aChar)
		{
		case '"':
			newLine = false;
			inQuote = !inQuote;
			break;

		case ',':
			newLine = false;
			if (inQuote == true)
			{
				field += *aChar;
			}
			else
			{
				line.push_back(field);
				field.clear();
			}
			break;

		case '\n':
		case '\r':
			if (inQuote == true)
			{
				field += *aChar;
			}
			else
			{
				if (newLine == false)
				{
				   line.push_back(field);
				   lines.push_back(line);
				   field.clear();
				   line.clear();
				   newLine = true;
				}
			}
			break;

		default:
			newLine = false;
			field.push_back(*aChar);
			break;
		}

		aChar++;
	}

	if (field.size())
	  line.push_back(field);
	if (line.size())
	  lines.push_back(line);
}



int main(int argc,char * argv[])
{
	const char * filename = "../data/train.csv";
		FILE *fp = fopen(filename,"rb");
	size_t sz;
	char *buff;
	fseek(fp, 0, SEEK_END);  
	sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buff = (char *)malloc(sizeof(char)*sz);
	fread(buff,sz,1,fp); // 故意的
	string info(buff);
	free(buff);
	fclose(fp);
	vector<vector<string> > lines;
	ParseCSV(info,lines);
	perceptron pModel[10];
	//lines[0].erase(&(lines[0][0]));   
	for(int i = 0 ; i < 10 ; i ++ )
	{
		pModel[i].set_word_seq(lines[0]);
	}
	printf("loading ... "); fflush(stdout);
	for(vector<vector<string> >::size_type ix = 1 ; ix < (lines.size() * 0.8); ix ++ )
	{
		if(ix % 1000 == 0 ) 
		{
			printf("%d...",(int)ix);fflush(stdout);
		}
		if(lines[ix].size() < 10 ) continue;
		fsdoc doc ;
		int label = atoi(lines[ix][0].c_str());
		for(vector<string>::size_type jx = 1 ; jx != lines[ix].size() ; jx++ )
		{
			doc.x[jx-1] = atoi(lines[ix][jx].c_str()) > 125 ? 1 : -1;
		}
		/*
		printf("[%d]:\n",doc.label);
		for(int i = 0 ; i < 784 ; i ++){
			if(i % 28 == 0 ) printf("\n");
			if((int)doc.x[i] == -1 ) printf("_");
			else printf("#");
		}
		printf("\n");
		*/
		for(int i = 0 ; i < 10 ; i ++ )
		{
			doc.label = i == label ? 1 : -1;
			pModel[i].add_doc(doc);
		}
	}
	printf("done\n"); fflush(stdout);
	char nm[2] = "";
	for(int i = 0 ; i < 10 ; i ++ )
	{
		pModel[i].learn_doc();
		nm[0] = i + '0';
		pModel[i].store_model(nm);
	}
	return 0;
}

