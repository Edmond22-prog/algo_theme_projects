#include <iostream>
#include <math.h>

using namespace std;

// renvoyer la taille d'un nombre
int getSize(int num)
{
    int count = 0;
    while (num > 0)
    {
        count++;
        num /= 10;
    }
    return count;
}

// algorithme de karashuba
int karatsuba(int X, int Y)
{
    // Cas de base
    if (X < 10 && Y < 10)
        return X * Y;

    // determiner la taille maximale entre celles de X et Y
    int n = fmax(getSize(X), getSize(Y));

    // Diviser les nombre X et Y
    int k = (int)ceil(n / 2); // arrondi au plus petit entier >= n/2
    
    int p = (int)pow(10, k); // 10^k
    int a = (int)floor(X / p);
    int b = X % p;
    int c = (int)floor(Y / p);
    int d = Y % p;

    // Appels récursifs
    int ac = karatsuba(a, c);
    int bd = karatsuba(b, d);
    int e = ac + bd - karatsuba(a - b, c - d); // e = (ad+bc) * 10^k = ac + bd - (a-b)(c-d)

    // retourner le résultat d'après la formule : ac * 10^2k + e * 10^k + bd
    return (int)(pow(10, 2*k) * ac + pow(10, k) * e + bd);
}

// lire un polynome et extraire ces coefficients
// sous forme d'un entier
int getEntier(int n)
{
    string P("");
    for (int i = n; i >= 0; i--)
    {
        int coef(0);
        cout << "coefficient de degre " << i << ": >> ";
        cin >> coef;
        P += to_string(coef);
    }
    return stoi(P);
}

int main(int argc, char const *argv[])
{
    int n, P(10), Q(203);
    // cout << endl
    //     << "======================= Produit DE DEUX POLYNOMES ===========" << endl
    //     << endl;

    // // premier polynome
    // cout << "-------- Premier polynome --------" << endl
    //     << endl;
    // cout << "entrer son degre : ";
    // cin >> n;
    // P = getEntier(n);
    // cout << endl
    //     << "Entier correspondant : " << P << endl
    //     << endl;

    // // deuxième polynome
    // cout << "-------- Deuxieme polynome --------" << endl
    //     << endl;
    // cout << "entrer son degre : ";
    // cin >> n;
    // Q = getEntier(n);
    // cout << endl
    //     << "Entier correspondant : " << Q << endl
    //     << endl;

    // multiplication par l'algo de karatshuba
    int R = karatsuba(P, Q);
    cout << "Le resultat de la multiplication est : "
        << R << endl
        << endl;

    return 0;
}
