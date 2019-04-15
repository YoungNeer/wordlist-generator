#include <iostream>
#include <cmath>
using namespace std;


class shorthand{
    public:
        int noi,len;//noofinstances
        char sign;//%$#
        string range,calc;//string of repeated character of range[0]
        int noOfInstances(string s,char c){
            /*This function will return no of instances of c in string s*/
            int j=0;
            for (int i=0;i<s.length();++i){
                if (s[i]==c){
                ++j;
                }
            }
            return j;
        }
        shorthand(string s,string r,char c){
            sign=c;
            len=r.length();
            noi=noOfInstances(s,sign);
            range=r;
            calc=string(noi,range[0]);
        }
        
};


int valueAt(char source,string check){
  int val=-1;
  for (int i=0;check[i]!='\0';++i)
    if (source==check[i]){
      val=i;
      break;}
  return val;
}

inline void increment(char &c,string r){
  c=r[valueAt(c,r)+1];
}

void loop(int i,string &str,int len,string range){
  if (i!=0){
    str[i]=range[0]-1;
    //why not range[0], (i tried it before) because we have to increment it later, 
    //so it would be incremented to range[1] which we dont want
    if (i!=len)
      increment(str[i],range);
    if (str[i-1]!=range[range.length()-1]){
      increment(str[i-1],range);
    }
    else
      loop(i-1,str,len,range);
  }
}

string println (string &str,int len,string range){
  if (str[len]==range[range.length()-1])
    loop(len,str,len,range);
  increment(str[len],range);
  return str;
}

string reformString(string s,char c,string b){
    /*Reforms string s replacing each character c in s with i,i+1,(upto nth instance) of b
      Example- reform("abcd##,hash.sign,"12") will give you abcd12*/
    int j=0;
    for (int i=0;i<s.length();++i)
        if(s[i]==c)
            s[i]=b[j++];
    return s;
}

int ipow(int n,int times){
    if (times==0)
        return 1;
    else
        return pow(n,times);
}
bool containSChar(string s){
    //checks if string s contains standard character i.e., alpha,numberic or @#!$%&*
    bool b=true;
    for (int i=0;i<s.length();++i)
        if (s[i]>=32&&s[i]<=126);
        else{
            b=false;
            break;}
    return b;

}
void queryPrint(string query){
    shorthand hash(query, "0123456789",'#'),perc(query,"abcdefghijklmnopqrstuvwxyz",'%'),dollar(query,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",'$');
    string str=reformString(query,dollar.sign,dollar.calc);
    str=reformString(str,perc.sign,perc.calc);
    cout<<reformString(str,hash.sign,hash.calc)<<endl;
    for (int jp=0;jp<ipow(perc.len,perc.noi);++jp,dollar.calc=string(dollar.noi,dollar.range[0])){
        for (int jd=0;jd<ipow(dollar.len,dollar.noi);++jd,hash.calc=string(hash.noi,hash.range[0])){
            for (int jh=1;jh<pow(hash.len,hash.noi);++jh){
                cout<<reformString(str,hash.sign,println(hash.calc,hash.noi-1,hash.range))<<endl;
            }
            if (dollar.noi!=0&&jd!=pow(dollar.len,dollar.noi)-1){
                str=reformString(query,dollar.sign,println(dollar.calc,dollar.noi-1,dollar.range));
                str=reformString(str,perc.sign,perc.calc);
                cout<<reformString(str,hash.sign,string(hash.noi,hash.range[0]))<<endl;
            }
        }
        if (perc.noi!=0&&jp!=pow(perc.len,perc.noi)-1){
            str=reformString(query,perc.sign,println(perc.calc,perc.noi-1,perc.range));
            cout<<reformString(reformString(str,hash.sign,string(hash.noi,hash.range[0])),dollar.sign,string(dollar.noi,dollar.range[0]))<<endl; 
        }
    }
}

int main(){
    string query;
    cin>>query;
    cout<<containSChar(query);
    
    //queryPrint(query);
}