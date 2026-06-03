# Necromante

Un Necromante levantó ejércitos de no-muertos y amenaza al reino. Eres Ardelia, la única aventurera dispuesta a hacerle frente. Gana experiencia en la Mazmorra de Entrenamiento, consigue equipo en el pueblo, y cuando estés lista, entra a su Guarida.

Aventura de texto por turnos hecha en C++.

---

## Cómo compilar y ejecutar

**Linux / Mac**
```bash
g++ necromancer.cpp -o necromancer
./necromancer
```

**Windows**
```bash
g++ necromancer.cpp -o necromancer.exe
necromancer.exe
```

Requiere g++ con soporte C++11 o superior.

---

## Controles

Toda la interacción es con números y Enter.

| Input | Acción |
|-------|--------|
| `1` | Mazmorra de entrenamiento / Atacar |
| `2` | Guarida del Necromante / Defender |
| `3` | Ir al pueblo / Usar item en combate |
| `4` | Ver inventario |
| `9` | Volver / Salir |

---

## Cómo se juega

- Entra a la **Mazmorra de Entrenamiento** para pelear, ganar XP y subir de nivel
- Ve al **Pueblo** a comprar pociones y equipo con el oro que consigues
- Cuando llegues al **nivel 3**, puedes entrar a la **Guarida del Necromante** y enfrentarlo
- Si tu vida llega a 0 en cualquier combate, es Game Over

---

## Autor y versión

**Autor:** Ali Angel  
**Versión:** 1.0  
**Materia:** Tecnología de la Programación — Universidad Amerike
