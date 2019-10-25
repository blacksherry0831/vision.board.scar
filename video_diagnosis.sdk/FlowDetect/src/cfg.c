#include "cfg.h"
/*-----------------------------------*/
static int G_Sigma_Up=6;
static int G_Sigma_Down=6;
/*-----------------------------------*/
static volatile unsigned int G_SENSOR=0xff;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSigmaUp()
{
	return G_Sigma_Up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetSigmaDown()
{
	return G_Sigma_Down;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigmaUp(int _sigma)
{
	G_Sigma_Up=_sigma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigmaUp2FPGA(int _sigma)
{
	SetSigmaUp(_sigma);
	fpga_set_sigma_up(G_Sigma_Up);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigmaDown(int _sigma)
{
	G_Sigma_Down=_sigma;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetSigmaDown2FPGA(int _sigma)
{
	SetSigmaDown(_sigma);
	fpga_set_sigma_down(G_Sigma_Down);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SaveParam2SDCard(
		const char* const path,
		const int* _param,
		const int _size)
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
void SetoutsideSigma()
{
		fpga_set_sigma_up(GetSigmaUp());
		fpga_set_sigma_down(GetSigmaDown());
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetinsideSigma()
{
		fpga_set_sigma_up(GetSigmaUp());
		fpga_set_sigma_down(GetSigmaDown());
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetGlobalSensor(unsigned int _channel)
{
	G_SENSOR=_channel;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetGlobalSensor()
{
	return G_SENSOR;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
unsigned int GetGlobalSensorMask(const int _ch)
{

			if(G_SENSOR & (0x01<<_ch)){
				return TRUE;
			}else{
				return FALSE;
			}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
