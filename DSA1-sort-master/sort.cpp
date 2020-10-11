// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2019

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
           << pData->firstName << " " 
           << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);
  return 0;
}
// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.











































#include <iterator>
#include <cmath>
#include <unordered_map> 

class ssnObject {
public:
  int data;
  string ssn;
  ssnObject(){}
  ssnObject(int data, string ssn){}
  int returnData(){return this->data;}
  string returnSSN(){return this->ssn;}
};

int stdSort[1200000];
//int arr[3][1000000];
//ssnObject radix[3][1200000];
Data dumbArray[10000000];
Data *dumbPointers[250000];




std::vector<std::string> firstNames={"AALIYAH","AARON","ABEL","ABIGAIL","ABRAHAM","ADALINE","ADALYN","ADALYNN","ADAM","ADDISON","ADELINE","ADELYN","ADRIAN","ADRIANA","AIDAN","AIDEN","ALAINA","ALAN","ALANA","ALAYNA","ALEJANDRO","ALEX","ALEXA","ALEXANDER","ALEXANDRA","ALEXIS","ALICE","ALINA","ALIVIA","ALIYAH","ALLISON","ALYSSA","AMARA","AMAYA","AMELIA","AMIR","AMY","ANA","ANASTASIA","ANDREA","ANDRES","ANDREW","ANGEL","ANGELA","ANGELINA","ANNA","ANNABELLE","ANTHONY","ANTONIO","ARABELLA","ARIA","ARIANA","ARIANNA","ARIEL","ARTHUR","ARYA","ASHER","ASHLEY","ASHTON","ATHENA","AUBREE","AUBREY","AUDREY","AUGUST","AURORA","AUSTIN","AUTUMN","AVA","AVERY","AVERY","AXEL","AYDEN","AYLA","BAILEY","BARRETT","BEAU","BECKETT","BELLA","BENJAMIN","BENNETT","BENTLEY","BLAKE","BRADLEY","BRADY","BRANDON","BRANTLEY","BRAXTON","BRAYDEN","BRIAN","BRIANNA","BRIELLE","BRODY","BROOKE","BROOKLYN","BROOKLYNN","BROOKS","BRYAN","BRYCE","BRYNLEE","BRYSON","CADEN","CALEB","CALLIE","CALVIN","CAMDEN","CAMERON","CAMILA","CARLOS","CAROLINE","CARSON","CARTER","CATHERINE","CAYDEN","CECILIA","CHARLES","CHARLIE","CHARLIE","CHARLOTTE","CHASE","CHLOE","CHRISTIAN","CHRISTOPHER","CLAIRE","CLARA","CLAYTON","COLE","COLIN","COLTON","CONNOR","COOPER","CORA","DAISY","DAKOTA","DALEYZA","DAMIAN","DANIEL","DANIELA","DAVID","DAWSON","DEAN","DECLAN","DELANEY","DELILAH","DEREK","DESTINY","DIANA","DIEGO","DOMINIC","DYLAN","EASTON","EDEN","EDWARD","ELEANOR","ELENA","ELI","ELIANA","ELIAS","ELIJAH","ELISE","ELIZA","ELIZABETH","ELLA","ELLIANA","ELLIE","ELLIOT","ELLIOTT","ELOISE","EMERSON","EMERSYN","EMERY","EMILIA","EMILIANO","EMILY","EMMA","EMMANUEL","EMMETT","ERIC","ESTHER","ETHAN","EVA","EVAN","EVELYN","EVERETT","EVERLY","EZEKIEL","EZRA","FAITH","FELIX","FINLEY","FINN","FIONA","GABRIEL","GABRIELLA","GAEL","GAVIN","GENESIS","GENEVIEVE","GEORGE","GEORGIA","GIANNA","GIOVANNI","GRACE","GRACIE","GRAHAM","GRANT","GRAYSON","GREYSON","GRIFFIN","HADLEY","HAILEY","HANNAH","HARLEY","HARMONY","HARPER","HARRISON","HAYDEN","HAYDEN","HAZEL","HENRY","HOLDEN","HUDSON","HUNTER","IAN","IRIS","ISAAC","ISABEL","ISABELLA","ISABELLE","ISAIAH","ISLA","ISRAEL","IVAN","IVY","JACE","JACK","JACKSON","JACOB","JADE","JADEN","JAKE","JAMES","JAMESON","JASMINE","JASON","JASPER","JAVIER","JAX","JAXON","JAXSON","JAYCE","JAYDEN","JAYLA","JEREMIAH","JEREMY","JESSE","JESSICA","JESUS","JOANNA","JOCELYN","JOEL","JOHN","JONAH","JONATHAN","JORDAN","JORDYN","JORGE","JOSE","JOSEPH","JOSEPHINE","JOSHUA","JOSIAH","JOSIE","JOSUE","JUAN","JUDAH","JUDE","JULIA","JULIAN","JULIANA","JULIANNA","JULIET","JULIETTE","JUNE","JUSTIN","KADEN","KAI","KAIDEN","KALEB","KARTER","KATHERINE","KAYDEN","KAYLA","KAYLEE","KENDALL","KENNEDY","KENNETH","KEVIN","KHLOE","KILLIAN","KIMBERLY","KING","KINGSTON","KINSLEY","KNOX","KYLE","KYLIE","KYRIE","LAILA","LANDON","LAUREN","LAYLA","LEAH","LEILA","LEILANI","LEO","LEON","LEONARDO","LEVI","LIAM","LILA","LILIANA","LILLIAN","LILLY","LILY","LINCOLN","LOGAN","LOLA","LONDON","LONDYN","LORENZO","LUCA","LUCAS","LUCIA","LUCY","LUIS","LUKAS","LUKE","LUNA","LYDIA","LYLA","MACKENZIE","MADDOX","MADELINE","MADELYN","MADISON","MAGGIE","MAKAYLA","MALACHI","MALIA","MARCUS","MARGARET","MARIA","MARIAH","MARK","MARLEY","MARY","MASON","MATEO","MATIAS","MATTEO","MATTHEW","MAVERICK","MAX","MAXIMUS","MAXWELL","MAYA","MCKENZIE","MELANIE","MELODY","MESSIAH","MIA","MICAH","MICHAEL","MICHELLE","MIGUEL","MILA","MILES","MILO","MOLLY","MORGAN","MYA","MYLES","NAOMI","NATALIA","NATALIE","NATHAN","NATHANIEL","NEVAEH","NICHOLAS","NICOLAS","NICOLE","NOAH","NOELLE","NOLAN","NORA","NORAH","NOVA","OLIVER","OLIVIA","OMAR","OSCAR","OWEN","PAIGE","PAISLEY","PARKER","PARKER","PATRICK","PAUL","PAXTON","PAYTON","PENELOPE","PETER","PEYTON","PIPER","PRESLEY","PRESTON","QUINN","RACHEL","RAELYNN","REAGAN","REBECCA","REESE","REMI","REMINGTON","RHETT","RICHARD","RILEY","RIVER","ROBERT","ROMAN","ROSALIE","ROSE","ROWAN","ROWAN","RUBY","RYAN","RYDER","RYKER","RYLEE","RYLEIGH","SADIE","SAMANTHA","SAMUEL","SANTIAGO","SARA","SARAH","SAVANNAH","SAWYER","SAWYER","SCARLETT","SEBASTIAN","SELENA","SERENITY","SIENNA","SILAS","SKYLAR","SLOANE","SOFIA","SOPHIA","SOPHIE","STELLA","STEVEN","SUMMER","SYDNEY","TAYLOR","TEAGAN","TESSA","THEODORE","THIAGO","THOMAS","TIMOTHY","TRINITY","TRISTAN","TUCKER","TYLER","VALENTINA","VALERIA","VALERIE","VANESSA","VICTOR","VICTORIA","VINCENT","VIOLET","VIVIAN","WAYLON","WESLEY","WESTON","WILLIAM","WILLOW","WYATT","XANDER","XAVIER","XIMENA","ZACHARY","ZANDER","ZANE","ZAYDEN","ZION","ZOE","ZOEY"};

std::vector<std::string> lastNames={"ACOSTA","ADAMS","ADKINS","AGUILAR","AGUIRRE","ALEXANDER","ALLEN","ALVARADO","ALVAREZ","ANDERSON","ANDREWS","ARMSTRONG","ARNOLD","AUSTIN","AVILA","AYALA","BAILEY","BAKER","BALDWIN","BANKS","BARBER","BARKER","BARNES","BARNETT","BARRETT","BARTON","BATES","BECK","BECKER","BELL","BENNETT","BENSON","BERRY","BISHOP","BLACK","BLAIR","BLAKE","BOWEN","BOWMAN","BOYD","BRADLEY","BRADY","BREWER","BROOKS","BROWN","BRYANT","BURGESS","BURKE","BURNS","BURTON","BUSH","BUTLER","BYRD","CABRERA","CALDERON","CALDWELL","CAMACHO","CAMPBELL","CAMPOS","CANNON","CARDENAS","CARLSON","CARPENTER","CARR","CARRILLO","CARROLL","CARTER","CASTANEDA","CASTILLO","CASTRO","CERVANTES","CHAMBERS","CHAN","CHANDLER","CHANG","CHAPMAN","CHAVEZ","CHEN","CHRISTENSEN","CLARK","CLARKE","COHEN","COLE","COLEMAN","COLLINS","COLON","CONTRERAS","COOK","COOPER","CORTEZ","COX","CRAIG","CRAWFORD","CROSS","CRUZ","CUMMINGS","CUNNINGHAM","CURRY","CURTIS","DANIEL","DANIELS","DAVIDSON","DAVIS","DAWSON","DAY","DEAN","DELACRUZ","DELEON","DELGADO","DENNIS","DIAZ","DIXON","DOMINGUEZ","DOUGLAS","DOYLE","DUNCAN","DUNN","DURAN","EDWARDS","ELLIOTT","ELLIS","ERICKSON","ESPINOZA","ESTRADA","EVANS","FARMER","FERGUSON","FERNANDEZ","FIELDS","FIGUEROA","FISCHER","FISHER","FITZGERALD","FLEMING","FLETCHER","FLORES","FORD","FOSTER","FOWLER","FOX","FRANCIS","FRANCO","FRANK","FRANKLIN","FRAZIER","FREEMAN","FUENTES","FULLER","GALLAGHER","GALLEGOS","GARCIA","GARDNER","GARNER","GARRETT","GARZA","GEORGE","GIBSON","GILBERT","GILL","GOMEZ","GONZALES","GONZALEZ","GOODMAN","GOODWIN","GORDON","GRAHAM","GRANT","GRAVES","GRAY","GREEN","GREENE","GREGORY","GRIFFIN","GRIFFITH","GROSS","GUERRA","GUERRERO","GUTIERREZ","GUZMAN","HAIL","HALE","HALL","HAMILTON","HAMMOND","HAMPTON","HANSEN","HANSON","HARDY","HARMON","HARPER","HARRINGTON","HARRIS","HARRISON","HART","HARVEY","HAWKINS","HAYES","HAYNES","HENDERSON","HENRY","HERNANDEZ","HERRERA","HICKS","HIGGINS","HILL","HINES","HODGES","HOFFMAN","HOLLAND","HOLMES","HOLT","HOPKINS","HORTON","HOWARD","HOWELL","HUANG","HUBBARD","HUDSON","HUGHES","HUNT","HUNTER","INGRAM","JACKSON","JACOBS","JAMES","JENKINS","JENNINGS","JENSEN","JIMENEZ","JOHNSON","JOHNSTON","JONES","JORDAN","JOSEPH","JUAREZ","KELLER","KELLEY","KELLY","KENNEDY","KHAN","KIM","KING","KLEIN","KNIGHT","LAMBERT","LANE","LARA","LARSON","LAWRENCE","LAWSON","LE","LEE","LEON","LEONARD","LEWIS","LI","LIN","LITTLE","LIU","LOGAN","LONG","LOPEZ","LOVE","LOWE","LUCAS","LUNA","LYNCH","LYONS","MACK","MALDONADO","MALONE","MANN","MANNING","MARQUEZ","MARSHALL","MARTIN","MARTINEZ","MASON","MATTHEWS","MAXWELL","MAY","MCCARTHY","MCCOY","MCDANIEL","MCDONALD","MCGEE","MCKINNEY","MCLAUGHLIN","MEDINA","MEJIA","MENDEZ","MENDOZA","MEYER","MILES","MILLER","MILLS","MIRANDA","MITCHELL","MOLINA","MONTGOMERY","MONTOYA","MOORE","MORALES","MORAN","MORENO","MORGAN","MORRIS","MORRISON","MOSS","MULLINS","MUNOZ","MURPHY","MURRAY","MYERS","NAVARRO","NEAL","NELSON","NEWMAN","NEWTON","NGUYEN","NICHOLS","NORMAN","NORRIS","NUNEZ","OBRIEN","OCHOA","OCONNOR","OLIVER","OLSON","ORTEGA","ORTIZ","OWENS","PACHECO","PADILLA","PAGE","PALMER","PARK","PARKER","PARKS","PARSONS","PATEL","PATTERSON","PAUL","PAYNE","PEARSON","PENA","PEREZ","PERKINS","PERRY","PERSON","PETERS","PETERSON","PHAM","PHILLIPS","PIERCE","PORTER","POTTER","POWELL","POWERS","PRICE","QUINN","RAMIREZ","RAMOS","RAMSEY","RAY","REED","REESE","REEVES","REID","REYES","REYNOLDS","RHODES","RICE","RICHARDS","RICHARDSON","RILEY","RIOS","RIVAS","RIVERA","ROBBINS","ROBERTS","ROBERTSON","ROBINSON","ROBLES","RODGERS","RODRIGUEZ","ROGERS","ROJAS","ROMAN","ROMERO","ROSALES","ROSE","ROSS","ROWE","RUIZ","RUSSELL","RYAN","SALAZAR","SALINAS","SANCHEZ","SANDERS","SANDOVAL","SANTIAGO","SANTOS","SAUNDERS","SCHMIDT","SCHNEIDER","SCHROEDER","SCHULTZ","SCHWARTZ","SCOTT","SERRANO","SHARP","SHAW","SHELTON","SHERMAN","SILVA","SIMMONS","SIMON","SIMPSON","SIMS","SINGH","SMITH","SNYDER","SOLIS","SOTO","SPENCER","STANLEY","STEELE","STEPHENS","STEVENS","STEVENSON","STEWART","STONE","STRICKLAND","SULLIVAN","SUTTON","SWANSON","TATE","TAYLOR","TERRY","THOMAS","THOMPSON","THORNTON","TODD","TORRES","TOWNSEND","TRAN","TRUJILLO","TUCKER","TURNER","VALDEZ","VALENCIA","VARGAS","VASQUEZ","VAUGHN","VAZQUEZ","VEGA","VELASQUEZ","WADE","WAGNER","WALKER","WALLACE","WALSH","WALTERS","WALTON","WANG","WARD","WARNER","WARREN","WASHINGTON","WATERS","WATKINS","WATSON","WATTS","WEAVER","WEBB","WEBER","WEBSTER","WELCH","WELLS","WEST","WHEELER","WHITE","WILLIAMS","WILLIAMSON","WILLIS","WILSON","WISE","WOLF","WOLFE","WONG","WOOD","WOODS","WRIGHT","WU","YANG","YOUNG","ZHANG","ZIMMERMAN"};

unordered_map<string,int> firstNameMap;
unordered_map<string,int> lastNameMap;















int checkSortCase(list<Data*> &l){
    auto it = l.begin();
    auto it2 = it++;
    if( (l.front()->firstName==l.back()->firstName) && (l.front()->lastName==l.back()->lastName)){
        cout << " Case 4" << endl;
        return 4;
    }
    else if (( (*it)->lastName==(*it2)->lastName )){
        cout << " Case 3" <<endl;
        return 3;
    }
    else{
        cout << "Case 1 or 2" << endl;
        return 1;
    }
}
int convertSSN(string ssn, int cut){
  string removed; 
  int converted;
  for(int i=0;i<11-cut;i++){
      if (isdigit(ssn[i])){
        removed=removed+ssn[i];
      }
  }

  char *rmvptr = &removed[0];
  while(*rmvptr){
    converted = converted*10 +(*rmvptr++ - '0');
  }
  return converted;
}

int fastSSN(string ssn){
  int toAdd;
   toAdd=(ssn[0]-'0')*100000000+(ssn[1]-'0')*10000000+(ssn[2]-'0')*1000000+(ssn[4]-'0')*100000+(ssn[5]-'0')*10000+(ssn[7]-'0')*1000+(ssn[8]-'0')*100+(ssn[9]-'0')*10+(ssn[10]-'0');
   return toAdd;
}

string safeconvertSSN(string ssn){
  string removed; 
  for(int i=0;i<11;i++){
      if (isdigit(ssn[i])){
        removed=removed+ssn[i];
      }
  }
  return removed;
}

bool compareFunction(Data *a, Data *b){
    if (a->lastName != b->lastName){
        return a->lastName < b->lastName;
    }
     else if (a->firstName != b->firstName){
        return a->firstName < b->firstName;
    } 
    else {
        return a->ssn < b->ssn;
    }
}

bool compareFunction2(Data *a, Data *b){
    if (a->firstName != b->firstName){
        return 0;
    }
    else {
        return a->ssn < b->ssn;
    }
}
bool compareFunction3(Data *a, Data *b){
  const int aVal= lastNameMap[a->lastName]+firstNameMap[a->firstName];
  const int bVal= lastNameMap[b->lastName]+firstNameMap[b->firstName];

    if (aVal!=bVal){
        return aVal < bVal;
    } 
    else {
        return a->ssn < b->ssn;
    }
}
bool justSSNcompare(Data *a, Data *b){
  return a->ssn < b->ssn;
}


bool insertionBootLegCheck(string k, string key){//tries to use very few digits initially for insertion sort comparisons
  if(convertSSN(k, 10) > convertSSN(key, 10)) return true;
  else if (convertSSN(k, 10) == convertSSN(key, 10)){
    if(convertSSN(k, 9) > convertSSN(key,9)) return true;
    else if (convertSSN(k, 9) == convertSSN(key,9)){
      if (convertSSN(k, 0) > convertSSN(key,0)) return true;
    }
  }
  return false;
}

/* Not being used */
void insertionSort(list<Data*> &l){ // I dont use this, this was my first implementation. Here for testing purposes.
    int arraysize, j;
    string key;
    auto itAnchor = l.begin();
    auto endAnchor = l.end();
    endAnchor--;
    auto itTemp = itAnchor;

    while(itAnchor!=endAnchor){
      
      for(arraysize=0; ( (*itTemp)->firstName == (*itAnchor)->firstName ) && (itTemp != endAnchor); arraysize++) itTemp++; //iterate to find group of same last first
      string arr[arraysize];
      itTemp = itAnchor; 

      for(int i=0; i<arraysize; i++){ //copy that group into an array
        arr[i]=(*itTemp)->ssn;
        itTemp++;
      } 

      for(int i=1; i<(arraysize); i++){ //insertion sort
        key = (arr[i]);
        j=i-1;

        while( j>=0 && insertionBootLegCheck(arr[j], key)){
          arr[j+1] = arr[j];
          j--;
        }
        arr[j+1]=key;
      }
      for(int i=1; i<arraysize+1; i++){//copying array values to actual list
        (*itAnchor)->ssn=arr[i-1];
        itAnchor++;
      }
    //itAnchor is currently on the next group. now repeat until it reaches end iterator... 
    }
}

/* Not being used */


void insertionSort2( list<Data *> &l) { 
  //this is so much faster than making an array every single time wow
  //it completely cuts the need to do ssn-->int conversion and making arrays and then putting everything back together
        auto begin = l.begin();
        auto end = l.end();
        list<Data *>::iterator itr;
        for( list<Data *>::iterator i = next(begin, 1); i != end; i++ ){ //same idea as doing this with arrays, just with iterators and direct editting now
            Data* temp= *i; //set temp to what we're on right now
            for(itr = i; (itr != begin) && (compareFunction2(temp, *(prev(itr,1)))); itr-- ){
              //compare to previous nodes until reach first. Swap when find one that it's greater or reach end(start of list, or lower value name).
                *itr = *(prev(itr,1));
            }
            *itr  = temp;
        }
}


/* Not being used */
int getMax(ssnObject arr[], int n){
  int max = arr[0].data;
  for (int i=1; i<n ; i++){
    if (arr[i].data>max) max=arr[i].data;
  }
  return max;
}

/* Not being used */
void countSort(ssnObject arr[], ssnObject output[], int n, int exp){
  int i,count[10]={0};

  for( i=0; i<n; i++)
    count[ (arr[i].data/exp)%10 ]++;
  for (i = 1; i < 10; i++) 
    count[i] += count[i - 1]; 

  for (i = n - 1; i >= 0; i--){ 
      output[count[(arr[i].data/exp)%10 ] - 1] = arr[i]; 
      count[ (arr[i].data/exp)%10 ]--; 
  } 

  for (i=0; i<n; i++){
    arr[i]=output[i];
  }
}

/* Not being used... unless i can make it much much faster lol*/
void radixSort(ssnObject arr[], ssnObject output[], int n){
  int max = getMax(arr, n);

  for (int exp=1; max/exp >1000; exp*=10)
    countSort(arr, output, n , exp);
}








void sortDataList(list<Data *> &l) { 
int sortCase = checkSortCase(l);
    if(sortCase==1){
    
    int count =0;
    list<Data *>::iterator it = l.begin();
    for(int i=0; i<500;i++){
      firstNameMap[firstNames[i]]=i;
      lastNameMap[lastNames[i]]=1000*i; //for unique combination
    }

    for(int i=0; i<250000; i++){
      dumbPointers[i]=&dumbArray[i*20];
    }
    for(int i=0; it!=l.end();i++){
      int placementVal = lastNameMap[(*it)->lastName]+firstNameMap[(*it)->firstName];
      int corPoint = 500*(placementVal/1000) + placementVal%1000;
      dumbPointers[corPoint]++;
      dumbPointers[corPoint]->firstName=(*it)->firstName;
      dumbPointers[corPoint]->lastName=(*it)->lastName;
      dumbPointers[corPoint]->ssn=(*it)->ssn;
      it++;
    }

    it = l.begin();
      for(int i=0; i<250000; i++){
        while(dumbPointers[i]->firstName!=""){
          (*it)->firstName=dumbPointers[i]->firstName;
          (*it)->lastName=dumbPointers[i]->lastName;
          (*it)->ssn=dumbPointers[i]->ssn;
          dumbPointers[i]--;
          count++;
          it++;
        }
      }
    insertionSort2(l);
    }
    
    else if(sortCase==3){
      insertionSort2(l);
    }

    else if(sortCase==4){//convert this to integers and use standard sort. Array of integers is much faster to sort. Quick int->str conversion with ASCII codes.
      list<Data *>::iterator it = l.begin();
       string toGrab;
      int toAdd;

      for(int i=0; it!=l.end(); i++){
        toGrab=(*it)->ssn;
        toAdd=fastSSN(toGrab);
        stdSort[i]=toAdd;
    //  radix[0][i].data=toAdd;
    //  radix[0][i].ssn=toGrab;
        it++;
      }
      it=l.begin();
      const int size = sizeof(stdSort)/sizeof(stdSort[0]);
      std::sort(stdSort, stdSort+size, less<int>());
      const int sizeDiff=size - l.size();
      for(int i=0; it!=l.end(); i++){
        (*it)->ssn='0'+stdSort[sizeDiff+i]/100000000%10;
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/10000000%10;
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/1000000%10;
         (*it)->ssn+="-";
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/100000%10;
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/10000%10;
        (*it)->ssn+="-";
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/1000%10;
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/100%10;
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/10%10;
        (*it)->ssn+='0'+stdSort[sizeDiff+i]/1%10;
        it++;
      }
      /*it=l.begin();
      radixSort(radix[0],radix[1],size);
      for(int i=0;it!=l.end();i++){
        (*it)->ssn=radix[1][i].ssn;
        it++;
      }*/
    }
}