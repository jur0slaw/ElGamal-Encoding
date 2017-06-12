#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

struct pojemnik{
    int czynnik;
    int krotnosc;
};

struct zapis{
    pojemnik tab[256];
    int ilosc = 0;

    void dodaj(int x){
        int i=0;
        while(i<ilosc){
            if(x==tab[i].czynnik){
                tab[i].krotnosc++;
                break;
            }
            i++;
        }
        if(i==ilosc){
            tab[ilosc].czynnik=x;
            tab[ilosc].krotnosc=1;
            ilosc++;
        }

    }
    void wypisz_czynniki(){
        cout << "(";
        for(int i=0;i<ilosc;i++){
            cout << tab[i].czynnik;
            if(i!=ilosc-1){
                cout << ",";
            }
        }
        cout << ")";
    }
    void wypisz_krotnosci(){
        cout << "(";
        for(int i=0;i<ilosc;i++){
            cout << tab[i].krotnosc;
            if(i!=ilosc-1){
                cout << ",";
            }
        }
        cout << ")";
    }
};

void faktoryzacja(int d,zapis &foo){
    double y;
    double x = floor(sqrt(d));
    if(x==sqrt(d)){
        faktoryzacja((int)x,foo);
        faktoryzacja((int)x,foo);
    }else{
        x++;
        while(x<(d+1)/2){
            y=x*x-d;
            if(y>0 and sqrt(y)==floor((sqrt(y)))){
                int a,b;
                a = x+sqrt(y);
                b = x-sqrt(y);
                faktoryzacja(a,foo);
                faktoryzacja(b,foo);
                break;
            }else{
                x++;
            }
        }
        if(x>=(d+1)/2){
            foo.dodaj(d);
        }
    }
}

int potegowanie_modulo(int wykladnik, int podstawa, int modulo){

    long int temp = wykladnik;
    int wykladnik_bin[64];
    memset(wykladnik_bin,0,64*sizeof(int));

    int i=0;
    while(temp>0){
        wykladnik_bin[63-i]=temp%2;
        temp=temp/2;
        i++;
    }

    i = 0;
    while(wykladnik_bin[i]==0){
        i++;
    }

    int pierwszy_adres=i;
    int potegi_modulo[64];
    potegi_modulo[63]=podstawa%modulo;

    for(i=62;i>=pierwszy_adres;i--){
        potegi_modulo[i]=(potegi_modulo[i+1]*potegi_modulo[i+1])%modulo;

    }
    long int wynik=1;

    for(i=pierwszy_adres;i<64;i++){
        if(wykladnik_bin[i]==1){
            wynik=(wynik*potegi_modulo[i])%modulo;
        }
    }
    return wynik;
}

bool sprawdzenie_pierwszosci(int zakres){


    int podloga = floor(sqrt(zakres));

    //generacja tablicy liczb naturalnych

    int tab[zakres+1];

    for(int i = 1 ;i < zakres+1; i++){
        tab[i]=1;
    }

    int j;

    for(int i = 2; i<podloga;i++){
        if(tab[i]!=0){
            j=i+i;
            while(j<=zakres){
                tab[j]=0;
                j+=i;
            }
        }
    }
    if(tab[zakres]==1){
        return true;
    }else return false;
}

int main()
{
    zapis foo;

    int a;
    int d;
    int n;
    cout << "Podaj liczbe wejsciowa pierwsza n:" << endl;
    cin >> n ;


    while(!sprawdzenie_pierwszosci(n)){
        cout << "Liczba n nie jest pierwsza. Wprowadz ponownie: " << endl;
        cin >> n;
    }

    a = n-1;
    d=a;

    while(d%2==0){
        d/=2;
        foo.dodaj(2);
    }

    if(d>1){
        faktoryzacja(d,foo);
    }



    a++;
    int q;
    int flag=0;

    cout << endl << endl << "Podaj liczbe r bedaca pierwiastkiem pierwotnym n (1<r<n-1): " << endl;

    cin >> q;

    if((potegowanie_modulo(a,q,n)==1)){
       flag = 1;
    }

    cout << q << "^" << a << " = " << potegowanie_modulo(a,q,n) << "(mod " << n << ")" << endl;

    for(int i=0;i<foo.ilosc;i++){
      // cout << q << "^" << a << "/" << foo.tab[i].czynnik << " = " << potegowanie_modulo((a)/foo.tab[i].czynnik,q,n) << "(mod " << n << ")" << endl;
        if((potegowanie_modulo((a)/foo.tab[i].czynnik,q,n)==1)){
            flag = 1;
        }
    }


    if(flag==1){
       cout << "Liczba " << q << "nie jest pierwiastkiem pierwotnym.";
       return 1;

    }

    int k;

    cout << "Wprowadz liczbe k (1<k<n-1)" << endl;

    cin >> k;

    int klucz_a = potegowanie_modulo(k,q,n);

    int t;

    cout << "Wprowadz tekst t:" << endl;

    cin >> t;

    cout << "Wprowadz 'losowa' liczbe j:" << endl;

    int j;

    cin >> j;

    int c1,c2;

    c1 = potegowanie_modulo(j,q,n);
    c2 = (t*potegowanie_modulo(j,klucz_a,n))%n;

    cout << "Klucz publiczny to: (" << n << "," << q << "," << klucz_a << ")" << endl;
    cout << "Klucz prywatny to: (" << n << "," << q << "," << klucz_a << "," << k << ")" << endl;
    cout << "Szyfrogram to: (" << c1 << "," << c2 << ")" << endl;

    int t_odszyfrowany = (c2*potegowanie_modulo(n-1-k,c1,n))%n;

    cout << "Odszyfrowany tekst to: " << t_odszyfrowany;

    return 0;
}
