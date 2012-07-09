#ifndef SILINK_H
#define SILINK_H
/****************************************
*  Computer Algebra System SINGULAR     *
****************************************/
/* $Id$ */
/*
* ABSTRACT: general interface to links
*/

#include <kernel/structs.h>
#include <Singular/sing_dbm.h>

// extension links:
typedef BOOLEAN    (*slOpenProc)(si_link l, short flag, leftv h);
typedef BOOLEAN    (*slWriteProc)(si_link l, leftv lv);
typedef BOOLEAN    (*slCloseProc)(si_link l);
typedef BOOLEAN    (*slKillProc)(si_link l);
typedef leftv      (*slReadProc)(si_link l);
typedef leftv      (*slRead2Proc)(si_link l, leftv a);
typedef BOOLEAN    (*slDumpProc)(si_link l);
typedef BOOLEAN    (*slGetDumpProc)(si_link l);
typedef const char* (*slStatusProc)(si_link l, const char *request);

struct s_si_link_extension
{
  si_link_extension next;
  slOpenProc       Open;
  slCloseProc      Close;
  slKillProc       Kill;
  slReadProc       Read;
  slRead2Proc      Read2;
  slWriteProc      Write;
  slDumpProc       Dump;
  slGetDumpProc    GetDump;
  slStatusProc     Status;
  const char       *type;
};

struct sip_link
{
  si_link_extension m; // methods
  char *mode;
  char *name;          // used for filename and/or further specs
  void *data;          // the link itself
  BITSET flags;        // 0=close open = 1: read = 2: write = 3
  short ref;           // reference counter
};

// flags:
#define SI_LINK_CLOSE   0
#define SI_LINK_OPEN    1
#define SI_LINK_READ    2
#define SI_LINK_WRITE   4

// tests:
#define SI_LINK_CLOSE_P(l)  (!(l)->flags)
#define SI_LINK_OPEN_P(l)   ((l)->flags & SI_LINK_OPEN)
#define SI_LINK_W_OPEN_P(l) ((l)->flags &  SI_LINK_WRITE)
#define SI_LINK_R_OPEN_P(l) ((l)->flags &  SI_LINK_READ)
#define SI_LINK_RW_OPEN_P(l) (SI_LINK_W_OPEN_P(l) && SI_LINK_R_OPEN_P(l))

#define SI_LINK_SET_CLOSE_P(l)  ((l)->flags = SI_LINK_CLOSE)
#define SI_LINK_SET_OPEN_P(l, flag)   ((l)->flags |= SI_LINK_OPEN |flag)
#define SI_LINK_SET_W_OPEN_P(l) ((l)->flags |= (SI_LINK_OPEN | SI_LINK_WRITE))
#define SI_LINK_SET_R_OPEN_P(l) ((l)->flags |= (SI_LINK_OPEN | SI_LINK_READ))
#define SI_LINK_SET_RW_OPEN_P(l) ((l)->flags |= (SI_LINK_OPEN | SI_LINK_READ | SI_LINK_WRITE))

BOOLEAN slOpen(si_link l, short flag, leftv h);
BOOLEAN slClose(si_link l);
leftv   slRead(si_link l,leftv a=NULL);
BOOLEAN slWrite(si_link l, leftv v);
BOOLEAN slDump(si_link l);
BOOLEAN slGetDump(si_link l);
const char* slStatus(si_link l, const char *request);
const char* slStatusAscii(si_link l,const  char* request);
BOOLEAN slInit(si_link l, char *str);
void slKill(si_link l);
void slCleanUp(si_link l);
void slStandardInit();
inline si_link slCopy(si_link l)
{
  l->ref++;
  return l;
}

#include <omalloc/omalloc.h>
inline char* slString(si_link l)
{
  if (l->name != NULL)
  {
    return omStrDup(l->name);
  }
  else
  {
    return omStrDup("");
  }
}

extern omBin s_si_link_extension_bin;
extern omBin sip_link_bin;
extern omBin ip_link_bin;

int slStatusSsiL(lists L, int timeout);

typedef struct
{
  leftv u;
  si_link l;
  void * next;
} link_struct;

typedef link_struct* link_list;

extern link_list ssiToBeClosed;
extern BOOLEAN ssiToBeClosed_inactive;
#endif // SILINK_H
