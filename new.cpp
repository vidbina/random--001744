#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//Global konstant
const int MAX_KOMPISAR = 6;

const int MAX_PERSONER = 10;

//Den statiska arrayen kompisar har storleken MAX_KOMPISAR med ant_kompisar st element inlagda. MAX_KOMPISAR kan vara en global konstant.


//Den statiska arrayen trans är av storlek MAX_TRANSAKTIONER och har antalTrans st element inlagda.
// MAX_TRANSAKTIONER kan vara en global konstant.
const int MAX_TRANSAKTIONER = 30; // TODO: I dont know what this number is supposed to be

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
    TransaktionsLista() {};
    ~TransaktionsLista() {};
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
  TransaktionsLista l;

  ifstream ifs ("resa.txt", std::ifstream::in);

  if(!ifs.is_open()) {
    // TODO: translate
    cout << "Invalid file" << endl;
    return 0;
  }

  l.laesin(ifs);

  while(true) {
    switch(skriv_meny()) {
      case 0:
        // TODO: save to file and exit
        return 0;
      case 1:
        cout << "datum typ namn belopp ant_kompisar kompisar*" << endl;
        l.laesin(cin);
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
  os << datum; // An example
    // TODO: Not sure if we need to print a space of something between each variable, like "os << datum << " ";
  os << typ;
  os << namn;
  os << belopp;
  os << ant_kompisar;
  for(int i = 0; i<ant_kompisar; i++) {
    os << kompisar[i];
  }
}

//Metoden laesEnTrans läser data om en transaktion (kvitto) från tangentbord eller en fil. Denna är av typen bool, eftersom den kan komma att anropas från klassen TransaktionsLista:s metod laesin med en loop av typen

bool Transaktion::laesEnTrans( istream &is )
{
    // TODO: Before reading from is, make sure it has data
    if(!is.good()) { return false; }

    is >> datum >> typ >> namn >> belopp >> ant_kompisar;

    for(int i = 0; i < ant_kompisar; i++) {
      is >> kompisar[i];
    }

    if(!cin.good()) {
      return false;
    }

    return true;
}
     
//Metoderna laesin och skrivut läser in värden till ett TransaktionsLista-objekt från/till fil eller tangentbord/skärm. Använder sig av inläsnings- och utskriftsmetoder i klassen Transaktion.     
void TransaktionsLista::laesin( istream & is )
{
  // How do we handle menu like flows and file flows. For option 1, we need to
  // enter text through the keyboard. When do we break out of this, now the
  // flow breaks when an invalid entry is encountered, but that sometimes
  // requires some bogus entries since the first fields take string values and
  // therefore match any input. At the belopp field we can finally trigger a
  // failure to exit.
  while (!is.eof() && is.good())
  {
      Transaktion t;
      bool ok = t.laesEnTrans(is);

      if (ok)
      {
          cout << "just read transaction " << antalTrans << endl;
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
