#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int n_of_words(const char* x, int n){///êîë ñëîâ
    int j=1;
    for(int i=0; i<n;i++){
        if(isspace(x[i])){
            j++;
            continue;
        }
    }
    return j;
}

void form_changer(string categories[], int n_of_w){
    int l_of_str, is_noun=0,is_pril=0;
    string slovo="",xn,x_okon,x_a,x_b,x_left, x_t,x_p,okonch,okonch_a,okonch_b;

    for(int i=0;i<n_of_w;++i){
        l_of_str = categories[i].length()-2;
        x_okon = x_left = categories[i];

        x_okon.erase(0,l_of_str);
        x_left.erase(l_of_str,1);

        okonch_a = x_okon;


int k=0;
        if(x_okon=="àÿ"){

            okonch="îé";///îáóâü, ôóòáîëêà, îäåæäà
            if(!i){is_pril++;
            x_t = x_p = categories[i+1];}else
            if (is_noun)
                x_t = x_p = categories[i-1];

            slovo+=x_left.erase(l_of_str,1)+okonch+" ";
            okonch_b = x_t.erase(0,x_t.length()-2);
            x_t.erase(0,x_t.length()-1);
            okonch_b.erase(okonch_b.end()-1);

            if(okonch_b=="ê"){
                k++;
                cout<<"okonb = "<<okonch_b<<endl;
                slovo+=x_p.erase(x_p.length()-1,1)+"è";
            }
            if(x_t=="ü"){
                slovo+=x_p.erase(x_p.length()-1,1)+"è";
            }
            else if(!k)
                slovo+=x_p.erase(x_p.length()-1,1)+"û";
        }else if(!i){
            is_noun++;
        }


        int is_pred=0; ///Ïðåäëîãè
        if(categories[i].length()<4&&categories[i]=="äëÿ"||categories[i]=="c"||categories[i]=="ïî"||categories[i]=="íà"){
            for(int j=i;j<n_of_w;++j){
                i++;
                is_pred++;
                slovo=slovo+" "+categories[j];
            }
        }
        if(is_pred)break;
    }
    cout<<"Ïðîèçâîäèòåëü "+slovo+" èç";
}

int main()
{
    system("chcp 1251>0");
    setlocale(LC_ALL,"Russian");
    string category="Æåíñêàÿ îäåæäà íà ëåòî";
    //getline(cin,category);
    string country="Ðîññèÿ";

    int h=0;
    int count=0,no=0;
    char myArray[category.size()+1];
    strcpy(myArray, category.c_str());
    int ip = n_of_words(myArray,category.length());
string categories[ip];
char *pl;
pl = strtok(myArray," ");
int y=0;
while (pl != NULL&&y<ip){
    categories[y]=pl;
    cout<<pl<<" ";
    y++;
    pl = strtok (NULL, " ,.-");
}
cout<<"\n\n";
//for(int i=0;i<ip;++i){
//    cout<<categories[i]<<endl;
//}
form_changer(categories,ip);
cout<<"\n";
getchar();

//cout<<okonchanie(categories,ip);

}
