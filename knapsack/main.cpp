#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void sac_a_dos(vector<int> &w , vector<int> &v , int n , int W){
    int profit = 0 ;
    //on crée la matrice de taille n+1 * W+1;
    vector<vector<int>> P(n + 1,vector<int>(W + 1));
    vector<int> res(n);

    for(int i = 0 ; i < n+1 ; i++){
        for(int j = 0 ; j < W+1 ; j++){
            if(i == 0 || j == 0) {
                P[i][j] = 0;
            }
            else if( j - w[i-1] < 0 ){
                P[i][j] = P[i-1][j];
            }
            else {
                P[i][j] =  max(P[i-1][j], P[i-1][j - w[i-1]] + v[i-1]);
            }
        }
    }

    for(int i = 0 ; i < n+1 ; i++){
        for(int j = 0 ; j < W+1 ; j++){
            cout << P[i][j] << " ";
        }
        cout <<endl;
    }
    profit = P[n][W];

    //partie pour afficher les objets selectionnés
    int i = n , nombre = P[n][W];
    bool trouve = false;
    while( i > 0 ){
        i = i -1;
        if(i == 0 && (nombre == 0)){
            res[i] = 0;
        }
        else {
            for(int k =0 ;k < W+1 ; k++) {
                if(P[i][k] ==  nombre){
                    trouve = true;
                    break;
                }
            }

            if( !trouve){
                res[i] = 1;
                nombre -= v[i];
            } else {
                res[i] = 0;
            }
            trouve = false;
        }

    }

    cout << endl << "la valeur maximale pouvant etre obtenue est "<< profit <<endl;

    //affichage
    for(int i = 0 ; i < n  ; i++){
        cout << "objet " << i+1 << " : poids = " << w[i] << " valeur = " << v[i] << " nombre = " << res[i] << endl;
    }

}

int main()
{
    int W,n;

    cout <<endl<< "\t\t-----------------ALGORITHME DU SAC A DOS--------------------\n" <<endl;
    cout << "Veuillez entrer le poids total de votre sac : ";
    cin >> W ;

    // on vérifie que le poids entré n'est pas inférieur ou égal à 0
    if(W < 0 ) {
        cout << "votre poids dois etre superieur ou egal a 0" <<endl;
    }

    cout << "Veuillez entrer votre nombre d'objets : ";
    cin >> n;
    cout <<endl;

    //on vérifie que le nombre d'objects entré n'est pas inferieur à 0
    if(W <= 0 ) {
        cout << "votre nombre d'objets dois etre superieur ou egal a 0" <<endl;
    }

    /*on déclare deux vecteurs de taille n , l'un contenant les poids de chaque objets et l'autre les valeurs
    et on les initialise à 0*/
    vector<int> w(n,0), v(n,0),x(n,0);
    for(int i = 0 ; i < n ; i ++ ){
        cout << "veuillez entrer le poids de l'objet "<< i+1 <<" : ";
        cin >> w[i];
        cout  << "veuilez entrer la valeur de l'objet " << i+1 <<" : " ;
        cin >> v[i];
        cout <<endl;
    }

    // on implémente l'algo de sac à dos
    sac_a_dos(w,v,n,W);



    return 0;
}
