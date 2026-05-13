#include <iostream>
#include <conio.h>

class Personaje{
private:
    std::string nombre;
    int vida;
    int danio;
    int defensa;
public:
    Personaje(int _vida, int _danio, std::string _nombre, int _defensa)
    {
        vida = _vida;
        danio = _danio;
        nombre = _nombre;
        defensa = _defensa;
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
};

class Jugador : public Personaje{

public:
    Jugador(int _vida, int _danio, std::string _nombre, int _defensa): Personaje(_vida,_danio,_nombre, _defensa)
    {

    }
};

class Enemigo : public Personaje
{
public:
    Enemigo(int _vida, int _danio, std::string _nombre, int _defensa): Personaje(_vida,_danio,_nombre, _defensa)
    {

    }
};

void fn_PressAnyKey();
void fn_MostrarMenu();
void fn_MostrarVida(Jugador _j, Enemigo _e);
void fn_JugadorAtaca(Jugador& _j, Enemigo& _e);
void fn_EnemigoAtaca(Jugador& _j, Enemigo& _e, int& _opcion);

int main()
{


}

void fn_PressAnyKey()
{
    std::cout<<"\nPRESIONA CUALQUIER TECLA PARA CONTINUAR...";
    getch();
    system("cls");
}


void fn_MostrarMenu()
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

void fn_EnemigoAtaca(Jugador& _j, Enemigo& _e, int& _opcion)
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
