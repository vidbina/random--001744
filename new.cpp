#include <string>
#include <iostream>
#include <fstream>

// Options 1 through 5 implemented (more or less :P)
// Screwing up on case 6, find the comments in the code l165

using namespace std;

//Global konstant
const int MAX_KOMPISAR = 6;

const int MAX_PERSONER = 10;

//Den statiska arrayen kompisar har storleken MAX_KOMPISAR med ant_kompisar st element inlagda. MAX_KOMPISAR kan vara en global konstant.


//Den statiska arrayen trans är av storlek MAX_TRANSAKTIONER och har antalTrans st element inlagda.
// MAX_TRANSAKTIONER kan vara en global konstant.
const int MAX_TRANSAKTIONER = 30; // TODO: I dont know what this number is supposed to be

// Weird design
class Person
{
  private:
    string namn;
    double betalat_andras;
    double skyldig;
  public:
    Person() {};
    Person(string n, double b, double s);
    double haemta_betalat();
    double haemta_skyldig();
    void skrivUt();
};

class PersonLista
{
  private:
    int antal_pers;
    Person pers[MAX_PERSONER];
  public:
    PersonLista() {};
    ~PersonLista() {};
    void laggTillEn(Person pny);
    void skrivUtOchFixa();
    double summaSkyldig();
    double summaBetalat();
    bool finnsPerson(const string& namn);
};

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
    string haemta_kompisar_namn(int id);
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
    int length();
    Transaktion get(int id);
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

  if(!cin.good()) {
    cout << "fix" << endl;
    cin.clear();
    return 100; // trigger the default case
  }

  cin >> choice;

  return choice;
}

// create a transaction list
// add a transaction

int main()
{
  TransaktionsLista tl;
  PersonLista pl;

  string namnet;

  ifstream ifs ("resa.txt", std::ifstream::in);

  if(!ifs.is_open()) {
    // TODO: translate
    cout << "Invalid file" << endl;
    return 0;
  }

  tl.laesin(ifs);
  // Weird design, there is no person or personlist until this point. So I
  // guess we'll have to traverse the transactionlist and populate the person
  // list and there has been no instruction to pass the list point along to the
  // tf methods in order to automatically populate it.

  while(true) {
    // TODO: Translate
    switch(skriv_meny()) {
      case 0:
        // TODO: save to file and exit
        return 0;
      case 1:
        cout << "datum typ namn belopp ant_kompisar kompisar*" << endl;
        tl.laesin(cin);
      case 2:
        tl.skrivut(cout);
      case 3:
        cout << "Total costs are: " << tl.totalkostnad() << endl;
      case 4:
        // TODO: check, but not really because its a string anyways
        cout << "Enter the name of the person" << endl;
        cin >> namnet;
        cout << namnet << " is receiving " << tl.liggerUteMed(namnet) << " from the pot" << endl;
      case 5:
        cout << "Enter the name of the person" << endl;
        cin >> namnet;
        cout << namnet << " has to pay " << tl.aerSkyldig(namnet) << " into the pot" << endl;
      case 6:
        // DISCLAIMER: This will be sloppy, I will basically walk through the
        // transaction list and for every name that I encounter, of the
        // transaction owner and then the other folks listed on that
        // transaction, perform a laggTillEn call with aerSkyldig and
        // liggerUteMed on those names. I make the assumption that if I were to
        // call aeSkyldig and liggerUteMed on any name multiple times the
        // output values would be the same since the list doesn't change. In an
        // ideal world, I would have kept track of every name that I have
        // encountered so far, but my brain is not digging it.
        
        // TODO: DEBUG THIS UNHOLY MESS

        // get a list of all names in the transaction list
        cout << "A" << endl;
        for(int i = 0; i < tl.length(); i++) { // for every index in the list
          // get the name of the owner
          string owner = tl.get(i).haemta_namn();
          // and add the owner's record to the person list if not already there
          cout << "b" << endl;
          if(!pl.finnsPerson(owner)) {
            pl.laggTillEn(Person(owner, tl.aerSkyldig(owner), tl.liggerUteMed(owner)));
          }

          cout << "c" << endl;
          // get the name of all the leaches on this transactions
          for (int j = 0; j < tl.get(i).haemta_ant_kompisar(); j++) {
            // for every other person listed on the transaction ⇒ to something
            cout << "d" << endl;
            string leach_name = tl.get(i).haemta_kompisar_namn(j);
            cout << "e" << endl;
            if(!pl.finnsPerson(leach_name)) {
              cout << "f" << endl;
              pl.laggTillEn(Person(leach_name, tl.aerSkyldig(leach_name), tl.liggerUteMed(leach_name)));
              cout << "g" << endl;
            }
          }
        }
        cout << "FIN" << endl;

        pl.skrivUtOchFixa();
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

string Transaktion::haemta_kompisar_namn(int id)
{
  if(id < MAX_KOMPISAR) {
    return kompisar[id];
  }
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
  os << "Datum: " << datum << endl; // An example
    // TODO: Not sure if we need to print a space of something between each variable, like "os << datum << " ";
  os << "Typ: " << typ << endl;
  os << "Namn: " << namn << endl;
  os << "Belopp: " << belopp << endl;
  os << "Ant kompisar: " << ant_kompisar << endl;
  for(int i = 0; i<ant_kompisar; i++) {
    os << "  Kompisar " << i << " " << kompisar[i] << endl;
  }
  os << endl;
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
          laggTill(t);
      }
  }
}

void TransaktionsLista::skrivut( ostream & os )
{
    for (int i = 0; i < antalTrans-1; i++)
    {
        trans[i].skrivEnTrans(os);
    }
}
void TransaktionsLista::laggTill( Transaktion & t ) {
  // NOTE: Perhaps we should refrain from possibly overwriting a position that
  // is already populated and perform some sanity checks on t
  trans[antalTrans] = t;
  // NOTE: Perhaps we should check that we're not at our max yet
  antalTrans++;
}

double TransaktionsLista::totalkostnad() {
  double sum = 0;

  for (int i = 0; i < antalTrans -1; i++) {
    sum = sum + trans[i].haemta_belopp();
  }

  return sum;
}

double TransaktionsLista::liggerUteMed(string namnet) {
  double sum = 0;

  for (int i = 0; i < antalTrans -1; i++) {
    if(trans[i].haemta_namn() == namnet) {
      // this is a transaction that I added so I paid
      double transaction_cost = trans[i].haemta_belopp();
      double friends_count = trans[i].haemta_ant_kompisar();
      double share_to_be_received = friends_count/(friends_count+1);

      sum = sum + transaction_cost*share_to_be_received;
    }
  }

  return sum;
}

double TransaktionsLista::aerSkyldig(string namnet) {
  double sum = 0;

  for (int i = 0; i < antalTrans -1; i++) {
    if(trans[i].finnsKompis(namnet)) {
      double transaction_cost = trans[i].haemta_belopp();
      double friends_count = trans[i].haemta_ant_kompisar();
      double share_to_pay = 1/(friends_count+1);

      sum = sum + transaction_cost*share_to_pay;
    }
  }

  return sum;
}

int TransaktionsLista::length() {
  // NOTE: Kind of messy, when we have as many items as the max size at which
  // this array is declared, we'll have some discrepancies
  return antalTrans-1;
}

Transaktion TransaktionsLista::get(int id) {
  if(id < MAX_TRANSAKTIONER) {
    return trans[id];
  }
}

Person::Person(string n, double b, double s) {
  namn = n;
  betalat_andras = b;
  skyldig = s;
}

void Person::skrivUt() {
  cout << "Something sensible about "<< namn << endl;
}

void PersonLista::laggTillEn(Person pny) {
  // See notes for TransaktionsLista::lagTill :facepalm:
  pers[antal_pers] = pny;
  antal_pers++;
}

void PersonLista::skrivUtOchFixa() {
  for(int i = 0; i < antal_pers; i++) {
    // TODO: Too tired now
    pers[i].skrivUt();
  }
}

double PersonLista::summaSkyldig() {
  return 0;
}

double PersonLista::summaBetalat() {
  return 0;
}

bool PersonLista::finnsPerson(const string& namn) {
  return false;
}
