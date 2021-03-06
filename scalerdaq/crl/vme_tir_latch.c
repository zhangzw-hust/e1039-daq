#define ROL_NAME__ "VME1"
#define MAX_EVENT_LENGTH 1024
#define MAX_EVENT_POOL   500
#define VME
#define TRIG_SUPV
#define INIT_NAME vme_tir_latch__init
#include <rol.h>
#include <VME_source.h>
#define TIR_ADDR 0x0ed0
#define LATCH_ADDR 0x09000000
struct vme_ts2 *tsP;
extern int bigendian_out;
static void __download()
{
    daLogMsg("INFO","Readout list compiled %s", DAYTIME);
#ifdef POLLING___
   rol->poll = 1;
#endif
    *(rol->async_roc) = 0; /* Normal ROC */
  {  /* begin user */
unsigned long res;
  bigendian_out = 0;
  tirInit(TIR_ADDR);
  latchInit(0x09000000,0x100000,1);
    daLogMsg("INFO","User Download TIR Executed");

  }  /* end user */
} /*end download */     

static void __prestart()
{
CTRIGINIT;
    *(rol->nevents) = 0;
  {  /* begin user */
    daLogMsg("INFO","User Prestart TIR Executed");

    daLogMsg("INFO","Entering User Trigger Prestart");

    VME_INIT;
    CTRIGRSA(VME,1,usrtrig,usrtrig_done);
    CRTTYPE(1,VME,1);
  latchReset(0);
  latchTrigDisable(0);
  latchFifoClear(0);
  latchTrigEnable(0);
    daLogMsg("INFO","Ending TIR Prestart");

    daLogMsg("INFO","Prestart  1");

  latchStatus(0);
  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
    *(rol->nevents) = 0;
    rol->recNb = 0;
} /*end prestart */     

static void __end()
{
  {  /* begin user */
unsigned long trig_count;
  latchTrigDisable(0);
    daLogMsg("INFO","User End Executed VME TIR");

  CDODISABLE(VME,1,0);
  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
} /* end end block */

static void __pause()
{
  {  /* begin user */
    daLogMsg("INFO","User Pause Executed");

  CDODISABLE(VME,1,0);
  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
} /*end pause */
static void __go()
{

  {  /* begin user */
  CDOENABLE(VME,1,0);
    daLogMsg("INFO","Entering User Go");

  latchFifoClear(0);
  latchReset(0);
  latchTrigEnable(0);
    daLogMsg("INFO","Finish User Go");

  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
}

void usrtrig(unsigned long EVTYPE,unsigned long EVSOURCE)
{
    long EVENT_LENGTH;
  {  /* begin user */
unsigned long ii, event_ty, event_no;
 event_ty = EVTYPE;
 event_no = *rol->nevents;
  latchTrigDisable(0);
 rol->dabufp = (long *) 0;
    CEOPEN(EVTYPE, BT_UI4);
 latchFifoStatus(0,3);
  *rol->dabufp++ = latchd[0]->data[0];
  *rol->dabufp++ = latchd[0]->data[0];
    CECLOSE;
  }  /* end user */
} /*end trigger */

void usrtrig_done()
{
  {  /* begin user */
  latchFifoClear(0);
  latchTrigEnable(0);
  }  /* end user */
} /*end done */

void __done()
{
poolEmpty = 0; /* global Done, Buffers have been freed */
  {  /* begin user */
  CDOACK(VME,1,0);
  latchFifoClear(0);
  }  /* end user */
} /*end done */

static void __status()
{
  {  /* begin user */
  }  /* end user */
} /* end status */

