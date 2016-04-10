/*
    TODO:
    - Buscar paper donde se haya utilizado el algoritmo the Karcain y Sanders
    - Buscar numero de repeticiones.
    - Buscar localizacion.
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

const int MAX = 200005;
int N, h, sa[MAX], pos[MAX], tmp[MAX], lcp[MAX];
 
// Structure to store information of a suffix
struct suffix
{
    int index;
    char *suff;
};

struct suffix suffixes[MAX];
 
// A comparison function used by sort() to compare two suffixes
int cmp(struct suffix a, struct suffix b)
{
    return strcmp(a.suff, b.suff) < 0? 1 : 0;
}
 
// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
int *buildSuffixArray(char *txt, int n)
{
    //cout << "\nWord: " << txt << endl << endl;
    //cout << n << endl;

    //cout << "Suffixes: " << endl;

    // A structure to store suffixes and their indexes

 
    // Store suffixes and their indexes in an array of structures.
    // The structure is needed to sort the suffixes alphabatically
    // and maintain their old indexes while sorting
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suff = (txt+i);
        //cout << i << ": " << suffixes[i].suff << endl;
    }
 
    // Sort the suffixes using the comparison function
    // defined above.
    sort(suffixes, suffixes+n, cmp);
 
    // Store indexes of all sorted suffixes in the suffix array
    int *suffixArr = new int[n];
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;
 
    // cout << "\nSuffixes Array: " << endl;
    // for(int i = 0; i < n; i++)

    // cout << suffixArr[i] << ": " << suffixes[/*suffixArr[*/i/*]*/].suff << endl;
    // cout << endl;

    // Return the suffix array
    return  suffixArr;
}
 
// A utility function to print an array of given size
void printArr(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

bool compare(int i, int j) {
  if(pos[i] != pos[j]) return pos[i] < pos[j]; // compare by the first h chars
  i += h, j += h; // if prefvious comparing failed, use 2*h chars
  return (i < N && j < N) ? pos[i] < pos[j] : i > j; // return results
}

void build(char *str) {
  N = strlen(str);
  for(int i=0; i<N; ++i) sa[i] = i, pos[i] = str[i]; // initialize variables
  for(h=1;;h<<=1) {
    sort(sa, sa+N, compare); // sort suffixes
    for(int i=0; i<N-1; ++i) tmp[i+1] = tmp[i] + compare(sa[i], sa[i+1]); // bucket suffixes
    for(int i=0; i<N; ++i) pos[sa[i]] = tmp[i]; // update pos (reverse mapping of suffix array)
    if(tmp[N-1] == N-1) break; // check if done
  }
}

void lcp_compute(char *str) {
  for(int i=0, k=0; i<N; ++i)
    if(pos[i] != N-1) {
      for(int j=sa[pos[i]+1]; str[i+k] == str[j+k];) k++;
      lcp[pos[i]] = k;
      if(k) k--;
    }
}

void printLCP(int n) {
    int ocurrencies = 1; 
    int biggest = lcp[0];
    int index = 0;

    for(int i = 0 ; i < n ; i++) {
        if (lcp[i - 1] > biggest) {
            biggest = lcp[i - 1];
            index = i - 1;
        }   
    }

    string LCP = suffixes[index].suff;
    cout << "\nLongest common prefix: ";
    for(int j = 0 ; j < biggest ; j++) {
        cout << LCP[j];
    }

    cout << "\nNumber of ocurrencies: ";
    int count = 1;
    int tempIndex = index;
    while(lcp[tempIndex] == biggest) {
        count++;
        tempIndex++;
    }
    cout << count << endl;

    cout << "Ocurrencies: " << endl;
    int k = 1;
    for(int i = index ; i < index + count ; i++) {
        cout << "\t" << k << ") " << suffixes[i].suff << endl;
        k++;
    }
    cout << endl;
}
 
// Driver program to test above functions
int main()
{
    //char txt[] = "como_odio_las_profesoras_que_se_ponen_a_dar_clases_normales_un_dia_antes_de_vacaciones_de_semana_santa,_como_si_nos_fuesemos_a_acordar._espero_con_ansias_semana_santa_y_estar_en_la_chacra_con_mis_amigos._cuenta_atras_para_que_me_den_las_vacaciones_de_semana_santa._buenas_noches!!!_ya_viene_semana_santa._en_semana_santa_quiero_irme_de_misiones..._a_dubai._todos_somos_ateos,_hasta_que_nos_dicen_en_la_escuela_que_nos_daran_dos_semanas_de_vacaciones_de_semana_santa._con_tantos_trabajos_y_examenes_no_me_emociona_ni_mi_cumpleanos_ni_la_semana_santa._solo_ya_quiero_que_comienze_semana_santa._¿en_semana_santa_no_se_rumbea?_ay_no_pues,_que_haremos_con_las_dignas._estoy_que_les_pongo_una_veladora._que_ganas_de_que_sea_semana_santa_para_no_saber_ni_como_me_llamo.";
    //char txt[] = "mississippi";
    char txt[] = "freexfreedyfreshz";
    //char txt[] = "I stand here today humbled by the task before us, grateful for the trust you have bestowed, mindful of the sacrifices borne by our ancestors. I thank President Bush for his service to our nation, as well as the generosity and cooperation he has shown throughout this transition. Forty-four Americans have now taken the presidential oath. The words have been spoken during rising tides of prosperity and the still waters of peace. Yet, every so often the oath is taken amidst gathering clouds and raging storms. At these moments, America has carried on not simply because of the skill or vision of those in high office, but because We the People have remained faithful to the ideals of our forbearers, and true to our founding documents. So it has been. So it must be with this generation of Americans. That we are in the midst of crisis is now well understood. Our nation is at war, against a far-reaching network of violence and hatred. Our economy is badly weakened, a consequence of greed and irresponsibility on the part of some, but also our collective failure to make hard choices and prepare the nation for a new age. Homes have been lost; jobs shed; businesses shuttered. Our health care is too costly; our schools fail too many; and each day brings further evidence that the ways we use energy strengthen our adversaries and threaten our planet. Thank you. Thank you very much. It is an honor as always, my fellow Republicans, to join you at our national convention and add my voice to yours as we nominate the next president of the United States, my friend, Governor Mitt Romney. I had hopes once of addressing under different circumstances, but our fellow Americans had another plan four years ago and I accept their decision. I thank President Bush for his service to our nation. I am conscious of the debt I owe America.  And I thank you for the honor. When we nominate Mitt Romney, we do so with a greater purpose than winning an advantage for our party.  We charged him with the care of by a higher cause.  His election represents the best hopes for our country, and the world. It is said that this election will turn on domestic and economic issues.  But what Mitt Romney knows, and what we know is the success at home also depends on our leadership in the world.  It is our willingness to shape world events for the better that has kept a safe, increased our prosperity, preserved our liberty and transformed human history. At our best, America has led.  We have led by our example as a shining city on a hill.  We have lead in the direction of patriots from both parties.  We have led shoulder to shoulder with steadfast friends and allies.";


    int n = strlen(txt);

    build(txt);
    lcp_compute(txt);
    int *suffixArr = buildSuffixArray(txt,  n);
    printLCP(n);
    
    return 0;
}