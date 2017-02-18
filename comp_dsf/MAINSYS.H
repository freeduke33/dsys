/*     Last modify 2.12.93 by D.Kokorev */
#ifndef __mainsys_II_
#define __mainsys_II_

#ifndef NOARG
#define NOARG void
#endif

#ifndef VOID
#define VOID void
#endif

#ifndef CTYP
#define CTYP pascal
#endif


enum _block_type_  {  EASY_ZVENO =1,  DIF_ZVENO  =2,  // функциональные звенья
		      EASY_GEN   =3,  DIF_GEN    =4,
		      DSYS_BEG   =5,  DSYS_END   =6,

		      BLK_ADD    =7,  BLK_SUB    =8,  // арифметические звенья
		      BLK_MUL    =9,  BLK_DIV    =10,

		      BLK_HOR   =11,  BLK_VER    =12, // соединительные звенья
		      BLK_LEFT  =13,  BLK_RIGHT  =14,
		      BLK_NLEFT =15,  BLK_NRIGHT =16,
		      BLK_KREST =17,  BLK_VTR    =18,
		      BLK_LTR   =19,  BLK_RTR    =20,
		      BLK_NTR   =21,  BLK_NONE   =22
                   };

enum _error_type_  { ERR_NONE, ERR_BLK };

enum _retval_type_ { SUCCESS, ERROR, WARNING };

enum _ask_type_    { ASK_CONFIRM, DEFAULT_OK, DEFAULT_ERROR, ASK_SELECT };
enum _trig_type_   { CANCEL, CONTINUE, SAVE };

enum _emode_type_  { inWINDOW, inSCREEN, HIDDEN };
enum _wmode_type_  { WAIT_KEY, NOWAIT_KEY, WAIT_TIME };
enum _mmode_type_  { SAVE_MSG, NOSAVE_MSG };

typedef char  _dir_type_[64];
typedef char  _dirs_type_[256];
typedef char  _name_type_[16];
typedef char  _file_type_[64+16];
typedef char  _cmdline_[128];


enum _sig_type_  { SIG_NOMEM, SIG_ERRARG, SIG_ERRIO, SIG_GLOBAL };
enum _gen_type_  { SIN, PSIN, MEANDR, ONE, VOLUME };
enum _dgen_type_ { DSYS, PROGRAMM };


/* ====================================================================== */

typedef enum _sig_type_     SigType;
typedef enum _ask_type_     AskType;
typedef enum _trig_type_    TrigType;

typedef enum _gen_type_     GenT,  *GenP;
typedef enum _dgen_type_    DGenT, *DGenP;
typedef enum _emode_type_   EModeT,*EModeP;
typedef enum _wmode_type_   WModeT,*WModeP;
typedef enum _mmode_type_   MModeT,*MModeP;

typedef unsigned char       Byte,  ByteT,  *ByteP;
typedef   signed char       Short, ShortT, *ShortP;
typedef unsigned int        Word,  WordT,  *WordP;
typedef unsigned long       DWord, DWordT, *DWordP;
typedef enum _retval_type_  RetVal,RetValT,*RetValP;


typedef enum _block_type_     BlockT,  *BlockP;
typedef enum _error_type_     ErrT,    *ErrP;
typedef struct _date_type_    DateT,   *DateP;
typedef struct _param_struct_ ParamT,  *ParamP;
typedef struct _global_param_ GlobalT, *GlobalP;
typedef struct _scr_struct_   ScrT,    *ScrP;
typedef Byte                  CurT,    *CurP;
typedef _dir_type_            DirT,    *DirP;
typedef _dirs_type_           DirsT,   *DirsP;
typedef _file_type_           FileT,   *FileP;
typedef _cmdline_             CmdLineT,*CmdLineP;
typedef _name_type_           NameT,   *NameP;
typedef struct _blk_struct_   DefBlkT, *DefBlkP;
typedef struct _exec_struct_  ExecT,   *ExecP;
typedef struct _config_       CfgT,    *CfgP;

typedef struct _file_id_      FileID;

typedef struct _EasyZveno_s_  EasyZvenoT, *EasyZvenoP;
typedef struct _EasyGen_s_    EasyGenT,   *EasyGenP;
typedef struct _DifZveno_s_   DifZvenoT,  *DifZvenoP;
typedef struct _DifGen_s_     DifGenT,    *DifGenP;

typedef struct _sin_struct_    SinT,    *SinP;
typedef struct _psin_struct_   PSinT,   *PSinP;
typedef struct _meandr_struct_ MeandrT, *MeandrP;
typedef struct _one_struct_    OneT,    *OneP;
typedef struct _volume_struct_ VolumeT, *VolumeP;

/* ====================================================================== */

struct _date_type_
{
 Word Date;
 Word Time;
};



struct _file_id_     // идентификатор файла
{
 char String[40];    // наименование типа файла
 Word CRC;           // CRC заголовка
};


struct _scr_struct_  // описание файла-схемы
{
  FileT name;

  CurT CurX,CurY;
  CurT BegX,BegY;
};


struct _EasyZveno_s_
{
  float A0,A1,A2;
  float B0,B1,B2;
};

struct _sin_struct_
{
 float Ampl,Chast,Faza;
 float Const;
};

struct _psin_struct_
{
 float Ampl[3],Chast[3],Faza[3];
 float Const;
};

struct _exec_struct_
{
 Word   FreeMem;        // свободное место в Kb
 Byte   wtime;		// время ожидания
 FileT  cmd;            // строка запуска
 EModeT win;            // режим запуска
 WModeT wait;           // режим после запуска
 MModeT msg;            // сообщения порожденного процесса
};


struct _meandr_struct_
{
 float Ampl,Chast;
 float Const;
};

struct _one_struct_
{
 float Ampl;
 float Wait;
};

struct _volume_struct_
{
 float Ampl;
 float Wait;
};




struct _EasyGen_s_
{
  GenT  Gen;
  union
   {
   SinT    Sin;
   PSinT   PSin;
   MeandrT Meandr;
   OneT    One;
   VolumeT Volume;
   } U;
};


struct _DifZveno_s_
{
  Word   Group;
  DateT  date;
  NameT  name;
};

struct _DifGen_s_
{
  DGenT Gen;
  union
   {
   DifZvenoT  Dsys;
   ExecT      Prg;
   } U;
};


struct _param_struct_
{
 BlockT Blk;
 Word  Group;
 union
  {
  EasyZvenoT   EasyZveno;
  DifZvenoT    DifZveno;
  EasyGenT     EasyGen;
  DifGenT      DifGen;
  } U;
};

struct _global_param_
{
  float Chast;     //  частота
  float Length;    //  длительность процесса
  BlockT  Gen;     //  глобальный генератор
  union
   {
   EasyGenT EasyGen;
   DifGenT  DifGen;
   } U;
};

struct _blk_struct_
{
  BlockT  Blk;
  CurT    x,y;
  ParamP  Dat;
  DefBlkP next,prev;
};






struct _config_
{
  FileID ID;
  DirT   dir_tmp,
         dir_project,
         dir_result,
         dir_work,
         dir_include;

// типы звеньев по умолчанию
  EasyZvenoT EasyZveno;
  EasyGenT   EasyGen;
  DifZvenoT  DifZveno;
  DifGenT    DifGen;
  GlobalT    Glb;

// параметры  звеньев по умолчанию
  SinT    Sin;
  PSinT   PSin;
  MeandrT Meandr;
  OneT    One;
  VolumeT Volume;

  ExecT   Compile,
	  Archive,
          Perform;
};


#endif
