#include <string>
#include <iostream>

using namespace std;

//Global konstant
const int MAX_KOMPISAR = 6;

//Den statiska arrayen kompisar har storleken MAX_KOMPISAR med ant_kompisar st element inlagda. MAX_KOMPISAR kan vara en global konstant.


//Den statiska arrayen trans är av storlek MAX_TRANSAKTIONER och har antalTrans st element inlagda.
// MAX_TRANSAKTIONER kan vara en global konstant.
const int MAX_TRANSAKTIONER = 10; // TODO: I dont know what this number is supposed to be

class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int ant_kompisar;
    string kompisar[MAX_KOMPISAR];
    
public:
    Transaktion(){}
    ~Transaktion(){}
    string haemta_namn();
    double haemta_belopp();
    int haemta_ant_kompisar();
    bool finnsKompis( string namnet );
    bool laesEnTrans( istream &is );
    void skrivEnTrans( ostream &os );
//    ...eventuellt div. annat...
};

class TransaktionsLista
{
    private:
    Transaktion trans[MAX_TRANSAKTIONER];
    int antalTrans = 0;

    public:
    TransaktionsLista();
    ~TransaktionsLista();
    void laesin( istream & is );
    void skrivut( ostream & os );
    void laggTill( Transaktion & t );
    double totalkostnad();
    double liggerUteMed( string namnet );
    double aerSkyldig( string namnet );
    //PersonLista FixaPersoner(); // TODO: PersonLista isn't a defined class, it needs to be created or the return typ needs to be changed
     //...eventuellt div. annat...
};

int skriv_meny() {
  int choice;

  cout << "Välj i menyn nedan:" << endl;
  cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
  cout << "1. Läs in en transaktion från tangentbordet." << endl;
  cout << "2. Skriv ut information om alla transaktioner." << endl;
  cout << "3. Beräkna totala kostnaden." << endl;
  cout << "4. Hur mycket är en viss person skyldig?" << endl;
  cout << "5. Hur mycket ligger en viss person ute med?" << endl;
  cout << "6. Lista alla personer mm och FIXA!!!" << endl;

  cin >> choice;

  return choice;
}

// create a transaction list
// add a transaction

int main()
{
  TransaktionsLista list();

  while(true) {
    switch(skriv_meny()) {
      case 0:
        // TODO: save to file and exit
        return(0);
      default:
        cout << "WIP" << endl;
    }
  }

    // En inläsningsmetod i klassen TransaktionsLista.
    //Transaktion t;

    

    // Så länge det går bra att läsa (filen ej slut)
//    while ( t.laesEnTrans( is ) )
//    {
//        laggTill( t );
//    }
}

  //Metoderna haemta_namn, haemta_ant_kompisar och haemta_belopp är s.k. selektorer, som returnerar motsvarande attributvärden.
string Transaktion::haemta_namn()
{
    return namn;
}

int Transaktion::haemta_ant_kompisar()
{
    return ant_kompisar;
}

double Transaktion::haemta_belopp()
{
    return belopp;
}

//Metoden finnsKompis letar igenom arrayen kompisar och returnerar true om namnet finns, annars false.
bool Transaktion::finnsKompis(string namnet)
{

    for (int i = 0; i < MAX_KOMPISAR; i++)
    {
        if (kompisar[i] == namnet)
        {
            return true;
        }
    }   

    return false;
}

//Metoden skrivEnTrans skriver ut information om ett objekt (dvs "aktuella objektet" tillhörande denna klass), dvs attributens värden, antingen till en fil eller till skärmen. Se körexempel nedan.
void Transaktion::skrivEnTrans( ostream &os )
{
// In this method you want to write all of the attributes of Transaction ( datum, belopp, etc)
// the order of these items being written has to be the same as the order they are being read in laesEnTrans

/*
    string datum;
    string typ;
    string namn;
    double belopp;
    int ant_kompisar;
    string kompisar[MAX_KOMPISAR];
*/

}

//Metoden laesEnTrans läser data om en transaktion (kvitto) från tangentbord eller en fil. Denna är av typen bool, eftersom den kan komma att anropas från klassen TransaktionsLista:s metod laesin med en loop av typen

bool Transaktion::laesEnTrans( istream &is )
{
// In this method you want to write all of the attributes of Transaction ( datum, belopp, etc)
// this function should be able to create transactions from the text that is provided by is


    if(!is) // Om vi inte kan läsa från is
    {
        return false;
    }
    
    // Before reading from is, make sure it has data
    is >> datum; // An example

// Pay exrta attention to "is" having data when reading from it.
// All of the data needs to go into the attributes for this object

/*    
    string datum;
    string typ;
    string namn;
    double belopp;
    int ant_kompisar;
    string kompisar[MAX_KOMPISAR];
*/

    return true;
}
     

     
     
//Metoderna laesin och skrivut läser in värden till ett TransaktionsLista-objekt från/till fil eller tangentbord/skärm. Använder sig av inläsnings- och utskriftsmetoder i klassen Transaktion.     
void TransaktionsLista::laesin( istream & is )
{
  // TODO: translate
  cout << "Enter your transaction date";
  cout << "Enter your transaction type";
  cout << "Enter your transaction name";
  cout << "Enter your transaction value";
  cout << "Enter your transaction participant count";
  cout << "Enter your transaction name of person x";

  // TODO: sanity check all input values
  // perhaps even while you are collecting them ;)

  //trans[antalTrans] = Transaction
    while (true)
    {
        Transaktion t;
        bool ok = t.laesEnTrans(is);
        if (ok)
        {
            trans[antalTrans] = t;
            antalTrans++;
        }
    }
}

void TransaktionsLista::skrivut( ostream & os )
{
    for (int i = 0; i < antalTrans; i++)
    {
        trans[i].skrivEnTrans(os);
    }
}
