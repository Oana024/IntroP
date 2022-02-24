#include <bits/stdc++.h>

using namespace std;

char cuvant[256];
char grup_consoane[10][4]={"lpt", "mpt", "nct", "ncs", "ndv", "rct", "rtf", "stm"};
char hiat[10][3]={"aa", "ae", "ao", "ee", "oe", "oo", "ue", "uo", "uu"};

bool vocala(char c)
{
    if(strchr("AEIOUaeiou", c)!=0 && isalpha(c))
        return true;
    return false;
}

bool consoana(char c)
{
    if(strchr("AEIOUaeiou", c)==0 && isalpha(c))
        return true;
    return false;
}

void desparte(int pozitie)
{
    char aux[256];
    strcpy(aux, cuvant+pozitie);
    cuvant[pozitie]='-';
    cuvant[pozitie+1]='\0';
    strcat(cuvant, aux);
}

int main(){
    int i, j, p, ok;

    while(1){

    cin>>cuvant;

    for(i=0; i<strlen(cuvant); i++)
        if(vocala(cuvant[i]) && consoana(cuvant[i+1]) && vocala(cuvant[i+2]))//o consoana intre 2 vocale
        {
            if(strchr("cg", cuvant[i+1]) && strchr("ei", cuvant[i+2]) && i+2==strlen(cuvant)-1)
                continue;
            else
                desparte(i+1);
        }
        else
            if(vocala(cuvant[i]) && consoana(cuvant[i+1]) && consoana(cuvant[i+2]) && vocala(cuvant[i+3]))//2 consoane intre 2 vocale
            {
                if(strchr("cg", cuvant[i+2]) && strchr("ei", cuvant[i+3]) && i+3==strlen(cuvant)-1)
                    continue;
                else
                    if(strchr("cg", cuvant[i+1]) && cuvant[i+2]=='h' && strchr("ei", cuvant[i+3]))
                        desparte(i+1);
                    else
                        if(strchr("lr", cuvant[i+2]) && strchr("bcdfghptv", cuvant[i+1]))
                            desparte(i+1);
                        else
                            desparte(i+2);
            }
            else
                if(vocala(cuvant[i]) && consoana(cuvant[i+1]) && consoana(cuvant[i+2]) && consoana(cuvant[i+3]))//3+ consoane intre 2 vocale
                {
                    p=i+3;
                    while(vocala(cuvant[p])==0 && p<strlen(cuvant))
                        p++;

                    if(vocala(cuvant[p]))
                    {
                        if(p==i+4)
                        {
                            ok=0;
                            for(j=0; j<8 && ok==0; j++)
                                if(cuvant[i+1]==grup_consoane[j][0] && cuvant[i+2]==grup_consoane[j][1] && cuvant[i+3]==grup_consoane[j][2])
                                {
                                    desparte(i+3);
                                    ok=1;
                                }

                            if(ok==0)
                                desparte(i+2);
                        }
                        else
                            desparte(i+2);
                    }
                }
                else
                    if(vocala(cuvant[i]) && vocala(cuvant[i+1]))//2 vocale
                    {
                        if(vocala(cuvant[i+2]) && vocala(cuvant[i+3]))
                        {
                            if(cuvant[i]=='e' && cuvant[i+1]=='i' && cuvant[i+2]=='o' && cuvant[i+3]=='a')
                            {
                                desparte(i+1);
                                i+=3;
                            }
                        }
                        else
                            if(cuvant[i]=='i' && (consoana(cuvant[i+2]) || i+1==strlen(cuvant)-1))
                            {
                                if(consoana(cuvant[i-1]))
                                    desparte(i+1);
                            }
                            else
                                if(vocala(cuvant[i+2]) && cuvant[i]=='a')
                                {
                                    desparte(i+1);
                                    i++;
                                }
                                else
                                    if(i>1 && cuvant[i-1]=='h' && strchr("cg", cuvant[i-2]) && ((cuvant[i]=='i' && strchr("ae", cuvant[i+1])) || (cuvant[i]=='e' && cuvant[i+1]=='e')) )
                                        desparte(i+1);
                                    else
                                        if(i>0 && strchr("cg", cuvant[i-1]) && ((cuvant[i]=='i' && strchr("ae", cuvant[i+1])) || (cuvant[i]=='e' && cuvant[i+1]=='e')))
                                            desparte(i+1);
                                        else
                                            if(i>1 && cuvant[i-1]=='h' && strchr("cg", cuvant[i-2]) && strchr("ei", cuvant[i]))
                                                continue;
                                            else
                                                if(i>0 && strchr("ei", cuvant[i]) && strchr("cg", cuvant[i-1]))
                                                    continue;
                                                else
                                                {
                                                    ok=0;
                                                    for(j=0; j<9 && ok==0; j++)
                                                        if(hiat[j][0]==cuvant[i] && hiat[j][1]==cuvant[i+1])
                                                        {
                                                            desparte(i+1);
                                                            ok=1;
                                                        }
                                                    if(ok==0)
                                                        desparte(i+1);
                                            }
                    }

    cout<<cuvant<<'\n';
    }
}
