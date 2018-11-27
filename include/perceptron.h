#ifndef __PERCEPTION_H__
#define __PERCEPTION_H__

#include <vector>
#include <string>
#include <cstdio>

#ifndef FEATURE_NUM
#define FEATURE_NUM 784
#endif // FEATURE_NUM

typedef struct{
	double x[FEATURE_NUM];
	int label;
}fsdoc; // train/predict doc

namespace std{

class perceptron
{
public :
	perceptron()
	{
		label = 0;
		for(int i = 0 ; i < FEATURE_NUM;i++)
		{
			w[i] = 0;
		}
		alpha = 0.025;
		convergence = 1000;
		
	}
	
	~perceptron()
	{
	}
	
	//train
	void add_doc(fsdoc doc)
	{
		all_doc.push_back(doc);
	}
	
	void learn_doc()
	{
		//int no_change_continue_num = 0;
		printf("learning ... "); fflush(stdout);
		for(int c = 0 ; c < convergence ; c ++ )
		{
			if(c % 10 == 0 )
			{
				printf("%d...",c);
				fflush(stdout);
			}
			bool changed = false;
			for(vector<fsdoc>::size_type ix = 0; ix < all_doc.size() ; ix ++)
			{
				double p = 0;
				for(int j = 0 ; j < FEATURE_NUM ; j ++ )
				{
					p += w[j] * all_doc[ix].x[j];
				}
				if(all_doc[ix].label * p  <= 0 )
				{
					changed = true;
					for(int j = 0 ; j < FEATURE_NUM ; j++ )
					{
						w[j] += alpha * all_doc[ix].label *  all_doc[ix].x[j];
					}
				}
			}
			if(!changed)
			{
				//no_change_continue_num ++ ;
				//if(no_change_continue_num > 20)
				//{
					//printf("no any change at %d continued times : %d\n",c,no_change_continue_num);
					printf("no any change at %d\n",c);
					break;
				//}
			}else{
				//no_change_continue_num = 0;
			}
		}
		printf("done\n");
	}
	
	bool store_model(const char * mkname)
	{
		char modelname[255];
		sprintf(modelname,"model/%s.model",mkname);
		FILE * fp = fopen(modelname,"w");
		if(fp == NULL ) return false;
		for(int i = 0 ; i < FEATURE_NUM ; i ++)
		{
			fprintf(fp,"%s\t%lf\n",word_seq[i].c_str(),w[i]);
		}
		fclose(fp);
		return true;
	}
	
	// predict
	bool load_model(const char * mkname)
	{
		char modelname[255];
		sprintf(modelname,"model/%s.model",mkname);
		FILE * fp = fopen(modelname,"r");
		if(fp == NULL ) return false;
		for(int i = 0 ; i < FEATURE_NUM ; i ++)
		{
			char buff[1024];
			fscanf(fp,"%s\t%lf\n",buff,&w[i]);
			word_seq.push_back(string(buff));
			//printf("%s ## %lf \n",word_seq[i].c_str(),w[i]);
		}
		fclose(fp);
		return true;
	}
	
	int predict(fsdoc doc)
	{
		
		double p = 0;
		for(int j = 0 ; j < FEATURE_NUM ; j ++ )
		{
			p += w[j] * doc.x[j];
		}
		if(p < 0) return -1;
		else return 1;
	}
	
	// etc.
	void set_word_seq(vector<string> wseq)
	{
		
		for(vector<string>::size_type i = 1 ; i < wseq.size(); i ++ ) word_seq.push_back(wseq[i]);
	}
	
	vector<string> get_word_seq()
	{
		return word_seq;
	}

private :
	int label;
	double w[FEATURE_NUM];
	vector<string> word_seq; //size = FEATURE_NUM
	vector<fsdoc> all_doc;
	int convergence;
	double alpha; // learning rate , value <1 Example: Can be set as 0.25

};

}


#endif // __PERCEPTION_H__
