// C++ program to find minimum number of coins

#include <bits/stdc++.h>
using namespace std;
 
// La fonction prend en parametre la somme à rembourser, l'ensemble des valeurs des pieces qui seront utilisees et un parametre n qui contient la taille de ce vecteur de pieces 
std::vector<int> MinNumCoins(int somme, int pieces[], int n)
{
    // premiere etape (tri de la liste dans l'ordre croissant de valeurs de pieces)
    sort(pieces, pieces + n); 

    // Initialisation du vecteur resultat
    vector<int> result(n);
 
    
    //initialisation du compteur permettant de parcourir les differentes pieces
    int i = 1; 

    // Comme le tableau est trié dans l'ordre croissant nous prendront les pieces de la derniere à la première.
    while (somme > 0 & i<=n) {

        // la matrice du resultat contient dans chaque case le nombre de fois que la piece correspondante à cet indice est prise
        result[i-1] = somme / pieces[n-i];

        // Ensuite je decremente la valeur de la somme de la valeur qui est deja prise avec la piece precedente*nombre d'occurence de cette piece
        somme = somme - result[i-1] * pieces[n-i];

        // Incrementation du compteur pour passer à la prochaine valeur de piece
        i = i+1;
    }
 
    return result;
}
 
// Driver Code
int main()
{
    cout << "Entrez le nombre de pieces disponibles : ";
    int n, s;
    cin >> n;
    int c[n];
    for (int i = 0; i < n; i++) {
        cout << "Entrez la valeur de la piece " << i+1 << " : ";
        cin >> c[i];
    }
    cout << "Entrez la somme à rembourser : ";
    cin >> s;
    
    int len_c = (sizeof(c) / sizeof(c[0]));
    sort(c, c + len_c);

    //Appel de la fonction
    vector<int> r(n);
    r = MinNumCoins(s, c, len_c);

    // Affichage du resultat
    cout << "\n" ;
    int somme_finale = 0;
    for (int i = 0; i < n; i++){
        if (r[i] != 0) 
        {
            cout << " " << c[n-i-1] << " (" << r[i] << " fois) \t";
            somme_finale = somme_finale + (r[i]*c[n-i-1]);
        }
    }
    cout << "\n";
    if (s != somme_finale)
    {
        string chaine = "\n Mais l'algorithme n'est pas optimal car la somme remboursee est " + to_string(somme_finale) + " au lieu de " + to_string(s) + "\n";
        cout << chaine;
    }
    
    return 0;
}