#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>

class Item
{
private:
    std::string NombreItem;
    std::string DescripcionItem;
    float PrecioItem;
    
public:
    Item(std::string _NombreItem, std::string _DescripcionItem, float _PrecioItem)
    {
        NombreItem = _NombreItem;
        DescripcionItem = _DescripcionItem;
        PrecioItem = _PrecioItem;
    }

    std::string GetNombreItem()
    {
        return NombreItem;
    }

    std::string GetDescripcionItem()
    {
        return DescripcionItem;
    }

    float GetPrecioItem()
    {
        return PrecioItem;
    }
};


class Personaje{
private:
    std::string nombre;
    int vida;
    int danio;
    int defensa;
    int XP;
    std::vector<Item> Inventario;
public:
    Personaje(int _vida, int _danio, std::string _nombre, int _defensa,int _XP)
    {
        vida = _vida;
        danio = _danio;
        nombre = _nombre;
        defensa = _defensa;
        XP = _XP;
    }

    void fn_TomarDanio(int danioATomar)
    {
        vida -= danioATomar;
    }

    int GetVida()
    {
        return vida;
    }

    int GetDanio()
    {
        return danio;
    }

    std::string GetNombre()
    {
        return nombre;
    }

    int GetDefensa()
    {
        return defensa;
    }
    
    void CheckInventory()
    {
        int index = 1;

        for(Item i : Inventario)
        {
            std::cout<<index<<". "<<i.GetNombreItem()<<"/n"<<i.GetDescripcionItem()<<std::endl;
            index+=1;
        }
    }

    int GetXP()
    {
        return XP;
    }

    void GenerateXP()
    {
        srand(time(0));
        rand() % (10 - 5 +1) + 5;
    }
    
};

class Jugador : public Personaje{

public:
    Jugador(int _vida, int _danio, std::string _nombre, int _defensa,int _XP): Personaje(_vida,_danio,_nombre, _defensa, _XP)
    {

    }
};

class Enemigo : public Personaje
{
public:
    Enemigo(int _vida, int _danio, std::string _nombre, int _defensa,int _XP): Personaje(_vida,_danio,_nombre, _defensa, _XP)
    {

    }

   
};

void fn_PressAnyKey();
void fn_MenuJuego();
void fn_MostrarMenuCombate();
void fn_MostrarVida(Jugador _j, Enemigo _e);
void fn_JugadorAtaca(Jugador& _j, Enemigo& _e);
void fn_EnemigoAtaca(Jugador& _j, Enemigo& _e, int _opcion);
void fn_EncuentroCombate(Jugador& _j, Enemigo& _e);
void fn_ExplorarPueblo();

int main()
{
	

    Jugador j(10,20,"Juan",5,0);
    Enemigo e(20,5,"el diablo", 5, 5);

    //fn_EncuentroCombate(j,e);

    e.GenerateXP();

    std::cout<<"Enemigo XP: "<<e.GetXP();
    fn_PressAnyKey();
    std::cout<<"Enemigo XP: "<<e.GetXP();
    fn_PressAnyKey();
    std::cout<<"Enemigo XP: "<<e.GetXP();
    fn_PressAnyKey();
}

void fn_PressAnyKey()
{
    std::cout<<"\nPRESIONA CUALQUIER TECLA PARA CONTINUAR...";
    getch();
    system("cls");
}


void fn_MostrarMenuCombate()
{
    std::cout<<"1.-ATTACK\n2.-DEFEND\n\n9.-EXIT\nOpcion: ";
}

void fn_MostrarVida(Jugador _j, Enemigo _e)
{
    std::cout<<"Vida "<<_j.GetNombre()<<": "<< _j.GetVida()<<" |";
    std::cout<<" Vida "<<_e.GetNombre()<<": "<<_e.GetVida()<<std::endl;
}

void fn_JugadorAtaca(Jugador& _j, Enemigo& _e)
{
    std::cout<<_j.GetNombre()<< " ataca a "<<_e.GetNombre()<<" haciendo "<<_j.GetDanio()<<" de danio";
    _e.fn_TomarDanio(_j.GetDanio());
    fn_PressAnyKey();

}

void fn_EnemigoAtaca(Jugador& _j, Enemigo& _e, int _opcion)
{
    std::cout<<_e.GetNombre()<< " ataca a "<<_j.GetNombre()<<" haciendo "<<_e.GetDanio()<<" de danio";
    fn_PressAnyKey();
    if(_opcion == 2)
    {
        std::cout<<_j.GetNombre()<<" se defiende! mitigando "<<_j.GetDefensa()<<" de danio";
        _j.fn_TomarDanio(_e.GetDanio()-_j.GetDefensa());
        fn_PressAnyKey();
    }else
    {
        _j.fn_TomarDanio(_e.GetDanio());
    }
}

void fn_EncuentroCombate(Jugador& _j, Enemigo& _e)
{
    int opcion;

     do
    {
        fn_MostrarVida(_j,_e);
        fn_MostrarMenuCombate();
        std::cin>>opcion;

        switch (opcion)
        {
        case 1:

            fn_JugadorAtaca(_j,_e);

            if(_e.GetVida()>0)
            {
                fn_EnemigoAtaca(_j,_e,opcion);
            }else
            {
                break;
            }
        case 2:
            fn_EnemigoAtaca(_j,_e,opcion);
            break;
        case 9:
            exit(0);
            break;   
        default:
            std::cout<<"OPCION INVALIDA, POR FAVOR INTENTA DE NUEVO";
            std::cin.clear();
            std::cin.ignore();
            fn_PressAnyKey();           
            break;
        }
    }while(_j.GetVida()>0 && _e.GetVida()>0);

    if(_j.GetVida() <= 0)
    {
        std::cout<<_j.GetNombre()<<" ha muerto";
    }else if(_e.GetVida() <= 0)
    {
        std::cout<<"Felicidades! derrotaste a "<<_e.GetNombre();
    }
}

void fn_MenuJuego()
{
    std::cout<<"~~~~~~~~~~ NECROMANCER ~~~~~~~~~~"<<std::endl;
    std::cout<<"1.- Entrar a Mazmorra"<<std::endl;
    std::cout<<"2.- Ir al pueblo"<<std::endl;
}

void fn_TiendaItems()
{
    std::cout<< "~~~~~~~~~~ TIENDA ~~~~~~~~~~"<<std::endl;
    std::cout<< " ";
}

void fn_ExplorarPueblo()
{
    int opc;
    while(true)
    {
        std::cout<<"~~~~~~~~~~PUEBLO~~~~~~~~~~"<<std::endl;
        std::cout<<"1.-Tienda"<<std::endl;
        std::cout<<"9.-Salir"<<std::endl;
        std::cout<<"Opcion: ";
        std::cin>>opc;
        switch(opc)
        {
            case 1:

        break;

        }
    }
}

