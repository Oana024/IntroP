#include <graphics.h>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int tabla[7][7], dim, d, l;
int dx[]={-1, 0, 0, 1};
int dy[]={0, 1, -1, 0};

struct
{
    int x, y;
}mutare;

void deseneaza_piesa(int x, int y, int c)
{
    if(c==1)
    {
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
    }
    else
        if(c==2)
        {
            setcolor(BLUE);
            setfillstyle(SOLID_FILL, BLUE);
        }
        else
        {
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
        }

    fillellipse(x, y, 30, 30);

    setcolor(WHITE);
}

void deseneaza_tabla(int dim, int d, int l)
{
    rectangle(d, d, dim-50, dim-50);

    int i, j, x, y;

    for(i=d; i<=dim-d; i+=l)
    {
        line(i, d, i, dim-d);
        line(d, i, dim-d, i);
    }

    deseneaza_piesa(x-l/2, y-l/2, 3);
    for(i=1; i<=5; i++)
        for(j=1; j<=5; j++)
            if(i!=3 || j!=3)
            {
                x=l*i+d;
                y=l*j+d;
                tabla[i][j]=3-((i+j)%2+1);
                deseneaza_piesa(x-l/2, y-l/2, tabla[i][j]);
            }

    mutare.x=3;
    mutare.y=3;

    for(i=0; i<=6; i++)
    {
        tabla[0][i]=tabla[6][i]=3;
        tabla[i][0]=tabla[i][6]=3;
    }
}

int avem_castigator(int x, int y, int j)
{
    if(tabla[x-1][y]!=j && tabla[x+1][y]!=j && tabla[x][y-1]!=j && tabla[x][y+1]!=j)
        return 3-j;
    return 0;
}

bool ok(int x, int y, int j)
{
    if(tabla[x][y]!=j)
        return false;

    if(tabla[x-1][y]==0 || tabla[x+1][y]==0 || tabla[x][y-1]==0 || tabla[x][y+1]==0)
        return true;

    return false;
}

void gaseste_poz(int &x, int &y)
{
    x=x-50;
    y=y-50;
    x=x/120+1;
    y=y/120+1;
}

void joaca2(int x, int y)
{
    int i, px, py, mx, my, ok=0;

    srand(time(NULL));
    while(ok==0)
    {
        i=rand()%4;
        mx=x+dx[i];
        my=y+dy[i];
        if(tabla[mx][my]==2)
        {
            px=l*my+d;
            py=l*mx+d;
            deseneaza_piesa(px-l/2, py-l/2, 3);

            swap(tabla[mx][my], tabla[x][y]);

            px=l*y+d;
            py=l*x+d;

            mutare.x=mx;
            mutare.y=my;

            deseneaza_piesa(px-l/2, py-l/2, 2);
            ok=1;
        }
    }
}

void joaca1(int x, int y, int jucator)
{
    int px, py;

    px=l*y+d;
    py=l*x+d;

    deseneaza_piesa(px-l/2, py-l/2, 3);

    swap(tabla[x][y], tabla[mutare.x][mutare.y]);

    px=l*mutare.y+d;
    py=l*mutare.x+d;

    mutare.x=x;
    mutare.y=y;

    deseneaza_piesa(px-l/2, py-l/2, jucator);

}

int main()
{
    dim=700, d=50;
    int x, y, jucator;
	initwindow(dim, dim, "Patrate Glisante");

	l=(dim-2*d)/5;

    deseneaza_tabla(dim, d, l);

    jucator=1;
    while(avem_castigator(mutare.x, mutare.y, jucator)==0)
    {
        if(jucator==1)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                y=mousex();
                x=mousey();

                if(x>d && x<dim-d && y>d && y<dim-d)
                {
                    gaseste_poz(x, y);
                    if(ok(x, y, jucator))
                    {
                        joaca1(x, y, jucator);
                        jucator=3-jucator;
                    }
                }
            }
        }
        else
        {
            usleep(100000);
            joaca2(mutare.x, mutare.y);
            jucator=3-jucator;
        }
    }

    setcolor(YELLOW);
    settextstyle(0, HORIZ_DIR, 6);
    if(avem_castigator(mutare.x, mutare.y, jucator)==1)
        outtextxy(50, 350, "ATI CASTIGAT!");
    else
        outtextxy(80, 350, "ATI PIERDUT!");

	getch();
}
