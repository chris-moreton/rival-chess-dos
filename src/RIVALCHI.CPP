/* RIVALCHI.CPP */

#include <assert.h>
#include <stdlib.h>
#include "rivaldef.h"

extern mvtype best_at[32];
extern optiontype options;

int values[115]=
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
55,0,0,0,0,0,0,0,0,0,0,0,54,0,65,25,45,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
55,0,0,0,0,0,0,0,0,0,0,0,54,0,65,25,45
};

int values2[115]=
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,0,0,0,0,0,0,0,0,1,0,0,3,0,2,9,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,0,0,0,0,0,0,0,0,1,0,0,3,0,2,9,5
};

extern char centrality[100];
mvtype mv;
struct postype globpos;
struct movelist allmoves;
char i,j;

char check(struct postype *pos, SQUARE kng)
{
  // look for check on square 'kng' making exceptions for queen and bishop
  // when playing SHATRANJ
  char d0,d1,d2,d3;
  SQUARE usesquare=kng;
  do usesquare++; while (pos->brd[usesquare]=='-'); d0=pos->brd[usesquare];
  usesquare=kng; do usesquare+=10; while (pos->brd[usesquare]=='-'); d1=pos->brd[usesquare];
  usesquare=kng; do usesquare--; while (pos->brd[usesquare]=='-'); d2=pos->brd[usesquare];
  usesquare=kng; do usesquare-=10; while (pos->brd[usesquare]=='-'); d3=pos->brd[usesquare];
  if (pos->brd[kng]<'Z')
  {
	if (d0=='r' || d1=='r' || d2=='r' || d3=='r') return(TRUE);
	if (options.game==SHATRANJ)
	{
	  if (kng-22>10) d0=pos->brd[kng-22]; else d0='-';
	  if (kng-18>10) d1=pos->brd[kng-18]; else d1='-';
	  if (kng+18<89) d2=pos->brd[kng+18]; else d2='-';
	  if (kng+22<89) d3=pos->brd[kng+22]; else d3='-';
	  if (d0=='b' || d1=='b' || d2=='b' || d3=='b') return(TRUE);
	  d0=pos->brd[kng-11];
	  d1=pos->brd[kng-9];
	  d2=pos->brd[kng+11];
	  d3=pos->brd[kng+9];
	  if (d0=='q' || d1=='q' || d2=='q' || d3=='q') return(TRUE);
	} else
	{
	   if (d0=='q' || d1=='q' || d2=='q' || d3=='q') return(TRUE);
	   usesquare=kng; while (pos->brd[usesquare=usesquare-11]=='-'); d0=pos->brd[usesquare];
	   usesquare=kng; while (pos->brd[usesquare=usesquare+9]=='-'); d1=pos->brd[usesquare];
	   usesquare=kng; while (pos->brd[usesquare=usesquare+11]=='-'); d2=pos->brd[usesquare];
	   usesquare=kng; while (pos->brd[usesquare=usesquare-9]=='-'); d3=pos->brd[usesquare];
	   if (d0=='q' || d1=='q' || d2=='q' || d3=='q') return(TRUE);
	   if (d0=='b' || d1=='b' || d2=='b' || d3=='b') return(TRUE);
	}
	return(
			 pos->brd[kng+11]=='p' ||
			 pos->brd[kng-9]=='p' ||
			 (kng<77 && pos->brd[kng+12]=='n') ||
			 (kng<68 && pos->brd[kng+21]=='n') ||
			 (kng>22 && pos->brd[kng-12]=='n') ||
			 (kng>31 && pos->brd[kng-21]=='n') ||
			 (kng>29 && pos->brd[kng-19]=='n') ||
			 pos->brd[kng+8]=='n' ||
			 pos->brd[kng-8]=='n' ||
			 (kng<70 && pos->brd[kng+19]=='n') ||
			 pos->brd[kng+10]=='k' ||
			 pos->brd[kng-10]=='k' ||
			 pos->brd[kng+9]=='k' ||
			 pos->brd[kng-11]=='k' ||
			 pos->brd[kng+11]=='k' ||
			 pos->brd[kng-9]=='k' ||
			 pos->brd[kng+1]=='k' ||
			 pos->brd[kng-1]=='k');
  } else
  {
	if (d0=='R' || d1=='R' || d2=='R' || d3=='R') return(TRUE);
	if (options.game==SHATRANJ)
	{
	  if (kng-22>10) d0=pos->brd[kng-22]; else d0='-';
	  if (kng-18>10) d1=pos->brd[kng-18]; else d1='-';
	  if (kng+18<89) d2=pos->brd[kng+18]; else d2='-';
	  if (kng+22<89) d3=pos->brd[kng+22]; else d3='-';
	  if (d0=='B' || d1=='B' || d2=='B' || d3=='B') return(TRUE);
	  d0=pos->brd[kng-11];
	  d1=pos->brd[kng-9];
	  d2=pos->brd[kng+11];
	  d3=pos->brd[kng+9];
	  if (d0=='Q' || d1=='Q' || d2=='Q' || d3=='Q') return(TRUE);
	} else
	{
	   if (d0=='Q' || d1=='Q' || d2=='Q' || d3=='Q') return(TRUE);
	   usesquare=kng; while (pos->brd[usesquare=usesquare-11]=='-'); d0=pos->brd[usesquare];
	   usesquare=kng;	while (pos->brd[usesquare=usesquare+9]=='-'); d1=pos->brd[usesquare];
	   usesquare=kng;	while (pos->brd[usesquare=usesquare+11]=='-'); d2=pos->brd[usesquare];
	   usesquare=kng;	while (pos->brd[usesquare=usesquare-9]=='-'); d3=pos->brd[usesquare];
	   if (d0=='Q' || d1=='Q' || d2=='Q' || d3=='Q') return(TRUE);
	   if (d0=='B' || d1=='B' || d2=='B' || d3=='B') return(TRUE);
	}
	return (
		 pos->brd[kng+9]=='P' ||
		 pos->brd[kng-11]=='P' ||
		 (kng<77 && pos->brd[kng+12]=='N') ||
		 (kng<68 && pos->brd[kng+21]=='N') ||
		 (kng>22 && pos->brd[kng-12]=='N') ||
		 (kng>31 && pos->brd[kng-21]=='N') ||
		 (kng>29 && pos->brd[kng-19]=='N') ||
		 pos->brd[kng+8]=='N' ||
		 pos->brd[kng-8]=='N' ||
		 (kng<70 && pos->brd[kng+19]=='N') ||
		 pos->brd[kng+10]=='K' ||
		 pos->brd[kng-10]=='K' ||
		 pos->brd[kng+9]=='K' ||
		 pos->brd[kng-11]=='K' ||
		 pos->brd[kng+11]=='K' ||
		 pos->brd[kng-9]=='K' ||
		 pos->brd[kng+1]=='K' ||
		 pos->brd[kng-1]=='K' );
  }
}

#define QADD qadd()

void qadd(void)
{
  allmoves.amount++;
  mv.lastwin=globpos.brd[mv.t];
  allmoves.move[allmoves.amount]=mv;
  allmoves.move[allmoves.amount].score=values[mv.lastwin];
  allmoves.move[allmoves.amount].score+=(values2[globpos.brd[mv.f]]);
}



void reverse(void)
{
   struct movelist temp;
   temp=allmoves;
   for (i=1; i<=allmoves.amount; i++)
   {
     temp.move[i]=allmoves.move[allmoves.amount-(i-1)];
   }
   allmoves=temp;
}

void _near quicksort(int left, int right)
{
	register int test = allmoves.move[(left+right)/2].score;
	int i=left;
	int j=right;
	mvtype swap;
	do
	{
	  while (allmoves.move[i].score<test) i++;
	  while (test<allmoves.move[j].score) j--;
	  if (i<=j)
	  {
		  swap=allmoves.move[i];
		  allmoves.move[i++]=allmoves.move[j];
		  allmoves.move[j--]=swap;
	  }
	} while (i<=j);
	if (left<j) quicksort(left, j);
	if (i<right) quicksort(i, right);
}

void _near change_loc(struct postype *pos, SQUARE from, SQUARE to)
{
  int i=-1;
  if (pos->brd[from]>'a')
  switch(pos->brd[from])
  {
		case 'p' :
again1: 	if (pos->bpawn[++i]==from)	{ pos->bpawn[i]=to; return; } goto again1;
		case 'n' :
again3:		if (pos->bknight[++i]==from)		{ pos->bknight[i]=to; return;	}goto again3;
		case 'q' :
again5:		if (pos->bqueen[++i]==from)		{ pos->bqueen[i]=to;	return; }goto again5;
		case 'b' :
again7:		if (pos->bbish[++i]==from)		{ pos->bbish[i]=to; return; }goto again7;
		case 'r' :
again9:		if (pos->brook[++i]==from)		{ pos->brook[i]=to; return; }goto again9;
		case 'k' :
again11:	if (pos->bking[++i]==from)		{ pos->bking[i]=to; return; }goto again11;
  }
  switch (pos->brd[from])
  {
		case 'P' :
again2: if (pos->wpawn[++i]==from){ pos->wpawn[i]=to; return; }goto again2;
		case 'N' :
again4:		if (pos->wknight[++i]==from)		{ pos->wknight[i]=to; return;	}goto again4;
		case 'Q' :
again6:		if (pos->wqueen[++i]==from)		{ pos->wqueen[i]=to;	return; }goto again6;
		case 'B' :
again8:		if (pos->wbish[++i]==from)		{ pos->wbish[i]=to; return; }goto again8;
		case 'R' :
again10:		if (pos->wrook[++i]==from)		{ pos->wrook[i]=to; return; }goto again10;
		case 'K' :
again12:		if (pos->wking[++i]==from)		{ pos->wking[i]=to; return; }goto again10;
//		case 'k' : pos->blackking=to; break;
//		case 'K' : pos->whiteking=to;
	}
}

void _near kill_loc(struct postype *pos, SQUARE loc)
{
  /* swap with last in array, decrement piece count */
  int i=-1;
  if (pos->brd[loc]>'a')
  switch(pos->brd[loc])
  {
		case 'p' : pos->total_bmat-=100;
again1:	if (pos->bpawn[++i]==loc) { pos->bpawn[i]=pos->bpawn[pos->bpawncount--]; return; } goto again1;
		case 'n' : pos->total_bmat-=320;
again3: if (pos->bknight[++i]==loc)	{ pos->bknight[i]=pos->bknight[pos->bknightcount--]; return;	} goto again3;
		case 'q' : pos->total_bmat-=900;
again5: if (pos->bqueen[++i]==loc) { pos->bqueen[i]=pos->bqueen[pos->bqueencount--];	return; } goto again5;
		case 'b' : pos->total_bmat-=325;
again7: if (pos->bbish[++i]==loc) { pos->bbish[i]=pos->bbish[pos->bbishcount--]; return; } goto again7;
		case 'r' : pos->total_bmat-=500;
again9: if (pos->brook[++i]==loc) { pos->brook[i]=pos->brook[pos->brookcount--]; return; } goto again9;
		case 'k' : pos->total_bmat-=300;
again11: if (pos->bking[++i]==loc) { pos->bking[i]=pos->bking[pos->bkingcount--]; return; } goto again11;
  } // switch
  switch(pos->brd[loc])
  {
		case 'P' : pos->total_wmat-=100;
again2: if (pos->wpawn[++i]==loc) { pos->wpawn[i]=pos->wpawn[pos->wpawncount--]; return; } goto again2;
		case 'N' : pos->total_wmat-=320;
again4: if (pos->wknight[++i]==loc)	{ pos->wknight[i]=pos->wknight[pos->wknightcount--]; return;	} goto again4;
		case 'Q' : pos->total_wmat-=900;
again6: if (pos->wqueen[++i]==loc) { pos->wqueen[i]=pos->wqueen[pos->wqueencount--];	return; } goto again6;
		case 'B' : pos->total_wmat-=325;
again8: if (pos->wbish[++i]==loc) { pos->wbish[i]=pos->wbish[pos->wbishcount--]; return; } goto again8;
		case 'R' : pos->total_wmat-=500;
again10: if (pos->wrook[++i]==loc) { pos->wrook[i]=pos->wrook[pos->wrookcount--]; return; } goto again10;
		case 'K' : pos->total_wmat-=300;
again12: if (pos->wking[++i]==loc) { pos->wking[i]=pos->wking[pos->wkingcount--]; return; } goto again12;
	} // switch
}

void alter(struct postype *pos, mvtype mv, struct postype *newpos)
{
  char pxf=mv.f/10;
  char pyf=mv.f%10;
  char pxt=mv.t/10;
  char pyt=mv.t%10;
  *newpos=*pos;
  newpos->mvr=(pos->mvr=='w') ? 'b' : 'w';
  switch (mv.f)
  {
	  case 58 : newpos->bking_moved=TRUE; break;
	  case 51 : newpos->wking_moved=TRUE; break;
	  case 11 : newpos->wrook1_moved=TRUE; break;
	  case 18 : newpos->brook1_moved=TRUE; break;
	  case 88 : newpos->brook2_moved=TRUE; break;
	  case 81 : newpos->wrook2_moved=TRUE;
  }
  if (pyf==7 && pyt==5 && pos->brd[mv.f]=='p') newpos->en_pawn=pxf; else
	  if (pyf==2 && pyt==4 && pos->brd[mv.f]=='P' ) newpos->en_pawn=pxf; else
	newpos->en_pawn=99;
  switch (pos->brd[mv.t])
  {
	  case '-' : break;
	  case 'R' : newpos->wmat=newpos->wmat-5; break;
	  case 'B' : newpos->wmat=newpos->wmat-3; break;
	  case 'N' : newpos->wmat=newpos->wmat-3; break;
	  case 'r' : newpos->bmat=newpos->bmat-5; break;
	  case 'b' : newpos->bmat=newpos->bmat-3; break;
	  case 'n' : newpos->bmat=newpos->bmat-3;
  }
  if (mv.f==58 && pos->brd[58]=='k')
  {
		if (mv.t==38)
		{
	 change_loc(newpos,58,38);
	 change_loc(newpos,18,48);
	 newpos->bking[0]=38;
	 newpos->brd[58]='-';
	 newpos->brd[38]='k';
	 newpos->brd[48]='r';
	 newpos->brd[18]='-';
	 newpos->black_castled=TRUE;
	 return;
		} else
		if (mv.t==78)
		{
	 change_loc(newpos,58,78);
	 change_loc(newpos,88,68);
	 newpos->bking[0]=78;
	 newpos->brd[58]='-';
	 newpos->brd[78]='k';
	 newpos->brd[68]='r';
	 newpos->brd[88]='-';
	 newpos->black_castled=TRUE;
	 return;
		}
  }
  if (mv.f==51 && pos->brd[51]=='K')
  {
		if (mv.t==71)
		{
	 change_loc(newpos,51,71);
	 change_loc(newpos,81,61);
	 newpos->wking[0]=71;
	 newpos->brd[51]='-';
	 newpos->brd[71]='K';
	 newpos->brd[61]='R';
	 newpos->brd[81]='-';
	 newpos->white_castled=TRUE;
	 return;
		} else
		if (mv.t==31)
		{
	 change_loc(newpos,51,31);
	 change_loc(newpos,11,41);
	 newpos->wking[0]=31;
	 newpos->brd[51]='-';
	 newpos->brd[31]='K';
	 newpos->brd[41]='R';
	 newpos->brd[11]='-';
	 newpos->white_castled=TRUE;
	 return;
		}
  }
  /* the next two if statements deal with en passant moves when made */
  if (pos->brd[mv.f]=='p' && pxf!=pxt && pos->brd[mv.t]=='-')
  {
	 kill_loc(newpos,mv.t+1);
	 newpos->brd[mv.t+1]='-';
  }
  if (pos->brd[mv.f]=='P' && pxf!=pxt && pos->brd[mv.t]=='-')
  {
	 kill_loc(newpos,mv.t-1);
	 newpos->brd[mv.t-1]='-';
  }
  if (newpos->brd[mv.t]!='-') kill_loc(newpos,mv.t);
  change_loc(newpos,mv.f,mv.t);
  newpos->brd[mv.t]=pos->brd[mv.f];
  newpos->brd[mv.f]='-';
  if (pyt==8 && newpos->brd[mv.t]=='P')
  {
	  kill_loc(newpos, mv.t);
	  if (options.game==KINGLET)
	  {
	     newpos->brd[mv.t]='K';
	     newpos->wking[++newpos->wkingcount]=mv.t;
	     newpos->total_wmat=newpos->total_wmat+300;
	  } else
	  {
	     newpos->brd[mv.t]='Q';
	     newpos->wqueen[++newpos->wqueencount]=mv.t;
	     newpos->total_wmat=newpos->total_wmat+800;
	  }
  }
  if (pyt==1 && newpos->brd[mv.t]=='p')
  {
	  kill_loc(newpos, mv.t);
	  if (options.game==KINGLET)
	  {
	     newpos->bking[++newpos->bkingcount]=mv.t;
	     newpos->brd[mv.t]='k';
	     newpos->total_bmat=newpos->total_bmat+300;
	  } else
	  {
	     newpos->bqueen[++newpos->bqueencount]=mv.t;
	     newpos->brd[mv.t]='q';
	     newpos->total_bmat=newpos->total_bmat+800;
	  }
  }
//  if (newpos->brd[mv.t]=='k') newpos->bking[0]=mv.t;
//  if (newpos->brd[mv.t]=='K') newpos->wking[0]=mv.t;
}


#define ADD add()

void add(void)
{
  int ii;

  allmoves.amount++;
  mv.lastwin=globpos.brd[mv.t];
  allmoves.move[allmoves.amount]=mv;
  allmoves.move[allmoves.amount].score=values[mv.lastwin];
  allmoves.move[allmoves.amount].score+=(values2[globpos.brd[mv.f]]);

//  if (mv.f==best_at[0].f && mv.t==best_at[0].t) allmoves.move[allmoves.amount].score=0;
  for (ii=0; best_at[ii].f!=0; ii++)
	  if (mv.f==best_at[ii].f && mv.t==best_at[ii].t)
	  {
			allmoves.move[allmoves.amount].score=ii;
			break;
	  }
}

struct movelist get_children(struct postype *pos)
{
 register int i, ii;
 char t1, t2;
 allmoves.amount=0;
 globpos=*pos;
 if (globpos.mvr=='b')

 {
	for (i=0; i<=pos->bpawncount; i++)
	{
		mv.f=pos->bpawn[i];
		if (globpos.brd[mv.f-1]=='-')
		{
		     mv.t=mv.f-1;
		     ADD;
		     if (options.game!=SHATRANJ && mv.f%10==7 && globpos.brd[mv.f-2]=='-')
		     {
			mv.t=mv.f-2;
			ADD;
		     }
		}
		if (globpos.brd[mv.f+9]>'A' && pos->brd[mv.f+9]<'Z') {mv.t=mv.f+9; ADD;}
		if (globpos.brd[mv.f-11]>'A' && pos->brd[mv.f-11]<'Z') {mv.t=mv.f-11; ADD;}
		t1=mv.f/10; t2=mv.f%10;
		if (t1==globpos.en_pawn+1 && t2==4) {mv.t=mv.f-11; ADD;}
		if (t1==globpos.en_pawn-1 && t2==4) {mv.t=mv.f+9; ADD;}
	}
	for (i=0; i<=pos->brookcount; i++)
	{
		mv.f=pos->brook[i];
		for (mv.t=mv.f; globpos.brd[++mv.t]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
		for (mv.t=mv.f; globpos.brd[--mv.t]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
	}
	for (i=0; i<=pos->bbishcount; i++)
	{
		mv.f=pos->bbish[i];
		if (options.game==SHATRANJ)
		{
		   if (mv.f+18<89 && globpos.brd[mv.t=mv.f+18]<'Z') ADD;
		   if (mv.f+22<89 && globpos.brd[mv.t=mv.f+22]<'Z') ADD;
		   if (mv.f-18>10 && globpos.brd[mv.t=mv.f-18]<'Z') ADD;
		   if (mv.f-22>10 && globpos.brd[mv.t=mv.f-22]<'Z') ADD;
		} else
		{
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';) ADD;
		if (globpos.brd[mv.t]<'Z') ADD;
		}
	}
	for (i=0; i<=pos->bknightcount; i++)
	{
		mv.f=pos->bknight[i];
		if ((mv.t=mv.f+12)<89 && (globpos.brd[mv.t]<'Z')) ADD;
		if ((mv.t=mv.f-12)<89 && (globpos.brd[mv.t]<'Z')) ADD;
		if ((mv.t=mv.f+21)<89 && (globpos.brd[mv.t]<'Z')) ADD;
		if ((mv.t=mv.f-21)<89 && (globpos.brd[mv.t]<'Z')) ADD;
		if ((mv.t=mv.f+19)<89 && (globpos.brd[mv.t]<'Z')) ADD;
		if ((mv.t=mv.f-19)<89 && (globpos.brd[mv.t]<'Z')) ADD;
		if (globpos.brd[mv.t=mv.f+8]<'Z') ADD;
		if ((mv.t=mv.f-8)<89 && (globpos.brd[mv.t]<'Z')) ADD;
	}
	for (i=0; i<=pos->bkingcount; i++)
	{
		mv.f=pos->bking[i];
		if (globpos.brd[mv.t=mv.f+10]<'Z') ADD;
		if (globpos.brd[mv.t=mv.f+9]<'Z') ADD;
		if (globpos.brd[mv.t=mv.f+11]<'Z') ADD;
		if (globpos.brd[mv.t=mv.f-10]<'Z') ADD;
		if (globpos.brd[mv.t=mv.f-9]<'Z') ADD;
		if (globpos.brd[mv.t=mv.f-11]<'Z') ADD;
		if (globpos.brd[mv.t=mv.f+1]<'Z') ADD;
		if (globpos.brd[mv.t=mv.f-1]<'Z') ADD;
		if (options.game!=SHATRANJ)
		{
		   if (!globpos.brook2_moved && globpos.bking_moved==FALSE && mv.f==58 && globpos.brd[68]=='-' && globpos.brd[mv.t=78]=='-' && globpos.brd[88]=='r') ADD;
		   if (!globpos.brook1_moved && globpos.bking_moved==FALSE && mv.f==58 && globpos.brd[48]=='-' && globpos.brd[mv.t=38]=='-' && globpos.brd[28]=='-' && globpos.brd[18]=='r') ADD;
		}
	}
	for (i=0; i<=pos->bqueencount; i++)
	{
		mv.f=pos->bqueen[i];
		if (options.game==SHATRANJ)
		{
		   if (globpos.brd[mv.t=mv.f+9]<'Z') ADD;
		   if (globpos.brd[mv.t=mv.f+11]<'Z') ADD;
		   if (globpos.brd[mv.t=mv.f-9]<'Z') ADD;
		   if (globpos.brd[mv.t=mv.f-11]<'Z') ADD;
		} else
		{
		   for (mv.t=mv.f; globpos.brd[++mv.t]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		   for (mv.t=mv.f; globpos.brd[--mv.t]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';) ADD;
		   if (globpos.brd[mv.t]<'Z') ADD;
		}
	}
 } else
 {
	for (i=0; i<=pos->wpawncount; i++)
	{
		mv.f=pos->wpawn[i];
		if (globpos.brd[mv.f+1]=='-')
		{
		    mv.t=mv.f+1;
		    ADD;
		    if (options.game!=SHATRANJ && mv.f%10==2 && globpos.brd[mv.f+2]=='-')
		    {
		       mv.t=mv.f+2;
		       ADD;
		    }
		}
		if (globpos.brd[mv.f+11]>'a' && pos->brd[mv.f+11]<'z') {mv.t=mv.f+11; ADD;}
		if (globpos.brd[mv.f-9]>'a' && pos->brd[mv.f-9]<'z') {mv.t=mv.f-9; ADD;}
		t1=mv.f/10; t2=mv.f%10;
		if (t1==globpos.en_pawn+1 && t2==5) {mv.t=mv.f-9; ADD;}
		if (t1==globpos.en_pawn-1 && t2==5) {mv.t=mv.f+11; ADD;}
	}
	for (i=0; i<=pos->wrookcount; i++)
	{
		mv.f=pos->wrook[i];
		for (mv.t=mv.f; globpos.brd[++mv.t]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
		for (mv.t=mv.f; globpos.brd[--mv.t]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
	}
	for (i=0; i<=pos->wbishcount; i++)
	{
		mv.f=pos->wbish[i];
		if (options.game==SHATRANJ)
		{
		   if (mv.f+18<89 && (globpos.brd[mv.t=mv.f+18]>'a' || globpos.brd[mv.t]=='-')) ADD;
		   if (mv.f+22<89 && (globpos.brd[mv.t=mv.f+22]>'a' || globpos.brd[mv.t]=='-')) ADD;
		   if (mv.f-22>10 && (globpos.brd[mv.t=mv.f-22]>'a' || globpos.brd[mv.t]=='-')) ADD;
		   if (mv.f-18>10 && (globpos.brd[mv.t=mv.f-18]>'a' || globpos.brd[mv.t]=='-')) ADD;
		} else
		{
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';) ADD;
		if (globpos.brd[mv.t]>'a') ADD;
		}
	}
	for (i=0; i<=pos->wknightcount; i++)
	{
		mv.f=pos->wknight[i];
		if ((mv.t=mv.f+12)<89 && (globpos.brd[mv.t]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((mv.t=mv.f-12)<89 && (globpos.brd[mv.t]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((mv.t=mv.f+21)<89 && (globpos.brd[mv.t]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((mv.t=mv.f-21)<89 && (globpos.brd[mv.t]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((mv.t=mv.f+19)<89 && (globpos.brd[mv.t]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((mv.t=mv.f-19)<89 && (globpos.brd[mv.t]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if (globpos.brd[mv.t=mv.f+8]>'a' || globpos.brd[mv.t]=='-') ADD;
		if ((mv.t=mv.f-8)<89 && (globpos.brd[mv.t]>'a' || globpos.brd[mv.t]=='-')) ADD;
	}
	for (i=0; i<=pos->wkingcount; i++)
	{
		mv.f=pos->wking[i];
		if ((globpos.brd[mv.t=mv.f+10]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((globpos.brd[mv.t=mv.f+9]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((globpos.brd[mv.t=mv.f+11]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((globpos.brd[mv.t=mv.f-10]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((globpos.brd[mv.t=mv.f-11]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((globpos.brd[mv.t=mv.f-9]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((globpos.brd[mv.t=mv.f-1]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if ((globpos.brd[mv.t=mv.f+1]>'a' || globpos.brd[mv.t]=='-')) ADD;
		if (options.game!=SHATRANJ)
		{
		   if (globpos.wrook2_moved==FALSE && globpos.wking_moved==FALSE && mv.f==51 && globpos.brd[61]=='-' && globpos.brd[mv.t=71]=='-' && globpos.brd[81]=='R') ADD;
		   if (globpos.wrook1_moved==FALSE && globpos.wking_moved==FALSE && mv.f==51 && globpos.brd[41]=='-' && globpos.brd[mv.t=31]=='-' && globpos.brd[21]=='-' && globpos.brd[11]=='R') ADD;
		}
	}
	for (i=0; i<=pos->wqueencount; i++)
	{
		mv.f=pos->wqueen[i];
		if (options.game==SHATRANJ)
		{
		   if ((globpos.brd[mv.t=mv.f+9]>'a' || globpos.brd[mv.t]=='-')) ADD;
		   if ((globpos.brd[mv.t=mv.f+11]>'a' || globpos.brd[mv.t]=='-')) ADD;
		   if ((globpos.brd[mv.t=mv.f-11]>'a' || globpos.brd[mv.t]=='-')) ADD;
		   if ((globpos.brd[mv.t=mv.f-9]>'a' || globpos.brd[mv.t]=='-')) ADD;
		} else
		{
		   for (mv.t=mv.f; globpos.brd[++mv.t]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		   for (mv.t=mv.f; globpos.brd[--mv.t]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';) ADD;
		   if (globpos.brd[mv.t]>'a') ADD;
		}
	}
 }
 assert(allmoves.amount<maxmovelist);
	if (allmoves.amount>1)
	{
	  quicksort(1, allmoves.amount);
	  if (options.game==GIVEAWAY) reverse();
	}

 return(allmoves);
}

struct movelist q_get_children(struct postype *pos)
{
 register int i;
 char t1, t2;
 allmoves.amount=0;
 globpos=*pos;
 if (globpos.mvr=='b')
 {
	for (i=0; i<=pos->bpawncount; i++)
	{
		mv.f=pos->bpawn[i];
		if (globpos.brd[mv.f-1]=='-')
		{
		    if (mv.f%10<4)
		    {
		       mv.t=mv.f-1;
		       QADD;
		    }
		 }
		 if (globpos.brd[mv.f+9]>'A' && pos->brd[mv.f+9]<'Z') {mv.t=mv.f+9; QADD;}
		 if (globpos.brd[mv.f-11]>'A' && pos->brd[mv.f-11]<'Z') {mv.t=mv.f-11; QADD;}
		 t1=mv.f/10; t2=mv.f%10;
		 if (t1==globpos.en_pawn+1 && t2==4) {mv.t=mv.f-11; QADD;}
		 if (t1==globpos.en_pawn-1 && t2==4) {mv.t=mv.f+9; QADD;}
	}
	for (i=0; i<=pos->brookcount; i++)
	{
		mv.f=pos->brook[i];
		for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
	}
	for (i=0; i<=pos->bbishcount; i++)
	{
		mv.f=pos->bbish[i];
		if (options.game==SHATRANJ)
		{
		   if (mv.f+18<89 && globpos.brd[mv.t=mv.f+18]<'Z') QADD;
		   if (mv.f+22<89 && globpos.brd[mv.t=mv.f+22]<'Z') QADD;
		   if (mv.f-18>10 && globpos.brd[mv.t=mv.f-18]<'Z') QADD;
		   if (mv.f-22>10 && globpos.brd[mv.t=mv.f-22]<'Z') QADD;
		} else
		{
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		}
	}
	for (i=0; i<=pos->bknightcount; i++)
	{
		mv.f=pos->bknight[i];
		if ((mv.t=mv.f+12)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f-12)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f+21)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f-21)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f+19)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f-19)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if (globpos.brd[mv.t=mv.f+8]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if ((mv.t=mv.f-8)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
	}
	for (i=0; i<=pos->bkingcount; i++)
	{
		mv.f=pos->bking[i];
		if (globpos.brd[mv.t=mv.f+10]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f+9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f+11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-10]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-1]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f+1]>'A' && globpos.brd[mv.t]<'Z') QADD;
	}
	for (i=0; i<=pos->bqueencount; i++)
	{
		mv.f=pos->bqueen[i];
		if (options.game==SHATRANJ)
		{
		   if (globpos.brd[mv.t=mv.f+9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		   if (globpos.brd[mv.t=mv.f+11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		   if (globpos.brd[mv.t=mv.f-11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		   if (globpos.brd[mv.t=mv.f-9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		} else
		{
		   for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		}
	}
 } else
 {
	for (i=0; i<=pos->wpawncount; i++)
	{
		mv.f=pos->wpawn[i];
		if (globpos.brd[mv.f+1]=='-')
		{
		    if (mv.f%10>5)
		    {
			mv.t=mv.f+1;
			QADD;
		    }
		}
		if (globpos.brd[mv.f+11]>'a' && pos->brd[mv.f+11]<'z') {mv.t=mv.f+11; QADD;}
		if (globpos.brd[mv.f-9]>'a' && pos->brd[mv.f-9]<'z') {mv.t=mv.f-9; QADD;}
		t1=mv.f/10; t2=mv.f%10;
		if (t1==globpos.en_pawn+1 && t2==5) {mv.t=mv.f-9; QADD;}
		if (t1==globpos.en_pawn-1 && t2==5) {mv.t=mv.f+11; QADD;}
	}
	for (i=0; i<=pos->wrookcount; i++)
	{
		mv.f=pos->wrook[i];
		for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
	}
	for (i=0; i<=pos->wbishcount; i++)
	{
		mv.f=pos->wbish[i];
		if (options.game==SHATRANJ)
		{
		   if (mv.f+18<89 && (globpos.brd[mv.t=mv.f+18]>'a' || globpos.brd[mv.t]=='-')) QADD;
		   if (mv.f+22<89 && (globpos.brd[mv.t=mv.f+22]>'a' || globpos.brd[mv.t]=='-')) QADD;
		   if (mv.f-22>10 && (globpos.brd[mv.t=mv.f-22]>'a' || globpos.brd[mv.t]=='-')) QADD;
		   if (mv.f-18>10 && (globpos.brd[mv.t=mv.f-18]>'a' || globpos.brd[mv.t]=='-')) QADD;
		} else
		{
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		}
	}
	for (i=0; i<=pos->wknightcount; i++)
	{
		mv.f=pos->wknight[i];
		if ((mv.t=mv.f+12)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f-12)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f+21)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f-21)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f+19)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f-19)<89 && globpos.brd[mv.t]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+8]>'a') QADD;
		if ((mv.t=mv.f-8)<89 && globpos.brd[mv.t]>'a') QADD;
	}
	for (i=0; i<=pos->wkingcount; i++)
	{
		mv.f=pos->wking[i];
		if (globpos.brd[mv.t=mv.f+10]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+9]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+11]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-10]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-9]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-11]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+1]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-1]>'a') QADD;
	}
	for (i=0; i<=pos->wqueencount; i++)
	{
		mv.f=pos->wqueen[i];
		if (options.game==SHATRANJ)
		{
		   if (globpos.brd[mv.t=mv.f+9]>'a') QADD;
		   if (globpos.brd[mv.t=mv.f+11]>'a') QADD;
		   if (globpos.brd[mv.t=mv.f-9]>'a') QADD;
		   if (globpos.brd[mv.t=mv.f-11]>'a') QADD;
		} else
		{
		   for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		}
	}
 }
 assert(allmoves.amount<maxmovelist);
 return(allmoves);
}

struct movelist capture_get_children(struct postype *pos)
{
 register int i;
 char t1, t2;
 allmoves.amount=0;
 globpos=*pos;
 if (globpos.mvr=='b')
 {
	for (i=0; i<=pos->bpawncount; i++)
	{
		mv.f=pos->bpawn[i];
		 if (globpos.brd[mv.f+9]>'A' && pos->brd[mv.f+9]<'Z') {mv.t=mv.f+9; QADD;}
		 if (globpos.brd[mv.f-11]>'A' && pos->brd[mv.f-11]<'Z') {mv.t=mv.f-11; QADD;}
		 t1=mv.f/10; t2=mv.f%10;
		 if (t1==globpos.en_pawn+1 && t2==4) {mv.t=mv.f-11; QADD;}
		 if (t1==globpos.en_pawn-1 && t2==4) {mv.t=mv.f+9; QADD;}
	}
	for (i=0; i<=pos->brookcount; i++)
	{
		mv.f=pos->brook[i];
		for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
	}
	for (i=0; i<=pos->bbishcount; i++)
	{
		mv.f=pos->bbish[i];
		if (options.game==SHATRANJ)
		{
		   if (mv.f+18<89 && globpos.brd[mv.t=mv.f+18]<'Z') QADD;
		   if (mv.f+22<89 && globpos.brd[mv.t=mv.f+22]<'Z') QADD;
		   if (mv.f-18>10 && globpos.brd[mv.t=mv.f-18]<'Z') QADD;
		   if (mv.f-22>10 && globpos.brd[mv.t=mv.f-22]<'Z') QADD;
		} else
		{
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		if (globpos.brd[mv.t]<'Z') QADD;
		}
	}
	for (i=0; i<=pos->bknightcount; i++)
	{
		mv.f=pos->bknight[i];
		if ((mv.t=mv.f+12)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f-12)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f+21)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f-21)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f+19)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if ((mv.t=mv.f-19)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
		if (globpos.brd[mv.t=mv.f+8]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if ((mv.t=mv.f-8)<89 && (globpos.brd[mv.t]>'A' && globpos.brd[mv.t]<'Z')) QADD;
	}
	for (i=0; i<=pos->bkingcount; i++)
	{
		mv.f=pos->bking[i];
		if (globpos.brd[mv.t=mv.f+10]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f+9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f+11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-10]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f-1]>'A' && globpos.brd[mv.t]<'Z') QADD;
		if (globpos.brd[mv.t=mv.f+1]>'A' && globpos.brd[mv.t]<'Z') QADD;
	}
	for (i=0; i<=pos->bqueencount; i++)
	{
		mv.f=pos->bqueen[i];
		if (options.game==SHATRANJ)
		{
		   if (globpos.brd[mv.t=mv.f+9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		   if (globpos.brd[mv.t=mv.f+11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		   if (globpos.brd[mv.t=mv.f-11]>'A' && globpos.brd[mv.t]<'Z') QADD;
		   if (globpos.brd[mv.t=mv.f-9]>'A' && globpos.brd[mv.t]<'Z') QADD;
		} else
		{
		   for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		   if (globpos.brd[mv.t]<'Z') QADD;
		}
	}
 } else
 {
	for (i=0; i<=pos->wpawncount; i++)
	{
		mv.f=pos->wpawn[i];
		if (globpos.brd[mv.f+11]>'a' && pos->brd[mv.f+11]<'z') {mv.t=mv.f+11; QADD;}
		if (globpos.brd[mv.f-9]>'a' && pos->brd[mv.f-9]<'z') {mv.t=mv.f-9; QADD;}
		t1=mv.f/10; t2=mv.f%10;
		if (t1==globpos.en_pawn+1 && t2==5) {mv.t=mv.f-9; QADD;}
		if (t1==globpos.en_pawn-1 && t2==5) {mv.t=mv.f+11; QADD;}
	}
	for (i=0; i<=pos->wrookcount; i++)
	{
		mv.f=pos->wrook[i];
		for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
	}
	for (i=0; i<=pos->wbishcount; i++)
	{
		mv.f=pos->wbish[i];
		if (options.game==SHATRANJ)
		{
		   if (mv.f+18<89 && (globpos.brd[mv.t=mv.f+18]>'a' || globpos.brd[mv.t]=='-')) QADD;
		   if (mv.f+22<89 && (globpos.brd[mv.t=mv.f+22]>'a' || globpos.brd[mv.t]=='-')) QADD;
		   if (mv.f-22>10 && (globpos.brd[mv.t=mv.f-22]>'a' || globpos.brd[mv.t]=='-')) QADD;
		   if (mv.f-18>10 && (globpos.brd[mv.t=mv.f-18]>'a' || globpos.brd[mv.t]=='-')) QADD;
		} else
		{
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		if (globpos.brd[mv.t]>'a') QADD;
		}
	}
	for (i=0; i<=pos->wknightcount; i++)
	{
		mv.f=pos->wknight[i];
		if ((mv.t=mv.f+12)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f-12)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f+21)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f-21)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f+19)<89 && globpos.brd[mv.t]>'a') QADD;
		if ((mv.t=mv.f-19)<89 && globpos.brd[mv.t]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+8]>'a') QADD;
		if ((mv.t=mv.f-8)<89 && globpos.brd[mv.t]>'a') QADD;
	}
	for (i=0; i<=pos->wkingcount; i++)
	{
		mv.f=pos->wking[i];
		if (globpos.brd[mv.t=mv.f+10]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+9]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+11]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-10]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-9]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-11]>'a') QADD;
		if (globpos.brd[mv.t=mv.f+1]>'a') QADD;
		if (globpos.brd[mv.t=mv.f-1]>'a') QADD;
	}
	for (i=0; i<=pos->wqueencount; i++)
	{
		mv.f=pos->wqueen[i];
		if (options.game==SHATRANJ)
		{
		   if (globpos.brd[mv.t=mv.f+9]>'a') QADD;
		   if (globpos.brd[mv.t=mv.f+11]>'a') QADD;
		   if (globpos.brd[mv.t=mv.f-9]>'a') QADD;
		   if (globpos.brd[mv.t=mv.f-11]>'a') QADD;
		} else
		{
		   for (mv.t=mv.f; globpos.brd[++mv.t]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[--mv.t]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+10]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-10]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+11]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-9]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t+9]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		   for (mv.t=mv.f; globpos.brd[mv.t=mv.t-11]=='-';);
		   if (globpos.brd[mv.t]>'a') QADD;
		}
	}
 }
 assert(allmoves.amount<maxmovelist);
 return(allmoves);
}

BOOLEAN no_check_position(struct postype *pos, mvtype mv, struct postype *newpos)
{
  alter(pos,mv,newpos);
  if (pos->mvr=='b')
  {
	if (check(newpos,newpos->bking[0])) return(FALSE);
	if (mv.f==58)
	{
	  if (mv.t==78 && pos->brd[58]=='k')
	  {
		 if ((check(pos,58) || check(newpos,68) || check(newpos,78))) return(FALSE);
	  } else
	  if (mv.t==38 && pos->brd[58]=='k')
     {
	 if ((check(pos,58) || check(newpos,48) || check(newpos,38))) return(FALSE);
	  }
	}
  } else
  {
	if (check(newpos,newpos->wking[0])) return(FALSE);
	if (mv.f==51)
	{
	 if (mv.t==71 && pos->brd[51]=='K')
	 {
		if (check(pos,51) || check(newpos,61) || check(newpos,71)) return(FALSE);
	 } else
	 if (mv.t==31 && pos->brd[51]=='K')
	 {
		if (check(pos,51) || check(newpos,41) || check(newpos,31)) return(FALSE);
	 }
	}
  }
  return(TRUE);
}

char previous_pos(struct postype current, struct gametype game, char times)
{
  int i,j;
  char same, count;
  struct postype pos, previous;
  count=0;
  previous=game.firstpos;
  for (i=1; i<game.movenum; i++)
  {
	  same=TRUE;
	  for (j=11; j<=88; j++)
	  {
	if (current.brd[j]!=previous.brd[j])
	{
	  same=FALSE;
	  break;
	}
	  }
	  if (current.mvr != previous.mvr) same=FALSE;
	  if (same==TRUE) count++;
	  if (count==times) return(TRUE);
	  pos=previous;
	  alter(&pos,game.previous_moves[i],&previous);
  }
  return(FALSE);
}


