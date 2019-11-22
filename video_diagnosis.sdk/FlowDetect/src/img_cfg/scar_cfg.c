#include "scar_cfg.h"
/*-----------------------------------*/
static SCAR_PARAM  G_SCAR_PARAM={
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		0,
		1};
/*-----------------------------------*/
SCAR_MASK_SEQ_MULTI	G_MASK_SEQ_MULTI;
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void InitScarMaskSeq()
{
	memset(&G_MASK_SEQ_MULTI,0,sizeof(SCAR_MASK_SEQ_MULTI));
	SetScarCurrentSerialNumber_default();
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSnoIdx()
{
	return G_MASK_SEQ_MULTI.mask_sno%MAX_DETECT_SNO;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarCurrentMask(
		const int _sno,
		const unsigned int* 	_mask_seq,
		const int	_num,
		const int  _loop)
{
	const int SZ_INT=sizeof(int);
	assert(SZ_INT==4);

	G_MASK_SEQ_MULTI.mask_sno=_sno;
	const int sno_i=GetMaskSnoIdx();
	G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq_num	=_num;
	G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq_loop	=_loop;

	int mi=0;

	for(mi=0;mi<_num;mi++){

		const unsigned int*		seq_current=_mask_seq+mi*8;

		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].mask_id= UChar2Int((const unsigned char*)(seq_current),SZ_INT);
		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].scar_th.global_th_up=UChar2Int((const unsigned char*)(seq_current+1),SZ_INT);
		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].scar_th.global_th_down=UChar2Int((const unsigned char*)(seq_current+2),SZ_INT);
		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].scar_th.row_th_up=UChar2Int((const unsigned char*)(seq_current+3),SZ_INT);
		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].scar_th.row_th_down=UChar2Int((const unsigned char*)(seq_current+4),SZ_INT);
		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].scar_th.col_th_up=UChar2Int((const unsigned char*)(seq_current+5),SZ_INT);
		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].scar_th.col_th_down=UChar2Int((const unsigned char*)(seq_current+6),SZ_INT);
		G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[mi].work_mode=UChar2Int((const unsigned char*)(seq_current+7),SZ_INT);

	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarCurrentSerialNumber_default()
{
	G_MASK_SEQ_MULTI.mask_sno=0xffffffff;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarMaskSeq_SNO()
{
	return G_MASK_SEQ_MULTI.mask_sno;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarMaskChannel_Total_Num()
{
	const int sno_i=GetMaskSnoIdx();
	if(sno_i==0xffffffff){
		return INT32_MAX;
	}else{
		return G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq_num;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarMaskSeqChannel_Is_Loop()
{
	const int sno_i=GetMaskSnoIdx();
	if(sno_i==0xffffffff){
		return 0;
	}else{
		return G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq_loop;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarCurrentMask_Cmd(const CMD_CTRL* const  _cmd)
{

	const unsigned int* seq_ptr				=	ParseMaskSeq_Ptr(_cmd);
	const int   		mask_img_num		=	ParseMaskSeq_MaskImgNumber(_cmd);
	const int   		seq_serial_number	=	ParseMaskSeq_SerialNumber(_cmd);
	const int   		seq_loop			=	ParseMaskSeq_Loop(_cmd);

	SetScarCurrentMask(
			seq_serial_number,
			seq_ptr,
			mask_img_num,
			seq_loop);

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarWorkMode()
{
	return G_SCAR_PARAM.work_mode;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarGlobalThresholdUp()
{
	return G_SCAR_PARAM.scar_th.global_th_up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarGlobalThresholdDown()
{
	return G_SCAR_PARAM.scar_th.global_th_down;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarRowThresholdUp()
{
	return G_SCAR_PARAM.scar_th.row_th_up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarRowThresholdDown()
{
	return G_SCAR_PARAM.scar_th.row_th_down;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarColThresholdUp()
{
	return G_SCAR_PARAM.scar_th.col_th_up;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetScarColThresholdDown()
{
	return G_SCAR_PARAM.scar_th.col_th_down;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarWorkMode(const int _th)
{
	G_SCAR_PARAM.work_mode=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdUp(const int _th)
{
	G_SCAR_PARAM.scar_th.global_th_up=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdDown(const int _th)
{
	G_SCAR_PARAM.scar_th.global_th_down=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdUp(const int _th)
{
	G_SCAR_PARAM.scar_th.row_th_up=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdDown(const int _th)
{
	G_SCAR_PARAM.scar_th.row_th_down=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdUp(const int _th)
{
	G_SCAR_PARAM.scar_th.col_th_up=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdDown(const int _th)
{
	G_SCAR_PARAM.scar_th.col_th_down=_th;
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarWorkMode2FPGA(const int _th)
{
	SetScarWorkMode(_th);
	fpga_img_scar_detect_mode(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdUp2FPGA(const int _th)
{
	SetScarGlobalThresholdUp(_th);
	fpga_img_scar_detect_set_g_th_up(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarGlobalThresholdDown2FPGA(const int _th)
{
	SetScarGlobalThresholdDown(_th);
	fpga_img_scar_detect_set_g_th_down(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdUp2FPGA(const int _th)
{
	SetScarRowThresholdUp(_th);
	fpga_img_scar_detect_set_row_th_up(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarRowThresholdDown2FPGA(const int _th)
{
	SetScarRowThresholdDown(_th);
	fpga_img_scar_detect_set_row_th_down(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdUp2FPGA(const int _th)
{
	SetScarColThresholdUp(_th);
	fpga_img_scar_detect_set_col_th_up(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
void SetScarColThresholdDown2FPGA(const int _th)
{
	SetScarColThresholdDown(_th);
	fpga_img_scar_detect_set_col_th_down(_th);
}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeqChannel(const int _idx)
{
	const int sno_i=GetMaskSnoIdx();
	if(sno_i==0xffffffff){
			return 0;
	}else{
			return G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[_idx].mask_id;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeq_work_mode(const int _idx)
{
	const int sno_i=GetMaskSnoIdx();
	if(sno_i==0xffffffff){
			return 0;
	}else{
		return G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[_idx].work_mode;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeq_g_th_up(const int _idx)
{
	const int sno_i=GetMaskSnoIdx();
	if(sno_i==0xffffffff){
			return 0;
	}else{
			return G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[_idx].scar_th.global_th_up;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeq_g_th_down(const int _idx)
{

	const int sno_i=GetMaskSnoIdx();
	if(sno_i==0xffffffff){
			return 0;
	}else{
			return G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[_idx].scar_th.global_th_down;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeq_row_th_up(const int _idx)
{

	const int sno_i=GetMaskSnoIdx();
	if(sno_i==0xffffffff){
			return 0;
	}else{
			return G_MASK_SEQ_MULTI.mask_seqs[sno_i].mask_seq[_idx].scar_th.row_th_up;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeq_row_th_down(const int _idx)
{

	const int sno_i=GetMaskSnoIdx();
		if(sno_i==0xffffffff){
			return 0;
	}else{
		return G_MASK_SEQ_MULTI.mask_seqs[ sno_i].mask_seq[_idx].scar_th.row_th_down;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeq_col_th_up(const int _idx)
{

	const int sno_i=GetMaskSnoIdx();
		if(sno_i==0xffffffff){
			return 0;
	}else{
		return G_MASK_SEQ_MULTI.mask_seqs[ sno_i].mask_seq[_idx].scar_th.col_th_up;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
int GetMaskSeq_col_th_down(const int _idx)
{

	const int sno_i=GetMaskSnoIdx();
		if(sno_i==0xffffffff){
			return 0;
	}else{
		return G_MASK_SEQ_MULTI.mask_seqs[ sno_i].mask_seq[_idx].scar_th.col_th_down;
	}

}
/*-----------------------------------*/
/**
 *
 */
/*-----------------------------------*/
