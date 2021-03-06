#include <iostream>
#include <math.h>
#include <fstream>
#include <stdexcept>
#include <string.h>
#include <cstdlib>
/*
�����: �(�����), �(��������),��(������),�(������),�(������), �(�������).
�������� �������:
1) (�, ��)
    ���������� �������� ���� ����� ������� ����� 2-� ������:
   > �) � � �� ����� � � � �� ������. ���� �������, �� ���������� ��������� (�, �, �, �) �. �.:
     �) ������� ����� 2-�� �����, ������ � ����� 1-�� � �������� ����� 2-�� �����, ��� ����� ��������� ����� ��������� �� ����� ������ � � 1-��.
     �) ���������� (�, �, �, �)[1-��] � (�, �, �, �)[2-��], ���� �������, �� ������� ������ �����, ���� ������.
        ���� �� �������, �� ����������� ������� � ��������� � ��������� (�, �).
2) (�, �) // ��� ��. ���� �������, �� �������(����������� 0) ������ �����, ���� ������.
        ���� �� �������, �� ����������� ������� � ��������� � ��������� (�, �).
3) (�, �) // ��� ��. ���� �������, �� ������� ������ �����, ���� ������.
        ���� �� �������, �� ����������� ������� � ��������� � ��������� ��������� �����.
        ��������� �� ����� ������.
4) ���������� (����������_������ - �������)
*/
#define lr(x) x/100000*10+x/1000%10 /// left-right
#define lrx(x) x/10000%10*1000+x/10%10*100+x/100%10*10+x%10///���������_�����(left-right)
#define fb(x) x/10000%10*10+x/100%10///front-back
#define fbx(x) x/100000*1000+x/10%10*100+x/1000%10*10+x%10
#define tb(x) x/10%10*10+x%10///top-bottom
#define tbx(x) x/100000*1000+x/10000%10*100+x/1000%10*10+x/100%10

using namespace std;

const int len=12;///����� ������ ������ + 1
char line[len];

int parse_int(const char* pstr, int len){///�������������� ������ � �����
  int r=0;
  for(int i=0; i<len; ++i){
    char c=*pstr++;
    if(isdigit(c)){
      r*=10;
      r+=(c-'0');
    }
    else if(!isspace(c)){
        throw domain_error("������! ������������� � �����!");
    }
  }
  return r;
}
int arr_x(int x[],char *filename){///������� ������ � ������ �����
ifstream fin(filename);
if(!fin){cout<<"File not found (from int arr_x)!"; return 1;}
int isN=0, i=0;

    while(fin.getline(line,len)){
        if(!isN){
            ++isN;
            continue;
        }
        x[i]=parse_int(line, strlen(line));
        cout<<x[i]<<endl;
        i++;
    }
cout<<endl;
fin.close();
}
int size_n(char *filename){///���������� ������ ������ (����������_������)
 ifstream fin(filename);
 if(!fin){cout<<"File not found (from int size_n)!"; return 1; }
    while(fin.getline(line,len)){
        return atoi(line);
    }
}
int size(int x){///����� �����
    int i=0;
    while(x){
        x/=10;
        i++;
    }
    return i;
}
int find_index(int x,int c){///���������� �����, ������ ������
    int i=1;
    int h=x;
        while(1){
            if (h%10!=c){
                i++;
                h/=10;
            }
            else
                return i;
        }
}
int shifting(int x,int length){///����� ������
    int v=1;
    for(int i=0;i<size(x)-1;++i)
        v=v*10;
    for(int i=0; i<length; ++i)
        x=x%v*10+x/v;
    return x;
}
int number_of_schemes(int x[],int n){///��������. ����������� ���������� ����
    int lr,lrx,tmp_lr,tmp_lrx,
        fb,fbx,tmp_fb,tmp_fbx,
        tb,tbx,tmp_tb,tmp_tbx;
    int c,length;
    int count=0;
    for(int i=0;i<n;++i){
        lr=lr(x[i]); lrx=lrx(x[i]);
        fb=fb(x[i]); fbx=fbx(x[i]);
        tb=tb(x[i]); tbx=tbx(x[i]);
        if(x[i]==0)continue;
        for(int j=i+1;j<n;++j){
            tmp_lr=lr(x[j]); tmp_lrx=lrx(x[j]);
            tmp_fb=fb(x[j]); tmp_fbx=fbx(x[j]);
            tmp_tb=tb(x[j]); tmp_tbx=tbx(x[j]);
            if(x[j]==0)continue;
            if(lr==tmp_lr){
                c = lrx/1000;
                length=size(tmp_lrx)-find_index(tmp_lrx,c);
                if(shifting(tmp_lrx,length)==lrx){
                    count++;
                    x[j]=0;
                }
            }
            else if(fb==tmp_fb){
                c = fbx/1000;
                length=size(tmp_fbx)-find_index(tmp_fbx,c);
                if(shifting(tmp_fbx,length)==fbx){
                    count++;
                    x[j]=0;
                }
            }
            else if(tb==tmp_tb){
                c = tbx/1000;
                length=size(tmp_tbx)-find_index(tmp_tbx,c);
                if(shifting(tmp_tbx,length)==tbx){
                    count++;
                    x[j]=0;
                }
            }

        }
    }
    return n-count;
}


int main(){
    int n = size_n("kosti.txt");
    int x[n];
    arr_x(x,"kosti.txt");
    cout<<"number_of_schemes = "<<number_of_schemes(x,n);
    getchar();
}
