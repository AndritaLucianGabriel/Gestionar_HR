#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <typeinfo>
#include <list>
#include <exception>

using namespace std;

///
class Angajat
{
protected:
    string nume;
    string data_angajare;
    double salariu;
    bool manager;
    int man_ang;
    string *nume_man_ang;
    string functie;
public:
    Angajat(string, string, double, bool, int, string*, string);
    Angajat(const Angajat&);
    virtual ~Angajat();

    string get_nume(){return nume;}
    double get_salariu(){return salariu;}
    bool get_manager(){return manager;}
    int get_man_ang(){return man_ang;}
    string get_nume_man_ang(int j){return nume_man_ang[j];}

    void set_salariu(double salariu){this->salariu=salariu;}

    int diferite_comp(Angajat&){return 1;}
    void diminuare(){this->salariu=this->salariu-(16*this->salariu/100);}

    Angajat& operator=(const Angajat&);
    virtual void citire(istream&);
    friend istream& operator>>(istream&, Angajat&);
    virtual void afisare(ostream&);
    friend ostream& operator<<(ostream&, Angajat&);
};

//constructor cu paramentrii impliciti
Angajat::Angajat(string nume="", string data_angajare="", double salariu=0, bool manager=0, int man_ang=0, string* nume_man_ang=NULL, string functie="")
{
    this->nume=nume;
    this->data_angajare=data_angajare;
    this->salariu=salariu;
    this->manager=manager;
    this->man_ang=man_ang;
    try
    {
        this->nume_man_ang=new string[man_ang];
        for(int i=0;i<man_ang;i++)
            if(nume_man_ang[i]==this->nume)
                throw(2);
            else
                this->nume_man_ang[i]=nume_man_ang[i];
        this->functie=functie;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"\t\t\tWARNING!\t Am vazut ca numele unui angajat din lista de subordonati coincide cu cel curent\n";
            exit(0);
    }
}

//constructor pentru copiere
Angajat::Angajat(const Angajat& z)
{
    this->nume=z.nume;
    this->data_angajare=z.data_angajare;
    this->salariu=z.salariu;
    this->manager=z.manager;
    this->man_ang=z.man_ang;
    try
    {
        this->nume_man_ang=new string[z.man_ang];
        for(int i=0;i<man_ang;i++)
            this->nume_man_ang[i]=z.nume_man_ang[i];
        this->functie=z.functie;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//destructor
Angajat::~Angajat()
{
    this->nume="";
    this->data_angajare="";
    this->salariu=0;
    this->manager=0;
    this->man_ang=0;
    delete []this->nume_man_ang;
    this->functie="";
}

//supraincarcarea operatorului=
Angajat& Angajat::operator=(const Angajat& z)
{
    this->nume=z.nume;
    this->data_angajare=z.data_angajare;
    this->salariu=z.salariu;
    this->manager=z.manager;
    this->man_ang=z.man_ang;
    try
    {
        this->nume_man_ang=new string[z.man_ang];
        for(int i=0;i<man_ang;i++)
            this->nume_man_ang[i]=z.nume_man_ang[i];
        this->functie=z.functie;

    return *this;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

void Angajat::citire(istream& in)
{
    string meh;
    cout<<"\n\t\tIntroduceti numele angajatului: ";
    getline(in,this->nume);
    cout<<"\t\tIntroduceti data angajarii: ";
    getline(in,this->data_angajare);
    cout<<"\t\tIntroduceti salariul: ";
    in>>this->salariu;
    cout<<"\t\tIntroduceti daca este manager sau nu (bool): ";
    in>>this->manager;
    in.get();
    if(this->manager==0)
    {
        cout<<"\t\tIntroduceti functia: ";
        getline(in,this->functie);
    }
    else
    {
        cout<<"\t\t\tIntroduceti numarul de angajati coordonati de "<<this->nume<<": ";
        in>>this->man_ang;
        try
        {
            this->nume_man_ang=new string[man_ang];
            in.get();
            if(man_ang==1)
            {
                cout<<"\t\t\tIntroduceti numele angajatului: ";
                getline(in,meh);
                if(meh!=this->nume)
                    this->nume_man_ang[0]=meh;
                else
                {
                    cout<<"\t\t\tWARNING!\t Am vazut ca e identic numele, hai ia-o de la capat :)\n";
                    exit(0);
                }
            }
            else
            {
                for(int i=0;i<man_ang;i++)
                {
                    cout<<"\t\t\tIntroduceti numele angajatului cu nr "<<i+1<<": ";
                    getline(in,meh);
                    if(meh!=this->nume)
                        this->nume_man_ang[i]=meh;
                    else
                    {
                        cout<<"\t\t\tWARNING!\t Am vazut ca e identic numele, hai ia-o de la capat :)\n";
                        exit(0);
                    }
                }
            }
        }
        catch(bad_alloc var)
        {
            cout<<"Allocation Failure\n";
            exit(EXIT_FAILURE);
        }
    }
}

istream& operator>>(istream& in, Angajat& z)
{
    z.citire(in);
    return in;
}

void Angajat::afisare(ostream& out)
{
    if(this->nume=="")
        out<<"\t\tAngajatul nu exista\n";
    else
    {
        out<<"\t\t"<<this->nume<<" a fost angajat la data de "<<this->data_angajare;
        if(this->manager!=0)
        {
            out<<" cu functia de 'Manager' avand salariul de "<<this->salariu<<" lei\n";
            if(man_ang!=1)
            {
                out<<"\t\t\tCei "<<this->man_ang<<" angajati coordonati de "<<this->nume<<" sunt: ";
                for(int i=0;i<man_ang-1;i++)
                    out<<this->nume_man_ang[i]<<", ";
                out<<this->nume_man_ang[man_ang-1]<<"\n";
            }
            else
            {
                out<<"\t\t\tAngajatul coordonat de "<<this->nume<<" este: ";
                out<<this->nume_man_ang[0]<<endl;
            }
        }
        else
            out<<" cu functia de '"<<this->functie<<"' avand salariul de "<<this->salariu<<" lei\n";
    }
}
ostream& operator<<(ostream& out, Angajat& z)
{
    z.afisare(out);
    return out;
}

///
class Departament:public Angajat
{
protected:
    string nume_dep;
    int nr_ang;
    Angajat *ang;
public:
    void verif_man_ang(string*, int&);

    Departament(string, int, Angajat*);
    Departament(const Departament&);
    ~Departament();

    string get_nume_dep(){return nume_dep;}
    int get_nr_ang(){return nr_ang;}

    int diferite_dep(Departament&);
    int sterge_angj(string);
    void adauga_angj(Angajat);
    //functia ce calculeaza cheltuielile salariale ale departamentului curent
    double cheltuieli_salariale(){double sum=0;for(int i=0;i<nr_ang;i++) sum+=ang[i].get_salariu();return sum;}
    //functie ce afiseaza toti managerii
    void lista_man(){for(int i=0;i<nr_ang;i++)if(ang[i].get_manager()==1)cout<<ang[i];}
    //functie ce faciliteaza aplicarea discountului (cerinta B) diminuand fiecare salariu cu 16%
    void diminuare(){for(int i=0;i<nr_ang;i++)ang[i].set_salariu(ang[i].get_salariu()-(16*ang[i].get_salariu()/100));}
    //functie test cu rol de exemplificare al dynamic cast-ului
    void verif_dyn_cast(){cout<<"Sunt in clasa Departament\n";}

    Departament& operator=(const Departament&);
    friend Departament& operator+(Departament&, Departament&);

    void citire(istream&);
    friend istream& operator>>(istream&, Departament&);
    void afisare(ostream&);
    friend ostream& operator<<(ostream&, Departament&);
};

//functie ce verifica faptul ca numele unui manager nu se afla in lista de angajati subordonati de acesta
void Departament::verif_man_ang(string *nume_ang_f, int &poz1)
{
    try
    {
        string **nume_ang=new string*[nr_ang];
        int poz=0;
        int v[nr_ang];
        for(int i=0;i<nr_ang;i++)//aici aflu lista de angajati pentru fiecare manager
        {
            if(ang[i].get_manager()==1)
            {
                nume_ang[poz]=new string[ang[i].get_man_ang()];
                v[poz]=i;
                for(int j=0;j<ang[i].get_man_ang();j++)
                {
                    nume_ang[poz][j]=ang[i].get_nume_man_ang(j);;
                }
                poz++;
            }
        }

        for(int i=0;i<poz;i++)//aici verific diferentele dintre nume
        {
            for(int j=0;j<ang[v[i]].get_man_ang();j++)
            {
                for(int p=i+1;p<poz;p++)
                {
                    for(int k=0;k<ang[v[i+1]].get_man_ang();k++)
                    {
                        if(nume_ang[i][j]==nume_ang[p][k])
                        {
                            int avem=0;
                            for(int t=0;t<poz1;t++)
                            {
                                if(nume_ang_f[t]==nume_ang[i][j])
                                    avem++;
                            }
                            if(avem==0)
                            {
                                nume_ang_f[poz1]=nume_ang[i][j];
                                poz1++;
                            }
                        }
                    }
                }
            }
        }
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//constructor cu parametrii impliciti
Departament::Departament(string nume_dep="", int nr_ang=0, Angajat* ang=NULL)
{
    this->nume_dep=nume_dep;
    this->nr_ang=nr_ang;
    try
    {
        this->ang=new Angajat[nr_ang];
            for(int i=0;i<nr_ang;i++)
        this->ang[i]=ang[i];
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//constructor pentru copiere
Departament::Departament(const Departament& z)
{
    this->nume_dep=z.nume_dep;
    this->nr_ang=z.nr_ang;
    try
    {
        this->ang=new Angajat[z.nr_ang];
            for(int i=0;i<nr_ang;i++)
        this->ang[i]=z.ang[i];
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//destructor
Departament::~Departament()
{
    this->nume_dep="";
    this->nr_ang=0;
    delete []this->ang;
}

//functie ce va fi folosita pentru determinarea diferentelor dintre un departament curent si unul dat
//prin parametru (o sa fie folosita in template)
int Departament::diferite_dep(Departament &z)
{
    int exista_dep=0;
    int exista_ang=0;
    if(this->nume_dep==z.nume_dep&&this->nr_ang==z.nr_ang)
    {
        for(int i=0;i<this->nr_ang;i++)
        {
            for(int j=0;j<z.nr_ang;j++)
            {
                if(this->ang[i].get_nume()==z.ang[j].get_nume())
                    exista_ang++;
            }
        }
        if(exista_ang==nr_ang)
            exista_dep++;
    }
    return exista_dep;
}

//functie ce sterge un angajat cerut din departamentul curent
int Departament::sterge_angj(string z)
{
    int gasit=0;
    for(int i=0;i<nr_ang;i++)
    {
        if(this->ang[i].get_nume()==z)
        {
            gasit++;
            if(this->nr_ang==1)
                this->ang=NULL;
            else
            {
                for(int j=i+1;j<nr_ang;j++)
                {
                    this->ang[i]=this->ang[j];
                }
            }
            nr_ang--;
        }
    }
    return gasit;
}

//functie ce adauga un angajat in departamentul curent
void Departament::adauga_angj(Angajat angj)
{
    int i;
    Angajat copie[this->nr_ang+1];
    for(i=0;i<this->nr_ang;i++)
        copie[i]=this->ang[i];
    copie[i]=angj;
    this->nr_ang++;
    this->ang=new Angajat[this->nr_ang];
    for(int i=0;i<this->nr_ang;i++)
        this->ang[i]=copie[i];
}

//supraincarcarea operatorului=
Departament& Departament::operator=(const Departament& z)
{
    this->nume_dep=z.nume_dep;
    this->nr_ang=z.nr_ang;
    try
    {
        this->ang=new Angajat[z.nr_ang];
        for(int i=0;i<nr_ang;i++)
            this->ang[i]=z.ang[i];
        return *this;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//se va folosi in operator+ din clasa Companie (aici stim deja ca au acelasi nume)
//functie ce faciliteaza fuzionarea a doua companii (va fi folosita in template)
Departament& operator+(Departament& a, Departament&b)
{
    try
    {
        int poz=0;
        Departament *c=new Departament;
        c->nume_dep=a.nume_dep;
        c->nr_ang=a.nr_ang+b.nr_ang;
        c->ang=new Angajat[c->nr_ang];
        for(int i=0;i<a.nr_ang;i++)
        {
            c->ang[poz]=a.ang[i];
            poz++;
        }
        for(int i=0;i<b.nr_ang;i++)
        {
            c->ang[poz]=b.ang[i];
            poz++;
        }
        return *c;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

void Departament::citire(istream& in)
{
    cout<<"\n\tIntroduceti numele departamentului: ";
    getline(in,this->nume_dep);
    cout<<"\tIntroduceti numarul de angajati: ";
    in>>this->nr_ang;
    in.get();
    try
    {
        this->ang=new Angajat[nr_ang];
        for(int i=0;i<nr_ang;i++)
            ang[i].citire(in);
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

istream& operator>>(istream& in, Departament& z)
{
    z.citire(in);
    return in;
}

void Departament::afisare(ostream& out)
{

    if(this->nume_dep=="")
        out<<"\n\tDepartamentul nu exista\n";
    else
        if(this->nr_ang==0)
            out<<"\n\tDepartamentul '"<<this->nume_dep<<"' nu are angajati\n";
        else
        {
            out<<"\n\tIn departamentul '"<<this->nume_dep<<"' lucreaza "<<this->nr_ang<<" de angajati:\n\n";

            string nume_ang[nr_ang]={""};
            int poz1=0;
            int afis[nr_ang]={0};
            verif_man_ang(nume_ang, poz1);
            for(int i=0;i<nr_ang;i++)
            {
                for(int j=0;j<poz1;j++)
                {
                    if(nume_ang[j]==ang[i].get_nume())
                        afis[i]++;
                }
                if(afis[i]!=0)
                    out<<"\t\tWARNING!\t"<<ang[i].get_nume()<<" are mai multi manageri!\n";
                else
                {
                    ang[i].afisare(out);
                    afis[i]++;
                }
            }
        }
}

ostream& operator<<(ostream& out, Departament& z)
{
    z.afisare(out);
    return out;
}

///
class Companie:public Departament
{
protected:
    string nume_comp;
    int nr_dep;
    Departament *dep;
public:
    Companie(string, int, Departament*);
    Companie(const Companie&);
    ~Companie();

    //seteri ce ma vor ajuta in principiu la supraincarcarea operatorului+ in clasa Companie_disc
    void set_nume_comp(string nume_comp){this->nume_comp=nume_comp;}
    void set_nr_dep(int nr_dep){this->nr_dep=nr_dep;}
    void set_dep_elem(int i, Departament &x){this->dep[i]=x;}
    void set_dep_dim(int i){this->dep=new Departament[i];}

    int get_nr_dep(){return nr_dep;}
    //functie ce returneaza numarul de angajati din cadrul companiei curente
    int get_nr_ang(){int sum=0;for(int i=0;i<nr_dep;i++)sum+=dep[i].get_nr_ang();return sum;}
    string get_nume_comp(){return nume_comp;}
    Departament get_dep(int i){return this->dep[i];}
    //am avut nevoie de un getter cu referinta atunci cand aplicam supraincarcarea operatorului+ in clasa Departament
    Departament& get_dep_ref(int i){return dep[i];}

    //chiar nu mi am dat seama cum se la integrez si p.astea mai decent
    void lipsa_inspiratie()const{cout<<"Hai ca am si functie constanta\n";}
    void verif_dyn_cast(){cout<<"Sunt in clasa Companie\n";}

    int diferite_comp(Companie);
    int sterge_angj(string);
    int adauga_angj(Angajat, string);
    int sterge_dept(string);
    int adauga_dept(Departament);
    //continuarea functiilor cu acelasi nume din clasa Departament, dar la nivel de Companie
    double cheltuieli_salariale(){double sum=0;for(int i=0;i<nr_dep;i++)sum+=dep[i].cheltuieli_salariale();return sum;}
    void lista_man(){for(int i=0;i<nr_dep;i++)dep[i].lista_man();}
    //functie ce returneaza numele fiecarui departament din cadrul unei companii
    void lista_dep(int n){for(int i=0;i<nr_dep;i++)if(dep[i].get_nr_ang()>=n)cout<<"'"<<dep[i].get_nume_dep()<<"' ";}

    Companie& operator=(const Companie&);
    friend Companie& operator+(Companie&, Companie&);

    void citire(istream&);
    friend istream& operator>>(istream&, Companie&);
    void afisare(ostream&);
    friend ostream& operator<<(ostream&, Companie&);
};

//constructor cu parametrii impliciti
Companie::Companie(string nume_comp="", int nr_dep=0, Departament* dep=NULL)
{
    this->nume_comp=nume_comp;
    this->nr_dep=nr_dep;
    try
    {
        this->dep=new Departament[nr_dep];
        for(int i=0;i<nr_dep;i++)
            this->dep[i]=dep[i];
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//constructor de copiere
Companie::Companie(const Companie& z)
{
    this->nume_comp=z.nume_comp;
    this->nr_dep=z.nr_dep;
    try
    {
        this->dep=new Departament[z.nr_dep];
        for(int i=0;i<nr_dep;i++)
            this->dep[i]=z.dep[i];
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//destructor
Companie::~Companie()
{
    this->nume_comp="";
    this->nr_dep=0;
    delete []this->dep;
}

//functie ce verifica diferentele dintre compania curenta si una primita ca parametru
int Companie::diferite_comp(Companie z)
{
    int exista_comp=0;
    int exista_dep=0;
    if(this->nume_comp==z.nume_comp&&this->nr_dep==z.nr_dep)
    {
        for(int i=0;i<this->nr_dep;i++)
        {
            for(int j=0;j<this->nr_dep;j++)
            {
                if(this->dep[i].diferite_dep(z.dep[j])==1)
                    exista_dep++;
            }
        }
        if(exista_dep==this->nr_dep)
            exista_comp++;
    }
    return exista_comp;
}

//functie ce faciliteaza stergerea unui angajat primit ca parametru
int Companie::sterge_angj(string angj)
{
    int gasit=0;
    for(int i=0;i<nr_dep;i++)
        if(this->dep[i].sterge_angj(angj)==1)
            gasit++;
    return gasit;
}

//functie ce faciliteaza adaugarea unui angajat primit ca parametru
int Companie::adauga_angj(Angajat angj, string dept)
{
    int gasit=0;
    for(int i=0;i<nr_dep;i++)
    {
        if(this->dep[i].get_nume_dep()==dept)
        {
            gasit++;
            this->dep[i].adauga_angj(angj);
        }
    }
    return gasit;
}

//functie ce faciliteaza stergerea unui departament primit ca parametru
int Companie::sterge_dept(string dept)
{
    int gasit=0;
    for(int i=0;i<nr_dep;i++)
    {
        if(this->dep[i].get_nume_dep()==dept)
        {
            gasit++;
            if(this->nr_dep==1)
                this->dep=NULL;
            else
            {
                for(int j=i+1;j<nr_dep;j++)
                {
                    this->dep[i]=this->dep[j];
                }
            }
            nr_dep--;
        }
    }
    return gasit;
}

//functie ce faciliteaza adaugarea unui departament primit ca parametru
int Companie::adauga_dept(Departament dept)
{
    int gasit=0;
    for(int i=0;i<nr_dep;i++)
        if(this->dep[i].get_nume_dep()==dept.get_nume_dep())
            gasit++;
    if(gasit==0)
    {
        int i;
        Departament copie[this->nr_dep+1];
        for(i=0;i<this->nr_dep;i++)
            copie[i]=this->dep[i];
        copie[i]=dept;
        this->nr_dep++;
        this->dep=new Departament[this->nr_dep];
        for(int i=0;i<this->nr_dep;i++)
            this->dep[i]=copie[i];
    }
    return gasit;
}

//supraincarcarea operatorului=
Companie& Companie::operator=(const Companie& z)
{
    this->nume_comp=z.nume_comp;
    this->nr_dep=z.nr_dep;
    try
    {
        this->dep=new Departament[z.nr_dep];
        for(int i=0;i<nr_dep;i++)
            this->dep[i]=z.dep[i];
        return *this;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

//supraincarcarea operatorului+
Companie& operator+(Companie& a, Companie& b)
{
    try
    {
        Companie *c=new Companie;
        Departament copie[a.nr_dep+b.nr_dep];
        c->nume_comp=a.nume_comp;
        int nr_dep_local=0;
        for(int i=0;i<a.nr_dep;i++)
        {
            for(int j=0;j<b.nr_dep;j++)
            {
                if(a.dep[i].get_nume_dep()==b.dep[j].get_nume_dep())
                {
                    copie[nr_dep_local]=b.dep[j];
                    nr_dep_local++;
                }
            }
        }
        int poz=0;
        int apare;
        c->nr_dep=(a.nr_dep+b.nr_dep)-nr_dep_local;
        c->dep=new Departament[c->nr_dep];
        for(int i=0;i<a.nr_dep;i++)
        {
            apare=0;
            for(int j=0;j<nr_dep_local;j++)
            {
                if(a.dep[i].get_nume_dep()==copie[j].get_nume_dep())
                {
                    c->dep[poz]=a.dep[i]+copie[j];
                    poz++;
                    apare++;
                }
            }
            if(apare==0)
            {
                c->dep[poz]=a.dep[i];
                poz++;
            }
        }
        for(int i=0;i<b.nr_dep;i++)
        {
            apare=0;
            for(int j=0;j<nr_dep_local;j++)
            {
                if(b.dep[i].get_nume_dep()==copie[j].get_nume_dep())
                {
                    apare++;
                }
            }
            if(apare==0)
            {
                c->dep[poz]=b.dep[i];
                poz++;
            }
        }

        return *c;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

void Companie::citire(istream& in)
{
    cout<<"\nIntroduceti numele companiei: ";
    getline(in,this->nume_comp);
    cout<<"Introduceti numarul de departamente: ";
    in>>this->nr_dep;
    in.get();
    try
    {
        this->dep=new Departament[nr_dep];
        for(int i=0;i<nr_dep;i++)
            dep[i].citire(in);
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

istream& operator>>(istream& in, Companie& z)
{
    z.citire(in);
    return in;
}

void Companie::afisare(ostream& out)
{
    cout<<endl;
    if(this->nume_comp=="")
        out<<"Compania nu exista\n";
    else
    if(this->nr_dep==0)
        out<<"Compania "<<this->nume_comp<<" nu are departamente\n";
    else
    {
        if(this->nr_dep>1)
        {
            out<<"Compania se numeste '"<<this->nume_comp<<"' si are "<<this->nr_dep<<" departamente\n";
            for(int i=0;i<nr_dep;i++)
                dep[i].afisare(out);
        }
        else
        {
            out<<"Compania se numeste '"<<this->nume_comp<<"' si are un departament\n";
            dep[0].afisare(out);
        }

    }
}

ostream& operator<<(ostream& out, Companie& z)
{
    z.afisare(out);
    return out;
}

///
class Companie_disc:public Companie
{
public:
    //functie ce mi apeleaza diminuare() din fiecare departament reprezentand discountul de 16%
    void diminuare();
    //am avut nevoie de citire si constructor nou pentru a aplica diminuare
    Companie_disc(string, int, Departament*);
    void citire(istream&);
};

void Companie_disc::diminuare()
{
    for(int i=0;i<nr_dep;i++)
        dep[i].diminuare();
}

Companie_disc::Companie_disc(string nume_comp="", int nr_dep=0, Departament* dep=NULL):Companie(nume_comp, nr_dep, dep)
{
    this->diminuare();
}

//asta a fost o durere
//practic e aceeasi supraincarcare din Companie, doar ca folosesc setteri si getteri
Companie_disc& operator+(Companie_disc& a, Companie_disc& b)
{
    try
    {
        Companie_disc *c=new Companie_disc;
        Departament copie[a.get_nr_dep()+b.get_nr_dep()];
        Departament nou;
        c->set_nume_comp(a.get_nume_comp());
        int nr_dep_local=0;
        for(int i=0;i<a.get_nr_dep();i++)
        {
            for(int j=0;j<b.get_nr_dep();j++)
            {
                if(a.get_dep(i).get_nume_dep()==b.get_dep(j).get_nume_dep())
                {
                    copie[nr_dep_local]=b.get_dep(j);
                    nr_dep_local++;
                }
            }
        }
        int poz=0;
        int apare;
        c->set_nr_dep((a.get_nr_dep()+b.get_nr_dep())-nr_dep_local);
        c->set_dep_dim(c->get_nr_dep());
        for(int i=0;i<a.get_nr_dep();i++)
        {
            apare=0;
            for(int j=0;j<nr_dep_local;j++)
            {
                if(a.get_dep(i).get_nume_dep()==copie[j].get_nume_dep())
                {
                    c->set_dep_elem(poz,a.get_dep_ref(i)+copie[j]);
                    poz++;
                    apare++;
                }
            }
            if(apare==0)
            {
                c->set_dep_elem(poz,a.get_dep_ref(i));
                poz++;
            }
        }
        for(int i=0;i<b.get_nr_dep();i++)
        {
            apare=0;
            for(int j=0;j<nr_dep_local;j++)
            {
                if(b.get_dep(i).get_nume_dep()==copie[j].get_nume_dep())
                {
                    apare++;
                }
            }
            if(apare==0)
            {
                c->set_dep_elem(poz,b.get_dep_ref(i));
                poz++;
            }
        }

        return *c;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

void Companie_disc::citire(istream& in)
{
    cout<<"\nIntroduceti numele companiei: ";
    getline(in,this->nume_comp);
    cout<<"Introduceti numarul de departamente: ";
    in>>this->nr_dep;
    in.get();
    try
    {
        this->dep=new Departament[nr_dep];
        for(int i=0;i<nr_dep;i++)
            dep[i].citire(in);
        this->diminuare();
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
}

///
template <class grup> class HRManager
{
private:
    grup *v;
    int nr_grup;
public:
    //am incercat sa l dau private dar nu mi incrementeaza atunci cand declar un nou obiect
    //si doar public am observat ca l recunoaste (de ce?)
    static int numarGrupuri;

    //constructor cu parametrii impliciti
    HRManager(grup *p=NULL, int nr=0)
    {
        nr_grup=nr;
        try
        {
            v=new grup[nr_grup];
            for(int i=0;i<nr_grup;i++)
                v[i]=p[i];
            numarGrupuri++;
        }
        catch(bad_alloc var)
        {
            cout<<"Allocation Failure\n";
            exit(EXIT_FAILURE);
        }
    }

    //constructor de copiere
    HRManager(HRManager& z)
    {
        nr_grup=z.nr_grup;
        try
        {
            v=new grup[nr_grup];
            for(int i=0;i<nr_grup;i++)
                v[i]=z.v[i];
            numarGrupuri++;
        }
        catch(bad_alloc var)
        {
            cout<<"Allocation Failure\n";
            exit(EXIT_FAILURE);
        }
    }

    //destructor
    ~HRManager()
    {
        delete []v;
        nr_grup=0;
    }

    int get_nr_grup(){return nr_grup;}
    grup get_v(int i){return v[i];}

    //folosirea functiei statice (variabila statica unica pe tip de template)
    static int count(){return numarGrupuri;}
    void afisare_count()
    {
        if(HRManager<grup>::count()!=1)
        {
            if(typeid(v)==typeid(Companie*))
                cout<<"Avem "<<HRManager<grup>::count()<<" obiecte de tip Companie\n";
            else
            if(typeid(v)==typeid(Departament*))
                cout<<"Avem "<<HRManager<grup>::count()<<" obiecte de tip Departament\n";
            else
            if(typeid(v)==typeid(Angajat*))
                cout<<"Avem "<<HRManager<grup>::count()<<" obiecte de tip Angajat\n";
            else
                cout<<"Aoleu ati gresit tipul\n";
        }
        else
        {
            if(typeid(v)==typeid(Companie*))
                cout<<"Avem un obiect de tip Companie\n";
            else
            if(typeid(v)==typeid(Departament*))
                cout<<"Avem un obiect de tip Departament\n";
            else
            if(typeid(v)==typeid(Angajat*))
                cout<<"Avem un obiect de tip Angajat\n";
            else
                cout<<"Aoleu ati gresit tipul\n";
        }

    }

    //supraincarcarea operatorului= la nivel de template
    HRManager& operator=(HRManager <grup> &z)
    {
        nr_grup=z.nr_grup;
        try
        {
            v=new grup[nr_grup];
            for(int i=0;i<nr_grup;i++)
                v[i]=z.v[i];

            return *this;
        }
        catch(bad_alloc var)
        {
            cout<<"Allocation Failure\n";
            exit(EXIT_FAILURE);
        }
    }

    friend istream& operator>>(istream& in, HRManager <grup> &p)
    {
        if(typeid(p.v)!=typeid(Companie*))
        {
            cout<<"\nIntroduceti numarul de obiecte: ";
            in>>p.nr_grup;
            in.get();
            try
            {
                p.v=new grup[p.nr_grup];
                for(int i=0;i<p.nr_grup;i++)
                {
                    cout<<"\n\tIntroduceti obiectul cu nr "<<i+1<<"\n\t";
                    in>>p.v[i];
                }
            }
            catch(bad_alloc var)
            {
                cout<<"Allocation Failure\n";
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cout<<"\nIntroduceti numarul de obiecte: ";
            in>>p.nr_grup;
            in.get();
            int n,j;
            int copie_j;
            try
            {
                p.v=new grup[p.nr_grup];
                grup copie;
                int i;
                for(i=0;i<p.nr_grup;i++)
                {
                    n=0;
                    start:
                    {
                        cout<<"\n\tIntroduceti obiectul cu nr "<<i+1<<"\n\t";
                        in>>copie;
                        for(j=0;j<i;j++)
                            if(p.v[j].diferite_comp(copie)==1)
                            {
                                n++;
                                copie_j=j;
                            }
                        if(n==0)
                            p.v[i]=copie;
                        else
                        {
                            while(p.v[copie_j].diferite_comp(copie)==1)
                            {
                                cout<<"\nCompania exista deja! Reintroduceti obiectul!\n";
                                goto start;
                            }
                            p.v[i]=copie;
                        }
                    }
                }
            }
            catch(bad_alloc var)
            {
                cout<<"Allocation Failure\n";
                exit(EXIT_FAILURE);
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, HRManager <grup> &p)
    {
        if(p.nr_grup==1)
            cout<<"\nAvem un obiect:\n";
        else
            cout<<"\nAvem "<<p.nr_grup<<" obiecte:\n";
        for(int i=0;i<p.nr_grup;i++)
            out<<p.v[i]<<"\n";
        return out;
    }

    //fuzionarea a doua companii folosindu-ne de operatorul+ la nivel de Companie
    void fuzionare()
    {
        if(nr_grup<2)
            cout<<"\n\n\t\tWARNING!\tFuzionarea nu are sens! Nu avem suficiente obiecte de tip 'Companie'\n";
        else
        {
            string a, b;
            int poz_a, poz_b;
            cout<<"\n\nIntroduceti ce companii doriti sa fuzionati (a doua va fi asimilata)\n";
            cout<<"Prima: ";
            getline(cin,a);
            cout<<"A doua: ";
            getline(cin,b);
            for(int i=0;i<nr_grup;i++)
            {
                if(v[i].get_nume_comp()==a)
                    poz_a=i;
                else
                    if(v[i].get_nume_comp()==b)
                        poz_b=i;
            }
            v[poz_a]=v[poz_a]+v[poz_b];
            for(int i=poz_b+1;i<nr_grup;i++)
                v[i-1]=v[i];
            nr_grup--;
        }
    }

    //functie ce permite modificarea la nivel de Companie cat si la nivel de grup
    void modificare()
    {
        int opt;
        cout<<"\n\n";
        cout<<"\t1. Introduceti 1 pentru stergere angajat\n";
        cout<<"\t2. Introduceti 2 pentru adaugare angajat\n";
        cout<<"\t3. Introduceti 3 pentru stergere departament\n";
        cout<<"\t4. Introduceti 4 pentru adaugare departament\n";
        cout<<"\t5. Introduceti 5 pentru stergere companie\n";
        cout<<"\t6. Introduceti 6 pentru adaugare companie\n";
        cout<<"\t0. Iesire\n";
        do
        {
            cout<<("\nIntroduceti numarul cerintei: ");
            cin>>opt;
            switch(opt)
            {
                case 0:
                    cout<<"\n\t\tModificarea gestionarului se va termina\n\n\n";
                    system("pause");
                    cout<<"\n\n";
                    break;

                case(1):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tStergere angajat\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de angajati pe care vreti sa-i stergeti: ";
                        cin>>nr;
                        cout<<endl;
                        string angj[nr];
                        cin.get();
                        //Am nevoie de nume doarece o sa am probleme in cazul in care numele departamentelor
                        //sunt generalizate (IT, Financiar etc).
                        if(nr==1)
                        {
                            cout<<"Introduceti numele angajatului: ";
                            getline(cin,angj[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"Introduceti numele angajatului cu nr "<<i+1<<": ";
                                getline(cin,angj[i]);
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].sterge_angj(angj[j])==0)
                                            cout<<"\tAngajatul "<<angj[j]<<" nu exista in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tStergerea angajatului "<<angj[j]<<" a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus angajati\n";
                    }

                    break;
                case(2):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tAdaugare angajat\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de angajati pe care vreti sa-i adaugati: ";
                        cin>>nr;
                        cout<<endl;
                        Angajat angj[nr];
                        string dept[nr];
                        cin.get();
                        //Am nevoie de nume doarece o sa am probleme in cazul in care numele departamentelor
                        //sunt generalizate (IT, Financiar etc).
                        if(nr==1)
                        {
                            cout<<"\nIntroduceti informatiile angajatului: ";
                            cin>>angj[0];
                            cout<<"\t\tIntroduceti departamentul: ";
                            getline(cin,dept[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\nIntroduceti informatiile angajatului cu nr "<<i+1<<": ";
                                cin>>angj[i];
                                cout<<"\t\tIntroduceti departamentul: ";
                                getline(cin,dept[i]);
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].adauga_angj(angj[j],dept[j])==0)
                                            cout<<"\n\tDepartamentul "<<dept[j]<<" nu exista in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tAdaugarea angajatului "<<angj[j].get_nume()<<" in departamentul '"<<dept[j]<<"' a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus angajati\n";
                    }

                    break;
                case(3):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tStergere departamente\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de departamente pe care vreti sa le stergeti: ";
                        cin>>nr;
                        cout<<endl;
                        string dept[nr];
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"Introduceti numele departamentului: ";
                            getline(cin,dept[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"Introduceti numele departamentului cu nr "<<i+1<<": ";
                                getline(cin,dept[i]);
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {

                                        if(v[i].sterge_dept(dept[j])==0)
                                            cout<<"\tDepartamentul '"<<dept[j]<<"' nu exista in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tStergerea departamentului '"<<dept[j]<<"' a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus departamente\n";
                    }

                    break;
                case(4):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tAdaugare departament\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de departamente pe care vreti sa-i adaugati: ";
                        cin>>nr;
                        cout<<endl;
                        Departament dept[nr];
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"\nIntroduceti informatiile departamentului: ";
                            cin>>dept[0];
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\nIntroduceti informatiile departamentului cu nr "<<i+1<<": ";
                                cin>>dept[i];
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].adauga_dept(dept[j])==1)
                                            cout<<"\n\tDepartamentul '"<<dept[j].get_nume_dep()<<"' exista deja in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tAdaugarea deptartamentului '"<<dept[j].get_nume_dep()<<"' a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus departamente\n";
                    }

                    break;
                case(5):
                    {
                        int nr;
                        cout<<"\n\t\t\tStergerea companiilor\n";
                        cout<<"\tIntroduceti numarul de companii pe care vreti sa le stergeti: ";
                        cin>>nr;
                        string comp[nr];
                        int gasit[nr]={0};
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"\nIntroduceti numele companiei: ";
                            getline(cin,comp[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\nIntroduceti numele companiei cu nr "<<i+1<<": ";
                                getline(cin,comp[i]);
                            }
                        if(nr!=0)
                        {
                            for(int j=0;j<nr;j++)
                            {
                                for(int i=0;i<nr_grup;i++)
                                {
                                    if(v[i].get_nume_comp()==comp[j])
                                    {
                                        gasit[j]++;
                                        for(int l=i+1;l<nr_grup;l++)
                                        {
                                            v[i]=v[l];
                                        }
                                        cout<<"\nStergerea companiei "<<comp[0]<<" s-a realizat cu succes\n";
                                        nr_grup--;
                                    }
                                }
                            }
                        }
                        else
                        if(nr==1)
                        {
                            if(v[0].get_nume_comp()==comp[0])
                            {
                                gasit[0]++;
                                v=NULL;
                                nr_grup--;
                                cout<<"\nStergerea companiei "<<comp[0]<<" s-a realizat cu succes\n";
                            }
                        }
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus companii\n";
                        else
                            for(int i=0;i<nr;i++)
                                if(gasit[i]==0)
                                    cout<<"\nCompania "<<comp[i]<<" nu se afla in grup\n";
                    }

                    break;
                case(6):
                    {
                        int nr;
                        cout<<"\n\t\t\tAdaugarea companiilor\n";
                        cout<<"\tIntroduceti numarul de companii pe care vreti sa le adaugati: ";
                        cin>>nr;
                        Companie comp[nr];
                        int gasit[nr]={0};
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"\nIntroduceti informatiile companiei: ";
                            cin>>comp[0];
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\nIntroduceti informatiile companiei cu nr "<<i+1<<": ";
                                cin>>comp[i];
                            }
                        if(nr!=0)
                        {
                            int poz=0;
                            Companie copie[nr_grup+nr];
                            for(int i=0;i<nr_grup;i++)
                            {
                                copie[poz]=v[i];
                                poz++;
                            }
                            for(int i=0;i<nr;i++)
                            {
                                copie[poz]=comp[i];
                                poz++;
                            }
                            for(int i=0;i<nr_grup;i++)
                            {
                                for(int j=0;j<nr;j++)
                                {
                                    if(v[i].get_nume_comp()==comp[j].get_nume_comp())
                                        gasit[j]++;
                                }
                            }
                            int sum=0;
                            for(int i=0;i<nr;i++)
                                if(gasit[i]!=0)
                                    sum++;
                            v=new grup[nr_grup+nr-sum];
                            for(int i=0;i<nr_grup+nr;i++)
                            {
                                if(i>nr_grup&&gasit[i]==0)
                                    v[i]=copie[i];
                                else
                                if(i<=nr_grup)
                                    v[i]=copie[i];
                            }
                            nr_grup=nr_grup+nr-sum;
                            for(int i=0;i<nr;i++)
                            {
                                if(gasit[i]==0)
                                    cout<<"\nAdaugarea companiei "<<comp[i].get_nume_comp()<<" a fost efectuata cu succes\n";
                                else
                                    cout<<"\nCompania "<<comp[i].get_nume_comp()<<" se afla deja in grup\n";
                            }
                        }
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus companii\n";
                    }

                    break;
                default:
                    cout<<"\nSelectie invalida\n";
                    break;
            }
        }
        while(opt!=0);
    }

    //de aici incep functiile de generare de rapoarte prezentate in clasa Companie
    void raport_nr_ang_dep()
    {
        int poz;
        cout<<"\nCarui obiect vreti sa aflati nr de angajati: ";
        cin>>poz;
        poz--;
        if(typeid(v)==typeid(Departament*))
        {
            if(v[poz].get_nr_ang()!=1)
                cout<<"\nDepartamentul '"<<v[poz].get_nume_dep()<<"' are "<<v[poz].get_nr_ang()<<" angajati\n";
            else
                cout<<"\nDepartamentul '"<<v[poz].get_nume_dep()<<"' are un angajat\n";
        }
        else
            cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie'\n";

    }

    void raport_nr_ang_comp()
    {
        int poz;
        cout<<"\nCarui obiect vreti sa aflati nr de angajati: ";
        cin>>poz;
        poz--;
        if(typeid(v)==typeid(Companie*))
        {
            if(v[poz].get_nr_ang()!=1)
                cout<<"\nCompania '"<<v[poz].get_nume_comp()<<"' are "<<v[poz].get_nr_ang()<<" angajati\n";
            else
                cout<<"\nCompania '"<<v[poz].get_nume_comp()<<"' are un angajat\n";
        }
        else
            cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie'\n";
    }

    void cheltuieli_salariale()
    {
        int poz;
        cout<<"\nCarei companii vreti sa aflati cheltuielile salariale lunare: ";
        cin>>poz;
        poz--;
        if(typeid(v)==typeid(Companie*))
        {
            cout<<"\nCompania '"<<v[poz].get_nume_comp()<<"' are cheltuieli salariale lunare in valoare de "<<v[poz].cheltuieli_salariale()<<" lei\n";
        }
        else
            cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie'\n";
    }

    void lista_man()
    {
        int poz;
        cout<<"\nCarei companii vreti sa aflati lista de manageri: ";
        cin>>poz;
        poz--;
        if(typeid(v)==typeid(Companie*))
        {
            cout<<"\nCompania '"<<v[poz].get_nume_comp()<<" are urmatorii manageri: \n";
            v[poz].lista_man();
        }
        else
            cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie'\n";
    }

    //Am interpretat cerinta si am hotarat sa fac minimul pe companie, nu pe grup (imi pare mai logic)
    void min_n_ang()
    {
        int poz,n;
        cout<<"\nCarei companii vreti sa aflati lista departamentelor cu un minim de angajati: ";
        cin>>poz;
        poz--;
        cout<<"Introduceti minim: ";
        cin>>n;
        if(typeid(v)==typeid(Companie*))
        {
            cout<<"\nCompania '"<<v[poz].get_nume_comp()<<" are urmatoarele departamente cu numar minim: ";
            v[poz].lista_dep(n);
        }
        else
            cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie'\n";
    }
};
//GeeksforGeeks :)
template <class grup>
int HRManager <grup>::numarGrupuri = 0;

///
//nu exista o metoda de mostenire ceva intre template ul asta si template ul anterior cand avem obiecte de
//tip Companie? Gen sa fac un cast a lui grup* v la Companie_disc
//explicatiile sunt aceleasi ca mai sus cu mentiunea ca am scos functia raport_nr_ang_dep (explicatie la apel)
template <> class HRManager<Companie_disc>
{
private:
    Companie_disc *v;
    int nr_grup;
public:
    static int numarGrupuri;

    HRManager(Companie_disc *p=NULL, int nr=0)
    {
        nr_grup=nr;
        try
        {
            v=new Companie_disc[nr_grup];
            for(int i=0;i<nr_grup;i++)
                v[i]=p[i];
            numarGrupuri++;
        }
        catch(bad_alloc var)
        {
            cout<<"Allocation Failure\n";
            exit(EXIT_FAILURE);
        }
    }

    HRManager(HRManager& z)
    {
        nr_grup=z.nr_grup;
        try
        {
            v=new Companie_disc[nr_grup];
            for(int i=0;i<nr_grup;i++)
                v[i]=z.v[i];
            numarGrupuri++;
        }
        catch(bad_alloc var)
        {
            cout<<"Allocation Failure\n";
            exit(EXIT_FAILURE);
        }
    }

    ~HRManager()
    {
        delete []v;
        nr_grup=0;
    }

    int get_nr_grup(){return nr_grup;}
    Companie_disc get_v(int i){return v[i];}

    static int count(){return numarGrupuri;}
    void afisare_count()
    {
        if(HRManager<Companie_disc>::count()!=1)
        {
            if(typeid(v)==typeid(Companie_disc*))
                cout<<"Avem "<<HRManager<Companie_disc>::count()<<" obiecte de tip Companie_disc\n";
            else
                cout<<"Aoleu ati gresit tipul\n";
        }
        else
        {
            if(typeid(v)==typeid(Companie_disc*))
                cout<<"Avem un obiect de tip Companie_disc\n";
            else
                cout<<"Aoleu ati gresit tipul\n";
        }

    }

    HRManager& operator=(HRManager <Companie_disc> &z)
    {
        nr_grup=z.nr_grup;
        try
        {
            v=new Companie_disc[nr_grup];
            for(int i=0;i<nr_grup;i++)
                v[i]=z.v[i];

            return *this;
        }
        catch(bad_alloc var)
        {
            cout<<"Allocation Failure\n";
            exit(EXIT_FAILURE);
        }
    }

    friend istream& operator>>(istream& in, HRManager <Companie_disc> &p)
    {
        if(typeid(p.v)!=typeid(Companie_disc*))
        {
            cout<<"\nIntroduceti numarul de obiecte: ";
            in>>p.nr_grup;
            in.get();
            try
            {
                p.v=new Companie_disc[p.nr_grup];
                for(int i=0;i<p.nr_grup;i++)
                {
                    cout<<"\n\tIntroduceti obiectul cu nr "<<i+1<<"\n\t";
                    in>>p.v[i];
                }
            }
            catch(bad_alloc var)
            {
                cout<<"Allocation Failure\n";
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            cout<<"\nIntroduceti numarul de obiecte: ";
            in>>p.nr_grup;
            in.get();
            int n,j;
            int copie_j;
            try
            {
                p.v=new Companie_disc[p.nr_grup];
                Companie_disc copie;
                int i;
                for(i=0;i<p.nr_grup;i++)
                {
                    n=0;
                    start:
                    {
                        cout<<"\n\tIntroduceti obiectul cu nr "<<i+1<<"\n\t";
                        in>>copie;
                        for(j=0;j<i;j++)
                            if(p.v[j].diferite_comp(copie)==1)
                            {
                                n++;
                                copie_j=j;
                            }
                        if(n==0)
                            p.v[i]=copie;
                        else
                        {
                            while(p.v[copie_j].diferite_comp(copie)==1)
                            {
                                cout<<"\nCompania exista deja! Reintroduceti obiectul!\n";
                                goto start;
                            }
                            p.v[i]=copie;
                        }
                    }
                }
            }
            catch(bad_alloc var)
            {
                cout<<"Allocation Failure\n";
                exit(EXIT_FAILURE);
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, HRManager <Companie_disc> &p)
    {
        if(p.nr_grup==1)
            cout<<"\nAvem un obiect:\n";
        else
            cout<<"\nAvem "<<p.nr_grup<<" obiecte:\n";
        for(int i=0;i<p.nr_grup;i++)
            out<<p.v[i]<<"\n";
        return out;
    }

    void fuzionare()
    {
        if(nr_grup<2)
            cout<<"\n\n\t\tWARNING!\tFuzionarea nu are sens! Nu avem suficiente obiecte de tip 'Companie_disc'\n";
        else
        {
            string a, b;
            int poz_a, poz_b;
            cout<<"\n\nIntroduceti ce companii doriti sa fuzionati (a doua va fi asimilata)\n";
            cout<<"Prima: ";
            getline(cin,a);
            cout<<"A doua: ";
            getline(cin,b);
            for(int i=0;i<nr_grup;i++)
            {
                if(v[i].get_nume_comp()==a)
                    poz_a=i;
                else
                    if(v[i].get_nume_comp()==b)
                        poz_b=i;
            }
            v[poz_a]=v[poz_a]+v[poz_b];
            for(int i=poz_b+1;i<nr_grup;i++)
                v[i-1]=v[i];
            nr_grup--;
        }
    }

    void modificare()
    {
        int opt;
        cout<<"\n\n";
        cout<<"\t1. Introduceti 1 pentru stergere angajat\n";
        cout<<"\t2. Introduceti 2 pentru adaugare angajat\n";
        cout<<"\t3. Introduceti 3 pentru stergere departament\n";
        cout<<"\t4. Introduceti 4 pentru adaugare departament\n";
        cout<<"\t5. Introduceti 5 pentru stergere companie\n";
        cout<<"\t6. Introduceti 6 pentru adaugare companie\n";
        cout<<"\t0. Iesire\n";
        do
        {
            cout<<("\nIntroduceti numarul cerintei: ");
            cin>>opt;
            switch(opt)
            {
                case 0:
                    cout<<"\n\t\tModificarea gestionarului se va termina\n\n\n";
                    system("pause");
                    cout<<"\n\n";
                    break;

                case(1):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tStergere angajat\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de angajati pe care vreti sa-i stergeti: ";
                        cin>>nr;
                        cout<<endl;
                        string angj[nr];
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"Introduceti numele angajatului: ";
                            getline(cin,angj[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"Introduceti numele angajatului cu nr "<<i+1<<": ";
                                getline(cin,angj[i]);
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].sterge_angj(angj[j])==0)
                                            cout<<"\tAngajatul "<<angj[j]<<" nu exista in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tStergerea angajatului "<<angj[j]<<" a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus angajati\n";
                    }

                    break;
                case(2):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tAdaugare angajat\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de angajati pe care vreti sa-i adaugati: ";
                        cin>>nr;
                        cout<<endl;
                        Angajat angj[nr];
                        string dept[nr];
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"\nIntroduceti informatiile angajatului: ";
                            cin>>angj[0];
                            angj[0].diminuare();
                            cout<<"\t\tIntroduceti departamentul: ";
                            getline(cin,dept[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\nIntroduceti informatiile angajatului cu nr "<<i+1<<": ";
                                cin>>angj[i];
                                angj[i].diminuare();
                                cout<<"\t\tIntroduceti departamentul: ";
                                getline(cin,dept[i]);
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].adauga_angj(angj[j],dept[j])==0)
                                            cout<<"\n\tDepartamentul "<<dept[j]<<" nu exista in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tAdaugarea angajatului "<<angj[j].get_nume()<<" in departamentul '"<<dept[j]<<"' a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus angajati\n";
                    }

                    break;
                case(3):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tStergere departamente\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de departamente pe care vreti sa le stergeti: ";
                        cin>>nr;
                        cout<<endl;
                        string dept[nr];
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"Introduceti numele departamentului: ";
                            getline(cin,dept[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"Introduceti numele departamentului cu nr "<<i+1<<": ";
                                getline(cin,dept[i]);
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].sterge_dept(dept[j])==0)
                                            cout<<"\tDepartamentul '"<<dept[j]<<"' nu exista in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tStergerea departamentului '"<<dept[j]<<"' a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus departamente\n";
                    }

                    break;
                case(4):
                    {
                        int nr,avem=0;
                        string comp;
                        cout<<"\n\t\t\tAdaugare departament\n";
                        cout<<"\tIntroduceti numele companiei unde modificati: ";
                        cin.get();
                        getline(cin,comp);
                        cout<<"\tIntroduceti numarul de departamente pe care vreti sa-i adaugati: ";
                        cin>>nr;
                        cout<<endl;
                        Departament dept[nr];
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"\nIntroduceti informatiile departamentului: ";
                            cin>>dept[0];
                            dept[0].diminuare();
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\nIntroduceti informatiile departamentului cu nr "<<i+1<<": ";
                                cin>>dept[i];
                                dept[i].diminuare();
                            }
                        if(nr!=0)
                        {
                            for(int i=0;i<nr_grup;i++)
                            {
                                if(v[i].get_nume_comp()==comp)
                                {
                                    avem++;
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].adauga_dept(dept[j])==1)
                                            cout<<"\n\tDepartamentul '"<<dept[j].get_nume_dep()<<"' exista deja in compania "<<comp<<"\n";
                                        else
                                            cout<<"\n\tAdaugarea deptartamentului '"<<dept[j].get_nume_dep()<<"' a avut succes\n";
                                    }
                                }
                            }
                        }
                        if(avem==0&&nr!=0)
                            cout<<"\n\tWARNING!\tCompania introdusa nu exista\n";
                        else
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus departamente\n";
                    }

                    break;
                case(5):
                    {
                        int nr;
                        cout<<"\n\t\t\tStergerea companiilor\n";
                        cout<<"\tIntroduceti numarul de companii pe care vreti sa le stergeti: ";
                        cin>>nr;
                        string comp[nr];
                        int gasit[nr]={0};
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"\nIntroduceti numele companiei: ";
                            getline(cin,comp[0]);
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\nIntroduceti numele companiei cu nr "<<i+1<<": ";
                                getline(cin,comp[i]);
                            }
                        if(nr!=0)
                        {
                            for(int j=0;j<nr;j++)
                            {
                                for(int i=0;i<nr_grup;i++)
                                {
                                    if(v[i].get_nume_comp()==comp[j])
                                    {
                                        gasit[j]++;
                                        for(int l=i+1;l<nr_grup;l++)
                                        {
                                            v[i]=v[l];
                                        }
                                        cout<<"\nStergerea companiei "<<comp[0]<<" s-a realizat cu succes\n";
                                        nr_grup--;
                                    }
                                }
                            }
                        }
                        else
                        if(nr==1)
                        {
                            if(v[0].get_nume_comp()==comp[0])
                            {
                                gasit[0]++;
                                v=NULL;
                                nr_grup--;
                                cout<<"\nStergerea companiei "<<comp[0]<<" s-a realizat cu succes\n";
                            }
                        }
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus companii\n";
                        else
                            //nu am folosit try catch doarece voiam sa afisez ce companii nu s-au gasit,
                            //nu doar prima care nu s-a gasit (explicatia se repeta pentru fiecare case() din
                            //functia modificare())
                            for(int i=0;i<nr;i++)
                                if(gasit[i]==0)
                                    cout<<"\nCompania "<<comp[i]<<" nu se afla in grup\n";
                    }

                    break;
                case(6):
                    {
                        int nr;
                        cout<<"\n\t\t\tAdaugarea companiilor\n";
                        cout<<"\tIntroduceti numarul de companii pe care vreti sa le adaugati: ";
                        cin>>nr;
                        Companie_disc comp[nr];
                        int gasit[nr]={0};
                        cin.get();
                        if(nr==1)
                        {
                            cout<<"\n\tIntroduceti informatiile companiei";
                            cin>>comp[0];
                        }
                        else
                        if(nr>1)
                            for(int i=0;i<nr;i++)
                            {
                                cout<<"\n\tIntroduceti informatiile companiei cu nr "<<i+1;
                                cin>>comp[i];
                            }
                        if(nr!=0)
                        {
                            int poz=0;
                            try
                            {
                                Companie_disc copie[nr_grup+nr];
                                for(int i=0;i<nr_grup;i++)
                                {
                                    copie[poz]=v[i];
                                    poz++;
                                }
                                for(int i=0;i<nr;i++)
                                {
                                    copie[poz]=comp[i];
                                    poz++;
                                }
                                for(int i=0;i<nr_grup;i++)
                                {
                                    for(int j=0;j<nr;j++)
                                    {
                                        if(v[i].get_nume_comp()==comp[j].get_nume_comp())
                                            gasit[j]++;
                                    }
                                }
                                int sum=0;
                                for(int i=0;i<nr;i++)
                                    if(gasit[i]!=0)
                                        sum++;
                                v=new Companie_disc[nr_grup+nr-sum];
                                for(int i=0;i<nr_grup+nr;i++)
                                {
                                    if(i>nr_grup&&gasit[i]==0)
                                        v[i]=copie[i];
                                    else
                                    if(i<=nr_grup)
                                        v[i]=copie[i];
                                }
                                nr_grup=nr_grup+nr-sum;
                                for(int i=0;i<nr;i++)
                                {
                                    if(gasit[i]==0)
                                        cout<<"\nAdaugarea companiei "<<comp[i].get_nume_comp()<<" a fost efectuata cu succes\n";
                                    else
                                        cout<<"\nCompania "<<comp[i].get_nume_comp()<<" se afla deja in grup\n";
                                }
                            }
                            catch(bad_alloc var)
                            {
                                cout<<"Allocation Failure\n";
                                exit(EXIT_FAILURE);
                            }
                        }
                        if(nr==0)
                            cout<<"\n\tWARNING!\tNu ati introdus companii\n";
                    }

                    break;
                default:
                    cout<<"\nSelectie invalida\n";
                    break;
            }
        }
        while(opt!=0);
    }

    void raport_nr_ang_comp()
    {
        int poz;
        cout<<"\nCarui obiect vreti sa aflati nr de angajati: ";
        cin>>poz;
        poz--;
        try
        {
            if(poz<0||poz>nr_grup)
                throw 1;
            else
            if(typeid(v)==typeid(Companie_disc*))
            {
                if(v[poz].get_nr_ang()!=1)
                    cout<<"\nCompania '"<<v[poz].get_nume_comp()<<"' are "<<v[poz].get_nr_ang()<<" angajati\n";
                else
                    cout<<"\nCompania '"<<v[poz].get_nume_comp()<<"' are un angajat\n";
            }
            else
                cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie_disc'\n";
        }
        catch(int i)
        {
            cout<<"\n\n\t\tWARNING!\tPozitia aleasa nu corespunde niciunei companii\n";
            exit(EXIT_FAILURE);
        }
    }

    void cheltuieli_salariale()
    {
        int poz;
        cout<<"\nCarei companii vreti sa aflati cheltuielile salariale lunare: ";
        cin>>poz;
        poz--;
        try
        {
            if(poz<0||poz>nr_grup)
                throw 1;
            else
            if(typeid(v)==typeid(Companie_disc*))
            {
                cout<<"\nCompania '"<<v[poz].get_nume_comp()<<"' are cheltuieli salariale lunare in valoare de "<<v[poz].cheltuieli_salariale()<<" lei\n";
            }
            else
                cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie_disc'\n";
        }
        catch(int i)
        {
            cout<<"\n\n\t\tWARNING!\tPozitia aleasa nu corespunde niciunei companii\n";
            exit(EXIT_FAILURE);
        }
    }

    void lista_man()
    {
        int poz;
        cout<<"\nCarei companii vreti sa aflati lista de manageri: ";
        cin>>poz;
        poz--;
        try
        {
            if(poz<0||poz>nr_grup)
                throw 1;
            else
            if(typeid(v)==typeid(Companie_disc*))
            {
                cout<<"\nCompania '"<<v[poz].get_nume_comp()<<" are urmatorii manageri: \n";
                v[poz].lista_man();
            }
            else
                cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie_disc'\n";
        }
        catch(int i)
        {
            cout<<"\n\n\t\tWARNING!\tPozitia aleasa nu corespunde niciunei companii\n";
            exit(EXIT_FAILURE);
        }
    }

    void min_n_ang()
    {
        int poz,n,gasit=0;
        cout<<"\nCarei companii vreti sa aflati lista departamentelor cu un minim de angajati: ";
        cin>>poz;
        poz--;
        cout<<"Introduceti minim: ";
        cin>>n;
        try
        {
            if(poz<0||poz>nr_grup)
                throw 1;
            else
            if(typeid(v)==typeid(Companie_disc*))
            {
                cout<<"\nCompania '"<<v[poz].get_nume_comp()<<" are urmatoarele departamente cu numar minim: ";
                v[poz].lista_dep(n);
                gasit++;
            }
            else
                cout<<"\n\n\t\tWARNING!\tTrebuie sa apelati functia cu obiecte de tip 'Companie_disc'\n";
            if(gasit==0)
                throw 's';
        }
        catch(int i)
        {
            cout<<"\n\n\t\tWARNING!\tPozitia aleasa nu corespunde niciunei companii\n";
            exit(EXIT_FAILURE);
        }
        catch(char s)
        {
            cout<<"\n\n\t\tWARNING!\tMinimul cerut nu exista\n";
            exit(EXIT_FAILURE);
        }
    }
};
int HRManager <Companie_disc>::numarGrupuri = 0;

//functie pentru citirea a n obiecte de tipuri diferite
void tip(Angajat *&p, int i, list<Angajat*> &l)
{
    string s;
    cout<<"\nIntroduceti tipul obiectului (Angajat/Departament/Companie) cu numarul "<<i+1<<": ";
    cin>>s;
    cin.get();
    try
    {
        if(s=="Angajat")
        {
                p=new Angajat;
                cin>>*p;
                l.push_back(*&p);
        }
        else
            if(s=="Departament")
            {
                p=new Departament;
                cin>>*p;
                l.push_back(*&p);
            }
            else
                if (s=="Companie")
                {
                    p=new Companie;
                    cin>>*p;
                    l.push_back(*&p);
                }
                else
                    throw 's';
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(char s)
    {
        cout<<"Nu ati introdus un obiect valid\n";
        exit(EXIT_FAILURE);
    }
}

void menu_interactiv()
{
    int option;
    do
    {
        cout<<"\nAndrita Lucian-Gabriel 253\nProiect 3 - Tema 11 \n";
        cout<<"\n\t\t\t\t\t\t\t MENIU:";
        cout<<"\n========================================================================================================================\n\n";
        cout<<"1.  Testare constructor de ini. cu param. impliciti, constructor de copiere si operatorul= din clasa ANGAJAT\n";
        cout<<"2.  Testare constructor de ini. cu param. impliciti, constructor de copiere si operatorul= din clasa DEPARTAMENT\n";
        cout<<"3.  Testare constructor de ini. cu param. impliciti, constructor de copiere si operatorul= din clasa COMPANIE\n";
        cout<<"4.  Testare citire si afisare din toate clasele pornind de la a doua derivata prin apel invers\n";
        cout<<"5.  Testarea functionalitatii sablonului HRManager\n";
        cout<<"6.  Testarea fuzionarii a doua companii\n";
        cout<<"7.  Testarea diferentei la citire dintre companii in cadrul gestionarului\n";
        cout<<"8.  Testarea functiei pentru adaugare/stergere obiecte la nivelul gestionarului\n";
        cout<<"9.  Testarea furnizarii de rapoarte la nivelul gestionarului\n";
        cout<<"10. Testarea optiunii de lucru cu companii ce beneficiaza de scutire de impozit\n";
        cout<<"11. Testarea functiilor statice/constante\n";
        cout<<"12. Testarea conceptelor de RTTI\n";
        cout<<"13. Testarea citirii a n obiecte folosind STL\n";
        cout<<"0.  Iesire\n\n";

        cout<<("\nIntroduceti numarul cerintei: ");
        cin>>option;
        cin.get();
        cout<<"\n";

        switch(option)
        {
            case 0:
                cout<<"\n\t\tProgramul se va termina\n";
                break;

            case 1:
                {
                    cout<<"\n\t\tTestare constr. de ini. cu param. impliciti, constr. de copiere si op.= din clasa ANGAJAT\n";
                    int n;
                    cout<<"Introduceti numarul de angajati: ";
                    cin>>n;
                    cin.get();
                    try
                    {
                        string nume[n];
                        string data_angajare[n];
                        double salariu[n];
                        int man_ang[n];
                        string **nume_man_ang;
                        nume_man_ang=new string*[n];
                        bool manager[n];
                        string functie[n]={""};
                        Angajat x[n];
                        for(int i=0; i<n; i++)
                        {
                            cout<<"\nIntroduceti numele angajatului: ";
                            getline(cin,nume[i]);
                            cout<<"Introduceti data angajarii: ";
                            getline(cin,data_angajare[i]);
                            cout<<"Introduceti salariul: ";
                            cin>>salariu[i];
                            cout<<"Introduceti daca este manager sau nu (bool): ";
                            cin>>manager[i];
                            cin.get();
                            man_ang[i]=0;
                            nume_man_ang[i]=new string[man_ang[i]];
                            if(manager[i]==0)
                            {
                                cout<<"Introduceti functia: ";
                                getline(cin,functie[i]);
                            }
                            else
                            {
                                cout<<"\t\t\tIntroduceti numarul de angajati coordonati de "<<nume[i]<<": ";
                                cin>>man_ang[i];
                                nume_man_ang[i]=new string[man_ang[i]];
                                cin.get();
                                if(man_ang[i]==1)
                                {
                                    cout<<"\t\t\tIntroduceti numele angajatului: ";
                                    getline(cin,nume_man_ang[i][0]);
                                }
                                else
                                {
                                    for(int j=0;j<man_ang[i];j++)
                                    {
                                        cout<<"\t\t\tIntroduceti numele angajatului cu nr "<<j+1<<": ";
                                        getline(cin,nume_man_ang[i][j]);
                                    }
                                }
                            }
                            Angajat y1(nume[i],data_angajare[i],salariu[i],manager[i],man_ang[i],nume_man_ang[i],functie[i]);

                            Angajat y2(y1);
                            Angajat y3=y2;
                            Angajat y4;
                            y4=y3;
                            x[i]=y4;
                        }
                        cout<<endl;
                        for(int i=0; i<n; i++)
                            cout<<x[i];
                    }
                    catch(bad_alloc var)
                    {
                        cout<<"Allocation Failure\n";
                        exit(EXIT_FAILURE);
                    }
                }

                break;
            case 2:
                {
                    cout<<"\n\t\tTestare constr. de ini. cu param. impliciti, constr. de copiere si op.= din clasa DEPARTAMENT\n";
                    int n;
                    cout<<"Introduceti numarul de angajati: ";
                    cin>>n;
                    cin.get();
                    Angajat x[n];
                    for(int i=0; i<n; i++)
                        cin>>x[i];
                    Departament x1("Socului Kebab",n,x);
                    Departament x2(x1);
                    Departament x3=x2;
                    Departament x4;
                    x4=x3;
                    cout<<x4;
                }

                break;
            case 3:
                {
                    cout<<"\n\t\tTestare constr. de ini. cu param. impliciti, constr. de copiere si op.= din clasa COMPANIE\n";
                    int n;
                    cout<<"Introduceti numarul de departamente: ";
                    cin>>n;
                    cin.get();
                    Departament x[n];
                    for(int i=0;i<n;i++)
                        cin>>x[i];
                    Companie x1("Dristor Kebab", n, x);
                    Companie x2(x1);
                    Companie x3=x2;
                    Companie x4;
                    x4=x3;
                    cout<<x4;
                }

                break;
            case 4:
                {
                    cout<<"\n\t\tTestare citire si afisare din toate clasele pornind de la a doua derivata prin apel invers\n";
                    Companie x;
                    cin>>x;
                    cout<<x;
                }

                break;
            case 5:
                {
                    cout<<"\n\t\tTestarea functionalitatii sablonului HRManager\n";
                    HRManager <Angajat> x;
                    cin>>x;
                    HRManager <Angajat> y1(x);
                    HRManager <Angajat> y2=y1;
                    HRManager <Angajat> y3;
                    y3=y1;
                    x.afisare_count();
                    cout<<y3;
                }

                break;
            case 6:
                {
                    cout<<"\n\t\tTestarea operatorului+ (din clasa Companie) pentru fuzionarea a doua companii\n";
                    Companie x,y;
                    cin>>x>>y;
                    Companie z;
                    z=x+y;
                    cout<<z;
                    cout<<"\n\tTestarea fuzionarii a doua companii la nivelul gestionarului\n";
                    HRManager <Companie> p;
                    cin>>p;
                    p.fuzionare();
                    cout<<p;
                }

                break;
            case 7:
                {
                    cout<<"\n\t\tTestarea diferentei dintre doua departamente\n";
                    Departament x;
                    cin>>x;
                    Departament y;
                    cin>>y;
                    cout<<"\n\tDepartamentele sunt ";
                    if(x.diferite_dep(y)==0)
                        cout<<"diferite\n";
                    else
                        cout<<"egale\n";
                    cout<<"\n\t\tTestarea diferentei dintre doua companii\n";
                    Companie x1;
                    cin>>x1;
                    Companie y1;
                    cin>>y1;
                    cout<<"\n\tCompaniile sunt ";
                    if(x1.diferite_comp(y1)==0)
                        cout<<"diferite\n";
                    else
                        cout<<"egale\n";
                    cout<<"\n\t\tTestarea diferentei dintre doua companii la nivelul gestionarului\n";
                    HRManager <Companie> x2;
                    cin>>x2;
                    cout<<x2;
                }

                break;
            case 8:
                {
                    cout<<"\n\t\tTestarea functiei pentru adaugare/stergere obiecte la nivelul gestionarului\n";
                    HRManager <Companie>x;
                    cin>>x;
                    x.modificare();
                    cout<<x;
                }

                break;
            case 9:
                {
                    cout<<"\n\t\tTestarea furnizarii de rapoarte la nivelul gestionarului\n";
                    //Nr de angajati comp/dep
                    HRManager <Departament>x1;
                    cin>>x1;
                    x1.raport_nr_ang_dep();
                    HRManager <Companie>x2;
                    cin>>x2;
                    x2.raport_nr_ang_comp();

                    //Cheltuieli salariale lunare
                    x2.cheltuieli_salariale();

                    //Lista manageri
                    x2.lista_man();

                    //Min n angajati
                    x2.min_n_ang();
                }

                break;
            case 10:
                {
                    cout<<"\n\t\tTestarea clasa companie cu discount\n";
                    int n;
                    cout<<"Introduceti numarul de departamente: ";
                    cin>>n;
                    cin.get();
                    Departament z[n];
                    for(int i=0;i<n;i++)
                        cin>>z[i];
                    Companie_disc z1("Taxim Kebab", n, z);
                    Companie z2(z1);
                    Companie z3=z2;
                    Companie z4;
                    z4=z3;
                    cout<<z4;
                    cin>>z1;
                    cout<<z1;

                    cout<<"\n\n\t\tTestare template specializat\n";
                    Companie_disc x1[2];
                    for(int i=0;i<2;i++)
                        cin>>x1[i];
                    HRManager <Companie_disc> y(x1,2);
                    HRManager <Companie_disc> y1(y);
                    HRManager <Companie_disc> y2=y1;

                    Companie_disc x,y5;
                    cin>>x>>y5;
                    Companie_disc z5;
                    z5=x+y5;
                    cout<<z5;

                    HRManager <Companie_disc> y3;
                    y3=y2;
                    y.afisare_count();
                    cout<<y3;
                    cin>>y3;
                    cout<<y3;
                    y3.fuzionare();
                    cout<<y3;

                    //sterg angajati
                    y3.modificare();
                    cout<<y3;
                    //adaug
                    y3.modificare();
                    cout<<y3;
                    //sterg departamente
                    y3.modificare();
                    cout<<y3;
                    //adaug
                    y3.modificare();
                    cout<<y3;
                    //sterg companii
                    y3.modificare();
                    cout<<y3;
                    //adaug
                    y3.modificare();
                    cout<<y3;

                    //Nu am cum sa testez raportul pt nr de angajati pe departament deoarece am
                    //template specializat
                    //Nr de angajati comp
                    y3.raport_nr_ang_comp();
                    //Cheltuieli salariale lunare
                    y3.cheltuieli_salariale();
                    //Lista manageri
                    y3.lista_man();
                    //Min n angajati
                    y3.min_n_ang();
                }

                break;
            case 11:
                {
                    cout<<"\n\t\tTestarea functie statica\n";
                    HRManager <Companie> x[10];
                    HRManager <Angajat> y;
                    x[0].afisare_count();
                    y.afisare_count();
                    cout<<"\n\t\tTestarea functie constanta\n";
                    Companie z;
                    z.lipsa_inspiratie();
                }

                break;
            case 12:
                {
                    cout<<"\n\t\tTestarea conceptelor de RTTI\n";
                    //UPCASTING
                    Departament *x= new Companie;
                    if(typeid(x)==typeid(Departament*))
                        cout<<"\nPointerul este de tip Departament\n";
                    else
                        cout<<"Upcasting-ul a esuat\n";
                    if(typeid(*x)==typeid(Companie))
                        cout<<"\tInformatia propriu-zisa este de tip Companie\n";
                    else
                        cout<<"Informatia este corupta\n\n";
                    x->verif_dyn_cast();

                    //CONVERSIE PROPRIU-ZISA
                    Companie *px= dynamic_cast <Companie*>(x);
                    if(typeid(px)==typeid(Companie*))
                        cout<<"\nPointerul este de tip Companie in urma conversiei\n";
                    else
                        cout<<"Dynamic castul a esuat\n";
                    if(typeid(*px)==typeid(Companie))
                        cout<<"\tLa adresa pointerului se afla informatie apartinand clasei Companie => conversia a reusit\n";
                    else
                        cout<<"Informatia este corupta\n";
                    px->verif_dyn_cast();
                }

                break;
            case 13:
                {
                    cout<<"\n\t\tTestarea citirii a n obiecte folosind STL\n";
                    list <Angajat*> meh;
                    Angajat **v;
                    int n;
                    cout<<"Dati nr de obiecte: ";
                    cin>>n;
                    try
                    {
                        v=new Angajat*[n];
                        for(int i=0;i<n;i++)
                            tip(v[i],i,meh);
                        list<Angajat*>::iterator i;
                        for (i=meh.begin();i!=meh.end();++i)
                            cout<<(**i);
                    }
                    catch(bad_alloc var)
                    {
                        cout<<"Allocation Failure\n";
                        exit(EXIT_FAILURE);
                    }
                }

                break;
            default:
                cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause");
        system("cls");
    }
    while (option!=0);
}

int main()
{
    menu_interactiv();
    cout<<"\n\n";
    return 0;
}
