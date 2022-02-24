#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

ifstream f("arbore.in");

struct nod{
    int informatieUtila, nivel, coloana;
    nod *stanga, *dreapta;
};

typedef nod* arbore;

int NrLinii, NrColoane, DimLinie, DimColoana, DimNod;

void NumerotareColoane(arbore a, int c)
{
    if(a!=NULL)
    {
        if(a->stanga!=NULL)
        {
            NumerotareColoane(a->stanga, c-1);
        }
        a->coloana=c;
        if(a->dreapta!=NULL)
        {
            NumerotareColoane(a->dreapta, c+1);
        }
    }
}

void citeste_arbore(arbore &a)
{
    int x;

    f>>x;
    if(x!=0)
    {
        a=new nod;
        a->informatieUtila=x;
        citeste_arbore(a->stanga);
        citeste_arbore(a->dreapta);
    }
    else
        a=NULL;
}

void NiveleArbore(arbore a, int niv)
{
    if(a!=NULL)
    {
        if(niv>NrLinii)
            NrLinii=niv;
        a->nivel=niv;
        NiveleArbore(a->stanga, niv+1);
        NiveleArbore(a->dreapta, niv+1);
    }
}

void IntToChar(int info, char s[])
{
    char cifra;
    int i=0;
    while(info)
    {
        cifra=char(info%10+'0');
        s[i++]=cifra;
        info/=10;
    }
    s[i]='\0';
    for(i=0; i<strlen(s)/2; i++)
        swap(s[i], s[strlen(s)-i-1]);
}

void deseneazaNod(arbore a)
{
    int linie=a->nivel, coloana=a->coloana, x=coloana*DimColoana, y=(linie-1)*DimLinie;

    circle(x+(DimColoana/2),y+(DimLinie/2), DimNod);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x+(DimColoana/2), y+(DimLinie/2), DimNod-1, DimNod-1);
    setcolor(WHITE);
    char s[101];
    IntToChar(a->informatieUtila, s);
    outtextxy(x+(DimColoana/2)-textheight(s)/2, y+(DimLinie/2)-textheight(s)/2, s);

}

void deseneazaMuchie(arbore a, arbore b)
{
    int linie1, linie2, coloana1, coloana2;
    linie1=a->nivel;
    coloana1=a->coloana;
    linie2=b->nivel;
    coloana2=b->coloana;

    int x1, x2, y1, y2;
    x1=coloana1*DimColoana;
    y1=(linie1-1)*DimLinie;
    x2=coloana2*DimColoana;
    y2=(linie2-1)*DimLinie;

    line(x1+(DimColoana/2), y1+(DimLinie/2), x2+(DimColoana/2), y2+(DimLinie/2));
}


void deseneazaArbore(arbore a)
{
    if(a!=NULL)
    {
        if(a->stanga != NULL)
            deseneazaMuchie(a, a->stanga);
        if(a->dreapta != NULL)
            deseneazaMuchie(a, a->dreapta);
        deseneazaNod(a);
        deseneazaArbore(a->stanga);
        deseneazaArbore(a->dreapta);
    }
}

int NoduriStanga(arbore a)
{
    if(a==NULL)
        return 0;
    return 1+NoduriStanga(a->stanga);
}

int latimeArbore(arbore a)
{
    if(a==NULL)
        return 0;
    return 1+latimeArbore(a->stanga)+latimeArbore(a->dreapta);
}

int main(){
    arbore a;
    citeste_arbore(a);
    NumerotareColoane(a, NoduriStanga(a));
    NumerotareColoane(a->dreapta, NoduriStanga(a->dreapta)+NoduriStanga(a));

    NiveleArbore(a, 1);
    NrColoane=latimeArbore(a);

    initwindow(1300, 700, "Reprezentare Grafica Arbore");

    DimLinie=700/NrLinii;
    DimColoana=1300/NrColoane;
    DimNod=DimColoana/2-DimColoana/4;

    deseneazaArbore(a);

    getch();

}
