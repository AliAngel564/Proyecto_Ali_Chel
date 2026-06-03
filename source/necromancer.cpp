#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
 
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
 
    void fn_ClearScreen()
    {
        system("cls");
    }
 
#else
    #include <termios.h>
    #include <unistd.h>
 
    int getch()
    {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);          
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);        
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
        ch = getchar();                           
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
        return ch;
    }
 
    void fn_ClearScreen()
    {
        system("clear");
    }
 
#endif


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

public:
    Personaje(int _vida, int _danio, std::string _nombre, int _defensa, int _XP)
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

    void SetVida(int _vida)
    {
        vida = _vida;
    }

    int GetDanio()
    {
        return danio;
    }

    void SetDanio(int _danio)
    {
        danio = _danio;
    }

    std::string GetNombre()
    {
        return nombre;
    }

    int GetDefensa()
    {
        return defensa;
    }

    void SetDefensa(int _defensa)
    {
        defensa = _defensa;
    }

    int GetXP()
    {
        return XP;
    }

    void GenerateXP()
    {
        XP += rand() % (10 - 5 + 1) + 5;
    }
};


class Jugador : public Personaje{
private:
    float dinero;
    int nivel;
    int vidaBase;
    int danioBase;
    int defensaBase;
    int vidaMaxima;
    std::vector<Item> Inventario;
    int capacidadInventario;

public:
    Jugador(int _vida, int _danio, std::string _nombre, int _defensa, int _XP): Personaje(_vida, _danio, _nombre, _defensa, _XP)
    {
        dinero = 50.0f;
        nivel = 1;
        vidaBase = _vida;
        danioBase = _danio;
        defensaBase = _defensa;
        vidaMaxima = _vida;
        capacidadInventario = 5;
    }

    int GetVidaMaxima()
    {
        return vidaMaxima;
    }

    float GetDinero()
    {
        return dinero;
    }

    void SetDinero(float _dinero)
    {
        dinero = _dinero;
    }

    int GetNivel()
    {
        return nivel;
    }

    int GetTamanioInventario()
    {
        return Inventario.size();
    }

    int GetCapacidadInventario()
    {
        return capacidadInventario;
    }

    bool AgregarItem(Item _item)
    {
        if((int)Inventario.size() >= capacidadInventario)
        {
            std::cout << "Inventario lleno! (max " << capacidadInventario << " items)" << std::endl;
            return false;
        }
        Inventario.push_back(_item);
        return true;
    }

    bool SoltarItem(int _index)
    {
        if(_index < 0 || _index >= (int)Inventario.size())
        {
            std::cout << "Item invalido" << std::endl;
            return false;
        }
        std::cout << Inventario[_index].GetNombreItem() << " eliminado del inventario" << std::endl;
        Inventario.erase(Inventario.begin() + _index);
        return true;
    }

    void CheckInventory()
    {
        if(Inventario.empty())
        {
            std::cout << "Inventario vacio" << std::endl;
            return;
        }
        int index = 1;
        for(Item i : Inventario)
        {
            std::cout << index << ". " << i.GetNombreItem() << "\n   " << i.GetDescripcionItem() << std::endl;
            index += 1;
        }
    }

    Item GetItem(int _index)
    {
        return Inventario[_index];
    }

    void ActualizarNivel()
    {
        int nuevoNivel = 1 + (GetXP() / 20);
        if(nuevoNivel > nivel)
        {
            nivel = nuevoNivel;
            SetDanio(danioBase + (nivel - 1) * 5);
            SetDefensa(defensaBase + (nivel - 1) * 2);
            vidaMaxima = vidaBase + (nivel - 1) * 10;
            SetVida(vidaMaxima);
            std::cout << "\n*** SUBISTE AL NIVEL " << nivel << "! ***" << std::endl;
            std::cout << "Danio: " << GetDanio() << " | Defensa: " << GetDefensa() << std::endl;
        }
    }
};

class Enemigo : public Personaje
{
public:
    Enemigo(int _vida, int _danio, std::string _nombre, int _defensa, int _XP): Personaje(_vida, _danio, _nombre, _defensa, _XP)
    {

    }
};

void fn_PressAnyKey();
void fn_MenuJuego(Jugador& _j);
void fn_MostrarMenuCombate();
void fn_MostrarVida(Jugador _j, Enemigo _e);
void fn_JugadorAtaca(Jugador& _j, Enemigo& _e);
void fn_EnemigoAtaca(Jugador& _j, Enemigo& _e, int _opcion);
void fn_EncuentroCombate(Jugador& _j, Enemigo& _e);
void fn_ExplorarPueblo(Jugador& _j);
void fn_TiendaItems(Jugador& _j);
void fn_MazmorraGrindeo(Jugador& _j);
void fn_MazmorraFinal(Jugador& _j);
void fn_UsarInventario(Jugador& _j);
void fn_Intro();
int fn_LeerOpcion();

int main()
{
    srand(time(0));

    Jugador j(50, 10, "Ardelia", 5, 0);

    fn_Intro();

    int opcion;
    do
    {
        fn_MenuJuego(j);
        opcion = fn_LeerOpcion();

        switch(opcion)
        {
            case 1:
                fn_MazmorraGrindeo(j);
                break;
            case 2:
                fn_MazmorraFinal(j);
                break;
            case 3:
                fn_ExplorarPueblo(j);
                break;
            case 4:
                fn_UsarInventario(j);
                break;
            case 9:
                std::cout << "Hasta luego..." << std::endl;
                return 0;
            default:
                std::cout << "OPCION INVALIDA" << std::endl;
                fn_PressAnyKey();
                break;
        }

    } while(j.GetVida() > 0);

    std::cout << "\n========================================" << std::endl;
    std::cout << "   " << j.GetNombre() << " ha caido en batalla..." << std::endl;
    std::cout << "   El Necromante sigue reinando." << std::endl;
    std::cout << "           GAME OVER" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}

int fn_LeerOpcion()
{
    int opcion;
    while(!(std::cin >> opcion))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Opcion invalida, ingresa un numero: ";
    }
    std::cin.ignore(1000, '\n');
    return opcion;
}

void fn_Intro()
{
    fn_ClearScreen();
    std::cout << "========================================" << std::endl;
    std::cout << "          N E C R O M A N C E R        " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nUn Necromante ha invadido las tierras de tu reino." << std::endl;
    std::cout << "Gana experiencia en la mazmorra, consigue equipo" << std::endl;
    std::cout << "en el pueblo, y enfrentalo cuando estes lista." << std::endl;
    std::cout << "\nBuena suerte, aventurera." << std::endl;
    fn_PressAnyKey();
}


void fn_MazmorraGrindeo(Jugador& _j)
{
    fn_ClearScreen();
    std::cout << "~~~~~~~~~~ MAZMORRA DE ENTRENAMIENTO ~~~~~~~~~~" << std::endl;
    std::cout << "Nivel: " << _j.GetNivel() << " | XP: " << _j.GetXP() << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "1.- Explorar (combate)" << std::endl;
    std::cout << "9.- Volver" << std::endl;
    std::cout << "Opcion: ";

    int opc;
    opc = fn_LeerOpcion();

    switch(opc)
    {
        case 1:
        {
            int vidaEnemigo    = 30 + (_j.GetNivel() * 10);
            int danioEnemigo   = 5  + (_j.GetNivel() * 2);
            int defensaEnemigo = 2  + (_j.GetNivel() * 1);

            std::string nombres[] = {"Esqueleto", "Zombie", "Espectro", "Golem de carne"};
            std::string nombreEnemigo = nombres[rand() % 4];

            Enemigo e(vidaEnemigo, danioEnemigo, nombreEnemigo, defensaEnemigo, 10);
            fn_EncuentroCombate(_j, e);

            if(e.GetVida() <= 0)
            {
                _j.GenerateXP();
                std::cout << "\nGanaste XP! Total: " << _j.GetXP() << std::endl;
                _j.ActualizarNivel();

                int oro = rand() % 9 + 2;
                _j.SetDinero(_j.GetDinero() + oro);
                std::cout << "Encontraste $" << oro << " de oro!" << std::endl;
            }
            fn_PressAnyKey();
            break;
        }
        case 9:
            break;
        default:
            std::cout << "OPCION INVALIDA" << std::endl;
            fn_PressAnyKey();
            break;
    }
}

void fn_MazmorraFinal(Jugador& _j)
{
    fn_ClearScreen();
    std::cout << "~~~~~~~~~~ GUARIDA DEL NECROMANTE ~~~~~~~~~~" << std::endl;
    std::cout << "Un aura oscura lo cubre todo...\nno hay retorno." << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    if(_j.GetNivel() < 3)
    {
        std::cout << "Sientes un aura abrumadora." << std::endl;
        std::cout << "No estas lista, regresa cuando tengas mas experiencia." << std::endl;
        fn_PressAnyKey();
        return;
    }

    std::cout << "Nivel: " << _j.GetNivel() << " | Vida: " << _j.GetVida() << std::endl;
    std::cout << "\n1.- Enfrentar al Necromante" << std::endl;
    std::cout << "9.- Retroceder" << std::endl;
    std::cout << "Opcion: ";

    int opc;
    opc = fn_LeerOpcion();

    if(opc == 1)
    {
        std::cout << "\nTe adentras en lo mas profundo..." << std::endl;
        std::cout << "El Necromante te espera." << std::endl;
        fn_PressAnyKey();

        Enemigo necromante(200, 20, "El Necromante", 15, 100);
        fn_EncuentroCombate(_j, necromante);

        if(necromante.GetVida() <= 0)
        {
            fn_ClearScreen();
            std::cout << "========================================" << std::endl;
            std::cout << "Contra todo pronostico saliste victoriosa" << std::endl;
            std::cout << "El reino esta a salvo gracias a ti." << std::endl;
            std::cout << "\tFIN" << std::endl;
            std::cout << "========================================" << std::endl;
            fn_PressAnyKey();
            exit(0);
        }
    }
}


void fn_PressAnyKey()
{
    std::cout<<"\nPRESIONA CUALQUIER TECLA PARA CONTINUAR...";
    getch();
    fn_ClearScreen();
}


void fn_MenuJuego(Jugador& _j)
{
    std::cout << "\n~~~~~~~~~~ NECROMANTE ~~~~~~~~~~" << std::endl;
    std::cout << "Nivel: " << _j.GetNivel() << " | XP: " << _j.GetXP() << " | Dinero: $" << _j.GetDinero() << std::endl;
    std::cout << "Vida: " << _j.GetVida() << "/" << _j.GetVidaMaxima() << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "1.- Mazmorra de entrenamiento" << std::endl;
    std::cout << "2.- Guarida del Necromante" << std::endl;
    std::cout << "3.- Ir al pueblo" << std::endl;
    std::cout << "4.- Ver inventario" << std::endl;
    std::cout << "9.- Salir" << std::endl;
    std::cout << "Opcion: ";
}

void fn_MostrarMenuCombate()
{
    std::cout<<"1.-ATTACK\n2.-DEFEND\n3.-USAR ITEM\n\n9.-EXIT\nOpcion: ";
}

void fn_MostrarVida(Jugador _j, Enemigo _e)
{
    std::cout<<"Vida "<<_j.GetNombre()<<": "<< _j.GetVida()<<" |";
    std::cout<<" Vida "<<_e.GetNombre()<<": "<<_e.GetVida()<<std::endl;
}

void fn_JugadorAtaca(Jugador& _j, Enemigo& _e)
{
    int danioReal = rand() % (_j.GetDanio() / 2 + 1) + (_j.GetDanio() / 2);
    std::cout<<_j.GetNombre()<< " ataca a "<<_e.GetNombre()<<" haciendo "<<danioReal<<" de danio";
    _e.fn_TomarDanio(danioReal);
    fn_PressAnyKey();
}

void fn_EnemigoAtaca(Jugador& _j, Enemigo& _e, int _opcion)
{
    int danioReal = rand() % (_e.GetDanio() / 2 + 1) + (_e.GetDanio() / 2);
    std::cout<<_e.GetNombre()<< " ataca a "<<_j.GetNombre()<<" haciendo "<<danioReal<<" de danio";
    fn_PressAnyKey();
    if(_opcion == 2)
    {
        std::cout<<_j.GetNombre()<<" se defiende! mitigando "<<_j.GetDefensa()<<" de danio";
        _j.fn_TomarDanio(danioReal - _j.GetDefensa());
        fn_PressAnyKey();
    }else
    {
        _j.fn_TomarDanio(danioReal);
    }
}

void fn_EncuentroCombate(Jugador& _j, Enemigo& _e)
{
    int opcion;

    do
    {
        fn_MostrarVida(_j,_e);
        fn_MostrarMenuCombate();
        opcion = fn_LeerOpcion();

        switch (opcion)
        {
        case 1:
            fn_JugadorAtaca(_j,_e);
            if(_e.GetVida()>0) fn_EnemigoAtaca(_j,_e,opcion);
            break;
            
        case 2:
            fn_EnemigoAtaca(_j,_e,opcion);
            break;
        case 3:
            fn_UsarInventario(_j);
            if(_e.GetVida()>0) fn_EnemigoAtaca(_j,_e,opcion);
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
        std::cout<<_j.GetNombre()<<" ha caido en batalla";
    }else if(_e.GetVida() <= 0)
    {
        std::cout<<"Felicidades! derrotaste a "<<_e.GetNombre()<<"!";
    }
}


void fn_UsarInventario(Jugador& _j)
{
    fn_ClearScreen();
    std::cout << "--- INVENTARIO (" << _j.GetTamanioInventario() << "/" << _j.GetCapacidadInventario() << ") ---" << std::endl;
    _j.CheckInventory();

    if(_j.GetTamanioInventario() == 0)
    {
        fn_PressAnyKey();
        return;
    }

    std::cout << "\nUsar item (numero, 0 para cancelar): ";
    int idx = fn_LeerOpcion();

    if(idx == 0 || idx > _j.GetTamanioInventario()) return;

    Item itemElegido = _j.GetItem(idx - 1);

    if(itemElegido.GetNombreItem() == "Pocion de vida")
    {
        if(_j.GetVida() >= _j.GetVidaMaxima())
        {
            std::cout << "Tu vida ya esta al maximo!" << std::endl;
            fn_PressAnyKey();
        }
        else
        {
            int vidaNueva = _j.GetVida() + 30;
            if(vidaNueva > _j.GetVidaMaxima()) vidaNueva = _j.GetVidaMaxima();
            _j.SetVida(vidaNueva);
            _j.SoltarItem(idx - 1);
            std::cout << "Usaste la pocion! Vida: " << _j.GetVida() << "/" << _j.GetVidaMaxima() << std::endl;
            fn_PressAnyKey();
        }
    }
    else if(itemElegido.GetNombreItem() == "Pocion de fuerza")
    {
        _j.SetDanio(_j.GetDanio() + 5);
        _j.SoltarItem(idx - 1);
        std::cout << "Usaste la pocion! Danio actual: " << _j.GetDanio() << std::endl;
        fn_PressAnyKey();
    }
    else
    {
        std::cout << itemElegido.GetNombreItem() << " no se puede usar directamente." << std::endl;
        fn_PressAnyKey();
    }
}


void fn_TiendaItems(Jugador& _j)
{
    Item catalogo[] = {
        Item("Pocion de vida",    "Restaura 30 de vida",         25.0f),
        Item("Espada de hierro",  "Aumenta tu danio en 10",      60.0f),
        Item("Escudo de madera",  "Aumenta tu defensa en 5",     40.0f),
        Item("Pocion de fuerza",  "Aumenta tu danio en 5",       30.0f),
    };
    int tamCatalogo = 4;

    int opc;
    do
    {
        fn_ClearScreen();
        std::cout << "~~~~~~~~~~ TIENDA ~~~~~~~~~~" << std::endl;
        std::cout << "Tu dinero: $" << _j.GetDinero() << std::endl;
        std::cout << "----------------------------" << std::endl;

        for(int i = 0; i < tamCatalogo; i++)
        {
            std::cout << i+1 << ". " << catalogo[i].GetNombreItem()
                      << " - $" << catalogo[i].GetPrecioItem()
                      << "\n   " << catalogo[i].GetDescripcionItem() << std::endl;
        }

        std::cout << "\n5.- Ver/Usar inventario" << std::endl;
        std::cout << "9.- Salir de la tienda" << std::endl;
        std::cout << "Opcion: ";
        opc = fn_LeerOpcion();

        if(opc >= 1 && opc <= tamCatalogo)
        {
            Item itemElegido = catalogo[opc - 1];
            if(_j.GetDinero() < itemElegido.GetPrecioItem())
            {
                std::cout << "No tienes suficiente dinero!" << std::endl;
            }
            else if(_j.GetTamanioInventario() >= _j.GetCapacidadInventario())
            {
                std::cout << "Inventario lleno!" << std::endl;
            }
            else
            {
                _j.SetDinero(_j.GetDinero() - itemElegido.GetPrecioItem());

                if(itemElegido.GetNombreItem() == "Pocion de vida")
                {
                    _j.AgregarItem(itemElegido);
                    std::cout << "Pocion guardada en inventario!" << std::endl;
                }
                else if(itemElegido.GetNombreItem() == "Espada de hierro")
                {
                    _j.SetDanio(_j.GetDanio() + 10);
                    _j.AgregarItem(itemElegido);
                    std::cout << "Equipaste la espada! Danio actual: " << _j.GetDanio() << std::endl;
                }
                else if(itemElegido.GetNombreItem() == "Escudo de madera")
                {
                    _j.SetDefensa(_j.GetDefensa() + 5);
                    _j.AgregarItem(itemElegido);
                    std::cout << "Equipaste el escudo! Defensa actual: " << _j.GetDefensa() << std::endl;
                }
                else if(itemElegido.GetNombreItem() == "Pocion de fuerza")
                {
                    _j.AgregarItem(itemElegido);
                    std::cout << "Pocion guardada en inventario!" << std::endl;
                }

                std::cout << "Compraste: " << itemElegido.GetNombreItem()
                          << " | Dinero restante: $" << _j.GetDinero() << std::endl;
            }
            fn_PressAnyKey();
        }
        else if(opc == 5)
        {
            fn_UsarInventario(_j);
        }

    } while(opc != 9);
}


void fn_ExplorarPueblo(Jugador& _j)
{
    int opc;
    do
    {
        fn_ClearScreen();
        std::cout << "~~~~~~~~~~PUEBLO~~~~~~~~~~" << std::endl;
        std::cout << "1.- Tienda" << std::endl;
        std::cout << "9.- Salir" << std::endl;
        std::cout << "Opcion: ";
        opc = fn_LeerOpcion();
        switch(opc)
        {
            case 1:
                fn_TiendaItems(_j);
                break;
            case 9:
                break;
            default:
                std::cout << "OPCION INVALIDA" << std::endl;
                fn_PressAnyKey();
                break;
        }
    } while(opc != 9);
}