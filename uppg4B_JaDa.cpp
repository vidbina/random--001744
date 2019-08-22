
/*
 ================================================================================
 Datorer och programmering, DoP, 10 hsp, termin/år:__sommar 2019_______
 
 Inlämningsuppgift nr _4B___
 
 Namn: ___Jack Dahén_________________________________________________
 
 Personummer: __9406186982________________
 
 Fyll i (alt. stryk det som INTE är relevant) av nedanstående:
 
 Den fil som jag lämnar in går att kompilera och
 programmet fungerar för alla de testdata som finns för uppgiften: Ja/Nej
 Om Nej, beskriv vilka testdata som ger problem:  __________________
 
 
 Jag har använt kompilator/editor (namn/version) ______clang/ xcode 5.0.2_________________
 
 Jag har använt följande dator (t.ex. PC, Mac, Annat): __Mac________
 med operativsystemet (t.ex. WindowsXP, Windows7,...) : ____OSx version 10.9.5__________
 
 Jag har arbetat ungefär  _______ timmar med denna uppgift
 
 ================================================================================
 */

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
using namespace std;


const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
{{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
    7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
    0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
    1.89,0.03},
    {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
        7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
        1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
        0.30,0.15},
    {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
        3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
        0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
        0.45,0.00},
    {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
        8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
        0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
        0.69,1.24}};

void berakna_histogram_abs(string text, int &antal, int total[]);
void abs_till_rel( double frekV[], int antal, int total[]);
void plotta_histogram_rel(double frekV[]);
void tolkning(double frekV[]);
string namn_pa_fil();
string inlasning(string filnamn);


int main()
{
    string text;
    double frekV[ANTAL_BOKSTAVER] = {0};
    int total[ANTAL_BOKSTAVER] = {0};
    int antal= 0;

    //Temp
    cout<< "Mata in en rad:";
    getline(cin, text);
    string innehall = text;
    
    //string fil = namn_pa_fil();
    //string innehall = inlasning(fil);
    berakna_histogram_abs(innehall, antal, total);
    abs_till_rel( frekV, antal, total);
    plotta_histogram_rel( frekV);
    tolkning(frekV );
    
    return 0;
}


void berakna_histogram_abs(string text, int &antal, int total[])
{
    for(int i=0; i<text.length(); i++)
    {
        if( isalpha(text[i]) && (!isdigit(text[i])) )
        {
            char lower = tolower(text[i]);
            int index = 0;
            index = lower - 'a';
            total[index]++;
            antal++;
        }
    }
}


void abs_till_rel( double frekV[], int antal, int total[])
{
    if (antal ==0)
        return;
    
    for(int i=0; i<ANTAL_BOKSTAVER; i++)
        frekV[i] = total [i]/ (double) antal;
}


void plotta_histogram_rel(double frekV[])
{
    cout << "Resultat för bokstäverna A-Z:" << endl;
    cout << " " << endl;
    cout << "Bokstavsfördelning:" << endl;
    cout << "Bokstav:" << "       " << "Histogram:" << endl;
    
    for(int i=0; i<ANTAL_BOKSTAVER; i++)
    {
        char bok = i + 'a';
        cout << bok << "               ";
        int stjarnor = frekV[i]*200;
        cout << string(stjarnor, '*') << endl;
    }
}


void tolkning(double frekV[])
{
    string sprak[4] = {"Engelska", "Franska", "Svenska", "Tyska"};
    double minSum = numeric_limits<double>::max();
    string minSprak;
    for (int j = 0; j < ANTAL_SPRAK; j++)
    {
        double sum= 0;
        for(int i=0; i<ANTAL_BOKSTAVER; i++)
        {
            sum = (frekV[i]-TOLK_HJALP[j][i]) * (frekV[i]-TOLK_HJALP[j][i]) + sum;
        }
        if (sum < minSum)
        {
            minSum = sum;
            minSprak = sprak[j];
        }
        cout << sprak[j] << ": " << sum << endl;
    }
    cout << "Med störst sannolikhet, är detta språk: " << minSprak << ": " << minSum << endl;
}



/*
string namn_pa_fil()
{
    string fil;
    
    cout << "Läs fil: " << endl;
    cin >> fil;
    if( fil.rfind(".txt") != string::npos)
    {
        return fil;
    } else {
        return fil.append(".txt");
    }
}


string inlasning(string filnamn)
{
    ifstream fil;
    string innehall = "";
    cout << "Läser från fil: " << filnamn << endl;
    fil.open(filnamn);
    if (!fil.is_open())
    {
        cout << "Kunde inte öppna: " << filnamn << endl;
        return "";
    }
    while(!fil.eof())
    {
        string nyrad;
        getline(fil, nyrad);
        innehall = innehall.append(nyrad);
    }
    cout << "Läste " << innehall.length() << " tecken från " << filnamn << endl;
    return innehall;
}
*/

/*
 ================================================================================
 Här följer programkörningar för alla testdata:
 ==============================================
 
 ...
 
 ================================================================================
  - Ett eller ett par stycken om vad uppgiften gick ut på? 
 
 *Att skriva ett hududprogram som endast inehåller anrop till de olika funktionerna. Skriv en funktion för varje operation som ska göras: 
 Läs in namn på fil och kolla att filnamnet är korrekt, annars rätta till det.
 Läs in matchande fil och sparar inehållet i en sträng.
 Beräkna histogram av innehållet i strängen ( en text i detta fall), alltså att beräkna hur många av varje bokstav som finns.
 Räkna om histogramet med absoluta värden till relativa, så man kan beräkna med vilken frekvens de exicterar i filen. 
 Skriv ut en tabell som skriver ut frekvensen i form av symboler, där 1% == **. 
 Tolka histogramet och jämför de olika frekvenserna för var bokstav med generell frekvenns för ett visst språk. Ju mindre värde dessto mer lika är textfilen ett språk.
 
 
 - Vilka svårigheter som fanns, vad du tyckte var besvärligt?
 
 - Hur du löste problemen:
 
 
 
 Om det finns frågor att besvara i uppgiften ska det göras här.
 -I lösningsförslagen tipsar vi om att man ska skapa/ladda hem en fil med bara lite innehåll medan man testar sitt program. Varför, tror du?
 
 *Eftersom det är lätt att överblicka om det stämer, man kan till och med räkna antal bokstäver själv i huvudet och jämnföra det med programkörningen.
 
 -Texten i filen lagerlof.txt innehåller de svenska bokstäverna å, ä och ö. Som programet fungerar nu räknas inte dessa bokstäver alls. Hur skulle man gå tillväga för att också inkludera å, ä och ö i histogrammet? Du behöver inte ge en program-lösning, men resonera kring hur man skulle kunna göra.
 
 *Skapa en array med värdena som kommer efter de 26 bokstäverna, tex. svenska_bokstavar[] {26, 27, 28}
 för å, ä & ö.
 
 
 */
