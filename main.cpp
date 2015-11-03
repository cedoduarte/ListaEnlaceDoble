#include <iostream>
#include <cstdlib>

using namespace std;

class Nodo
{
public:
    Nodo(int numero = 0)
        : mNumero(numero)
        , mSiguiente(NULL)
        , mAnterior(NULL)
    {
    }

    void setNumero(int numero) { mNumero = numero; }
    void setSiguiente(Nodo *siguiente) { mSiguiente = siguiente; }
    void setAnterior(Nodo *anterior) { mAnterior = anterior; }
    Nodo *getSiguiente() const { return mSiguiente; }
    Nodo *getAnterior() const { return mAnterior; }
    int getNumero() const { return mNumero; }
private:
    int mNumero;
    Nodo *mSiguiente;
    Nodo *mAnterior;
};

class Programa
{
public:
    Programa()
        : mInicio(NULL)
        , mFinal(NULL)
    {
    }

    void inicia();
private:
    enum Opcion
    {
        CREA_INICIO = 1,
        CREA_FINAL,
        RECORRIDO_DE_LA_LISTA,
        RECORRE_RECURSIVO,
        RECORRE_REVERSA,
        INSERTA_AL_INICIO,
        INSERTA_AL_FINAL,
        INSERTA_ANTES_DE_X,
        INSERTA_DESPUES_DE_X,
        ELIMINA_PRIMERO,
        ELIMINA_ULTIMO,
        ELIMINA_X,
        ELIMINA_ANTES_DE_X,
        ELIMINA_DESPUES_DE_X,
        BUSQUEDA_DESORDENADA,
        BUSQUEDA_ORDENADA,
        SALIR
    };

    void creaInicio();
    void creaFinal();
    void recorridoDeLaLista();
    void recorreRecursivo(Nodo *nodo) const;
    void recorreRecursivo() const;
    void recorreReversa() const;
    void insertaAlInicio();
    void insertaAlFinal();
    void insertaAntesDeX();
    void insertaDespuesDeX();
    void eliminaPrimero();
    void eliminaUltimo();
    void eliminaX();
    void eliminaAntesDeX();
    void eliminaDespuesDeX();
    void busquedaDesordenada() const;
    void busquedaOrdenada() const;
    void salir() const;
    Nodo *getX(int x) const;

    void imprimeMenu() const;
    void leeOpcion();

    Nodo *mInicio;
    Nodo *mFinal;
};

int main()
{
    Programa programa;
    programa.inicia();
    return 0;
}

void Programa::inicia()
{
    while (true) {
        imprimeMenu();
        leeOpcion();
    }
}

void Programa::creaInicio()
{
    int numero;
    cout << "numero: ";
    cin >> numero;
    mInicio = new Nodo(numero);
    if (!mFinal) {
        mFinal = mInicio;
    } else {
        mFinal->setAnterior(mInicio);
        mInicio->setSiguiente(mFinal);
    }
}

void Programa::creaFinal()
{
    int numero;
    cout << "numero: ";
    cin >> numero;
    mFinal = new Nodo(numero);
    if (!mInicio) {
        mInicio = mFinal;
    } else {
        mInicio->setSiguiente(mFinal);
        mFinal->setAnterior(mInicio);
    }
}

void Programa::recorridoDeLaLista()
{
    for (Nodo *ix = mInicio; ix != NULL; ix = ix->getSiguiente()) {
        cout << ix->getNumero() << ' ';
    }
    cout << endl;
}

void Programa::recorreRecursivo(Nodo *nodo) const
{
    if (!nodo) {
        return;
    }
    cout << nodo->getNumero() << ' ';
    recorreRecursivo(nodo->getSiguiente());
}

void Programa::recorreRecursivo() const
{
    recorreRecursivo(mInicio);
    cout << endl;
}

void Programa::recorreReversa() const
{
    Nodo *ix = mFinal;
    while (ix != NULL) {
        cout << ix->getNumero() << ' ';
        ix = ix->getAnterior();
    }
    cout << endl;
}

void Programa::insertaAlInicio()
{
    if (!mInicio) {
        cout << "no existe inicio" << endl;
        return;
    }
    int numero;
    cout << "numero: ";
    cin >> numero;
    Nodo *nodo = new Nodo(numero);
    nodo->setSiguiente(mInicio);
    mInicio->setAnterior(nodo);
    mInicio = nodo;
}

void Programa::insertaAlFinal()
{
    if (!mFinal) {
        cout << "no existe final" << endl;
        return;
    }
    int numero;
    cout << "numero: ";
    cin >> numero;
    Nodo *nodo = new Nodo(numero);
    nodo->setAnterior(mFinal);
    mFinal->setSiguiente(nodo);
    mFinal = nodo;
}

void Programa::insertaAntesDeX()
{
    int x;
    cout << "x: ";
    cin >> x;
    Nodo *ix = getX(x);
    if (!ix) {
        cout << "no hay x = " << x << endl;
        return;
    }
    int numero;
    cout << "numero: ";
    cin >> numero;
    Nodo *nodo = new Nodo(numero);

    if (ix == mInicio) {
        mInicio->setAnterior(nodo);
        nodo->setSiguiente(mInicio);
        mInicio = nodo;
        return;
    }

    Nodo *A = ix->getAnterior();
    A->setSiguiente(nodo);
    nodo->setAnterior(A);
    nodo->setSiguiente(ix);
    ix->setAnterior(nodo);
}

void Programa::insertaDespuesDeX()
{
    int x;
    cout << "x: ";
    cin >> x;
    Nodo *ix = getX(x);
    if (!ix) {
        cout << "no hay x = " << x << endl;
        return;
    }
    int numero;
    cout << "numero: ";
    cin >> numero;
    Nodo *nodo = new Nodo(numero);

    if (ix == mFinal) {
        mFinal->setSiguiente(nodo);
        nodo->setAnterior(mFinal);
        mFinal = nodo;
        return;
    }

    Nodo *A = ix->getSiguiente();
    ix->setSiguiente(nodo);
    nodo->setAnterior(ix);
    nodo->setSiguiente(A);
    A->setAnterior(nodo);
}

void Programa::eliminaPrimero()
{
    mInicio = mInicio->getSiguiente();
}

void Programa::eliminaUltimo()
{
    Nodo *nodo = mFinal->getAnterior();
    nodo->setSiguiente(NULL);
    mFinal = nodo;
}

void Programa::eliminaX()
{
    int x;
    cout << "x: ";
    cin >> x;
    Nodo *ix = getX(x);
    if (!ix) {
        cout << "no hay x = " << x << endl;
        return;
    }
    Nodo *A = ix->getAnterior();
    Nodo *B = ix->getSiguiente();
    A->setSiguiente(B);
    B->setAnterior(A);
}

void Programa::eliminaAntesDeX()
{
    int x;
    cout << "x: ";
    cin >> x;
    Nodo *ix = getX(x);
    if (!ix) {
        cout << "no hay x = " << x << endl;
        return;
    }
    Nodo *A = ix->getAnterior();
    Nodo *A2 = A->getAnterior();
    A2->setSiguiente(ix);
    ix->setAnterior(A2);
}

void Programa::eliminaDespuesDeX()
{
    int x;
    cout << "x: ";
    cin >> x;
    Nodo *ix = getX(x);
    if (!ix) {
        cout << "no hay x = " << x << endl;
        return;
    }
    Nodo *A = ix->getSiguiente();
    Nodo *B = A->getSiguiente();
    ix->setSiguiente(B);
    B->setAnterior(ix);
}

void Programa::busquedaDesordenada() const
{
    int numero;
    cout << "numero: ";
    cin >> numero;
    Nodo *nodo = getX(numero);
    if (nodo) {
        cout << "Si existe el elemento " << numero << endl;
    } else {
        cout << "NO existe el elemento " << numero << endl;
    }
}

void Programa::busquedaOrdenada() const
{
    busquedaDesordenada();
}

void Programa::salir() const
{
    exit(EXIT_SUCCESS);
}

Nodo *Programa::getX(int x) const
{
    for (Nodo *ix = mInicio; ix != NULL; ix = ix->getSiguiente()) {
        if (ix->getNumero() == x) {
            return ix;
        }
    }
    return NULL;
}

void Programa::imprimeMenu() const
{
    string opciones[] = {
        "crea inicio",
        "crea final",
        "recorrido de la lista",
        "recorre recursivo",
        "recorre reversa",
        "inserta al inicio",
        "inserta al final",
        "inserta antes de x",
        "inserta despues de x",
        "elimina primero",
        "elimina ultimo",
        "elimina x",
        "elimina antes de x",
        "elimina despues de x",
        "busqueda desordenada",
        "busqueda ordenada",
        "salir"
    };
    const int tam = sizeof(opciones) / sizeof(string);
    for (int ix = 0; ix < tam; ++ix) {
        cout << (ix + 1) << ". " << opciones[ix] << endl;
    }
    cout << ": ";
}

void Programa::leeOpcion()
{
    int opcion;
    cin >> opcion;
    switch (opcion) {
    case CREA_INICIO:
        creaInicio();
        break;
    case CREA_FINAL:
        creaFinal();
        break;
    case RECORRIDO_DE_LA_LISTA:
        recorridoDeLaLista();
        break;
    case RECORRE_RECURSIVO:
        recorreRecursivo();
        break;
    case RECORRE_REVERSA:
        recorreReversa();
        break;
    case INSERTA_AL_INICIO:
        insertaAlInicio();
        break;
    case INSERTA_AL_FINAL:
        insertaAlFinal();
        break;
    case INSERTA_ANTES_DE_X:
        insertaAntesDeX();
        break;
    case INSERTA_DESPUES_DE_X:
        insertaDespuesDeX();
        break;
    case ELIMINA_PRIMERO:
        eliminaPrimero();
        break;
    case ELIMINA_ULTIMO:
        eliminaUltimo();
        break;
    case ELIMINA_X:
        eliminaX();
        break;
    case ELIMINA_ANTES_DE_X:
        eliminaAntesDeX();
        break;
    case ELIMINA_DESPUES_DE_X:
        eliminaDespuesDeX();
        break;
    case BUSQUEDA_DESORDENADA:
        busquedaDesordenada();
        break;
    case BUSQUEDA_ORDENADA:
        busquedaOrdenada();
        break;
    case SALIR:
        salir();
        break;
    }
}
