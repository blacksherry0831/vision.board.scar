#include "cfg.h"
/*-----------------------------------*/
int G_Sigma=6;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSigma()
{
	return G_Sigma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigma(int _sigma)
{
	G_Sigma=_sigma;
	int param[1]={_sigma};
	SaveParam2SDCard(PATH_SDCARD_IMG_SIGMA_CFG,param,1);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveParam2SDCard(const char* const path,const int* _param,const int _size)
{
		char buff[1024];
		FILE *fp = fopen(path,"wt+");

	 	int i=0;

	 	if (NULL == fp){
	 		return ;
	 	}

	 	for(i=0;i<_size;i++){
	 		snprintf(buff,sizeof(buff),"%d,%d\n",i,_param[i]);
	 		fputs(buff,fp);
	 	}

	 	 fclose(fp);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigma4SDCard()
{
	int param[1]={0};
	if(is_file_exist(PATH_SDCARD_IMG_SIGMA_CFG)==SUCCESS){
		ReadParam4SDCard(PATH_SDCARD_IMG_SIGMA_CFG,param, 1);
		SetSigma(param[0]);
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void ReadParam4SDCard(const char* const path, int* _param,const int _size)
{
			char buff[1024]={0};
			int i=0;
			FILE *fp = fopen(path,"r");

						if (NULL == fp){
							return ;
						}

						for(i=0;i<_size;i++){

							memset(buff,0,sizeof(buff));
							fgets(buff,sizeof(buff),fp);

							 char*token=strtok(buff,",");

							 while(token!=NULL){

								 _param[i]= atoi(token);

								 token=strtok(NULL,",");

							 }

						}

		 fclose(fp);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetoutsideSigma(int _sigma)
{
	SetSigma(_sigma);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetinsideSigma(int _sigma)
{
	SetSigma(_sigma);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
