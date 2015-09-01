#include<iostream.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
int cx,cy,q;

class mouse
{
       REGS    regs;
       int no_buttons;
       public:
	       void show_mouse();
	       void get_status();
	       void hide_mouse();
	       mouse()
	       {
		       regs.x.ax=0;
		       int86(0x33,&regs,&regs);
		       if (regs.x.ax==0xfff)no_buttons=regs.x.bx;
	       }
}m;
void mouse::show_mouse()
{
       regs.x.ax=0x01;
       int86(0x33,&regs,&regs);
}
void mouse::hide_mouse()
{
       regs.x.ax=0x02;
       int86(0x33,&regs,&regs);
} 
void mouse::get_status()
{
       regs.x.ax=0x03;
       int86(0x03,&regs,&regs);
       while(q!=1)
       {
	       regs.x.ax=0x03;
	       int86(0x33,&regs,&regs);
	       q=regs.x.bx;
	       cx=regs.x.cx;
	       cy=regs.x.dx;
       }
       q=0;
}

void grid()
{
	      setcolor(2);
	for(int x=200,i=1;(x<=440)&&(i<=7);i++,x +=40)
		line(x,100,x,420);
	for(int y=100,j=1;(y<=420)&&(j<=9);j++,y +=40)
		line(200,y,440,y);

}
void outline()
{
	setfillstyle(8,8);
	setcolor(8);
	rectangle(150,50,490,470);
	bar(151,51,489,469);
	rectangle(170,70,470,450);
	setfillstyle(1,0);
	bar(171,71,469,449);
	setcolor(RED);
	rectangle(195,95,445,425);
	line(445,215,450,215);
	line(445,255,450,255);
	setcolor(BLACK);
	line(445,215,445,255);
	int x=getmaxx()-35;
	int y=getmaxy()-25;
	setcolor(15);
	outtextxy(x,y,"EXIT");

}
void rat(int a,int b,int x,int y)
{
		setcolor(8);
		setfillstyle(1,8);
		arc(a+15,y-4,0.1,180,14);
		arc(a+25,y-4,0.1,180,7);
		pieslice(a+16,y-4,180,0.1,13);
		pieslice(a+26,y-4,0.1,180,7);
		putpixel(a+26,y-8,BLACK);
		putpixel(a+29,y-7,BLACK);

}
struct block
{
	int tx,ty,bx,by;
}t[11]={{321,141,399,179},{201,181,319,219},{361,181,399,259},{401,181,439,259}
,{321,261,439,299},{281,221,319,339},{201,261,239,419},{241,381,359,419},
{361,301,399,419},{401,301,439,419},{201,221,239,259}};

void exit1(int cx,int cy)
{
	int x=getmaxx()-35;
	int y=getmaxy()-35;
	if(cx>x&&cy>y)
		exit(0);
}
void	print_score(int	score,int count)
{
	char	s[20];
		cleardevice();
		setcolor(11);
		settextstyle(3,0,3);
		itoa(score,s,10);
		outtextxy(150,100,"SCORE:");
		outtextxy(340,100,s);
	    if(count<=10)
	    {
		score+=40;
		outtextxy(150,200,"BONUS POINTS:");
		outtextxy(340,200,"40");
	    }
	   else if((count>10)&&(score<=20))
	   {
		 score+=10;
		outtextxy(150,200,"BONUS POINTS:");
		outtextxy(340,200,"10");
	   }
	   else
	   {
		outtextxy(150,200,"BONUS POINTS:");
		outtextxy(340,200,"0");
	   }
	    itoa(score,s,10);
	    outtextxy(150,300,"TOTAL SCORE:");
	    outtextxy(340,300,s);
}


block	a[13]={{241,101,319,139},{201,141,239,219},{241,181,279,259},{201,301,279,339},
		{201,381,319,419},{281,181,359,219},{281,261,319,379},{401,101,439,259},
		{321,261,439,299},{321,301,359,379},{361,301,439,339},{361,341,439,379},{201,221,239,259}};

void print_w3l2()
{
	cleardevice();
	outline();
	//rat();
	setcolor(8);
	setfillstyle(11,185);
	for(int i=0;i<13;i++)
	{
		if(i==12)
			rat(a[i].tx,a[i].ty,a[i].bx,a[i].by);

		else
		{
			rectangle(a[i].tx,a[i].ty,a[i].bx,a[i].by);
			bar(a[i].tx+5,a[i].ty+5,a[i].bx-5,a[i].by-5);
		}
	}
}
void  w3l2()
{
	    print_w3l2();
	int lor,bor,L1,L2,score=0;
	int U1,U2,Cx,Cy,flag1=1,flag2=1,game=1,count=0;

	do
	{

	  do
	  {
		flag1=1;
		m.show_mouse();
		m.get_status();
		m.hide_mouse();
		delay(300);
		exit1(cx,cy);
		Cx=cx;
		Cy=cy;

	     for(int i=0;i<13&&flag1==1;i++)
	     {
		if((a[i].tx<=Cx&&a[i].bx>=Cx)&&(a[i].ty<=Cy&&a[i].by>=Cy))
		{

			L1=200,L2=440,U1=100,U2=420;
			flag1=0;
			lor=a[i].bx-a[i].tx;
			bor=a[i].by-a[i].ty;
			if(i==12) lor=lor+bor;
		       if(lor>bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cy>=a[i].ty&&cy<=a[i].by)
				   {
				     for(int j=0;j<13;j++)
				     {
				       if(j!=i)
				       {
					if(!((a[j].ty<a[i].ty&&a[j].by<a[i].ty)||(a[j].ty>a[i].by&&a[j].by>a[i].by)))
					{
						if(a[j].bx<a[i].tx&&L1<a[j].bx)
							L1=a[j].bx;
						else if(a[j].tx>a[i].bx&&L2>a[j].tx)
							L2=a[j].tx;
					}
				       }
				      }


					  if(cx<a[i].tx&&cx>L1)
					  {
						for(j=0;(L1+j)<a[i].tx;j=j+40)
						{
						      if(cx>(L1+j)&&cx<(L1+j+40))
						      {
								flag2=0;
								a[i].tx=L1+j+1;
								if(i==12)
								{
									a[i].bx=a[i].tx+38;
									rat(a[i].tx,a[i].ty,a[i].bx,a[i].by);
								}
								else
									a[i].bx=a[i].tx+lor;
						      }
						}
					  }
					  else if(cx>a[i].bx&&cx<L2)
					  {
						for(j=0;(L2-j)>a[i].bx;j=j+40)
						{
						      if(cx<(L2-j)&&cx>(L2-j-40))
						      {
								flag2=0;
								a[i].bx=L2-j-1;
								if(i==12)
								{
									a[i].tx=a[i].bx-38;
									rat(a[i].tx,a[i].ty,a[i].bx,a[i].by);
								}
								else

									a[i].tx=a[i].bx-lor;
						      }
						}
					  }
					  else if(cx>a[i].tx&&cx<a[i].bx)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
					print_w3l2();
				/*Print the maze!!*/
		       }
		       if(lor<bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cx>=a[i].tx&&cx<=a[i].bx)
				   {
				     for(int j=0;j<13;j++)
				     {
				       if(j!=i)
				       {
					if(!((a[j].tx<=a[i].tx&&a[j].bx<=a[i].tx)||(a[j].tx>=a[i].bx&&a[j].bx>=a[i].bx)))
					{
						if(a[j].by<a[i].ty&&U1<a[j].by)
							U1=a[j].by;
						else if(a[j].ty>a[i].by&&U2>a[j].ty)
							U2=a[j].ty;
					}
				       }
				      }


					  if(cy<a[i].ty&&cy>U1)
					  {
						for(j=0;(U1+j)<=a[i].ty;j=j+40)
						{
						      if(cy>(U1+j)&&cy<(U1+j+40))
						      {
								flag2=0;
								a[i].ty=U1+j+1;
								if(i==12)
								{
									a[i].by=a[i].ty+38;
									rat(a[i].tx,a[i].ty,a[i].bx,a[i].by);
								}
								else

									a[i].by=a[i].ty+bor;
						      }
						}
					  }

					  else if(cy>a[i].by&&cy<U2)
					  {
						for(j=0;(U2-j)>=a[i].by;j=j+40)
						{
						      if(cy<(U2-j)&&cy>(U2-j-40))
						      {
								flag2=0;
								a[i].by=U2-j-1;
								if(i==12)
								{
									a[i].ty=a[i].by-38;
									rat(a[i].tx,a[i].ty,a[i].bx,a[i].by);
								}
								else

									a[i].ty=a[i].by-bor;
						      }
						}
					  }
					  else if(cy>a[i].ty&&cy<a[i].by)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
				print_w3l2();
				/*Print the maze!!*/

		       }
		       cout<<count<<"\b";
		       score+=10;
		}
	     }

	}while(flag1);
	if(a[12].bx>420)
	{
	  game=0;
	}

    }while(game);
	print_score(score,count);
}
block	b[13]={{201,101,239,219},{241,101,279,219},{281,101,359,139},
		{361,101,399,219},{401,101,439,219},{281,181,319,259},
		{321,141,359,259},{361,221,399,299},{401,221,439,299},
		{281,261,319,379},{201,381,279,419},{281,381,359,419},
		{201,221,239,259}};
void print_w3l3()
{
	cleardevice();
	outline();
	//rat();
	setcolor(8);
	setfillstyle(11,185);
	for(int i=0;i<13;i++)
	{

		rectangle(b[i].tx,b[i].ty,b[i].bx,b[i].by);
		bar(b[i].tx+5,b[i].ty+5,b[i].bx-5,b[i].by-5);
	}
}
void	w3l3()
{
	    print_w3l3();
	int lor,bor,L1,L2,score=10;
	int U1,U2,Cx,Cy,flag1=1,flag2=1,game=1,count=0;

	do
	{

	  do
	  {
		flag1=1;
		m.show_mouse();
		m.get_status();
		m.hide_mouse();
		delay(300);
		exit1(cx,cy);
		Cx=cx;
		Cy=cy;

	     for(int i=0;i<13&&flag1==1;i++)
	     {
		if((b[i].tx<=Cx&&b[i].bx>=Cx)&&(b[i].ty<=Cy&&b[i].by>=Cy))
		{

			L1=200,L2=440,U1=100,U2=420;
			flag1=0;
			lor=b[i].bx-b[i].tx;
			bor=b[i].by-b[i].ty;
			if(i==12) lor=lor+bor;
		       if(lor>bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cy>=b[i].ty&&cy<=b[i].by)
				   {
				     for(int j=0;j<13;j++)
				     {
				       if(j!=i)
				       {
					if(!((b[j].ty<b[i].ty&&b[j].by<b[i].ty)||(b[j].ty>b[i].by&&b[j].by>b[i].by)))
					{
						if(b[j].bx<b[i].tx&&L1<b[j].bx)
							L1=b[j].bx;
						else if(b[j].tx>b[i].bx&&L2>b[j].tx)
							L2=b[j].tx;
					}
				       }
				      }


					  if(cx<b[i].tx&&cx>L1)
					  {
						for(j=0;(L1+j)<b[i].tx;j=j+40)
						{
						      if(cx>(L1+j)&&cx<(L1+j+40))
						      {
								flag2=0;
								b[i].tx=L1+j+1;
								if(i==12)
									b[i].bx=b[i].tx+38;
								else
									b[i].bx=b[i].tx+lor;
						      }
						}
					  }
					  else if(cx>b[i].bx&&cx<L2)
					  {
						for(j=0;(L2-j)>b[i].bx;j=j+40)
						{
						      if(cx<(L2-j)&&cx>(L2-j-40))
						      {
								flag2=0;
								b[i].bx=L2-j-1;
								if(i==12)
									b[i].tx=b[i].bx-38;
								else

									b[i].tx=b[i].bx-lor;
						      }
						}
					  }
					  else if(cx>b[i].tx&&cx<b[i].bx)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
					print_w3l3();
				/*Print the maze!!*/
		       }
		       if(lor<bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cx>=b[i].tx&&cx<=b[i].bx)
				   {
				     for(int j=0;j<13;j++)
				     {
				       if(j!=i)
				       {
					if(!((b[j].tx<=b[i].tx&&b[j].bx<=b[i].tx)||(b[j].tx>=b[i].bx&&b[j].bx>=b[i].bx)))
					{
						if(b[j].by<b[i].ty&&U1<b[j].by)
							U1=b[j].by;
						else if(b[j].ty>b[i].by&&U2>b[j].ty)
							U2=b[j].ty;
					}
				       }
				      }


					  if(cy<b[i].ty&&cy>U1)
					  {
						for(j=0;(U1+j)<=b[i].ty;j=j+40)
						{
						      if(cy>(U1+j)&&cy<(U1+j+40))
						      {
								flag2=0;
								b[i].ty=U1+j+1;
								if(i==12)
									b[i].by=b[i].ty+38;
								else

									b[i].by=b[i].ty+bor;
						      }
						}
					  }

					  else if(cy>b[i].by&&cy<U2)
					  {
						for(j=0;(U2-j)>=b[i].by;j=j+40)
						{
						      if(cy<(U2-j)&&cy>(U2-j-40))
						      {
								flag2=0;
								b[i].by=U2-j-1;
								if(i==12)
									b[i].ty=b[i].by-38;
								else

									b[i].ty=b[i].by-bor;
						      }
						}
					  }
					  else if(cy>b[i].ty&&cy<b[i].by)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
				print_w3l3();
				/*Print the maze!!*/

		       }
		       cout<<count<<"\b";
		       score+=10;
		}
	     }

	}while(flag1);
	if(b[12].bx>420)
	{
	  game=0;
	}
	}while(game);

   print_score(score,count);

}
void  w1l1()
{
	    print_w1l1();
	int lor,bor,L1,L2,score=0;
	int U1,U2,Cx,Cy,flag1=1,flag2=1,game=1,count=0;

	do
	{

	  do
	  {
		flag1=1;
		m.show_mouse();
		m.get_status();
		m.hide_mouse();
		delay(300);
		exit1(cx,cy);
		Cx=cx;
		Cy=cy;

	     for(int i=0;i<11&&flag1==1;i++)
	     {
		if((t[i].tx<=Cx&&t[i].bx>=Cx)&&(t[i].ty<=Cy&&t[i].by>=Cy))
		{

			L1=200,L2=440,U1=100,U2=420;
			flag1=0;
			lor=t[i].bx-t[i].tx;
			bor=t[i].by-t[i].ty;
			if(i==10) lor=lor+bor;
		       if(lor>bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cy>=t[i].ty&&cy<=t[i].by)
				   {
				     for(int j=0;j<11;j++)
				     {
				       if(j!=i)
				       {
					if(!((t[j].ty<t[i].ty&&t[j].by<t[i].ty)||(t[j].ty>t[i].by&&t[j].by>t[i].by)))
					{
						if(t[j].bx<t[i].tx&&L1<t[j].bx)
							L1=t[j].bx;
						else if(t[j].tx>t[i].bx&&L2>t[j].tx)
							L2=t[j].tx;
					}
				       }
				      }


					  if(cx<t[i].tx&&cx>L1)
					  {
						for(j=0;(L1+j)<t[i].tx;j=j+40)
						{
						      if(cx>(L1+j)&&cx<(L1+j+40))
						      {
								flag2=0;
								t[i].tx=L1+j+1;
								if(i==10)
									t[i].bx=t[i].tx+38;
								else
									t[i].bx=t[i].tx+lor;
						      }
						}
					  }
					  else if(cx>t[i].bx&&cx<L2)
					  {
						for(j=0;(L2-j)>t[i].bx;j=j+40)
						{
						      if(cx<(L2-j)&&cx>(L2-j-40))
						      {
								flag2=0;
								t[i].bx=L2-j-1;
								if(i==10)
									t[i].tx=t[i].bx-38;
								else

									t[i].tx=t[i].bx-lor;
						      }
						}
					  }
					  else if(cx>t[i].tx&&cx<t[i].bx)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
					print_1();
				/*Print the maze!!*/
		       }
		       if(lor<bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cx>=t[i].tx&&cx<=t[i].bx)
				   {
				     for(int j=0;j<11;j++)
				     {
				       if(j!=i)
				       {
					if(!((t[j].tx<=t[i].tx&&t[j].bx<=t[i].tx)||(t[j].tx>=t[i].bx&&t[j].bx>=t[i].bx)))
					{
						if(t[j].by<t[i].ty&&U1<t[j].by)
							U1=t[j].by;
						else if(t[j].ty>t[i].by&&U2>t[j].ty)
							U2=t[j].ty;
					}
				       }
				      }


					  if(cy<t[i].ty&&cy>U1)
					  {
						for(j=0;(U1+j)<=t[i].ty;j=j+40)
						{
						      if(cy>(U1+j)&&cy<(U1+j+40))
						      {
								flag2=0;
								t[i].ty=U1+j+1;
								if(i==10)
									t[i].by=t[i].ty+38;
								else

									t[i].by=t[i].ty+bor;
						      }
						}
					  }

					  else if(cy>t[i].by&&cy<U2)
					  {
						for(j=0;(U2-j)>=t[i].by;j=j+40)
						{
						      if(cy<(U2-j)&&cy>(U2-j-40))
						      {
								flag2=0;
								t[i].by=U2-j-1;
								if(i==10)
									t[i].ty=t[i].by-38;
								else

									t[i].ty=t[i].by-bor;
						      }
						}
					  }
					  else if(cy>t[i].ty&&cy<t[i].by)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
				print1();
				/*Print the maze!!*/

		       }
		       cout<<count<<"\b";
		       score+=10;
		}
	     }

	}while(flag1);
	if(t[10].bx>420)
	{
	  game=0;
	}

    }while(game);
    print_score(score,count);
}
block  z[9]={{321,101,439,139},{201,141,279,179},{241,181,279,339},{321,181,359,299},{281,261,319,339},
	     {321,301,439,339},{241,341,359,379},{281,381,439,419},{201,221,239,259}};
void print_w4()
{      cleardevice();
	outline();
	//rat();
	setcolor(8);
	setfillstyle(11,185);
	for(int i=0;i<9;i++)
	{
		if(i==8)
		{
		  rat();
		}
		
		else
		{
		rectangle(z[i].tx,z[i].ty,z[i].bx,z[i].by);
		bar(z[i].tx+5,z[i].ty+5,z[i].bx-5,z[i].by-5);
		}
	}
}
void  w4()
{
       print_w4();
	int lor,bor,L1,L2,score=0;
	int U1,U2,Cx,Cy,flag1=1,flag2=1,game=1,count=0;

	do
	{

	  do
	  {
		flag1=1;
		m.show_mouse();
		m.get_status();
		m.hide_mouse();
		delay(300);
		exit1(cx,cy);
		Cx=cx;
		Cy=cy;

	     for(int i=0;i<9&&flag1==1;i++)
	     {
		if((z[i].tx<=Cx&&z[i].bx>=Cx)&&(z[i].ty<=Cy&&z[i].by>=Cy))
		{

			L1=200,L2=440,U1=100,U2=420;
			flag1=0;
			lor=z[i].bx-z[i].tx;
			bor=z[i].by-z[i].ty;
			if(i==8) lor=lor+bor;
		       if(lor>bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cy>=z[i].ty&&cy<=z[i].by)
				   {
				     for(int j=0;j<9;j++)
				     {
				       if(j!=i)
				       {
					if(!((z[j].ty<z[i].ty&&z[j].by<z[i].ty)||(z[j].ty>z[i].by&&z[j].by>z[i].by)))
					{
						if(z[j].bx<z[i].tx&&L1<z[j].bx)
							L1=z[j].bx;
						else if(z[j].tx>z[i].bx&&L2>z[j].tx)
							L2=z[j].tx;
					}
				       }
				      }


					  if(cx<z[i].tx&&cx>L1)
					  {
						for(j=0;(L1+j)<z[i].tx;j=j+40)
						{
						      if(cx>(L1+j)&&cx<(L1+j+40))
						      {
								flag2=0;
								z[i].tx=L1+j+1;
								if(i==8)
									z[i].bx=z[i].tx+38;
								else
									z[i].bx=z[i].tx+lor;
						      }
						}
					  }
					  else if(cx>z[i].bx&&cx<L2)
					  {
						for(j=0;(L2-j)>z[i].bx;j=j+40)
						{
						      if(cx<(L2-j)&&cx>(L2-j-40))
						      {
								flag2=0;
								z[i].bx=L2-j-1;
								if(i==8)
									z[i].tx=z[i].bx-38;
								else

									z[i].tx=z[i].bx-lor;
						      }
						}
					  }
					  else if(cx>z[i].tx&&cx<z[i].bx)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
					print_w4();
				/*Print the maze!!*/
		       }
		       if(lor<bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cx>=z[i].tx&&cx<=z[i].bx)
				   {
				     for(int j=0;j<9;j++)
				     {
				       if(j!=i)
				       {
					if(!((z[j].tx<=z[i].tx&&z[j].bx<=z[i].tx)||(z[j].tx>=z[i].bx&&z[j].bx>=z[i].bx)))
					{
						if(z[j].by<z[i].ty&&U1<z[j].by)
							U1=z[j].by;
						else if(z[j].ty>z[i].by&&U2>z[j].ty)
							U2=z[j].ty;
					}
				       }
				      }


					  if(cy<z[i].ty&&cy>U1)
					  {
						for(j=0;(U1+j)<=z[i].ty;j=j+40)
						{
						      if(cy>(U1+j)&&cy<(U1+j+40))
						      {
								flag2=0;
								z[i].ty=U1+j+1;
								if(i==8)
									z[i].by=z[i].ty+38;
								else

									z[i].by=z[i].ty+bor;
						      }
						}
					  }

					  else if(cy>z[i].by&&cy<U2)
					  {
						for(j=0;(U2-j)>=z[i].by;j=j+40)
						{
						      if(cy<(U2-j)&&cy>(U2-j-40))
						      {
								flag2=0;
								z[i].by=U2-j-1;
								if(i==8)
									z[i].ty=z[i].by-38;
								else

									z[i].ty=z[i].by-bor;
						      }
						}
					  }
					  else if(cy>z[i].ty&&cy<z[i].by)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
				print_w4();
				/*Print the maze!!*/

		       }
		       cout<<count<<"\b";
			score+=10;
		}
	     }

	}while(flag1);
	if(z[8].bx>420)
	{
	  game=0;
	}

    }while(game);
	print_score(score,count);
}
block  c[11]={{241,101,359,139},{201,141,279,179},{361,101,399,259},{401,101,439,219},{281,181,319,339},{241,221,279,299},
                              {321,261,399,299},{321,301,439,339},{321,341,359,419},{201,341,319,379},{201,221,239,259}};
void print_w5()
{                      
                        cleardevice();
	outline();
	rat();
	setcolor(8);
	setfillstyle(11,185);
	for(int i=0;i<11;i++)
	{
		if(i==10)
		{
			rat();

		}
		else
		{
		rectangle(c[i].tx,c[i].ty,c[i].bx,c[i].by);
		bar(c[i].tx+5,c[i].ty+5,c[i].bx-5,c[i].by-5);
		}
	}
}
void  w5()
{
	     print_w5();
	int lor,bor,L1,L2,score=0;
	int U1,U2,Cx,Cy,flag1=1,flag2=1,game=1,count=0;

	do
	{

	  do
	  {
		flag1=1;
		m.show_mouse();
		m.get_status();
		m.hide_mouse();
		delay(300);
		exit1(cx,cy);
		Cx=cx;
		Cy=cy;

	     for(int i=0;i<11&&flag1==1;i++)
	     {
		if((c[i].tx<=Cx&&c[i].bx>=Cx)&&(c[i].ty<=Cy&&c[i].by>=Cy))
		{

			L1=200,L2=440,U1=100,U2=420;
			flag1=0;
			lor=c[i].bx-c[i].tx;
			bor=c[i].by-c[i].ty;
			if(i==10) lor=lor+bor;
		       if(lor>bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cy>=c[i].ty&&cy<=c[i].by)
				   {
				     for(int j=0;j<11;j++)
				     {
				       if(j!=i)
				       {
					if(!((c[j].ty<c[i].ty&&c[j].by<c[i].ty)||(c[j].ty>c[i].by&&c[j].by>c[i].by)))
					{
						if(c[j].bx<c[i].tx&&L1<c[j].bx)
							L1=c[j].bx;
						else if(c[j].tx>c[i].bx&&L2>c[j].tx)
							L2=c[j].tx;
					}
				       }
				      }


					  if(cx<c[i].tx&&cx>L1)
					  {
						for(j=0;(L1+j)<c[i].tx;j=j+40)
						{
						      if(cx>(L1+j)&&cx<(L1+j+40))
						      {
								flag2=0;
								c[i].tx=L1+j+1;
								if(i==10)
									c[i].bx=c[i].tx+38;
								else
									c[i].bx=c[i].tx+lor;
						      }
						}
					  }
					  else if(cx>c[i].bx&&cx<L2)
					  {
						for(j=0;(L2-j)>c[i].bx;j=j+40)
						{
						      if(cx<(L2-j)&&cx>(L2-j-40))
						      {
								flag2=0;
								c[i].bx=L2-j-1;
								if(i==10)
									c[i].tx=c[i].bx-38;
								else

									c[i].tx=c[i].bx-lor;
						      }
						}
					  }
					  else if(cx>c[i].tx&&cx<c[i].bx)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
					print_w5();
				/*Print the maze!!*/
		       }
		       if(lor<bor)
		       {
				do
				{
				   flag2=1;
				   m.show_mouse();
				   m.get_status();
				   count++;
				   m.hide_mouse();
				   delay(300);
				   exit1(cx,cy);
				   if(cx>=c[i].tx&&cx<=c[i].bx)
				   {
				     for(int j=0;j<11;j++)
				     {
				       if(j!=i)
				       {
					if(!((c[j].tx<=c[i].tx&&c[j].bx<=c[i].tx)||(c[j].tx>=c[i].bx&&c[j].bx>=c[i].bx)))
					{
						if(c[j].by<c[i].ty&&U1<c[j].by)
							U1=c[j].by;
						else if(c[j].ty>c[i].by&&U2>c[j].ty)
							U2=c[j].ty;
					}
				       }
				      }


					  if(cy<c[i].ty&&cy>U1)
					  {
						for(j=0;(U1+j)<=c[i].ty;j=j+40)
						{
						      if(cy>(U1+j)&&cy<(U1+j+40))
						      {
								flag2=0;
								c[i].ty=U1+j+1;
								if(i==10)
									c[i].by=c[i].ty+38;
								else

									c[i].by=c[i].ty+bor;
						      }
						}
					  }

					  else if(cy>c[i].by&&cy<U2)
					  {
						for(j=0;(U2-j)>=c[i].by;j=j+40)
						{
						      if(cy<(U2-j)&&cy>(U2-j-40))
						      {
								flag2=0;
								c[i].by=U2-j-1;
								if(i==10)
									c[i].ty=c[i].by-38;
								else

									c[i].ty=c[i].by-bor;
						      }
						}
					  }
					  else if(cy>c[i].ty&&cy<c[i].by)
						flag2=0;
				   }
				}while(flag2);
				if(flag2==0)
				print_w5();
				/*Print the maze!!*/

		       }
		       cout<<count<<"\b";
			score=score+10;
		}
	     }

	}while(flag1);
	if(c[10].bx>420)
	{
	  game=0;
	}

    }while(game);
	print_score(score,count);
}
void main()
{
		int gd=9,gm=2;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
   
    //	delay(500);
	//w3l3();
      //	delay(500);
	w3l2();
       //	delay(500);
	getch();
	closegraph();
}
